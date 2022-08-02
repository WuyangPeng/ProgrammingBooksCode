// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Font Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

//declare some font objects
LPD3DXFONT fontArial24 = NULL;
LPD3DXFONT fontGaramond36 = NULL;
LPD3DXFONT fontTimesNewRoman40 = NULL;


bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);

    //create some fonts
    fontArial24 = MakeFont("Arial",24);
    fontGaramond36 = MakeFont("Garamond",36);
    fontTimesNewRoman40 = MakeFont("Times New Roman", 40);


    return true;
}

void Game_Run(HWND window)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //update input devices
    DirectInput_Update();


    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

    //start rendering
    if (d3ddev->BeginScene())
    {
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
    

        //demonstrate font output
        FontPrint(fontArial24, 60, 50, "This is the Arial 24 font printed with ID3DXFont");

        FontPrint(fontGaramond36, 60, 100, "The text can be printed in any color like this magenta!", D3DCOLOR_XRGB(255,0,255));

        FontPrint(fontTimesNewRoman40, 60, 150, "Or how about bright green instead?", D3DCOLOR_XRGB(0,255,0));


        //demonstrate text wrapping inside a rectangular region
        RECT rect = { 60, 250, 350, 700 };
        D3DCOLOR white = D3DCOLOR_XRGB(255,255,255);
        string text = "This is a long string that will be ";
        text += "wrapped inside a rectangle.";
        fontTimesNewRoman40->DrawText( spriteobj, text.c_str(), text.length(), &rect, DT_WORDBREAK, white); 


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
    if (fontArial24) fontArial24->Release(); 
    if (fontGaramond36) fontGaramond36->Release();
    if (fontTimesNewRoman40) fontTimesNewRoman40->Release();

    DirectInput_Shutdown();
    Direct3D_Shutdown();
}