//-----------------------------------------------------------------------
//  
//  Name: main.h
//  
//  Author: Mat Buckland 2002
//
//  Desc:  Lunar Lander example project
//
//------------------------------------------------------------------------


#include <windows.h>   
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>


#include "defines.h"
#include "utils.h"
#include "CController.h"
#include "CTimer.h"
#include "Resource.h"


///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter6 - Lunar Lander - Unmanned";
char*			szWindowClassName = "Lander";


//The controller class for this simulation
CController*	g_pController	 = NULL; 

//---------------------------- Cleanup ----------------------------------
//
//	simply cleans up any memory issues when the application exits
//-----------------------------------------------------------------------
void Cleanup()
{
	if (g_pController)

		delete g_pController;
}
//-----------------------------------WinProc-----------------------------
//
//-----------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, 
						                UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	//these hold the dimensions of the client window area
	static int cxClient, cyClient;

	//used to create the back buffer
	static HDC		  hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap; 


	switch(msg)
	{	
		case WM_CREATE: 
		{
			//seed the random number generator
			srand((unsigned) time(NULL));

			//get the size of the client window
			RECT rect;
			GetClientRect(hWnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;

			//setup the controller
			g_pController = new CController(cxClient,
                                      cyClient);

				//create a surface for us to render to(backbuffer)
			hdcBackBuffer = CreateCompatibleDC(NULL);

			HDC hdc = GetDC(hWnd);

			hBitmap = CreateCompatibleBitmap(hdc,
											                 cxClient,
											                 cyClient);
			ReleaseDC(hWnd, hdc);

			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap); 

      //play the start up wav
      PlaySound("open_window", NULL, SND_ASYNC|SND_FILENAME);
		} 
			
		break;
		
		//check key press messages
		case WM_KEYUP:
		{
			switch(wparam)
			{

				case VK_ESCAPE:
				{
          SendMessage(hWnd, WM_DESTROY, NULL, NULL);
				}

				break;

        case 'R':
          {
            g_pController->NewRun();
          }

          break;

				case 'F':
					{
						g_pController->ToggleFastRender();
					}
					
					break;

        case 'B':
          {
            g_pController->ToggleShowFittest();

           }

          break;

			}//end WM_KEYUP switch
		}

		break;

		case WM_PAINT: 
		{
      PAINTSTRUCT ps;
      
		  BeginPaint(hWnd, &ps);
		
			//fill our backbuffer with black
			BitBlt(hdcBackBuffer,
             0,
             0,
             cxClient,
             cyClient,
             NULL,
             NULL,
             NULL,
             BLACKNESS);
			
			//render the mines and sweepers
			g_pController->Render(hdcBackBuffer);
			
			//now blit backbuffer to front
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

			EndPaint(hWnd, &ps);
		} 
			
		break;

		case WM_DESTROY: 
		{
			SelectObject(hdcBackBuffer, hOldBitmap);
			
			//clean up our backbuffer objects
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap); 

      // kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);
 		} 
			
		break;

		default:break;

	}//end switch

	//default msg handler 
	return (DefWindowProc(hWnd, msg, wparam, lparam));

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
	HWND	   hWnd;	 
	MSG		   msg;		 

	// first fill in the window class stucture
	winclass.cbSize       = sizeof(WNDCLASSEX);
	winclass.style			  = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			  = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor		  = LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground= NULL; 
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName= szWindowClassName;
	winclass.hIconSm      = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON2));


	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		MessageBox(NULL, "Error Registering Class!", "Error", 0);
    return 0;
	}

	// create the window
	if (!(hWnd = CreateWindowEx(NULL,									
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
	
	// Show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT );
	UpdateWindow(hWnd);

	//create a timer
	CTimer timer(FRAMES_PER_SECOND);

	//start the timer
	timer.Start();

	// Enter the message loop
	bool bDone = false;

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
							
		if (timer.ReadyForNextFrame() || g_pController->FastRender())
		{	
		  if(!g_pController->Update())
			{
				//we have a problem, end app
				bDone = true;
			}

			//this will call WM_PAINT which will render our scene
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
    }					
					
	}//end while
	
  // Clean up everything and exit the app
  Cleanup();
  UnregisterClass( szWindowClassName, winclass.hInstance );
	
	return 0;

} //end WinMain



