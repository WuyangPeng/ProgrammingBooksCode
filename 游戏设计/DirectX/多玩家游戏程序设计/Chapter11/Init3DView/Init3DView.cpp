//###################################################################################
//#																					#
//#			Chapter 12 - Direct X Graphics Fundamentals								#		
//#																					#
//#						Initializes the 3D Environment & Sets up view				#
//#																					#
//#						Todd Barron, 01/17/2001										#
//#																					#
//###################################################################################

#define INITGUID
#define WIN32_LEAN_AND_MEAN	// No MFC
#include <d3d8.h>
#include <d3dx8.h>
#include <stdio.h>

// Direct 3D Globals
LPDIRECT3D8			pD3D;
LPDIRECT3DDEVICE8	pd3dDevice;
D3DXMATRIX			matProj;		// Projection Data
D3DXMATRIX			matCameraView;	// Camera Data
D3DXVECTOR3			vecCameraSource;
D3DXVECTOR3			vecCameraTarget;

// Class name & app name
const char	*szWndClass		= "Init3DView";
const char	*szProgramName	= "Init3DView Example";

// Windows Globals
HINSTANCE	g_hInstance;
HWND		g_hWnd;

// Function Prototypes
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT hrInit3D( HWND hWnd );
void vCleanup(void);
void vRenderScene(void);
void vSetupView(void);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS	wc;
	HWND		hWnd;
	MSG			msg;

	// Set up and register window class
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MsgProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szWndClass;
    RegisterClass(&wc);

    // Create a window
    hWnd = CreateWindowEx(WS_EX_TOPMOST,
                          szWndClass,
                          szProgramName,
                          WS_OVERLAPPEDWINDOW,
                          0,
                          0,
                          640,
                          480,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

	// Setup global window handles
	g_hInstance = hInstance;
	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if( hrInit3D(hWnd) == E_FAIL ) {
		exit(1);
	}

	// Setup the camera
	vSetupView();

	// Display the 3d Environment
	vRenderScene();

	// Process messages until the program is terminated
	while( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	// Cleanup the environment
	vCleanup();

	return(msg.wParam);
};

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The application's message loop
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
			return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: hrInit3D()
// Desc: Initializes Direct 3D
//-----------------------------------------------------------------------------
HRESULT hrInit3D( HWND hWnd ) 
{
	D3DPRESENT_PARAMETERS	d3dpp; 
	D3DDISPLAYMODE			d3ddm;
	RECT					rcWindowBounds;    // Saved window bounds for mode switches
    RECT					rcWindowClient;    // Saved client area size for mode switches

    // Create the D3D object.
    if( NULL == ( pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
        return E_FAIL;
    
	// Get adapter settings
    if( FAILED( pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return E_FAIL;

	// Get the size of the window
	GetWindowRect( hWnd, &rcWindowBounds );
    GetClientRect( hWnd, &rcWindowClient );

	// Clear out device parameters
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	
	//
	// Setup device parameters
	//
	d3dpp.hDeviceWindow				= hWnd; 
	d3dpp.BackBufferWidth			= (rcWindowClient.right - rcWindowClient.left); 
	d3dpp.BackBufferHeight			= (rcWindowClient.bottom - rcWindowClient.top); 
	d3dpp.BackBufferFormat			= d3ddm.Format; 
	d3dpp.BackBufferCount			= 1;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_FLIP;
	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE; 
	d3dpp.EnableAutoDepthStencil	= TRUE; 
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.Windowed					= TRUE;

    // Create the D3DDevice
    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: vSetupView()
// Desc: Sets up the viewport and camera
//-----------------------------------------------------------------------------
void vSetupView(void)
{
	// Set where camera is viewing from
	vecCameraSource.x = 0.0f;
	vecCameraSource.y = 0.0f;
	vecCameraSource.z = 10.0f;
	// Set what camera is looking at
	vecCameraTarget.x = 0.0f;
	vecCameraTarget.y = 0.0f;
	vecCameraTarget.z = 0.0f;

	// Setup Camera View
	D3DXMatrixLookAtLH( &matCameraView, 
						&vecCameraSource, 
						&vecCameraTarget, 
						&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	// Tell the device to use the camera view for the viewport
	pd3dDevice->SetTransform( D3DTS_VIEW, &matCameraView );

	// Setup Projection 
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	// Tell the device to use the above matrix for projection
	pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//-----------------------------------------------------------------------------
// Name: vCleanup()
// Desc: Cleans up Direct X Graphics & Other allocations
//-----------------------------------------------------------------------------
void vCleanup(void)
{
	if( pd3dDevice != NULL )
		pd3dDevice->Release();
	if( pD3D != NULL )
		pD3D->Release();
	UnregisterClass( szWndClass, g_hInstance );
}

//-----------------------------------------------------------------------------
// Name: vRenderScene()
// Desc: Displays the 3d scene
//-----------------------------------------------------------------------------
void vRenderScene(void)
{
	// Clear the scene
	pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150,150,255), 1.0f, 0 );
	pd3dDevice->BeginScene();
	pd3dDevice->EndScene();
	// Output the scene
	pd3dDevice->Present( NULL, NULL, NULL, NULL );
}



