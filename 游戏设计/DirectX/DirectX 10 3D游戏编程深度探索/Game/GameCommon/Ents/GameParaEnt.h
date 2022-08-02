/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _GAMEPARAENT_H
#define _GAMEPARAENT_H

#include "GameEnt.h"

enum eParaEntType
{
	petRocket, // rockets, sent by the server
	petSpark   // sparks, totally client-side.
};

objID GetNextTempParaID();
objID GetNextParaEntID();

class cGameParaEnt : public cGameEnt
{
	eParaEntType	m_type;

	point3	m_x0, m_v0, m_a;
	float	m_t;

	cGameParaEnt();

	int m_nBounces; // for sparks.

public:

	virtual void Tick( float tickLength );

	virtual bool RespondToCollision( cGameEnt* pOther );

	/**
	 * We extend the base set of message handling abilities
	 */
	virtual UINT ProcMsg( const sMsg& msg );

	virtual bool HitsObjects()
	{
		switch( m_type )
		{
		case petRocket:
			return true;
		case petSpark:
			return false;
		}
		return true;
	}

	/**
	 * Create a spawn entity
	 */
	static cGameParaEnt* CreateParaEnt(
		eParaEntType type,
		objID id,
		const point3& x0,
		float tInitial,
		const point3& v0,
		const point3& a );
};

#endif // _GAMEPARAENT_H
