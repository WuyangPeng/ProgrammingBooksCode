/*  Beginning Game Programming, Third Edition
    MyDirectX.h

    Changes during AR:
        return value of Key_Down
        restored KEY_DOWN macro 
*/

#pragma once

//header files
#define WIN32_EXTRA_LEAN
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <io.h>
#include <algorithm>
using namespace std;

//libraries
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//program values
extern const string APPTITLE;
extern const int SCREENW;
extern const int SCREENH;
extern bool gameover;

//macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//Direct3D objects
extern LPDIRECT3D9 d3d; 
extern LPDIRECT3DDEVICE9 d3ddev; 
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPD3DXSPRITE spriteobj;

//sprite structure
struct SPRITE
{
    bool alive; //added ch14
	float x,y;
	int frame, columns;
	int width, height;
	float scaling, rotation;
	int startframe, endframe;
	int starttime, delay;
	int direction;
	float velx, vely;
	D3DCOLOR color;

	SPRITE() 
	{
		frame = 0;
		columns = 1;
		width = height = 0;
		scaling = 1.0f;
		rotation = 0.0f;
		startframe = endframe = 0;
		direction = 1;
		starttime = delay = 0;
		velx = vely = 0.0f;
		color = D3DCOLOR_XRGB(255,255,255);
	}
};

//Direct3D functions
bool Direct3D_Init(HWND hwnd, int width, int height, bool fullscreen);
void Direct3D_Shutdown();
LPDIRECT3DSURFACE9 LoadSurface(string filename);
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, int destx, int desty, 
    int framenum, int framew, int frameh, int columns);
void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);


// added/modified in ch14
    void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
        int frame = 0, int columns = 1, float rotation = 0.0f, 
        float scaleW = 1.0f, float scaleH = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

    void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
        int frame = 0, int columns = 1, float rotation = 0.0f, float scaling = 1.0f, 
        D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

//bounding box collision detection
int Collision(SPRITE sprite1, SPRITE sprite2);

//distance based collision detection
bool CollisionD(SPRITE sprite1, SPRITE sprite2);

//DirectInput objects, devices, and states
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern DIMOUSESTATE mouse_state;
extern XINPUT_GAMEPAD controllers[4];

//DirectInput functions
bool DirectInput_Init(HWND);
void DirectInput_Update();
void DirectInput_Shutdown();
bool Key_Down(int);
int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
void XInput_Vibrate(int contNum = 0, int amount = 65535);
bool XInput_Controller_Found();

//game functions
bool Game_Init(HWND window);
void Game_Run(HWND window);
void Game_End();


//font functions
LPD3DXFONT MakeFont(string name, int size);
void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));



//DirectSound code added in chapter 11
#include "DirectSound.h"

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxerr9.lib")

//primary DirectSound object
extern CSoundManager *dsound;

//function prototypes
bool DirectSound_Init(HWND hwnd);
void DirectSound_Shutdown();
CSound *LoadSound(string filename);
void PlaySound(CSound *sound);
void LoopSound(CSound *sound);
void StopSound(CSound *sound);



//3D Mesh code added in chapter 13

//define the MODEL struct
struct MODEL
{
    LPD3DXMESH mesh;
    D3DMATERIAL9* materials;
    LPDIRECT3DTEXTURE9* textures;
    DWORD material_count;
	D3DXVECTOR3 translate;
	D3DXVECTOR3 rotate;
	D3DXVECTOR3 scale;

	MODEL()
	{
		material_count = 0;
		mesh = NULL;
		materials = NULL;
		textures = NULL;
		translate = D3DXVECTOR3(0.0f,0.0f,0.0f);
		rotate = D3DXVECTOR3(0.0f,0.0f,0.0f);
		scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	}
};

//3D mesh function prototypes
void DrawModel(MODEL *model);
void DeleteModel(MODEL *model);
MODEL *LoadModel(string filename);
bool FindFile(string *filename);
bool DoesFileExist(const string &filename);
void SplitPath(const string& inputPath, string* pathOnly, string* filenameOnly);
void SetCamera(float posx, float posy, float posz, float lookx = 0.0f, float looky=0.0f, float lookz=0.0f);

