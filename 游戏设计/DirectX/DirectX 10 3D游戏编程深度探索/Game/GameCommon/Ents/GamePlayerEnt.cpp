/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "GamePlayerEnt.h"

#include "..\netmsgs\MiscNM.h"

objID GetNextPlayerEntID()
{
	static unsigned short nextOffset = 0;
	return MakeID( c_playerSegment, nextOffset++ );
}

cGamePlayerEnt::cGamePlayerEnt() 
: cGameEnt()
{
	m_score = 0;
	DebPrint(L"Constructing a game player object... should have registered...");
	// Nothing to do.
}

cGamePlayerEnt::~cGamePlayerEnt()
{
	/**
	 * remove ourself from the world
	 */
	SendMessage( sMsg( msgRemovePlayer, g_gameWorldID, (int)GetID() ));
}


void cGamePlayerEnt::Tick( float tickLength )
{
	SetLoc( GetLoc() + GetVel()*tickLength );
}


bool cGamePlayerEnt::RespondToCollision( cGameEnt* pOther )
{
	return true;
}


UINT cGamePlayerEnt::ProcMsg( const sMsg& msg )
{
	static point3 retVal;
	switch( msg.m_type )
	{
	case msgGetSpawnLoc:
		retVal = 
			GetLoc() + 
			point3::Spherical( GetYaw(), GetPitch(), 1.f );
		return (UINT)&retVal;
	case msgGetSpawnDir:
		retVal = point3::Spherical( GetYaw(), GetPitch(), 1.f );
		return (UINT)&retVal;
	default:
		return cGameEnt::ProcMsg( msg );
	}
}


void cGamePlayerEnt::SetScore( int score )
{ 
	if( IsClient() )
	{
		// On the client, just change the score.
		m_score = score; 
	}
	else
	{
		// On the server, broadcast the new score.
		m_score = score; 

		cNM_ScoreChange msg( GetID(), score );
		SendMessage( sMsg( msgBroadcastUR, g_gameServer, &msg ) );
	}
}


cGamePlayerEnt* cGamePlayerEnt::CreateOnServer( 
	HOSTHANDLE host, 
	wstring name )
{
	assert( !IsClient() );

	LogPrint(L"Server is creating a player entity" );
	cGamePlayerEnt* pEnt = new cGamePlayerEnt();

	/**
	 * Do some housekeeping
	 */
	pEnt->SetID( GetNextPlayerEntID() );
	pEnt->SetHost( host );
	pEnt->SetName( name ); 
	pEnt->SetHealth( 100 );
	pEnt->m_bSphere.m_radius = 0.5f;
	pEnt->m_bSphere.m_loc = pEnt->GetLoc();


	/**
	 * Register the object with the message daemon
	 */
	MsgDaemon()->RegObject( 
		pEnt->GetID(), 
		(iGameObject*)pEnt );

	/**
	 * Find the parent cell
	 */
	pEnt->m_parent = SendMessage( 
		sMsg( msgFindContainingCell, g_gameWorldID, pEnt->GetLoc() )
		);

	/**
	 * Notify out parent cell that we're setting up house
	 */
	SendMessage( 
		sMsg( msgAddObjRef, pEnt->m_parent, (int)pEnt->GetID() )
		);

	/**
	 * Tell the world that there is a new player in town
	 */
	SendMessage( 
		sMsg( msgAddPlayer, g_gameWorldID, (int)pEnt->GetID() )
		);

	/**
	 * FIXMENOW: should send notifications to players
	 */

	return pEnt;
}

cGamePlayerEnt* cGamePlayerEnt::CreateOnClient( objID id, wstring name )
{
	assert( IsClient() );

	LogPrint(L"Client is creating a player entity" );
	cGamePlayerEnt* pEnt = new cGamePlayerEnt();

	/**
	 * Do some housekeeping
	 */
	pEnt->SetID( id );
	pEnt->SetName( name ); 
	pEnt->SetHealth( 100 );
	pEnt->m_bSphere.m_radius = 0.4f;
	pEnt->m_bSphere.m_loc = pEnt->GetLoc();


	/**
	 * Register the object with the message daemon
	 */
	MsgDaemon()->RegObject( 
		pEnt->GetID(), 
		(iGameObject*)pEnt );

	/**
	 * TODO: Right now, the client has no relationship
	 * between the ents and the cells they're in.  If
	 * you wanted to implement something like portal 
	 * rendering clientside, the cells would need to 
	 * know which objects are in them (so they can be
	 * drawn)... Code to register an object with a cell
	 * would go here, copied from CreateOnServer.
	 */

	/**
	 * Tell the world that there is a new player in town
	 */
	SendMessage( 
		sMsg( msgAddPlayer, g_gameWorldID, (int)pEnt->GetID() )
		);


	return pEnt;
}


