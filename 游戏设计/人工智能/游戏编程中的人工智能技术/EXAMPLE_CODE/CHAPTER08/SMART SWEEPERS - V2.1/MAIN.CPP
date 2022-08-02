#include <windows.h>   
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "CController.h"
#include "CTimer.h"
#include "resource.h"
#include "CParams.h"



///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter8 - Obstacle Avoidance v2.1";
char*			szWindowClassName = "sweeper";


//The controller class for this simulation
CController*	g_pController	 = NULL; 

CParams   g_Params;

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
LRESULT CALLBACK WindowProc(HWND   hwnd, 
						                UINT   msg, 
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
			GetClientRect(hwnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;

			//setup the controller
			g_pController = new CController(hwnd);

				//create a surface for us to render to(backbuffer)
			hdcBackBuffer = CreateCompatibleDC(NULL);

			HDC hdc = GetDC(hwnd);

			hBitmap = CreateCompatibleBitmap(hdc,
											                cxClient,
											                cyClient);
			ReleaseDC(hwnd, hdc);

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

				case 'F':
					{
						g_pController->FastRenderToggle();
					}
					
					break;
          
        case 'R':
          {
             if (g_pController)
             {
               delete g_pController;
             }

             //setup the new controller
			       g_pController = new CController(hwnd);
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
			
			//render the mines and sweepers
			g_pController->Render(hdcBackBuffer);
			
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

      // kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);
 		} 
			
		break;

		default:break;

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
	winclass.hIcon			  = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
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

	// create the window (one that cannot be resized)
	if (!(hwnd = CreateWindowEx(NULL,									
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
	ShowWindow(hwnd, SW_SHOWDEFAULT );
	UpdateWindow(hwnd);

	//create a timer
	CTimer timer(CParams::iFramesPerSecond);

	//start the timer
	timer.Start();

	// Enter the message loop
	bool bDone = FALSE;

	while(!bDone)
	{
					
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
		{
			if( msg.message == WM_QUIT ) 
			{
				// Stop loop if it's a quit message
				bDone = TRUE;
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
				bDone = TRUE;
			}

			//this will call WM_PAINT which will render our scene
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
    }					
					
	}//end while
	

    // Clean up everything and exit the app
    Cleanup();
    UnregisterClass( szWindowClassName, winclass.hInstance );
	
	return 0;

} // end WinMain



