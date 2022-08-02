// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Render Mesh Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

DWORD screentimer = timeGetTime();

MODEL *mesh=NULL;


bool Game_Init(HWND window)
{
    srand( (int)time(NULL) );

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


   //set the camera position
    SetCamera( 0.0f, -800.0f, -200.0f );

    //use ambient lighting and z-buffering
    d3ddev->SetRenderState(D3DRS_ZENABLE, true);
    d3ddev->SetRenderState(D3DRS_LIGHTING, false); 

    //load the mesh file
    mesh = LoadModel("Fokker.X");
    if (mesh == NULL)
    {
        MessageBox(window, "Error loading mesh", APPTITLE.c_str(), MB_OK);
        return 0;
    }

    return true;
}

void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
        D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    /*
     * slow rendering to approximately 60 fps
     */
    if (timeGetTime() > screentimer + 14)
    {
        screentimer = GetTickCount();

        //start rendering
        if (d3ddev->BeginScene())
        {
            //rotate the view
            D3DXMATRIX matWorld;
            D3DXMatrixRotationY(&matWorld, timeGetTime()/1000.0f);
            d3ddev->SetTransform(D3DTS_WORLD, &matWorld);
            
            //draw the model
            DrawModel(mesh);

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
    //free memory and shut down
    DeleteModel(mesh);

    DirectSound_Shutdown();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}