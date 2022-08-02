//-----------------------------------------------------------------------
//  
//  Name: GDI_Backbuffer example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: Code demonstrating screen flashing/tearing/flickering
//
//------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#include "defines.h"
#include "utils.h"



//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Bouncing Balls - Without Backbuffer";
char*	g_szWindowClassName = "MyWindowClass";

//--------------------------------SBall------------------------------------
//
//  define a simple structure for the balls
//-------------------------------------------------------------------------
struct SBall
{
  //to hold the balls coordinates
  int posX;
  int posY;

  //and velocity
  int velX;
  int velY;

  SBall(){}
  
};

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
  
    //create some balls
    static SBall* balls = new SBall[NUM_BALLS];

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
         
         //set up the balls with random positions and velocities
         for (int i=0; i<NUM_BALLS; ++i)
         {
           balls[i].posX = RandInt(0, cxClient);
           balls[i].posY = RandInt(0, cyClient);
           balls[i].velX = RandInt(0, MAX_VELOCITY);
           balls[i].velY = RandInt(0, MAX_VELOCITY);
         }
      }

      break;

    case WM_KEYUP:
      {
        switch(wParam)
        {
         case VK_ESCAPE:
          {
            PostQuitMessage(0);
          }
          
          break;
        }
      }
    
    case WM_PAINT:
      {
 		       
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);
          
         //first select a pen to draw with and store a copy
         //of the pen we are swapping it with
         OldPen = (HPEN)SelectObject(ps.hdc, BluePen);

         //do the same for our brush
         OldBrush = (HBRUSH)SelectObject(ps.hdc, RedBrush);

         //update and draw the balls
         for (int i=0; i<NUM_BALLS; ++i)
         {

          //check to see if they have hit any walls and reverse velocity 
           //accordingly
           if ( (balls[i].posX >= cxClient) || (balls[i].posX <0))
           {
             balls[i].velX = -balls[i].velX;
           }

           if ( (balls[i].posY >= cyClient) || (balls[i].posY <0))
           {
             balls[i].velY = -balls[i].velY;
           }

           // update their position
           balls[i].posX += balls[i].velX;
           balls[i].posY += balls[i].velY;

       
          
           
           //render to display
           Ellipse(ps.hdc,
                   balls[i].posX - RADIUS,
                   balls[i].posY - RADIUS,
                   balls[i].posX + RADIUS,
                   balls[i].posY + RADIUS);
 

         }
        
         //replace the original pen
         SelectObject(ps.hdc, OldPen);
         //and brush
         SelectObject(ps.hdc, OldBrush);
          
         EndPaint (hwnd, &ps);

         //delay a little
         Sleep(10);

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
         DeleteObject(BluePen);
         DeleteObject(OldPen);

         //and the brushes
         DeleteObject(RedBrush);
         DeleteObject(OldBrush);

         //and the balls
         delete[] balls;
         
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


