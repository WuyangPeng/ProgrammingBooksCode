//###################################################################################
//#																					#
//#			Chapter 6 - CreateThread Program										#		
//#																					#
//#						Creates a thread running in the background					#
//#						Also demonstrates usage of Mutexes							#
//#																					#
//#						Todd Barron, 10/08/2000										#
//#																					#
//###################################################################################

// Standard windows include
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

// Mutex handle
HANDLE	g_hCreditMutex;

// Memory shared with thread
struct SharedMemory
{
	int iQuit;
	int	iCredits;
};

// Our global shared memory
SharedMemory g_SharedMem;

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);

// Thread function prototype
void thrCreditsThread(SharedMemory *sm);

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND		hWnd;
	MSG			msg;
	WNDCLASSEX	wndclass;
	int			iStartCredits = 0;	// Keep track of last known credits

	// Thread Variables
	DWORD	dwCreditsID;
	HANDLE	hCreditsThreadHandle;

	// Create our CreditMutex Here
	g_hCreditMutex = CreateMutex(
		NULL,
		0,  
		"Credit Mutex"
	);

	// Initialize the data structure
	g_SharedMem.iCredits = 0;
	g_SharedMem.iQuit = 0;

	// Create the CreditThread here
	hCreditsThreadHandle = CreateThread(
		NULL,											// Security, default is ok
		NULL,											// Initial stack size, default ok
		(LPTHREAD_START_ROUTINE ) &thrCreditsThread,    // The thread function  
		&g_SharedMem,									// Data to pass to the function
		NULL,											// Creation flags, keep NULL
		&dwCreditsID									// Identifier (we dont use this)
	);
 
	// Set up window attributes
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= fnMessageProcessor;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= "Create Thread Class";		// Registered Class Name
	wndclass.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );

	if( RegisterClassEx( &wndclass ) == 0 ) 
	{
		// Do error logic here
		exit(1);
	}

	// Create the window
	hWnd = CreateWindow(	"Create Thread Class",			// Application Name
							"Coin Acceptor Simulator - Press ENTER To Subtract Credit",		// Name Displayed on Title Bar
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL,
							NULL,
							hInstance,
							NULL );

	// Display the window
	ShowWindow( hWnd, iCmdShow );
	UpdateWindow( hWnd );

	// Process messages until the program is terminated
	while( TRUE )
	{
		// Check if credits have been updated
		if( iStartCredits != g_SharedMem.iCredits ) {
			iStartCredits = g_SharedMem.iCredits;
			// Force window to update
			InvalidateRect(hWnd,NULL,0);
		}
		// Check for Windows Events & Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Tell the thread to quit
	g_SharedMem.iQuit = 1;

	// Wait on the thread to finish (wait forever if necessary)
	WaitForSingleObject( hCreditsThreadHandle, INFINITE );

	// Free the mutex
	CloseHandle( g_hCreditMutex );

	// Free the credits thread
	CloseHandle( hCreditsThreadHandle );

	return ( msg.wParam );
}

//
// Message Loop CallBack Function ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	char		szCredits[128];
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rect;
	
	// Force a redraw
	InvalidateRect(hWnd,NULL,0);

	switch( iMsg ) 
	{
		// Called when window is first created
		case WM_CREATE:
			return( 0 );
		// Called when the window is refreshed
		case WM_PAINT:
			hdc = BeginPaint( hWnd, &ps );
			GetClientRect( hWnd, &rect );
			// Populate the string to output
			sprintf(szCredits,"Credits = %d   ",g_SharedMem.iCredits); 
			// Draw the text 
			TextOut( hdc, 0, 0, szCredits, strlen(szCredits) );
			EndPaint( hWnd, &ps );
			return( 0 );
		// Called when the user closes the window or terminates the application
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return( 0 );
		// Remove a credit when the user presses a key
		case WM_KEYDOWN:
			// Request CreditsMutex
			WaitForSingleObject( g_hCreditMutex, INFINITE );

			// Only remove credits if present
			if( g_SharedMem.iCredits ) {
				// Remove a credit
				g_SharedMem.iCredits--;
			}

			// Release the credits mutex
			ReleaseMutex( g_hCreditMutex );
			return( 0 );
	}
	
	return DefWindowProc( hWnd, iMsg, wParam, lParam );
}

//
// The Credits Thread Function
//
void thrCreditsThread(SharedMemory *sm)
{
	// Loop until we are told to quit
	while( !sm->iQuit ) {
		// Add a credit every second
		Sleep( 1000 );		

		// Request CreditsMutex
		WaitForSingleObject( g_hCreditMutex, INFINITE );

		// Add to credits
		sm->iCredits++;

		// Release the credits mutex
		ReleaseMutex( g_hCreditMutex );
	}
}


