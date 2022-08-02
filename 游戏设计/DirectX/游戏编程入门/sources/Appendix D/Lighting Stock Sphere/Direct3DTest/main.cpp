/*
	D3DXSprite Test Program
	By John Doe, Uber Coder Supreme
	Don't mess with my code!
*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

const bool wireframe = false;
const char *APPTITLE = "Lighting Example";
const int SCREENW = 1024;
const int SCREENH = 768;
HWND window;
bool gameover = false;

//Direct3D objects
LPDIRECT3D9 d3d = NULL; 
LPDIRECT3DDEVICE9 d3ddev = NULL; 

//define the 2D rendering objects
LPD3DXSPRITE d3dxsprite = NULL;

LPD3DXMESH sphere;


//void CreateCube(double width, double height, double depth)
//{
//	D3DXCreateBox(g_engine->getDevice(), (float)width, (float)height, (float)depth, &mesh, NULL);
//}
//
//void CreateTeapot()
//{
//	D3DXCreateTeapot(g_engine->getDevice(), &mesh, NULL);
//}



void Create_Point_Light(int lightNum, D3DXVECTOR3 position, double range)
{
	D3DLIGHT9 p_light;
	//D3DCOLORVALUE p_color;

	ZeroMemory( &p_light, sizeof(D3DLIGHT9) );

	p_light.Diffuse.r = p_light.Ambient.r = 1.0f;
	p_light.Diffuse.g = p_light.Ambient.g = 1.0f;
	p_light.Diffuse.b = p_light.Ambient.b = 1.0f;
	p_light.Diffuse.a = p_light.Ambient.a = 1.0f;

	p_light.Range = (float)range;
	p_light.Type = D3DLIGHT_POINT;
	p_light.Position = position;
	p_light.Attenuation0 = 0.1f;

	d3ddev->SetLight(lightNum, &p_light);
	d3ddev->LightEnable(lightNum,TRUE);
}

void Set_Camera(float x,float y,float z)
{
    D3DXMATRIX p_matrixProj;
    D3DXMATRIX p_matrixView;
	D3DXMATRIX p_matrixRot;
    D3DXVECTOR3 p_updir;
	double p_nearRange;
	double p_farRange;
	double p_aspectRatio;
	double p_fov;
	D3DXVECTOR3 p_position;
	D3DXVECTOR3 p_rotation;
	D3DXVECTOR3 p_target;

	p_position = D3DXVECTOR3(x, y, z);
	p_target = D3DXVECTOR3(0.0f,0.0f,0.0f);
	p_updir = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//hard coded to 1.3333 by default
	p_fov = D3DX_PI / 4.0;
	p_aspectRatio = 1024 / 768;
	p_nearRange = 1.0;
	p_farRange = 2000.0;

    //set the camera's perspective matrix
    D3DXMatrixPerspectiveFovLH(&p_matrixProj, (float)p_fov, (float)p_aspectRatio, (float)p_nearRange, (float)p_farRange);
    d3ddev->SetTransform(D3DTS_PROJECTION, &p_matrixProj);

    //set the camera's view matrix
    D3DXMatrixLookAtLH(&p_matrixView, &p_position, &p_target, &p_updir);
	d3ddev->SetTransform(D3DTS_VIEW, &p_matrixView );
}


void Create_Directional_Light(int lightNum, D3DXVECTOR3 direction, double range)
{
	D3DLIGHT9 p_light;
	ZeroMemory( &p_light, sizeof(D3DLIGHT9) );

	p_light.Diffuse.r = p_light.Ambient.r = 1.0f;
	p_light.Diffuse.g = p_light.Ambient.g = 1.0f;
	p_light.Diffuse.b = p_light.Ambient.b = 1.0f;
	p_light.Diffuse.a = p_light.Ambient.a = 1.0f;
	p_light.Range = (float)range;

	p_light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVec3Normalize( (D3DXVECTOR3*)&p_light.Direction, &direction );

	d3ddev->SetLight(lightNum, &p_light);
	d3ddev->LightEnable(lightNum,TRUE);
}


//void Create_Spot_Light(int lightNum, D3DLIGHTTYPE type, D3DXVECTOR3 position, D3DXVECTOR3 direction, double range)
//{
//	this->p_lightNum = lightNum;
//	ZeroMemory( &p_light, sizeof(D3DLIGHT9) );
//
//	p_light.Diffuse.r = p_light.Ambient.r = 1.0f;
//	p_light.Diffuse.g = p_light.Ambient.g = 1.0f;
//	p_light.Diffuse.b = p_light.Ambient.b = 1.0f;
//	p_light.Diffuse.a = p_light.Ambient.a = 1.0f;
//	p_light.Range = (float)range;
//
//	switch(type)
//	{
//		case D3DLIGHT_POINT:
//			p_light.Type = D3DLIGHT_POINT;
//			p_light.Position = position;
//			p_light.Attenuation0 = 0.1f;
//			break;
//
//		case D3DLIGHT_SPOT:
//			p_light.Type = D3DLIGHT_SPOT;
//			p_light.Position = position;
//			p_light.Direction = direction;
//			p_light.Theta = 0.5f;
//			p_light.Phi = 1.0f;
//			p_light.Falloff = 1.0f;
//			p_light.Attenuation0 = 1.0f;
//			break;
//
//		case D3DLIGHT_DIRECTIONAL:
//		default:
//			p_light.Type = D3DLIGHT_DIRECTIONAL;
//			//create a normalized direction 
//			D3DXVec3Normalize( (D3DXVECTOR3*)&p_light.Direction, &direction );
//			break;
//	}
//
//	//enable the light
//	Update();
//	Show();
//}
int Direct3D_Init( HWND window, int width, int height, int colordepth, bool fullscreen )
{
    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d == NULL) return 0;

    //set configuration options for Direct3D
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.hDeviceWindow = window;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0; 
	d3dpp.Windowed = (!fullscreen);
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = 1;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL; 
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;

    //create the Direct3D device
    d3d->CreateDevice( 
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,  &d3ddev);
    if ( d3ddev == NULL) return 0; 

	d3ddev->Clear(0, NULL, 0, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

	//create D3DXSprite object
	D3DXCreateSprite( d3ddev, &d3dxsprite );

	//Set Default Material
    D3DMATERIAL9 mat;
	memset(&mat, 0, sizeof(mat));
	mat.Diffuse.r = mat.Ambient.r = 1.0f;
	mat.Diffuse.g = mat.Ambient.g = 1.0f;
	mat.Diffuse.b = mat.Ambient.b = 1.0f;
	mat.Diffuse.a = mat.Ambient.a = 1.0f;
	d3ddev->SetMaterial(&mat);

    return 1;
}

void Direct3D_Run()
{
	static int frame = 0;
	static int starttime = 0;

	//clear the scene 
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,100), 1.0f, 0);

	//start rendering
    if (d3ddev->BeginScene())
    {

		//set rotation matrix
		D3DXMATRIX matRotate;
		static float y = 0.0;
		y += 0.0001;
		D3DXMatrixRotationY(&matRotate, y);
	    d3ddev->SetTransform(D3DTS_WORLD, &matRotate);

		if (wireframe)
			d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); 
		else
			d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		sphere->DrawSubset(0);


		d3dxsprite->Begin(D3DXSPRITE_ALPHABLEND);
		d3dxsprite->End();
        d3ddev->EndScene();
    }

    //copy the back buffer to the screen
    d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Direct3D_Close()
{
	d3dxsprite->Release();
	d3ddev->Release();
	d3d->Release();
}

LPDIRECT3DTEXTURE9 LoadTexture (char *filename)
{
    LPDIRECT3DTEXTURE9 texture = NULL; //the texture pointer
    D3DXIMAGE_INFO info; //struct for reading bitmap header

	//get width and height from bitmap file
    HRESULT result = D3DXGetImageInfoFromFile (filename, &info);
    if (result != D3D_OK)
        return NULL;

	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx ( 
        d3ddev,              //Direct3D device object
        filename,            //bitmap filename
        info.Width,          //bitmap image width
        info.Height,         //bitmap image height
        1,                   //mip-map levels (1 for no chain)
        D3DPOOL_DEFAULT,     //the type of surface (standard)
        D3DFMT_UNKNOWN,      //surface format (default)
        D3DPOOL_DEFAULT,     //memory class for the texture
        D3DX_DEFAULT,        //image filter
        D3DX_DEFAULT,        //mip filter
        D3DCOLOR_XRGB(255,0,255),
        &info,               //bitmap file info (from loaded file)
        NULL,                //color palette
        &texture );          //destination texture

    //make sure the texture was loaded correctly
    if (result != D3D_OK) return NULL;
    return texture;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message)  
    {
		 case WM_DESTROY:
			 gameover = true;
             PostQuitMessage(0);
             break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

ATOM MyRegisterClass (HINSTANCE hInstance) 
{
  //create the window class structure
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX); 
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC) WinProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = NULL;
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = APPTITLE;
  wc.hIconSm       = NULL;
  return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) 
{
  window = CreateWindow(
	APPTITLE,              //window class
	APPTITLE,              //title bar
	WS_OVERLAPPEDWINDOW,   //window style
	CW_USEDEFAULT,         //x position of window
	CW_USEDEFAULT,         //y position of window
	1024,                   //width of the window
	768,                   //height of the window
	NULL,                  //parent window
	NULL,                  //menu
	hInstance,             //application instance
	NULL);                 //window parameters

  if (!window) return FALSE;
  ShowWindow (window, nCmdShow);
  UpdateWindow (window);
  return TRUE;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg;
  MyRegisterClass(hInstance);
  if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	//initialize Direct3D
	Direct3D_Init(window, SCREENW, SCREENH, 32, false);

	//set up the camera
	Set_Camera(0.0,1.0,-30.0);

	//create a point light
	D3DXVECTOR3 pos(0.0f,35.0f,0.0f);
	Create_Point_Light(0, pos, 35);

	//create a sphere
	D3DXCreateSphere(d3ddev, 5.0f, 20, 20, &sphere, NULL);


  while (!gameover)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

	Direct3D_Run();

  }
  Direct3D_Close();
  return 1;
}