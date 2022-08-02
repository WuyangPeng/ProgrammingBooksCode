#include "SoundSystem.h"
#include "dxutil.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// Name: SoundSystem::~SoundSystem()
// Desc: Sound System Class destructor
//-----------------------------------------------------------------------------
SoundSystem::~SoundSystem()
{
	SAFE_RELEASE(pLoader);
	SAFE_RELEASE(pPerformance);
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::SoundSystem()
// Desc: Sound System Class constructor
//-----------------------------------------------------------------------------
SoundSystem::SoundSystem()
{
	pLoader = NULL;
	pPerformance = NULL;
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::hrInitSoundSystem()
// Desc: Initializes Direct Audio
//-----------------------------------------------------------------------------
HRESULT SoundSystem::hrInitSoundSystem(void)
{
	HRESULT					hResult;
	IDirectMusicAudioPath8	*path;

	// Initialize COM
	CoInitialize(NULL);
	
	// Create the loader
	if( FAILED( hResult = CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
		CLSCTX_INPROC, IID_IDirectMusicLoader8,
		(void**)&pLoader) )) {
		return(SOUNDERROR_MUSICLOADER);
	}
	
	// Create the performance
	if( FAILED( hResult = CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
		CLSCTX_INPROC, IID_IDirectMusicPerformance8,
		(void**)&pPerformance ))) {
		return(SOUNDERROR_MUSICPERFORMANCE);
	}
	
	// Initialize the audio
	if( FAILED( hResult = pPerformance->InitAudio( 
		NULL,
		NULL,
		hWnd,
		DMUS_APATH_DYNAMIC_STEREO,
		4,
		DMUS_AUDIOF_ALL,
		NULL
		))) {
		return(SOUNDERROR_INITAUDIO);
	}
	
	// Get the default path
	if( FAILED( pPerformance->GetDefaultAudioPath( &path ) ) ) 
		return(SOUNDERROR_PATH);
	
	// Set the default volume
	if( FAILED( path->SetVolume(0,0) ) ) 
		return(SOUNDERROR_VOLUME);

	return(S_OK);
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::hrLoadSound()
// Desc: Loads a sound and stores it in the GameSound passed
//-----------------------------------------------------------------------------
HRESULT SoundSystem::hrLoadSound(char *szname,GameSound *gs)
{
	WCHAR	wstrFileName[256];
	
	// Convert the filename to wide character format
	DXUtil_ConvertGenericStringToWide( wstrFileName, szname );
	
	// Make sure audio is initialized
	if( !pLoader ) 
		return(SOUNDERROR_MUSICLOADER);
	if( !pPerformance ) 
		return(SOUNDERROR_MUSICPERFORMANCE);
	// Clean up sound if it already exists
	if( gs->pSound ) {
		gs->pSound->Unload( pPerformance );
		gs->pSound->Release();
		gs->pSound = NULL;
	}
	
	// Load the sound from a file
	if ( FAILED(pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,
		IID_IDirectMusicSegment8,
		wstrFileName,
		(LPVOID*) &gs->pSound
		)))
	{
		return(SOUNDERROR_LOAD);
	}
	
	gs->pPerformance = pPerformance;

	// Download the data
	if ( FAILED ( gs->pSound->Download( pPerformance ) ) ) {
		return(SOUNDERROR_DOWNLOAD);
	}
	
	return(S_OK);
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::hrPlaySound()
// Desc: Plays a GameSound segment object
//-----------------------------------------------------------------------------
HRESULT SoundSystem::hrPlaySound(GameSound *gs)
{
	// Make sure there is a performance object present
	if( !pPerformance ) 
		return( SOUNDERROR_MUSICPERFORMANCE );
	
	if( !gs->pSound )
		return( SOUNDERROR_NOSEGMENT );
	
	// Play the sound segment
	if( FAILED ( pPerformance->PlaySegmentEx(
		gs->pSound,
		NULL,
		NULL,
		DMUS_SEGF_DEFAULT | DMUS_SEGF_SECONDARY,
		0,
		NULL,
		NULL,
		NULL
		))) 
		return( SOUNDERROR_PLAYFAIL );
	
	return(S_OK); 
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::hrInitSoundSystem()
// Desc: Initializes Direct Audio
//-----------------------------------------------------------------------------
GameSound::GameSound()
{
	pSound = NULL;
	pPerformance = NULL;
}

//-----------------------------------------------------------------------------
// Name: SoundSystem::hrInitSoundSystem()
// Desc: Initializes Direct Audio
//-----------------------------------------------------------------------------
GameSound::~GameSound()
{
	if( pSound ) {
		if( pPerformance ) 
			pSound->Unload( pPerformance );
	}
	SAFE_RELEASE(pSound);
}
