//###################################################################################
//#																					#
//#			Chapter 13 - Direct X Audio Fundamentals								#		
//#																					#
//#						Initializes Direct Audio									#
//#																					#
//#						Todd Barron, 01/18/2001										#
//#																					#
//###################################################################################

#include <stdio.h>
#include <Dmusici.h>

#define SOUNDERROR_MUSICLOADER		0x85000001
#define SOUNDERROR_MUSICPERFORMANCE	0x85000002
#define SOUNDERROR_INITAUDIO		0x85000003
#define SOUNDERROR_PATH				0x85000004
#define SOUNDERROR_VOLUME			0x85000005

// Windows Globals
const char	*szWndClass		= "DirectAudio";
const char	*szProgramName	= "Direct-Audio Init Program";
HINSTANCE	g_hInstance;

// Direct Audio Globals
IDirectMusicLoader8			*pLoader = NULL;
IDirectMusicPerformance8	*pPerformance = NULL;

// Function Prototypes
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void vCleanup(void);
HRESULT hrInitDirectAudio(HWND hWnd);

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

