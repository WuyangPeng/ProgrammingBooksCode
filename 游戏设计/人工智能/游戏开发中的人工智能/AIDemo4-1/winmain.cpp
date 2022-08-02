//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Flocking, Chapter 4
*/
//---------------------------------------------------------------------------

// Windows Header Files:
#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>

// Local Header Files:
#include "resource.h"
#include "winmain.h"


// Defines:
#define	APPNAME	"AI Ch2 Demo"

// Forward declarations for non-window related functions
void	DrawLineToDC(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void	DrawRectangleToDC(HDC hdc, RECT *r, int thk, COLORREF borderCLR, COLORREF fillCLR);
void	DrawEllipseToDC(HDC hdc, RECT *r, int thk, COLORREF clr);
void	DrawStringToDC(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);
void	CreateBackBuffer(void);
void	DeleteBackBuffer(void);



// Forward declarations for window related functions
LRESULT CALLBACK DemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



// Window related global variables
HINSTANCE		hinst; 
HWND			hMainWindow;
RECT			MainWindowRect;
HDC				BackBufferDC;
HBITMAP			hBackBuffer;
LPBITMAPINFO	lpBackBufferBitmapInfo;
bool			Initialized = false;
int				nShowCmd;

/*HINSTANCE	hInst; // current instance
int			nShowCmd; // current show command	
char		szAppName[] = APPNAME; // The name of this application
char		szTitle[]   = APPNAME; // The title bar text
HWND		hTheMainWindow;
*/

// globals

bool	ShowTrails;
bool	ShowVectors;

int		TargetX;
int		TargetY;

bool	WideView;
bool	LimitedView;
bool	NarrowView;
bool	Chase;



// Forward declarations for non-window related functions
void	InitializeVariables(void);
void	DrawTopView(HDC hdc, RECT *r);
void	DrawLine(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void	DrawRectangle(HDC hdc, RECT *r, int thk, COLORREF clr);
void	DrawString(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);

extern	void UpdateSimulation(void);
extern	bool Initialize(void);

//----------------------------------------------------------------------------------------------------//
// This is the applications "main" function. Note that I'm not using a message loop here
// since there is no main window. All I do is display a dialog box immediately upon startup
// and let the dialog handler take care of the messages.
//----------------------------------------------------------------------------------------------------//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//----------------------------------------------------------------------------------------------------//
{	

	MSG msg;
	HANDLE hAccelTable;		

	if (!hPrevInstance) {
		// Perform instance initialization:
		if (!InitApplication(hInstance)) {
			return (FALSE);
		}
	}

	// Perform application initialization:	
	if (!InitInstance(hInstance, nCmdShow)) {
		return (FALSE);
	}

	hAccelTable = LoadAccelerators (hInstance, APPNAME);

	// Main message loop:
	while (1) {		

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		
		if(Initialized)
			UpdateSimulation();

	}

	return (msg.wParam);

	lpCmdLine; // This will prevent 'unused formal parameter' warnings



}


BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;
    HWND      hwnd;

    hwnd = FindWindow (APPNAME, NULL);
    if (hwnd) {
        if (IsIconic(hwnd)) {
            ShowWindow(hwnd, SW_RESTORE);
        }
        SetForegroundWindow (hwnd);

        return FALSE;
        }

        wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc   = (WNDPROC)WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = NULL;//LoadIcon (hInstance, MAKEINTRESOURCE(IDI_MAINICON));
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);//NULL
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//(HBRUSH)(COLOR_WINDOW+1);

		wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
		
		wc.lpszClassName = APPNAME;
        
		return RegisterClass(&wc);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{			
	hinst = hInstance;
	nShowCmd = nCmdShow;	

	MainWindowRect.left = 0;
	MainWindowRect.top = 0;
	MainWindowRect.right = _WINWIDTH;
	MainWindowRect.bottom = _WINHEIGHT;
 
	hMainWindow = CreateWindow(	APPNAME, 
								APPNAME,
								WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
								0, 0, _WINWIDTH, _WINHEIGHT,
								NULL, NULL, hinst, NULL);
			
	// create back buffer
	CreateBackBuffer();

	ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

	Initialized = Initialize();

	return (TRUE);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	int			wmId, wmEvent;   		
	BOOL		validmenu = FALSE;	
	int			selection =0;
	PAINTSTRUCT			ps;
	HDC			pDC;
	WPARAM		key;
	int			w, h;
	UINT		state;
	
	switch (message) {

		case WM_CREATE:
			ShowTrails = false;
			ShowVectors = false;
			WideView = false;
			LimitedView = false;
			NarrowView = false;
			Chase = false;			
			break;

		case WM_ACTIVATE:
			state = ShowTrails ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWTRAILS, state);
			
			state = ShowVectors ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWVECTORS, state);

			state = WideView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_WIDEFIELDOFVIEW, state);

			state = LimitedView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_LIMITEDFIELDOFVIEW, state);
			
			state = NarrowView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_NARROWFIELDOFVIEW, state);
			
			state = Chase ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_CHASEMOUSE, state);
			
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			
			switch(wmId) {

				case ID_CLOSEMENU:
					DeleteBackBuffer();
					PostQuitMessage(0);
					break;

				case ID_OPTIONS_SHOWTRAILS:
					ShowTrails = !ShowTrails;
					state = ShowTrails ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWTRAILS, state);
					break;

				case ID_OPTIONS_SHOWVECTORS:
					ShowVectors = !ShowVectors;
					state = ShowVectors ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWVECTORS, state);					
					break;

				case ID_OPTIONS_WIDEFIELDOFVIEW:
					WideView = !WideView;
					state = WideView ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_WIDEFIELDOFVIEW, state);

					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_LIMITEDFIELDOFVIEW, MF_UNCHECKED);
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_NARROWFIELDOFVIEW, MF_UNCHECKED);
					LimitedView = false;
					NarrowView = false;

					break;

				case ID_OPTIONS_LIMITEDFIELDOFVIEW:
					LimitedView = !LimitedView;
					state = LimitedView ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_LIMITEDFIELDOFVIEW, state);
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_WIDEFIELDOFVIEW, MF_UNCHECKED);
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_NARROWFIELDOFVIEW, MF_UNCHECKED);
					WideView = false;
					NarrowView = false;

					break;

				case ID_OPTIONS_NARROWFIELDOFVIEW:
					NarrowView = !NarrowView;
					state = NarrowView ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_NARROWFIELDOFVIEW, state);
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_LIMITEDFIELDOFVIEW, MF_UNCHECKED);
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_WIDEFIELDOFVIEW, MF_UNCHECKED);
					LimitedView = false;
					WideView = false;

					break;

				case ID_OPTIONS_CHASEMOUSE:
					Chase = !Chase;
					state = Chase ? MF_CHECKED:MF_UNCHECKED;
					CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_CHASEMOUSE, state);

					break;
			}
			break;

		case	WM_MOUSEMOVE:
			TargetX = LOWORD(lParam);
			TargetY = HIWORD(lParam); 
			break;


		case WM_DESTROY:
			DeleteBackBuffer();
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:

			break;

		case WM_PAINT:			
				pDC = BeginPaint(hMainWindow, (LPPAINTSTRUCT) &ps);

				w = MainWindowRect.right - MainWindowRect.left;
				h = MainWindowRect.bottom - MainWindowRect.top;
				BitBlt(pDC, 0, 0, w, h, BackBufferDC, 0, 0, SRCCOPY);

				EndPaint(hMainWindow, (LPPAINTSTRUCT) &ps);				
				return (0);
			break;
        
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

