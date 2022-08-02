//#define WIN32_LEAN_AND_MEAN

#include <windows.h>   
#include <stdlib.h>
#include <time.h>

#include "CgaBob.h"
#include "defines.h"

using namespace std;



///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter3 - Pathfinder";
char*			szWindowClassName = "PFclass";

//pointer to the GA object
CgaBob*	g_pGABob;


//-----------------------------------WinProc------------------------------------------
//
//------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	//device context for our window
	HDC				hdc;	
	PAINTSTRUCT     ps;

	//these hold the dimensions of the client window area
	static int cxClient, cyClient;

	//used to create the back buffer
	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;
						  

	switch(msg)
	{	
    case WM_CREATE: 
		{
			//seed the random number generator
			srand((unsigned) time(NULL));

			//create the GA class
			g_pGABob = new CgaBob(CROSSOVER_RATE,
								            MUTATION_RATE,
							            	POP_SIZE,
								            CHROMO_LENGTH,
								            GENE_LENGTH);
			
			//get the size of the client window
			RECT rect;
			GetClientRect(hwnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;

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
				case VK_RETURN:
				{
					g_pGABob->Run(hwnd);

				}
					
				break;

				case VK_ESCAPE:
				{
					PostQuitMessage(0);
				}

				break;

				case VK_SPACE:
					{
						g_pGABob->Stop();
					}
					
					break;

				
			}//end switch
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

			hdc = BeginPaint(hwnd, &ps);
			
			//fill our backbuffer with white
			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);
			
			//render the map and best route
			g_pGABob->Render(cxClient, cyClient, hdcBackBuffer);
			
			//now blit backbuffer to front
			BitBlt(hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY);

			ReleaseDC(hwnd, hdc);
			
			EndPaint(hwnd, &ps);
		} 
			
		break;

		case WM_DESTROY: 
		{
			
			SelectObject(hdcBackBuffer, hOldBitmap);
			
			//clean up our backbuffer objects
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap);

			//delete our GA object
			delete g_pGABob;

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
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			    = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	  = WindowProc;
	winclass.cbClsExtra		  = 0;
	winclass.cbWndExtra		  = 0;
	winclass.hInstance		  = hinstance;
	winclass.hIcon			    = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		    = LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground	= NULL; 
	winclass.lpszMenuName	  = NULL;
	winclass.lpszClassName	= szWindowClassName;
	winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);


	// register the window class
	if (!RegisterClassEx(&winclass))
		return 0;

	// create the window
	if (!(hwnd = CreateWindowEx(NULL,									
								szWindowClassName,						
								szApplicationName,						
								WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					 			0,0,									
								WINDOW_WIDTH,WINDOW_HEIGHT,				
								NULL,									
								NULL,								
								hinstance,								
								NULL)))									
	return 0;

	ShowWindow(hwnd, ncmdshow);
	UpdateWindow(hwnd);

	//enter the message loop
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
		
    //if the user has started the run update the GA and display
    //accordingly
    if (g_pGABob->Started())
    {
	    //update the gun
      g_pGABob->Epoch();

	    //this will call WM_PAINT 
	    InvalidateRect(hwnd, NULL, TRUE);
		  UpdateWindow(hwnd);
    }
					
					
	}//end while
	

  UnregisterClass( szWindowClassName, winclass.hInstance );
 
             
  return 0;                                   
             

} // end WinMain



