//
// sketch.cpp
// Draws in the client area with the mouse.
// Draws with color selected from list of predefined colors.
// Pen widths also selected from a list of predefined pens.
// Copyright (c) William H. Murray and Chris H. Pappas, 2000
//

#include <windows.h>
#include "resource.h"

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK AboutDlgProc(HWND,UINT,WPARAM,LPARAM);

char szProgName[]="ProgName";        // app name
char szApplName[]="SketchMenu";      // menu name
char szCursorName[]="SketchCursor";  // cursor name
char szIconName[]="SketchIcon";      // icon name
static WORD wColor;					 // color from menu
BOOL bDrawtrail;                     // (t/f) draw?
POINT omouselocat,nmouselocat;       // position

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPreInst,
                   LPSTR lpszCmdLine,int nCmdShow)
{
  HWND hWnd;
  MSG  lpMsg;
  WNDCLASS wcApp;
  
  wcApp.lpszClassName=szProgName;
  wcApp.hInstance    =hInst;
  wcApp.lpfnWndProc  =WndProc;
  wcApp.hCursor      =LoadCursor(hInst,szCursorName);
  wcApp.hIcon        =LoadIcon(hInst,szIconName);
  wcApp.lpszMenuName =szApplName;
  wcApp.hbrBackground=(HBRUSH) GetStockObject(WHITE_BRUSH);
  wcApp.style        =CS_HREDRAW|CS_VREDRAW;
  wcApp.cbClsExtra   =0;
  wcApp.cbWndExtra   =0;
  if (!RegisterClass (&wcApp))
    return 0;
  
  hWnd=CreateWindow(szProgName,"Drawing with the Mouse",
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

// About dialog box control selection
BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT messg,
						   WPARAM wParam,LPARAM lParam)
{
  switch (messg) {
    case WM_INITDIALOG:
      break;
    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case IDOK:
          EndDialog(hDlg,0);
          break;
        default:
          return FALSE;
	  }
	  break;
    default:
      return FALSE;
  }
  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT messg,
                         WPARAM wParam,LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;
  HMENU hmenu;
  static HPEN hOPen,hNPen;
  static COLORREF tempcolor=RGB(0,0,0);
  static COLORREF wColorValue[12]={RGB(0,0,0),        //BLACK
                                   RGB(255,255,255),  //WHITE
                                   RGB(255,0,0),      //RED
                                   RGB(255,96,0),     //ORANGE
                                   RGB(255,255,0),    //YELLOW
                                   RGB(0,255,0),      //GREEN
                                   RGB(0,0,255),      //BLUE
                                   RGB(255,0,255),    //MAGENTA
                                   RGB(128,255,0),    //LT GREEN
                                   RGB(0,255,255),    //LT BLUE
                                   RGB(255,0,159),    //LT RED
                                   RGB(180,180,180)}; //LT GRAY
  static int penwidth=2;
  static POINT pt;

  switch (messg)
  {
    case WM_COMMAND:
      // menu item selections
      switch (LOWORD(wParam)) { 
        case ID_OPTIONS_CLEAR:
          tempcolor=wColorValue[1];
          InvalidateRect(hWnd,NULL,TRUE);
          break;
        case ID_OPTIONS_EXIT:
          SendMessage(hWnd,WM_CLOSE,0,0L);
          break;
        case ID_PEN_TWO:
          penwidth=2;
          break;
        case ID_PEN_FIVE:
          penwidth=5;
          break;
        case ID_PEN_TEN:
          penwidth=10;
          break;
        case ID_PEN_THIRTY:
          penwidth=30;
          break;
        case ID_PEN_SIXTY:
          penwidth=60;
          break;
        case ID_HELP_ABOUT:
          DialogBox((HINSTANCE) GetModuleHandle(NULL),
                   "AboutDlgBox",hWnd,
                   AboutDlgProc);
          break;
        case IDM_BLACK:
        case IDM_WHITE:
        case IDM_RED:
        case IDM_ORANGE:
        case IDM_YELLOW:
        case IDM_GREEN:
        case IDM_BLUE:
        case IDM_MAGENTA:
        case IDM_LTGREEN:
        case IDM_LTBLUE:
        case IDM_LTRED:
        case IDM_LTGRAY:
          hmenu=GetMenu(hWnd);
          CheckMenuItem(hmenu,wColor,MF_UNCHECKED);
          wColor=LOWORD(wParam);
          CheckMenuItem(hmenu,wColor,MF_CHECKED);
		  tempcolor=wColorValue[wColor-IDM_BLACK];
          break;
		default:
          break;
	  }
      break;

	case WM_LBUTTONDOWN:
      // draw when mouse button is down
      nmouselocat.x=LOWORD(lParam);
      nmouselocat.y=HIWORD(lParam);
      omouselocat=nmouselocat;
      SetCapture(hWnd);
      bDrawtrail=TRUE;
      break;

    case WM_MOUSEMOVE:
      // follow the mouse around
      if (bDrawtrail) {
        omouselocat=nmouselocat;
        nmouselocat.x=LOWORD(lParam);
        nmouselocat.y=HIWORD(lParam);
        InvalidateRect(hWnd,NULL,FALSE);
        UpdateWindow(hWnd);
	  }
      break;

    case WM_LBUTTONUP:
      // do not draw when mouse button is up
      ReleaseCapture();
      bDrawtrail=FALSE;
      break;

    case WM_PAINT:
      hdc=BeginPaint(hWnd,&ps);
      hNPen=CreatePen(PS_SOLID,penwidth,tempcolor);
      hOPen=(HPEN) SelectObject(hdc,hNPen);
      MoveToEx(hdc,omouselocat.x,omouselocat.y,NULL);
      LineTo(hdc,nmouselocat.x,nmouselocat.y);
      SelectObject(hdc,hOPen);
	  DeleteObject(hNPen);
      
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