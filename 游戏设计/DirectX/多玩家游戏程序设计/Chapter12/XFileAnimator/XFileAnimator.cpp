//###################################################################################
//#																					#
//#			Chapter 12 - Direct X Graphics Fundamentals								#		
//#																					#
//#						Animates an X-File											#
//#																					#
//#						Todd Barron, 02/18/2001										#
//#																					#
//###################################################################################

#define INITGUID
#define WIN32_LEAN_AND_MEAN	// No MFC
#include <d3d8.h>
#include <d3dx8.h>
#include <stdio.h>
#include "dxutil.h"

#define PI 3.1415926535897932384626433832795
#define DegToRad(deg) ((deg/180.0f)*PI)

// Direct 3D Globals
LPDIRECT3D8				pD3D;
LPDIRECT3DDEVICE8		pd3dDevice;
D3DXMATRIX				matProj;		// Projection Data
D3DXMATRIX				matCameraView;	// Camera Data
D3DXVECTOR3				vecCameraSource;
D3DXVECTOR3				vecCameraTarget;
LPD3DXMESH				pMesh;
D3DMATERIAL8			*pMeshMaterials;
LPDIRECT3DTEXTURE8		*pMeshTextures;
DWORD					dwNumMaterials;
LPD3DXBUFFER			pD3DXMtrlBuffer;
float					fRotation = 0.0f;

// Windows Globals
const char	*szWndClass		= "XFileAnimator";
const char	*szProgramName	= "XFileAnimator Example";
HINSTANCE	g_hInstance;

// Function Prototypes
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT hrInit3D( HWND hWnd );
void vCleanup(void);
void vRenderScene(void);
void vSetupView(void);
HRESULT hLoadXFile(char *szName);

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

	// Setup global window instance
	g_hInstance = hInstance;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if( hrInit3D(hWnd) == E_FAIL ) {
		exit(1);
	}

	// Load the X-File Object
	hLoadXFile("3DData//droid_still.x");

	// Setup the view
	vSetupView();

	// Process messages until the program is terminated
	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
			vRenderScene();
		}
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
		case WM_KEYDOWN:
			// Handle any non-accelerated key commands
			switch (wParam)
			{
			case VK_ESCAPE:
				break;
				// Left Arrow Key
			case 37:
				fRotation += 2.0f;
				break;
				// Right Arrow Key
			case 39:
				fRotation -= 2.0f;
				break;
			default:
				break;
			}
			break;
		default:
			break;
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
		// Try 32-bits
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D32;
		if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&pd3dDevice ) ) )
		{
			return E_FAIL;
		}
    }

	// Turn on the zbuffer
    pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    // Turn on ambient lighting 
    pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

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
	vecCameraSource.y = 35.0f;
	vecCameraSource.z = -50.0f;
	// Set what camera is looking at
	vecCameraTarget.x = 0.0f;
	vecCameraTarget.y = 10.0f;
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
	// Release X-File Objects
	SAFE_RELEASE(pMesh);
	SAFE_DELETE_ARRAY(pMeshMaterials)
	SAFE_DELETE_ARRAY(pMeshTextures);
	SAFE_RELEASE(pD3DXMtrlBuffer);
	// Release 3D system objects
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
	D3DXMATRIX	matRotation;
	int			mat;
		
	// Clear the backbuffer and the zbuffer
    pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	// Begin Rendering
	pd3dDevice->BeginScene();
	
	//
	// Initialization
	//
	
	// Set the rotation
	D3DXMatrixRotationY( &matRotation, (float)DegToRad(fRotation) );
	pd3dDevice->SetTransform(D3DTS_WORLD, &matRotation);
	
	// Render the objects
	for( mat = 0 ; mat < (signed)dwNumMaterials ; mat++ ) {
		// Activate the material
		pd3dDevice->SetMaterial( &pMeshMaterials[mat] );
		// Set the appropriate texture
		pd3dDevice->SetTexture( 0, pMeshTextures[mat] );
		// Draw the mesh subset
		pMesh->DrawSubset( mat );
	}

	// Stop Rendering
	pd3dDevice->EndScene();
	// Output the scene
	pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

//-----------------------------------------------------------------------------
// Name: hLoadXFile()
// Desc: Loads an X-File into global memory space
//-----------------------------------------------------------------------------
HRESULT hLoadXFile(char *szName)
{
	HRESULT	hResult = S_OK;
	int		i;
	char	szFullPath[256];

	dwNumMaterials = 0;
	
	// Load Geometry
	if( FAILED( D3DXLoadMeshFromX( 
		szName, 
		D3DXMESH_SYSTEMMEM, 
		pd3dDevice, 
		NULL, 
		&pD3DXMtrlBuffer, 
		&dwNumMaterials, 
		&pMesh ) ) ) {
		return(-1);
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	// Allocate memory for materials and textures
	pMeshMaterials = new D3DMATERIAL8[dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE8[dwNumMaterials];

	// Load in the materials and textures
	for( i = 0; i < (signed)dwNumMaterials ; i++ ) {
		// Copy the material
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// Set the ambient color for the material (D3DX does not do this)
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		sprintf(szFullPath,"3DData//%s",d3dxMaterials[i].pTextureFilename);
		// Create the texture
		if( FAILED( D3DXCreateTextureFromFile( 
			pd3dDevice,
			szFullPath,
			&pMeshTextures[i] ) ) ) {
				delete pMeshTextures[i];
				pMeshTextures[i] = NULL;
		}
	}
	// Release the material buffer
	SAFE_RELEASE(pD3DXMtrlBuffer);

	return( hResult );
}
