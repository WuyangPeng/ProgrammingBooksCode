// Ex11_01.cpp   Native windows program to display text in a window
#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
  WPARAM wParam, LPARAM lParam);

// Listing OFWIN_1
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  WNDCLASSEX WindowClass;                        // Structure to hold our window's attributes

  static LPCTSTR szAppName { _T("OFWin") };      // Define window class name
  HWND hWnd;                                     // Window handle
  MSG msg;                                       // Windows message structure

  WindowClass.cbSize = sizeof(WNDCLASSEX);       // Set structure size

  // Redraw the window if the size changes
  WindowClass.style = CS_HREDRAW | CS_VREDRAW;

  // Define the message handling function
  WindowClass.lpfnWndProc = WindowProc;

  WindowClass.cbClsExtra = 0;                    // No extra bytes after the window class
  WindowClass.cbWndExtra = 0;                    // structure or the window instance

  WindowClass.hInstance = hInstance;             // Application instance handle

  // Set default application icon
  WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

  // Set window cursor to be the standard arrow
  WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

  // Set gray brush for background color
  WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));

  WindowClass.lpszMenuName = nullptr;            // No menu
  WindowClass.lpszClassName = szAppName;         // Set class name
  WindowClass.hIconSm = nullptr;                 // Default small icon

  // Now register our window class
  RegisterClassEx(&WindowClass);

  // Now we can create the window
  hWnd = CreateWindow(
    szAppName,                                   // the window class name
    _T("A Basic Window the Hard Way"),           // The window title
    WS_OVERLAPPEDWINDOW,                         // Window style as overlapped
    CW_USEDEFAULT,                               // Default screen position of upper left
    CW_USEDEFAULT,                               // corner of our window as x,y.
    CW_USEDEFAULT,                               // Default window size width ...
    CW_USEDEFAULT,                               // ... and height
    nullptr,                                     // No parent window
    nullptr,                                     // No menu
    hInstance,                                   // Program Instance handle
    nullptr                                      // No window creation data
    );

  ShowWindow(hWnd, nCmdShow);                    // Display the window
  UpdateWindow(hWnd);                            // Redraw window client area 

  // The message loop
  while (GetMessage(&msg, nullptr, 0, 0) == TRUE) // Get any messages
  {
    TranslateMessage(&msg);                      // Translate the message
    DispatchMessage(&msg);                       // Dispatch the message
  }

  return static_cast<int>(msg.wParam);           // End, so return to Windows
}

// Listing OFWIN_2
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
  WPARAM wParam, LPARAM lParam)
{

  switch (message)                               // Process selected messages
  {
  case WM_PAINT:                                 // Message is to redraw the window
    HDC hDC;
    PAINTSTRUCT PaintSt;                         // Structure defining area to be drawn
    hDC = BeginPaint(hWnd, &PaintSt) ;           // Prepare to draw the window

    // Get upper left and lower right of client area
    RECT aRect;                                  // A working rectangle
    GetClientRect(hWnd, &aRect);

    SetBkMode(hDC, TRANSPARENT);                 // Set text background mode

    // Now draw the text in the window client area
    DrawText(
      hDC,                                       // Device context handle
      _T("But, soft! What light through yonder window breaks?"),
      -1,                                        // Indicate null terminated string
      &aRect,                                    // Rectangle in which text is to be drawn
      DT_SINGLELINE |                            // Text format - single line
      DT_CENTER |                                //             - centered in the line
      DT_VCENTER);                               //             - line centered in aRect

    EndPaint(hWnd, &PaintSt);                    // Terminate window redraw operation
    return 0;

  case WM_DESTROY:                               // Window is being destroyed
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}
