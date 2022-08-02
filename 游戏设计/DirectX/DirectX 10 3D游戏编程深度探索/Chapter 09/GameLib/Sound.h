/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _SOUND_H
#define _SOUND_H

#include <map>

#include "SoundLayer.h"
#include "Wavread.h"

class cSound  
{
	CWaveSoundRead*     m_pWaveSoundRead;
	LPDIRECTSOUNDBUFFER8	m_pBuffer;
	int					m_bufferSize;

	/**
	 * Multiple sounds that use the same
	 * file shouldn't re-read it, they should
	 * share the CWSR object.  This map
	 * implements rudimentary reference counting.
	 * I would have just changed CWaveSoundRead,
	 * but I wanted to keep it unchanged from the
	 * samples.
	 */
	static std::map< CWaveSoundRead*, int > m_waveMap;

	void Init();

public:
	cSound( TCHAR* filename );
	cSound( cSound& in );
	cSound& operator=( const cSound &in );

	virtual ~cSound();

	void Restore();
	void Fill();
	void Play( bool bLoop = false );

	bool IsPlaying();

};

#endif //_SOUND_H
