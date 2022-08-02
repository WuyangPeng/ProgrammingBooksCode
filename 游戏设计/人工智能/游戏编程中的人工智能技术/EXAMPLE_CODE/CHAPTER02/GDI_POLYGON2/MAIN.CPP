//-----------------------------------------------------------------------
//  
//  Name: GDI_Polygon2 example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: Code demonstrating the creation and use of a realtime message
//        pump
//
//------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#include "defines.h"
#include "utils.h"



//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "The Groovy GDI - Dazzle";
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
    static HPEN OldPen   = NULL;

    //create a solid brush
    static HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));
    static HBRUSH OldBrush = NULL;
  
    //these hold the dimensions of the client window area
	  static int cxClient, cyClient;

    //this will hold the vertices of the polygons we create
    static POINT verts[NUM_VERTS];

    static int iNumVerts = NUM_VERTS;
    
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

         //seed random number generator
         srand((unsigned) time(NULL));

         //now lets create some random vertices
         for (int v=0; v<iNumVerts; ++v)
         {
           verts[v].x = RandInt(0, cxClient);
           verts[v].y = RandInt(0, cyClient);
         }

      }

      break;

    case WM_KEYUP:
      {
        switch(wParam)
        {
        case VK_SPACE:
          {
            //create some new points for our polygon
            //now lets create some random vertices
            for (int v=0; v<iNumVerts; ++v)
            {
              verts[v].x = RandInt(0, cxClient);
              verts[v].y = RandInt(0, cyClient);
            }

             //refresh the display so we can see our
              //new polygon
              InvalidateRect(hwnd, NULL, TRUE);
              UpdateWindow(hwnd);
          }
          
          break;

        case VK_ESCAPE:
          {
            PostQuitMessage(0);
          }
          
          break;
        }
      }
    
    case WM_PAINT:
      {
 				 //create some random vertices for the polygon
         for (int v=0; v<iNumVerts; ++v)
         {
           verts[v].x = RandInt(0, cxClient);
           verts[v].y = RandInt(0, cyClient);
         } 
        
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);
          
         //first select a pen to draw with and store a copy
         //of the pen we are swapping it with
         OldPen = (HPEN)SelectObject(ps.hdc, BluePen);

         //do the same for our brush
         OldBrush = (HBRUSH)SelectObject(ps.hdc, RedBrush);

         //draw the polygon
         Polygon(ps.hdc, verts, iNumVerts);
         
         //replace the original pen
         SelectObject(ps.hdc, OldPen);
         //and brush
         SelectObject(ps.hdc, OldBrush);
          
         EndPaint (hwnd, &ps);

         //use this as a simple delay so we can see the 
         //polygons
         Sleep(100);
      }

      break;

    //has the user resized the client area?
		case WM_SIZE:
		  {
        //if so we need to update our variables so that any drawing
        //we do using cxClient and cyClient is scaled accordingly
			  cxClient = LOWORD(lParam);
			  cyClient = HIWORD(lParam);

        //create a new polygon
        for (int v=0; v<iNumVerts; ++v)
        {
           verts[v].x = RandInt(0, cxClient);
           verts[v].y = RandInt(0, cyClient);
        }
      }

      break;
          
		 case WM_DESTROY:
			 {
				 //delete the pens        
         DeleteObject(BluePen);
         DeleteObject(OldPen);

         //and the brushes
         DeleteObject(RedBrush);
         DeleteObject(OldBrush);
         
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

	   // Enter the message loop
	   bool bDone = false;

     MSG msg;

	   while(!bDone)
     {
					
		  while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
		  {
			  if( msg.message == WM_QUIT ) 
			  {
				  // Stop loop if it's a quit message
				  bDone = true;
			  } 

			  else 
			  {
				  TranslateMessage( &msg );
				  DispatchMessage( &msg );
			  }
		  }

			//this will call WM_PAINT which will render our scene
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

      //*** your game loop goes here ***//
   					
    }//end while

     UnregisterClass( g_szWindowClassName, winclass.hInstance );

     return msg.wParam;
}


