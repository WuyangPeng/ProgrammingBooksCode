//###################################################################################
//#																					#
//#			Chapter 16 - RPGQuest													#
//#																					#
//#						Complete Client-Server Game									#
//#																					#
//#						Todd Barron, 03/12/2001										#
//#																					#
//###################################################################################
#include "RPGQuest.h"
#include "..\\Common\\PacketInfo.h"

void vChangeZones(int zone);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX	wndclass;
	HWND		hWnd;
	MSG			msg;
	DWORD		dwGovernor = timeGetTime();
	HRESULT		hr;
	
	// Set up window attributes
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= MsgProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szWndClass;	// Registered Class Name
	wndclass.hIconSm		= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
		
	if( RegisterClassEx( &wndclass ) == 0 ) {
		// Do error logic here
		exit(1);
	}
	
	// Create the main window
	hWnd = CreateWindow(	
		szWndClass,				// Class Name
		szProgramName,			// Name Displayed on Title Bar
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL );

	// Setup global window instance
	g_hInstance = hInstance;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Clear out player information	
	vInitializeObjects();
	
	// Setup Communications System
	if( (hrInitializeDirectPlay(hWnd)) == -1 ) {
		MessageBox( hWnd, "DirectPlay Error", "Unable to initialize Direct Play.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}
	
	if( hrInit3D(hWnd) == E_FAIL ) {
		MessageBox( hWnd, "Direct3D Error", "Unable to initialize Direct 3D.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}

	hr = hrInitDirectInput();
	if( hr == INPUTERROR_NODI ) {
		MessageBox( hWnd, "DirectInput Error", "Unable to initialize Direct Input.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}
	
	hr = hrInitKeyboard(hWnd);
	if( hr == INPUTERROR_NOKEYBOARD ) {
		MessageBox( hWnd, "DirectInput Error", "Unable to initialize Keyboard.", MB_ICONERROR );
		vCleanup();
		exit(1);
	}

	// Setup the 3D models and textures
	vInitGeometry();
	// Setup the view
	vSetupView();
	// Create scene lights
	vCreateLights();
	// Init sound system
	vInitSoundEngine(hWnd);

	LocalPlayer.bActive = 1;

	vAddMessage("Connecting to the Game Server...",D3DCOLOR_RGBA(255, 255, 255, 255));
	vRenderScene();

	// Connect to the game server
	if( (hrJoinGame(hWnd) ) == -1 ) {
		MessageBox( hWnd, "Unable to connect to game server!", "Connection Error!", MB_ICONERROR );
		vCleanup();
		exit(1);
	}

	vAddMessage("Connected to the Game Server",D3DCOLOR_RGBA(255, 255, 255, 255));
	vRenderScene();

	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message != WM_QUIT ) {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
			// Dont update game more than 30 FPS
			if( timeGetTime() > dwGovernor+33 ) {
				dwGovernor = timeGetTime();
				// Update players and execute pending actions
				vUpdateObjects();
				vRenderScene();
			}
			// Update keys
			hrReadKeyboard();
			if( diks[DIK_LEFT] ) {
				bTurnLeft = 1;
			}
			if( diks[DIK_RIGHT] ) {
				bTurnRight = 1;
			}
			if( diks[DIK_UP] ) {
				bAccelerate = 1;
			}
			if( diks[DIK_DOWN] ) {
				bDeaccelerate = 1;
			}
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
		case WM_SETCURSOR:
            // Turn off Windows cursor in fullscreen mode
            if( !g_bWindowed )
            {
                SetCursor( NULL );
                return TRUE;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage( 0 );
			return 0;
		case WM_KEYDOWN:
			// Handle any non-accelerated key commands
            switch (wParam)
            {
                case VK_ESCAPE:
					PostMessage(hWnd, WM_QUIT, 0, 0);
                    return 0;
			}
			break;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: vCleanup()
// Desc: Cleans up Direct X Graphics & Other allocations
//-----------------------------------------------------------------------------
void vCleanup(void)
{
	int i;
	
	// Release Graphics
	for( i = 0 ; i < MAX_TEXTURES ; i++ ) {
		SAFE_RELEASE( g_pTexture[i] );
	}
	
	SAFE_RELEASE( pD3DXFont );
	SAFE_RELEASE( pd3dDevice );
	SAFE_RELEASE( pD3D );
	if( hFont ) {
		DeleteObject( hFont );
		hFont = NULL;
	}
	// Release Sounds
	SAFE_DELETE( g_GameSounds.gsFire );
	// Release Direct Play Objects
	SAFE_RELEASE( g_pDeviceAddress );
    SAFE_RELEASE( g_pHostAddress );
	if( g_pDP ) {
		// Close our connection
        g_pDP->Close(0);
		// Release the DirectPlay object
        SAFE_RELEASE( g_pDP );
    }
	DeleteCriticalSection( &g_csModifyPlayer );
	// Release Keyboard
	if( pKeyboard ) 
        pKeyboard->Unacquire();
	SAFE_RELEASE( pKeyboard );
	SAFE_RELEASE( pDI );

	// Uninitialize the COM library
	CoUninitialize();
	// Clear the Window class
	UnregisterClass( szWndClass, g_hInstance );
}

//-----------------------------------------------------------------------------
// Name: vGetVelocity()
// Desc: Retrieves the X and Y vector for a given angle
//-----------------------------------------------------------------------------
void vGetVelocity( float fAngle, float &vx, float &vz )
{
	double	fRad;

	// Convert to radians
	fRad = DegToRad(fAngle);
	// Figure the vector
	vx = (float)sin(fRad);
	vz = (float)cos(fRad);
}

//-----------------------------------------------------------------------------
// Name: vInitializeObjects()
// Desc: Initializes game object structures
//-----------------------------------------------------------------------------
void vInitializeObjects(void)
{
	int i;

	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		memset(&PlayerInfo[i],0,sizeof(CLIENT_PLAYER_INFORMATION));
	}
	memset(&LocalPlayer,0,sizeof(CLIENT_PLAYER_INFORMATION));

	for( i = 0 ; i < MAX_TEXTURES ; i++ ) {
		g_pTexture[i] = NULL;
	}

	g_GameSounds.gsFire = NULL;
}

//-----------------------------------------------------------------------------
// Name: iAddPlayer()
// Desc: Adds a player to the rendering system
//-----------------------------------------------------------------------------
int iAddPlayer(int id, CLIENT_PLAYER_INFORMATION pinfo)
{
	int		i;
	char	szMessage[256];

	// Assign if either already used, or free slot
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( !PlayerInfo[i].bActive || PlayerInfo[i].iPlayerID == id ) {
			break;
		}
	}	
	// No free slots
	if( i == MAX_PLAYERS )
		return(-1);

	sprintf(szMessage,"%s Is In The Zone @ %.2f,%.2f",pinfo.szPlayerName,pinfo.vecCurPos.x,pinfo.vecCurPos.z);
	vAddMessage(szMessage,D3DCOLOR_RGBA(255, 0, 255, 255));

	EnterCriticalSection( &g_csModifyPlayer );
	PlayerInfo[i].bActive = 1;
	memcpy(&PlayerInfo[i],&pinfo,sizeof(CLIENT_PLAYER_INFORMATION));
	PlayerInfo[i].iPlayerID = id;
	LeaveCriticalSection( &g_csModifyPlayer );

	return(i);
}

//-----------------------------------------------------------------------------
// Name: vInitSoundEngine()
// Desc: Initializes sound system
//-----------------------------------------------------------------------------
void vInitSoundEngine(HWND hWnd)
{
	SoundEngine.hWnd = hWnd;
	if( !FAILED(SoundEngine.hrInitSoundSystem()) ) {
		g_GameSounds.gsFire = new GameSound;
		SoundEngine.hrLoadSound("data\\sfx\\attack.wav",g_GameSounds.gsFire);
	}
}

//-----------------------------------------------------------------------------
// Name: vUpdateObjects()
// Desc: Updates players position and settings, sends command packets
//-----------------------------------------------------------------------------
void vUpdateObjects(void)
{
	float			fRot,fx,fz;
	PacketAngle		pacAngle;
	PacketVelocity	pacVel;
	HRESULT			hReturn;
	void			*packet;
	int				i;
	float			fMultiplier = 0.0f;

	EnterCriticalSection( &g_csModifyPlayer );
	// Multiply the updates based on the server's speed
	fMultiplier = (float)iUpdates;
	fRot = LocalPlayer.fRot;
	// Accelerate
	if( bAccelerate ) {
		bAccelerate = 0;
		if( LocalPlayer.fVelocity < 2.0f )
			LocalPlayer.fVelocity += 1.0f;
		pacVel.dwSize = sizeof(PacketVelocity);
		pacVel.dwType = PACKET_TYPE_VELOCITY;
		pacVel.fVelocity = (float)LocalPlayer.fVelocity;
		// Convert the packet to a void stream
		packet = (VOID*)&pacVel;
		// Send the velocity packet
		hReturn = hrSendClientMessage(PACKET_TYPE_VELOCITY,packet);
	}
	// Deaccelerate
	if( bDeaccelerate ) {
		bDeaccelerate = 0;
		if( LocalPlayer.fVelocity > -1.0f )
			LocalPlayer.fVelocity -= 1.0f;
		pacVel.dwSize = sizeof(PacketVelocity);
		pacVel.dwType = PACKET_TYPE_VELOCITY;
		pacVel.fVelocity = (float)LocalPlayer.fVelocity;
		// Convert the packet to a void stream
		packet = (VOID*)&pacVel;
		// Send the velocity packet
		hReturn = hrSendClientMessage(PACKET_TYPE_VELOCITY,packet);
	}
	// Rotate Left
	if( bTurnLeft ) {
		bTurnLeft = 0;
				
		LocalPlayer.fRot -= 5.0f;
		if( LocalPlayer.fRot < 0.0f ) 
			LocalPlayer.fRot = 350.0f;

		pacAngle.dwSize = sizeof(PacketAngle);
		pacAngle.dwType = PACKET_TYPE_ANGLE;
		pacAngle.fAngle = LocalPlayer.fRot;
		// Convert the packet to a void stream
		packet = (VOID*)&pacAngle;
		// Send the rotation packet
		hReturn = hrSendClientMessage(PACKET_TYPE_ANGLE,packet);
	}
	// Rotate Right
	if( bTurnRight ) {
		bTurnRight = 0;
		LocalPlayer.fRot += 5.0f;
		if( LocalPlayer.fRot >= 360.0f ) 
			LocalPlayer.fRot = 0.0f;
		pacAngle.dwSize = sizeof(PacketAngle);
		pacAngle.dwType = PACKET_TYPE_ANGLE;
		pacAngle.fAngle = LocalPlayer.fRot;
		// Convert the packet to a void stream
		packet = (VOID*)&pacAngle;
		// Send the angle packet
		hReturn = hrSendClientMessage(PACKET_TYPE_ANGLE,packet);
	}

	// Update players
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		// Update the player if active
		if( PlayerInfo[i].bActive ) {
			// Update the player if in the zone
			if( PlayerInfo[i].iZone == iZone ) {
				// Get the players velocity
				vGetVelocity(PlayerInfo[i].fRot,fx,fz);
				fx *= fMultiplier;
				fz *= fMultiplier;
				
				PlayerInfo[i].vecCurPos.x += (float)(fx*PlayerInfo[i].fVelocity)*-1;
				PlayerInfo[i].vecCurPos.z += (float)(fz*PlayerInfo[i].fVelocity)*-1;
								
				// Check if mech has moved far enough to animate it
				if( (PlayerInfo[i].vecLastPos.x-PlayerInfo[i].vecCurPos.x) > 2.0f || (PlayerInfo[i].vecLastPos.x-PlayerInfo[i].vecCurPos.x) < -2.0f ) {
					if( PlayerInfo[i].fVelocity > 0.0f ) 
						PlayerInfo[i].iFrame++;
					else
						PlayerInfo[i].iFrame--;
					PlayerInfo[i].vecLastPos.x = PlayerInfo[i].vecCurPos.x;
					PlayerInfo[i].vecLastPos.z = PlayerInfo[i].vecCurPos.z;
				}
				else if( (PlayerInfo[i].vecLastPos.z-PlayerInfo[i].vecCurPos.z) > 2.0f || (PlayerInfo[i].vecLastPos.z-PlayerInfo[i].vecCurPos.z) < -2.0f ) {
					if( PlayerInfo[i].fVelocity > 0.0f ) 
						PlayerInfo[i].iFrame++;
					else
						PlayerInfo[i].iFrame--;
					PlayerInfo[i].vecLastPos.x = PlayerInfo[i].vecCurPos.x;
					PlayerInfo[i].vecLastPos.z = PlayerInfo[i].vecCurPos.z;
				}
				
				// Check if animation needs to loop
				if( PlayerInfo[i].iFrame >= 12 ) 
					PlayerInfo[i].iFrame = 0;
				else if( PlayerInfo[i].iFrame < 0 ) 
					PlayerInfo[i].iFrame = 11;
				
				PlayerInfo[i].fVelocity *= 0.5f;
			}
		}
	}

	// Update Ourselves
	vGetVelocity(LocalPlayer.fRot,fx,fz);
	LocalPlayer.vecCurPos.x += (float)(fx*LocalPlayer.fVelocity)*-1;
	LocalPlayer.vecCurPos.z += (float)(fz*LocalPlayer.fVelocity)*-1;
	LocalPlayer.fVelocity *= 0.5f;
	// Reset server speed
	iUpdates = 0;
	LeaveCriticalSection( &g_csModifyPlayer );
}

//-----------------------------------------------------------------------------
//
//
//
//							DIRECT 3D FUNCTIONS
//
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: hrInit3D()
// Desc: Initializes Direct 3D
//-----------------------------------------------------------------------------
HRESULT hrInit3D( HWND hWnd ) 
{
	D3DPRESENT_PARAMETERS	d3dpp; 
	HRESULT					hResult;
	RECT					rcWindowBounds;    // Saved window bounds for mode switches
	RECT					rcWindowClient;    // Saved client area size for mode switches
	D3DAdapterInfo			*pAdapterInfo = &g_Adapters[g_dwAdapter];
	D3DDeviceInfo			*pDeviceInfo  = &pAdapterInfo->devices[pAdapterInfo->dwCurrentDevice];
	D3DModeInfo				*pModeInfo    = &pDeviceInfo->modes[pDeviceInfo->dwCurrentMode];
	
	// Create the D3D object.
	if( NULL == ( pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) ) {
		MessageBox( hWnd, "Direct3D Error", "Unable to initialize Direct3D, please check version.", MB_ICONERROR );
		return(E_FAIL);
	}
	
	// Build a list of available devices
	hResult = hrBuildDeviceList(hWnd);
	if( hResult == VIDEODEVICEERROR_NOCOMPATIBLE ) {
		MessageBox( hWnd, "Adapter Error", "No compatible 3D adapters found.", MB_ICONERROR );
		return(E_FAIL);
	}
	else if( hResult == VIDEODEVICEERROR_NOWINDOWED ) {
		MessageBox( hWnd, "Adapter Error", "No available windowable 3D adapter found, please switch to 16 or 32 bit mode.", MB_ICONERROR );
		return(E_FAIL);
	}
	
	// Get the size of the window
	GetWindowRect( hWnd, &rcWindowBounds );
	GetClientRect( hWnd, &rcWindowClient );
	
	// Set to fullscreen
	if( !g_bWindowed ) 
		SetWindowLong( hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
	
	// Set temp pointers
	pAdapterInfo = &g_Adapters[g_dwAdapter];
	pDeviceInfo  = &pAdapterInfo->devices[pAdapterInfo->dwCurrentDevice];
	pModeInfo    = &pDeviceInfo->modes[pDeviceInfo->dwCurrentMode];

	// Set up the presentation parameters
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed					= pDeviceInfo->bWindowed;
	d3dpp.BackBufferCount			= 1;
	d3dpp.MultiSampleType			= pDeviceInfo->MultiSampleType;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_FLIP;
	d3dpp.EnableAutoDepthStencil	= g_bUseDepthBuffer;
	d3dpp.AutoDepthStencilFormat	= pModeInfo->DepthStencilFormat;
	d3dpp.hDeviceWindow				= hWnd;
	
	// Run this code if in windowed mode
	if( g_bWindowed ) {
		d3dpp.BackBufferWidth  = (rcWindowClient.right - rcWindowClient.left);
		d3dpp.BackBufferHeight = (rcWindowClient.bottom - rcWindowClient.top);
		d3dpp.BackBufferFormat = pAdapterInfo->d3ddmDesktop.Format;
	}
	// Run this code if in fullscreen mode
	else {
		d3dpp.BackBufferWidth  = pModeInfo->Width;
		d3dpp.BackBufferHeight = pModeInfo->Height;
		d3dpp.BackBufferFormat = pModeInfo->Format;
	}
	
	// Create the device
	hResult = pD3D->CreateDevice( g_dwAdapter, pDeviceInfo->DeviceType, hWnd, pModeInfo->dwBehavior, &d3dpp, &pd3dDevice );
	if( !SUCCEEDED(hResult) ) {
		MessageBox( hWnd, "Device Error", "Failed to create display device!", MB_ICONERROR );
		return(E_FAIL);
	}
	
	// Turn on the zbuffer
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	// Turn on ambient lighting 
	pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00101010 );
	
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: vUpdateCamera()
// Desc: Updates the camera position in the 3D scene
//-----------------------------------------------------------------------------
void vUpdateCamera(void)
{
	D3DXMATRIX			matRotation;

	// Set where camera is viewing from
	vecCameraSource.x = LocalPlayer.vecCurPos.x;
	vecCameraSource.y = 15.0f+LocalPlayer.vecCurPos.y;
	vecCameraSource.z = LocalPlayer.vecCurPos.z+1;
	// Set what camera is looking at
	vecCameraTarget.x = LocalPlayer.vecCurPos.x;
	vecCameraTarget.y = 15.0f+LocalPlayer.vecCurPos.y;
	vecCameraTarget.z = LocalPlayer.vecCurPos.z;
	// Setup Camera View
	D3DXMatrixLookAtLH( &matCameraView, 
		&vecCameraSource, 
		&vecCameraTarget, 
		&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	
	// Rotate the camera view now
	D3DXMatrixRotationY( &matRotation, -LocalPlayer.fRot/RADIAN_TO_DEGREES );
	
	matCameraView *= matRotation;
	
	// Tell the device to use the camera view for the viewport
	pd3dDevice->SetTransform( D3DTS_VIEW, &matCameraView );
}

//-----------------------------------------------------------------------------
// Name: vRenderScene()
// Desc: Displays the 3d scene
//-----------------------------------------------------------------------------
void vRenderScene(void)
{	
	RECT				rTemp4 = { 5, 5, 600, 30 };
	RECT				rTemp1 = { 5, (SCREEN_HEIGHT-65), 400, (SCREEN_HEIGHT) };
	char				szMessage[256];
	int					i;
	static DWORD		dwFrameTimer = 0;
	static int			iFrames = 0;
	static int			iFPS = 0;			
		
	// Update the time of day
	if( bUpdateTime ) {
		pd3dDevice->SetRenderState( D3DRS_AMBIENT, colorTimeColor );
		bUpdateTime = 0;
	}

	// Clear the backbuffer and the zbuffer
    pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	// Begin Rendering
	pd3dDevice->BeginScene();

	// Update the camera position
	vUpdateCamera();
	
	// Turn on texture filtering
	pd3dDevice->SetTextureStageState(0,D3DTSS_MINFILTER ,D3DTEXF_ANISOTROPIC);
	pd3dDevice->SetTextureStageState(0,D3DTSS_MAGFILTER ,D3DTEXF_ANISOTROPIC);

	// Display Players
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive && PlayerInfo[i].iZone == iZone )
			o3dPlayer.vDisplayXYZ(PlayerInfo[i].vecCurPos.x,12.0f,PlayerInfo[i].vecCurPos.z,0.0f,PlayerInfo[i].fRot,0.0f);
	}
	
	// Display the arena
	o3dZone[iZoneMap].vDisplayXYZ(0.0f,0.0f,0.0f);
		
	// Calculate the frame rate
	if( timeGetTime() > dwFrameTimer+1000 ) {
		iFPS = iFrames;
		dwFrameTimer = timeGetTime();
		iFrames = 1;
	}
	else {
		iFrames++;
	}
	// Display the player cords & fps
	sprintf(szMessage,"X = %.2f, Z = %.2f, FPS = %d, Rotation = %.2f",LocalPlayer.vecCurPos.x,LocalPlayer.vecCurPos.z,iFPS,LocalPlayer.fRot);
	pD3DXFont->DrawText(szMessage, -1, &rTemp4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	// Output message log
	for( i = iMessageLogPos ; i < iLastMessage ; i++ ) {
		rTemp1.bottom = SCREEN_HEIGHT;
		rTemp1.left = 15;
		rTemp1.right = SCREEN_WIDTH;
		rTemp1.top = (SCREEN_HEIGHT-200)+((i-iMessageLogPos)*12);
		pD3DXFont->DrawText(MessageLog[i].szMessage, -1, &rTemp1, DT_LEFT, MessageLog[i].color);
	}

	// Stop Rendering
	pd3dDevice->EndScene();
	// Output the scene
	if( (pd3dDevice->Present( NULL, NULL, NULL, NULL )) == D3DERR_DEVICELOST ) {
	}
}

//-----------------------------------------------------------------------------
// Name: vInitGeometry()
// Desc: Creates the geometry for the quad
//-----------------------------------------------------------------------------
void vInitGeometry(void)
{
	char	szFileName[256];
	float	fSizeX = 50.0f;
	float	fSizeY = 50.0f;
	DWORD	dwColor = D3DCOLOR_XRGB(255,255,255);

	sprintf(szFileName,"Data\\3DObjects\\rpgquest0.x");
	o3dZone[0].hLoad(szFileName,pd3dDevice);
	
	sprintf(szFileName,"Data\\3DObjects\\rpgquest1.x");
	o3dZone[1].hLoad(szFileName,pd3dDevice);

	sprintf(szFileName,"Data\\3DObjects\\rpgquest2.x");
	o3dZone[2].hLoad(szFileName,pd3dDevice);

	// Load the player (cubehead)
	sprintf(szFileName,"Data\\3DObjects\\cube_head.x");
	o3dPlayer.hLoad(szFileName,pd3dDevice);

	// Create the common text font
	hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PROOF_QUALITY, 0, "arial"); 
	D3DXCreateFont(pd3dDevice, hFont, &pD3DXFont); 
}

//-----------------------------------------------------------------------------
// Name: vCreateLights()
// Desc: Creates a point light and default material
//-----------------------------------------------------------------------------
void vCreateLights(void)
{
	D3DLIGHT8		d3dLight;
	
	// Clear out light structure
	ZeroMemory(&d3dLight, sizeof(D3DLIGHT8));
	d3dLight.Type = D3DLIGHT_POINT;
	
	d3dLight.Diffuse.r  = 1.0f;
	d3dLight.Diffuse.b  = 1.0f;
	d3dLight.Diffuse.g  = 1.0f;
	
	d3dLight.Position.x = 0.0f;
	d3dLight.Position.y = 50.0f;
	d3dLight.Position.z = 50.0f;
	d3dLight.Attenuation0 = 1.0f; 
	d3dLight.Attenuation1 = 0.0025f;
	d3dLight.Range      = 1000.0f;
	// Set the active light
    pd3dDevice->SetLight( 0, &d3dLight );
	// Enable the light
    pd3dDevice->LightEnable( 0, TRUE );

	d3dLight.Range        = 200.0f;
	d3dLight.Attenuation0 = 1.0f; 
	d3dLight.Attenuation1 = 0.01f;
	d3dLight.Diffuse.r  = 1.0f;
	d3dLight.Diffuse.g  = 0.0f;
	d3dLight.Diffuse.b  = 0.0f;
	d3dLight.Position.x = 200.0f;
	d3dLight.Position.y = 50.0f;
	d3dLight.Position.z = 200.0f;
	// Set the active light
    pd3dDevice->SetLight( 1, &d3dLight );
	// Enable the light
    pd3dDevice->LightEnable( 1, TRUE );

	d3dLight.Diffuse.r  = 0.0f;
	d3dLight.Diffuse.g  = 0.0f;
	d3dLight.Diffuse.b  = 1.0f;
	d3dLight.Position.x = -200.0f;
	d3dLight.Position.y = 50.0f;
	d3dLight.Position.z = 200.0f;
	// Set the active light
    pd3dDevice->SetLight( 2, &d3dLight );
	// Enable the light
    pd3dDevice->LightEnable( 2, TRUE );

	d3dLight.Diffuse.r  = 0.0f;
	d3dLight.Diffuse.g  = 1.0f;
	d3dLight.Diffuse.b  = 0.0f;
	d3dLight.Position.x = -200.0f;
	d3dLight.Position.y = 50.0f;
	d3dLight.Position.z = -200.0f;
	// Set the active light
    pd3dDevice->SetLight( 3, &d3dLight );
	// Enable the light
    pd3dDevice->LightEnable( 3, TRUE );

	d3dLight.Diffuse.r  = 1.0f;
	d3dLight.Diffuse.g  = 0.0f;
	d3dLight.Diffuse.b  = 1.0f;
	d3dLight.Position.x = 200.0f;
	d3dLight.Position.y = 50.0f;
	d3dLight.Position.z = -200.0f;
	// Set the active light
    pd3dDevice->SetLight( 4, &d3dLight );
	// Enable the light
    pd3dDevice->LightEnable( 4, TRUE );
	
	// Tell D3D to utilize lights
    pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//-----------------------------------------------------------------------------
// Name: vSetupView()
// Desc: Sets up the viewport and camera
//-----------------------------------------------------------------------------
void vSetupView(void)
{
	// Set where camera is viewing from
	vecCameraSource.x = -300.0f;
	vecCameraSource.y = 50.0f;
	vecCameraSource.z = 150.0f;
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
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/1.8f, 1.0f, 1.0f, 1800.0f );
	// Tell the device to use the above matrix for projection
	pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//-----------------------------------------------------------------------------
// Name: hrBuildDeviceList()
// Desc: Builds a list of available 3D devices for the application
//-----------------------------------------------------------------------------
HRESULT hrBuildDeviceList(HWND hWnd)
{
	const DWORD			dwNumDeviceTypes = 2;
	const char			*szDeviceDescs[] = { "HAL", "REF" };
	const D3DDEVTYPE	DeviceTypes[] = { D3DDEVTYPE_HAL, D3DDEVTYPE_REF };
	D3DDISPLAYMODE		modes[100];
	D3DFORMAT			formats[20];
	BOOL				bFormatConfirmed[20];
	DWORD				dwBehavior[20];
	D3DFORMAT			fmtDepthStencil[20];
	D3DAdapterInfo		*pAdapter;
	BOOL				bHALExists = FALSE;
	BOOL				bHALIsWindowedCompatible = FALSE;
	BOOL				bHALIsDesktopCompatible = FALSE;
	BOOL				bHALIsSampleCompatible = FALSE;
	DWORD				dwNumFormats;
	DWORD				dwNumModes;
	DWORD				dwNumAdapterModes;
	unsigned int		iAdapter,iMode,iDevice;
	DWORD				a,d,f,m;
	D3DDISPLAYMODE		DisplayMode;
	BOOL				bFoundVidMode = FALSE;
	D3DDeviceInfo		*pDevice;
	
	for( iAdapter = 0; iAdapter < pD3D->GetAdapterCount(); iAdapter++ ) {
		// Fill in adapter info
		pAdapter  = &g_Adapters[g_dwNumAdapters];
		pD3D->GetAdapterDisplayMode( iAdapter, &pAdapter->d3ddmDesktop );
		pAdapter->dwNumDevices    = 0;
		pAdapter->dwCurrentDevice = 0;
		
		// Enumerate all display modes on this adapter
		dwNumFormats      = 0;
		dwNumModes        = 0;
		dwNumAdapterModes = pD3D->GetAdapterModeCount( iAdapter );
		
		// Add the adapter's current desktop format to the list of formats
		formats[dwNumFormats++] = pAdapter->d3ddmDesktop.Format;
		
		// Loop through modes
		for( iMode = 0; iMode < dwNumAdapterModes; iMode++ ) {
			// Get the display mode attributes
			pD3D->EnumAdapterModes( iAdapter, iMode, &DisplayMode );
			
			// Filter out low-resolution modes
			if( (DisplayMode.Width < SCREEN_WIDTH) || (DisplayMode.Height < SCREEN_HEIGHT) )
				continue;
			
			// Check if the mode already exists
			for( m = 0; m < dwNumModes; m++ ) {
				if( ( modes[m].Width  == DisplayMode.Width  ) &&
					( modes[m].Height == DisplayMode.Height ) &&
					( modes[m].Format == DisplayMode.Format ) )
					break;
			}
			
			// If we found a new mode, add it to the list of modes
			if( m == dwNumModes ) {
				modes[dwNumModes].Width       = DisplayMode.Width;
				modes[dwNumModes].Height      = DisplayMode.Height;
				modes[dwNumModes].Format      = DisplayMode.Format;
				modes[dwNumModes].RefreshRate = 0;
				dwNumModes++;
				// Check if the mode's format already exists
				for( f = 0; f < dwNumFormats; f++ ) {
					if( DisplayMode.Format == formats[f] )
						break;
				}
				// If the format is new, add it to the list
				if( f == dwNumFormats )
					formats[dwNumFormats++] = DisplayMode.Format;
			}
		}
		
		// Add devices to adapter
		for( iDevice = 0; iDevice < dwNumDeviceTypes; iDevice++ ) {
			// Fill in device info
			pDevice                 = &pAdapter->devices[pAdapter->dwNumDevices];
			pDevice->DeviceType     = DeviceTypes[iDevice];
			pD3D->GetDeviceCaps( iAdapter, DeviceTypes[iDevice], &pDevice->d3dCaps );
			strcpy(pDevice->szDesc,szDeviceDescs[iDevice]);
			pDevice->dwNumModes     = 0;
			pDevice->dwCurrentMode  = 0;
			pDevice->bCanDoWindowed = FALSE;
			pDevice->bWindowed		= FALSE;
			pDevice->MultiSampleType = D3DMULTISAMPLE_NONE;
			
			// Check each format to see if it is compatible with the application
			for( f = 0; f < dwNumFormats; f++ ) {
				bFormatConfirmed[f] = FALSE;
				fmtDepthStencil[f] = D3DFMT_UNKNOWN;
				
				// Skip formats that cannot be used as render targets on this device
				if( FAILED( pD3D->CheckDeviceType( iAdapter, pDevice->DeviceType, formats[f], formats[f], FALSE ) ) )
					continue;
				
				if( pDevice->DeviceType == D3DDEVTYPE_HAL ) {
					// This system has a HAL device
					bHALExists = TRUE;
					// Check if Windowed mode is possible
					if( pDevice->d3dCaps.Caps2 & D3DCAPS2_CANRENDERWINDOWED ) {
						// HAL can run in a window for some mode
						bHALIsWindowedCompatible = TRUE;
						
						if( f == 0 ) {
							// HAL can run in a window for the current desktop mode
							bHALIsDesktopCompatible = TRUE;
						}
					}
				}
				// Confirm the device/format for HW vertex processing
				if( pDevice->d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) {
					if( pDevice->d3dCaps.DevCaps & D3DDEVCAPS_PUREDEVICE ) {
						dwBehavior[f] = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
						
						if( SUCCEEDED( hrConfirmDevice( &pDevice->d3dCaps, dwBehavior[f], formats[f] ) ) )
							bFormatConfirmed[f] = TRUE;
					}
					
					if ( FALSE == bFormatConfirmed[f] ) {
						dwBehavior[f] = D3DCREATE_HARDWARE_VERTEXPROCESSING;
						
						if( SUCCEEDED( hrConfirmDevice( &pDevice->d3dCaps, dwBehavior[f], formats[f] ) ) )
							bFormatConfirmed[f] = TRUE;
					}
					
					if ( FALSE == bFormatConfirmed[f] ) {
						dwBehavior[f] = D3DCREATE_MIXED_VERTEXPROCESSING;
						
						if( SUCCEEDED( hrConfirmDevice( &pDevice->d3dCaps, dwBehavior[f], formats[f] ) ) )
							bFormatConfirmed[f] = TRUE;
					}
				}
				
				// Confirm the device/format for SW vertex processing
				if( FALSE == bFormatConfirmed[f] ) {
					dwBehavior[f] = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
					
					if( SUCCEEDED( hrConfirmDevice( &pDevice->d3dCaps, dwBehavior[f], formats[f] ) ) )
						bFormatConfirmed[f] = TRUE;
				}
				
				// Find a suitable depth/stencil buffer format for this device/format
				if( bFormatConfirmed[f] && g_bUseDepthBuffer ) {
					if( !bFindDepthStencilFormat( 8, 0, iAdapter, pDevice->DeviceType,
						formats[f], &fmtDepthStencil[f] ) ) {
						bFormatConfirmed[f] = FALSE;
					}
				}
			}
			
			// Add modes that are confirmed to the list of available modes
			for( m = 0; m < dwNumModes; m++ ) {
				for( f = 0; f < dwNumFormats; f++ ) {
					if( modes[m].Format == formats[f] ) {
						if( bFormatConfirmed[f] == TRUE ) {
							// Add this mode to the device's list of valid modes
							pDevice->modes[pDevice->dwNumModes].Width      = modes[m].Width;
							pDevice->modes[pDevice->dwNumModes].Height     = modes[m].Height;
							pDevice->modes[pDevice->dwNumModes].Format     = modes[m].Format;
							pDevice->modes[pDevice->dwNumModes].dwBehavior = dwBehavior[f];
							pDevice->modes[pDevice->dwNumModes].DepthStencilFormat = fmtDepthStencil[f];
							pDevice->dwNumModes++;
							
							if( pDevice->DeviceType == D3DDEVTYPE_HAL )
								bHALIsSampleCompatible = TRUE;
						}
					}
				}
			}
			
			// Check if there was a device found that matched desired requirements
			for( m = 0; m < pDevice->dwNumModes; m++ ) {
				if( pDevice->modes[m].Width == SCREEN_WIDTH && pDevice->modes[m].Height == SCREEN_HEIGHT ) {
					pDevice->dwCurrentMode = m;
					if( g_bWindowed ) {
						if( pDevice->modes[m].Format == pAdapter->d3ddmDesktop.Format ) {
							bFoundVidMode = TRUE;
							break;
						}
					}
					else if( pDevice->modes[m].Format == D3DFMT_R5G6B5 ||
						pDevice->modes[m].Format == D3DFMT_X1R5G5B5 ||
						pDevice->modes[m].Format == D3DFMT_A1R5G5B5 ||
						pDevice->modes[m].Format == D3DFMT_X8R8G8B8 ||
						pDevice->modes[m].Format == D3DFMT_A8R8G8B8 ) {
						bFoundVidMode = TRUE;
						break;
					}
				}
			}
			
			// Check if device can work in a window
			if( bFormatConfirmed[0] && (pDevice->d3dCaps.Caps2 & D3DCAPS2_CANRENDERWINDOWED) ) {
				pDevice->bCanDoWindowed = TRUE;
				pDevice->bWindowed      = TRUE;
			}
			
			// If valid modes were found, keep this device
			if( pDevice->dwNumModes > 0 )
				pAdapter->dwNumDevices++;
		}
		// If valid devices were found, keep this adapter
		if( pAdapter->dwNumDevices > 0 )
			g_dwNumAdapters++;
	}
	
	// Return an error if no compatible devices were found
	if( !g_dwNumAdapters || !bFoundVidMode )
		return( VIDEODEVICEERROR_NOCOMPATIBLE );
	
	// Choose a default adapter
	for( a = 0; a < g_dwNumAdapters; a++ ) {
		for( d = 0; d < g_Adapters[a].dwNumDevices; d++ ) {
			if( (g_Adapters[a].devices[d].bWindowed && g_bWindowed) || (!g_bWindowed) ) {
				
				g_Adapters[a].dwCurrentDevice = d;
				g_dwAdapter = a;
				g_Adapters[a].devices[d].bWindowed = g_bWindowed;
				
				// Display a warning message
				if( g_Adapters[a].devices[d].DeviceType == D3DDEVTYPE_REF ) {
					if( !bHALExists )
						MessageBox( hWnd, "HAL Error", "Hardware Acceleration Not Found.", MB_ICONERROR );
					else if( !bHALIsSampleCompatible )
						MessageBox( hWnd, "HAL Error", "Your Hardware Acceleration Cannot Support This Application.", MB_ICONERROR );
					else if( !bHALIsWindowedCompatible && !g_bWindowed )
						MessageBox( hWnd, "HAL Error", "Your Hardware Acceleration Cannot Render To A Window.", MB_ICONERROR );
					else if( !bHALIsDesktopCompatible && !g_bWindowed )
						MessageBox( hWnd, "HAL Error", "Your Hardware Acceleration Cannot Render To A Window In The Current Desktop Setting.", MB_ICONERROR );
					else
						MessageBox( hWnd, "HAL Error", "Your Hardware Acceleration Cannot Support This Application In The Current Desktop Setting.", MB_ICONERROR );
				}
				
				return S_OK;
			}
		}
	}

    return( VIDEODEVICEERROR_NOWINDOWED );
}

//-----------------------------------------------------------------------------
// Name: hrConfirmDevice()
// Desc: Returns success if the device passed meets the apps requirements
//-----------------------------------------------------------------------------
HRESULT hrConfirmDevice( D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format )
{
	// Check for alpha support
	if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHAPALETTE )
        return S_OK;
    if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHA )
        return S_OK;

	return S_OK;

    return E_FAIL;
}

//-----------------------------------------------------------------------------
// Name: bFindDepthStencilFormat()
// Desc: Tries to find a valied stencil format for the passed requirements
//-----------------------------------------------------------------------------
BOOL bFindDepthStencilFormat( DWORD dwMinDepth, DWORD dwMinStencil, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat )
{
    D3DFORMAT	d3dfFormat = D3DFMT_UNKNOWN;
	
	if( dwMinDepth <= 16 && dwMinStencil == 0 ) {
		d3dfFormat = D3DFMT_D16;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}
	if( dwMinDepth <= 15 && dwMinStencil <= 1 ) {
		d3dfFormat = D3DFMT_D15S1;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}
	if( dwMinDepth <= 24 && dwMinStencil == 0 ) {
		d3dfFormat = D3DFMT_D24X8;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}
	if( dwMinDepth <= 24 && dwMinStencil <= 8 ) {
		d3dfFormat = D3DFMT_D24S8;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}
	if( dwMinDepth <= 24 && dwMinStencil <= 4 ) {
		d3dfFormat = D3DFMT_D24X4S4;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}
	if( dwMinDepth <= 32 && dwMinStencil == 0 ) {
		d3dfFormat = D3DFMT_D32;
		if( (bValidateFormat(d3dfFormat, iAdapter, DeviceType, TargetFormat)) == TRUE ) {
			*pDepthStencilFormat = d3dfFormat;
			return(TRUE);
		}
	}

    return FALSE;
}

//-----------------------------------------------------------------------------
// Name: bValidateFormat()
// Desc: Checks if the passed format is compatible
//-----------------------------------------------------------------------------
BOOL bValidateFormat(D3DFORMAT d3dfFormatToTest, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat)
{
	if( SUCCEEDED( pD3D->CheckDeviceFormat( iAdapter, DeviceType, TargetFormat, 
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, d3dfFormatToTest ) ) ) {
        if( SUCCEEDED( pD3D->CheckDepthStencilMatch( iAdapter, DeviceType, 
			TargetFormat, TargetFormat, d3dfFormatToTest ) ) ) {
            return TRUE;
        }
    }
	return(FALSE);
}

//-----------------------------------------------------------------------------
//
//
//
//							DIRECT PLAY FUNCTIONS
//
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: hrInitializeDirectPlay()
// Desc: Initializes all Direct Play interfaces and objects
//-----------------------------------------------------------------------------
HRESULT hrInitializeDirectPlay( HWND hWindow ) 
{
	HRESULT	hReturn;
	
	// Initialize COM
	hReturn = CoInitialize( NULL );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Error Initializing COM", "DirectPlay Error", MB_ICONERROR );
		return hReturn;
	}

	// Initialize critical sections for multi-threading
	InitializeCriticalSection( &g_csModifyPlayer );
	
	// Create IDirectPlay8Client Object
	if( FAILED( hReturn = CoCreateInstance( CLSID_DirectPlay8Client, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IDirectPlay8Client, 
		(LPVOID*) &g_pDP ) ) )
        MessageBox( hWindow, "Can't Create DPlayClient", "DirectPlay Error", MB_ICONERROR );
	
	// Init IDirectPlay8Client Message Handler
	if( FAILED( hReturn = g_pDP->Initialize( NULL, DirectPlayMessageHandler, 0 ) ) ) {
		MessageBox( hWindow, "Failed to Message Handler", "DirectPlay Error", MB_ICONERROR );
		return -1;
	}
	
	// Create a device address
	hReturn = CoCreateInstance( CLSID_DirectPlay8Address, NULL,CLSCTX_INPROC_SERVER, IID_IDirectPlay8Address, (LPVOID*) &g_pDeviceAddress );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Failed to Create Device", "CoCreateInstance()", MB_ICONERROR );
		return -1;
	}
	
	// Set our service provider to TCP/IP
	if( FAILED( hReturn = g_pDeviceAddress->SetSP( &CLSID_DP8SP_TCPIP ) ) ) {
		MessageBox( hWindow, "Failed to SetSP() for Device Address", "Invalid Param", MB_ICONERROR );
		return -1;
	}
	
	// Create a host address
	hReturn = CoCreateInstance( CLSID_DirectPlay8Address, NULL,CLSCTX_INPROC_SERVER, IID_IDirectPlay8Address, (LPVOID*) &g_pHostAddress );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Failed to Create Host Address()", "Invalid Param", MB_ICONERROR );
		return -1;
	}
	// Set the host address to TCP/IP
	if( FAILED( hReturn = g_pHostAddress->SetSP( &CLSID_DP8SP_TCPIP ) ) ) {
		MessageBox( hWindow, "Failed to SetSP() for Host Address", "Invalid Param", MB_ICONERROR );
		return -1;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler()
// Desc: Handles all Direct Play messages
//-----------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer )
{
	HRESULT					hReturn = S_OK;
	PacketAngle				*pacAngle;
	PacketVelocity			*pacVel;
	PacketPosition			*pacPos;
	PacketRequestPlayerInfo	pacRequest;
	PacketPlayerInfo		*pacPlayerInfo;
	PacketMessage			*pacMessage;
	PacketZoneChange		*pacZone;
	PacketTimeChange		*pacTime;
	PacketRemovePlayer		*pacRemove;
	PacketAttitude			*pacAttitude;
	void					*packet;
	int						iPlayerID;
	
	switch( dwMessageId ) 
	{
		case DPN_MSGID_TERMINATE_SESSION:
		{
			PDPNMSG_TERMINATE_SESSION pTerminateSessionMsg;
			pTerminateSessionMsg = (PDPNMSG_TERMINATE_SESSION)pMsgBuffer;
			break;
		}
		
		case DPN_MSGID_RECEIVE:
		{
			PDPNMSG_RECEIVE pReceiveMsg;
			PacketGeneric	*PGen;

			pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
			
			// Cast it to a generic packet so we can check the type
			PGen = (PacketGeneric*)pReceiveMsg->pReceiveData;

			// Check for server messages
			if( PGen->dwType == PACKET_TYPE_REQUESTPASSWORD ) {
				vSubmitPassword();
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_GAMEUPDATE ) {
				EnterCriticalSection( &g_csModifyPlayer );
				iUpdates++;
				LeaveCriticalSection( &g_csModifyPlayer );
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_MESSAGE ) {
				pacMessage = (PacketMessage*)pReceiveMsg->pReceiveData;
				vAddMessage(pacMessage->szMessage,pacMessage->color);
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_ZONECHANGE ) {
				pacZone = (PacketZoneChange*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				LocalPlayer.vecCurPos.x = pacZone->fXPos;
				LocalPlayer.vecCurPos.z = pacZone->fZPos;
				iZone = pacZone->iZone;
				iZoneMap = pacZone->iZoneMap;
				LocalPlayer.fRot = pacZone->fRot;
				LocalPlayer.fVelocity = 0.0f;
				vChangeZones(pacZone->iZone);
				LeaveCriticalSection( &g_csModifyPlayer );
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_CHANGEPOSITION ) {
				pacPos = (PacketPosition*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				LocalPlayer.vecCurPos.x = pacPos->fx;
				LocalPlayer.vecCurPos.z = pacPos->fz;
				LocalPlayer.fVelocity = 0.0f;
				LeaveCriticalSection( &g_csModifyPlayer );
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_TIMECHANGE ) {
				pacTime = (PacketTimeChange*)pReceiveMsg->pReceiveData;
				vUpdateTimeOfDay(pacTime->iTime);
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_ADDPLAYER ) {
				pacPlayerInfo = (PacketPlayerInfo*)pReceiveMsg->pReceiveData;
				iAddPlayer(pacPlayerInfo->iPlayerID,pacPlayerInfo->piInfo);
				break;
			}
			else if( PGen->dwType == PACKET_TYPE_REMOVEPLAYER ) {
				pacRemove = (PacketRemovePlayer*)pReceiveMsg->pReceiveData;
				vRemovePlayer(pacRemove->iPlayerID);
				break;
			}

			// If the packet id is not -1, then it is for another player					
			if( PGen->iPlayerID != -1 ) {
				// Figure out who is sending the message
				iPlayerID = iGetPlayerID(PGen->iPlayerID);
				
				// If the player does not exist in the game, request information about them
				if( iPlayerID == -1 ) {
					vAddMessage("Requesting Player Information",D3DCOLOR_RGBA(255, 255, 255, 255));
					pacRequest.dwSize = sizeof(PacketRequestPlayerInfo);
					pacRequest.dwType = PACKET_TYPE_REQUESTPLAYERINFO;
					pacRequest.iPlayerID = PGen->iPlayerID;
					packet = (VOID*)&pacRequest;
					hReturn = hrSendClientMessage(pacRequest.dwType,packet);
					break;
				}
			}
			else {
				// Set the target player to ourselves
				iPlayerID = -2;
			}

			if( PGen->dwType == PACKET_TYPE_ANGLE ) {
				pacAngle = (PacketAngle*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				if( iPlayerID != -2 ) 
					PlayerInfo[iPlayerID].fRot = pacAngle->fAngle;
				else
					LocalPlayer.fRot = pacAngle->fAngle;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_VELOCITY ) {
				pacVel = (PacketVelocity*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				if( iPlayerID != -2 ) 
					PlayerInfo[iPlayerID].fVelocity = pacVel->fVelocity;
				else
					LocalPlayer.fVelocity = pacVel->fVelocity;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_POSITION ) {
				pacPos = (PacketPosition*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				if( iPlayerID != -2 ) {
					PlayerInfo[iPlayerID].vecCurPos.x = pacPos->fx;
					PlayerInfo[iPlayerID].vecCurPos.z = pacPos->fz;
				}
				else {
					LocalPlayer.vecCurPos.x = pacPos->fx;
					LocalPlayer.vecCurPos.z = pacPos->fz;
				}
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_ATTITUDE ) {
				pacAttitude = (PacketAttitude*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				if( iPlayerID == -2 ) {
					LocalPlayer.vecCurPos.x = pacAttitude->fx;
					LocalPlayer.vecCurPos.z = pacAttitude->fz;
					LocalPlayer.fRot = pacAttitude->fRot;
					LocalPlayer.fVelocity = pacAttitude->fVelocity;
				}
				else {
					PlayerInfo[iPlayerID].vecCurPos.x = pacAttitude->fx;
					PlayerInfo[iPlayerID].vecCurPos.z = pacAttitude->fz;
					PlayerInfo[iPlayerID].fRot = pacAttitude->fRot;
					PlayerInfo[iPlayerID].fVelocity = pacAttitude->fVelocity;
				}
				LeaveCriticalSection( &g_csModifyPlayer );
			}
		}
	}
	
	return hReturn;
}

//-----------------------------------------------------------------------------
// Name: hrJoinGame()
// Desc: Function to join the game
//-----------------------------------------------------------------------------
HRESULT hrJoinGame( HWND hWnd )
{
	HRESULT					hReturn = S_OK;
	WCHAR					wszHostName[256];
	WCHAR					wszPeerName[256];
	char					szPeerName[256];
	char					szIP[256];
	DWORD					dwPort;
	DWORD					dwLength = 256;
	DPN_APPLICATION_DESC	dpnAppDesc;
	DPN_PLAYER_INFO			dpPlayerInfo;

	// Read some settings from the config file
	FILE *fp = fopen("config.txt","r");
	fgets(szIP,16,fp);
	szIP[strlen(szIP)-1] = '\0';
	fgets(szPeerName,32,fp);
	szPeerName[strlen(szPeerName)-1] = '\0';
	fclose(fp);

	// Set the peer info
	DXUtil_ConvertGenericStringToWide( wszPeerName, szPeerName );
	
	ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
	dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
	dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
	dpPlayerInfo.pwszName = wszPeerName;
	
	// Make this a synchronous call
	if( FAILED( hReturn = g_pDP->SetClientInfo( &dpPlayerInfo, NULL, NULL, DPNSETCLIENTINFO_SYNC ) ) ) {
		return -1;
	}
		
	// Prepare the application description
	ZeroMemory( &dpnAppDesc, sizeof( DPN_APPLICATION_DESC ) );
	dpnAppDesc.dwSize = sizeof( DPN_APPLICATION_DESC );
	dpnAppDesc.guidApplication = GUID_GAMESERVER;

	// Set the IP
	DXUtil_ConvertGenericStringToWide( wszHostName, szIP );
	// Set the port number
	dwPort = 6000;

	// Add host name to address
	hReturn = g_pHostAddress->AddComponent(DPNA_KEY_HOSTNAME,wszHostName,(wcslen(wszHostName)+1)*sizeof(WCHAR),DPNA_DATATYPE_STRING);
	if( hReturn != S_OK ) {
		MessageBox( hWnd, "Failed to AddComponent()", "hrJoinGame()", MB_ICONERROR );
		return -1;
	}
	// Add port number to address
	hReturn = g_pHostAddress->AddComponent(DPNA_KEY_PORT,&dwPort,sizeof(DWORD),DPNA_DATATYPE_DWORD);
	if( hReturn != S_OK ) {
		MessageBox( hWnd, "Failed to AddComponent()", "hrJoinGame()", MB_ICONERROR );
		return -1;
	}

	// Connect to the session
	hReturn = g_pDP->Connect(	&dpnAppDesc,
								g_pHostAddress,    
								g_pDeviceAddress,
								NULL,
								NULL,
								NULL,	
								NULL,
								NULL, 
								&g_hConnectAsyncOp,
								NULL); // flags
	
	if( hReturn != E_PENDING && FAILED(hReturn) ) {
		return -1;
	}
	SetTimer( hWnd, TIMERID_CONNECT_COMPLETE, 100, NULL );

	return(hReturn);
}

//-----------------------------------------------------------------------------
// Name: hrSendClientMessage()
// Desc: Used to send messages to the server
//-----------------------------------------------------------------------------
HRESULT	hrSendClientMessage( DWORD dwMessageType, PVOID pMsgBuffer, DWORD flags )
{
	DPNHANDLE		hAsync;
    DWORD			dwLength;
	DPN_BUFFER_DESC bufferDesc;
	PacketGeneric	*PGen;

	// Cast to a generic packet to get the size
	PGen = (PacketGeneric*)pMsgBuffer;
	dwLength = PGen->dwSize;

	if( dwLength == 0 ) 
		return(0);

	bufferDesc.dwBufferSize = dwLength;
	bufferDesc.pBufferData  = (BYTE*)pMsgBuffer;

	g_pDP->Send( &bufferDesc, 1, 0, NULL, &hAsync, flags );

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: iGetPlayerID()
// Desc: Returns the player slot that matches the passed ID
//-----------------------------------------------------------------------------
int iGetPlayerID(int id)
{
	int i;

	// Remove Player from list
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].iPlayerID == id ) {
				return(i);
			}
		}
	}
	return(-1);
}

//-----------------------------------------------------------------------------
//
//
//
//							DIRECT INPUT FUNCTIONS
//
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: hrInitDirectInput()
// Desc: Initializes Direct Input
//-----------------------------------------------------------------------------
HRESULT	hrInitDirectInput(void)
{
	HRESULT	hReturn = 0;
	
	// Do not try to create Direct Input if already created
	if( !pDI ) {
		// Create a DInput object
		if( FAILED( hReturn = DirectInput8Create( g_hInstance, DIRECTINPUT_VERSION, 
			IID_IDirectInput8, (VOID**)&pDI, NULL ) ) )
			return(INPUTERROR_NODI);
	}

	// Get the keyboard layout
	g_Layout = GetKeyboardLayout(0);
	
	return(hReturn);
}

//-----------------------------------------------------------------------------
// Name: hrInitKeyboard()
// Desc: Initializes Keyboard
//-----------------------------------------------------------------------------
HRESULT hrInitKeyboard(HWND hWnd)
{
	HRESULT			hReturn = 0;
	DIPROPDWORD		dipdw; 
	
	// Don't try to create the keyboard twice
	if( pKeyboard ) 
		return(INPUTERROR_KEYBOARDEXISTS);
	// Exit out if no Direct Input interface found
	else if ( !pDI ) 
		return(INPUTERROR_NODI);

	// Obtain an interface to the system keyboard device
	if( FAILED( hReturn = pDI->CreateDevice( GUID_SysKeyboard, &pKeyboard, NULL ) ) )
		return(INPUTERROR_NOKEYBOARD);
	
	// Create buffer to hold keyboard data
	ZeroMemory(&dipdw,sizeof(DIPROPDWORD));
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD); 
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	dipdw.diph.dwObj		= 0; 
	dipdw.diph.dwHow		= DIPH_DEVICE; 
	dipdw.dwData			= KEYBOARD_BUFFERSIZE;
	
	// Set the size of the buffer
	if( FAILED( hReturn = pKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) ) 
		return(INPUTERROR_NOKEYBOARD);
	
	// Set the format of the keyboard
	if( FAILED( hReturn = pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
		return(INPUTERROR_NOKEYBOARD);
	
	// Set the co-operative level to exclusive access
	if( FAILED( hReturn = pKeyboard->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) ) {
		return(INPUTERROR_NOKEYBOARD);
	}
	
	// Acquire the keyboard device
	pKeyboard->Acquire();
	
	return(0);
}

//-----------------------------------------------------------------------------
// Name: hrReadKeyboard()
// Desc: Reads buffered data from the Keyboard
//-----------------------------------------------------------------------------
HRESULT hrReadKeyboard( void )
{
	HRESULT				hr;
	DWORD				dwCurBuffer;
	DIDEVICEOBJECTDATA	didKeyboardBuffer[KEYBOARD_BUFFERSIZE];
	DWORD				dwItems = KEYBOARD_BUFFERSIZE;
	BYTE				byteASCII;

	// Dont try to read the keyboard if the interface or device is invalid
    if( !pKeyboard || !pDI ) 
        return(INPUTERROR_NOKEYBOARD);

	// Read the buffered data
	hr = pKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didKeyboardBuffer, &dwItems, 0); 
	// Reacquire the keyboard if focus is lost
	if( FAILED(hr) ) {
		// Acquire it
		hr = pKeyboard->Acquire();
		// If input has been lost then return ok
		if( hr == DIERR_INPUTLOST ) 
			return(S_OK);
		else
			return(INPUTERROR_NOKEYBOARD);
	}
	
	// Process data if there is data to read
	if ( dwItems ) {
		// Process the data
		for(dwCurBuffer = 0; dwCurBuffer < dwItems; dwCurBuffer++) {
			// Map scan-code to ascii code
			byteASCII = Scan2Ascii(didKeyboardBuffer[dwCurBuffer].dwOfs);
			// Set key to be down (depressed)
			if( didKeyboardBuffer[dwCurBuffer].dwData & 0x80 ) {
				ascKeys[byteASCII] = 1;
				diks[didKeyboardBuffer[dwCurBuffer].dwOfs] = 1;
			}
			// Set key to be up
			else {
				ascKeys[byteASCII] = 0;
				diks[didKeyboardBuffer[dwCurBuffer].dwOfs] = 0;
			}
		}
	} 

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Scan2Ascii()
// Desc: Converts a scan code to ASCII
//-----------------------------------------------------------------------------
BYTE Scan2Ascii(DWORD scancode)
{
	UINT vk;
	
	vk = MapVirtualKeyEx( scancode, 1, g_Layout);

	return(vk);
}

//-----------------------------------------------------------------------------
// Name: vChangeZones()
// Desc: Update camera to reflect zone change
//-----------------------------------------------------------------------------
void vChangeZones(int zone)
{
	vUpdateCamera();
}

//-----------------------------------------------------------------------------
// Name: vAddMessage()
// Desc: Add a message to the message output list
//-----------------------------------------------------------------------------
void vAddMessage(char *szmessage,D3DCOLOR color)
{
	// Add the message to the log
	strcpy(MessageLog[iLastMessage].szMessage,szmessage);
	MessageLog[iLastMessage].color = color;
	
	iLastMessage++;
	// Scroll message window if needed
	if( (iLastMessage - iMessageLogPos) > 10 ) 
		iMessageLogPos++;

	if( iLastMessage >= 64 ) {
		iMessageLogPos = 0;
		iLastMessage = 0;
		strcpy(MessageLog[0].szMessage,"");
		strcpy(MessageLog[1].szMessage,"");
		strcpy(MessageLog[2].szMessage,"");
		strcpy(MessageLog[3].szMessage,"");
		strcpy(MessageLog[4].szMessage,"");
	}
}

//-----------------------------------------------------------------------------
// Name: vUpdateTimeOfDay()
// Desc: Update the time of day based on the server's messagess
//-----------------------------------------------------------------------------
void vUpdateTimeOfDay(int newtime)
{
	if( newtime < 0 ) 
		newtime = 0;
	else if ( newtime > 255 ) 
		newtime = 255;

	bUpdateTime = 1;
	colorTimeColor = D3DCOLOR_XRGB(newtime,newtime,newtime);
}

//-----------------------------------------------------------------------------
// Name: vSubmitPassword()
// Desc: Submit authentication password to the server
//-----------------------------------------------------------------------------
void vSubmitPassword(void)
{
	PacketPasswordSubmit	pacSubmitPassword;
	void					*packet;
	FILE					*fp;
	char					szPlayerName[32];
	char					szPassword[32];

	fp = fopen("config.txt","r");
	if( fp == NULL ) 
		return;

	// First line is server IP, ignore it
	fgets(szPlayerName,32,fp);
	// Read the player name
	fgets(szPlayerName,32,fp);
	szPlayerName[strlen(szPlayerName)-1] = '\0';
	// Read the password
	fgets(szPassword,32,fp);
	szPassword[strlen(szPassword)-1] = '\0';
	fclose(fp);

	vAddMessage("Submitting Password...",D3DCOLOR_RGBA(255, 255, 255, 255));

	pacSubmitPassword.dwSize = sizeof(PacketPasswordSubmit);
	pacSubmitPassword.dwType = PACKET_TYPE_SUBMITPASSWORD;
	strcpy(pacSubmitPassword.szPassword,szPassword);
	packet = (VOID*)&pacSubmitPassword;
	hrSendClientMessage(PACKET_TYPE_SUBMITPASSWORD,packet,DPNSEND_GUARANTEED);
}

//-----------------------------------------------------------------------------
// Name: vRemovePlayer()
// Desc: Deactivate a player
//-----------------------------------------------------------------------------
void vRemovePlayer(int id)
{
	char	szMessage[256];
	int		iPlayer = 0;

	// Keep from corrupting memory
	if( id >= MAX_PLAYERS ) 
		return;

	iPlayer = iGetPlayerID(id);
	if( iPlayer >= 0 ) {
		// If it is active, deactivate it
		if( PlayerInfo[iPlayer].bActive ) {
			EnterCriticalSection( &g_csModifyPlayer );
			sprintf(szMessage,"%s Has Left The Game",PlayerInfo[iPlayer].szPlayerName);
			vAddMessage(szMessage,D3DCOLOR_RGBA(155, 155, 255, 255));
			// Clear all memory for the player
			memset(&PlayerInfo[iPlayer],0,sizeof(CLIENT_PLAYER_INFORMATION));
			LeaveCriticalSection( &g_csModifyPlayer );
		}
	}
}







