#include <windows.h>   
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>


#include "defines.h"
#include "utils.h"
#include "CTimer.h"
#include "CController.h"
#include "CParams.h"
#include "resource.h"



///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter10 - Brainy Aliens";
char*			szWindowClassName = "Brainy Aliens";

//create an instance of the parameter class
CParams      g_Params;

//and a pointer to the controller class
CController* g_pController;

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

        case 'R':
				{
					g_pController->Reset();
				}

				break;

			}//end WM_KEYUP switch
		}

		break;

		case WM_PAINT: 
		{     
      PAINTSTRUCT ps;
      
		  BeginPaint(hWnd, &ps);
		
			//fill our backbuffer with white
			BitBlt(hdcBackBuffer,
             0,
             0,
             cxClient,
             cyClient,
             NULL,
             NULL,
             NULL,
             BLACKNESS);

      //render
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

	// default msg handler 
	return (DefWindowProc(hWnd, msg, wparam, lparam));

}//end WinProc


//-----------------------------------WinMain-----------------------------------------
//	Entry point for our windows application
//-----------------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE hinstance,
					          HINSTANCE hprevinstance,
					          LPSTR     lpcmdline,
					          int       ncmdshow)
{

	WNDCLASSEX winclass; 
	HWND	   hWnd;	 
	MSG		   msg;		
  
  //load in the parameters
  if (!g_Params.Initialize())
  {
    return 0;
  }

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
	winclass.hIconSm      = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));


	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		MessageBox(NULL, "Error Registering Class!", "Error", 0);
    return 0;
	}

	// create a window which cannot be resized
	if (!(hWnd = CreateWindowEx(NULL,									
								szWindowClassName,						
								szApplicationName,						
								WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
					 			GetSystemMetrics(SM_CXSCREEN)/2 - CParams::WindowWidth/2,
                GetSystemMetrics(SM_CYSCREEN)/2 - CParams::WindowHeight/2,									
                CParams::WindowWidth,
                CParams::WindowHeight,				
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
  CTimer timer(CParams::iFramesPerSecond);

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
        MessageBox(NULL, "Controller Update faulty", "Error!", NULL);

        bDone = true;
      }

			//this will call WM_PAINT which will render our scene
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
    }					
					
	}//end while
	

  UnregisterClass( szWindowClassName, winclass.hInstance );

  //delete the controller
  delete g_pController;
	
	return 0;

} 



