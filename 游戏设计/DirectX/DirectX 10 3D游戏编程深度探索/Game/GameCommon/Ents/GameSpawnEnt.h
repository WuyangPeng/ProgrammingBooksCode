/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _GAMESPAWNENT_H
#define _GAMESPAWNENT_H

#include "GameEnt.h"
#include "..\ResourceMgr.h"

objID GetNextSpawnEntID();

class cGameSpawnEnt : public cGameEnt
{
	// constructor is private to force usage of CreateSpawnEnt
	cGameSpawnEnt();
public:

	//==========--------------------------   cGameEnt routines

	virtual void Tick( float tickLength ){}

	virtual bool RespondToCollision( cGameEnt* pOther ){ return true; }

	/**
	 * We extend the base set of message handling abilities
	 */
	virtual UINT ProcMsg( const sMsg& msg );

	virtual bool HitsObjects(){ return false; }

	/**
	 * Create a spawn entity
	 */
	static cGameSpawnEnt* CreateSpawnEnt(
		objID id,
		sEntState state );


};

#endif //_GAMESPAWNENT_H