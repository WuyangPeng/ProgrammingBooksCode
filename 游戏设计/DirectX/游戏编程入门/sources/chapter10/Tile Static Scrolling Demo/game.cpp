// Beginning Game Programming, Second Edition
// ScrollTest program

#include "game.h"

int ScrollX, ScrollY;			//current scroll position
int SpeedX, SpeedY;				//scroll speed
LPDIRECT3DSURFACE9 gameworld;	//scroll buffer
long start;						//timing variable

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

//initializes the game
int Game_Init(HWND hwnd)
{
	Init_DirectInput(hwnd);
	Init_Keyboard(hwnd);
	Init_Mouse(hwnd);

	start = GetTickCount();
	BuildGameWorld();

    return 1;
}

//the main game loop
void Game_Run(HWND hwnd)
{
    //make sure the Direct3D device is valid
    if (d3ddev == NULL)
        return;

	//poll DirectInput devices
	Poll_Keyboard();
	Poll_Mouse();

    //check for escape key (to exit program)
    if (Key_Down(DIK_ESCAPE))
        PostMessage(hwnd, WM_DESTROY, 0, 0);

	//scroll based on mouse input
	if (Mouse_X() != 0) ScrollX += Mouse_X();
	if (Mouse_Y() != 0)	ScrollY += Mouse_Y();

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
   
			//stop rendering
			d3ddev->EndScene();
		}
	}

    //display the back buffer on the screen
    d3ddev->Present(NULL, NULL, NULL, NULL);

}


//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{
	Kill_Keyboard();
	Kill_Mouse();
	dinput->Release();
}

void BuildGameWorld()
{
	HRESULT result;
    int x, y;
    LPDIRECT3DSURFACE9 tiles;
    
    //load the bitmap image containing all the tiles
    tiles = LoadSurface("groundtiles.bmp", D3DCOLOR_XRGB(0,0,0));
    
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

void ScrollScreen()
{
    //update horizontal scrolling position and speed
    ScrollX += SpeedX;
    if (ScrollX < 0) 
	{
        ScrollX = 0;
        SpeedX = 0;
	}
    else if (ScrollX > GAMEWORLDWIDTH - SCREEN_WIDTH)
	{
        ScrollX = GAMEWORLDWIDTH - SCREEN_WIDTH;
        SpeedX = 0;
	}
    
    //update vertical scrolling position and speed
    ScrollY += SpeedY;
    if (ScrollY < 0)
	{
        ScrollY = 0;
        SpeedY = 0;
	}
    else if (ScrollY > GAMEWORLDHEIGHT - SCREEN_HEIGHT)
	{
        ScrollY = GAMEWORLDHEIGHT - SCREEN_HEIGHT;
        SpeedY = 0;
	}
    
    //set dimensions of the source image
	RECT r1 = {ScrollX, ScrollY, ScrollX+SCREEN_WIDTH-1, 
        ScrollY+SCREEN_HEIGHT-1};
    
    //set the destination rect
	RECT r2 = {0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1};
    
    //draw the current game world view
    d3ddev->StretchRect(gameworld, &r1, backbuffer, &r2, 
        D3DTEXF_NONE);

}
