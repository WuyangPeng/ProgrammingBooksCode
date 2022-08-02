/////////////////////////////////////////////////////////////////////////
//
//		File: main.h
//
//		Author: Mat Buckland
//
//		Desc: Code to solve the traveling salesman problem.
//
/////////////////////////////////////////////////////////////////////////

#include <windows.h>   
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>

#include "gaTSP.h"
#include "defines.h"
#include "resource.h"

using namespace std;


///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Chapter5 - Our Salesman Gets Smarter";
char*			szWindowClassName = "TSPclass";

char*			szMutationOperators[6] = {"Exchange Mutation",
										"Displacement Mutation",
										"Scramble Mutation",
										"Insertion Mutation",
										"Inversion Mutation",
										"Displaced Inversion Mutation"};

char*			szCrossoverOperators[4] = {"Partially Matched Crossover",
										 "Order Based Crossover",
										 "Order Crossover"
										 "Position Based Crossover"};

//pointer to our TSP object
CgaTSP* g_pTSP;


//-----------------------------------WinProc------------------------------------------
//
//------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, 
						                UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	//device context for our window
	HDC	            hdc;	
	PAINTSTRUCT     ps;

	//these hold the dimensions of the client window area
	static int cxClient, cyClient;

	//used to create the back buffer
	static HDC	  	hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;
	
  HMENU  hmenu = GetMenu(hwnd);
  
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

			//create a surface for us to render to(backbuffer)
			hdcBackBuffer = CreateCompatibleDC(NULL);

			HDC hdc = GetDC(hwnd);

			hBitmap = CreateCompatibleBitmap(hdc,
											 cxClient,
											 cyClient);

			ReleaseDC(hwnd, hdc);

			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

			//create our TSP class object
			//global instance of our TSP class
			g_pTSP = new CgaTSP(MUTATION_RATE,
							            CROSSOVER_RATE,
							            POP_SIZE,
							            NUM_CITIES,
							            IM,
							            PMX,
                          NONE,
                          TOURNAMENT,
							            WINDOW_WIDTH,
							            WINDOW_HEIGHT,
                          hwnd);

      CheckMenuRadioItem(hmenu, ID_SELECT_ROULETTE, ID_SELECT_SUS, ID_SELECT_TOURNAMENT, MF_BYCOMMAND);
      CheckMenuRadioItem(hmenu, ID_SCALE_NONE, ID_SCALE_BOLTZMANN, ID_SCALE_NONE, MF_BYCOMMAND);
      CheckMenuRadioItem(hmenu, ID_MUTATE_EM, ID_MUTATE_DM, ID_MUTATE_IM, MF_BYCOMMAND);
      CheckMenuRadioItem(hmenu, ID_ELITISM_ON, ID_ELITISM_OFF, ID_ELITISM_ON, MF_BYCOMMAND);
      CheckMenuRadioItem(hmenu, ID_CROSSOVER_PMX, ID_CROSSOVER_PBX, ID_CROSSOVER_PMX, MF_BYCOMMAND);

		} 
			
		break;
		//check key press messages
		case WM_KEYUP:
		{
			switch(wparam)
			{
				case VK_RETURN:
				{
					g_pTSP->Run(hwnd);

				}
					
				break;

				case VK_ESCAPE:
				{

					PostQuitMessage(0);
				}

				break;

				case VK_SPACE:
					{
            g_pTSP->Stop();					
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

			//create the city coordinates based on the area of the 
			//client window
		
			g_pTSP->Resize(cxClient, cyClient);

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

			//this is where we do all our drawing to screen. CgaTSP::Run() 
			//calls InvalidateRect & UpdateWindow each generation.

			hdc = BeginPaint(hwnd, &ps);

      //fill our backbuffer with white
	    BitBlt(hdcBackBuffer,
             0, 0,
             cxClient,
             cyClient,
             NULL,
             NULL,
             NULL,
             WHITENESS);
			
      g_pTSP->Render(hdcBackBuffer, cxClient, cyClient);

      	//now blit backbuffer to front
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

			ReleaseDC(hwnd, hdc);
			
			EndPaint(hwnd, &ps);
		} 
			
		break;

    case WM_COMMAND:
    {
       switch(wparam)
       {
       case ID_SELECT_ROULETTE:
         {
           g_pTSP->SetSelectionMethod(ROULETTE);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SELECT_ROULETTE, ID_SELECT_SUS, ID_SELECT_ROULETTE, MF_BYCOMMAND);


         }

         break;

       case ID_SELECT_TOURNAMENT:
         {
           g_pTSP->SetSelectionMethod(TOURNAMENT);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SELECT_ROULETTE, ID_SELECT_SUS, ID_SELECT_TOURNAMENT, MF_BYCOMMAND);
         }

         break;

       case ID_SELECT_ALTTOURNAMENT:
         {
           g_pTSP->SetSelectionMethod(ALT_TOURNAMENT);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SELECT_ROULETTE, ID_SELECT_SUS, ID_SELECT_ALTTOURNAMENT, MF_BYCOMMAND);
         }

         break;

       case ID_SELECT_SUS:
         {
           g_pTSP->SetSelectionMethod(SUS);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SELECT_ROULETTE, ID_SELECT_SUS, ID_SELECT_SUS, MF_BYCOMMAND);
         }

         break;
           
       case ID_SCALE_RANK:
         {
           g_pTSP->SetScalingMethod(RANK);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SCALE_NONE, ID_SCALE_BOLTZMANN, ID_SCALE_RANK, MF_BYCOMMAND);
         }

         break;

       case ID_SCALE_NONE:
         {
            g_pTSP->SetScalingMethod(NONE);
            InvalidateRect(hwnd, NULL, TRUE);
		        UpdateWindow(hwnd);

            CheckMenuRadioItem(hmenu, ID_SCALE_NONE, ID_SCALE_BOLTZMANN, ID_SCALE_NONE, MF_BYCOMMAND);
         }

         break;

       case ID_SCALE_SIGMA:
         {
           g_pTSP->SetScalingMethod(SIGMA);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SCALE_NONE, ID_SCALE_BOLTZMANN, ID_SCALE_SIGMA, MF_BYCOMMAND);
         }

         break;

       case ID_SCALE_BOLTZMANN:
         {
           g_pTSP->SetScalingMethod(BOLTZMANN);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_SCALE_NONE, ID_SCALE_BOLTZMANN, ID_SCALE_BOLTZMANN, MF_BYCOMMAND);
         }

         break;

       case ID_MUTATE_DM:
         {
           g_pTSP->SetMutation(DM);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_MUTATE_EM, ID_MUTATE_DM, ID_MUTATE_DM, MF_BYCOMMAND);
         }

         break;
 

       case ID_MUTATE_SM:
         {
           g_pTSP->SetMutation(SM);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_MUTATE_EM, ID_MUTATE_DM, ID_MUTATE_SM, MF_BYCOMMAND);
         }

         break;

       case ID_MUTATE_EM:
         {
           g_pTSP->SetMutation(EM);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_MUTATE_EM, ID_MUTATE_DM, ID_MUTATE_EM, MF_BYCOMMAND);
         }

         break;
         
       case ID_MUTATE_IM:
         {
           g_pTSP->SetMutation(IM);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_MUTATE_EM, ID_MUTATE_DM, ID_MUTATE_IM, MF_BYCOMMAND);
         }

         break;

       case ID_CROSSOVER_PMX:
         {
           g_pTSP->SetCrossover(PMX);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);
           
           CheckMenuRadioItem(hmenu, ID_CROSSOVER_PMX, ID_CROSSOVER_PBX, ID_CROSSOVER_PMX, MF_BYCOMMAND);
         }

         break;

        case ID_CROSSOVER_OBX:
         {
           g_pTSP->SetCrossover(OBX);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_CROSSOVER_PMX, ID_CROSSOVER_PBX, ID_CROSSOVER_OBX, MF_BYCOMMAND);
         }

         break;

        case ID_CROSSOVER_PBX:
         {
           g_pTSP->SetCrossover(PBX);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_CROSSOVER_PMX, ID_CROSSOVER_PBX, ID_CROSSOVER_PBX, MF_BYCOMMAND);
         }

         break;

        case ID_ELITISM_ON:
         {
           g_pTSP->SetElitism(true);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_ELITISM_ON, ID_ELITISM_OFF, ID_ELITISM_ON, MF_BYCOMMAND);
         }

         break;

        case ID_ELITISM_OFF:
         {
           g_pTSP->SetElitism(false);
           InvalidateRect(hwnd, NULL, TRUE);
		       UpdateWindow(hwnd);

           CheckMenuRadioItem(hmenu, ID_ELITISM_ON, ID_ELITISM_OFF, ID_ELITISM_OFF, MF_BYCOMMAND);
         }

         break;
       }// end switch WM_COMMAND
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
	winclass.hbrBackground	= NULL; //(HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName	  = MAKEINTRESOURCE(IDR_MENU1);
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
					 			GetSystemMetrics(SM_CXSCREEN)/2 - WINDOW_WIDTH/2,
                GetSystemMetrics(SM_CYSCREEN)/2 - WINDOW_HEIGHT/2,								
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
    if (g_pTSP->Started())
    {
	    //update the gun
      g_pTSP->Epoch();

	    //this will call WM_PAINT 
	    InvalidateRect(hwnd, NULL, TRUE);
		  UpdateWindow(hwnd);
    }
					
					
	}//end while
	

  UnregisterClass( szWindowClassName, winclass.hInstance );
 
  //delete our GA instance
  if (g_pTSP)
  {
    delete g_pTSP;
  }
             
  return 0;

} // end WinMain



