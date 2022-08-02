// Include the OpenGL libraries.  These two lines are equivalent to going into Project->Settings,
// clicking on the Link tab, and then adding "glu32.lib" and "opengl32.lib" to the Object/library modules
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#include "resource.h"

// For creating a console and redirecting cout in Win32 applications
#include "redirectcon.h"
// High resolution timer class: written by Richard S. Wright
#include "Stopwatch.h"
// Class for drawing fonts to the screen using OpenGL Display Lists
#include "Ogl_Draw.h"

#include "Tank.h"
#include "ProjectileManager.h"
#include "ParticleEngine.h"
#include "Wall.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <ctime>
#include <string>
#include <iostream>
using namespace std;

/***********/
/* GLOBALS */
/***********/

/* Game entities */
Wall theWall;													// The wall objects
Wall theGround;													// The ground objects
Tank canon[2];													// The canons

/* Game State */
bool pause = false;												// Is the game paused?
BYTE turn = 0;													// Who's turn is it
BYTE prevturn = 1;												// Who had the previous turn

/* Rendering */
int screenx, screeny;											// The screen resolution
bool drawBounds = false;										// Should we draw the bounding volumes?
Ogl_Draw oglFonts;												// The font renderer

/* HUD */ 
float pos_x_P1 = 0.0f, pos_y_P1, pos_x_P2, pos_y_P2;			// Current position of the canonball
double T_time_P1 = 0, T_time_P2;								// Elapsed time since firing
float max_height_P1 = 0.0f, max_height_P2;						// The maximum height the canonball has reached
float launch_posx_P1 = 0.0f, launch_posy_P1, launch_posx_P2, 
			launch_posy_P2;										// Where is the end of the canon barrel at

/* Misc */
HWND hWndDlg;													// Handle to the Dialog Box
SS_StopWatch stopWatch;											// The high resolution timers
SS_StopWatch timer;												// The high resolution timers

/**************/
/* PROTOTYPES */
/**************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OrthoMode(float left, float top, float right, float bottom);
// Function written by Richard S. Wright
BYTE *gltLoadTGA(const string &szFile, int *nWidth, int *nHeight);

/* Inlines */ 
inline void ChangeTurn(void)
{
	if (turn == 0)
	{
		turn = 1;
		T_time_P2 = 0.0f;
		pos_x_P2 = pos_y_P2 = 0.0f;
	}
	else if (turn == 1)
	{
		turn = 0;
		T_time_P1 = 0.0f;
		pos_x_P1 = pos_y_P1 = 0.0f;
	}
}

// Basic Win32 Entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));

	MSG msg;		// Window message
	WNDCLASS wc;	// Define the charactistics of the window
	HWND hWnd;		// Handle to created window

	HWND desktopWnd;
	HDC desktopDC;

	// Define class for Windows
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Canon Physics";

	if(!RegisterClass(&wc))
	{
		MessageBox(NULL, "Window Class register failure", NULL, MB_OK);
		return FALSE;
	}

	// Get a handle to the desktop window
	desktopWnd = GetDesktopWindow();
	// Get a handle to the desktop's device context
	desktopDC = GetDC(desktopWnd);

	// Store the screen resolution
	screenx = GetDeviceCaps(desktopDC, HORZRES);
	screeny = GetDeviceCaps(desktopDC, VERTRES);

	// Release the desktop's device context because OpenGL is about to take over.
	ReleaseDC(desktopWnd, desktopDC);

	// Create the Window
	hWnd = CreateWindow(wc.lpszClassName,
						"Canon Physics",
						WS_CLIPCHILDREN | WS_CLIPSIBLINGS | 
						WS_POPUP,
						0, 0,
						screenx, screeny,
						NULL, NULL, hInstance, NULL);

	// If window not created, stop!!!
	if (!hWnd)
		return FALSE;

	hWndDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogProc);
	if (!hWndDlg)
		return FALSE;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// Windows message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// Windows callback function
