//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 2 EXAMPLE PROGRAM

	NAME:		Cannon
	PURPOSE:	To demonstrate 3D particle kinematics
	BY:			David Bourg
	DATE:		03/01/00
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
#define		MYTOPVIEW	1000
#define		MYSIDEVIEW	2000

// Forward declarations for window related functions
LRESULT CALLBACK DemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Window related global variables
HINSTANCE	hinst; 
HWND		hMainWindow; 

// Forward declarations for non-window related functions
void	InitializeVariables(void);
void	DrawTopView(HDC hdc, RECT *r);
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

			// Now go ahead and create a child window for the top view
			hTopView = CreateWindowEx(	0L, 
									"ViewClass", 
									NULL, 
									WS_CHILD | WS_VISIBLE | WS_BORDER,
									150, 
									10, 
									500, 
									200,
									hDlg, 
									NULL, 
									hinst, 
									NULL);

			// Tag the window with our identifier, MYTOPVIEW, so that we
			// can distinguish it from the side view window when it's time
			// to draw in the window.
			SetWindowLong(hTopView, GWL_USERDATA, MYTOPVIEW);
   
			// Show the window
			ShowWindow(hTopView, SW_SHOW);
			UpdateWindow(hTopView);

			// Now go ahead and create a child window for the side view
			hSideView = CreateWindowEx(	0L, 
									"ViewClass", 
									NULL, 
									WS_CHILD | WS_VISIBLE | WS_BORDER,
									150, 
									10+10+200, 
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
			sprintf( str, "%f", Vm );
			SetDlgItemText(hDlg, IDC_VM, str);

			sprintf( str, "%f", Alpha );
			SetDlgItemText(hDlg, IDC_ALPHA, str);

			sprintf( str, "%f", Gamma );
			SetDlgItemText(hDlg, IDC_GAMMA, str);
			
			sprintf( str, "%f", L );
			SetDlgItemText(hDlg, IDC_L, str);
			
			sprintf( str, "%f", Yb );
			SetDlgItemText(hDlg, IDC_YB, str);

			sprintf( str, "%f", X );
			SetDlgItemText(hDlg, IDC_X, str);

			sprintf( str, "%f", Y );
			SetDlgItemText(hDlg, IDC_Y, str);
			
			sprintf( str, "%f", Z );
			SetDlgItemText(hDlg, IDC_Z, str);
			
			sprintf( str, "%f", Length );
			SetDlgItemText(hDlg, IDC_LENGTH, str);
			
			sprintf( str, "%f", Width );
			SetDlgItemText(hDlg, IDC_WIDTH, str);
			
			sprintf( str, "%f", Height );
			SetDlgItemText(hDlg, IDC_HEIGHT, str);

			break;

		// handle the dialog controls here:
		case WM_COMMAND:
			switch( LOWORD( wParam) )
			{
				case IDC_REFRESH:
					// update the variables with
					// the values shown in the edit controls
					GetDlgItemText(hDlg, IDC_VM, str, 15);
					Vm = atof(str);
			
					GetDlgItemText(hDlg, IDC_ALPHA, str, 15);
					Alpha = atof(str);
			
					GetDlgItemText(hDlg, IDC_GAMMA, str, 15);
					Gamma = atof(str);			
			
					GetDlgItemText(hDlg, IDC_L, str, 15);
					L  = atof(str);			
			
					GetDlgItemText(hDlg, IDC_YB, str, 15);
					Yb = atof(str);
			
					GetDlgItemText(hDlg, IDC_X, str, 15);
					X = atof(str);

					GetDlgItemText(hDlg, IDC_Y, str, 15);
					Y = atof(str);
			
					GetDlgItemText(hDlg, IDC_Z, str, 15);
					Z = atof(str);
			
					GetDlgItemText(hDlg, IDC_LENGTH, str, 15);
					Length = atof(str);
			
					GetDlgItemText(hDlg, IDC_WIDTH, str, 15);
					Width = atof(str);
			
					GetDlgItemText(hDlg, IDC_HEIGHT, str, 15);
					Height = atof(str);
					
					// re-initialize the time and position of the shell
					time = 0;
					s.i = 0;
					s.j = 0;
					s.k = 0;

					// Repaint the views
					hdc = GetDC(hTopView);
					GetClientRect(hTopView, &r);
					DrawTopView(hdc, &r);
					ReleaseDC(hTopView, hdc);

					hdc = GetDC(hSideView);
					GetClientRect(hSideView, &r);
					DrawSideView(hdc, &r);
					ReleaseDC(hSideView, hdc);
					break;

				case IDC_FIRE:
					// update the variables with
					// the values shown in the edit controls			
					GetDlgItemText(hDlg, IDC_VM, str, 15);
					Vm = atof(str);
			
					GetDlgItemText(hDlg, IDC_ALPHA, str, 15);
					Alpha = atof(str);
			
					GetDlgItemText(hDlg, IDC_GAMMA, str, 15);
					Gamma = atof(str);			
			
					GetDlgItemText(hDlg, IDC_L, str, 15);
					L  = atof(str);			
			
					GetDlgItemText(hDlg, IDC_YB, str, 15);
					Yb = atof(str);
			
					GetDlgItemText(hDlg, IDC_X, str, 15);
					X = atof(str);

					GetDlgItemText(hDlg, IDC_Y, str, 15);
					Y = atof(str);
			
					GetDlgItemText(hDlg, IDC_Z, str, 15);
					Z = atof(str);
			
					GetDlgItemText(hDlg, IDC_LENGTH, str, 15);
					Length = atof(str);
			
					GetDlgItemText(hDlg, IDC_WIDTH, str, 15);
					Width = atof(str);
			
					GetDlgItemText(hDlg, IDC_HEIGHT, str, 15);
					Height = atof(str);

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

						// update the views
						hdc = GetDC(hTopView);
						GetClientRect(hTopView, &r);
						DrawTopView(hdc, &r);
						ReleaseDC(hTopView, hdc);

						hdc = GetDC(hSideView);
						GetClientRect(hSideView, &r);
						DrawSideView(hdc, &r);
						ReleaseDC(hSideView, hdc);
					}

					// Report results
					if (status == 1)
						MessageBox(NULL, "Direct Hit", "Score!", MB_OK);

					if (status == 2)
						MessageBox(NULL, "Missed Target", "No Score.", MB_OK);

					if (status == 3)
						MessageBox(NULL, "Timed Out", "Error", MB_OK);
					break;			
			
				case ID_CLOSE:
					// clean up the child windows and close the dialog box
					DestroyWindow(hTopView);
					DestroyWindow(hSideView);
					EndDialog(hDlg, 1);
					break;

				case IDCANCEL:
					// clean up the child windows and close the dialog box
					DestroyWindow(hTopView);
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

			if(tag == MYTOPVIEW) // We need to draw the top view
			{
				GetClientRect(hwnd, &r);
				DrawTopView(hdc, &r);
			} else // We need to draw the side view
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
	Vm		=	50;		// m/s
	Alpha	=	25;		// degrees
	Gamma	=	0;		// along x-axis
	L		=	12;		// m
	Yb		=	10;		// on x-z plane

	X		=	400;	// m
	Y		=	35;		// on x-z plane
	Z		=	45;		// on x-axis
	Length	=	10;		// m
	Width	=	15;		// m
	Height	=	20;		// m

	s.i		=	0;		// m
	s.j		=	0;		// m
	s.k		=	0;		// m

	time	=	0;		// seconds
	tInc	=	0.05;	// seconds
	g		=	9.8;	// m/(s*s)
}

