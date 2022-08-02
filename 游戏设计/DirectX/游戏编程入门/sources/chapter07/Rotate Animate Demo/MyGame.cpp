/*
    Beginning Game Programming, Third Edition
    MyGame.cpp
*/

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Sprite Rotation and Animation Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

LPDIRECT3DTEXTURE9 paladin = NULL;
D3DCOLOR color = D3DCOLOR_XRGB(255,255,255);
float scale = 0.004f;
float r = 0;
float s = 1.0f;
int frame=0, columns, width, height;
int startframe, endframe, starttime=0, delay;


bool Game_Init(HWND window)
{
    //initialize Direct3D
    Direct3D_Init(window, SCREENW, SCREENH, false);

    //initialize DirectInput
    DirectInput_Init(window);


    //load the sprite sheet
    paladin = LoadTexture("paladin_walk.png");
    if (!paladin) {
        MessageBox(window, "Error loading sprite", "Error", 0);
        return false;
    }

    return true;
}


void Game_Run(HWND window)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //update input devices
    DirectInput_Update();

    //clear the scene
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    //start rendering
    if (d3ddev->BeginScene())
    {
        //begin sprite rendering
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

	    //scale the sprite from tiny to huge over time
        s += scale;
	    if (s < 0.5f || s > 6.0f) scale *= -1;


        //set animation properties
        columns = 8;
        width = height = 96;
        startframe = 24;
        endframe = 31;
        delay = 90;
        Sprite_Animate( frame, startframe, endframe, 1, starttime, delay );

        //transform and draw sprite
        Sprite_Transform_Draw( paladin, 300, 200, width, height,  frame, columns, 0, s, color );

        //end sprite rendering
        spriteobj->End();

        //stop rendering
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

 	//exit when escape key is pressed
	if (KEY_DOWN(VK_ESCAPE)) gameover = true;

    //controller Back button also ends
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;

}

void Game_End()
{
    //free memory and shut down
    paladin->Release();

    DirectInput_Shutdown();
    Direct3D_Shutdown();
}