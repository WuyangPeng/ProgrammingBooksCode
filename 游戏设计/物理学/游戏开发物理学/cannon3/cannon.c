//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 4 EXAMPLE PROGRAM

	NAME:		Cannon 2
	PURPOSE:	To demonstrate 3D particle kinetics
	BY:			David Bourg
	DATE:		04/28/00
	COPYRIGHT:	Copyright 2000 by David Bourg
*/
//----------------------------------------------------------------------------------------------------//
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
#include "cannon.h"

// Defines:
#define		MYSIDEVIEW	2000

// Forward declarations for window related functions
LRESULT CALLBACK DemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Window related global variables
HINSTANCE	hinst; 
HWND		hMainWindow; 

// Forward declarations for non-window related functions
void	InitializeVariables(void);
void	DrawSideView(HDC hdc, RECT *r);
void	DrawLine(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void	DrawRectangle(HDC hdc, RECT *r, int thk, COLORREF clr);
void	DrawString(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);
int		DoSimulation(void);


//----------------------------------------------------------------------------------------------------//
// This is the applications "main" function. Note that I'm not using a message loop here
// since there is no main window. All I do is display a dialog box immediately upon startup
// and let the dialog handler take care of the messages.
//----------------------------------------------------------------------------------------------------//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//----------------------------------------------------------------------------------------------------//
{	
	DLGPROC		dlgprc;
	int			retval = 0;
 
    // Display the dialog box and check to make sure it was created:
    dlgprc = (DLGPROC) MakeProcInstance(DemoDlgProc, hInstance);    
    retval = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DEMODIALOG), NULL, dlgprc);	
	if(retval == -1)
	{
		MessageBox(NULL, "Error", "Can't create dialog box.", MB_OK);
		return FALSE;
	}
	FreeProcInstance((FARPROC) dlgprc);
	
	
	// Return false since we never got to a main message loop
	return (FALSE);
}