void	CopyBackBufferToWindow(void)
{
	int	w, h;
	HDC	dc;
	
	dc = GetDC(hMainWindow);

	w = MainWindowRect.right - MainWindowRect.left;
	h = MainWindowRect.bottom - MainWindowRect.top;
	BitBlt(dc, 0, 0, w, h, BackBufferDC, 0, 0, SRCCOPY);

	DeleteDC(dc);

}

void	ClearBackBuffer(void)
{
	DrawRectangle(&MainWindowRect, 1, RGB(0,0,0), RGB(255, 255, 255));
}

void CreateBackBuffer(void)
{
		HDC				hdc = GetDC(hMainWindow);		
		BYTE			*lpbits = NULL; 
		DWORD			retval = 0;
		

		BackBufferDC = CreateCompatibleDC(hdc);
          
		lpBackBufferBitmapInfo =  (LPBITMAPINFO) malloc(sizeof(BITMAPINFOHEADER));
	
		lpBackBufferBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		lpBackBufferBitmapInfo->bmiHeader.biWidth = MainWindowRect.right - MainWindowRect.left;
		lpBackBufferBitmapInfo->bmiHeader.biHeight = MainWindowRect.bottom - MainWindowRect.top;
		lpBackBufferBitmapInfo->bmiHeader.biPlanes = 1;
		lpBackBufferBitmapInfo->bmiHeader.biBitCount = 24;
		lpBackBufferBitmapInfo->bmiHeader.biCompression = BI_RGB;
		lpBackBufferBitmapInfo->bmiHeader.biSizeImage = 0;
		lpBackBufferBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
		lpBackBufferBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
		lpBackBufferBitmapInfo->bmiHeader.biClrUsed = 0;
		lpBackBufferBitmapInfo->bmiHeader.biClrImportant = 0;
   		
		hBackBuffer = CreateDIBSection(BackBufferDC, lpBackBufferBitmapInfo, DIB_RGB_COLORS, (void **) &lpbits, NULL, 0);

		SelectObject(BackBufferDC, (HBITMAP) hBackBuffer);

		DrawRectangleToDC(BackBufferDC, &MainWindowRect, 4, RGB(0, 0, 0), RGB(255, 255, 255));
}

