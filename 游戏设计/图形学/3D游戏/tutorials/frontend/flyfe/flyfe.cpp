#include <windows.h>
#include "..\..\lib\Fly3D.h"

char szTitle[100]="MyGame Title";
char szWindowClass[100]="MyGame";

// loads the menu level
void LoadLevel(HWND hWnd, HINSTANCE hInst)
{
	init_engine(hWnd,hInst,FLYAPPID_FLY);
	init_directx();
	init_render(FLY_RENDER_OPENGL);
	
	fullscreen=1;
	rend->SetFullScreen();
	
	flyengine->open_fly_file("menu/menu.fly");
	flyengine->init_texture_cache();
	InvalidateRect(hFlyWnd, 0, 0);
}

// main window message processing
LRESULT CALLBACK WinFunc (HWND hWnd, UINT mens, WPARAM wParam, LPARAM lParam)
{
	switch (mens)
	{
	// window resize
	case WM_SIZE:
		if (rend)
			rend->ResizeView(LOWORD(lParam),HIWORD(lParam));
	break;

	// window activation
	case WM_ACTIVATE:
		if (flyengine)
			if (LOWORD(wParam)==WA_INACTIVE || flyengine->con.mode)
				flyengine->noinput=1;
			else flyengine->noinput=0;
		break;

	// quit app
	case WM_DESTROY:
		PostQuitMessage (0);
	break;
	}

	return DefWindowProc (hWnd, mens, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lp, int nCmd)
{
	WNDCLASS wcl;
	MSG  msg;

	// register window class
	wcl.style			= CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc		= (WNDPROC)WinFunc;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hInstance		= hInst;
	wcl.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor			= 0;
	wcl.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcl.lpszMenuName	= NULL;
	wcl.lpszClassName	= szWindowClass;
	if (!RegisterClass (&wcl))
	{
	  MessageBox (0, "Can't register Window", "ERROR", MB_OK);
	  return 0;
	}

	// cerate main window
	HWND hWndMain = CreateWindowEx(
							0,
							szWindowClass,
							szTitle,
							WS_POPUP,
							0, 0,
							GetSystemMetrics( SM_CXSCREEN ),
							GetSystemMetrics( SM_CYSCREEN ),
							NULL,
							NULL,
							hInst,
							NULL 
						  );

	// load the level
	ShowWindow (hWndMain, SW_MAXIMIZE);
	LoadLevel (hWndMain, hInst);

	// main loop
	while (1) 
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) 
		{
			if (GetMessage(&msg, NULL, 0, 0)) 
				{
				if (flyengine && (
					(msg.message==WM_KEYDOWN && msg.wParam==VK_ESCAPE) ||
					(msg.message==WM_CHAR && flyengine->con.mode && msg.wParam!=VK_ESCAPE)))
						flyengine->con.key_press(msg.wParam);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
			else 
				{
				// frees engine, render, directx and quits app
				free_engine();
				free_render();
				free_directx();
				return TRUE;
				}
			}
		
		if (rend && flyengine)
			if (flyengine->step())	// simmulate
				rend->DrawView();   // draw view
		}
}

