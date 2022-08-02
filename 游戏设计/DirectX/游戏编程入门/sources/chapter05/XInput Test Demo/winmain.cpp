/*
    Beginning Game Programming, Third Edition
    Chapter 5
    XInput_Test Program
*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <xinput.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"xinput.lib")

//application title
const string APPTITLE = "XInput Test Program";

//macro to read the keyboard 
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//screen resolution
const int SCREENW = 640;
const int SCREENH = 480;

//Direct3D objects
LPDIRECT3D9 d3d = NULL; 
LPDIRECT3DDEVICE9 d3ddev = NULL; 

bool gameover = false;


/**
 ** Initializes XInput and any connected controllers
 **/ 
bool XInput_Init(int contNum = 0)
{
    XINPUT_CAPABILITIES caps;
    ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
    XInputGetCapabilities(contNum, XINPUT_FLAG_GAMEPAD, &caps);
    if (caps.Type != XINPUT_DEVTYPE_GAMEPAD) return false;

    return true;
}

/**
 ** Causes the controller to vibrate
 **/
void XInput_Vibrate(int contNum = 0, int left = 65535, int right = 65535)
{
    XINPUT_VIBRATION vibration;
    ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right; 
    XInputSetState( contNum, &vibration );
}

/**
 ** Checks the state of the controller
 **/
void XInput_Update()
{
    for (int i=0; i< 4; i++ )
    {
        XINPUT_STATE state;
        ZeroMemory( &state, sizeof(XINPUT_STATE) );

        //get the state of the controller 
        DWORD result = XInputGetState( i, &state );

        if( result == 0 )
        { 
            // controller is connected 
            if (state.Gamepad.bLeftTrigger)
                MessageBox(0, "Left Trigger", "Controller", 0);

            else if (state.Gamepad.bRightTrigger)
                MessageBox(0, "Right Trigger", "Controller", 0);

            else if (state.Gamepad.sThumbLX < -10000 || state.Gamepad.sThumbLX > 10000)
                MessageBox(0, "Left Thumb Stick", "Controller", 0);

            else if (state.Gamepad.sThumbRX < -10000 || state.Gamepad.sThumbRX > 10000)
                MessageBox(0, "Right Thumb Stick", "Controller", 0);
            
            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
                MessageBox(0, "DPAD Up", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
                MessageBox(0, "DPAD Down", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
                MessageBox(0, "DPAD Left", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
                MessageBox(0, "DPAD Right", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
                MessageBox(0, "Start", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
                MessageBox(0, "Left Thumb", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
                MessageBox(0, "Right Thumb", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
                MessageBox(0, "Left Shoulder", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
                MessageBox(0, "Right Shoulder", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
                XInput_Vibrate(0, 65535, 65535);
                MessageBox(0, "A", "Controller", 0);
            }

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                XInput_Vibrate(0, 0, 0);
                MessageBox(0, "B", "Controller", 0);
            }

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
                MessageBox(0, "X", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
                MessageBox(0, "Y", "Controller", 0);

            else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
                gameover = true;

        }
        else {
            // controller is not connected 
        }
    }
}

/**
 ** Game initialization
 **/
bool Game_Init(HWND hwnd)
{
    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d == NULL)
    {
        MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
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
    d3dpp.hDeviceWindow = hwnd;

    //create Direct3D device
    d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    if (!d3ddev)
    {
        MessageBox(hwnd, "Error creating Direct3D device", "Error", MB_OK);
        return false;
    }

    //initialize XInput
    XInput_Init();


    return true;
}

/**
 ** Game update
 **/
void Game_Run(HWND hwnd)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //clear the backbuffer to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,150), 1.0f, 0);
    
    //start rendering
    if (d3ddev->BeginScene())
    {
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    //check for escape key (to exit program)
    if (KEY_DOWN(VK_ESCAPE))
        PostMessage(hwnd, WM_DESTROY, 0, 0);

    XInput_Update();
}

/**
 ** Game shutdown
 **/

void Game_End(HWND hwnd)
{
    if (d3ddev) d3ddev->Release();
    if (d3d) d3d->Release();
}

/**
 ** Windows event handler
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
 ** Windows entry point
 **/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //create the window class structure
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = APPTITLE.c_str();
    wc.hIconSm       = NULL;
    RegisterClassEx(&wc);

    //create a new window
    HWND window = CreateWindow(APPTITLE.c_str(), APPTITLE.c_str(), 
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

        Game_Run(window);
    }

    Game_End(window);

    return message.wParam;
}

