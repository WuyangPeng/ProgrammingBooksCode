// OGL_Wrapper.h: interface for the OGL_Wrapper class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OGL_WRAPPER_H_
#define _OGL_WRAPPER_H_

#include <windows.h>
#include <gltools.h>
//#pragma comment(lib, "glTools.lib")

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
//#include <stdio.h>

//#pragma comment(lib, "openGL32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glAux.lib")	

#include "Timer.h"
#include "Ball.h"
#include "3ds.h"
#include "SoundClass.h"

class OGL_Wrapper  
{
private:
	HGLRC hRC;			// handle to our permanent OpenGL rendering context
	HDC hDC;			// handle to our private GDI device context
	HWND hWnd;			// handle to our window
	bool fullscreen;	// true if running in fullscreen
	Ball ball[16];		// our 16 balls
	Ball col;			// the transparent ball used for prediction
	float radius;		// the radius of the balls
	SoundClass soundPlayer;	  // Our DirectSound class

public:
	// constructor, initialization
	OGL_Wrapper()
	{
		hRC = NULL;
		hDC = NULL;
		hWnd = NULL;
		frames = 0;
	}
	// Destructor
	virtual ~OGL_Wrapper() { }

	Timer timer;		// Instances of our timer class used to for camera movement and 		
	Timer lastframe;	// frame-rate calculation
	int frames;			// Holds our FPS

	static GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	int InitGL(bool firstLoad);
	GLvoid InitGame(GLvoid);
	GLvoid ShutdownGame();
	int DrawGLScene(bool true_render = true);
	GLvoid KillGLWindow(HINSTANCE hInstance);
	BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag, 
						HINSTANCE hInstance, bool firstLoad/*, WNDPROC WndProc*/);

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	inline HGLRC getHRC() { return hRC; };
	inline HDC getHDC() { return hDC; };
	inline HWND getHWND() { return hWnd; };

	void DrawSphere(float radius);
	void DrawFloor(void);

	void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);
	void CreateTargaTexture(UINT textureArray[], LPSTR strFileName, int textureID);
	int RetrieveObjectID(int x, int y);
	void drawModel(t3DModel &model, UINT *text);
	void PerspectiveMode();
	void OrthoMode(int left, int top, int right, int bottom);

};

#endif
