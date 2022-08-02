// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Stock Mesh Demo";
const int SCREENW = 1024;
const int SCREENH = 768;

DWORD screentimer = 0;

LPD3DXMESH mesh;


void SetCamera(float posx, float posy, float posz, float lookx = 0.0f, float looky=0.0f, float lookz=0.0f)
{
	float fov = D3DX_PI / 4.0;
	float aspectRatio = SCREENW / SCREENH;
	float nearRange = 1.0;
	float farRange = 2000.0;
    D3DXVECTOR3 updir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 position = D3DXVECTOR3(posx, posy, posz);
	D3DXVECTOR3 target = D3DXVECTOR3(lookx, looky, lookz);

    //set the perspective 
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, fov, aspectRatio, nearRange, farRange);
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProj);

	//set up the camera view matrix
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &position, &target, &updir);
    d3ddev->SetTransform(D3DTS_VIEW, &matView);
}


bool Game_Init(HWND window)
{
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
	SetCamera( 0.0f, 1.0f, -4.0f );

    //use ambient lighting and z-buffering
    d3ddev->SetRenderState(D3DRS_ZENABLE, true);
    d3ddev->SetRenderState(D3DRS_LIGHTING, false); 


	/** 
     * create a stock 3D mesh: uncomment only one line at a time
    **/
	//D3DXCreateBox(d3ddev, 1.0f, 1.0f, 1.0f, &mesh, NULL);
	//D3DXCreateSphere(d3ddev, 1.0f, 20, 20, &mesh, NULL);
	//D3DXCreateCylinder(d3ddev, 1.0f, 1.0f, 2.0f, 20, 20, &mesh, NULL);
	D3DXCreateTorus(d3ddev, 0.5f, 1.0f, 20, 20, &mesh, NULL);
	//D3DXCreateTeapot(d3ddev, &mesh, NULL);

    return true;
}

void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);


    // slow rendering to approximately 60 fps
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
	        
			//draw the mesh
			mesh->DrawSubset(0);


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
	mesh->Release();

    DirectSound_Shutdown();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}