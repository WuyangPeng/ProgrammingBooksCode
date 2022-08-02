//-----------------------------------------------------------------------
//  
//  Name: Resources_Dialog_Box
//  
//  Author: Mat Buckland 2002
//
//  Desc: Code to demonstrate the creation of a simple 'About' dialogue
//        boxe.
//
//  NOTE: Don't forget to include the library winmm.lib in your project
//        settings and to #include the resource.h file
//------------------------------------------------------------------------

#include <windows.h>

#include "defines.h"
#include "resource.h"



//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Resources - Dialog Box";
char*	g_szWindowClassName = "MyWindowClass";

//--------------------------------- DialogProc ---------------------------
//
//------------------------------------------------------------------------
BOOL CALLBACK DialogProc(HWND   hwnd,
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

//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
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
         
         PlaySound("window_open.wav", NULL, SND_FILENAME | SND_ASYNC);
			 }

       break;

    case WM_KEYUP:
      {
        switch(wParam)
        {
        case VK_ESCAPE:
          {
            //if the escape key has been pressed exit the program
            PostQuitMessage(0);
          }
        }
      }
    
		case WM_PAINT:
			 {
 				  PAINTSTRUCT ps;
          
          BeginPaint (hwnd, &ps);

				   //**this is where we do any drawing to the screen**
     
          EndPaint (hwnd, &ps);
			 }

       break;
          
		 case WM_DESTROY:
			 {
				  // kill the application, this sends a WM_QUIT message  
				  PostQuitMessage (0);
			 }

       break;

     case WM_COMMAND:
       {
         switch(wParam)
         {
         case IDSAVE:
           {
             //do your saving here
           }

           break;

         case IDLOAD:
           {
             //do your loading here
           }

           break;
           
         case IDSOUND1:
           {
             PlaySound("wav1.wav", NULL, SND_FILENAME | SND_ASYNC);
           }

           break;

         case IDSOUND2:
           {
              PlaySound("wav2.wav", NULL, SND_FILENAME | SND_ASYNC);
           }

           break;

         case IDABOUT:
           {
             DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DialogProc);
           }
           break;

         }// end switch WM_COMMAND
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


