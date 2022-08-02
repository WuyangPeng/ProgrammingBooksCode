/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "GameServer.h"

#include "..\gamelib\File.h"
#include "..\gamecommon\ents\gameEnt.h"
#include <string>
using namespace std;

void PlayGameSound( resID id )
{
}

#define SERVER_LISTENPORT	4000	// the port the server is listening for data on.
#define CLIENT_LISTENPORT	4001	// the port the client is listening for data on.

extern void EbPrintf( TCHAR* first, ... );
extern void AddPlayer( TCHAR* playerName );
extern void RemovePlayer( TCHAR* playerName );


string		g_IPAddress;	// If server, what address do we connect to?
MTUDP		g_comm;	// the network comm class
HOSTHANDLE	g_serverHost;	// the handle to the server host.

// The world
cGameWorld* g_pWorld;

bool IsClient()
{
	return false;
}

objID GetClientID()
{
	// shouldn't go here.
	assert(-1);
	return -1;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cGameServer::cGameServer()
{
}

cGameServer::~cGameServer()
{

}

void cGameServer::Initialize()
{
	EbPrintf( L"Server starting up..." );
	MsgDaemon()->RegObject( g_gameServer, this );

	LogPrint(L"Server starting up...");

	unsigned char foo = 1;
	cNetMessageMaker::ConstructMessage( &foo, 1 );
//	cNM_LoginRequestMaker blah( 5 );

	// Load the default world.
	EbPrintf( L"Loading world data..." );
	cFile file;
	file.Open( L"..\\bin\\media\\level1.world" );
	g_pWorld = new cGameWorld( file );
	file.Close();


	// By now all the world data is loaded.	just sit around and wait
	// for some connections.
	EbPrintf( L"Starting up comm layer..." );
	g_comm.Startup( SERVER_LISTENPORT, CLIENT_LISTENPORT );
	g_comm.StartServer();

	// Server side I open a sending socket first so that I can respond
	// immediately if there is any data when I open the listen socket.
	// Internally to MTUDP it makes no difference.
	g_comm.StartSending();
	g_comm.StartListening();

	g_serverHost = 0;
	//m_pPlayer->SetHost( m_serverHost );	// loopback and never actually go through the net. (:

	EbPrintf( L"!! Server is online and can accept connections" );
}

void cGameServer::Tick()
{
	float timeDelta = 1/40.f; // FIXME: should calc this.
	// Any messages from clients?	process them
	char			data[ MAX_UDPBUFFERSIZE ];
	HOSTHANDLE		srcHostID;
	cDataExtract	extract;
	unsigned short	amnt;
	vector< cGameEnt* > objList;

	assert( g_pWorld );

	/**
	 * Step 1:
	 * go through all of the objects, and set their
	 * last state equal to their current state
	 */
	g_pWorld->EntIterStart();
	while( !g_pWorld->EntIterDone() )
	{
		ResetState( g_pWorld->EntIterCurr() );
		g_pWorld->EntIterNext();
	}

	/**
	 * Step 2:
	 * Get reliable messages.
	 * Reliable messages include requests to log in, notice of intent to disconnect,
	 * Chat messages, votes, name/model changes, spawn request, etc...
	 * We're not supporting all those options, but feel free to add them.
	 */
	while( ( amnt = g_comm.GetReliableData( data, MAX_UDPBUFFERSIZE, &srcHostID ) ) != 0 )
	{
		extract.SetBuffer( data, amnt * 8 );

		cNetMessage* pMsg = cNetMessageMaker::ConstructMessage( 
			(unsigned char*)extract.GetBuffer(), 
			extract.GetBufferLengthInBytes() );

		pMsg->SetFrom( srcHostID );

		pMsg->Exec();

		delete pMsg;
	}

	/**
	 * Step 3:
	 * Get Unreliable messages
	 */
	while( ( amnt = g_comm.GetUnreliableData( data, MAX_UDPBUFFERSIZE, &srcHostID ) ) != 0 )
	{
		extract.SetBuffer( data, amnt * 8 );

		cNetMessage* pMsg = cNetMessageMaker::ConstructMessage( 
			(unsigned char*)extract.GetBuffer(), 
			extract.GetBufferLengthInBytes() );

		pMsg->SetFrom( srcHostID );

		pMsg->Exec();

		delete pMsg;
	}

	/**
	 * Step 4:
	 * Give all our objects a timeslice
	 */
	g_pWorld->EntIterStart();
	while( !g_pWorld->EntIterDone() )
	{
		g_pWorld->EntIterCurr()->Tick( timeDelta );
		g_pWorld->EntIterNext();
	}

	g_pWorld->EntIterStart();
	while( !g_pWorld->EntIterDone() )
	{
		g_pWorld->EntIterCurr()->CheckState();
		g_pWorld->EntIterNext();
	}

	/**
	 * Step 5:
	 * Run object-object collision tests
	 */
	g_pWorld->RunCollisionTests();

	/**
	 * Step 6:
	 * Broadcast any changes in objects
	 */
	g_pWorld->EntIterStart();
	while( !g_pWorld->EntIterDone() )
	{
		BroadcastStateChanges( g_pWorld->EntIterCurr() );
		g_pWorld->EntIterNext();
	}

	/**
	 * Step 7:
	 * Run a mortis check (kill any mortisable objects)
	 */
	g_pWorld->EntIterStart();
	while( !g_pWorld->EntIterDone() )
	{
		if(MortisCheck( g_pWorld->EntIterCurr() ))
			break;

		g_pWorld->EntIterNext();
	}

	/**
	 * Step 8:
	 * Anybody that hasn't talked to us in awhile, kill.
	 */
	// TODO: add timeouts so crashed clients get removed
	// correctly.
}

void cGameServer::Shutdown()
{

}

UINT cGameServer::ProcMsg( const sMsg& msg )
{
	cNetMessage* pMsg;
	objID target;
	switch( msg.m_type )
	{
	case msgPrintString:
		assert( msg.m_pData );
		EbPrintf( (TCHAR*)msg.m_pData );
		return 0;
	case msgSendNetMessageR:
		pMsg = (cNetMessage*)msg.m_pData;
		target = msg.m_i[1];
		ReliableSendToPlayer( *pMsg, target );
		return 0;

	case msgSendNetMessageUR:
		pMsg = (cNetMessage*)msg.m_pData;
		target = msg.m_i[1];
		UnreliableSendToPlayer( *pMsg, target );
		return 0;

	case msgBroadcastUR:
		pMsg = (cNetMessage*)msg.m_pData;
		UnreliableSendToAllPlayers( *pMsg );
		return 0;

	case msgBroadcastR:
		pMsg = (cNetMessage*)msg.m_pData;
		ReliableSendToAllPlayers( *pMsg );
		return 0;

	case msgBroadcastRExcept:
		pMsg = (cNetMessage*)msg.m_pData;
		ReliableSendToAllPlayersExcept( *pMsg, msg.m_i[1] );
		return 0;

	case msgAddPlayerName:
		{
		string ansiString((char*)msg.m_pData );
		wstring wString(ansiString.begin(), ansiString.end());
		AddPlayer((TCHAR*)wString.c_str());
		return 0;
		}

	case msgRemovePlayerName:
		{
		string ansiString((char*)msg.m_pData );
		wstring wString(ansiString.begin(), ansiString.end());
		RemovePlayer((TCHAR*)wString.c_str());
		return 0;
		}

	case msgGetServerTime:
		return timeGetTime();

	case msgKillSocket:
		g_comm.HostDestroy( msg.m_i[0] );
		return 0;

	default:
		DP0(L"Bad Message got to cGameServer\n");
		return -1;
	}
}

void cGameServer::ReliableSendToPlayer( cNetMessage& msg, objID player )
{
	cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)MsgDaemon()->Get( player );

	if( !pPlayer )
	{
		LogPrint(L"cGameServer::ReliableSendToPlayer: bad player ID");
		return;
	}

	char buff[ MAX_UDPBUFFERSIZE ];
	int len = msg.SerializeTo( (unsigned char*)buff );

	g_comm.ReliableSendTo( &buff[0], len, pPlayer->GetHost() );
}

