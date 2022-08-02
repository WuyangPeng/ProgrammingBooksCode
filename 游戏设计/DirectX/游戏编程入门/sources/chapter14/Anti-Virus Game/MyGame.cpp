/*
    Beginning Game Programming, Third Edition
    Anti-Virus Game
    MyGame.cpp
*/

#include "MyDirectX.h"
#include <sstream>
using namespace std;

const string APPTITLE = "Anti-Virus Game";
const int SCREENW = 1024;
const int SCREENH = 768;

//font variables
LPD3DXFONT font;
LPD3DXFONT debugfont;

//timing variables
bool paused = false;
DWORD refresh = 0;
DWORD screentime = 0;
double screenfps = 0.0;
double screencount = 0.0;
DWORD coretime = 0;
double corefps = 0.0;
double corecount = 0.0;
DWORD currenttime;

//background scrolling variables
const int BUFFERW = SCREENW * 2;
const int BUFFERH = SCREENH;
double scrollx=0;
double scrolly=0;
LPDIRECT3DSURFACE9 background = NULL;
const double virtual_level_size = BUFFERW * 5;
double virtual_scrollx = 0;

//player variables
LPDIRECT3DTEXTURE9 player_ship;
SPRITE player;
enum PLAYER_STATES
{
    NORMAL = 0,
    PHASING = 1,
    CHARGING = 2,
    OVERLOADING = 3
};
PLAYER_STATES player_state = NORMAL;
PLAYER_STATES player_state_previous = NORMAL;
D3DXVECTOR2 position_history[8];
int position_history_index = 0;
DWORD position_history_timer = 0;
double charge_angle = 0.0;
double charge_tweak = 0.0;
double charge_tweak_dir = 1.0;
double energy = 100.0;
double health = 100.0;

//enemy virus objects
const int VIRUSES = 100;
LPDIRECT3DTEXTURE9 virus1_image;
SPRITE viruses[VIRUSES];

const int FRAGMENTS = 300;
LPDIRECT3DTEXTURE9 fragment_image;
SPRITE fragments[FRAGMENTS];

//bullet variables
LPDIRECT3DTEXTURE9 purple_fire;
const int BULLETS = 300;
SPRITE bullets[BULLETS];
int player_shoot_timer = 0;
int firepower = 1;
int bulletcount = 0;

//sound effects
CSound *tisk=NULL;
CSound *foom=NULL;
CSound *charging=NULL;


//GUI elements
LPDIRECT3DTEXTURE9 energy_slice;
LPDIRECT3DTEXTURE9 health_slice;

//controller vibration
int vibrating = 0;
int vibration = 100;


/**
 **
 **/
bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);
    DirectSound_Init(window);


    //create a font
    font = MakeFont("Arial Bold", 24);
    debugfont = MakeFont("Arial", 14);

    //load background
    LPDIRECT3DSURFACE9 image = NULL;
    image = LoadSurface("binary.bmp");
    if (!image) return false;


    //load player sprite
    player_ship = LoadTexture("ufo.png");
    player.x = 100;
    player.y = 350;
    player.width = player.height = 64;

    for (int n=0; n<4; n++)
        position_history[n] = D3DXVECTOR2(-100,0);

    //load bullets
    purple_fire = LoadTexture("purplefire.tga");
    for (int n=0; n<BULLETS; n++)
    {
        bullets[n].alive = false;
        bullets[n].x = 0;
        bullets[n].y = 0;
        bullets[n].width = 55;
        bullets[n].height = 16;
    }

    //load enemy viruses
    virus1_image = LoadTexture("virus1.tga");
    for (int n=0; n<VIRUSES; n++)
    {
        viruses[n].alive = true;
        viruses[n].width = 96;
        viruses[n].height = 96;
        viruses[n].x = (float)( 1000 + rand() % BUFFERW );
        viruses[n].y = (float)( rand() % SCREENH );
        viruses[n].velx = (float)((rand() % 8) * -1);
        viruses[n].vely = (float)(rand() % 2 - 1);
    }


    //load gui elements
    energy_slice = LoadTexture("energyslice.tga");
    health_slice = LoadTexture("healthslice.tga");



    //load audio files
    tisk = LoadSound("clip.wav");
    foom = LoadSound("longfoom.wav");
    charging = LoadSound("charging.wav");


    //load memory fragments (energy)
    fragment_image = LoadTexture("fragment.tga");
    for (int n=0; n<FRAGMENTS; n++)
    {
        fragments[n].alive = true;
        D3DCOLOR fragmentcolor = D3DCOLOR_ARGB( 
            200 + rand() % 55, 
            150 + rand() % 100, 
            150 + rand() % 100, 
            150 + rand() % 100);
        fragments[n].color = fragmentcolor;
        fragments[n].width = 128;
        fragments[n].height = 128;
        fragments[n].scaling = (float)(rand() % 20 + 10) / 150.0f;
        fragments[n].rotation = (float)( rand() % 360 );
        fragments[n].velx = (float)(rand() % 4 + 1) * -1.0f;
        fragments[n].vely = (float)(rand() % 10 - 5) / 10.0f;
        fragments[n].x = (float)( rand() % BUFFERW );
        fragments[n].y = (float)( rand() % SCREENH );
    }



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
    RECT source_rect = {0, 0, SCREENW, SCREENH };
    RECT dest_ul = { 0, 0, SCREENW, SCREENH };

    d3ddev->StretchRect(
        image, 
        &source_rect, 
        background, 
        &dest_ul, 
        D3DTEXF_NONE);

    //copy image to upper right corner of background
    RECT dest_ur = { SCREENW, 0, SCREENW*2, SCREENH };

    d3ddev->StretchRect(
        image, 
        &source_rect, 
        background, 
        &dest_ur, 
        D3DTEXF_NONE);

    //get pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, 
        &backbuffer);


    //remove image
    image->Release();

    return true;
}

/**
 **
 **/
void Game_End()
{
    background->Release();
    font->Release();
    debugfont->Release();
    fragment_image->Release();
    delete charging;
    delete foom;
    delete tisk;
    energy_slice->Release();
    health_slice->Release();
    virus1_image->Release();
    purple_fire->Release();
    player_ship->Release();

    DirectSound_Shutdown();
    DirectInput_Shutdown();
    Direct3D_Shutdown();

}

/**
 **
 **/
template <class T>
std::string static ToString(const T & t, int places = 2)
{
    ostringstream oss;
    oss.precision(places);
    oss.setf(ios_base::fixed);
    oss << t; 
    return oss.str();
}

/**
 **
 **/
void move_player(float movex, float movey)
{
    //cannot move while overloading!
    if (player_state == OVERLOADING 
        || player_state_previous == OVERLOADING) 
        return;

    float multi = 4.0f;
    player.x += movex * multi; 
    player.y += movey * multi;
}


/**
 **
 **/
const double PI = 3.1415926535;
const double PI_under_180 = 180.0f / PI;
const double PI_over_180 = PI / 180.0f;

double toRadians(double degrees)
{
    return degrees * PI_over_180;
}

double toDegrees(double radians)
{
    return radians * PI_under_180;
}

double wrap(double value, double bounds)
{
    double result = fmod(value, bounds);
    if (result < 0) result += bounds;
    return result;
}

double wrapAngleDegs(double degs)
{
    return wrap(degs, 360.0);
}

double LinearVelocityX(double angle)
{
    //angle -= 90;
    if (angle < 0) angle = 360 + angle;    
    return cos( angle * PI_over_180);
}

double LinearVelocityY(double angle)
{
    //angle -= 90;
    if (angle < 0) angle = 360 + angle;    
    return sin( angle * PI_over_180);
}

/**
 **
 **/
void add_energy(double value)
{
    energy += value;
    if (energy < 0.0) energy = 0.0;
    if (energy > 100.0) energy = 100.0;
}

/**
 **
 **/
void Vibrate(int contnum, int amount, int length)
{
    vibrating = 1;
    vibration = length;
    XInput_Vibrate(contnum, amount);
}

