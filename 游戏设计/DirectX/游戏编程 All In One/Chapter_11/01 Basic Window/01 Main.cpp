 // '01 Main.cpp'
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
 kWndClass.lpszClassName = "01 Basic Window";

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
 hWindow = CreateWindow ("01 Basic Window", "01 Basic Window", 
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                         NULL, NULL, hInstance, NULL);
 ShowWindow (hWindow, nShowCmd);

  // "The Message Loop"
 MSG kMessage;
  // Enter the message loop and deal with all messages sent to our
  // window
 while (GetMessage (&kMessage, hWindow, 0, 0))
 {
  TranslateMessage (&kMessage);
  DispatchMessage (&kMessage);
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



