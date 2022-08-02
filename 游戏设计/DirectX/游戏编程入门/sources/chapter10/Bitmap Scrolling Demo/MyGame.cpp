// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
#include <sstream>
using namespace std;

const string APPTITLE = "Bitmap Scrolling Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

const int BUFFERW = SCREENW * 2;
const int BUFFERH = SCREENH * 2;

LPDIRECT3DSURFACE9 background = NULL;

LPD3DXFONT font;

double scrollx=0, scrolly=0;


bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);


    //create a font
    font = MakeFont("Arial", 24);

    //load background
    LPDIRECT3DSURFACE9 image = NULL;
    image = LoadSurface("space2.bmp");
    if (!image) return false;


    //create background
    HRESULT result = 
    d3ddev->CreateOffscreenPlainSurface(
        BUFFERW,
        BUFFERH,
        D3DFMT_X8R8G8B8,
        D3DPOOL_DEFAULT,
        &background,
        NULL);
    if (result != D3D_OK) return false;

    //copy image to upper left corner of background
    RECT source_rect = {0, 0, 1024, 768 };
    RECT dest_ul = { 0, 0, 1024, 768 };
    d3ddev->StretchRect(image, &source_rect, background, &dest_ul, D3DTEXF_NONE);

    //copy image to upper right corner of background
    RECT dest_ur = { 1024, 0, 1024*2, 768 };
    d3ddev->StretchRect(image, &source_rect, background, &dest_ur, D3DTEXF_NONE);

    //copy image to lower left corner of background
    RECT dest_ll = { 0, 768, 1024, 768*2 };
    d3ddev->StretchRect(image, &source_rect, background, &dest_ll, D3DTEXF_NONE);

    //copy image to lower right corner of background
    RECT dest_lr = { 1024, 768, 1024*2, 768*2 };
    d3ddev->StretchRect(image, &source_rect, background, &dest_lr, D3DTEXF_NONE);

    //get pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);


    //remove image
    image->Release();

    return true;
}


void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
        D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    if (Key_Down(DIK_UP) || controllers[0].sThumbLY > 2000)
        scrolly -= 1;

    if (Key_Down(DIK_DOWN) || controllers[0].sThumbLY < -2000)
        scrolly += 1;

    if (Key_Down(DIK_LEFT) || controllers[0].sThumbLX < -2000)
        scrollx -= 1;

    if (Key_Down(DIK_RIGHT) || controllers[0].sThumbLX > 2000)
        scrollx += 1;


    //keep scrolling within boundary
    if (scrolly < 0)
        scrolly = BUFFERH - SCREENH;
    if (scrolly > BUFFERH - SCREENH)
        scrolly = 0;
    if (scrollx < 0)
        scrollx = BUFFERW - SCREENW;
    if (scrollx > BUFFERW - SCREENW)
        scrollx = 0;


    if (d3ddev->BeginScene())
    {

        RECT source_rect = {scrollx, scrolly, scrollx+1024, scrolly+768 };
        RECT dest_rect = { 0, 0, 1024, 768};

        d3ddev->StretchRect(background, &source_rect, backbuffer, &dest_rect, D3DTEXF_NONE);


        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

        std::ostringstream oss;
        oss << "Scroll Position = " << scrollx << "," << scrolly;
        FontPrint(font, 0, 0, oss.str());
   
        spriteobj->End();
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    if (KEY_DOWN(VK_ESCAPE)) gameover = true;
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;

}

void Game_End()
{
    background->Release();
    font->Release();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}