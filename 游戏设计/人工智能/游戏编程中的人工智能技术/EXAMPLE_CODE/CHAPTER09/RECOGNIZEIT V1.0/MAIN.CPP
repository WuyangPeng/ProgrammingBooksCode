#include <windows.h>   
#include <stdlib.h>
#include <time.h>

#include "CNeuralNet.h"
#include "defines.h"
#include "CController.h"
#include "CData.h"
#include "resource.h"

//turn off annoying STL warnings
#pragma warning (disable : 4089)



///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter9 - RecognizeIt v1.0";
char*			szWindowClassName = "Backprop";

//-----------------------------------WinProc-----------------------------
//
//-----------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, 
						                UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	//these hold the dimensions of the client window area
	static int cxClient, cyClient;

  //keep a note of the hinstance so any dialog boxes may
  //be invoked
  static HINSTANCE  hInstance;

	//used to create the back buffer
	static HDC		    hdcBackBuffer;
	static HBITMAP	  hBitmap;
	static HBITMAP	  hOldBitmap; 

  //the mouse recognition object
  static CController     MouseController(hwnd);  

	switch(msg)
	{	
		case WM_CREATE: 
		{
			//seed the random number generator
			srand((unsigned) time(NULL));

			//get the size of the client window
			RECT rect;
			GetClientRect(hwnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;


			//create a surface to render to(backbuffer)
			hdcBackBuffer = CreateCompatibleDC(NULL);

			HDC hdc = GetDC(hwnd);

			hBitmap = CreateCompatibleBitmap(hdc,
											                cxClient,
											                cyClient);
			ReleaseDC(hwnd, hdc);

			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);  
      
      hInstance = ((LPCREATESTRUCT)lparam)->hInstance;
      
		} 
			
		break;


    //this is here so winmain can train the network immediately
    //after the window is created and displayed
    case UM_TRAIN:
      {
        MouseController.TrainNetwork();
      }

      break;
      
    case WM_RBUTTONDOWN:
    {
      //switch mouse recording on
      MouseController.Drawing(true, hInstance);
    }
    
    break;

    case WM_RBUTTONUP:
    {
      //stop recording. If there is a problem with the network
      //exit from app
      if(!MouseController.Drawing(false, hInstance))
      {
        SendMessage(hwnd, WM_DESTROY, NULL, NULL);
      }
    }

    break;

    case WM_MOUSEMOVE:
    {
       if (MouseController.Drawing())
       {
          //record this mouse position
          MouseController.AddPoint(MAKEPOINTS(lparam));
       }
    }

    break;
		
		//check key press messages
		case WM_KEYUP:
		{
			switch(wparam)
			{

				case VK_ESCAPE:
				{
					PostQuitMessage(0);
				}

				break;

        case 'T':
          {
            if(!MouseController.TrainNetwork())
            {
              SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            }
          }

        break;

        case 'L':
          {
            
            MouseController.LearningMode();
          }

          break;

			}//end WM_KEYUP switch
		}

		break;

		//has the user resized the client area?
		case WM_SIZE:
		{
 			cxClient = LOWORD(lparam);
			cyClient = HIWORD(lparam);

			//resize the backbuffer accordingly
			SelectObject(hdcBackBuffer, hOldBitmap);

			HDC hdc = GetDC(hwnd);

			hBitmap = CreateCompatibleBitmap(hdc,
											                 cxClient,
											                 cyClient);
			ReleaseDC(hwnd, hdc);
			
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap); 
		} 

		break;

		case WM_PAINT: 
		{
      PAINTSTRUCT ps;
      
		  BeginPaint(hwnd, &ps);
		
			//fill the backbuffer with white
			BitBlt(hdcBackBuffer,
             0,
             0,
             cxClient,
             cyClient,
             NULL,
             NULL,
             NULL,
             WHITENESS);

      MouseController.Render(hdcBackBuffer, cxClient, cyClient);
			
			//now blit backbuffer to front
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

			EndPaint(hwnd, &ps);
		} 
			
		break;

		case WM_DESTROY: 
		{
			SelectObject(hdcBackBuffer, hOldBitmap);
			
			//clean up our backbuffer objects
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap); 
     
      //kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);
 		} 
			
		break;

	}//end switch

	// default msg handler 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

}//end WinProc


//-----------------------------------WinMain-----------------------------------------
//	Entry point for our windows application
//-----------------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE hinstance,
					          HINSTANCE hprevinstance,
					          LPSTR lpcmdline,
					          int ncmdshow)
{

	WNDCLASSEX winclass; 
	HWND	   hwnd;	 
	MSG		   msg;		 

	// first fill in the window class stucture
	winclass.cbSize       = sizeof(WNDCLASSEX);
	winclass.style			  = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			  = NULL;
	winclass.hCursor		  = LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground= NULL; 
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName= szWindowClassName;
	winclass.hIconSm      = NULL;


	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		MessageBox(NULL, "Error Registering Class!", "Error", 0);
    return 0;
	}

	// create the window (one that cannot be resized)
	if (!(hwnd = CreateWindowEx(NULL,									
								              szWindowClassName,						
								              szApplicationName,						
								              WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
					 			              GetSystemMetrics(SM_CXSCREEN)/2 - WINDOW_WIDTH/2,
                              GetSystemMetrics(SM_CYSCREEN)/2 - WINDOW_HEIGHT/2,									
								              WINDOW_WIDTH,
                              WINDOW_HEIGHT,				
								              NULL,									
								              NULL,								
								              hinstance,								
								              NULL)))	
	{
    MessageBox(NULL, "Error Creating Window!", "Error", 0);
		return 0;
	}
        
 
	
	//Show the window
	ShowWindow(hwnd, SW_SHOWDEFAULT );
	UpdateWindow(hwnd);

  //train the network
  SendMessage(hwnd, UM_TRAIN, NULL, NULL);

 	//entry point of our message handler
	while (GetMessage (&msg, NULL, 0, 0))
  {
     TranslateMessage (&msg);
     DispatchMessage (&msg);

     //update window
     InvalidateRect(hwnd, NULL, TRUE);
		 UpdateWindow(hwnd);
  }
							
  UnregisterClass( szWindowClassName, winclass.hInstance );
	
	return 0;

} //end WinMain



