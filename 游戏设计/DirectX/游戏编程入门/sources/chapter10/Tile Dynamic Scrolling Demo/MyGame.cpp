// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
#include <sstream>
using namespace std;

const string APPTITLE = "Tile-Based Dynamic Scrolling";
const int SCREENW = 1024;
const int SCREENH = 768;

LPD3DXFONT font;

//settings for the scroller
const int TILEWIDTH = 64;
const int TILEHEIGHT = 64;
const int MAPWIDTH = 16;
const int MAPHEIGHT = 24;

//scrolling window size
const int WINDOWWIDTH = (SCREENW / TILEWIDTH) * TILEWIDTH;
const int WINDOWHEIGHT = (SCREENH / TILEHEIGHT) * TILEHEIGHT;

int ScrollX, ScrollY;	
int SpeedX, SpeedY;					
long start;
LPDIRECT3DSURFACE9 scrollbuffer=NULL;
LPDIRECT3DSURFACE9 tiles=NULL;

int MAPDATA[MAPWIDTH*MAPHEIGHT] = {
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,
70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,
92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,
110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,
126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,
142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,
158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,
174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,
190,191,192,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,
42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,
63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,
84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,
104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,
136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,
152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,
168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,
184,185,186,187,188,189,190,191,192
};


bool Game_Init(HWND window)
{
    Direct3D_Init(window, SCREENW, SCREENH, false);
    DirectInput_Init(window);

    //create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

    //create a font
    font = MakeFont("Arial", 24);

	//load the tile images
	tiles = LoadSurface("spacemap.bmp");
    if (!tiles) return false;

	//create the scroll buffer surface in memory, slightly bigger 
    //than the screen
    const int SCROLLBUFFERWIDTH = SCREENW + TILEWIDTH * 2;
    const int SCROLLBUFFERHEIGHT = SCREENH + TILEHEIGHT * 2;

	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
		SCROLLBUFFERWIDTH, SCROLLBUFFERHEIGHT, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,
		&scrollbuffer, 
		NULL);
    if (result != S_OK) return false;

	start = GetTickCount();

    return true;
}

void Game_End()
{
    if (scrollbuffer) scrollbuffer->Release();
    if (tiles) tiles->Release();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}

//This function updates the scrolling position and speed
void UpdateScrollPosition()
{
    const int GAMEWORLDWIDTH = TILEWIDTH * MAPWIDTH;
    const int GAMEWORLDHEIGHT = TILEHEIGHT * MAPHEIGHT;

    //update horizontal scrolling position and speed
    ScrollX += SpeedX;

    if (ScrollX < 0) 
	{
        ScrollX = 0;
        SpeedX = 0;
	}
    else if (ScrollX > GAMEWORLDWIDTH - WINDOWWIDTH)
	{
        ScrollX = GAMEWORLDWIDTH - WINDOWWIDTH;
        SpeedX = 0;
	}
    
    //update vertical scrolling position and speed
    ScrollY += SpeedY;
    if (ScrollY < 0)
	{
        ScrollY = 0;
        SpeedY = 0;
	}
	else if (ScrollY > GAMEWORLDHEIGHT - WINDOWHEIGHT)
	{
        ScrollY = GAMEWORLDHEIGHT - WINDOWHEIGHT;
        SpeedY = 0;
    }
}

//This function does the real work of drawing a single tile from the 
//source image onto the tile scroll buffer. Parameters provide much 
//flexibility.
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



//This function fills the tilebuffer with tiles representing
//the current scroll display based on scrollx/scrolly.
void DrawTiles()
{
    int tilex, tiley;
    int columns, rows;
    int x, y;
    int tilenum;
    
    //calculate starting tile position
    tilex = ScrollX / TILEWIDTH;
    tiley = ScrollY / TILEHEIGHT;
    
    //calculate the number of columns and rows
    columns = WINDOWWIDTH / TILEWIDTH;
    rows = WINDOWHEIGHT / TILEHEIGHT;
    
    //draw tiles onto the scroll buffer surface
    for (y=0; y<=rows; y++)
	{
        for (x=0; x<=columns; x++)
		{
			//retrieve the tile number from this position
            tilenum = MAPDATA[((tiley + y) * MAPWIDTH + (tilex + x))];

			//draw the tile onto the scroll buffer
            DrawTile(tiles,tilenum,TILEWIDTH,TILEHEIGHT,16,scrollbuffer,
                x*TILEWIDTH,y*TILEHEIGHT);
		}
	}
}

//This function draws the portion of the scroll buffer onto the back buffer
//according to the current "partial tile" scroll position.
void DrawScrollWindow(bool scaled = false)
{
    //calculate the partial sub-tile lines to draw using modulus
    int partialx = ScrollX % TILEWIDTH;
    int partialy = ScrollY % TILEHEIGHT;
    
    //set dimensions of the source image as a rectangle
	RECT r1 = {partialx,partialy,partialx+WINDOWWIDTH-1,partialy+WINDOWHEIGHT-1};
        
    //set the destination rectangle
    RECT r2;
    if (scaled) {
        //use this line for scaled display
	    RECT r = {0, 0, WINDOWWIDTH-1, WINDOWHEIGHT-1};  
        r2 = r;
    }
    else {
        //use this line for non-scaled display
        RECT r = {0, 0, SCREENW-1, SCREENH-1};
        r2 = r;
    }

    //draw the "partial tile" scroll window onto the back buffer
    d3ddev->StretchRect(scrollbuffer, &r1, backbuffer, &r2, D3DTEXF_NONE);
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

    //keep the game running at a steady frame rate
    if (GetTickCount() - start >= 30)
    {
        //reset timing
        start = GetTickCount();

		//update the scrolling view
		UpdateScrollPosition();

		//start rendering
		if (d3ddev->BeginScene())
		{
			
			//draw tiles onto the scroll buffer
			DrawTiles();

			//draw the scroll window onto the back buffer
			DrawScrollWindow();


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

