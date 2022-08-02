/*
	Simple Shader example that draws a sphere as a black wireframe
*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

const char *APPTITLE = "Wireframe Mesh Vertex Shader Example";
const int SCREENW = 1024;
const int SCREENH = 768;
HWND window;
bool gameover = false;

LPDIRECT3D9 d3d = NULL; 
LPDIRECT3DDEVICE9 d3ddev = NULL; 
D3DXMATRIX mProj, mView, mWorld, mViewProj;
D3DXMATRIX mTrans, mRot, mScale;
LPD3DXMESH teapot1;
ID3DXEffect *shader1 = 0;
ID3DXBuffer *errors = 0;


void Set_Camera(float x,float y,float z)
{
	double p_fov = D3DX_PI / 4.0;
	double p_aspectRatio = 1024 / 768;
	double p_nearRange = 1.0;
	double p_farRange = 2000.0;
    D3DXVECTOR3 p_updir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 p_position = D3DXVECTOR3(x, y, z);
	D3DXVECTOR3 p_rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 p_target = D3DXVECTOR3(0.0f,1.0f,0.0f);

    //set the camera's view and perspective matrix
    D3DXMatrixPerspectiveFovLH(&mProj, (float)p_fov, (float)p_aspectRatio, (float)p_nearRange, (float)p_farRange);
    D3DXMatrixLookAtLH(&mView, &p_position, &p_target, &p_updir);

	//optimization
	mViewProj = mView * mProj;
}


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
    d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp,  &d3ddev);
    if (d3ddev == NULL) return 0; 

	//create a teapot
	D3DXCreateTeapot(d3ddev, &teapot1, NULL);

	//load the effect file
	D3DXCreateEffectFromFile(d3ddev, "Shader.fx", 0, 0,	D3DXSHADER_DEBUG, 0, &shader1, &errors);
	if (errors) {
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
		return 0;
	}
	//get the technique 
	shader1->SetTechnique("technique1");

    return 1;
}

void Direct3D_Run()
{
	static float y = 0.0;
	UINT numPasses = 0;

	//clear the scene 
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(250,250,250), 1.0f, 0);

	//transform the teapot
	y += 0.001;
	D3DXMatrixRotationYawPitchRoll(&mRot, y, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&mScale, 5.0f, 5.0f, 5.0f);


	//pass the matrix to the shader via a parameter
	mWorld = mRot * mScale * mTrans;

	//shader1->SetMatrix( "matrix_parameter", &(mWorld*mViewProj));
	shader1->SetMatrix("matWorld", &mWorld);
	shader1->SetMatrix("matViewProj", &mViewProj);


	//rendering
    if (d3ddev->BeginScene())
    {
		//shader 
		shader1->Begin(&numPasses, 0);
		for (int i=0; i<numPasses; ++i)
		{
			shader1->BeginPass(i);

			teapot1->DrawSubset(0);

			shader1->EndPass();
		}
		shader1->End();
        d3ddev->EndScene();
    }
    d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Direct3D_Close()
{
	teapot1->Release();
	d3ddev->Release();
	d3d->Release();
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


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

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
	RegisterClassEx(&wc);

	window = CreateWindow( APPTITLE, APPTITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREENW, SCREENH, NULL, NULL, hInstance, NULL); 
	if (!window) return 1;
	ShowWindow (window, nCmdShow);
	UpdateWindow (window);

	//initialize Direct3D
	Direct3D_Init(window, SCREENW, SCREENH, 32, false);

	//set up the camera
	Set_Camera(0.0,10.0,-30.0);

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