//
// Gets called whenever a message is sent to this window and then
// processes that message.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static HGLRC hrc;
	static float nWidth;
	static float nHeight;

	// Keep track of the frames per second.
	static double fps;

	switch(message)	
	{
		case WM_CREATE:
		{
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				32, // bit depth
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				16, // z-buffer depth
				0, 0, 0, 0, 0, 0, 0,
			};

			// Get device context only once.
			hdc = GetDC(hWnd);

			int nPixelFormat = ChoosePixelFormat(hdc, &pfd);
			SetPixelFormat(hdc, nPixelFormat, &pfd);

			// Create the OpenGL Rendering Context.
			hrc = wglCreateContext(hdc);
			wglMakeCurrent(hdc, hrc);

			// Set the clear color.
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glEnable(GL_TEXTURE_2D);
			glLineWidth(3.0f);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);

			// Create our DEBUG window.
			con::RedirectIOToConsole("Canon Physics Demo: Debug Window");
			cout << "Authors: Michael Fawcett and Mike Wigand\n";

			oglFonts.ChooseFont(hdc, 16, "Courier New");

			int width, height;
			BYTE *pData = gltLoadTGA("Images\\greentank.tga", &width, &height);
			canon[0].SetTexture(pData, width, height);
			canon[0].SetBarrelColor(RGB(4, 182, 0));
			canon[0].SetAngle(90);

			pData = gltLoadTGA("Images\\redtank.tga", &width, &height);
			canon[1].SetTexture(pData, width, height);
			canon[1].SetBarrelColor(RGB(182, 0, 0));
			canon[1].SetAngle(90);

			theWall.alive = false;
			pData = gltLoadTGA("Images\\brick wall.tga", &width, &height);
			theWall.SetTexture(pData, width, height);

			theGround.alive = true;
			theGround.SetBounds(0, 1, 50, 0);
			pData = gltLoadTGA("Images\\dirt.tga", &width, &height);
			theGround.SetTexture(pData, width, height);

			canon[0].Place(1, 1);
			canon[1].Place(48, 1);
			theWall.Place(0, 0);
			theGround.Place(0, 0);
		}
		break;
			
		case WM_DESTROY:
			DestroyWindow(hWndDlg);
			// Give back the OpenGL device.
			wglMakeCurrent(hdc, NULL);
			wglDeleteContext(hrc);

			// Give back the GDI device.
			ReleaseDC(hWnd, hdc);

			// Delete the console window.
			FreeConsole();

			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				// Toggle bounding bounds
				case VK_F2:
					drawBounds = !drawBounds;
					break;

				// Exit the program by sending the WM_DESTROY message
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					break;

				// Force up
				case VK_PRIOR:
					canon[turn].ForceUp(10.0f);
					break;

				case VK_UP:
					canon[turn].ForceUp();
					break;

				case VK_NEXT:
					canon[turn].ForceDown(10.0f);
					break;

				// Force down
				case VK_DOWN:
					canon[turn].ForceDown();
					break;

				// Mass up
				case 'Q':
					canon[turn].MassUp();
					break;

				// Mass down
				case 'A':
					canon[turn].MassDown();
					break;

				// Angle up
				case VK_LEFT:
					canon[turn].RotateLeft();
					break;

				// Angle down
				case VK_RIGHT:
					canon[turn].RotateRight();
					break;

				// Fire the projectile
				case VK_SPACE:
					if (turn != prevturn)
					{
						canon[turn].FireProjectile();
						prevturn = turn;
					}
					break;

				// Debug for changing turns
				case VK_F1:
					ShowWindow(hWndDlg, SW_NORMAL);
					break;

				// Pause the app
				case 'P':
					pause = pause ? false : true;
					break;

			}
			break;

		case WM_PAINT:
		{
				// Clear the buffers
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();

				// left, top, right, bottom
				OrthoMode(0, 37.5, 50, 0);

				// Draw the canons
				canon[0].Render();
				canon[1].Render();

				// Draw the wall
				theWall.Render();
				theGround.Render();

				// Pauses the update if the Dialog Box is Visible
				if (!IsWindowVisible(hWndDlg))
				{
					ProjectileManager::instance().Update();
					ParticleEngine::instance().Update();
				}

				ProjectileManager::instance().Render();
				ParticleEngine::instance().Render();
			 
				glDisable(GL_TEXTURE_2D);

				glColor3f(1.0f, 1.0f, 1.0f);
				glLineWidth(1.0f);
				glBegin(GL_LINES);

				for (int i = 0; i <= 50; i += 5)
				{
					glVertex3f((GLfloat)i, 0.0f, -0.1f);
					glVertex3f((GLfloat)i, 1.0f, -0.1f);
				}
				for (i = 1; i < 50; i++)
				{
					glVertex3f((GLfloat)i, 0.0f, -0.1f);
					glVertex3f((GLfloat)i, 0.3f, -0.1f);
				}

				glEnd();
				glLineWidth(3.0f);

				// Print out all of the stats
				// *** (The OglDraw class uses Ortho2D mode with 0, 0, 640, 480) ***
				glColor3f(1.0f, 1.0f, 1.0f);
				// Display Player 1 stats
				oglFonts.TextOut(10, 10, "Angle: %.2f°", canon[0].GetAngle());
				oglFonts.TextOut(10, 20, "Force: %.2f N", canon[0].GetForce());
				oglFonts.TextOut(10, 30, "Mass: %.2f Kg", canon[0].GetMass());
				oglFonts.TextOut(10, 40, "i_Velocity: %.2f m/s", canon[0].GetVelocity());
				oglFonts.TextOut(10, 50, "Launch Pos_x: %.2f", launch_posx_P1);
				oglFonts.TextOut(10, 60, "Launch Pos_y: %.2f", launch_posy_P1);
				
				oglFonts.TextOut(10, 80, "Pos_x: %.2f", pos_x_P1);
				oglFonts.TextOut(10, 90, "Pos_y: %.2f", pos_y_P1);
				oglFonts.TextOut(10, 100, "Time: %.2f", T_time_P1);
				oglFonts.TextOut(10, 110, "Max Height: %.2f", max_height_P1);
				
				// Display Player 2 stats
				oglFonts.TextOut(500, 10, "Angle: %.2f", canon[1].GetAngle());
				oglFonts.TextOut(500, 20, "Force: %.2f N", canon[1].GetForce());
				oglFonts.TextOut(500, 30, "Mass: %.2f Kg", canon[1].GetMass());
				oglFonts.TextOut(500, 40, "i_Velocity: %.2f m/s", canon[1].GetVelocity());
				oglFonts.TextOut(500, 50, "Launch Pos_x: %.2f", launch_posx_P2);
				oglFonts.TextOut(500, 60, "Launch Pos_y: %.2f", launch_posy_P2);

				oglFonts.TextOut(500, 80, "Pos_x: %.2f", pos_x_P2);
				oglFonts.TextOut(500, 90, "Pos_y: %.2f", pos_y_P2);
				oglFonts.TextOut(500, 100, "Time: %.2f", T_time_P2);
				oglFonts.TextOut(500, 110,"Max Height: %.2f", max_height_P2);

				// Display controls
				oglFonts.TextOut(260, 10, "FPS: %.2f", fps);
				oglFonts.TextOut(260, 20, "ground elasticity: %.1f", theGround.elasticity);
				oglFonts.TextOut(260, 30, "wall elasticity: %.1f", theWall.elasticity);
				oglFonts.TextOut(260, 40, "'P' - Pause");
				oglFonts.TextOut(260, 50, "'left & right arrow' - change angle");
				oglFonts.TextOut(260, 60, "'up & down arrow' - change force");
				oglFonts.TextOut(260, 70, "'Q & A' - change weight of canonball");
				oglFonts.TextOut(260, 80, "'SPACE' - shoot the canonball");
				
				// Displays if the app is paused
				if (pause)
					oglFonts.TextOut(280, 150, "PAUSED");
				else
					oglFonts.TextOut(280, 150, "Player %i", (turn + 1));


				// Print out the tick marks along the bottom of the screen
				for (i = 0; i < 50; i++)
				{
					if (!(i%5))
						oglFonts.TextOutOrtho(0, 50, 50, 0, i + 0.175f, 49.25f, "%i", i);
				}

				glEnable(GL_TEXTURE_2D);

				// Swap the buffers.
				SwapBuffers(hdc);

				// Calculate FPS and print it out every quarter second
				if (timer.GetElapsedSeconds() > 0.25f)
				{
					fps = 1.0 / stopWatch.GetElapsedSeconds();
					timer.Reset();
				}
				stopWatch.Reset();

				break;
		}
		case WM_SIZE:
		{
			nWidth = LOWORD(lParam);
			nHeight = HIWORD(lParam);

			// Map the OpenGL coordinates.
			glViewport(0, 0, (int)nWidth, (int)nHeight);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			gluPerspective(45.0f, nWidth/nHeight, 0.1f, 1000.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}			
		break;

		// We're not handling the message so pass it on and let Windows
		// do whatever the default action is.
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0L;
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD checked;

	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			// They're disabled at first
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_LEFT), EM_SETREADONLY, WPARAM(TRUE), 0);
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_WIDTH), EM_SETREADONLY, WPARAM(TRUE), 0);
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_HEIGHT), EM_SETREADONLY, WPARAM(TRUE), 0);
			// Only let them enter in 2 digits
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_LEFT), EM_LIMITTEXT, WPARAM(2), 0);
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_WIDTH), EM_LIMITTEXT, WPARAM(2), 0);
			SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_HEIGHT), EM_LIMITTEXT, WPARAM(2), 0);
			
			char buffer[] = "1.0";
			SetDlgItemText(hwndDlg, IDC_GE, buffer);
			SetDlgItemText(hwndDlg, IDC_WE, buffer);
			SetDlgItemText(hwndDlg, IDC_BL1, buffer);
			SetDlgItemText(hwndDlg, IDC_BL2, buffer);
			return TRUE;
		}
		case WM_COMMAND:
		{
			int msg = LOWORD(wParam);
			switch (msg)
			{
				case IDC_WALL_CHECK:
				{
					checked = SendMessage(GetDlgItem(hwndDlg, IDC_WALL_CHECK), BM_GETCHECK, 0, 0);

					if (checked)
					{
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_LEFT), EM_SETREADONLY, WPARAM(FALSE), 0);
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_WIDTH), EM_SETREADONLY, WPARAM(FALSE), 0);
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_HEIGHT), EM_SETREADONLY, WPARAM(FALSE), 0);
					}
					else
					{
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_LEFT), EM_SETREADONLY, WPARAM(TRUE), 0);
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_WIDTH), EM_SETREADONLY, WPARAM(TRUE), 0);
						SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_HEIGHT), EM_SETREADONLY, WPARAM(TRUE), 0);
					}
					break;
				}

				case IDOK:
				{
					char buffer[10];
					float left, top, right, bottom;

					theWall.alive = true;

					left = (float)GetDlgItemInt(hwndDlg, IDC_EDIT_LEFT, NULL, FALSE);
					right = left + (float)GetDlgItemInt(hwndDlg, IDC_EDIT_WIDTH, NULL, FALSE);
					bottom = 0;
					top = (float)GetDlgItemInt(hwndDlg, IDC_EDIT_HEIGHT, NULL, FALSE);
					theWall.SetBounds(left, top, right, bottom);

					GetDlgItemText(hwndDlg, IDC_GE, buffer, 10);
					theGround.elasticity = (float)atof(buffer);

					GetDlgItemText(hwndDlg, IDC_WE, buffer, 10);
					theWall.elasticity = (float)atof(buffer);

					GetDlgItemText(hwndDlg, IDC_BL1, buffer, 10);
					canon[0].SetBarrelLength((float)atof(buffer));

					GetDlgItemText(hwndDlg, IDC_BL2, buffer, 10);
					canon[1].SetBarrelLength((float)atof(buffer));

					ShowWindow(hwndDlg, SW_HIDE);
					ProjectileManager::instance().Reset();
					theWall.alive = checked ? true : false;

					if (turn == prevturn)
					{
						ChangeTurn();
					}
					break;
				}
				case IDCANCEL:
					ShowWindow(hwndDlg, SW_HIDE);
					ProjectileManager::instance().Reset();
					ChangeTurn();
					break;
			}

			break;
		}
	}

	return FALSE;
}

