//	WinMain.cpp : The meat and potatoes.
#include "Game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_CLASS_NAME	"WINDOWCLASS"		//	Class name.

/***********/
/* GLOBALS */
/***********/
HWND main_hWnd;		//	To store the Main Window Handle.
Game game;



/*************/
/* FUNCTIONS */
/*************/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//	This is the main message handler of the system
	PAINTSTRUCT	ps;			//	Used in WM_PAINT
	HDC			hdc;		//	Handle to a device context

	//	What is the message 
	switch(msg)
	{	
		case WM_CREATE: 
		{
			//	Do initialization stuff here
			return(0);
		}
		break;

		case WM_PAINT:
		{
			//	Start painting
			hdc = BeginPaint(hwnd,&ps);

			//	End painting
			EndPaint(hwnd,&ps);
			return(0);
		}
		break;

/*		case WM_CHAR:
		{
			if(wparam == VK_ESCAPE)
				PostQuitMessage(0);
				
		}
		break; */

		case WM_DESTROY: 
		case WM_CLOSE:
		{
			//	Kill the application			
			PostQuitMessage(0);
		}
		break;

		default:
		break;
	}

	//	Process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));
}

/***********/
/* WINMAIN */
/***********/

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	WNDCLASS winclass;	//	This will hold the class we create
	HWND	 hwnd;		//	Generic window handle
	MSG		 msg;		//	Generic message

	//	First fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
							  CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; 
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	//	Register the window class
	if (!RegisterClass(&winclass))
		return(0);

	bool fullscreen;
	long flags;

	MessageBox(NULL, "\tWould you like to run in fullscreen?\n(Windowed mode requires 16 bit desktop color depth)", 
			   "FULLSCREEN / WINDOWED", MB_YESNO) == IDYES
	? fullscreen = true : fullscreen = false;

	if(!fullscreen)
	{
		flags = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	}
	else
		flags = WS_OVERLAPPED | WS_VISIBLE | WS_POPUP;

	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME,				//	Class Name
							  "Racer",							//	Title of the Window.
							  flags,							//	Window Flags
					 		  0,0,								//	Window Start Point (x, y)
							  WINDOW_WIDTH,						//	Width of Window
							  WINDOW_HEIGHT,					//	Height of Window
							  NULL,								//	Handle to parent 
							  NULL,								//	Handle to menu
							  hinstance,						//	Instance
							  NULL)))							//	Creation params
		return(0);
	ShowCursor(FALSE);											// Hide Mouse Pointer

	//	Store the Handle to the Window.
	main_hWnd = hwnd;

	//	Perform all Game specific initialization
	game.GameInit(main_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT, fullscreen);

	//	Enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			//	Test if this is a quit
			if (msg.message == WM_QUIT)
				break;
		
			//	Translate any accelerator keys
			TranslateMessage(&msg);

			//	Send the message to the window proc
			DispatchMessage(&msg);
		}
    
		//	Main game processing goes here
		if (!(game.GameMain()))
			break;
	}

	//	Shutdown game and release all resources
//	Game.GameShutdown();

	//	Return to Windows like this
	return(msg.wParam);
}
