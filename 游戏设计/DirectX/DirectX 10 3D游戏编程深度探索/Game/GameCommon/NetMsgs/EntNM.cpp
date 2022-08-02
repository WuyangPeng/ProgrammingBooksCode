/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

//c:\Users\WooWoo\Desktop\Books\Adv 3D DX10\Source Code\Game\GameClient\StdAfx.h
//c:\Users\WooWoo\Desktop\Books\Adv 3D DX10\Source Code\Game\GameCommon\NetMsgs\EntNM.cpp
#include "stdafx.h"

#include "EntNM.h"

#include "..\MsgDaemon.h"

cNM_EntAdd::cNM_EntAdd( 
	int entID, 
	sEntState state )
: m_entID( entID )
, m_state( state )
{
}

int cNM_EntAdd::SerializeTo( unsigned char* pOutput )
{
	int dataSize = sizeof( sEntState ) + 4; // ent state, 1 int.
	*pOutput++ = 3;
	memcpy( pOutput, &m_entID, dataSize );
	return 1 + dataSize;
}	

void cNM_EntAdd::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = sizeof( sEntState ) + 4; // ent state, 1 ints.
	memcpy( &m_entID, pFromData + 1, dataSize );
}

void cNM_EntAdd::Exec()
{
	LogPrint(L"[cNM_EntAdd::Exec] id is (%d:%d)",
		GetIDSegment(m_entID), GetIDOffset(m_entID) );
	DebPrint(L"[cNM_EntAdd::Exec] id is (%d:%d)",
		GetIDSegment(m_entID), GetIDOffset(m_entID) );

	/**
	 * Use the segment constants to figure out what kind
	 * of object we got told to add.
	 */
	switch( GetIDSegment( m_entID ) )
	{
	case c_playerSegment:
		LogPrint(L"[ERROR] shouldn't get entadd's for players!" );
		break;
	case c_spawnSegment:
		LogPrint(L"  The hell do I do with spawn ents?" );
		break;
	case c_projSegment:
		{
			// Create a projection entity on the client
			cGameProjEnt* pEnt = cGameProjEnt::CreateOnClient(
				m_entID, m_state );
			LogPrint(L"  !! Added a projectile ent to the world");
			DebPrint(L"  !! Added a projectile ent to the world");
		}
		break;
	case c_paraSegment:
		LogPrint(L"  The hell do I do with para ents?" );
		break;
	default:
		// some other weird type
		LogPrint(L"[ERROR] Tried to create unknown object segment: %d", 
			GetIDSegment( m_entID ) );
	}
}

//==========--------------------------  

/**
 * FIXME: This message is redundant.  remove it.
 */


cNM_PlayerAdd::cNM_PlayerAdd( int playerID )
: m_playerID( playerID )
{
	cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)MsgDaemon()->Get( playerID );

	if( !pPlayer )
	{
		LogPrint(L"PlayerAdd: bad ID");
		return;
	}
	
	m_state = pPlayer->GetState();
	assert( pPlayer->GetName().length() <= 31 );
	wcscpy_s( m_name, 32, pPlayer->GetName().c_str() );
}

int cNM_PlayerAdd::SerializeTo( unsigned char* pOutput )
{
	int dataSize = 4 + sizeof( sEntState ) + 32; // int, entstate, and name
	*pOutput++ = 12;
	memcpy( pOutput, &m_playerID, dataSize );
	return 1 + dataSize;
}

void cNM_PlayerAdd::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + sizeof( sEntState ) + 32; // int, entstate, and name
	memcpy( &m_playerID, pFromData + 1, dataSize );
}

void cNM_PlayerAdd::Exec()
{
	DebPrint(L"Player %s has joined the game!", m_name);
	LogPrint(L"Adding a player with name %s", m_name);

	cGamePlayerEnt* pPlayer = 
		cGamePlayerEnt::CreateOnClient( m_playerID, wstring( m_name ) );

	pPlayer->SetState( m_state );
	LogPrint(L"Finished adding player\n");
}


//==========--------------------------  

cNM_EntStateChange::cNM_EntStateChange( 
	int entID, 
	sEntState state )
: m_entID( entID )
, m_state( state )
{

}

int cNM_EntStateChange::SerializeTo( unsigned char* pOutput )
{
	int dataSize = sizeof( sEntState ) + 4; // ent state, one int.
	*pOutput++ = 4;
	memcpy( pOutput, &m_entID, dataSize );
	return 1 + dataSize;
}

