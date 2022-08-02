// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Play Sound Program";
const int SCREENW = 1024;
const int SCREENH = 768;

LPDIRECT3DTEXTURE9 ball_image = NULL;
LPDIRECT3DTEXTURE9 bumper_image = NULL;
LPDIRECT3DTEXTURE9 background = NULL;

//balls
const int NUMBALLS = 10;
SPRITE balls[NUMBALLS];

//bumpers
SPRITE bumpers[4];

//timing variable
DWORD screentimer = timeGetTime();
DWORD coretimer = timeGetTime();
DWORD bumpertimer = timeGetTime();

//the wave sound
CSound *sound_bounce = NULL;
CSound *sound_electric = NULL;


bool Game_Init(HWND window)
{
    srand(time(NULL));

    //initialize Direct3D
    if (!Direct3D_Init(window, SCREENW, SCREENH, false))
    {
        MessageBox(window,"Error initializing Direct3D",APPTITLE.c_str(),0);
        return false;
    }

    //initialize DirectInput
    if (!DirectInput_Init(window))
    {
        MessageBox(window,"Error initializing DirectInput",APPTITLE.c_str(),0);
        return false;
    }

    //initialize DirectSound
    if (!DirectSound_Init(window))
    {
        MessageBox(window,"Error initializing DirectSound",APPTITLE.c_str(),0);
        return false;
    }


    //load the background image
    background = LoadTexture("craters.tga");
    if (!background) 
    {
        MessageBox(window,"Error loading craters.tga",APPTITLE.c_str(),0);
        return false;
    }

    //load the ball image
    ball_image = LoadTexture("lightningball.tga");
    if (!ball_image)
    {
        MessageBox(window,"Error loading lightningball.tga",APPTITLE.c_str(),0);
        return false;
    }

    //load the bumper image
    bumper_image = LoadTexture("bumper.tga");
    if (!ball_image)
    {
        MessageBox(window,"Error loading bumper.tga",APPTITLE.c_str(),0);
        return false;
    }

    //set the balls' properties
    for (int n=0; n<NUMBALLS; n++)
    {
        balls[n].x = (float)(rand() % (SCREENW-200));
        balls[n].y = (float)(rand() % (SCREENH-200));
        balls[n].width = 64;
        balls[n].height = 64;
        balls[n].velx = (float)(rand() % 6 - 3);
        balls[n].vely = (float)(rand() % 6 - 3);
    }

    //set the bumpers' properties
    for (int n=0; n<4; n++)
    {
        bumpers[n].width = 128;
        bumpers[n].height = 128;
        bumpers[n].columns = 2;
        bumpers[n].frame = 0;
    }
    bumpers[0].x = 150;
    bumpers[0].y = 150;
    bumpers[1].x = SCREENW-150-128;
    bumpers[1].y = 150;
    bumpers[2].x = 150;
    bumpers[2].y = SCREENH-150-128;
    bumpers[3].x = SCREENW-150-128;
    bumpers[3].y = SCREENH-150-128;

    //load bounce wave file
    sound_bounce = LoadSound("step.wav");
    if (!sound_bounce) 
    {
        MessageBox(window,"Error loading step.wav",APPTITLE.c_str(),0);
        return false;
    }

    return true;
}

void rebound(SPRITE &sprite1, SPRITE &sprite2)
{
    float centerx1 = sprite1.x + sprite1.width/2;
    float centery1 = sprite1.y + sprite1.height/2;

    float centerx2 = sprite2.x + sprite2.width/2;
    float centery2 = sprite2.y + sprite2.height/2;

    if (centerx1 < centerx2)
    {
        sprite1.velx = fabs(sprite1.velx) * -1;
    } 
    else if (centerx1 > centerx2) 
    {
        sprite1.velx = fabs(sprite1.velx);
    }

    if (centery1 < centery2)
    {
        sprite1.vely = fabs(sprite1.vely) * -1;
    } 
    else {
        sprite1.vely = fabs(sprite1.vely);
    }

    sprite1.x += sprite1.velx;
    sprite1.y += sprite1.vely;

}

void Game_Run(HWND window)
{
    int n;

    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    /*
     * slow ball movement
     */
    if (timeGetTime() > coretimer + 10)
    {
        //reset timing
        coretimer = GetTickCount();

        int width = balls[0].width;
        int height = balls[0].height;

        //move the ball sprites
        for (n=0; n<NUMBALLS; n++)
        {
            balls[n].x += balls[n].velx;
            balls[n].y += balls[n].vely;
    
            //warp the ball at screen edges
            if (balls[n].x > SCREENW)
            {
                balls[n].x = -width;
            }
            else if (balls[n].x < -width)
            {
                balls[n].x = SCREENW+width;
            }

            if (balls[n].y > SCREENH+height)
            {
                balls[n].y = -height;
            }
            else if (balls[n].y < -height)
            {
                balls[n].y = SCREENH+height;
            }
        }            
   }


    //reset bumper frames
    if (timeGetTime() > bumpertimer + 250)
    {
        bumpertimer = timeGetTime();
        for (int bumper=0; bumper<4; bumper++)
        {
            bumpers[bumper].frame = 0;
        }
    }

    /*
     * check for ball collisions with bumpers
     */
    for (int ball=0; ball<NUMBALLS; ball++)
    {
        for (int bumper=0; bumper<4; bumper++)
        {
            if (CollisionD(balls[ball], bumpers[bumper]))
            {
                rebound(balls[ball], bumpers[bumper]);
                bumpers[bumper].frame = 1;
                PlaySound(sound_bounce);
            }
        }
    }

    /*
     * check for sprite collisions with each other
     * (as fast as possible--with no time limiter)
     */
    for (int one=0; one<NUMBALLS; one++)
    {
        for (int two=0; two<NUMBALLS; two++)
        {
            if (one != two)
            {
                if (CollisionD(balls[one], balls[two]))
                {                
                    while (CollisionD(balls[one], balls[two]))
                    {
                        //rebound ball one
                        rebound(balls[one], balls[two]);

                        //rebound ball two
                        rebound(balls[two], balls[one]);

                    }

                }
            }
        }
    }


    /*
     * slow rendering to approximately 60 fps
     */
    if (timeGetTime() > screentimer + 14)
    {
        screentimer = GetTickCount();

        //start rendering
        if (d3ddev->BeginScene())
        {
            //start sprite handler
            spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

            //draw background
            Sprite_Transform_Draw(background, 0, 0, SCREENW, SCREENH);

            //draw the balls
            for (n=0; n<NUMBALLS; n++)
            {
                Sprite_Transform_Draw(ball_image, 
                    balls[n].x, balls[n].y, 
                    balls[n].width, balls[n].height);
            }

            //draw the bumpers
            for (n=0; n<4; n++)
            {
                Sprite_Transform_Draw(bumper_image, 
                    bumpers[n].x, 
                    bumpers[n].y,
                    bumpers[n].width, 
                    bumpers[n].height, 
                    bumpers[n].frame, 
                    bumpers[n].columns);
            }

            //stop drawing
            spriteobj->End();


            //stop rendering
            d3ddev->EndScene();
            d3ddev->Present(NULL, NULL, NULL, NULL);
        }
    }

    //exit with escape key or controller Back button
    if (KEY_DOWN(VK_ESCAPE)) gameover = true;
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK) gameover = true;

}

void Game_End()
{

    if (ball_image) ball_image->Release();
    if (bumper_image) bumper_image->Release();
    if (background) background->Release();

    if (sound_bounce) delete sound_bounce;
 
    DirectSound_Shutdown();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}