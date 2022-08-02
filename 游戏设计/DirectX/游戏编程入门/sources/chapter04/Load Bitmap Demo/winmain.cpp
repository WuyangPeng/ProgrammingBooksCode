/*
    Beginning Game Programming, Third Edition
    Chapter 4
    Load Bitmap program
*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <iostream>
using namespace std;

//program values
const string APPTITLE = "Load Bitmap Program";
const int SCREENW = 1024;
const int SCREENH = 768;

//key macro
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//Direct3D objects
LPDIRECT3D9 d3d = NULL; 
LPDIRECT3DDEVICE9 d3ddev = NULL; 
LPDIRECT3DSURFACE9 backbuffer = NULL;
LPDIRECT3DSURFACE9 surface = NULL;

bool gameover = false;

/**
 ** Game initialization function
 **/
bool Game_Init(HWND window)
{
    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d)
    {
        MessageBox(window, "Error initializing Direct3D", "Error", MB_OK);
        return false;
    }

    //set Direct3D presentation parameters
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = SCREENW;
    d3dpp.BackBufferHeight = SCREENH;
    d3dpp.hDeviceWindow = window;

    //create Direct3D device
    d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    if (!d3ddev)
    {
        MessageBox(window, "Error creating Direct3D device", "Error", MB_OK);
        return 0;
    }

    //clear the backbuffer to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
    
    //create surface
    HRESULT result = d3ddev->CreateOffscreenPlainSurface(
        SCREENW,                //width of the surface
        SCREENH,                //height of the surface
        D3DFMT_X8R8G8B8,    //surface format
        D3DPOOL_DEFAULT,    //memory pool to use
        &surface,           //pointer to the surface
        NULL);              //reserved (always NULL)

    if (!SUCCEEDED(result)) return false;

    //load surface from file into newly created surface
    result = D3DXLoadSurfaceFromFile(
        surface,            //destination surface
        NULL,               //destination palette
        NULL,               //destination rectangle
        "legotron.bmp",     //source filename
        NULL,               //source rectangle
        D3DX_DEFAULT,       //controls how image is filtered
        0,                  //for transparency (0 for none)
        NULL);              //source image info (usually NULL)

    //make sure file was loaded okay
    if (!SUCCEEDED(result)) return false;

    return true;
}

/**
 ** Game update function
 **/
void Game_Run(HWND hwnd)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

    //start rendering
    if (d3ddev->BeginScene())
    {
        //draw surface to the backbuffer
        d3ddev->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
     
        //stop rendering
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    //check for escape key (to exit program)
    if (KEY_DOWN(VK_ESCAPE))
        PostMessage(hwnd, WM_DESTROY, 0, 0);
}

/**
 ** Game shutdown function
 **/
void Game_End(HWND hwnd)
{
    if (surface) surface->Release();
    if (d3ddev) d3ddev->Release();
    if (d3d) d3d->Release();
}

/**
 ** Windows event handling function
 **/
LRESULT WINAPI WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            gameover = true;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

/**
 ** Windows entry point function
 **/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //initialize window settings
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra	 = 0;
    wc.cbWndExtra	 = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = APPTITLE.c_str();
    wc.hIconSm       = NULL;
    RegisterClassEx(&wc);

    //create a new window
    HWND window = CreateWindow( APPTITLE.c_str(), APPTITLE.c_str(),
       WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
       SCREENW, SCREENH, NULL, NULL, hInstance, NULL);

    //was there an error creating the window?
    if (window == 0) return 0;

    //display the window
    ShowWindow(window, nCmdShow);
    UpdateWindow(window);
	
	//initialize the game
    if (!Game_Init(window)) return 0;


    // main message loop
	MSG message;
	while (!gameover)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
	    {
		    TranslateMessage(&message);
		    DispatchMessage(&message);
	    }

        //process game loop 
        Game_Run(window);
    }

	return message.wParam;
}

