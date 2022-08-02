// OpenGL.cpp - Source File for API Wrapper
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGL/gl.h"       // OpenGL header.
#include "OpenGL/glu.h"      // Another OpenGL header.

#include "EntityManager.h"

EntityManager* EMan = EntityManager::getInstance();

// Initialize the one static instance of the class
OpenGL* OpenGL::instance = 0;

/////////////////////////
// FUNCTION DEFINTIONS //
/////////////////////////
// Accessor to the one static instance of the class
OpenGL* OpenGL::getInstance()
{
	// Allocates a new EntityManager on the first call
	if (instance == NULL)
	{
		// CEANUP
		instance = new OpenGL();
		instance->hDC = NULL;
	}

	// Return the pointer to the static instance of the class
	return instance;
}

void OpenGL::DestroyOpenGL()
{
	delete instance;
}

bool OpenGL::InitializeGL(CDC *DeviceContext)
{
   // This function will first get the display area so we can allow OpenGL
   // to attach to it.  This is normally done in a way in the Create message entry
   // of the Win32 version.  We also call SetupPixelFormat() here too.
   hDC = DeviceContext;

   // Error checking.
	if(hDC == NULL)
		return false;

	if(SetupPixelFormat() == -1)
		return false;

   // Creates the rendering context.
	hRC = wglCreateContext(hDC->GetSafeHdc());
   
   // Error checking.
   if(hRC == 0)
     return false;

   // Create the rendering context.
	if(wglMakeCurrent(hDC->GetSafeHdc(), hRC) == FALSE)
		return false;

   // Lastly lets set up all the OpenGl info we will need (clear the screen to black
   // and enable depth testing).
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

   return true;
}
	
void OpenGL::Reshape(int width, int height)
{
	// Set the viewport.
	glViewport(0, 0, width, height);

    // Set the projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-width/2, width/2, -height/2, height/2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void OpenGL::DestroyGL()
{
	// Delete our objects just like in the Win32 version.  This is normally done is
   // some sort of destroy or close message in Win32.
	wglMakeCurrent(hDC->GetSafeHdc(), NULL);
	wglDeleteContext(hRC);

   // Delete this object since we allocated it before.
	if(hDC)
	   {
		   delete hDC;
         hDC = NULL;
	   }
}

int OpenGL::SetupPixelFormat()
{
   // Just like in the Win32 OpenGL tutorials we have to set up the SetupPixelFormat().
   // This is the same code from the Win32 tutorials.
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		32,                               // 32-bit color depth
		0, 0, 0, 0, 0, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		0,                                // no accumulation buffer
		0, 0, 0, 0,                       // accumulation bits ignored
		32,                               // 16-bit z-buffer
		0,                                // no stencil buffer
		0,                                // no auxiliary buffer
		PFD_MAIN_PLANE,                   // main layer
		0,                                // reserved
		0, 0, 0                           // layer masks ignored
	};

   int m_nPixelFormat = ChoosePixelFormat(hDC->GetSafeHdc(), &pfd);

   if(m_nPixelFormat == 0) return -1;

   return SetPixelFormat(hDC->GetSafeHdc(), m_nPixelFormat, &pfd);
}

void OpenGL::Render()
{
   if (hDC)
   {
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		glScalef(15.0, 15.0, 15.0);
		
		// Draw the Grid - each gridline is 30 units away from the previous
		glBegin(GL_LINES);
		
		glColor3d(1.0, 0.0, 0.0f);

		for (double x = -25.0; x < 26.0; x += 1.0)
		{
			glVertex3d(x, -25, 0.0); glVertex3d(x, 25, 0.0);
		}

		for (double y = -25.0; y < 25.0; y += 1.0)
		{
			glVertex3d(-25, y, 0.0); glVertex3d(25, y, 0.0);
		}
		glEnd();

		// Mark the origin of the grid
		glPointSize(10.0);

		glBegin(GL_POINTS);	
			glColor3d(1.0, 1.0, 1.0);
			glVertex3d(0.0, 0.0, 0.0);
		glEnd();

		glPointSize(1.0f);
		
		glPopMatrix();
		// Draw entities on the grid
		bool drawSelect = false;
		EMan->entitiesItr = EMan->entities.begin();
		for (int j = 0; j < EMan->entities.size(); j++)
		{
			(*EMan->entitiesItr)->drawEntity();
			// Draw the traces of each entity
			if ((*EMan->entitiesItr) == EMan->selected)
			{
				drawSelect = true;
			}
			else
				drawSelect = false;

			(*EMan->entitiesItr)->drawTraces(drawSelect);

			EMan->entitiesItr++;
		}

		// Swap buffers.
		SwapBuffers(hDC->GetSafeHdc());
   }
}