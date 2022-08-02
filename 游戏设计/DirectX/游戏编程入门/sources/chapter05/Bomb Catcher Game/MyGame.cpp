/*
    Beginning Game Programming, Third Edition
    MyGame.cpp
*/

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Bomb Catcher Game";
const int SCREENW = 1024;
const int SCREENH = 768;

LPDIRECT3DSURFACE9 bomb_surf = NULL;
LPDIRECT3DSURFACE9 bucket_surf = NULL;

struct BOMB
{
    float x,y;

    void reset()
    {
        x = (float)(rand() % (SCREENW-128));
        y = 0;
    }
};

BOMB bomb;

struct BUCKET
{
    float x,y;
};

BUCKET bucket;

int score = 0;
int vibrating = 0;


/**
 ** Game initialization
 **/
bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);

    DirectInput_Init(window);

    bomb_surf = LoadSurface("bomb.bmp");
    if (!bomb_surf) {
        MessageBox(window, "Error loading bomb","Error",0);
        return false;
    }

    bucket_surf = LoadSurface("bucket.bmp");
    if (!bucket_surf) {
        MessageBox(window, "Error loading bucket","Error",0);
        return false;
    }


    //position the bomb
    srand( (unsigned int)time(NULL) );
    bomb.reset();

    //position the bucket
    bucket.x = 500;
    bucket.y = 630;


    return true;
}

void Game_Run(HWND window)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //update input devices
    DirectInput_Update();

    //move the bomb down the screen
    bomb.y += 2.0f;

    //see if bomb hit the floor
    if (bomb.y > SCREENH) 
    {
        MessageBox(0,"Oh no, the bomb exploded!!","YOU STINK",0);
        gameover = true;
    }

    //move the bucket with the mouse
    int mx = Mouse_X();
    if (mx < 0) bucket.x -= 6.0f;
    else if (mx > 0) bucket.x += 6.0f;
    
    //move the bucket with the keyboard
    if (Key_Down(DIK_LEFT)) bucket.x -= 6.0f;
    else if (Key_Down(DIK_RIGHT)) bucket.x += 6.0f;

    //move the bucket with the controller
    if (XInput_Controller_Found())
    {
        //left analog thumb stick
        if (controllers[0].sThumbLX < -5000) 
            bucket.x -= 6.0f;
        else if (controllers[0].sThumbLX > 5000) 
            bucket.x += 6.0f;

        //left and right triggers
        if (controllers[0].bLeftTrigger > 128) 
            bucket.x -= 6.0f;
        else if (controllers[0].bRightTrigger > 128) 
            bucket.x += 6.0f;

        //left and right D-PAD
        if (controllers[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) 
            bucket.x -= 6.0f;
        else if (controllers[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            bucket.x += 6.0f;

        //left and right shoulders
        if (controllers[0].wButtons & XINPUT_GAMEPAD_DPAD_LEFT) 
            bucket.x -= 6.0f;
        else if (controllers[0].wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
            bucket.x += 6.0f;
    }

    //update vibration
    if (vibrating > 0)
    {
        vibrating++;
        if (vibrating > 20)
        {
            XInput_Vibrate(0, 0);
            vibrating = 0;
        }
    } 


    //keep bucket inside the screen
    if (bucket.x < 0) bucket.x = 0;
    if (bucket.x > SCREENW-128) bucket.x = SCREENW-128;

    //see if bucket caught the bomb
    int cx = bomb.x + 64;
    int cy = bomb.y + 64;
    if (cx > bucket.x && cx < bucket.x+128 && cy > bucket.y && cy < bucket.y+128)
    {
        //update and display score
        score++;
        char s[255];
        sprintf(s, "%s [SCORE %d]", APPTITLE.c_str(), score);
        SetWindowText(window, s);

        //vibrate the controller
        XInput_Vibrate(0, 65000);
        vibrating = 1;

        //restart bomb
        bomb.reset();
    }

    //clear the backbuffer
    d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0,0,0));

    //start rendering
    if (d3ddev->BeginScene())
    {

        //draw the bomb
        DrawSurface(backbuffer, bomb.x, bomb.y, bomb_surf);

        //draw the bucket
        DrawSurface(backbuffer, bucket.x, bucket.y, bucket_surf);
     
        //stop rendering
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    //escape key exits
    if (Key_Down(DIK_ESCAPE)) 
        gameover = true;

    //controller Back button also exits
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;


}

void Game_End()
{
    if (bomb_surf) bomb_surf->Release();
    if (bucket_surf) bucket_surf->Release();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}