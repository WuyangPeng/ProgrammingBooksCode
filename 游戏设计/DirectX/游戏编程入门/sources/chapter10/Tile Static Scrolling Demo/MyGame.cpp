// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
#include <sstream>
using namespace std;

const string APPTITLE = "Tile-Based Static Scrolling";
const int SCREENW = 1024;
const int SCREENH = 768;

LPD3DXFONT font;

//settings for the scroller
const int TILEWIDTH = 64;
const int TILEHEIGHT = 64;
const int MAPWIDTH = 25;
const int MAPHEIGHT = 18;

//scrolling window size
const int WINDOWWIDTH = (SCREENW / TILEWIDTH) * TILEWIDTH;
const int WINDOWHEIGHT = (SCREENH / TILEHEIGHT) * TILEHEIGHT;

//entire game world dimensions
const int GAMEWORLDWIDTH = TILEWIDTH * MAPWIDTH;
const int GAMEWORLDHEIGHT = TILEHEIGHT * MAPHEIGHT;

int ScrollX, ScrollY;	
int SpeedX, SpeedY;					
long start;
LPDIRECT3DSURFACE9 gameworld = NULL;

int MAPDATA[MAPWIDTH*MAPHEIGHT] = {
	80,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,
    81,81,81,82,90,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,92,3,3,3,3,3,92,3,
    92,90,3,13,83,96,3,3,23,3,92,3,13,92,3,3,3,3,3,3,11,3,13,3,3,92,
    90,3,3,3,3,3,3,3,10,3,3,3,3,3,23,3,3,3,3,3,3,3,13,3,92,90,3,96,
    3,13,3,3,3,3,3,3,3,3,3,3,3,3,96,3,23,3,96,3,3,92,90,3,3,3,3,3,3,
    13,3,3,3,13,3,3,11,3,3,3,3,3,3,3,13,3,92,90,3,83,11,3,92,3,3,3,
    3,3,11,3,3,3,3,3,3,3,83,3,3,3,92,92,90,3,3,3,96,3,13,3,3,3,11,
    10,3,3,3,3,3,13,3,3,13,3,3,3,92,90,3,23,3,3,3,3,3,3,96,3,3,83,
    3,3,3,92,3,3,3,3,3,13,3,92,90,3,3,3,3,3,3,3,3,3,3,3,3,23,3,3,3,
    3,3,3,3,3,3,3,92,90,3,3,3,11,3,92,3,3,13,3,3,131,3,10,3,3,3,96,
    3,92,3,96,3,92,90,3,13,83,3,3,3,3,3,3,3,3,3,3,3,13,3,3,3,3,3,3,
    3,3,92,90,3,3,3,3,13,3,3,3,3,3,11,96,3,3,3,3,3,3,13,3,13,3,11,
    92,90,92,3,13,3,3,3,3,3,3,92,3,10,3,23,3,3,3,3,3,3,3,3,3,92,90,
    3,3,3,3,3,96,3,23,3,3,3,3,3,3,3,3,83,3,3,13,3,96,3,92,90,3,3,3,
    3,92,3,3,3,3,3,13,3,3,3,13,3,3,3,11,3,3,3,3,92,90,3,13,3,3,3,3,
    3,3,3,96,3,3,3,3,3,3,3,3,3,3,92,3,3,92,100,101,101,101,101,101,
    101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,
    101,101,102
};


void DrawTile(LPDIRECT3DSURFACE9 source,	// source surface image
				int tilenum,				// tile #
				int width,					// tile width
				int height,					// tile height
				int columns,				// columns of tiles
				LPDIRECT3DSURFACE9 dest,	// destination surface
				int destx,					// destination x
				int desty)					// destination y
{
    
    //create a RECT to describe the source image
    RECT r1;
    r1.left = (tilenum % columns) * width;
    r1.top = (tilenum / columns) * height;
    r1.right = r1.left + width;
    r1.bottom = r1.top + height;
    
    //set destination rect
	RECT r2 = {destx,desty,destx+width,desty+height};
    
    //draw the tile 
    d3ddev->StretchRect(source, &r1, dest, &r2, D3DTEXF_NONE);
}

