/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "GameSpawnEnt.h"
#include "..\MsgDaemon.h"

objID GetNextSpawnEntID()
{
	static unsigned short nextOffset = 0;
	return MakeID( c_spawnSegment, nextOffset++ );
}


cGameSpawnEnt::cGameSpawnEnt() 
: cGameEnt()
{

}


UINT cGameSpawnEnt::ProcMsg( const sMsg& msg )
{
	switch( msg.m_type )
	{
	case msgSpawnObject:
		{
			iGameObject* pObj = MsgDaemon()->Get( msg.m_i[0] );

			if( !pObj )
			{
				LogPrint(L"SpawnObj::ProcMsg: bad target ID");
				return 0;
			}

			pObj->ProcMsg( sMsg( msgSetLoc, 0, GetLoc() ) );
			pObj->ProcMsg( sMsg( msgSetYaw, 0, GetYaw()) );
			pObj->ProcMsg( sMsg( msgSetPitch, 0, GetPitch() ) );
			pObj->ProcMsg( sMsg( msgRebuildMatrix ) );

			/**
			 * Here we could spawn other things,
			 * such as a spawn sound, some sparks, etc
			 */
		}
		break;
	default:
		return cGameEnt::ProcMsg( msg );
	}
	return 0;
}


cGameSpawnEnt* cGameSpawnEnt::CreateSpawnEnt(
	objID id,
	sEntState state )
{
	cGameSpawnEnt* pOut = new cGameSpawnEnt();

	pOut->SetID( id );
	pOut->SetState( state );

	pOut->m_bSphere = bSphere3( 0.1f, state.m_loc );

	/**
	 * Register the object
	 */
	MsgDaemon()->RegObject( pOut->GetID(), (iGameObject*)pOut );

	/**
	 * Find the parent cell
	 */
	sMsg msg( msgFindContainingCell, g_gameWorldID, 0 );
	msg.m_pt = pOut->GetLoc();
	pOut->m_parent = MsgDaemon()->DeliverMessage( msg );

	/**
	 * Notify the cell of our entrance
	 */
	msg.m_type = msgAddObjRef;
	msg.m_dest = pOut->m_parent;
	msg.m_i[0] = pOut->GetID();
	MsgDaemon()->DeliverMessage( msg );

	return pOut;
}


