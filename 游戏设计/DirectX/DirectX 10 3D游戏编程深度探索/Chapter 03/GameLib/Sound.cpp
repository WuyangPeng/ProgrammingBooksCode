/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include "WavRead.h"
#include "Sound.h"

using std::map;

map< CWaveSoundRead*, int > cSound::m_waveMap;

cSound::cSound( TCHAR* filename )
{
	m_pWaveSoundRead = NULL;
	m_pBuffer = NULL;

    // Create a new wave file class
    m_pWaveSoundRead = new CWaveSoundRead();
	m_waveMap[ m_pWaveSoundRead ] = 1;

    // Load the wave file
    if( FAILED( m_pWaveSoundRead->Open( filename ) ) )
    {
        throw cGameError(L"couldn't open file!");
    }

	Init();
	Fill();
}

cSound::cSound( cSound& in )
{
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;
	Init();
	Fill();
}

cSound& cSound::operator=( const cSound &in )
{
	/**
	 * Destroy the old object
	 */
	int count = --m_waveMap[ m_pWaveSoundRead ];
	if( !count )
	{
		delete m_pWaveSoundRead;
	}
	SafeRelease( m_pBuffer );

	/**
	 * Clone the incoming one
	 */
	m_pWaveSoundRead = in.m_pWaveSoundRead;
	m_waveMap[ m_pWaveSoundRead ]++;

	Init();
	Fill();
	
	return *this;
}


cSound::~cSound()
{
	int count = m_waveMap[ m_pWaveSoundRead ];
	if( count == 1 )
	{
		delete m_pWaveSoundRead;
	}
	else
	{
		m_waveMap[ m_pWaveSoundRead ] = count - 1;
	}
		
	SafeRelease( m_pBuffer );
}

void cSound::Init()
{
    /**
	 * Set up the DirectSound surface. the size of the sound file 
	 * and the format of the data can be retrieved from the wave 
	 * sound object.  Besides that, we only set the STATIC flag,
	 * so that the driver isn't restricted in setting up the 
	 * buffer.
	 */
	sAutoZero<DSBUFFERDESC> dsbd;
    dsbd.dwFlags       = DSBCAPS_STATIC;
    dsbd.dwBufferBytes = m_pWaveSoundRead->m_ckIn.cksize;
    dsbd.lpwfxFormat   = m_pWaveSoundRead->m_pwfx;

    HRESULT hr; 

	// Temporary pointer to old DirectSound interface
	LPDIRECTSOUNDBUFFER pTempBuffer = 0;

	// Create the sound buffer
	hr = Sound()->GetDSound()->CreateSoundBuffer( &dsbd, &pTempBuffer, NULL );
    if( FAILED( hr ) )
    {
        throw cGameError(L"CreateSoundBuffer failed!");
    }

	// Upgrade the sound buffer to version 8
	pTempBuffer->QueryInterface( IID_IDirectSoundBuffer8, (void**)&m_pBuffer );
	if( FAILED( hr ) )
    {
        throw cGameError(L"SoundBuffer query to 8 failed!");
    }
	
	// Release the temporary old buffer
	pTempBuffer->Release();

    /**
	 * Remember how big the buffer is
	 */
    m_bufferSize = dsbd.dwBufferBytes;
}


void cSound::Restore()
{
    HRESULT hr;

    if( NULL == m_pBuffer )
	{
		return;
	}

    DWORD dwStatus;
    if( FAILED( hr = m_pBuffer->GetStatus( &dwStatus ) ) )
	{
		throw cGameError( L"couldn't get buffer status" );
	}

    if( dwStatus & DSBSTATUS_BUFFERLOST )
    {
		/**
		 * Chances are, we got here because the app /just/
		 * started, and DirectSound hasn't given us any 
		 * control yet.  Just spin until we can restore
		 * the buffer
		 */
        do 
        {
            hr = m_pBuffer->Restore();
            if( hr == DSERR_BUFFERLOST )
                Sleep( 10 );
        }
        while( hr = m_pBuffer->Restore() );

		/**
		 * The buffer was restored.  Fill 'er up.
		 */
        Fill();
    }
}


void cSound::Fill()
{
    HRESULT hr; 
    BYTE*   pbWavData; // Pointer to actual wav data 
    UINT    cbWavSize; // Size of data
    void*   pbData  = NULL;
    void*   pbData2 = NULL;
    ULONG   dwLength;
    ULONG   dwLength2;

	/**
	 * How big the wav file is
	 */
    UINT nWaveFileSize = m_pWaveSoundRead->m_ckIn.cksize;

    /**
	 * Allocate enough data to hold the wav file data
	 */
    pbWavData = new BYTE[ nWaveFileSize ];
    if( NULL == pbWavData )
	{
	    delete [] pbWavData;
        throw cGameError(L"Out of memory!");
	}

	hr = m_pWaveSoundRead->Read( 
		nWaveFileSize, 
        pbWavData, 
        &cbWavSize );
    if( FAILED( hr ) )           
	{
	    delete [] pbWavData;
        throw cGameError(L"m_pWaveSoundRead->Read failed");
	}

    /**
	 * Reset the file to the beginning 
	 */
    m_pWaveSoundRead->Reset();

    /**
	 * Lock the buffer so we can copy the data over
	 */
	hr = m_pBuffer->Lock( 
		0, m_bufferSize, &pbData, &dwLength, 
        &pbData2, &dwLength2, 0L );
    if( FAILED( hr ) )
	{
	    delete [] pbWavData;
        throw cGameError(L"m_pBuffer->Lock failed");
	}

    /**
	 * Copy said data over, unlocking afterwards
	 */
    memcpy( pbData, pbWavData, m_bufferSize );
    m_pBuffer->Unlock( pbData, m_bufferSize, NULL, 0 );

    /**
	 * We're done with the wav data memory.
	 */
    delete [] pbWavData;
}


bool cSound::IsPlaying()
{
    DWORD dwStatus = 0;

    m_pBuffer->GetStatus( &dwStatus );

    if( dwStatus & DSBSTATUS_PLAYING )
        return true;
    else 
        return false;
}


void cSound::Play( bool bLoop )
{
	HRESULT hr;
    if( NULL == m_pBuffer )
        return;

    // Restore the buffers if they are lost
    Restore();

    // Play buffer 
    DWORD dwLooped = bLoop ? DSBPLAY_LOOPING : 0L;
    if( FAILED( hr = m_pBuffer->Play( 0, 0, dwLooped ) ) )
	{
		throw cGameError(L"m_pBuffer->Play failed");
	}
}