void cNM_EntStateChange::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = sizeof( sEntState ) + 4; // ent state, one int.
	memcpy( &m_entID, pFromData + 1, dataSize );
}

void cNM_EntStateChange::Exec()
{
	// apply the state to the entity.
	cGameEnt* pEnt = (cGameEnt*)MsgDaemon()->Get( m_entID );
	//DebPrint(L"StateChange for %d", m_entID );

	if( NULL == pEnt )
	{
		LogPrint(L"[cNM_EntStateChange]: ERROR! Object not found: (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}

	pEnt->SetState( m_state );
}


//==========--------------------------  

cNM_SpawnReq::cNM_SpawnReq( int entID )
: m_entID( entID )
{

}

int cNM_SpawnReq::SerializeTo( unsigned char* pOutput )
{
	// First byte is the message ID (5)
	*pOutput++ = 5;

	*((int*)pOutput) = m_entID;

	return 1 + sizeof(int);
}

void cNM_SpawnReq::SerializeFrom( unsigned char *pFromData, int datasize )
{
	m_entID = *(int*)(pFromData + 1);
}

void cNM_SpawnReq::Exec()
{
	LogPrint(L"Received a Spawn Request");
	cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)MsgDaemon()->Get( m_entID );

	if( NULL == pPlayer )
	{
		LogPrint(L"[cNM_SpawnReq]: ERROR! Player not found: (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}

	if( pPlayer->GetStatus() != gesDead &&
		pPlayer->GetStatus() != gesUnSpawned )
	{
		// Shouldn't spawn (player is alive)
		return;
	}

	// otherwise, spawn away...
	cGameWorld* pWorld = (cGameWorld*)MsgDaemon()->Get( g_gameWorldID );

	objID spawnID = pWorld->GetGoodSpawnEnt();

	cGameSpawnEnt* pSpawn = (cGameSpawnEnt*)MsgDaemon()->Get( spawnID );

	sEntState state = pPlayer->GetState();

	state.m_health = 100;
	state.m_loc = pSpawn->GetLoc();
	state.m_status = gesAlive;

	pPlayer->SetState( state );

	DebPrint(L"spawning player %d....", m_entID );

	cNM_EntStateChange msg( m_entID, state );
	ReliableBroadcast( msg );
}

//==========--------------------------  

cNM_EntStateChangeRequest::cNM_EntStateChangeRequest( 
	int entID, 
	sEntState state )
: m_entID( entID )
, m_state( state )
{

}

int cNM_EntStateChangeRequest::SerializeTo( unsigned char* pOutput )
{
	int dataSize = sizeof( sEntState ) + 4; // ID + ent state
	*pOutput++ = 6;
	memcpy( pOutput, &m_entID, dataSize );
	return 1 + dataSize;
}

void cNM_EntStateChangeRequest::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = sizeof( sEntState ) + 4; // ID + ent state
	memcpy( &m_entID, pFromData+1, dataSize );
}

void cNM_EntStateChangeRequest::Exec()
{
	// Apply the state to the server-side object.
	cGameEnt* pEnt = (cGameEnt*)MsgDaemon()->Get( m_entID );

	if( NULL == pEnt )
	{
		LogPrint(L"[cNM_EntStateChangeRequest]: ERROR! Object not found: (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}
	
	pEnt->SetState( m_state );

	// Right now, just re-broadcast it out.
	cNM_EntStateChange msg( m_entID, m_state );
	UnreliableBroadcast( msg );
}


//==========--------------------------  

cNM_MiniStateChange::cNM_MiniStateChange( 
	int entID,
	sEntState& state )
: m_entID( entID )
, m_loc( state.m_loc )
, m_vel( state.m_vel )
, m_yaw( state.m_yaw )
, m_pitch( state.m_pitch )
{
	sMsg msg;
	msg.m_dest = g_gameID;
	msg.m_type = msgGetServerTime;
	m_time = SendMessage( msg );
}

int cNM_MiniStateChange::SerializeTo( unsigned char* pOutput )
{
	*pOutput++ = 9;
	int dataSize = 4 + 4 + 12 + 12 + 4 + 4;
	memcpy( pOutput, (void*)&m_entID, dataSize );
	return dataSize + 1;
}

void cNM_MiniStateChange::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + 4 + 12 + 12 + 4 + 4;
	memcpy( (void*)&m_entID, pFromData+1, dataSize );
}

void cNM_MiniStateChange::Exec()
{
	// apply the state to the entity.
	cGameEnt* pEnt = (cGameEnt*)MsgDaemon()->Get( m_entID );

	if( NULL == pEnt )
	{
		LogPrint(L"[cNM_MiniStateChange]: ERROR! Object not found: (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}

	if( !pEnt )
	{
		LogPrint(L"[cNM_MiniStateChange::Exec] got a bad ID: %d", m_entID );
		return;
	}

	if( IsClient() )
	{
		// only apply yaw and pitch if it's not the player object.
		if( GetClientID() != m_entID )
		{
			pEnt->SetYaw( m_yaw );
			pEnt->SetPitch( m_pitch );
		}
	}
	pEnt->SetLoc( m_loc );
	pEnt->SetVel( m_vel );
}


//==========--------------------------  

cNM_MiniStateChangeRequest::cNM_MiniStateChangeRequest( 
	int entID,
	sEntState& state )
: m_entID( entID )
, m_loc( state.m_loc )
, m_vel( state.m_vel )
, m_yaw( state.m_yaw )
, m_pitch( state.m_pitch )
{
	sMsg msg;
	msg.m_dest = g_gameID;
	msg.m_type = msgGetServerTime;
	m_time = SendMessage( msg );
}

int cNM_MiniStateChangeRequest::SerializeTo( unsigned char* pOutput )
{
	*pOutput++ = 10;
	int dataSize = 4 + 4 + 12 + 12 + 4 + 4;
	memcpy( pOutput, (void*)&m_entID, dataSize );
	return dataSize + 1;
}

void cNM_MiniStateChangeRequest::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + 4 + 12 + 12 + 4 + 4;
	memcpy( (void*)&m_entID, pFromData+1, dataSize );
}

void cNM_MiniStateChangeRequest::Exec()
{
	/**
	 * Apply the state change
	 */

	// FIXME: should scale for time here.
	cGameEnt* pEnt = (cGameEnt*)MsgDaemon()->Get( m_entID );

	if( NULL == pEnt )
	{
		LogPrint(L"[cNM_MiniStateChangeRequest]: ERROR! Object not found: (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}

	pEnt->SetLoc( m_loc );
	pEnt->SetYaw( m_yaw );
	pEnt->SetPitch( m_pitch );
	pEnt->SetVel( m_vel );
}

//==========--------------------------  

cNM_ProjFireRequest::cNM_ProjFireRequest( objID id )
{
	cGameEnt* pEnt = (cGameEnt*)MsgDaemon()->Get( id );

	if( !pEnt )
	{
		LogPrint(L"FireRequest: bad ID");
		return;
	}

	m_yaw = pEnt->GetYaw();
	m_pitch = pEnt->GetPitch();
	m_entID = id;
}

int cNM_ProjFireRequest::SerializeTo( unsigned char* pOutput )
{
	*pOutput++ = 11;
	int dataSize = 4 + 4 + 4; // 1 int, 2 floats
	memcpy( pOutput, &m_entID, dataSize );

	return 1 + dataSize;
}

void cNM_ProjFireRequest::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + 4 + 4; // 1 int, 2 floats
	memcpy( &m_entID, pFromData+1, dataSize );
}

void cNM_ProjFireRequest::Exec()
{
	DebPrint(L"Server received a request to fire a projectile" );
	LogPrint(L"obj %d wants to fire.", m_entID );
	cGameEnt* pSrc = (cGameEnt*)MsgDaemon()->Get( m_entID );

	if( NULL == pSrc )
	{
		LogPrint(L"[cNM_ProjFireRequest]: ERROR! Object not found (%d:%d)",
			GetIDSegment( m_entID ), GetIDOffset( m_entID ) );
		return;
	}

	/**
	 * Create a projectile entity
	 */
	cGameProjEnt* pProj = cGameProjEnt::CreateOnServer(
		m_entID, m_yaw, m_pitch );

	point3 loc = pSrc->GetLoc();
	LogPrint(L"launcher is at %f %f %f",
		loc.x, loc.y, loc.z );

	/**
	 * Broadcast the new entity
	 */
	cNM_EntAdd msg( 
		pProj->GetID(), 
		pProj->GetState() );
	ReliableBroadcast( msg );
	
	LogPrint(L"Sucessfully added rocket to world" );
}