//----------------------------------------------------------------------------------------------------//
// This is the message handler function for the main dialog box.  It is responsible for handling
// any interaction with it's controls and for updating the trajectory views that we'll be displaying.
//----------------------------------------------------------------------------------------------------//
LRESULT CALLBACK DemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//----------------------------------------------------------------------------------------------------//
{
	static	HWND	hTopView;
	static	HWND	hSideView;
	WNDCLASSEX		wclass;
	char			str[16];
	int				status;
	RECT			r;
	HDC				hdc;	

	switch (message) {
		// Initialize the dialog box here:
		case WM_INITDIALOG:
			// setup a child window class so we can create a couple
			// of windows to draw the two trajectory views on
			wclass.cbSize				=	sizeof(wclass);
			wclass.style				=	CS_HREDRAW | CS_VREDRAW;
			wclass.lpfnWndProc			=	DefaultWndProc;
			wclass.cbClsExtra			=	0;
			wclass.cbWndExtra			=	0;
			wclass.hInstance			=	hinst;
			wclass.hIcon				=	NULL;
			wclass.hCursor				=   NULL;
			wclass.hbrBackground		=	(HBRUSH) CreateSolidBrush(RGB(0,0,0));
			wclass.lpszMenuName			=	NULL;
			wclass.lpszClassName		=	"ViewClass";
			wclass.hIconSm				=	NULL;

			RegisterClassEx(&wclass);

			// Now go ahead and create a child window for the side view
			hSideView = CreateWindowEx(	0L, 
									"ViewClass", 
									NULL, 
									WS_CHILD | WS_VISIBLE | WS_BORDER,
									150, 
									10+10, 
									500, 
									200,
									hDlg, 
									NULL, 
									hinst, 
									NULL);

			// Tag the window with our identifier, MYSIDEVIEW, so that we
			// can distinguish it from the top view window when it's time
			// to draw in the window.
			SetWindowLong(hSideView, GWL_USERDATA, MYSIDEVIEW);
   
			// Show the window
			ShowWindow(hSideView, SW_SHOW);
			UpdateWindow(hSideView);

			// Now initialize all of the edit controls on the dialog box with our
			// default values for each variable.

			// Set default values for all variables
			InitializeVariables();
			
			// Now convert each variable value to a string and
			// set the appropriate edit control
			sprintf( str, "%f", V1.i );
			SetDlgItemText(hDlg, IDC_V0, str);

			sprintf( str, "%f", spin );
			SetDlgItemText(hDlg, IDC_SPIN, str);

			sprintf( str, "%f", m );
			SetDlgItemText(hDlg, IDC_M, str);

			sprintf( str, "%f", radius );
			SetDlgItemText(hDlg, IDC_RADIUS, str);
			break;

		// handle the dialog controls here:
		case WM_COMMAND:
			switch( LOWORD( wParam) )
			{
				case IDC_REFRESH:
					// update the variables with
					// the values shown in the edit controls
					GetDlgItemText(hDlg, IDC_V0, str, 15);
					V1.i = atof(str);
					V1.j = 0;

					GetDlgItemText(hDlg, IDC_SPIN, str, 15);
					spin = atof(str);
			
					GetDlgItemText(hDlg, IDC_M, str, 15);
					m = atof(str);
					
					GetDlgItemText(hDlg, IDC_RADIUS, str, 15);
					radius = atof(str);

					omega = (2*PI*spin)/60;

					
					// re-initialize the time and position of the shell
					time = 0;
					s1.i = 0;
					s1.j = 1.8288;					

					hdc = GetDC(hSideView);
					GetClientRect(hSideView, &r);
					DrawSideView(hdc, &r);
					ReleaseDC(hSideView, hdc);
					break;

				case IDC_FIRE:
					// update the variables with
					// the values shown in the edit controls			
					GetDlgItemText(hDlg, IDC_V0, str, 15);
					V1.i = atof(str);
					V1.j = 0;

					GetDlgItemText(hDlg, IDC_SPIN, str, 15);
					spin = atof(str);
			
					GetDlgItemText(hDlg, IDC_M, str, 15);
					m = atof(str);
					
					GetDlgItemText(hDlg, IDC_RADIUS, str, 15);
					radius = atof(str);

					omega = (2*PI*spin)/60;
					s1.i = 0;
					s1.j = 1.8288;					

					// initialize the time and status variables
					status = 0;
					time = 0;
					// start stepping through time for the sim.
					// until the target is hit, the shell hits
					// the ground, or the sim. times out.
					while(status == 0)
					{
						// do the next time step
						status = DoSimulation();

						hdc = GetDC(hSideView);
						GetClientRect(hSideView, &r);
						DrawSideView(hdc, &r);
						ReleaseDC(hSideView, hdc);
					}

					// Report results
					if (status == 3)
						MessageBox(NULL, "Timed Out", "Error", MB_OK);

					break;			
			
				case ID_CLOSE:
					// clean up the child windows and close the dialog box					
					DestroyWindow(hSideView);
					EndDialog(hDlg, 1);
					break;

				case IDCANCEL:
					// clean up the child windows and close the dialog box					
					DestroyWindow(hSideView);
					EndDialog(hDlg, 0);
					break;
			}			
			break;
		
		default:
			return( FALSE );
	}
    return ( TRUE );
}