void cGameServer::UnreliableSendToPlayer( cNetMessage& msg, objID player )
{
	cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)MsgDaemon()->Get( player );

	if( !pPlayer )
	{
		LogPrint(L"cGameServer::UnreliableSendToPlayer: bad player ID");
		return;
	}

	char buff[ MAX_UDPBUFFERSIZE ];
	int len = msg.SerializeTo( (unsigned char*)buff );

	g_comm.UnreliableSendTo( &buff[0], len, pPlayer->GetHost() );
}


void cGameServer::ReliableSendToAllPlayers( cNetMessage& msg )
{
	list<cGamePlayerEnt *>				playerList;
	list<cGamePlayerEnt *>::iterator	iPlayer;

	g_pWorld->ListPlayers( &playerList );

	char buff[ MAX_UDPBUFFERSIZE ];
	int len = msg.SerializeTo( (unsigned char*)buff );

	for( iPlayer = playerList.begin(); iPlayer != playerList.end(); ++iPlayer )
	{
		g_comm.ReliableSendTo( &buff[0], len, (*iPlayer)->GetHost() );
	}
}


void cGameServer::ReliableSendToAllPlayersExcept( cNetMessage& msg, objID exception )
{
	list<cGamePlayerEnt *>						playerList;
	list<cGamePlayerEnt *>::iterator	iPlayer;

	g_pWorld->ListPlayers( &playerList );

	char buff[ MAX_UDPBUFFERSIZE ];
	int len = msg.SerializeTo( (unsigned char*)buff );

	for( iPlayer = playerList.begin(); iPlayer != playerList.end(); ++iPlayer )
	{
		if( (*iPlayer)->GetID() == exception )
			continue;

		g_comm.ReliableSendTo( &buff[0], len, (*iPlayer)->GetHost() );
	}
}


void cGameServer::UnreliableSendToAllPlayers( cNetMessage& msg )
{
	list<cGamePlayerEnt *>						playerList;
	list<cGamePlayerEnt *>::iterator	iPlayer;

	g_pWorld->ListPlayers( &playerList );

	char buff[ MAX_UDPBUFFERSIZE ];
	int len = msg.SerializeTo( (unsigned char*)buff );

	for( iPlayer = playerList.begin(); iPlayer != playerList.end(); ++iPlayer )
	{
		if( (*iPlayer)->GetStatus() == gesMortis )
			continue;  // skip mortisized players
		g_comm.UnreliableSendTo( &buff[0], len, (*iPlayer)->GetHost() );
	}
}

