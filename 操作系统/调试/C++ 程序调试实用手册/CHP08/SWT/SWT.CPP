//
// swt.cpp
// Simple Windows Template
// Copyright (c) William H. Murray and Chris H. Pappas, 2000
//

#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

char szProgName[]="ProgName";

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPreInst,
                   LPSTR lpszCmdLine,int nCmdShow)
{
  HWND hWnd;
  MSG  lpMsg;
  WNDCLASS wcApp;
  
  wcApp.lpszClassName=szProgName;
  wcApp.hInstance    =hInst;
  wcApp.lpfnWndProc  =WndProc;
  wcApp.hCursor      =LoadCursor(NULL,IDC_ARROW);
  wcApp.hIcon        =0;
  wcApp.lpszMenuName =0;
  wcApp.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
  wcApp.style        =CS_HREDRAW|CS_VREDRAW;
  wcApp.cbClsExtra   =0;
  wcApp.cbWndExtra   =0;
  if (!RegisterClass (&wcApp))
    return 0;
  
  hWnd=CreateWindow(szProgName,"Simple Windows Template",
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,
                    CW_USEDEFAULT,CW_USEDEFAULT,
                    CW_USEDEFAULT,(HWND)NULL,(HMENU)NULL,
                    hInst,(LPSTR)NULL);
  ShowWindow(hWnd,nCmdShow);
  UpdateWindow(hWnd);
  while (GetMessage(&lpMsg,0,0,0)) {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return(lpMsg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd,UINT messg,
                         WPARAM wParam,LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
 
  switch (messg)
  {
    case WM_PAINT:
      hdc=BeginPaint(hWnd,&ps);

      MoveToEx(hdc,45,55,NULL);
      LineTo(hdc,480,410);

      TextOut(hdc,200,100,"A simple line",13);

      ValidateRect(hWnd,NULL);
      EndPaint(hWnd,&ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return(DefWindowProc(hWnd,messg,wParam,lParam));
      break;
  }
  return(0);
}
