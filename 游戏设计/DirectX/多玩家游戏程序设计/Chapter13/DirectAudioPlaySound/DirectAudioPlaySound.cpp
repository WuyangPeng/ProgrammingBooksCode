//###################################################################################
//#																					#
//#			Chapter 13 - Direct X Audio Fundamentals								#		
//#																					#
//#						Plays a wave file											#
//#																					#
//#						Todd Barron, 01/18/2001										#
//#																					#
//###################################################################################

#include <stdio.h>
#include <Dmusici.h>
#include "dxutil.h"

#define SOUNDERROR_MUSICLOADER		0x85000001
#define SOUNDERROR_MUSICPERFORMANCE	0x85000002
#define SOUNDERROR_INITAUDIO		0x85000003
#define SOUNDERROR_PATH				0x85000004
#define SOUNDERROR_VOLUME			0x85000005
#define SOUNDERROR_LOAD				0x85000006
#define SOUNDERROR_DOWNLOAD			0x85000007
#define SOUNDERROR_NOSEGMENT		0x85000008
#define SOUNDERROR_PLAYFAIL			0x85000009

// Windows Globals
const char	*szWndClass		= "DirectAudio";
const char	*szProgramName	= "Direct-Audio Init Program";
HINSTANCE	g_hInstance;

// Direct Audio Globals
IDirectMusicLoader8			*pLoader = NULL;
IDirectMusicPerformance8	*pPerformance = NULL;
IDirectMusicSegment8		*pSound = NULL;

// Function Prototypes
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void vCleanup(void);
HRESULT hrInitDirectAudio(HWND hWnd);
HRESULT hrLoadSound(char *szFileName);
HRESULT hrPlaySound(IDirectMusicSegment8 *pSegment);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS	wc;
	HWND		hWnd;
	MSG			msg;
	HRESULT		hr;
	
	// Set up and register window class
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH )GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWndClass;
	RegisterClass(&wc);
	
	// Create a window
	hWnd = CreateWindowEx(WS_EX_TOPMOST,
		szWndClass,
		szProgramName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		320,
		200,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// Setup global window instance
	g_hInstance = hInstance;
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// Initialize The Audio System
	hr = hrInitDirectAudio(hWnd);
	if( hr != S_OK ) {
		MessageBox( hWnd, "DirectAudio Error", "Unable to initialize Direct Audio.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}

	// Initialize The Audio System
	hr = hrLoadSound("testsound.wav");
	if( hr != S_OK ) {
		MessageBox( hWnd, "DirectAudio Error", "Unable to load media sample.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}

	// Play the sound
	hrPlaySound(pSound);
	// Wait 1/2 second
	Sleep(500);
	// Play sound again
	hrPlaySound(pSound);
	// Wait 1/2 second
	Sleep(500);
	// Play sound again
	hrPlaySound(pSound);

	// Process messages until the program is terminated
	while( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	// Cleanup the environment
	vCleanup();
	
	return(msg.wParam);
};

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The application's message loop
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	default:
		break;
	}
	
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: vCleanup()
// Desc: Cleans up Direct X Graphics & Other allocations
//-----------------------------------------------------------------------------
void vCleanup(void)
{
	// Clear the sound
	if( pSound ) {
		pSound->Unload( pPerformance );
		pSound->Release();
		pSound = NULL;
	}
	// Clear the loader
	if( pLoader ) {
		pLoader->Release();
		pLoader = NULL;
	}
	// Clear the performer
	if( pPerformance ) {
		pPerformance->Release();
		pPerformance = NULL;
	}
	// Shutdown COM
	CoUninitialize();
	// Clear the Window class object
	UnregisterClass( szWndClass, g_hInstance );
}

//-----------------------------------------------------------------------------
// Name: hrInitDirectAudio()
// Desc: Initializes the Direct Audio system to play music and sounds
//-----------------------------------------------------------------------------
HRESULT hrInitDirectAudio(HWND hWnd)
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
// Name: hrLoadSound()
// Desc: Loads a wave file
//-----------------------------------------------------------------------------
HRESULT hrLoadSound( char *szFileName )
{
	WCHAR	wstrFileName[256];
	
	// Convert the filename to wide character format
	DXUtil_ConvertGenericStringToWide( wstrFileName, szFileName );
	
	// Make sure audio is initialized
	if( !pLoader ) 
		return(SOUNDERROR_MUSICLOADER);
	if( !pPerformance ) 
		return(SOUNDERROR_MUSICPERFORMANCE);
	// Clean up sound if it already exists
	if( pSound ) {
		pSound->Unload( pPerformance );
		pSound->Release();
		pSound = NULL;
	}
	
	// Load the sound from a file
	if ( FAILED(pLoader->LoadObjectFromFile(
		CLSID_DirectMusicSegment,
		IID_IDirectMusicSegment8,
		wstrFileName,
		(LPVOID*) &pSound
		)))
	{
		return(SOUNDERROR_LOAD);
	}
	
	// Download the data
	if ( FAILED ( pSound->Download( pPerformance ) ) ) {
		return(SOUNDERROR_DOWNLOAD);
	}
	
	return(S_OK);
}

//-----------------------------------------------------------------------------
// Name: hrPlaySound()
// Desc: Plays the sound segment passed to it
//-----------------------------------------------------------------------------
HRESULT hrPlaySound(IDirectMusicSegment8 *pSegment)
{
	// Make sure there is a performance object present
	if( !pPerformance ) 
		return( SOUNDERROR_MUSICPERFORMANCE );
	
	if( !pSegment )
		return( SOUNDERROR_NOSEGMENT );
	
	// Play the sound segment
	if( FAILED ( pPerformance->PlaySegmentEx(
		pSegment,
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

