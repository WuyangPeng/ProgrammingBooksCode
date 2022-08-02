//-----------------------------------------------------------------------
//  
//  Name: GDI_Lines2 example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: Code demonstrating the creation and use of custom pens

//------------------------------------------------------------------------

#include <windows.h>

#include "defines.h"



//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "The Groovy GDI - Lines2";
char*	g_szWindowClassName = "MyWindowClass";

//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
    //create some pens to use for drawing
    static HPEN BluePen  = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	  static HPEN RedPen   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	  static HPEN GreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    static HPEN PurplePen= CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
    static HPEN OldPen   = NULL;
  
    //these hold the dimensions of the client window area
	  static int cxClient, cyClient;
    
    switch (msg)
    {
	
		//A WM_CREATE msg is sent when your application window is first
		//created
    case WM_CREATE:
      {
         //to get get the size of the client window first we need  to create
         //a RECT and then ask Windows to fill in our RECT structure with
         //the client window size. Then we assign to cxClient and cyClient 
         //accordingly
			   RECT rect;

			   GetClientRect(hwnd, &rect);

			   cxClient = rect.right;
			   cyClient = rect.bottom;

      }

      break;

    
    case WM_PAINT:
      {
 				 PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);

         //first select a pen to draw with and store a copy
         //of the pen we are swapping it with
         OldPen = (HPEN)SelectObject(ps.hdc, RedPen);

          //how many lines per side we are going to draw
          const int NumLinesPerSide = 10;

          //calculate the step size for the line drawing based upon the
          //the window dimensions
          int yStep = cyClient/NumLinesPerSide;
          int xStep = cxClient/NumLinesPerSide;
          
          //now do some drawing
          for (int mult=1; mult<NumLinesPerSide; ++mult)
          {
            //select a pen
            SelectObject(ps.hdc, RedPen);
            //move to beginning of the line
            MoveToEx(ps.hdc, xStep*mult, 0, 0);
            //draw the line
            LineTo(ps.hdc, 0, cyClient-yStep*mult);

            //select a pen
            SelectObject(ps.hdc, PurplePen);
            //move to beginning of the line
            MoveToEx(ps.hdc, xStep*mult, cyClient, 0);
            //draw the line
            LineTo(ps.hdc, cxClient, cyClient-yStep*mult);

            //select a pen
            SelectObject(ps.hdc, GreenPen);
            //move to beginning of the line
            MoveToEx(ps.hdc, xStep*mult, 0, 0);
            //draw the line
            LineTo(ps.hdc, cxClient, yStep*mult);

            //select a pen
            SelectObject(ps.hdc, BluePen);
            //move to beginning of the line
            MoveToEx(ps.hdc, xStep*mult, cyClient, 0);
            //draw the line
            LineTo(ps.hdc, 0, yStep*mult);
          }
         
         //replace the original pen
         SelectObject(ps.hdc, OldPen);
          
         EndPaint (hwnd, &ps);
      }

      break;

    //has the user resized the client area?
		case WM_SIZE:
		  {
        //if so we need to update our variables so that any drawing
        //we do using cxClient and cyClient is scaled accordingly
			  cxClient = LOWORD(lParam);
			  cyClient = HIWORD(lParam);
      }

      break;
          
		 case WM_DESTROY:
			 {
				 //delete the pens
         DeleteObject(RedPen);
         DeleteObject(GreenPen);
         DeleteObject(BluePen);
         DeleteObject(PurplePen);
         DeleteObject(OldPen);
         
         // kill the application, this sends a WM_QUIT message  
				 PostQuitMessage (0);
			 }

       break;

     }//end switch

     //this is where all the messages not specifically handled by our 
		 //winproc are sent to be processed
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
			MessageBox(NULL, "Registration Failed!", "Error", 0);

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
     UpdateWindow (hWnd);

     //this will hold any windows messages
		 MSG msg;
     
 		 //entry point of our message handler
		 while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg);
          DispatchMessage (&msg);
     }

     UnregisterClass( g_szWindowClassName, winclass.hInstance );
     return msg.wParam;
}


