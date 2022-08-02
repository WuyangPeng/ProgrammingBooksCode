//
// Saucer.cpp
// A procedure-oriented Windows Application
// that demonstrates simple animation techniques
// with a bitmapped images.
// Copyright (c) William H. Murray and Chris H. Pappas, 2000
//

#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

char szProgName[]="ProgName";
char szIconName[]="SaucerIcon";
char szBMName[]="BMImage";

HBITMAP hBitmap;
int iTimer,xPos,yPos;
int xPosInit,yPosInit,xStep,yStep;

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
  wcApp.hIcon        =LoadIcon(hInst,szIconName);
  wcApp.lpszMenuName =0;
  wcApp.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
  wcApp.style        =CS_HREDRAW|CS_VREDRAW;
  wcApp.cbClsExtra   =0;
  wcApp.cbWndExtra   =0;
  if (!RegisterClass (&wcApp))
    return 0;
  
  hWnd=CreateWindow(szProgName,"Flying Saucer Program",
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,
                    CW_USEDEFAULT,CW_USEDEFAULT,
                    CW_USEDEFAULT,(HWND)NULL,(HMENU)NULL,
                    hInst,(LPSTR)NULL);
  ShowWindow(hWnd,nCmdShow);
  UpdateWindow(hWnd);
  
  // load saucer bitmap
  hBitmap=LoadBitmap(hInst,szBMName);

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
  HDC hmdc;
  RECT rcWnd;
  static BITMAP bm;

  switch (messg)
  {
    case WM_CREATE:
      // initial values
      xPosInit=200;
      yPosInit=200;
      xStep=2;
      yStep=2;
      xPos=xPosInit;
      yPos=yPosInit;
      iTimer=SetTimer(hWnd,1,10,NULL);
      break;

    case WM_TIMER:
      // with each timer tick, draw image
      hdc=GetDC(hWnd);
      GetClientRect(hWnd,&rcWnd);
      hmdc=CreateCompatibleDC(hdc);
      xPos+=xStep;
      yPos+=yStep;

      // draw image 
      SelectObject(hmdc,hBitmap);
      GetObject(hBitmap,sizeof(bm),(LPSTR) &bm);
      BitBlt(hdc,xPos,yPos,bm.bmWidth,bm.bmHeight,
             hmdc,0,0,SRCCOPY);

      // check left and right window edges
      if((xPos+bm.bmWidth > rcWnd.right) ||
         (xPos < rcWnd.left)) {
        xStep=-xStep;
      }

      // check top and bottom window edges
      if((yPos+bm.bmHeight > rcWnd.bottom) ||
         (yPos < rcWnd.top)) {
        yStep=-yStep;
      }

      ReleaseDC(hWnd,hdc);
      DeleteDC(hmdc);
      break;

    case WM_DESTROY:
      if (hBitmap) DeleteObject(hBitmap);
      if(iTimer) KillTimer(hWnd,1);
      PostQuitMessage(0);
      break;

	default:
      return(DefWindowProc(hWnd,messg,wParam,lParam));
      break;
  }
  return(0);
}