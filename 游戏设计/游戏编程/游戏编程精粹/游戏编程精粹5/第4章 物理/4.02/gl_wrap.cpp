//----------------------------------------------------------------------------
//
//gl_wrap.cpp
//
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Inclusions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#include "gl_wrap.h"

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Definitions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

#define GL_PER_ANGLE 45.0f
#define GL_END_DIST 100.0f

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Structures
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Class Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Private Function Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Private Vars
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: External Function Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

PIXELFORMATDESCRIPTOR gl_get_pfd(int bpp)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof (PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bpp,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,
		0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	return pfd;
}

bool gl_create_wnd( const HWND & hWnd, const HDC & hDC, HGLRC & hRC)
{
	hRC = wglCreateContext(hDC);
	if(!hRC)
		return false;

	if(wglMakeCurrent(hDC,hRC) == FALSE)
	{
		wglDeleteContext(hRC);
		hRC = 0;
		return false;
	}
	
	return true;
}

void gl_resize_wnd(GLsizei width, GLsizei height)
{
	if(!width || !height)
		return;

	glViewport( 0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( GL_PER_ANGLE, (GLfloat)width/(GLfloat)height, 0.01f, GL_END_DIST);
	glMatrixMode(GL_MODELVIEW);
}

void gl_destroy_wnd( const HWND & hWnd, const HDC & hDC, HGLRC & hRC)
{
	if(hWnd && hDC)
	{
		wglMakeCurrent(hDC,0);
		if(hRC)
		{
			wglDeleteContext(hRC);
			hRC = 0;
		}
	}
}

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: External Class Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Internal Function Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    Source :: Internal Class Implementation
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//----------------------------------------------------------------------------
//gl_wrap.cpp
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------
