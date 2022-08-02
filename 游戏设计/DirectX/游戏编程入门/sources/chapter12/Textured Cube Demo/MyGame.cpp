// Beginning Game Programming, Third Edition
// MyGame.cpp

#include "MyDirectX.h"
using namespace std;

const string APPTITLE = "Vertex Buffer Textured Cube";
const int SCREENW = 1024;
const int SCREENH = 768;

DWORD screentimer = timeGetTime();

//vertex and quad definitions
#define D3DFVF_MYVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
struct VERTEX
{
    float x, y, z;
    float tu, tv;
};
struct QUAD
{
    VERTEX vertices[4];
    LPDIRECT3DVERTEXBUFFER9 buffer;
    LPDIRECT3DTEXTURE9 texture;
};



VERTEX cube[] = {
	{-1.0f, 1.0f,-1.0f, 0.0f,0.0f},     //side 1
	{ 1.0f, 1.0f,-1.0f, 1.0f,0.0f },
	{-1.0f,-1.0f,-1.0f, 0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f, 1.0f,1.0f },
	
	{-1.0f, 1.0f, 1.0f, 1.0f,0.0f },    //side 2
	{-1.0f,-1.0f, 1.0f, 1.0f,1.0f },
	{ 1.0f, 1.0f, 1.0f, 0.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f, 0.0f,1.0f },
	
	{-1.0f, 1.0f, 1.0f, 0.0f,0.0f },    //side 3
	{ 1.0f, 1.0f, 1.0f, 1.0f,0.0f },
	{-1.0f, 1.0f,-1.0f, 0.0f,1.0f },
	{ 1.0f, 1.0f,-1.0f, 1.0f,1.0f },
	
	{-1.0f,-1.0f, 1.0f, 0.0f,0.0f },    //side 4
	{-1.0f,-1.0f,-1.0f, 1.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f, 0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f, 1.0f,1.0f },

	{ 1.0f, 1.0f,-1.0f, 0.0f,0.0f },    //side 5
	{ 1.0f, 1.0f, 1.0f, 1.0f,0.0f },
	{ 1.0f,-1.0f,-1.0f, 0.0f,1.0f },
	{ 1.0f,-1.0f, 1.0f, 1.0f,1.0f },
	
	{-1.0f, 1.0f,-1.0f, 1.0f,0.0f },    //side 6
	{-1.0f,-1.0f,-1.0f, 1.0f,1.0f },
	{-1.0f, 1.0f, 1.0f, 0.0f,0.0f },
	{-1.0f,-1.0f, 1.0f, 0.0f,1.0f }
};

QUAD *quads[6]; 
D3DXVECTOR3 cameraSource;
D3DXVECTOR3 cameraTarget;



void SetPosition(QUAD *quad, int ivert, float x, float y, float z)
{
    quad->vertices[ivert].x = x;
    quad->vertices[ivert].y = y;
    quad->vertices[ivert].z = z;
}

void SetVertex(QUAD *quad, int ivert, float x, float y, float z, float tu, float tv)
{
    SetPosition(quad, ivert, x, y, z);
    quad->vertices[ivert].tu = tu;
    quad->vertices[ivert].tv = tv;
}

VERTEX CreateVertex(float x, float y, float z, float tu, float tv)
{
    VERTEX vertex;
    vertex.x = x;
    vertex.y = y;
    vertex.z = z;
    vertex.tu = tu;
    vertex.tv = tv;
    return vertex;
}

