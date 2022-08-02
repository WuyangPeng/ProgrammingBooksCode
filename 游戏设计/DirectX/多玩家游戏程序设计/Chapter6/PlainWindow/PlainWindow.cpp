//###################################################################################
//#																					#
//#			Chapter 6 - Plain Window Program										#		
//#																					#
//#						Creates an empty Window										#
//#																					#
//#						Todd Barron, 10/08/2000										#
//#																					#
//###################################################################################

// Standard windows include
#include <windows.h>

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND		hWnd;
	MSG			msg;
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
	wndclass.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= "Simple Window Class";	// Registered Class Name
	wndclass.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );

	if( RegisterClassEx( &wndclass ) == 0 ) 
	{
		// Do error logic here
		exit(1);
	}

	// Create the window
	hWnd = CreateWindow(	"Simple Window Class",		// Application Name
							"Simple Window Program",	// Name Displayed on Title Bar
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
	while( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return ( msg.wParam );
}

//
// Message Loop CallBack Function ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	switch( iMsg ) 
	{
		// Called when window is first created
		case WM_CREATE:
			return( 0 );
		// Called when the window is refreshed
		case WM_PAINT:
			return( 0 );
		// Called when the user closes the window or terminates the application
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return( 0 );
	}
	
	return DefWindowProc( hWnd, iMsg, wParam, lParam );
}

