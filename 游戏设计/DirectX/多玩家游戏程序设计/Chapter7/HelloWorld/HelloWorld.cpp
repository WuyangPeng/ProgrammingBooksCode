//###################################################################################
//#																					#
//#			Chapter 7 - Simple Windows Program										#		
//#																					#
//#						Displays "Hello World" in a window.							#
//#																					#
//#						Todd Barron, 09/28/2000										#
//#																					#
//###################################################################################

#include <windows.h>
#include <stdio.h>

LPCTSTR		lpszApplicationName = "HelloWorld";
LPCTSTR		lpszTitle			= "Hello World Program";

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;
	HWND		hWnd;
	WNDCLASSEX	wndclass;
	
	// Set up window attributes
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= fnMessageProcessor;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= lpszApplicationName;	// Registered Class Name
	wndclass.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );

	if( RegisterClassEx( &wndclass ) == 0 ) {
		// Do error logic here
		exit(1);
	}

	// Create the window
	hWnd = CreateWindow(	lpszApplicationName,		// Application Name
							lpszTitle,					// Name Displayed on Title Bar
							WS_OVERLAPPEDWINDOW,
							100,						// X-Starting Position
							100,						// Y-Starting Position
							400,						// Width
							340,						// Height
							NULL,
							NULL,
							hInstance,
							NULL );

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// Process messages until the program is terminated
	while( TRUE ) {
		// Check for Windows Events & Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return(msg.wParam);
}

// Windows Callback function to handle messages
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	switch (iMsg)
    {
		case WM_COMMAND:
			break;			
		case WM_CREATE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd, iMsg, wParam, lParam));
    }
	return(0L);
}
