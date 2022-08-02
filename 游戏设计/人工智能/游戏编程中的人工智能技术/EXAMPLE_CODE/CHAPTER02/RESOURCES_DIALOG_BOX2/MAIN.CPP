//-----------------------------------------------------------------------
//  
//  Name: Resources_Dialog_Box2 example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: Code demonstrating the use of a dialog box to change parameters
//------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#include "defines.h"
#include "utils.h"
#include "resource.h"



//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Bouncing Balls - with Dialog";
char*	g_szWindowClassName = "MyWindowClass";

//create some global variables for the ball size and number so that
//we can easily alter them via the options dialog box.
int g_iBallRadius = RADIUS;
int g_iNumBalls   = NUM_BALLS;

//global handle to our programs window
HWND g_hwnd = NULL;

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
//--------------------------------- AboutDialogProc ----------------------
//
//  message handler for the 'About' dialog box
//------------------------------------------------------------------------
BOOL CALLBACK AboutDialogProc(HWND   hwnd,
                              UINT   msg,
                              WPARAM wParam,
                              LPARAM lParam)
{
  switch(msg)
  {
  case WM_INITDIALOG:
    {
      return true;
    }

    break;

  case WM_COMMAND:
    {
      switch(LOWORD(wParam))
      {
      case IDOK:
        {
          EndDialog(hwnd, 0);

          return true;
        }

        break;
      }
    }

    break;

  }//end switch

  return false;
}
//--------------------------------- OptionsDialogProc ----------------------
//
//  message handler for the 'Ball Options' dialog box
//------------------------------------------------------------------------
BOOL CALLBACK OptionsDialogProc(HWND   hwnd,
                                UINT   msg,
                                WPARAM wParam,
                                LPARAM lParam)
{
  //get handles to edit controls
  HWND hwndNumBalls = GetDlgItem(hwnd, IDC_EDIT1);
	HWND hwndRadius		= GetDlgItem(hwnd, IDC_EDIT2);
	
   switch(msg)
  {
  case WM_INITDIALOG:
    {
      //we have to update the edit boxes with the current radius
      //and number of balls
		  string s = itos(g_iNumBalls);
		  SetWindowText(hwndNumBalls, s.c_str());

      s = itos(g_iBallRadius);
		  SetWindowText(hwndRadius, s.c_str());
      
      return true;
    }

    break;

  case WM_COMMAND:
    {
      switch(LOWORD(wParam))
      {
      case IDOK:
        {
          //for each edit box we collect the information and then change
          //the parameters accordingly
				  char  buffer[5];

          //-----------first the number of balls
				  GetWindowText(hwndNumBalls, buffer, 5);

				  //convert to an int
          g_iNumBalls = atoi(buffer);

          //-----------Now the radius
				  GetWindowText(hwndRadius, buffer, 5);

				  //convert to an int
          g_iBallRadius = atoi(buffer);

          //send a custom message to the WindowProc so that
          //new balls are spawned
          PostMessage(g_hwnd, UM_SPAWN_NEW, NULL, NULL);

          EndDialog(hwnd, 0);
				
          return true;
        }

        break;
      }
    }

    break;

  }//end switch

  return false;
}
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
    static SBall* balls;

	 //used to create the back buffer
   static HDC		hdcBackBuffer;
   static HBITMAP	hBitmap;
   static HBITMAP	hOldBitmap;

   //this holds the hinstance
   static HINSTANCE hInstance;

    switch (msg)
    {
	
		//A WM_CREATE msg is sent when your application window is first
		//created
    case WM_CREATE:
      {
         //get the instance handle so we can invoke the dialogue box
         //when required
         hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
          
			   RECT rect;

			   GetClientRect(hwnd, &rect);

			   cxClient = rect.right;
			   cyClient = rect.bottom;

         //seed random number generator
         srand((unsigned) time(NULL));

         //create the array of balls
         balls = new SBall[g_iNumBalls];
         
         //set up the balls with random positions and velocities
         for (int i=0; i<g_iNumBalls; ++i)
         {
           balls[i].posX = RandInt(0, cxClient);
           balls[i].posY = RandInt(0, cyClient);
           balls[i].velX = RandInt(0, MAX_VELOCITY);
           balls[i].velY = RandInt(0, MAX_VELOCITY);
         }
         
         //---------------create a surface for us to render to(backbuffer)

         //create a memory device context
         hdcBackBuffer = CreateCompatibleDC(NULL);

         //get the DC for the front buffer
         HDC hdc = GetDC(hwnd);

         hBitmap = CreateCompatibleBitmap(hdc,
                                          cxClient,
                                          cyClient);

			  
         //select the bitmap into the memory device context
			   hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

         //don't forget to release the DC
         ReleaseDC(hwnd, hdc);
      }

      break;

    case UM_SPAWN_NEW:
      {
        //create a new array of balls of the required size
        if (balls)
        {
          delete balls;
        }

        //create the array of balls
         balls = new SBall[g_iNumBalls];
         
         //set up the balls with random positions and velocities
         for (int i=0; i<g_iNumBalls; ++i)
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
    
    case WM_COMMAND:
       {
         switch(wParam)
         {
         case ID_ABOUT:
           {
             DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDialogProc);
           }
           break;

         case ID_BALL_OPTIONS:
           {
             DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, OptionsDialogProc);
           }
           break;


         }// end switch WM_COMMAND
       }

       break;


    case WM_PAINT:
      {
 		       
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);

        //fill our backbuffer with white
         BitBlt(hdcBackBuffer,
                0,
                0,
                cxClient,
                cyClient,
                NULL,
                NULL,
                NULL,
                WHITENESS);
          
         //first select a pen to draw with and store a copy
         //of the pen we are swapping it with
         OldPen = (HPEN)SelectObject(hdcBackBuffer, BluePen);

         //do the same for our brush
         OldBrush = (HBRUSH)SelectObject(hdcBackBuffer, RedBrush);

         //update and draw the balls
         for (int i=0; i<g_iNumBalls; ++i)
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
           Ellipse(hdcBackBuffer,
                   balls[i].posX - g_iBallRadius,
                   balls[i].posY - g_iBallRadius,
                   balls[i].posX + g_iBallRadius,
                   balls[i].posY + g_iBallRadius);
 

         }
        
         //replace the original pen
         SelectObject(hdcBackBuffer, OldPen);
         //and brush
         SelectObject(hdcBackBuffer, OldBrush);

         //now blit backbuffer to front
			   BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
          
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

      //now to resize the backbuffer accordingly. First select
      //the old bitmap back into the DC
			SelectObject(hdcBackBuffer, hOldBitmap);

      //don't forget to do this or you will get resource leaks
      DeleteObject(hBitmap); 

			//get the DC for the application
      HDC hdc = GetDC(hwnd);

			//create another bitmap of the same size and mode
      //as the application
      hBitmap = CreateCompatibleBitmap(hdc,
											cxClient,
											cyClient);

			ReleaseDC(hwnd, hdc);
			
			//select the new bitmap into the DC
      SelectObject(hdcBackBuffer, hBitmap);

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

         //clean up our backbuffer objects
         SelectObject(hdcBackBuffer, hOldBitmap);

         DeleteDC(hdcBackBuffer);
         DeleteObject(hBitmap); 
         
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
     winclass.hbrBackground = NULL;
     winclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
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
        
     
     g_hwnd = hWnd;

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


