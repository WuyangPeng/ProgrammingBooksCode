/**
    Beginning Game Programming, Third Edition
    Chapter 2
    GameLoop project
**/

#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

const string APPTITLE = "Game Loop";
HWND window;
HDC device;
bool gameover = false;


/**
 ** Loads and draws a bitmap from a file and then frees the memory
 **/
void DrawBitmap(char *filename, int x, int y)
{
    //load the bitmap image
    HBITMAP image = (HBITMAP)LoadImage(0,"c.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //read the bitmap's properties
    BITMAP bm;
    GetObject(image, sizeof(BITMAP), &bm);

    //create a device context for the bitmap
    HDC hdcImage = CreateCompatibleDC(device);
    SelectObject(hdcImage, image);

    //draw the bitmap to the window (bit block transfer)
    BitBlt( 
        device,                  //destination device context
        x, y,                    //x,y location on destination
        bm.bmWidth, bm.bmHeight, //width,height of source bitmap
        hdcImage,                  //source bitmap device context
        0, 0,                    //start x,y on source bitmap
        SRCCOPY);                //blit method

    //delete the device context and bitmap
    DeleteDC(hdcImage);
    DeleteObject((HBITMAP)image);
}

/**
 ** Startup and loading code goes here
 **/
bool Game_Init()
{
    //start up the random number generator
    srand(time(NULL));

    return 1;
}

/**
 ** Update function called from inside game loop
 **/
void Game_Run()
{
    if (gameover == true) return;

    //get the drawing surface
    RECT rect;
    GetClientRect(window, &rect);

    //draw bitmap at random location
    int x = rand() % (rect.right - rect.left);
    int y = rand() % (rect.bottom - rect.top);
    DrawBitmap("c.bmp", x, y);
}

/**
 ** Shutdown code
 **/
void Game_End()
{
    //free the device
    ReleaseDC(window, device);
}

/**
 ** Window callback function
 **/
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
    {
        case WM_DESTROY:
            gameover = true;
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 ** MyRegiserClass function sets program window properties
 **/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //create the window class structure
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 

    //fill the struct with info
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = APPTITLE.c_str();
    wc.hIconSm       = NULL;

    //set up the window with the class info
    return RegisterClassEx(&wc);
}

/**
 ** Helper function to create the window and refresh it
 **/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    //create a new window
    window = CreateWindow(
       APPTITLE.c_str(),              //window class
       APPTITLE.c_str(),              //title bar
       WS_OVERLAPPEDWINDOW,   //window style
       CW_USEDEFAULT,         //x position of window
       CW_USEDEFAULT,         //y position of window
       640,                   //width of the window
       480,                   //height of the window
       NULL,                  //parent window
       NULL,                  //menu
       hInstance,             //application instance
       NULL);                 //window parameters

    //was there an error creating the window?
    if (window == 0) return 0;

    //display the window
    ShowWindow(window, nCmdShow);
    UpdateWindow(window);

    //get device context for drawing
    device = GetDC(window);

    return 1;
}

/**
 ** Entry point function
 **/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    //create window
    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow)) return 0;

    //initialize the game
    if (!Game_Init()) return 0;

    // main message loop
    while (!gameover)
    {
        //process Windows events
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        //process game loop
        Game_Run();
    }

    //free game resources
    Game_End();

    return msg.wParam;
}


