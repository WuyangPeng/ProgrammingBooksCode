#include "OGL_Wrapper.h"


HINSTANCE hInstance;		// holds the instance of the application
OGL_Wrapper ogl_wrapper;

bool active = true;			// false if the window gets minimized
bool fullscreen = true;		// set to fullscreen by default

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)				
{
	MSG	msg;								// Windows Message Structure
	BOOL done = FALSE;						// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode? (Recommended)", "Start FullScreen?",
		MB_YESNO|MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;					
	}
	// Create Our OpenGL Window
	if (!ogl_wrapper.CreateGLWindow("OpenGL Framework", (fullscreen ? 1024 :800),
								    (fullscreen ? 768 : 600), 32, fullscreen, hInstance, true))
	{
		return 0;							// Quit If Window Was Not Created
	}
	// Init our game
	ogl_wrapper.InitGame();

	// The following few lines of code are the only fix I've found for an inexplicable corruption of 
	// textures exclusive to a few machines running Windows XP.  I don't know how this fixes the 
	// problem, or even why there is one in the first place, but it works.
	ogl_wrapper.KillGLWindow(hInstance);				
	if (!ogl_wrapper.CreateGLWindow("OpenGL Framework", (fullscreen ? 1024 : 800),
							(fullscreen ? 768 : 600), 32, fullscreen, hInstance, false))
	{
		return 0;				
	}		   
	//////////////////////////////////////////////////////////////////////////////////////

	while(!done)							// Our loop
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)		// Have We Received A Quit Message?
			{
				done = TRUE;					
			}
			else							// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);		// Translate The Message
				DispatchMessage(&msg);		// Dispatch The Message
			}
		}
		else								// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)						// Program Active?
			{
				done = !ogl_wrapper.DrawGLScene();		// Draw The Scene
				SwapBuffers(ogl_wrapper.getHDC());		// Swap Buffers (Double Buffering)
			}

			if (GetAsyncKeyState(VK_F1))				// Is F1 Being Pressed?
			{
				ogl_wrapper.KillGLWindow(hInstance);	// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!ogl_wrapper.CreateGLWindow("OpenGL Framework", (fullscreen ? 1024 : 800),
										(fullscreen ? 768 : 600), 32, fullscreen, hInstance, false))
				{
					return 0;				// Quit If Window Was Not Created
				}
			}
		}
	}
	// Shutdown
	ogl_wrapper.KillGLWindow(hInstance);							// Kill The Window
	return (msg.wParam);					// Exit The Program
}



