void DeleteBackBuffer(void)
{
		DeleteDC(BackBufferDC);
		DeleteObject(hBackBuffer);
		free(lpBackBufferBitmapInfo);
}

//----------------------------------------------------------------------------------------------------//
// This function simply draws a solid line to the given device context, given the line
// start and end point, its thickness and its color.
//----------------------------------------------------------------------------------------------------//
void DrawLineToDC(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr)
//----------------------------------------------------------------------------------------------------//
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;	
	COLORREF	FColor = clr;
	COLORREF	BColor = RGB(0, 0, 0);
				
	CurrentBrush = CreateSolidBrush(FColor);
	OldBrush = (HBRUSH) SelectObject( hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN) SelectObject(hdc, CurrentPen);

	MoveToEx(hdc, h1, v1, NULL);
	LineTo(hdc, h2, v2);
 
 	SelectObject(hdc, OldBrush);		
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen); 
}

//----------------------------------------------------------------------------------------------------//
// This function simply draws a filled rectangle to the given device context, given the
// rectangle dimensions, its border thickness and its border color (the rectangle is filled
// in black).
//----------------------------------------------------------------------------------------------------//
void DrawRectangleToDC(HDC hdc, RECT *r, int thk, COLORREF borderCLR, COLORREF fillCLR)
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;	
	COLORREF	FColor = borderCLR;
	COLORREF	BColor = fillCLR;
				
	CurrentBrush = CreateSolidBrush(BColor);
	OldBrush = (HBRUSH) SelectObject( hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN) SelectObject(hdc, CurrentPen);

	Rectangle(hdc, r->left, r->top, r->right, r->bottom);
 
 	SelectObject(hdc, OldBrush);		
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen); 
}

//----------------------------------------------------------------------------------------------------//
// This function simply draws a filled rectangle to the given device context, given the
// rectangle dimensions, its border thickness and its border color (the rectangle is filled
// in black).
//----------------------------------------------------------------------------------------------------//
void DrawEllipseToDC(HDC hdc, RECT *r, int thk, COLORREF clr)
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;	
	COLORREF	FColor = clr;
	COLORREF	BColor = RGB(0, 0, 0);
				
	CurrentBrush = CreateSolidBrush(BColor);
	OldBrush = (HBRUSH) SelectObject( hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN) SelectObject(hdc, CurrentPen);

	Ellipse(hdc, r->left, r->top, r->right, r->bottom);
 
 	SelectObject(hdc, OldBrush);		
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen); 
}


//----------------------------------------------------------------------------------------------------//
// This function simply draws text to the given device context, given the text string
// and the x,y coordinates of its lower left corner, the number of characters in the string,
// and the desired point size.
//----------------------------------------------------------------------------------------------------//
void DrawStringToDC(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz)
{
	COLORREF	FColor = RGB(255, 255, 255);
	COLORREF	BColor = RGB(0, 0, 0);
	HFONT		hFont, hOldFont;

	SetTextColor(hdc, FColor);	
	SetBkColor(hdc, BColor);
	SetBkMode(hdc, TRANSPARENT);		
	SetTextAlign(hdc, TA_BOTTOM|TA_LEFT);
    
	hFont = CreateFont(-ptsz, 0, 0, 0, 0, 
    		0, 0, 0, 0, 0, 0, 0, 0, "MS Serif");
	hOldFont = (HFONT) SelectObject(hdc, hFont);
		
	TextOut(hdc, x, y, lpszString, size);    
    
	SelectObject(hdc, hOldFont); 
	DeleteObject(hFont); 
}

//----------------------------------------------------------------------------------------------------//
// All of these function draw to the back buffer...
//----------------------------------------------------------------------------------------------------//

void	DrawLine(int x1, int y1, int x2, int y2, int thk, COLORREF clr)
{
	DrawLineToDC(BackBufferDC, x1, y1, x2, y2, thk, clr);
}

void	DrawRectangle(RECT *r, int thk, COLORREF borderCLR, COLORREF fillCLR)
{
	DrawRectangleToDC(BackBufferDC, r, thk, borderCLR, fillCLR);
}

void	DrawEllipse(RECT *r, int thk, COLORREF clr)
{
	DrawEllipseToDC(BackBufferDC, r, thk, clr);
}

BOOL IsKeyDown(short KeyCode)
{

	SHORT	retval;

	retval = GetAsyncKeyState(KeyCode);

	if (HIBYTE(retval))
		return TRUE;

	return FALSE;
}