void BuildGameWorld()
{
	HRESULT result;
    int x, y;
    LPDIRECT3DSURFACE9 tiles;
    
    //load the bitmap image containing all the tiles
    tiles = LoadSurface("groundtiles.bmp");
    
    //create the scrolling game world bitmap
    result = d3ddev->CreateOffscreenPlainSurface(
		GAMEWORLDWIDTH,         //width of the surface
		GAMEWORLDHEIGHT,        //height of the surface
		D3DFMT_X8R8G8B8,		
		D3DPOOL_DEFAULT,		
		&gameworld,             //pointer to the surface
		NULL);
	
    if (result != D3D_OK)
	{
        MessageBox(NULL,"Error creating working surface!","Error",0);
		return;
	}
    
    //fill the gameworld bitmap with tiles
    for (y=0; y < MAPHEIGHT; y++)
        for (x=0; x < MAPWIDTH; x++)
            DrawTile(tiles, MAPDATA[y * MAPWIDTH + x], 64, 64, 16, 
            gameworld, x * 64, y * 64);
        
    //now the tiles bitmap is no longer needed
    tiles->Release();
}

bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);

    //create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

    //create a font
    font = MakeFont("Arial", 24);


    BuildGameWorld();

	start = GetTickCount();

    return true;
}

void Game_End()
{
    if (gameworld) gameworld->Release();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}



void ScrollScreen()
{
    //update horizontal scrolling position and speed
    ScrollX += SpeedX;
    if (ScrollX < 0) 
	{
        ScrollX = 0;
        SpeedX = 0;
	}
    else if (ScrollX > GAMEWORLDWIDTH - SCREENW)
	{
        ScrollX = GAMEWORLDWIDTH - SCREENW;
        SpeedX = 0;
	}
    
    //update vertical scrolling position and speed
    ScrollY += SpeedY;
    if (ScrollY < 0)
	{
        ScrollY = 0;
        SpeedY = 0;
	}
    else if (ScrollY > GAMEWORLDHEIGHT - SCREENH)
	{
        ScrollY = GAMEWORLDHEIGHT - SCREENH;
        SpeedY = 0;
	}
    
    //set dimensions of the source image
	RECT r1 = {ScrollX, ScrollY, ScrollX+SCREENW-1, ScrollY+SCREENH-1};
    
    //set the destination rect
	RECT r2 = {0, 0, SCREENW-1, SCREENH-1};
    
    //draw the current game world view
    d3ddev->StretchRect(gameworld, &r1, backbuffer, &r2, 
        D3DTEXF_NONE);

}

void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

	//scroll based on key or controller input
    if (Key_Down(DIK_DOWN) || controllers[0].sThumbLY < -2000)
        ScrollY += 1;

    if (Key_Down(DIK_UP) || controllers[0].sThumbLY > 2000)
        ScrollY -= 1;

    if (Key_Down(DIK_LEFT) || controllers[0].sThumbLX < -2000)
        ScrollX -= 1;

    if (Key_Down(DIK_RIGHT) || controllers[0].sThumbLX > 2000)
        ScrollX += 1;

    //keep the game running at a steady frame rate
    if (GetTickCount() - start >= 30)
    {
        //reset timing
        start = GetTickCount();

		//start rendering
		if (d3ddev->BeginScene())
		{
			
            //update the scrolling view
            ScrollScreen();
		
            spriteobj->Begin(D3DXSPRITE_ALPHABLEND);

            std::ostringstream oss;
            oss << "Scroll Position = " << ScrollX << "," << ScrollY;
            FontPrint(font, 0, 0, oss.str());
   
            spriteobj->End();

			//stop rendering
			d3ddev->EndScene();
            d3ddev->Present(NULL, NULL, NULL, NULL);
		}
	}

    //to exit 
    if (KEY_DOWN(VK_ESCAPE) || 
        controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;

}

