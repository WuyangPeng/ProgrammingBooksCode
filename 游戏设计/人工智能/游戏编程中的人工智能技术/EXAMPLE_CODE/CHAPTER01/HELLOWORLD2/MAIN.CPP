#include <windows.h>

#include "defines.h"

//-----------------------------------------------------------------------
//  
//  Name: HelloWorld2 example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: Demonstration of (useless) window creation!
//
//------------------------------------------------------------------------
//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Hello World!";
char*	g_szWindowClassName = "MyWindowClass";

//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages. 
//  I'll be talking about this function in much more detail when we get
//  to the HelloWorld3 example. All you neeed to know for now is that this
//  function has to exist for this example to run!
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{

		 return DefWindowProc (hwnd, msg, wParam, lParam);
}

//-------------------------------- WinMain -------------------------------
//
//	The entry point of the windows program
//------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{
     //handle to our window
		 HWND						hWnd;
    
		 //our window class structure
		 WNDCLASSEX     winclass;

     // first fill in the window class stucture
	   winclass.cbSize        = sizeof(WNDCLASSEX);
	   winclass.style         = CS_HREDRAW | CS_VREDRAW;
     winclass.lpfnWndProc   = WindowProc;
     winclass.cbClsExtra    = 0;
     winclass.cbWndExtra    = 0;
     winclass.hInstance     = hInstance;
     winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
     winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
     winclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
     winclass.lpszMenuName  = NULL;
     winclass.lpszClassName = g_szWindowClassName;
	   winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

		 //register the window class
		if (!RegisterClassEx(&winclass))
		{
			MessageBox(NULL, "Class Registration Failed!", "Error", 0);

			//exit the application
			return 0;
		}

		 //create the window and assign its ID to hwnd    
     hWnd = CreateWindowEx (NULL,                 // extended style
                            g_szWindowClassName,  // window class name
                            g_szApplicationName,  // window caption
                            WS_OVERLAPPEDWINDOW,  // window style
                            0,                    // initial x position
                            0,                    // initial y position
                            WINDOW_WIDTH,         // initial x size
                            WINDOW_HEIGHT,        // initial y size
                            NULL,                 // parent window handle
                            NULL,                 // window menu handle
                            hInstance,            // program instance handle
                            NULL);                // creation parameters

     //make sure the window creation has gone OK
     if(!hWnd)
     {
       MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
     }
     
     //make the window visible
		 ShowWindow (hWnd, iCmdShow);

     UpdateWindow(hWnd);

     UnregisterClass( g_szWindowClassName, winclass.hInstance );

     return 0;
}


