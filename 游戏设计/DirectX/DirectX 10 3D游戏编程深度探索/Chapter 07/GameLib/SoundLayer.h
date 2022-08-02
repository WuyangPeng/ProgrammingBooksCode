/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _SOUNDLAYER_H
#define _SOUNDLAYER_H

#include <dsound.h>
#include "GameErrors.h"	// Added by ClassView

class cSound;

class cSoundLayer  
{

	LPDIRECTSOUND8			m_pDSound;
	LPDIRECTSOUNDBUFFER8	m_pPrimary; // primary mixer

	static cSoundLayer* m_pGlobalSLayer;

	cSoundLayer( HWND hWnd );

public:
	virtual ~cSoundLayer();

	static cSoundLayer* GetSound()
	{ 
		return m_pGlobalSLayer; 
	}

	LPDIRECTSOUND8 GetDSound()
	{
		return m_pDSound;
	}

	static void Create( HWND hWnd )
	{
		new cSoundLayer( hWnd );
	}
};

inline cSoundLayer* Sound()
{
	return cSoundLayer::GetSound();
}

#endif //_SOUNDLAYER_H
