#define INITGUID

#define APPNAME "Flight Sim"

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "mmsystem.h"


#include "d3dstuff.h"
#include "Physics.h"

#define		RENDER_FRAME_COUNT	330

// Global Variables:
HINSTANCE	hInst; // current instance
int			nShowCmd; // current show command	
char		szAppName[] = APPNAME; // The name of this application
char		szTitle[]   = APPNAME; // The title bar text
HWND		hTheMainWindow;

DWORD		OldTime, NewTime;
float		dt;

BOOL		Initialized = false;
float		TotalTime = 0;
int			FrameCounter = RENDER_FRAME_COUNT;

int			Configuration = 2;


// Foward declarations of functions included in this code module:
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void	NullEvent(void);
BOOL IsKeyDown(short KeyCode);

// externals
extern	RigidBody	Bodies[];
extern	d3dInfo	D3D;
extern	LPDIRECT3DRMWINDEVICE WinDev;

//----------------------------------------------------------------------------------------------------//

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HANDLE hAccelTable;		

	if (!hPrevInstance) {
		// Perform instance initialization:
		if (!InitApplication(hInstance)) {
			return (FALSE);
		}
	}

	// Perform application initialization:	
	if (!InitInstance(hInstance, nCmdShow)) {
		return (FALSE);
	}

	hAccelTable = LoadAccelerators (hInstance, szAppName);

	OldTime = timeGetTime();
	NewTime = OldTime;
	// Main message loop:
	while (1) {		

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		
		if(Initialized)
			NullEvent();

	}

	return (msg.wParam);

	lpCmdLine; // This will prevent 'unused formal parameter' warnings
}

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;
    HWND      hwnd;

    hwnd = FindWindow (szAppName, NULL);
    if (hwnd) {
        if (IsIconic(hwnd)) {
            ShowWindow(hwnd, SW_RESTORE);
        }
        SetForegroundWindow (hwnd);

        return FALSE;
        }

        wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc   = (WNDPROC)WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = NULL;//LoadIcon (hInstance, MAKEINTRESOURCE(IDI_MAINICON));
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);//NULL
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//(HBRUSH)(COLOR_WINDOW+1);

		wc.lpszMenuName = NULL; //MAKEINTRESOURCE(IDR_MAINMENU);//"MAINMENU";
		
		wc.lpszClassName = szAppName;
        
		return RegisterClass(&wc);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
			
	hInst = hInstance;

	nShowCmd = nCmdShow;	

    hTheMainWindow = CreateWindow(	szAppName, 
									szTitle,
									WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
									0, 0, 640, 480,
									NULL, NULL, hInst, NULL);

	if (!CreateD3DRMObject())
		return (FALSE);

    if (!CreateD3DRMClipperObject(hTheMainWindow))
		return (FALSE);	

	if (!CreateViewPort(hTheMainWindow))
		return (FALSE);
	
	ShowWindow(hTheMainWindow, nCmdShow);
    UpdateWindow(hTheMainWindow);

	InitializeObjects(Configuration);
	Initialized = true;
	TotalTime = 0;
	SetCamera3();


	return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	int			wmId, wmEvent;   		
	BOOL		validmenu = FALSE;	
	int			selection =0;
	PAINTSTRUCT			ps;
	HDC			pDC;
	WPARAM		key;
	
	switch (message) {
		case WM_ACTIVATE:
			if (SUCCEEDED(D3D.Device->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &WinDev)))
        		{   
					if (FAILED(WinDev->HandleActivate(wParam)))					
               			WinDev->Release();
				}

			

			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			/*switch(wmId) {

			
			}*/
			return (0);
			break;

		case WM_DESTROY:
			CleanUp();
			PostQuitMessage(0);
			break;

		case	WM_KEYUP:
			break;

		case WM_KEYDOWN:
			key = (int) wParam;

			if (key == 0x31) // 1
				SetCamera1();

			if (key == 0x32) // 2
				SetCamera2();

			if (key == 0x33) // 3
				SetCamera3();

			break;

		case WM_PAINT:			
				pDC = BeginPaint(hTheMainWindow, (LPPAINTSTRUCT) &ps);

				if (SUCCEEDED(D3D.Device->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &WinDev)))
        		{   
					if (FAILED(WinDev->HandlePaint(ps.hdc)))					
               			WinDev->Release();
				}
				

				EndPaint(hTheMainWindow, (LPPAINTSTRUCT) &ps);				
				return (0);
			break;
        
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

void	NullEvent(void)
{	
	Vector	vz, vx;
	int		i;
	char	buf[256];
	char	s[256];


	/*NewTime = timeGetTime();	
	dt = (float) (NewTime - OldTime)/1000.0f;
	OldTime = NewTime;
	
	if (dt > (0.001f))
		dt = (0.001f);*/

	dt = 0.0001f;

	
	TotalTime += dt;
	if(TotalTime > 2.0f) 
	{
		Configuration++;
		if(Configuration >= 3) Configuration = 0; 
		
		InitializeObjects(Configuration);				
		TotalTime = 0.0f;
		FrameCounter = 0;
	}

	StepSimulation(dt);
	
	if(FrameCounter >= RENDER_FRAME_COUNT)
	{			
		// Direct3D x = - our y
		// Direct3D y = our z
		// Direct3D z = our x
		SetCameraPosition(-Bodies[0].vPosition.y, Bodies[0].vPosition.z, Bodies[0].vPosition.x);

		vz = GetBodyZAxisVector(0); // pointing up in our coordinate system
		vx = GetBodyXAxisVector(0); // pointing forward in our coordinate system
		SetCameraOrientation(	-vx.y, vx.z, vx.x, 
							-vz.y, vz.z, vz.x);
		for(i=1; i<NUMBODIES; i++)
		{
			SetBodyPosition(i-1, -Bodies[i].vPosition.y, Bodies[i].vPosition.z, Bodies[i].vPosition.x);

			vz = GetBodyZAxisVector(i); // pointing up in our coordinate system
			vx = GetBodyXAxisVector(i); // pointing forward in our coordinate system
			SetBodyOrientation(i-1,	-vx.y, vx.z, vx.x, 
									-vz.y, vz.z, vz.x);
		}

		Render();
		FrameCounter = 0;	
		
		sprintf( buf, "TotalTime= %.3f ; ", TotalTime);
		strcpy(s, buf);
		SetWindowText(hTheMainWindow, s);
		
	} else
		FrameCounter++;

	

}

BOOL IsKeyDown(short KeyCode)
{

	SHORT	retval;

	retval = GetAsyncKeyState(KeyCode);

	if (HIBYTE(retval))
		return TRUE;

	return FALSE;
}