QUAD *CreateQuad(char *textureFilename)
{
    QUAD *quad = (QUAD*)malloc(sizeof(QUAD));

    //load the texture
    D3DXCreateTextureFromFile(d3ddev, textureFilename, &quad->texture);

    //create the vertex buffer for this quad
	d3ddev->CreateVertexBuffer( 
        4*sizeof(VERTEX), 
        0, 
        D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, 
        &quad->buffer, 
        NULL);

    //create the four corners of this dual triangle strip
    //each vertex is X,Y,Z and the texture coordinates U,V
    quad->vertices[0] = CreateVertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    quad->vertices[1] = CreateVertex( 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    quad->vertices[2] = CreateVertex(-1.0f,-1.0f, 0.0f, 0.0f, 1.0f);
    quad->vertices[3] = CreateVertex( 1.0f,-1.0f, 0.0f, 1.0f, 1.0f);

    return quad;
}

void DeleteQuad(QUAD *quad)
{
    if (quad == NULL) 
        return;

    //free the vertex buffer
    if (quad->buffer != NULL)
        quad->buffer->Release();

    //free the texture
    if (quad->texture != NULL)
        quad->texture->Release();

    //free the quad
    free(quad);
}

void DrawQuad(QUAD *quad)
{
    //fill vertex buffer with this quad's vertices
    void *temp = NULL;
    quad->buffer->Lock(0, sizeof(quad->vertices), (void**)&temp, 0);
    memcpy(temp, quad->vertices, sizeof(quad->vertices));
    quad->buffer->Unlock();

    //draw the textured dual triangle strip
    d3ddev->SetTexture(0, quad->texture);
    d3ddev->SetStreamSource(0, quad->buffer, 0, sizeof(VERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SetIdentity()
{
    //set default position, scale, and rotation
    D3DXMATRIX matWorld;
    D3DXMatrixTranslation(&matWorld, 0.0f, 0.0f, 0.0f);
    d3ddev->SetTransform(D3DTS_WORLD, &matWorld);
}

void ClearScene(D3DXCOLOR color)
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 );
}

void SetCamera(float x, float y, float z, float lookx, float looky, float lookz)
{
    D3DXMATRIX matView;
    D3DXVECTOR3 updir(0.0f,1.0f,0.0f);

    //move the camera
    cameraSource.x = x;
    cameraSource.y = y;
    cameraSource.z = z;
    
    //point the camera
    cameraTarget.x = lookx;
    cameraTarget.y = looky;
    cameraTarget.z = lookz;

    //set up the camera view matrix
    D3DXMatrixLookAtLH(&matView, &cameraSource, &cameraTarget, &updir);
    d3ddev->SetTransform(D3DTS_VIEW, &matView);
}

void SetPerspective(float fieldOfView, float aspectRatio, float nearRange, float farRange)
{
    //set the perspective so things in the distance will look smaller
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, fieldOfView, aspectRatio, nearRange, farRange);
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProj);
}


void init_cube()
{
    for (int q=0; q<6; q++)
    {
        int i = q*4;    //little shortcut into cube array
        quads[q] = CreateQuad("cube.bmp");
        for (int v=0; v<4; v++)
        {
            quads[q]->vertices[v] = CreateVertex(
                cube[i].x, cube[i].y, cube[i].z,    //position
                cube[i].tu, cube[i].tv);            //texture coords
            i++;    //next vertex
        }
    }
}

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


    //position the camera
    SetCamera(0.0f, 2.0f, -3.0f, 0, 0, 0);

    float ratio = (float)SCREENW / (float)SCREENH;
    SetPerspective(45.0f, ratio, 0.1f, 10000.0f);

    //turn dynamic lighting off, z-buffering on
    d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);

    //set the Direct3D stream to use the custom vertex
    d3ddev->SetFVF(D3DFVF_MYVERTEX);

    //convert the cube values into quads
    init_cube();

    return true;
}


void rotate_cube()
{
    static float xrot = 0.0f;
    static float yrot = 0.0f;
    static float zrot = 0.0f;

    //rotate the x and z axes
    xrot += 0.05f;
    yrot += 0.05f;
	//zrot += 0.05f;
	
    //create the matrices
    D3DXMATRIX matWorld;
    D3DXMATRIX matTrans;
	D3DXMATRIX matRot;

    //get an identity matrix
    D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.0f);

    //rotate the cube
	D3DXMatrixRotationYawPitchRoll(&matRot, 
		                           D3DXToRadian(xrot), 
		                           D3DXToRadian(yrot), 
		                           D3DXToRadian(zrot));
    matWorld = matRot * matTrans;

    //complete the operation
    d3ddev->SetTransform(D3DTS_WORLD, &matWorld);
}

void Game_Run(HWND window)
{
    if (!d3ddev) return;
    DirectInput_Update();
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);



    /*
     * slow rendering to approximately 60 fps
     */
    if (timeGetTime() > screentimer + 14)
    {
        screentimer = GetTickCount();

        rotate_cube();

        //start rendering
        if (d3ddev->BeginScene())
        {
            for (int n=0; n<6; n++)
                DrawQuad(quads[n]);

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
    for (int q=0; q<6; q++)
        DeleteQuad(quads[q]);

    DirectSound_Shutdown();
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}