//----------------------------------------------------------------------------------------------------//
// This is the default message processing function for the two child windows that are created
// so to draw the trajectory views.
//----------------------------------------------------------------------------------------------------//
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//----------------------------------------------------------------------------------------------------//
{	
	PAINTSTRUCT			ps;
	HDC					hdc;
	RECT				r;
	LONG				tag;

	switch (message) {
		case WM_PAINT:			
			hdc = BeginPaint(hwnd, &ps);

			// Get the tag that we set when we created the child windows
			// where we plan to draw the shell trajectory
			tag = GetWindowLong(hwnd, GWL_USERDATA);

			if(tag == MYSIDEVIEW)  // We need to draw the side view
			{
				GetClientRect(hwnd, &r);
				DrawSideView(hdc, &r);
			}			

			EndPaint(hwnd, &ps);
			break;
	}
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//----------------------------------------------------------------------------------------------------//
// Initialize the global variables required for the simulation.
//----------------------------------------------------------------------------------------------------//
void	InitializeVariables(void)
//----------------------------------------------------------------------------------------------------//
{
	V1.i	= 40.0;		// m/s
	V1.j	= 0.0;		// m/s

	m		= 0.136;	// kgs
	spin	= 0;		// rpm
	radius	= 0.0635;	// m

	time	=	0;		// seconds
	tInc	=	0.01;	// seconds
	g		=	9.8;	// m/(s*s)

	s1.i	=	0.0;
	s1.j	=	1.8288;

}

//----------------------------------------------------------------------------------------------------//
// This function draws the side (profile) view of the simulation.  It shows the cannon,
// the target and the shell trajectory.  Scale is 1 pixel per meter.
//----------------------------------------------------------------------------------------------------//
void	DrawSideView(HDC hdc, RECT *r)
//----------------------------------------------------------------------------------------------------//
{
	int					w = (r->right - r->left);	// the window width
	int					h = (r->bottom - r->top);	// the window height	
	COLORREF			red = RGB(255,0,0);
	COLORREF			black = RGB(0,0,0);
	COLORREF			blue = RGB(0,0,255);
	COLORREF			white = RGB(255,255,255);
	COLORREF			green = RGB(0,255,0);
	int					x,y;

	// NOTE: the h factor that you see in the following
	// calculations is an adjustment to place the origin 
	// at the bottom of the window.  The window origin is
	// the upper left corner by default. Note also that
	// since the vertical coordinate in the default window
	// coordinate system is positive down, we need to take
	// the negative of our calculated y-values in order to
	// plot the trajectory as though y is positive up.

	if(time == 0)
		DrawRectangle(hdc, r, 1, black);
	
	// Draw the shell in blue
	// Draw the shell in blue (only draw the shell if time is greater than zero, i.e., 
	// only after it leaves the barrel in our simulation
	if(time>0)
	{
		x = (int) (s2.i * 20);
		y = (int) ((-s2.j * 20) + h);
		DrawLine(hdc, x, y, x, y, 2, green);
	}

	// Draw label for this view
	DrawString(hdc, 5, 20, "Side View", 9, 14);

}

//----------------------------------------------------------------------------------------------------//
// This function simply draws a solid line to the given device context, given the line
// start and end point, its thickness and its color.
//----------------------------------------------------------------------------------------------------//
void DrawLine(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr)
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
void DrawRectangle(HDC hdc, RECT *r, int thk, COLORREF clr)
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

	Rectangle(hdc, r->left, r->top, r->right, r->bottom);
 
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
void DrawString(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz)
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
	hOldFont = SelectObject(hdc, hFont);
		
	TextOut(hdc, x, y, lpszString, size);    
    
	SelectObject(hdc, hOldFont); 
	DeleteObject(hFont); 
}


//----------------------------------------------------------------------------------------------------//
// This function steps the simulation ahead in time. This is where the kinematic properties
// are calculated.  The function will return 1 when the target is hit, and 2 when the shell
// hits the ground (x-z plane) before hitting the target, otherwise the function returns 0.
//----------------------------------------------------------------------------------------------------//
int	DoSimulation(void)
//----------------------------------------------------------------------------------------------------//
{
	double	C = PI * RHO * RHO * radius * radius * radius * omega;
	double	t;
		
	// step to the next time in the simulation
	time+=tInc;
	t = time;

	// calc V2:
	V2.i = 1.0f/(1.0f-(t/m)*(t/m)*C*C) * (V1.i + C * V1.j * (t/m) - C * g * (t*t)/m);
	V2.j = V1.j + (t/m)*C*V2.i - g*t;

	// calc S2:
	s2.i = s1.i + V1.i * t + (1.0f/2.0f) * (C/m * V2.j) * (t*t);
	s2.j = s1.j + V1.j * t + (1.0f/2.0f) * ( ((C*V2.i) - m*g)/m ) * (t*t);


	// Check for collision with ground (x-z plane)
	if(s2.j <= 0)
		return 2;

	// Cutoff the simulation if it's taking too long
	// This is so the program does not get stuck in the while loop
	if(time>60)
		return 3;

	return 0;	
}