//----------------------------------------------------------------------------------------------------//
// Here's where we draw the top view of the simulation.  We'll show the cannon location, 
// the target location, and the shell trajectory.  The scale here is 1 pixel equals 1 meter.
//----------------------------------------------------------------------------------------------------//
void	DrawTopView(HDC hdc, RECT *r)
//----------------------------------------------------------------------------------------------------//
{
	int					w = (r->right - r->left);	// the window width
	int					h = (r->bottom - r->top);	// the window height
	RECT				tr;
	COLORREF			red = RGB(255,0,0);
	COLORREF			black = RGB(0,0,0);
	COLORREF			blue = RGB(0,0,255);
	COLORREF			white = RGB(255,255,255);
	COLORREF			green = RGB(0,255,0);
	int					x,z;

	// NOTE: the h/2 factor that you see in the following
	// calculations is an adjustment to place the origin 
	// at mid-height in the window.  The window origin is
	// the upper left corner by default.

	if(time == 0)
		DrawRectangle(hdc, r, 1, black);

	// Draw target bounding box (we'll draw the target in red)
	tr.left = (int) (X - Length/2);
	tr.right = (int) (X + Length/2);
	tr.top = (int) (Z - Width/2 + h/2);
	tr.bottom = (int) (Z + Width/2 + h/2);
	DrawRectangle(hdc, &tr, 2, red);

	// Draw the cannon in black
	tr.left = 0;
	tr.top = h/2;
	tr.right = (int) (L * cos((90-Alpha) *3.14/180) * cos(Gamma * 3.14/180));
	tr.bottom = (int) (L * cos((90-Alpha) *3.14/180) * sin(Gamma * 3.14/180) + h/2);
	DrawLine(hdc, tr.left, tr.top, tr.right, tr.bottom, 2, blue);
	
	// Draw the shell in blue (only draw the shell if time is greater than zero, i.e., 
	// only after it leaves the barrel in our simulation
	if(time>0)
	{
		x = (int) (s.i);
		z = (int) (s.k + h/2);
		DrawLine(hdc, x, z, x, z, 2, green);
	}

	// Draw label for this view
	DrawString(hdc, 5, 20, "Top View", 8, 14);

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
	RECT				tr;
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

	// Draw target bounding box (we'll draw the target in red)
	tr.left = (int) (X - Length/2);
	tr.right = (int) (X + Length/2);
	tr.top = (int) (-Y + Height/2 + h);
	tr.bottom = (int) (-Y - Height/2 + h);
	DrawRectangle(hdc, &tr, 2, red);

	// Draw the cannon in black
	tr.left = 0;
	tr.top = h - (int) Yb;
	tr.right = (int) (L * cos((90-Alpha) *3.14/180) * cos(Gamma * 3.14/180));
	tr.bottom = (int) (-(L * cos(Alpha * 3.14/180)) + h - Yb);
	DrawLine(hdc, tr.left, tr.top, tr.right, tr.bottom, 2, blue);
	
	// Draw the shell in blue
	// Draw the shell in blue (only draw the shell if time is greater than zero, i.e., 
	// only after it leaves the barrel in our simulation
	if(time>0)
	{
		x = (int) (s.i);
		y = (int) (-s.j + h);
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
	double	cosX;
	double	cosY;
	double	cosZ;
	double	xe, ze;
	double	b, Lx, Ly, Lz;
	double	tx1, tx2, ty1, ty2, tz1, tz2;
	
	// step to the next time in the simulation
	time+=tInc;

	// First calculate the direction cosines for the cannon orientation.
	// In a real game you would not want to put this calculation in this
	// function since it is a waste of CPU time to calculate these values
	// at each time step as they never change during the sim.  I only put them here in 
	// this case so you can see all the calculation steps in a single function.
	b = L * cos((90-Alpha) *3.14/180);  // projection of barrel onto x-z plane
	Lx = b * cos(Gamma * 3.14/180);		// x-component of barrel length
	Ly = L * cos(Alpha * 3.14/180);		// y-component of barrel length
	Lz = b  * sin(Gamma * 3.14/180);	// z-component of barrel length

	cosX = Lx/L;
	cosY = Ly/L;
	cosZ = Lz/L;

	// These are the x and z coordinates of the very end of the cannon barrel
	// we'll use these as the initial x and z displacements
	xe = L * cos((90-Alpha) *3.14/180) * cos(Gamma * 3.14/180);
	ze = L * cos((90-Alpha) *3.14/180) * sin(Gamma * 3.14/180);
	
	// Now we can calculate the position vector at this time
	s.i = Vm * cosX * time + xe;
	s.j = (Yb + L * cos(Alpha*3.14/180)) + (Vm * cosY * time) - (0.5 * g * time * time);
	s.k = Vm * cosZ * time + ze;

	// Check for collision with target
	// Get extents (bounding coordinates) of the target
	tx1 = X - Length/2;
	tx2 = X + Length/2;
	ty1 = Y - Height/2;
	ty2 = Y + Height/2;
	tz1 = Z - Width/2;
	tz2 = Z + Width/2;
	
	// Now check to see if the shell has passed through the target
	// I'm using a rudimentary collision detection scheme here where
	// I simply check to see if the shell's coordinates are within the
	// bounding box of the target.  This works for demo purposes, but
	// a practical problem is that you may miss a collision if for a given
	// time step the shell's change in position is large enough to allow 
	// it to "skip" over the target.
	// A better approach is to look at the previous time step's position data
	// and to check the line from the previous postion to the current position
	// to see if that line intersects the target bounding box.
	if( (s.i >= tx1 && s.i <= tx2) &&
		(s.j >= ty1 && s.j <= ty2) &&
		(s.k >= tz1 && s.k <= tz2) )
		return 1;

	// Check for collision with ground (x-z plane)
	if(s.j <= 0)
		return 2;

	// Cutoff the simulation if it's taking too long
	// This is so the program does not get stuck in the while loop
	if(time>3600)
		return 3;

	return 0;	
}
