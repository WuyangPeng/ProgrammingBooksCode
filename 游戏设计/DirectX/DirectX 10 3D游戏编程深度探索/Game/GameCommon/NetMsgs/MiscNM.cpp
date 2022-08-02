/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include "MiscNM.h"


//==========--------------------------  


cNM_ScoreChange::cNM_ScoreChange( 
	int entID, 
	int newScore )
: m_entID( entID )
, m_newScore( newScore )
{
	LogPrint(L"cNM_ScoreChange construction: %d score should go to %d",
		m_entID,
		m_newScore );
}

int cNM_ScoreChange::SerializeTo( unsigned char* pOutput )
{
	int dataSize = 4 + 4; // id, score
	*pOutput++ = 13;
	memcpy( pOutput, &m_entID, dataSize );
	return 1 + dataSize;
}

void cNM_ScoreChange::SerializeFrom( unsigned char *pFromData, int datasize )
{
	int dataSize = 4 + 4; // id, score
	memcpy( &m_entID, pFromData + 1, dataSize );
}

void cNM_ScoreChange::Exec()
{
	DebPrint(L"Changing %d's score", m_entID );
	cGamePlayerEnt* pPlayer = (cGamePlayerEnt*)MsgDaemon()->Get( m_entID );

	if( !pPlayer )
	{
		LogPrint(L"ERROR: score change on bad player %d", m_entID);
		return;
	}

	DebPrint(L"Changing %d score to %d", m_entID, m_newScore );
	
	pPlayer->SetScore( m_newScore );
}
