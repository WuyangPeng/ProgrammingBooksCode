/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "GameProjEnt.h"
#include "GamePlayerEnt.h"
#include "..\MsgDaemon.h"
#include "..\netmsgs\miscnm.h"


objID GetNextProjEntID()
{
	static unsigned short nextOffset = 0;
	return MakeID( c_projSegment, nextOffset++ );
}


cGameProjEnt::cGameProjEnt() 
: cGameEnt()
{

}


UINT cGameProjEnt::ProcMsg( const sMsg& msg )
{
	switch( msg.m_type )
	{
	case msgNotifyPlaneCollision:
		DebPrint(L"Kaboom!  A rocket has exploded.");

		/**
		 * Change ourselves to a dead state.
		 */
		SetStatus( gesMortis );

		/**
		 * TODO: This would be the best place to add
		 * a rocket explosion.  The best bet would be
		 * to add a new object on the client side that
		 * contains sparks or something similar.
		 */

		break;

	case msgNotifyObjectCollision:
		DebPrint(L"Kaboom!  A rocket has hit an object!.");
		break;
		
	default:
		return cGameEnt::ProcMsg( msg );
	}
	return 0;
}


void cGameProjEnt::Tick( float tickLength )
{
	/**
	 * Early out if we're dead
	 */
	if( GetStatus() != gesAlive )
		return;

	/**
	 * The velocity is reset every frame (so that
	 * the player objects can move using velocity
	 * instead of specifying position every frame).
	 *
	 * To remedy the situation for objects like
	 * rockets, just re-create the velocity.
	 */
	point3 vel = point3::Spherical( GetYaw(), GetPitch(), 12.f );

	SetLoc( GetLoc() + vel * tickLength );
}

bool cGameProjEnt::RespondToCollision( cGameEnt* pOther )
{
	if( pOther )
	{

		switch( GetIDSegment( pOther->GetID() ) )
		{
		case c_playerSegment:
			{
				// Did we hit our parent object? (if so do nothing)
				if( m_launcher == pOther->GetID() )
				{
					return true;
				}

				// We hit a player. Apply damage and
				// destroy ourselves.
				cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)pOther;

				// Have rockets do 35 damage to the player
				int currHealth = pPlayer->GetHealth();

				if( currHealth < 35 )
				{
					// This will kill the player.  change the
					// score.  m_launcher gets an extra point.
					DebPrint(L"Changing %d's score", m_launcher );
					LogPrint(L"Changing %d's score", m_launcher );

					cGamePlayerEnt* pEnt = (cGamePlayerEnt*)MsgDaemon()->Get( m_launcher );

					if( !pEnt )
					{
						LogPrint(L"RespondToCollision: bad launcher ID");
						return true;
					}


					cNM_ScoreChange msg( m_launcher, pEnt->GetScore()+1 );
					ReliableBroadcast( msg );

				}

				// Apply the damage
				pPlayer->SetHealth( currHealth - 35 );

				// Time to die...
				SetStatus( gesMortis );

				//return false;
			}
		default:
			{
				// We hit something else.
				// Do nothing.
				return true;
			}
		}
	}

	return true;
}


cGameProjEnt* cGameProjEnt::CreateOnServer( objID parent, float yaw, float pitch )
{
	cGameProjEnt* pEnt = new cGameProjEnt();

	cGameEnt* pParent = (cGameEnt*)MsgDaemon()->Get( parent );

	if( !pParent )
	{
		LogPrint(L"ProjEnt::CreateOnServer: bad parent ID");
		return NULL;
	}

	int entID = GetNextProjEntID();
	pEnt->SetID( entID );
	LogPrint(L"spawning rocket with parent %d, id %d, yaw %f, pitch %f", 
		parent, entID, yaw, pitch );

	/**
	 * Housekeeping
	 */

	// calc the velocity.
	point3 vel = point3::Spherical( yaw, pitch, 3.f );

	pEnt->m_launcher = parent;

	pEnt->SetLoc( pParent->GetLoc() );
	pEnt->SetVel( vel );
	pEnt->SetYaw( yaw );
	pEnt->SetPitch( pitch );
	pEnt->SetStatus( gesAlive );

	pEnt->m_bSphere.m_loc = pEnt->GetLoc();
	pEnt->m_bSphere.m_radius = 0.3f;

	const point3& loc = pParent->GetLoc();
	LogPrint(L"Creating projectile on server at %f %f %f",
		loc.x, loc.y, loc.z );

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
	 * FIXMENOW: broadcast creation to clients.
	 */

	return pEnt;
}

cGameProjEnt* cGameProjEnt::CreateOnClient( objID id, sEntState& state )
{
	LogPrint(L"[cGameProjEnt::CreateOnClient]");
	cGameProjEnt* pEnt = new cGameProjEnt();

	pEnt->SetID( id );
	pEnt->SetState( state );

	LogPrint(L"spawning rocket at %f %f %f",
		state.m_loc.x, state.m_loc.y, state.m_loc.z );

	LogPrint(L"Creating projectile on client" );

	/**
	 * Register the object with the message daemon
	 */
	MsgDaemon()->RegObject( 
		pEnt->GetID(), 
		(iGameObject*)pEnt );

	return pEnt;
}