/**
 **
 **/
int find_bullet()
{
    int bullet = -1;
    for (int n=0; n<BULLETS; n++)
    {
        if (!bullets[n].alive) 
        {
            bullet = n;
            break;
        }
    }
    return bullet;
}

/**
 **
 **/
bool player_overload()
{
    //disallow overoad unless energy is at 100%
    if (energy < 50.0) return false;

    //reduce energy for this shot
    add_energy(-0.5);
    if (energy < 0.0) 
    {
        energy = 0.0;
        return false;
    }

    //play charging sound
    PlaySound(charging);

    //vibrate controller
    Vibrate(0, 20000, 20);

    int b1 = find_bullet();
    if (b1 == -1) return true;
    bullets[b1].alive = true;
    bullets[b1].velx = 0.0f;
    bullets[b1].vely = 0.0f;
    bullets[b1].rotation = (float)(rand() % 360);
    bullets[b1].x = player.x + player.width;
    bullets[b1].y = player.y + player.height/2 
        - bullets[b1].height/2;
    bullets[b1].y += (float)(rand() % 20 - 10);

    return true;
}

/**
 **
 **/
void player_shoot()
{
    //limit firing rate
    if ((int)timeGetTime() < player_shoot_timer + 100) return;
    player_shoot_timer = timeGetTime();

    //reduce energy for this shot
    add_energy(-1.0);
    if (energy < 1.0) 
    {
        energy = 0.0;
        return;
    }


    //play firing sound
    PlaySound(tisk);

    Vibrate(0, 25000, 10);

    //launch bullets based on firepower level
    switch(firepower)
    {
        case 1: 
        {
            //create a bullet
            int b1 = find_bullet();
            if (b1 == -1) return;
            bullets[b1].alive = true;
            bullets[b1].rotation = 0.0;
            bullets[b1].velx = 12.0f;
            bullets[b1].vely = 0.0f;
            bullets[b1].x = player.x + player.width/2;
            bullets[b1].y = player.y + player.height/2 
                - bullets[b1].height/2;
        }
        break;
        case 2:
        {
            //create bullet 1
            int b1 = find_bullet();
            if (b1 == -1) return;
            bullets[b1].alive = true;
            bullets[b1].rotation = 0.0;
            bullets[b1].velx = 12.0f;
            bullets[b1].vely = 0.0f;
            bullets[b1].x = player.x + player.width/2;
            bullets[b1].y = player.y + player.height/2 
                - bullets[b1].height/2;
            bullets[b1].y -= 10;

            //create bullet 2
            int b2 = find_bullet();
            if (b2 == -1) return;
            bullets[b2].alive = true;
            bullets[b2].rotation = 0.0;
            bullets[b2].velx = 12.0f;
            bullets[b2].vely = 0.0f;
            bullets[b2].x = player.x + player.width/2;
            bullets[b2].y = player.y + player.height/2 
                - bullets[b2].height/2;
            bullets[b2].y += 10;
        }
        break;

    case 3:
    {
        //create bullet 1
        int b1 = find_bullet();
        if (b1 == -1) return;
        bullets[b1].alive = true;
        bullets[b1].rotation = 0.0;
        bullets[b1].velx = 12.0f;
        bullets[b1].vely = 0.0f;
        bullets[b1].x = player.x + player.width/2;
        bullets[b1].y = player.y + player.height/2 
            - bullets[b1].height/2;

        //create bullet 2
        int b2 = find_bullet();
        if (b2 == -1) return;
        bullets[b2].alive = true;
        bullets[b2].rotation = 0.0;
        bullets[b2].velx = 12.0f;
        bullets[b2].vely = 0.0f;
        bullets[b2].x = player.x + player.width/2;
        bullets[b2].y = player.y + player.height/2 
            - bullets[b2].height/2;
        bullets[b2].y -= 16;

        //create bullet 3
        int b3 = find_bullet();
        if (b3 == -1) return;
        bullets[b3].alive = true;
        bullets[b3].rotation = 0.0;
        bullets[b3].velx = 12.0f;
        bullets[b3].vely = 0.0f;
        bullets[b3].x = player.x + player.width/2;
        bullets[b3].y = player.y + player.height/2 
            - bullets[b3].height/2;
        bullets[b3].y += 16;

    }
    break;

    case 4:
    {
        //create bullet 1
        int b1 = find_bullet();
        if (b1 == -1) return;
        bullets[b1].alive = true;
        bullets[b1].rotation = 0.0;
        bullets[b1].velx = 12.0f;
        bullets[b1].vely = 0.0f;
        bullets[b1].x = player.x + player.width/2;
        bullets[b1].x += 8;
        bullets[b1].y = player.y + player.height/2 
            - bullets[b1].height/2;
        bullets[b1].y -= 12;

        //create bullet 2
        int b2 = find_bullet();
        if (b2 == -1) return;
        bullets[b2].alive = true;
        bullets[b2].rotation = 0.0;
        bullets[b2].velx = 12.0f;
        bullets[b2].vely = 0.0f;
        bullets[b2].x = player.x + player.width/2;
        bullets[b2].x += 8;
        bullets[b2].y = player.y + player.height/2 
            - bullets[b2].height/2;
        bullets[b2].y += 12;

        //create bullet 3
        int b3 = find_bullet();
        if (b3 == -1) return;
        bullets[b3].alive = true;
        bullets[b3].rotation = 0.0;
        bullets[b3].velx = 12.0f;
        bullets[b3].vely = 0.0f;
        bullets[b3].x = player.x + player.width/2;
        bullets[b3].y = player.y + player.height/2 
            - bullets[b3].height/2;
        bullets[b3].y -= 32;

        //create bullet 4
        int b4 = find_bullet();
        if (b4 == -1) return;
        bullets[b4].alive = true;
        bullets[b4].rotation = 0.0;
        bullets[b4].velx = 12.0f;
        bullets[b4].vely = 0.0f;
        bullets[b4].x = player.x + player.width/2;
        bullets[b4].y = player.y + player.height/2 
            - bullets[b4].height/2;
        bullets[b4].y += 32;
    }
    break;

    case 5:
    {
        //create bullet 1
        int b1 = find_bullet();
        if (b1 == -1) return;
        bullets[b1].alive = true;
        bullets[b1].rotation = 0.0;
        bullets[b1].velx = 12.0f;
        bullets[b1].vely = 0.0f;
        bullets[b1].x = player.x + player.width/2;
        bullets[b1].y = player.y + player.height/2 
            - bullets[b1].height/2;
        bullets[b1].y -= 12;

        //create bullet 2
        int b2 = find_bullet();
        if (b2 == -1) return;
        bullets[b2].alive = true;
        bullets[b2].rotation = 0.0;
        bullets[b2].velx = 12.0f;
        bullets[b2].vely = 0.0f;
        bullets[b2].x = player.x + player.width/2;
        bullets[b2].y = player.y + player.height/2 
            - bullets[b2].height/2;
        bullets[b2].y += 12;

        //create bullet 3
        int b3 = find_bullet();
        if (b3 == -1) return;
        bullets[b3].alive = true;
        bullets[b3].rotation = -4.0;// 86.0;
        bullets[b3].velx = (float) (12.0 * 
            LinearVelocityX( bullets[b3].rotation ));
        bullets[b3].vely = (float) (12.0 * 
            LinearVelocityY( bullets[b3].rotation ));
        bullets[b3].x = player.x + player.width/2;
        bullets[b3].y = player.y + player.height/2 
            - bullets[b3].height/2;
        bullets[b3].y -= 20;

        //create bullet 4
        int b4 = find_bullet();
        if (b4 == -1) return;
        bullets[b4].alive = true;
        bullets[b4].rotation = 4.0;// 94.0;
        bullets[b4].velx = (float) (12.0 * 
            LinearVelocityX( bullets[b4].rotation ));
        bullets[b4].vely = (float) (12.0 * 
            LinearVelocityY( bullets[b4].rotation ));
        bullets[b4].x = player.x + player.width/2;
        bullets[b4].y = player.y + player.height/2 
            - bullets[b4].height/2;
        bullets[b4].y += 20;
    }
    break;
    }
}

