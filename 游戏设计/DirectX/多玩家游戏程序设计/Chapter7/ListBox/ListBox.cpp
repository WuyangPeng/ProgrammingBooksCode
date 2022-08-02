//###################################################################################
//#																					#
//#			Chapter 7 - Simple Child Object Program									#		
//#																					#
//#						Displays a listbox and a button								#
//#																					#
//#						Todd Barron, 10/01/2000										#
//#																					#
//###################################################################################

#include <windows.h>
#include <stdio.h>

#define		IDC_hBU_Join		40001
#define		IDC_hLB_Output		40002

// create some global handles for our child window components
HWND		hBU_Join			= NULL;
HWND		hLB_Output			= NULL;

LPCTSTR		lpszApplicationName = "ListBoxProg";
LPCTSTR		lpszTitle			= "ListBox Example";

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);
void vShowText(HWND	hChildHandle, char *szText);

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

	if( RegisterClassEx( &wndclass ) == 0 ) 
	{
		// Do error logic here
		exit(1);
	}

	// Create the window
	hWnd = CreateWindow(	lpszApplicationName,		// Application Name
							lpszTitle,					// Name Displayed on Title Bar
							WS_OVERLAPPEDWINDOW,
							100,
							100,
							400,
							340,
							NULL,
							NULL,
							hInstance,
							NULL );

	// hBU_Join
	hBU_Join = CreateWindow(
		"BUTTON",
		"Join",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		285,
		280,
		100,
		28,
		hWnd,(HMENU)IDC_hBU_Join,hInstance,NULL);

	// hLB_Output
	hLB_Output = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"LISTBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER,
		5,
		47,
		380,
		230,
		hWnd,(HMENU)IDC_hLB_Output,hInstance,NULL);	
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// Process messages until the program is terminated
	while( TRUE )
	{
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

// Callback function to handle window messages
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	char	szText[256];
	static	count = 0;

	switch (iMsg)
    {
		case WM_COMMAND:
			// Check for child window messages
			switch(LOWORD(wParam))
			{
				// Check if the user clicked the button
				case IDC_hBU_Join:
					sprintf(szText,"Join Number %d",count++);
					PlaySound("join.wav",NULL,SND_FILENAME|SND_ASYNC);
					vShowText(hLB_Output,szText);
					break;
			}
			break;			
		case WM_KEYDOWN:
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

//
// Function to display text into the edit window
//
void vShowText(HWND	hChildHandle, char *szText)
{
	int Line;
	
	// add string to the listbox
	SendMessage(hChildHandle,LB_ADDSTRING,0,(LPARAM)szText);
	
	// determine number of items in listbox
	Line = SendMessage(hChildHandle,LB_GETCOUNT,0,0);
	
	// flag last item as the selected item, to scroll listbox down
	SendMessage(hChildHandle,LB_SETCURSEL,Line-1,0);
	
	// unflag all items to eliminate negative highlite
	SendMessage(hChildHandle,LB_SETCURSEL,-1,0);
}
