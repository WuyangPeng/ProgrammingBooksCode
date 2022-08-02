/*
    Beginning Game Programming, Third Edition
    MyGame.cpp
*/

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Sprite Rotation and Scaling Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

LPDIRECT3DTEXTURE9 sunflower;
D3DCOLOR color;
int frame=0, columns, width, height;
int startframe, endframe, starttime=0, delay;

bool Game_Init(HWND window)
{
    //initialize Direct3D
    Direct3D_Init(window, SCREENW, SCREENH, false);

    //initialize DirectInput
    DirectInput_Init(window);

    //load the sprite image
    sunflower = LoadTexture("sunflower.bmp");

    return true;
}

void Game_Run(HWND window)
{
	static float scale = 0.001f;
	static float r = 0;
    static float s = 1.0f;

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

	    //set rotation and scaling
	    r = timeGetTime() / 600.0f;
        s += scale;
	    if (s < 0.1 || s > 1.25f) scale *= -1;

        //draw sprite
        width = height = 512;
        frame = 0;
        columns = 1;
        color = D3DCOLOR_XRGB(255,255,255);
        Sprite_Transform_Draw( sunflower, 300, 150, width, height, frame, columns, r, s, color );


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
    sunflower->Release();

    DirectInput_Shutdown();
    Direct3D_Shutdown();
}