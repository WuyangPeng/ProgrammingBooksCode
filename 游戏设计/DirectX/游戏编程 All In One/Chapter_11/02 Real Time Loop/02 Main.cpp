 // '02 Main.cpp'
#include <windows.h>

 // Message handler prototype
LRESULT CALLBACK WndProc (HWND hWindow, UINT iMessage, 
                          WPARAM wParam, LPARAM lParam);

 // "WinMain Vs. main"
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  // "The Window Class"
 WNDCLASS	kWndClass;
	
  // 'Visual' proprieties
 kWndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
 kWndClass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
 kWndClass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);

  // System proprieties
 kWndClass.hInstance     = hInstance;
 kWndClass.lpfnWndProc   = WndProc;
 kWndClass.lpszClassName = "02 Real time message loop";

  // Extra proprieties
 kWndClass.lpszMenuName  = NULL;

 kWndClass.cbClsExtra = NULL;
 kWndClass.cbWndExtra = NULL;
 kWndClass.style      = NULL;

  // Try to register class
 if (!RegisterClass (&kWndClass))
 {
  return -1;
 }

  // "The Window"
 HWND hWindow;
  // Create the window
 hWindow = CreateWindow ("02 Real time message loop", 
                         "02 Real time message loop", 
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                         NULL, NULL, hInstance, NULL);
 ShowWindow (hWindow, nShowCmd);

  // "The Message Loop"
 MSG kMessage;
  // Enter the real time message loop
 while (1)
 {
   // Query to see if there is any message in the queue
  if (PeekMessage (&kMessage, hWindow, 0, 0, PM_REMOVE))
  {
   // If it is the WM_QUIT message, quit the loop
   if (WM_QUIT == kMessage.message)
   {
    break;
   }
   // Process the message normally
	 else
	 {
	  TranslateMessage (&kMessage);
	  DispatchMessage (&kMessage);
	 }
  }
  // No message, do whatever we want
  else
  {
   // Do idle ...
  }
}

return 0L;
}

// "The Message Handler"
LRESULT CALLBACK WndProc (HWND hWindow, UINT iMessage, 
                          WPARAM wParam, LPARAM lParam)
{
 switch (iMessage)
 {
 // Close window
 case WM_CLOSE:
  PostQuitMessage (0);
 break;

 default:
  return DefWindowProc (hWindow, iMessage, wParam, lParam);
 }
 return 0;
}

 

