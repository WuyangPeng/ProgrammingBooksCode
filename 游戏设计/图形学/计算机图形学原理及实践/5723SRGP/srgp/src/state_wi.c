/*
	srgp_state_Win.c
	MS Windows version of state.c

*/

#include "srgplocal.h"
#include "srgp_win.h"
#include <string.h>
#include <dos.h>

char *szAppName = "SRGP";


HANDLE srgp__colorlist;
int	   srgp__nCmdShow;

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
				   LPSTR lpszCmdLine, int nCmdShow)
{
	int			i, j, start;
	char		*argstr;
	WNDCLASS	wndClass;

	if (!hPrevInstance)
	{
		wndClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wndClass.lpfnWndProc    = WndProc;
		wndClass.cbClsExtra		= 0;
		wndClass.cbWndExtra		= 0;
		wndClass.hInstance		= hInstance;
		wndClass.hIcon			= LoadIcon (hInstance, "srgp");
		wndClass.hCursor		= NULL;
		wndClass.hbrBackground	= GetStockObject (WHITE_BRUSH);
		wndClass.lpszMenuName	= NULL;
		wndClass.lpszClassName  = szAppName;

		if (!RegisterClass(&wndClass))
			return FALSE;
	}

	srgp__hInstance = hInstance;
	srgp__nCmdShow = nCmdShow;

	srgp__colorlist = LoadResource(hInstance,
					  FindResource(hInstance, "colorlist", "TEXT"));

	SRGP__memInit();

	UserMain(_argc,_argv);

	SRGP__memFree();

	return 0;
}


void SRGP__initGraphicsDevice (char *name, int requested_planes,
							   boolean debugasap)
{
	HWND hWnd;
	int width, height;
	RECT 	clientRect;
	RECT    winRect;
	HDC		hdc;

	/* Create and display the window */
	hWnd = CreateWindow(szAppName, name,
						(WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX |
						 WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU),
						 CW_USEDEFAULT, CW_USEDEFAULT,
						 srgp__curActiveCanvasSpec.max_xcoord + 1,
						 srgp__curActiveCanvasSpec.max_ycoord + 1,
						 NULL, NULL, srgp__hInstance, NULL);
	srgp__curActiveCanvasSpec.drawable.win = hWnd;
	srgp__canvasTable[0] = srgp__curActiveCanvasSpec;

	GetWindowRect(hWnd, &winRect);
	GetClientRect(hWnd, &clientRect);
	width = srgp__curActiveCanvasSpec.max_xcoord + 1 +
			(winRect.right - winRect.left) -
			(clientRect.right - clientRect.left);
	height = srgp__curActiveCanvasSpec.max_ycoord + 1 +
			 (winRect.bottom - winRect.top) -
			 (clientRect.bottom - clientRect.top);

	SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE);

	hdc = GetDC(hWnd);
	SelectObject (hdc, GetStockObject (NULL_BRUSH));
	SetBkMode (hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_BASELINE);

	SRGP__initColor (requested_planes);

	ReleaseDC (hWnd, hdc);

	UpdateWindow (hWnd);
	ShowWindow (hWnd, srgp__nCmdShow);

	srgp__canvasTable[0] = srgp__curActiveCanvasSpec;
}

/** SRGP_refresh
**/
void SRGP_refresh()
{
/* only needed on X11 workstations */
}

/** SRGP_enableSynchronous
No-op for Windows version.
**/
void SRGP_enableSynchronous()
{
}

/** SRGP_allowResize
No-op for Windows version.
**/
void SRGP_allowResize(boolean allow)
{
}

void SRGP__forceScreenResize (int newwidth, int newheight)
{
	RECT 	clientRect;
	RECT    winRect;
	int width, height;

	GetWindowRect(srgp__canvasTable[0].drawable.win, &winRect);
	GetClientRect(srgp__canvasTable[0].drawable.win, &clientRect);
	width = newwidth +
			(winRect.right - winRect.left) -
			(clientRect.right - clientRect.left);
	height = newheight +
			 (winRect.bottom - winRect.top) -
			 (clientRect.bottom - clientRect.top);

	SetWindowPos(srgp__canvasTable[0].drawable.win, NULL, 0, 0,
				 width, height, SWP_NOMOVE);

}

int SRGP_inquireWinInstance(void)
{
	return srgp__hInstance;
}