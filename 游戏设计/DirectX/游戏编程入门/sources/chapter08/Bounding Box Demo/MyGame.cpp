// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Bounding Box Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

SPRITE ship, asteroid1, asteroid2;

LPDIRECT3DTEXTURE9 imgShip = NULL;
LPDIRECT3DTEXTURE9 imgAsteroid = NULL;


bool Game_Init(HWND window)
{
    //initialize Direct3D
    Direct3D_Init(window, SCREENW, SCREENH, false);

    //initialize DirectInput
    DirectInput_Init(window);

    //load the sprite textures
    imgShip = LoadTexture("fatship.tga");
    if (!imgShip) return false;
	imgAsteroid = LoadTexture("asteroid.tga");
	if (!imgAsteroid) return false;

	//set properties for sprites
	ship.x = 450;
	ship.y = 300;
	ship.width = ship.height = 128;
	
	asteroid1.x = 50;
	asteroid1.y = 200;
	asteroid1.width = asteroid1.height = 60;
	asteroid1.columns = 8;
	asteroid1.startframe = 0;
	asteroid1.endframe = 63;
	asteroid1.velx = -2.0f;
	
	asteroid2.x = 900;
	asteroid2.y = 500;
	asteroid2.width = asteroid2.height = 60;
	asteroid2.columns = 8;
	asteroid2.startframe = 0;
	asteroid2.endframe = 63;
	asteroid2.velx = 2.0f;


    return true;
}

void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

	//move the ship up/down with arrow keys
	if (Key_Down(DIK_UP))
	{
		ship.y -= 1.0f;
		if (ship.y < 0) ship.y = 0;
	}

	if (Key_Down(DIK_DOWN)) 
	{
		ship.y += 1.0f;
		if (ship.y > SCREENH - ship.height)
			ship.y = SCREENH - ship.height;
	}

	//move and animate the asteroids
	asteroid1.x += asteroid1.velx;
	if (asteroid1.x < 0 || asteroid1.x > SCREENW-asteroid1.width)
		asteroid1.velx *= -1;
	Sprite_Animate(asteroid1.frame, asteroid1.startframe, asteroid1.endframe, asteroid1.direction, asteroid1.starttime, asteroid1.delay);

	asteroid2.x += asteroid2.velx;
	if (asteroid2.x < 0 || asteroid2.x > SCREENW-asteroid2.width)
		asteroid2.velx *= -1;
	Sprite_Animate(asteroid2.frame, asteroid2.startframe, asteroid2.endframe, asteroid2.direction, asteroid2.starttime, asteroid2.delay);

	//test for collisions
	if (Collision(ship, asteroid1))
		asteroid1.velx *= -1;

	if (Collision(ship, asteroid2))
		asteroid2.velx *= -1;


    if (d3ddev->BeginScene())
    {
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);


		Sprite_Transform_Draw(imgShip, ship.x, ship.y, ship.width, ship.height, ship.frame, ship.columns);

		Sprite_Transform_Draw(imgAsteroid, asteroid1.x, asteroid1.y, asteroid1.width, asteroid1.height, asteroid1.frame, asteroid1.columns);

		Sprite_Transform_Draw(imgAsteroid, asteroid2.x, asteroid2.y, asteroid2.width, asteroid2.height, asteroid2.frame, asteroid2.columns);


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
    if (imgShip) imgShip->Release();
	if (imgAsteroid) imgAsteroid->Release();

    DirectInput_Shutdown();
    Direct3D_Shutdown();
}