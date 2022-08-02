//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 4 EXAMPLE PROGRAM

	NAME:		Particle Explosion
	PURPOSE:	To demonstrate 2D particle kinematics
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
HDC			hBufferDC;
HBITMAP		hBufferBitmap;


// Forward declarations for non-window related functions
void	InitializeVariables(void);
void	DrawLine(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void	DrawRectangle(HDC hdc, RECT *r, int thk, COLORREF clr);
void	DrawCircle(HDC hdc, int cx, int cy, int r, COLORREF clr);
void	DrawString(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);
int		DoSimulation(void);

BOOL	UpdateParticleState(TParticle* p, int dtime);
void		CreateParticleExplosion(int x, int y, int force, int life, float gravity, float angle);
BOOL	DrawParticleExplosion(HDC hdc);
int tb_Rnd(int min, int max);
int tb_Round(double x);


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
	BOOL				status;
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
									400, 
									400,
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
			//UpdateWindow(hSideView);

			// Now initialize all of the edit controls on the dialog box with our
			// default values for each variable.

			// Set default values for all variables
			InitializeVariables();
			
			// Now convert each variable value to a string and
			// set the appropriate edit control
			sprintf( str, "%d", xc );
			SetDlgItemText(hDlg, IDC_X, str);

			sprintf( str, "%d", yc );
			SetDlgItemText(hDlg, IDC_Y, str);

			sprintf( str, "%d", V0 );
			SetDlgItemText(hDlg, IDC_V0, str);

			sprintf( str, "%d", Duration );
			SetDlgItemText(hDlg, IDC_DURATION, str);

			sprintf( str, "%f", Gravity );
			SetDlgItemText(hDlg, IDC_GRAVITY, str);

			sprintf( str, "%f", Angle );
			SetDlgItemText(hDlg, IDC_ANGLE, str);

			// create a buffer to draw on:
			hdc = GetDC(hSideView);
			hBufferDC = CreateCompatibleDC(hdc);
			hBufferBitmap = CreateCompatibleBitmap(hdc, 400, 400);
			ReleaseDC(hSideView, hdc);

			//hBufferBitmap = CreateBitmap(500, 200, 1, 24, NULL);
			

			SelectObject(hBufferDC, hBufferBitmap);


			break;

		// handle the dialog controls here:
		case WM_COMMAND:
			switch( LOWORD( wParam) )
			{
				case IDC_RANDOM:
				case IDC_FIRE:
					// update the variables with
					// the values shown in the edit controls			

					if(LOWORD(wParam) == IDC_FIRE)
					{
						GetDlgItemText(hDlg, IDC_X, str, 15);
						xc = atoi(str);
			
						GetDlgItemText(hDlg, IDC_Y, str, 15);
						yc = atoi(str);
			
						GetDlgItemText(hDlg, IDC_V0, str, 15);
						V0 = atoi(str);
			
						GetDlgItemText(hDlg, IDC_DURATION, str, 15);
						Duration = atoi(str);
			
						GetDlgItemText(hDlg, IDC_GRAVITY, str, 15);
						Gravity = atof(str);
			
						GetDlgItemText(hDlg, IDC_ANGLE, str, 15);
						Angle = atof(str);
					} else {
						xc = tb_Rnd(100, 300);
						yc = tb_Rnd(100, 300);
						V0 = tb_Rnd(10, 100);
						Duration = tb_Rnd(2000, 6000);
						Gravity = tb_Rnd(0, 100);
						Angle = 999;

						sprintf( str, "%d", xc );
						SetDlgItemText(hDlg, IDC_X, str);

						sprintf( str, "%d", yc );
						SetDlgItemText(hDlg, IDC_Y, str);

						sprintf( str, "%d", V0 );
						SetDlgItemText(hDlg, IDC_V0, str);

						sprintf( str, "%d", Duration );
						SetDlgItemText(hDlg, IDC_DURATION, str);

						sprintf( str, "%f", Gravity );
						SetDlgItemText(hDlg, IDC_GRAVITY, str);

						sprintf( str, "%f", Angle );
						SetDlgItemText(hDlg, IDC_ANGLE, str);
					}

					CreateParticleExplosion(xc, yc, V0, Duration, Gravity, Angle);
					r.left = 0;
					r.right = 400;
					r.top = 0;
					r.bottom = 400;

					// initialize the time and status variables
					status = TRUE;
					
					// start stepping through time for the sim.
					// until the target is hit, the shell hits
					// the ground, or the sim. times out.
					while(status)
					{
						DrawRectangle(hBufferDC, &r, 1, RGB(0,0,0));
						status = DrawParticleExplosion(hBufferDC);
						hdc = GetDC(hSideView);
						//status = DrawParticleExplosion(hdc);
						if(!BitBlt(	hdc,
								0,
								0,
								r.right,
								r.bottom,
								hBufferDC,
								0, 
								0,
								SRCCOPY)) 
						{
								MessageBox(NULL, "BitBlt failed", "Error", MB_OK);
								status = FALSE;
						}
						
						ReleaseDC(hSideView, hdc);
					}
					break;			
			
				case ID_CLOSE:
					// clean up the child windows and close the dialog box					
					DeleteObject(hBufferBitmap);
					DeleteDC(hBufferDC);
					DestroyWindow(hSideView);
					EndDialog(hDlg, 1);
					break;

				case IDCANCEL:
					// clean up the child windows and close the dialog box					
					DeleteObject(hBufferBitmap);
					DeleteDC(hBufferDC);
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
/*	PAINTSTRUCT			ps;
	HDC					hdc;
	RECT				r;
	LONG				tag;
*/
	switch (message) {
/*		case WM_PAINT:			
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
			break;*/
	}
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//----------------------------------------------------------------------------------------------------//
// Initialize the global variables required for the simulation.
//----------------------------------------------------------------------------------------------------//
void	InitializeVariables(void)
//----------------------------------------------------------------------------------------------------//
{
	xc = 200;
	yc = 100;
	V0 = 75;
	Duration = 4000;
	Gravity = 30.0f;
	Angle = 999;
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
	COLORREF	BColor = clr;
				
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
// This function simply draws a filled circle to the given device context
//----------------------------------------------------------------------------------------------------//
void DrawCircle(HDC hdc, int cx, int cy, int r, COLORREF clr)
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;	
	COLORREF	FColor = clr;
	COLORREF	BColor = clr;	
				
	CurrentBrush = CreateSolidBrush(BColor);
	OldBrush = (HBRUSH) SelectObject( hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, 1, FColor);
	OldPen = (HPEN) SelectObject(hdc, CurrentPen);

	Ellipse(hdc, cx - r, cy - r, cx + r, cy + r);
 
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

	return 0;	
}

///////////////////////////////////////////////////////////////////
/*  This is generic function to update the state of a given particle.
	There's no need to call this function directly, it's used by the
	particle explosion and hose functions.

	p:		pointer to a particle structure
	dtime:	time increment in milliseconds to advance the state of the particle

	If the total elapsed time for this particle has exceeded the particle's
	set life, then this function returns FALSE indicating that the particle
	should expire.	
*/
BOOL	UpdateParticleState(TParticle* p, int dtime)
{
	BOOL retval;
	float	t;
	
	p->time+=dtime;
	t = (float)p->time/1000.0f;
	p->x = p->vi * cos(p->angle*PI/180.0f) * t;
	p->y = p->vi * sin(p->angle*PI/180.0f) * t + (p->gravity*t*t)/2.0f;

	if (p->time >= p->life)
		retval = FALSE;
	else
		retval = TRUE;

	return retval;
}

/////////////////////////////////////////////////////////////////////
/*	This function creates a new particle explosion effect.

	x,y:	starting point of the effect
	Vinit:	a measure of how fast the particles will be sent flying (it's actually the initial
			velocity of the particles)
	life:	life of the particles in milliseconds; particles will fade and die out as they approach
			their specified life
	gravity:	the acceleration due to gravity which controls the rate at which particles will fall
				as they fly
	angle:	initial trajectory angle of the particles, specify 999 to create a particle explosion
			that emits particles in all directions; otherwise, 0 right, 90 up, 180 left, etc...

	clr:	use one of the defines in FX.h to indicate a color; kfxRandom randomly selects one of
			kfxRed, kfxBlue or kfxGreen.

	Returns an index to the new effect.
*/
void		CreateParticleExplosion(int x, int y, int Vinit, int life, float gravity, float angle)
{
	int	i;
	int	m;
	float f;

	Explosion.Active = TRUE;
	Explosion.x = x;
	Explosion.y = y;
	Explosion.V0 = Vinit;		
		
	for(i=0; i<_MAXPARTICLES; i++)
	{
		Explosion.p[i].x = 0;
		Explosion.p[i].y = 0;
		Explosion.p[i].vi = tb_Rnd(Vinit/2, Vinit);
			
		if(angle < 999)
		{
			if(tb_Rnd(0,1) == 0)
				m = -1;
			else
				m = 1;
			Explosion.p[i].angle = -angle + m * tb_Rnd(0,10);
		} else			
			Explosion.p[i].angle = tb_Rnd(0,360);

		f = (float) tb_Rnd(80, 100) / 100.0f;
		Explosion.p[i].life = tb_Round(life * f);
		Explosion.p[i].r = 255;//tb_Rnd(225, 255);
		Explosion.p[i].g = 255;//tb_Rnd(85, 115);
		Explosion.p[i].b = 255;//tb_Rnd(15, 45);
		Explosion.p[i].time = 0;
		Explosion.p[i].Active = TRUE;			
		Explosion.p[i].gravity = gravity;		
	}

}


///////////////////////////////////////////////////////////////////
// Draws the particle system and updates the state of each particle.
// Returns false when all of the particles have died out.
BOOL	DrawParticleExplosion(HDC hdc)
{
	int	i;
	BOOL	finished = TRUE;
	float			r;	
	COLORREF	clr;
	
	if(Explosion.Active)
	  for(i=0; i<_MAXPARTICLES; i++)
	  {
		if(Explosion.p[i].Active)
		{
			finished = FALSE;
			r = 	((float)(Explosion.p[i].life-Explosion.p[i].time)/(float)(Explosion.p[i].life));
			clr = RGB(tb_Round(r*Explosion.p[i].r), tb_Round(r*Explosion.p[i].g), tb_Round(r*Explosion.p[i].b));
			DrawCircle(	hdc, 
						Explosion.x+tb_Round(Explosion.p[i].x), 
						Explosion.y+tb_Round(Explosion.p[i].y), 
						2, 
						clr);
			Explosion.p[i].Active = UpdateParticleState(&(Explosion.p[i]), 10);
		}
	  }

	if(finished)
		Explosion.Active = FALSE;

	return !finished;
}

///////////////////////////////////////////////////////////////////
//  This function finds a random number
int tb_Rnd(int min, int max) {
	int	number;
		
    //number = min + rand()%max;
    //number = min +tb_Trunc(max*rand());
    number = (((abs(rand())%(max-min+1))+min));    
    
    if(number>max) {
    	number = max;
    	//tb_Beep();
    }
    
    if(number<min) {
    	number = min;
    	//tb_Beep();
    }	
		
	return number;
}

///////////////////////////////////////////////////////////////////
//  This function rounds a number
int tb_Round(double x) {
	int	result;
	double	remainder;

	result = (int) (x);
	
	if (result == 0) return 0;

	remainder = fmod(x, (double) result);
	if (remainder>=0.5)
		result++;

	return result;
}