/**
 **
 **/
void Game_Run(HWND window)
{
    if (!d3ddev) return;
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
        D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

    //get current ticks
    currenttime = timeGetTime();

    //calculate core frame rate
    corecount += 1.0;
    if (currenttime > coretime + 1000) 
    {
        corefps = corecount;
        corecount = 0.0;
        coretime = currenttime;
    }


    //run update on normal processes (like input) at 60 hz

    if (currenttime > refresh + 14)
    {
        refresh = currenttime;

        DirectInput_Update();

        if (!paused)
        {
            player_state = NORMAL;

            if (Key_Down(DIK_UP) || Key_Down(DIK_W) 
                || controllers[0].sThumbLY > 2000)
                move_player(0,-1);

            if (Key_Down(DIK_DOWN) || Key_Down(DIK_S) 
                || controllers[0].sThumbLY < -2000)
                move_player(0,1);

            if (Key_Down(DIK_LEFT) || Key_Down(DIK_A) 
                || controllers[0].sThumbLX < -2000)
                move_player(-1,0);

            if (Key_Down(DIK_RIGHT) || Key_Down(DIK_D) 
                || controllers[0].sThumbLX > 2000)
                move_player(1,0);

            if (Key_Down(DIK_Z) 
                || controllers[0].wButtons & XINPUT_GAMEPAD_B)
                player_state = PHASING;

            if (Key_Down(DIK_X) 
                || controllers[0].wButtons & XINPUT_GAMEPAD_X)
                player_state = CHARGING;

            if (Key_Down(DIK_C) 
                || controllers[0].wButtons & XINPUT_GAMEPAD_Y)
            {
                if (!player_overload()) 
                    player_state_previous = OVERLOADING;
                else
                    player_state = OVERLOADING;

            }

            if (Key_Down(DIK_SPACE) 
                || controllers[0].wButtons & XINPUT_GAMEPAD_A)
                player_shoot();

            //update background scrolling
            scrollx += 1.0;
            if (scrolly < 0)
                scrolly = BUFFERH - SCREENH;
            if (scrolly > BUFFERH - SCREENH)
                scrolly = 0;
            if (scrollx < 0)
                scrollx = BUFFERW - SCREENW;
            if (scrollx > BUFFERW - SCREENW)
                scrollx = 0;

            //update virtual scroll position
            virtual_scrollx+= 1.0;
            if (virtual_scrollx > virtual_level_size)
                virtual_scrollx = 0.0;


            //update overloaded bullets
            if (player_state == NORMAL 
                && player_state_previous == OVERLOADING)
            {
                int bulletcount = 0;

                //launch overloaded bullets
                for (int n=0; n<BULLETS; n++)
                {
                    //overloaded bullets start with zero velocity
                    if (bullets[n].alive && bullets[n].velx == 0.0f)
                    {
                        bulletcount++;
                        bullets[n].rotation = (float)(rand() % 90 - 45);
                        bullets[n].velx = (float) 
                            (20.0 * LinearVelocityX( bullets[n].rotation ));
                        bullets[n].vely = (float) 
                            (20.0 * LinearVelocityY( bullets[n].rotation ));
                    }
                }
                if (bulletcount > 0) 
                {
                    PlaySound(foom);
                    Vibrate(0, 40000, 30);
                }

                player_state_previous = NORMAL;
            }

            //update normal bullets
            bulletcount = 0;
            for (int n=0; n<BULLETS; n++)
            {
                if (bullets[n].alive) 
                {
                    bulletcount++;
                    bullets[n].x += bullets[n].velx;
                    bullets[n].y += bullets[n].vely;

                    if (bullets[n].x < 0 || bullets[n].x > SCREENW
                        || bullets[n].y < 0 || bullets[n].y > SCREENH)
                        bullets[n].alive = false;
                }
            }

            //update enemy viruses
            for (int n=0; n<VIRUSES; n++)
            {
                if (viruses[n].alive) 
                {
                    //move horiz based on x velocity
                    viruses[n].x += viruses[n].velx;
                    if (viruses[n].x < -96.0f)
                        viruses[n].x = (float)virtual_level_size;
                    if (viruses[n].x > (float)virtual_level_size)
                        viruses[n].x = -96.0f;

                    //move vert based on y velocity
                    viruses[n].y += viruses[n].vely;
                    if (viruses[n].y < -96.0f)
                        viruses[n].y = SCREENH;
                    if (viruses[n].y > SCREENH)
                        viruses[n].y = -96.0f;

                }
            }


            //update energy fragments
            for (int n=0; n<FRAGMENTS; n++)
            {
                if (fragments[n].alive)
                {
                    fragments[n].x += fragments[n].velx;
                    if (fragments[n].x < 0.0 - fragments[n].width) 
                        fragments[n].x = BUFFERW;
                    if (fragments[n].x > virtual_level_size) 
                        fragments[n].x = 0.0;
                    if (fragments[n].y < 0.0 - fragments[n].height) 
                        fragments[n].y = SCREENH;
                    if (fragments[n].y > SCREENH) 
                        fragments[n].y = 0.0;

                    if (player_state == CHARGING)
                    {
                        //temporarily enlarge fragment so it can be drawn in
                        float oldscale = fragments[n].scaling;
                        fragments[n].scaling *= 10.0;

                        //is it touching the player?
                        if (CollisionD( player, fragments[n] ))
                        {
                            //get center of player
                            float playerx = player.x + player.width/2.0f;
                            float playery = player.y + player.height/2.0f;

                            //get center of fragment
                            float fragmentx = fragments[n].x;
                            float fragmenty = fragments[n].y;

                            //suck fragment toward player
                            if (fragmentx < playerx) fragments[n].x += 6.0f;
                            if (fragmentx > playerx) fragments[n].x -= 6.0f;
                            if (fragmenty < playery) fragments[n].y += 6.0f;
                            if (fragmenty > playery) fragments[n].y -= 6.0f;

                        }

                        //restore fragment scale
                        fragments[n].scaling = oldscale;

                        //after scooping up a fragment, check for collision
                        if (CollisionD( player, fragments[n] ))
                        {
                            add_energy( 2.0 );
                            fragments[n].x = (float)(3000 + rand() % 1000);
                            fragments[n].y = (float)(rand() % SCREENH);
                        }

                    }
                }
            }


            //update controller vibration 
            if (vibrating > 0)
            {
                vibrating++;
                if (vibrating > vibration)
                {
                    XInput_Vibrate(0, 0);
                    vibrating = 0;
                }
            } 


        } //paused

        //calculate screen frame rate
        screencount += 1.0;
        if (currenttime > screentime + 1000) 
        {
            screenfps = screencount;
            screencount = 0.0;
            screentime = currenttime;
        }

        //number keys used for testing
        if (Key_Down(DIK_F1)) firepower = 1;
        if (Key_Down(DIK_F2)) firepower = 2;
        if (Key_Down(DIK_F3)) firepower = 3;
        if (Key_Down(DIK_F4)) firepower = 4;
        if (Key_Down(DIK_F5)) firepower = 5;

        if (Key_Down(DIK_P)) paused = !paused;

        if (Key_Down(DIK_E) || controllers[0].bRightTrigger)
        {
            add_energy(1.0);
        }

        if (KEY_DOWN(VK_ESCAPE)) gameover = true;
        if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
            gameover = true;
    }


    //examine every live virus for collision
    for (int v=0; v<VIRUSES; v++)
    {
        if (viruses[v].alive) 
        {
            //test collision with every live bullet
            for (int b=0; b<BULLETS; b++)
            {
                if (bullets[b].alive)
                {
                    if (Collision(viruses[v], bullets[b]))
                    {
                        bullets[b].alive = false;
                        viruses[v].alive = false;
                    }
                }
            }

        }

    } //for



    //draw scrolling background
    RECT source_rect = {
        (long)scrollx, 
        (long)scrolly, 
        (long)scrollx+SCREENW, 
        (long)scrolly+SCREENH 
    };
    RECT dest_rect = { 0, 0, SCREENW, SCREENH};
    d3ddev->StretchRect(background, &source_rect, backbuffer, 
        &dest_rect, D3DTEXF_NONE);


    //begin rendering
    if (d3ddev->BeginScene())
    {
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

        switch(player_state)
        {
            case PHASING: //draw phased out ship images
            {
                for (int n=0; n<4; n++)
                {
                    D3DCOLOR phasecolor = D3DCOLOR_ARGB(
                        rand() % 150, 0, 255, 255);

                    int x = (int)player.x + rand() % 12 - 6;
                    int y = (int)player.y + rand() % 12 - 6;

                    Sprite_Transform_Draw(
                        player_ship, 
                        x, y,
                        player.width, 
                        player.height,
                        0, 1, 0.0f, 1.0f, 
                        phasecolor);
                }
            }
            break;

            case CHARGING: //animate ship as a gravity well to suck energy
            {
                D3DCOLOR chargecolor = D3DCOLOR_ARGB( 
                    150 + rand() % 100, 50 + rand() % 150, 50, 50);

                charge_angle = wrapAngleDegs(charge_angle - 3.0);
                charge_tweak += 0.2 * charge_tweak_dir;
                if (charge_tweak < -4.0 || charge_tweak > 4.0) 
                    charge_tweak_dir *= -1;

                int x = (int)( player.x + cos(charge_angle) + charge_tweak );
                int y = (int)( player.y + sin(charge_angle) + charge_tweak );

                Sprite_Transform_Draw(
                    player_ship, 
                    x, y, 
                    player.width, player.height, 
                    0, 1, 
                    (float)toRadians(charge_angle), 
                    1.0f, 
                    chargecolor);

            }
            break;

            case OVERLOADING: //super weapon charges up
            {
                for (int n=0; n<4; n++)
                {
                    D3DCOLOR overcolor = 
                        D3DCOLOR_ARGB( 150 + rand() % 100, 80, 255, 255);

                    int x = (int)player.x + rand() % 12 - 6;
                    int y = (int)player.y;

                    Sprite_Transform_Draw(
                        player_ship, 
                        x, y, 
                        player.width, 
                        player.height, 
                        0, 1, 0.0f, 1.0f, 
                        overcolor);
                }
            }
            break;

            
            case NORMAL: //draw ship normally
            {
                //reset shadows if state just changed
                if (player_state_previous != player_state)
                {
                    for (int n=0; n<8; n++)
                    {
                        position_history[n].x = player.x;
                        position_history[n].y = player.y;
                    }
                }

                D3DCOLOR shadowcolor = D3DCOLOR_ARGB( 60, 0, 240, 240 );

                if (currenttime > position_history_timer + 40)
                {
                    position_history_timer = currenttime;
                    position_history_index++;
                    if (position_history_index > 7)
                    {
                        position_history_index = 7;
                        for (int a=1; a<8; a++)
                            position_history[a-1] = position_history[a];
                    }

                    position_history[position_history_index].x = player.x;
                    position_history[position_history_index].y = player.y;
                }

                for (int n=0; n<8; n++)
                {
                    shadowcolor = D3DCOLOR_ARGB( 20 + n*10, 0, 240, 240 );

                    //draw shadows of previous ship position
                    Sprite_Transform_Draw( 
                        player_ship, 
                        (int)position_history[n].x,
                        (int)position_history[n].y,
                        player.width, 
                        player.height, 
                        0, 1, 0.0f, 1.0f, 
                        shadowcolor);
                }

                //draw ship normally
                D3DCOLOR shipcolor = D3DCOLOR_ARGB(255, 0, 255, 255);
                Sprite_Transform_Draw(
                    player_ship, 
                    (int)player.x, 
                    (int)player.y, 
                    player.width, 
                    player.height, 
                    0, 1, 0.0f, 1.0f, 
                    shipcolor);

            }
            break;
        }

        //save player state
        player_state_previous = player_state;


        //draw enemy viruses
        D3DCOLOR viruscolor = D3DCOLOR_ARGB(200,255,255,255);
        for (int n=0; n<VIRUSES; n++)
        {
            //is this virus sprite alive?
            if (viruses[n].alive)
            {
                //is this virus sprite visible on the screen?
                if (viruses[n].x > -96.0f && viruses[n].x < SCREENW)
                {
                    Sprite_Transform_Draw( 
                        virus1_image,
                        (int)viruses[n].x, 
                        (int)viruses[n].y,
                        viruses[n].width, 
                        viruses[n].height,
                        0, 1, 0.0f, 1.0f, 
                        viruscolor);
                }
            }
        }


        //draw bullets
        D3DCOLOR bulletcolor = D3DCOLOR_ARGB(255,255,255,255);
        for (int n=0; n<BULLETS; n++)
        {
            if (bullets[n].alive) 
            {
                Sprite_Transform_Draw( 
                    purple_fire,
                    (int)bullets[n].x, 
                    (int)bullets[n].y,
                    bullets[n].width, 
                    bullets[n].height,
                    0, 1, 
                    (float)toRadians(bullets[n].rotation), 
                    1.0f, 
                    bulletcolor);
            }
        }


        //draw energy fragments
        for (int n=0; n<FRAGMENTS; n++)
        {
            if (fragments[n].alive)
            {
                Sprite_Transform_Draw( 
                    fragment_image, 
                    (int)fragments[n].x, 
                    (int)fragments[n].y, 
                    fragments[n].width, 
                    fragments[n].height,
                    0, 1, 
                    fragments[n].rotation, 
                    fragments[n].scaling, 
                    fragments[n].color);
            }
        }

        int y = SCREENH-12;
        D3DCOLOR color = D3DCOLOR_ARGB(200, 255, 255, 255);
        D3DCOLOR debugcolor = D3DCOLOR_ARGB(255, 255, 255, 255);


        //draw the gui elements

        FontPrint(font, 900, 0, "SCORE", color);

        D3DCOLOR energycolor = D3DCOLOR_ARGB(200,255,255,255);
        for (int n=0; n<energy * 5; n++)
            Sprite_Transform_Draw(
                energy_slice, 
                10+n*2, 0, 1, 32, 0, 
                1, 0.0f, 1.0f, 1.0f, 
                energycolor);

        D3DCOLOR healthcolor = D3DCOLOR_ARGB(200,255,255,255);
        for (int n=0; n<health*5; n++)
            Sprite_Transform_Draw(
                health_slice, 
                10+n*2, 
                SCREENH-21, 
                1, 20, 0, 1, 0.0f, 
                1.0f, 1.0f, 
                healthcolor);


        //draw debug messages
        FontPrint(debugfont, 0, y, "", debugcolor);
        
        FontPrint(debugfont, 0, y-12, 
            "Core FPS = " + ToString(corefps) 
            + " (" + ToString(1000.0 / corefps) + " ms)", 
            debugcolor);

        FontPrint(debugfont, 0, y-24, 
            "Screen FPS = " + ToString(screenfps), 
            debugcolor);

        FontPrint(debugfont, 0, y-36, 
            "Ship X,Y = " + ToString(player.x) + "," 
            + ToString(player.y), 
            debugcolor);

        FontPrint(debugfont, 0, y-48, 
            "Bullets = " + ToString(bulletcount));

        FontPrint(debugfont, 0, y-60, 
            "Buffer Scroll = " + ToString(scrollx), 
            debugcolor);

        FontPrint(debugfont, 0, y-72, 
            "Virtual Scroll = " + ToString(virtual_scrollx) 
            + " / " + ToString(virtual_level_size));

        FontPrint(debugfont, 0, y-84, 
            "Fragment[0] = " 
            + ToString(fragments[0].x) 
            + "," + ToString(fragments[0].y));
   
        spriteobj->End();

        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

}
