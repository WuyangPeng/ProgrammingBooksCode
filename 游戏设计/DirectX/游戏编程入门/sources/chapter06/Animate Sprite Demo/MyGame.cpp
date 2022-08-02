// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Animate Sprite Demo";
const int SCREENW = 800;
const int SCREENH = 600;

LPDIRECT3DTEXTURE9 explosion = NULL;

int frame = 0;
int starttime = 0;


bool Game_Init(HWND window)
{
    //initialize Direct3D
    if (!Direct3D_Init(window, SCREENW, SCREENH, false))
    {
        MessageBox(0, "Error initializing Direct3D","ERROR",0);
        return false;
    }

    //initialize DirectInput
    if (!DirectInput_Init(window))
    {
        MessageBox(0, "Error initializing DirectInput","ERROR",0);
        return false;
    }

    //load explosion sprite
    explosion = LoadTexture("explosion_30_128.tga");
    if (!explosion) return false;


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
        //start drawing
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);


        //animate and draw the sprite
		Sprite_Animate(frame, 0, 29, 1, starttime, 30);
		Sprite_Draw_Frame(explosion, 200, 200, frame, 128, 128, 6);


        //stop drawing
        spriteobj->End();

        //stop rendering
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    //Escape key ends program
	//exit when escape key is pressed
	if (KEY_DOWN(VK_ESCAPE)) gameover = true;

    //controller Back button also ends
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;

}

void Game_End()
{
    //free memory and shut down
    explosion->Release();

    DirectInput_Shutdown();
    Direct3D_Shutdown();
}