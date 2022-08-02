//###################################################################################
//#																					#
//#			Chapter 13 - Direct X Input Fundamentals								#		
//#																					#
//#						Reads input from a keyboard									#
//#																					#
//#						Todd Barron, 01/18/2001										#
//#																					#
//###################################################################################

#include <stdio.h>
#include <dinput.h>

#define KEYBOARD_BUFFERSIZE			10
#define INPUTERROR_NODI				0x81000001
#define INPUTERROR_NOKEYBOARD		0x81000002
#define INPUTERROR_KEYBOARDEXISTS	0x81000003

LPDIRECTINPUT8			pDI = NULL;         
LPDIRECTINPUTDEVICE8	pKeyboard = NULL; 
BYTE					diks[256];
BYTE					ascKeys[256];
HKL						g_Layout;

// Windows Globals
const char	*szWndClass		= "DirectInputKeyboardRead";
const char	*szProgramName	= "Direct-Input Keyboard Read Example";
HINSTANCE	g_hInstance;

// Function Prototypes
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void vCleanup(void);
HRESULT	hrInitDirectInput(void);
HRESULT hrInitKeyboard(HWND hWnd);
BYTE Scan2Ascii(DWORD scancode);
HRESULT hrReadKeyboard( void );

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
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// Setup global window instance
	g_hInstance = hInstance;
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	hr = hrInitDirectInput();
	if( hr == INPUTERROR_NODI ) {
		MessageBox( hWnd, "DirectInput Error", "Unable to initialize Direct Input.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}
	
	hr = hrInitKeyboard(hWnd);
	if( hr == INPUTERROR_NOKEYBOARD ) {
		MessageBox( hWnd, "DirectInput Error", "Unable to initialize Keyboard.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}
	
	// Process messages until the program is terminated
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else {
			hrReadKeyboard();
			// Exit the program if the ESC key is hit
			if( diks[DIK_ESCAPE] ) 
				break;
			else if ( ascKeys[13] ) 
				break;
		}
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
	if( pKeyboard ) {
		pKeyboard->Unacquire();
		pKeyboard->Release();
		pKeyboard = NULL;
	}
	if( pDI ) {
		pDI->Release();
		pDI = NULL;
	}
	
	UnregisterClass( szWndClass, g_hInstance );
}

//-----------------------------------------------------------------------------
// Name: hrInitDirectInput()
// Desc: Initializes Direct Input
//-----------------------------------------------------------------------------
HRESULT	hrInitDirectInput(void)
{
	HRESULT	hReturn = 0;
	
	// Do not try to create Direct Input if already created
	if( !pDI ) {
		// Create a DInput object
		if( FAILED( hReturn = DirectInput8Create( g_hInstance, DIRECTINPUT_VERSION, 
			IID_IDirectInput8, (VOID**)&pDI, NULL ) ) )
			return(INPUTERROR_NODI);
	}

	// Get the keyboard layout
	g_Layout = GetKeyboardLayout(0);
	
	return(hReturn);
}

//-----------------------------------------------------------------------------
// Name: hrInitKeyboard()
// Desc: Initializes Keyboard
//-----------------------------------------------------------------------------
HRESULT hrInitKeyboard(HWND hWnd)
{
	HRESULT			hReturn = 0;
	DIPROPDWORD		dipdw; 
	
	// Don't try to create the keyboard twice
	if( pKeyboard ) 
		return(INPUTERROR_KEYBOARDEXISTS);
	// Exit out if no Direct Input interface found
	else if ( !pDI ) 
		return(INPUTERROR_NODI);

	// Obtain an interface to the system keyboard device
	if( FAILED( hReturn = pDI->CreateDevice( GUID_SysKeyboard, &pKeyboard, NULL ) ) )
		return(INPUTERROR_NOKEYBOARD);
	
	// Create buffer to hold keyboard data
	ZeroMemory(&dipdw,sizeof(DIPROPDWORD));
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD); 
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	dipdw.diph.dwObj		= 0; 
	dipdw.diph.dwHow		= DIPH_DEVICE; 
	dipdw.dwData			= KEYBOARD_BUFFERSIZE;	// Buffer Size
	
	// Set the size of the buffer
	if( FAILED( hReturn = pKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) ) 
		return(INPUTERROR_NOKEYBOARD);
	
	// Set the format of the keyboard
	if( FAILED( hReturn = pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
		return(INPUTERROR_NOKEYBOARD);
	
	// Set the co-operative level to exclusive access
	if( FAILED( hReturn = pKeyboard->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) ) {
		return(INPUTERROR_NOKEYBOARD);
	}
	
	// Acquire the keyboard device
	pKeyboard->Acquire();
	
	return(0);
}

//-----------------------------------------------------------------------------
// Name: hrReadKeyboard()
// Desc: Reads buffered data from the Keyboard
//-----------------------------------------------------------------------------
HRESULT hrReadKeyboard( void )
{
	HRESULT				hr;
	DWORD				dwCurBuffer;
	DIDEVICEOBJECTDATA	didKeyboardBuffer[KEYBOARD_BUFFERSIZE];
	DWORD				dwItems = KEYBOARD_BUFFERSIZE;
	BYTE				byteASCII;

	// Dont try to read the keyboard if the interface or device is invalid
    if( !pKeyboard || !pDI ) 
        return(INPUTERROR_NOKEYBOARD);

	// Read the buffered data
	hr = pKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didKeyboardBuffer, &dwItems, 0); 
	// Keyboard may have been lost, reacquire it
	if( FAILED(hr) ) {
		pKeyboard->Acquire();
		return(S_OK);
	}
	// Process data if there is data to read
	if ( dwItems ) {
		// Process the data
		for(dwCurBuffer = 0; dwCurBuffer < dwItems; dwCurBuffer++) {
			// Map scan-code to ascii code
			byteASCII = Scan2Ascii(didKeyboardBuffer[dwCurBuffer].dwOfs);
			// Set key to be down (depressed)
			if( didKeyboardBuffer[dwCurBuffer].dwData & 0x80 ) {
				ascKeys[byteASCII] = 1;
				diks[didKeyboardBuffer[dwCurBuffer].dwOfs] = 1;
			}
			// Set key to be up
			else {
				ascKeys[byteASCII] = 0;
				diks[didKeyboardBuffer[dwCurBuffer].dwOfs] = 0;
			}
		}
	} 

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Scan2Ascii()
// Desc: Converts a scan code to ASCII
//-----------------------------------------------------------------------------
BYTE Scan2Ascii(DWORD scancode)
{
	UINT vk;
	
	vk = MapVirtualKeyEx( scancode, 1, g_Layout);

	return(vk);
}
