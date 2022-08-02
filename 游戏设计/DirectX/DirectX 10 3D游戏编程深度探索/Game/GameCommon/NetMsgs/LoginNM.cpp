/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "NetMessages.h"
#include "LoginNM.h"
#include "EntNM.h"

#pragma warning(disable : 4996)
// Just to save some bandwidth... When the login gets accepted
// This string holds the name we requested.
string g_desiredName;

cNM_LoginRequest::cNM_LoginRequest( 
	string clientName )
{
	strcpy_s( m_name, 32, clientName.c_str() );
	g_desiredName = clientName;
	DebPrint(L"Ready to try to login!\n" );
}

int cNM_LoginRequest::SerializeTo( unsigned char* pOutput )
{
	// First byte is the message ID (1)
	*pOutput++ = 1;

	// Next is the client name
	strcpy( (char*)pOutput, m_name );

	return 1 + 32;
}

void cNM_LoginRequest::SerializeFrom( 
	unsigned char *pFromData, 
	int datasize )
{
	strcpy_s( m_name, 32, (const char*)(pFromData + 1) );
}

void cNM_LoginRequest::Exec()
{
	/**
	 * Create the server-side player
	 */

	string ansiName(m_name);
	wstring wName(ansiName.begin(), ansiName.end());

	cGamePlayerEnt* pEnt = 
		cGamePlayerEnt::CreateOnServer( m_from, wName );
	int playerID = pEnt->GetID();

	/**
	 * Send a message back to the player.
	 */

	string ansiString(m_name);
	wstring wString(ansiString.begin(), ansiString.end());

	DebPrint(L"Sending Login Acceptance to player [%s]", wString.c_str() );
	ReliableSendToPlayer( 
		cNM_LoginAccepted(playerID), playerID
		);

	/**
	 * Now tell our new player about all the objects.
	 */
	GetWorld()->EntIterStart();
	while( !GetWorld()->EntIterDone() )
	{
		cGameEnt* pCurr = GetWorld()->EntIterCurr();
		GetWorld()->EntIterNext();

		objID currID = pCurr->GetID();

		unsigned short seg = GetIDSegment( currID );

		// skip spawn objects
		if( c_spawnSegment == seg )
			continue;

		// skip player objects
		if( c_playerSegment == seg )
			continue;

		cNM_EntAdd msg( currID, pCurr->GetState() );
		ReliableSendToPlayer( msg, playerID );
	}

	/**
	 * Tell it about all of the other players.
	 */
	list< cGamePlayerEnt* > playerList;
	GetWorld()->ListPlayers( &playerList );
	list< cGamePlayerEnt* >::iterator iter;
	for(iter = playerList.begin(); iter != playerList.end(); iter++ )
	{
		cGamePlayerEnt* pCurr = (*iter);

		if( pCurr->GetID() == playerID )
			continue;

		//cNM_PlayerAdd msg( pCurr->GetID() );

		wstring wString(pCurr->GetName());
		string ansiString(wString.begin(), wString.end());

		cNM_NewPlayer msg( 
			pCurr->GetID(), 
			pCurr->GetScore(), 
			ansiString.c_str(), 
			pCurr->GetState() );

		ReliableSendToPlayer( msg, playerID );
	}

	/**
	 * Tell the other players about it.
	 */
	{
		//cNM_PlayerAdd msg( playerID );
		cNM_NewPlayer msg( 
			playerID, 
			0, 
			string(m_name),
			pEnt->GetState() );
		ReliableBroadcastExcept( msg, playerID );
	}

	/**
	 * Add it from the edit box
	 */
	SendMessage( sMsg( msgAddPlayerName, g_gameServer, (void*)m_name ));
}

//==========--------------------------  

cNM_LoginAccepted::cNM_LoginAccepted( int playerID )
: m_playerID( playerID )
{
}

int cNM_LoginAccepted::SerializeTo( unsigned char* pOutput )
{
	// First byte is the message ID (1)
	*pOutput++ = 2;

	*((int*)pOutput) = m_playerID;

	return 1 + sizeof(int);
}

void cNM_LoginAccepted::SerializeFrom( unsigned char *pFromData, int datasize )
{
	m_playerID = *(int*)(pFromData + 1);
}

void cNM_LoginAccepted::Exec()
{
	DebPrint(L"Login Accepted!\n" );

	/**
	 * Create the client-side player
	 */

	wstring wString(g_desiredName.begin(), g_desiredName.end());
	cGamePlayerEnt* pEnt = 
		cGamePlayerEnt::CreateOnClient( m_playerID, wString );

	/**
	 * Notify the game client
	 */
	SendMessage( sMsg( msgPlayerCreated, g_gameID, (int)pEnt->GetID() ));

	/**
	 * Request a spawn
	 */
	cNM_SpawnReq msg( m_playerID );

	SendMessage( sMsg( msgSendToServerUR, g_gameID, &msg ) );

	//cGamePlayerEnt* pEnt = cGamePlayerEnt::CreatePlayerEnt( m_playerID );

}

//==========--------------------------  

cNM_LogoutNotice::cNM_LogoutNotice( int playerID )
: m_playerID( playerID )
{
}

int cNM_LogoutNotice::SerializeTo( unsigned char* pOutput )
{
	*pOutput++ = 7;
	*((int*)pOutput) = m_playerID;
	return 4 + 1;
}

void cNM_LogoutNotice::SerializeFrom( unsigned char *pFromData, int datasize )
{
	m_playerID = *((int*)(pFromData+1));
}

void cNM_LogoutNotice::Exec()
{
	DebPrint(L"Got a logout request");
	LogPrint(L"Got a logout request");

	cGamePlayerEnt* pEnt = (cGamePlayerEnt*)MsgDaemon()->Get( m_playerID );

	if( !pEnt )
	{
		LogPrint(L"LogoutNotice: bad ID");
		return;
	}

	/**
	 * Close the socket to the player
	 */
	SendMessage(
		sMsg( msgKillSocket, g_gameServer, (int)pEnt->GetHost() )
		);

	/**
	 * Broadcast a notification
	 */

	/**
	 * Remove it from the edit box
	 */
	SendMessage( 
		sMsg( msgRemovePlayerName, g_gameServer, (void*)pEnt->GetName().c_str() )
		);

	/**
	 * Remove the player
	 */
	pEnt->SetStatus( gesMortis );
}

//==========--------------------------  

cNM_NewPlayer::cNM_NewPlayer( int id, int score, string clientName, sEntState state )
{
	m_entID = id;
	m_score = score;
	strcpy_s( m_name, 32, clientName.c_str() );
	m_state = state;
}

int cNM_NewPlayer::SerializeTo( unsigned char* pOutput )
{
	int dataSize = 4 + 4 + 32 + sizeof( sEntState ); // id, score, name.
	*pOutput++ = 8;
	memcpy( pOutput, &m_entID, dataSize );
	return 1 + dataSize;
}

void cNM_NewPlayer::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + 4 + 32 + sizeof( sEntState ); // id, score, name.
	memcpy( &m_entID, pFromData + 1, dataSize );
}

void cNM_NewPlayer::Exec()
{
	// Create the player.
	DebPrint(L"Player %s has joined the game!", m_name);
	LogPrint(L"Adding a player with name %s", m_name);

	string ansiString(m_name);
	wstring wString(ansiString.begin(), ansiString.end());

	cGamePlayerEnt* pPlayer = 
		cGamePlayerEnt::CreateOnClient( m_entID, wString );

	pPlayer->SetState( m_state );
	pPlayer->SetScore( m_score );
	LogPrint(L"Finished adding player\n");
}


