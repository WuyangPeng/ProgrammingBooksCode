/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _MISCNM_H
#define _MISCNM_H

#include "NetMessages.h"


//=================================================================

/**
 * Message: Score Change
 * ID: 13
 * Desc: When someone dies, someone's score changes.  Just takes
 * a player ID and a new score.  Generally broadcast to all clients
 * whenever the score changes.
 */
class cNM_ScoreChange
: public cNetMessage
{
	int m_entID; // ID of the object that has been added.
	int m_newScore; // New score for that object.

public:

	cNM_ScoreChange( 
		int entID, 
		int newScore );
	cNM_ScoreChange(){}

	virtual int SerializeTo( unsigned char* pOutput );
	virtual void SerializeFrom( unsigned char *pFromData, int datasize );
	virtual void Exec();

protected:
};


#endif//_MISCNM_H