void OrthoMode(float left, float top, float right, float bottom)
{
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();								
	glOrtho(left, right, bottom, top, 0, 1);
	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();										
}

BYTE *gltLoadTGA(const string &szFile, int *nWidth, int *nHeight)
{
	HANDLE hFileHandle;
	unsigned long lBitSize = 0;
	short width, height;

	// Open the Bitmap file
	hFileHandle = CreateFile(szFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	// Check for open failure (most likely file does not exist).
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	// File is Open. Read in bitmap header information
	unsigned char caTGAHeader[18];

	DWORD dwBytes;
	ReadFile(hFileHandle,caTGAHeader,18, &dwBytes,NULL);

	// Check for a couple of simple errors	
	if(dwBytes != 18)
		return FALSE;

	// Save the size and dimensions of the bitmap
	memcpy(&width, &caTGAHeader[12], 2);
	memcpy(&height, &caTGAHeader[14], 2);

	lBitSize = width * height * 4;
	*nWidth = width;
	*nHeight = height;
	BYTE *pBytes = new BYTE[lBitSize];

	// Read in the bitmap bits
	ReadFile(hFileHandle,pBytes,lBitSize,&dwBytes,NULL);

	// Close the bitmap file now that we have all the data we need
	CloseHandle(hFileHandle);

	// Make RGB
	for(int i = 0; i < (int)lBitSize; i+= 4)
	{
		// Do the swap
		BYTE bByte = pBytes[i];
		pBytes[i] = pBytes[i+2];
		pBytes[i+2] = bByte;
	}

	return pBytes;
}
