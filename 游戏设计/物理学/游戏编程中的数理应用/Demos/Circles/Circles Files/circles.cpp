// Circles.cpp /////////////////////////////////////////////////////////////
//
// This example is used to demonstrate the movement and collision of two
// balls with the bounds of the screen and each other.  This program uses
// a frame based loop rather than relying on windows messages, in order to 
// regulate the speed of the balls.
//
////////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN				// We don't need any MFC objects

// INCLUDES ////////////////////////////////////////////////////////////////

#include <windows.h>					// Include std windows library
#include <time.h>
#include <stdlib.h>

#include "Ball.h"						// Our Ball Class

// DEFINES /////////////////////////////////////////////////////////////////

#define WINDOW_CLASS_NAME "WINCLASS1"	// The name of our window class
#define WINDOW_WIDTH 640				// The initial width of the window
#define WINDOW_HEIGHT 480				// The initial height of the window

// GLOBALS /////////////////////////////////////////////////////////////////

HWND g_main_window_handle = NULL;		// globally track main window
HINSTANCE hinstance_app = NULL;			// globally track hinstance

// FUNCTIONS ///////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	// what is the message 
	switch(msg)
	{	
		// Make sure that the user can not resize the screen smaller than 400 x 300
		case WM_GETMINMAXINFO:
		{
			// Retrieve the window size info from the lParam
			LPMINMAXINFO lpnmi = (LPMINMAXINFO)lParam;
			// Create a new point set to the min width and min height of the screen
			POINT ts;
			ts.x = 400;
			ts.y = 300;
			// Set the minTrackSize (the smallest size the window can be set to) 
			// to the new POINT
			lpnmi->ptMinTrackSize = ts;
		}
		break;

		case WM_DESTROY: 
		{

			// Kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);

			// Return success
			return(0);
		} 
		break;

		default:break;

	} // end switch

	// Process any messages that we didn't take care of 
	return (DefWindowProc(hWnd, msg, wParam, lParam));

} // end WinProc

// WINMAIN /////////////////////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hWnd;	 // generic window handle
	MSG		   msg;		 // generic message

	// first fill in the window class stucture
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
							  CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= NULL;
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm        = NULL;

	// Save hinstance globally
	hinstance_app = hinstance;

	// Register the window class
	if (!RegisterClassEx(&winclass))
		return(0);

	// Create the window
	if (!(hWnd = CreateWindowEx(NULL,						// extended window style
								WINDOW_CLASS_NAME,			// class
								"CIRCLES",					// title
								WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// window style
					 			100,20,						// initial x,y
								WINDOW_WIDTH,WINDOW_HEIGHT,	// initial width, height
								NULL,						// handle to parent 
								NULL,						// handle to menu
								hinstance,					// instance of this application
								NULL)))						// extra creation parms
		return(0);

	// Save main window handle
	g_main_window_handle = hWnd;

	HDC	hDC, hMemDC;		// Handles to a device context
	HBITMAP hOldBmp, hBmp;	// Bitmaps used for blitting the screen

	// Seed the random number generator
	srand(time(0));

	// Create the balls
	Ball ball1;
	Ball ball2;

	// Make some new pens and brushes for drawing the balls
	HPEN green_pen = CreatePen(PS_SOLID, 1, RGB(0,255,0));
	HBRUSH green_brush = CreateSolidBrush(RGB(0,255,0));
	HPEN blue_pen = CreatePen(PS_SOLID, 1, RGB(0,0,255));
	HBRUSH blue_brush = CreateSolidBrush(RGB(0,0,255));
	
	// Create a variable to store the time a collision happened.  This will be used to display 
	// a collision message to the screen for 1.5 seconds
	DWORD dwCollisionTime = 0;

	// Enter main loop
	while(TRUE)
	{
		// Get the client area
		RECT cr;
		GetClientRect(hWnd, &cr);

		// Test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// Test if this is a quit
			if (msg.message == WM_QUIT)
			   break;
			// Translate any messages
			TranslateMessage(&msg);
			// Send the message to the window proc
			DispatchMessage(&msg);
		} // end if

		// Get the time this function began executing
		DWORD dwStartTime = GetTickCount();
		// Get the display device context
		hDC = GetDC(hWnd);
		// Get the client retangle for the display bitmap
		GetClientRect(hWnd, &cr);

		// Create a new memory device context
		hMemDC = CreateCompatibleDC(hDC);
		// Create a bitmap for the memory DC
		hBmp = CreateCompatibleBitmap(hDC, cr.right, cr.bottom);
		// Attach the new bitmap to the memory DC
		hOldBmp = (HBITMAP)SelectObject(hMemDC, hBmp); 
		
		// Move the balls
		ball1.move();
		ball2.move();

		// Check for a collision with the wall
		ball1.checkWallCollision();
		ball2.checkWallCollision();

		// Check to see if the two balls collided, and if it's been more than 
		// 500 milliseconds since the last collision, to ensure the balls 
		// don't 'stick' to each other
		if (GetTickCount() - dwCollisionTime > 500 && ball1.checkBallCollision(ball2))
		{
			// They collided, so set the collision time to the current time
			dwCollisionTime = GetTickCount();
		} // end if

		// Display a message showing the collision for 1.5 seconds after a collision has occured
		if (GetTickCount() - dwCollisionTime < 1500)
		{
			// The string we want to output
			char string[] = "Collision Detected";

			// Set the Colors for outputing text to the screen
			// Set the foreground color to green
			SetTextColor(hMemDC, RGB(0,255,0));
			// Set the background color to black
			SetBkColor(hMemDC, RGB(0,0,0));
			// Set the transparency mode to OPAQUE
			SetBkMode(hMemDC, OPAQUE);
			// Show the message at the bottom center of the screen
			TextOut(hMemDC,(cr.right - cr.left) / 2 - (strlen(string) / 2) * 7,
					cr.bottom - 15, string, strlen(string));
		} // end if

		// Save the original pen and brush and select the Green ones into the DC
		HPEN original_pen = (HPEN)SelectObject(hMemDC, green_pen);
		HBRUSH original_brush = (HBRUSH)SelectObject(hMemDC, green_brush);

		// Draw the first ball to the screen
		ball1.show(hMemDC);

		// Select the Blue pen and brush into the DC
		SelectObject(hMemDC, blue_pen);
		SelectObject(hMemDC, blue_brush);

		// Draw the second ball to the screen
		ball2.show(hMemDC);

		// Select the original drawing tools back into the DC
		SelectObject(hMemDC, original_pen);
		SelectObject(hMemDC, original_brush);

		// Blit the new bitmap to the screen
		BitBlt(hDC, cr.left, cr.top, cr.right, cr.bottom, hMemDC, cr.left, cr.top, SRCCOPY);
		// Attach the old bitmap to the memory DC
		SelectObject(hMemDC, hOldBmp);
		// Delete the memory DC
		DeleteDC(hMemDC);
		// Delete the bitmap
		DeleteObject(hBmp);
		// Release the display DC
		ReleaseDC(hWnd, hDC); 

		// Wait until a frame phase has passed
		while((GetTickCount() - dwStartTime) < 33); 

	} // end while

	// Delete all of the pens and brushes that we created
	DeleteObject(green_pen);
	DeleteObject(green_brush);
	DeleteObject(blue_pen);
	DeleteObject(blue_brush);

	// Return to Windows
	return(msg.wParam);

} // end WinMain

////////////////////////////////////////////////////////////////////////////


