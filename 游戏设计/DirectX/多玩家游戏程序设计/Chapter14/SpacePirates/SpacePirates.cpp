//###################################################################################
//#																					#
//#			Chapter 14 - Space Pirates												#		
//#																					#
//#						Complete Peer-To-Peer Game									#
//#																					#
//#						Todd Barron, 03/12/2001										#
//#																					#
//###################################################################################
#include "SpacePirates.h"

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

	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message != WM_QUIT ) {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
			// Dont update game more than 30 FPS
			if( timeGetTime() > dwGovernor+33 ) {
				// Update players and execute pending actions
				vUpdateObjects();
				vUpdateNetwork();
				vRenderScene();
				dwGovernor = timeGetTime();
			}
			// Update keys
			hrReadKeyboard();
			// Spacebar = fire
			if( ascKeys[32] ) {
				bFireBullet = 1;
			}
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
	HRESULT			hReturn;
	PacketChat		pacChat;
	int				len;
	void			*packet;

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
				// Press ENTER
				case 13:
					// If not in command mode, go to command mode
					if( !g_iCommandMode ) {
						sprintf(szCommand,"Command:");
						sprintf(szSystemMessage,szCommand);
						g_iCommandMode = 1;
						
					}
					else {
						// Host the game
						if( !stricmp(&szCommand[8],"host") ) {
							hrHostGame(hWnd);
						}
						// Join the game
						else if( !stricmp(&szCommand[8],"join") ) {
							sprintf(szSystemMessage,"Joining");
							hrJoinGame(hWnd);
						}
						// Send a chat message
						else {
							sprintf(szSystemMessage,"%s:%s",PlayerInfo[g_iMyPlayerId].szPlayerName,(char*)&szCommand[8]);
							pacChat.dwSize = sizeof(PacketChat);
							pacChat.dwType = PACKET_TYPE_CHAT;
							strcpy(pacChat.szText,szSystemMessage);
							// Convert the packet to a void stream
							packet = (VOID*)&pacChat;
							// Send the velocity packet
							hReturn = hrSendPeerMessage(-1,PACKET_TYPE_CHAT,packet);
						}
						g_iCommandMode = 0;
					}
					break;

				default:
					// Add text to the command if in command mode
					if( g_iCommandMode ) {
						len = strlen(szCommand);
						szCommand[len] = wParam;
						szCommand[len+1] = '\0';
						sprintf(szSystemMessage,szCommand);
					}
					break;
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
	SAFE_DELETE( g_GameSounds.gsExplosion );
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
	CloseHandle( g_hConnectCompleteEvent );
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
		PlayerInfo[i].bActive = 0;
	}

	for( i = 0 ; i < MAX_BULLETS ; i++ ) {
		Bullet[i].bActive = 0;
	}

	for( i = 0 ; i < MAX_EXPLOSIONS ; i++ ) {
		Explosion[i].bActive = 0;
	}

	for( i = 0 ; i < MAX_TEXTURES ; i++ ) {
		g_pTexture[i] = NULL;
	}

	g_GameSounds.gsExplosion = NULL;
	g_GameSounds.gsFire = NULL;
}

//-----------------------------------------------------------------------------
// Name: iAddPlayer()
// Desc: Adds a player to the rendering system
//-----------------------------------------------------------------------------
int iAddPlayer(DPNID dpid, D3DXVECTOR3 pos, float fRot, char *szName)
{
	int i;

	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( !PlayerInfo[i].bActive ) {
			break;
		}
	}	
	// No free slots
	if( i == MAX_PLAYERS )
		return(-1);

	PlayerInfo[i].bActive = 1;
	PlayerInfo[i].dpnidPlayer = dpid;
	PlayerInfo[i].vecCurPos = pos;
	PlayerInfo[i].vecLastPos = pos;
	PlayerInfo[i].iFrame = 0;
	PlayerInfo[i].fRot = fRot;
	PlayerInfo[i].fVelocity = 0.0f;
	strcpy(PlayerInfo[i].szPlayerName,szName);
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
		g_GameSounds.gsExplosion = new GameSound;
		SoundEngine.hrLoadSound("data\\sfx\\hit.wav",g_GameSounds.gsExplosion);
		g_GameSounds.gsFire = new GameSound;
		SoundEngine.hrLoadSound("data\\sfx\\attack.wav",g_GameSounds.gsFire);
	}
}

//-----------------------------------------------------------------------------
// Name: vCreateBullet()
// Desc: Adds a bullet to the world
//-----------------------------------------------------------------------------
void vCreateBullet(DPNID dpowner, float fx, float fz, float fvel, float frot)
{
	int				i;
	PacketBullet	pacBul;
	void			*packet;
	HRESULT			hReturn;

	for( i = 0 ; i < MAX_BULLETS ; i++ ) {
		if( !Bullet[i].bActive ) {
			break;
		}
	}
	// Exit if no room for bullets
	if( i == MAX_BULLETS ) 
		return;
	Bullet[i].bActive = 1;
	Bullet[i].fx = fx;
	Bullet[i].fz = fz;
	Bullet[i].fVelocity = fvel+3.0f;
	Bullet[i].dpOwner = dpowner;
	Bullet[i].fRot = frot;

	SoundEngine.hrPlaySound(g_GameSounds.gsFire);

	// This is our bullet, send a bullet packet to everyone
	if( dpowner == g_dpnidLocalPlayer ) {
		pacBul.dwSize = sizeof(PacketBullet);
		pacBul.dwType = PACKET_TYPE_BULLET;
		pacBul.Bullet.bActive = 1;
		pacBul.Bullet.dpOwner = g_dpnidLocalPlayer;
		pacBul.Bullet.fRot = frot;
		pacBul.Bullet.fVelocity = fvel;
		pacBul.Bullet.fx = fx;
		pacBul.Bullet.fz = fz;
		// Convert the packet to a void stream
		packet = (VOID*)&pacBul;
		// Send the bullet packet
		hReturn = hrSendPeerMessage(-1,PACKET_TYPE_BULLET,packet);
	}
}

//-----------------------------------------------------------------------------
// Name: vUpdateObjects()
// Desc: Updates players position and settings, sends command packets
//-----------------------------------------------------------------------------
void vUpdateObjects(void)
{
	float			fx,fz;
	int				i,j,iHighestScoreHolder,lHighestScore;
	int				iKillBullet = 0;
	DWORD			dwCurrentTime = timeGetTime();
	DWORD			dwElapsed;
	float			fMultiplier;
	PacketAngle		pacAngle;
	PacketVelocity	pacVel;
	HRESULT			hReturn;
	void			*packet;

	// Figure elapsed time since last visit
	dwElapsed = (dwCurrentTime - dwFrameTimer);
	// Calculate frame adjustment
	fMultiplier = (float)((float)dwElapsed/33.0f);
	
	// Accelerate
	if( bAccelerate ) {
		bAccelerate = 0;
		if( PlayerInfo[g_iMyPlayerId].fVelocity < 2.0f )
			PlayerInfo[g_iMyPlayerId].fVelocity += 1.0f;
		pacVel.dwSize = sizeof(PacketVelocity);
		pacVel.dwType = PACKET_TYPE_VELOCITY;
		pacVel.fVelocity = (float)PlayerInfo[g_iMyPlayerId].fVelocity;
		// Convert the packet to a void stream
		packet = (VOID*)&pacVel;
		// Send the velocity packet
		hReturn = hrSendPeerMessage(-1,PACKET_TYPE_VELOCITY,packet);
	}
	// Deaccelerate
	if( bDeaccelerate ) {
		bDeaccelerate = 0;
		if( PlayerInfo[g_iMyPlayerId].fVelocity > -1.0f )
			PlayerInfo[g_iMyPlayerId].fVelocity -= 1.0f;
		pacVel.dwSize = sizeof(PacketVelocity);
		pacVel.dwType = PACKET_TYPE_VELOCITY;
		pacVel.fVelocity = (float)PlayerInfo[g_iMyPlayerId].fVelocity;
		// Convert the packet to a void stream
		packet = (VOID*)&pacVel;
		// Send the velocity packet
		hReturn = hrSendPeerMessage(-1,PACKET_TYPE_VELOCITY,packet);
	}
	// Rotate Left
	if( bTurnLeft ) {
		bTurnLeft = 0;
		PlayerInfo[g_iMyPlayerId].fRot -= 10.0f;
		if( PlayerInfo[g_iMyPlayerId].fRot < 0.0f ) 
			PlayerInfo[g_iMyPlayerId].fRot = 350.0f;

		pacAngle.dwSize = sizeof(PacketAngle);
		pacAngle.dwType = PACKET_TYPE_ANGLE;
		pacAngle.fAngle = PlayerInfo[g_iMyPlayerId].fRot;
		// Convert the packet to a void stream
		packet = (VOID*)&pacAngle;
		// Send the rotation packet
		hReturn = hrSendPeerMessage(-1,PACKET_TYPE_ANGLE,packet);
	}
	// Rotate Right
	if( bTurnRight ) {
		bTurnRight = 0;
		PlayerInfo[g_iMyPlayerId].fRot += 10.0f;
		if( PlayerInfo[g_iMyPlayerId].fRot >= 360.0f ) 
			PlayerInfo[g_iMyPlayerId].fRot = 0.0f;
		pacAngle.dwSize = sizeof(PacketAngle);
		pacAngle.dwType = PACKET_TYPE_ANGLE;
		pacAngle.fAngle = PlayerInfo[g_iMyPlayerId].fRot;
		// Convert the packet to a void stream
		packet = (VOID*)&pacAngle;
		// Send the angle packet
		hReturn = hrSendPeerMessage(-1,PACKET_TYPE_ANGLE,packet);
	}

	// Fire cannon if player hit fire button
	if( bFireBullet ) {
		vCreateBullet(PlayerInfo[g_iMyPlayerId].dpnidPlayer, PlayerInfo[g_iMyPlayerId].vecCurPos.x, PlayerInfo[g_iMyPlayerId].vecCurPos.z, (float)PlayerInfo[g_iMyPlayerId].fVelocity,PlayerInfo[g_iMyPlayerId].fRot);
		bFireBullet = 0;
	}
	EnterCriticalSection( &g_csModifyPlayer );
	// Update speed and position
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
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

			// Make sure mech doesnt leave the arena
			if( PlayerInfo[i].vecCurPos.x > ARENA_SIZE ) {
				PlayerInfo[i].vecCurPos.x = ARENA_SIZE;
				PlayerInfo[i].fVelocity = 0.0f;
			}
			else if( PlayerInfo[i].vecCurPos.x < -ARENA_SIZE ) {
				PlayerInfo[i].vecCurPos.x = -ARENA_SIZE;
				PlayerInfo[i].fVelocity = 0.0f;
			}
			if( PlayerInfo[i].vecCurPos.z > ARENA_SIZE ) {
				PlayerInfo[i].vecCurPos.z = ARENA_SIZE;
				PlayerInfo[i].fVelocity = 0.0f;
			}
			else if( PlayerInfo[i].vecCurPos.z < -ARENA_SIZE ) {
				PlayerInfo[i].vecCurPos.z = -ARENA_SIZE;
				PlayerInfo[i].fVelocity = 0.0f;
			}
		}
	}
	LeaveCriticalSection( &g_csModifyPlayer );
	// Update active bullets
	for( i = 0 ; i < MAX_BULLETS ; i++ ) {
		if( Bullet[i].bActive ) {
			iKillBullet = 0;
			vGetVelocity(Bullet[i].fRot,fx,fz);
			fx *= fMultiplier;
			fz *= fMultiplier;
			
			Bullet[i].fx += (float)(fx*Bullet[i].fVelocity)*-1;
			Bullet[i].fz += (float)(fz*Bullet[i].fVelocity)*-1;
			
			if( Bullet[i].fx > ARENA_SIZE ) {
				Bullet[i].fx = ARENA_SIZE;
				iKillBullet = 1;
			}
			else if( Bullet[i].fx < -ARENA_SIZE ) {
				Bullet[i].fx = -ARENA_SIZE;
				iKillBullet = 1;
			}
			if( Bullet[i].fz > ARENA_SIZE ) {
				Bullet[i].fz = ARENA_SIZE;
				iKillBullet = 1;
			}
			else if( Bullet[i].fz < -ARENA_SIZE ) {
				Bullet[i].fz = -ARENA_SIZE;
				iKillBullet = 1;
			}

			// Check if bullet hit a player
			for( j = 0 ; j < MAX_PLAYERS ; j++ ) {
				// Dont check bullet collision on its owner
				if( PlayerInfo[j].bActive ) {
					if( PlayerInfo[j].dpnidPlayer != Bullet[i].dpOwner ) {
						if( abs((int)Bullet[i].fz-(int)PlayerInfo[j].vecCurPos.z)<15 ) {
							if( abs((int)Bullet[i].fx-(int)PlayerInfo[j].vecCurPos.x)<15 ) {
								iKillBullet = 1;
								if( Bullet[i].dpOwner == g_dpnidLocalPlayer ) 
									PlayerInfo[g_iMyPlayerId].lScore += 100;
								break;
							}
						}
					}
				}
			}

			// Bullet hit something, create an explosion
			if( iKillBullet ) {
				Bullet[i].bActive = 0;
				iKillBullet = 0;
				// Find next explosion object
				for( j = 0 ; j < MAX_EXPLOSIONS ; j++ ) {
					if( !Explosion[j].bActive ) {
						Explosion[j].bActive = 1;
						Explosion[j].fx = Bullet[i].fx;
						Explosion[j].fz = Bullet[i].fz;
						Explosion[j].iFrame = 0;
						Explosion[j].dwFrameTime = timeGetTime()+100;
						SoundEngine.hrPlaySound(g_GameSounds.gsExplosion);
						break;
					}
				}
			}
		}
	}

	// Update explosion objects
	for( i = 0 ; i < MAX_EXPLOSIONS ; i++ ) {
		if( Explosion[i].bActive ) {
			// Update explosion frame
			if( timeGetTime() > Explosion[i].dwFrameTime ) {
				Explosion[i].iFrame ++;
				Explosion[i].dwFrameTime += 100;
			}
			if( Explosion[i].iFrame >= 8 ) {
				Explosion[i].bActive = 0;
			}
		}
	}

	lHighestScore = 0;
	iHighestScoreHolder = 0;
	// Check who has highest score
	for( j = 0 ; j < MAX_PLAYERS ; j++ ) {
		if( PlayerInfo[j].bActive ) {
			if( PlayerInfo[j].lScore > lHighestScore ) {
				iHighestScoreHolder = j;
				lHighestScore = PlayerInfo[j].lScore;
			}
		}
	}
	sprintf(szHighestScoreWinner,PlayerInfo[iHighestScoreHolder].szPlayerName);
	// Store highest score
	g_lHighestScore = PlayerInfo[iHighestScoreHolder].lScore;

	dwFrameTimer = timeGetTime();
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
	pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00606060 );
	
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: vUpdateCamera()
// Desc: Updates the camera position in the 3D scene
//-----------------------------------------------------------------------------
void vUpdateCamera(void)
{
	// Set where camera is viewing from
	vecCameraSource.x = PlayerInfo[g_iMyPlayerId].vecCurPos.x;
	vecCameraSource.y = 150.0f;
	vecCameraSource.z = PlayerInfo[g_iMyPlayerId].vecCurPos.z+150;
	// Set what camera is looking at
	vecCameraTarget.x = PlayerInfo[g_iMyPlayerId].vecCurPos.x;
	vecCameraTarget.y = 0.0f;
	vecCameraTarget.z = PlayerInfo[g_iMyPlayerId].vecCurPos.z;
	// Setup Camera View
	D3DXMatrixLookAtLH( &matCameraView, 
						&vecCameraSource, 
						&vecCameraTarget, 
						&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );

	// Tell the device to use the camera view for the viewport
	pd3dDevice->SetTransform( D3DTS_VIEW, &matCameraView );
}

//-----------------------------------------------------------------------------
// Name: vRenderScene()
// Desc: Displays the 3d scene
//-----------------------------------------------------------------------------
void vRenderScene(void)
{	
	D3DXMATRIX			matTranslation;
	D3DXMATRIX			matRotation;
	D3DXMATRIX			matRotation2;
	D3DXMATRIX			matScale;
	int					i,j;
	RECT				rTemp4 = { 5, 5, 600, 30 };
	RECT				rTemp1 = { 5, (SCREEN_HEIGHT-65), 400, (SCREEN_HEIGHT) };
	char				szScore[256];
		
	// Clear the backbuffer and the zbuffer
    pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	// Begin Rendering
	pd3dDevice->BeginScene();

	// Update the camera position
	vUpdateCamera();

	// Set the vertex buffer to render
	pd3dDevice->SetStreamSource( 0, lpVertexBuffer, sizeof(MYVERTEX) );
	// Set the vertex format
	pd3dDevice->SetVertexShader( D3DFVF_MYVERTEX );

	// Draw the Ground and walls
	for( i=-5;i<5;i++ ) {
		for( j=-5;j<5;j++ ) {
			
			// Draw back wall
			if( i == -5 ) {
				D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 1.0f );
				D3DXMatrixTranslation( &matTranslation, (j*50.0f)+25.0f, 25.0f, (i*50.0f)+0.0f );
				D3DXMatrixRotationX( &matRotation, 0.0f/RADIAN_TO_DEGREES );
				matScale *= matRotation;
				matScale *= matTranslation;
				pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
				if( j == 0 ) 
					pd3dDevice->SetTexture( 0, g_pTexture[12] );
				else
					pd3dDevice->SetTexture( 0, g_pTexture[11] );
				// Draw the primitive
				pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
			// Front Wall
			else if( i == 4 ) {
				if( PlayerInfo[g_iMyPlayerId].vecCurPos.z >= 200.0f ) 
					pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
				else
					pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
				
				D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 1.0f );
				D3DXMatrixTranslation( &matTranslation, (j*50.0f)+25.0f, 25.0f, (i*50.0f)+50.0f );
				D3DXMatrixRotationX( &matRotation, 0.0f/RADIAN_TO_DEGREES );
				matScale *= matRotation;
				matScale *= matTranslation;
				pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
				if( j == 0 ) 
					pd3dDevice->SetTexture( 0, g_pTexture[12] );
				else
					pd3dDevice->SetTexture( 0, g_pTexture[11] );
				// Draw the primitive
				pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
			}
			if( j == -5 ) {
				D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 1.0f );
				D3DXMatrixTranslation( &matTranslation, (j*50.0f), 25.0f, (i*50.0f)+25.0f );
				D3DXMatrixRotationY( &matRotation, 90.0f/RADIAN_TO_DEGREES );
				matScale *= matRotation;
				matScale *= matTranslation;
				pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
				if( i == 0 ) 
					pd3dDevice->SetTexture( 0, g_pTexture[12] );
				else
					pd3dDevice->SetTexture( 0, g_pTexture[11] );
				// Draw the primitive
				pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
			if( j == 4 ) {
				D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 1.0f );
				D3DXMatrixTranslation( &matTranslation, (j*50.0f)+50.0f, 25.0f, (i*50.0f)+25.0f );
				D3DXMatrixRotationY( &matRotation, -90.0f/RADIAN_TO_DEGREES );
				matScale *= matRotation;
				matScale *= matTranslation;
				pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
				if( i == 0 ) 
					pd3dDevice->SetTexture( 0, g_pTexture[12] );
				else
					pd3dDevice->SetTexture( 0, g_pTexture[11] );
				// Draw the primitive
				pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
			D3DXMatrixScaling( &matScale, 1.0f, 1.0f, 1.0f );
			D3DXMatrixTranslation( &matTranslation, (j*50.0f)+25.0f, 0.0f, (i*50.0f)+25.0f );
			D3DXMatrixRotationX( &matRotation, -90.0f/RADIAN_TO_DEGREES );
			matScale *= matRotation;
			matScale *= matTranslation;
			pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
			if( (i == -5 && j == -5) || (i == 4 && j == -5) || (i == -5 && j == 4) || (i == 4 && j == 4) ) 
				pd3dDevice->SetTexture( 0, g_pTexture[13] );
			else
				pd3dDevice->SetTexture( 0, g_pTexture[10] );
			// Draw the primitive
			pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	// Display Robots
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive )
			o3dShip[PlayerInfo[i].iFrame].vDisplayXYZ(PlayerInfo[i].vecCurPos.x,0.0f,PlayerInfo[i].vecCurPos.z,0.0f,PlayerInfo[i].fRot,0.0f);
	}
	
	// Restore scene material
	pd3dDevice->SetMaterial( &mtrlDefault );

	// Display Explosions, setup rendering for transparency
	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// Make ambient completely bright, this will make sure explosions are bright
	pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	// Set the vertex buffer to render
	pd3dDevice->SetStreamSource( 0, lpVertexBuffer, sizeof(MYVERTEX) );
	// Set the vertex format
	pd3dDevice->SetVertexShader( D3DFVF_MYVERTEX );
	// Disable lighting
	pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	// Render active Explosions
	for( i = 0 ; i < MAX_EXPLOSIONS ; i++ ) {
		if( Explosion[i].bActive ) {
			D3DXMatrixTranslation( &matTranslation, Explosion[i].fx, 0.0f+(0.25f*i), Explosion[i].fz );
			D3DXMatrixRotationX( &matRotation, -90.0f/RADIAN_TO_DEGREES );
			matRotation *= matTranslation;
			pd3dDevice->SetTransform(D3DTS_WORLD, &matRotation);
			// Set the explosion's texture frame
			pd3dDevice->SetTexture( 0, g_pTexture[Explosion[i].iFrame] );
			// Draw the primitive
			pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	// Turn Z-buffer back on
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	// Activate the bullet texture
	pd3dDevice->SetTexture( 0, g_pTexture[14] );
	// Render Bullets
	for( i = 0 ; i < MAX_BULLETS ; i++ ) {
		if( Bullet[i].bActive ) {
			D3DXMatrixScaling( &matScale, 0.5f, 0.5f, 0.5f );
			D3DXMatrixTranslation( &matTranslation, Bullet[i].fx, 15.0f, Bullet[i].fz );
			D3DXMatrixRotationX( &matRotation, -90.0f/RADIAN_TO_DEGREES );
			matScale *= matRotation;
			matScale *= matTranslation;
			pd3dDevice->SetTransform(D3DTS_WORLD, &matScale);
			// Draw the primitive
			pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	
	// Set state back to normal
	pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00808080 );
	pd3dDevice->SetTexture( 0, NULL );

	// Display the score
	sprintf(szScore,"SCORE %ld , HighScore: %s (%ld)", PlayerInfo[g_iMyPlayerId].lScore, szHighestScoreWinner, g_lHighestScore);
	pD3DXFont->DrawText(szScore, -1, &rTemp4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	if( strlen(szSystemMessage) ) {
		pD3DXFont->DrawText(szSystemMessage, -1, &rTemp1, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
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
	int		i;
	char	szFileName[256];
	void	*lpVertices;
	float	fSizeX = 50.0f;
	float	fSizeY = 50.0f;
	DWORD	dwColor = D3DCOLOR_XRGB(255,255,255);

	for( i = 0 ; i < 12 ; i++ ) {
		sprintf(szFileName,"Data\\3DObjects\\droid%d.x",i);
		o3dShip[i].hLoad(szFileName,pd3dDevice);
	}

	// Create the arena geometry
	g_Vertices[0].vecPos = D3DXVECTOR3(-fSizeX/2,fSizeY/2,0.0f);
	g_Vertices[0].u = 0.0f;
	g_Vertices[0].v = 0.0f;
	g_Vertices[0].dwDiffuse = dwColor;
	g_Vertices[0].vecNorm = D3DXVECTOR3(0.0f,0.0f,1.0f);
	
	g_Vertices[1].vecPos = D3DXVECTOR3(-fSizeX/2,-fSizeY/2,0.0f);
	g_Vertices[1].u = 0.0f;
	g_Vertices[1].v = 1.0f;		// Y
	g_Vertices[1].dwDiffuse = dwColor;
	g_Vertices[1].vecNorm = D3DXVECTOR3(0.0f,0.0f,1.0f);

	g_Vertices[2].vecPos = D3DXVECTOR3(fSizeX/2,fSizeY/2,0.0f);
	g_Vertices[2].u = -1.0f;	// X
	g_Vertices[2].v = 0.0f;
	g_Vertices[2].dwDiffuse = dwColor;
	g_Vertices[2].vecNorm = D3DXVECTOR3(0.0f,0.0f,1.0f);
	
	g_Vertices[3].vecPos = D3DXVECTOR3(fSizeX/2,-fSizeY/2,0.0f);
	g_Vertices[3].u = -1.0f;	// X
	g_Vertices[3].v = 1.0f;		// Y
	g_Vertices[3].dwDiffuse = dwColor;
	g_Vertices[3].vecNorm = D3DXVECTOR3(0.0f,0.0f,1.0f);
	
	// Create the vertex buffer
	if(FAILED(pd3dDevice->CreateVertexBuffer(4*sizeof(MYVERTEX), 0, D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &lpVertexBuffer))) {
		return;
	}
	
	// Lock the buffer
	if(FAILED(lpVertexBuffer->Lock(0, sizeof(g_Vertices), (BYTE**)&lpVertices, 0))) {
		return;
	}
	
	// Copy the g_Vertices information into the buffer
	memcpy(lpVertices, g_Vertices, sizeof(g_Vertices));
	// Unlock the buffer
	lpVertexBuffer->Unlock();
	
	//
	// Load Textures
	//
	for(i=0;i<8;i++) {
		sprintf(szFileName,"Data\\3DObjects\\exp%d.tga",i);
		if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[i] ) ) ) {
			return;
		}
	}
	// Load Ground Texture
	sprintf(szFileName,"Data\\3DObjects\\metal_plate.tga");
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[10] ) ) ) {
		return;
	}
	// Load Wall Texture
	sprintf(szFileName,"Data\\3DObjects\\stone02.bmp");
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[11] ) ) ) {
		return;
	}
	// Load Wall Texture
	sprintf(szFileName,"Data\\3DObjects\\stone03.bmp");
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[12] ) ) ) {
		return;
	}
	// Load Ground Texture
	sprintf(szFileName,"Data\\3DObjects\\metal_plate_start.tga");
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[13] ) ) ) {
		return;
	}
	// Load Ground Texture
	sprintf(szFileName,"Data\\3DObjects\\pulse.tga");
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, szFileName, &g_pTexture[14] ) ) ) {
		return;
	}
	
	// Create the common text font
	hFont = CreateFont(26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PROOF_QUALITY, 0, "georgia"); 
	D3DXCreateFont(pd3dDevice, hFont, &pD3DXFont); 
}

//-----------------------------------------------------------------------------
// Name: vCreateLights()
// Desc: Creates a point light and default material
//-----------------------------------------------------------------------------
void vCreateLights(void)
{
	D3DLIGHT8		d3dLight;

	// Initialize the default scene material
    ZeroMemory( &mtrlDefault, sizeof(D3DMATERIAL8) );
    mtrlDefault.Diffuse.r = 1.0f;
	mtrlDefault.Diffuse.g = 1.0f;
	mtrlDefault.Diffuse.b = 1.0f;
	pd3dDevice->SetMaterial( &mtrlDefault );
	
	// Clear out light structure
	ZeroMemory(&d3dLight, sizeof(D3DLIGHT8));
	d3dLight.Type = D3DLIGHT_POINT;
	d3dLight.Diffuse.r  = 1.0f;
	d3dLight.Diffuse.g  = 1.0f;
	d3dLight.Diffuse.b  = 1.0f;
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
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 800.0f );
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
	
	// Create IDirectPlay8Peer Object
	if( FAILED( hReturn = CoCreateInstance( CLSID_DirectPlay8Peer, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IDirectPlay8Peer, 
		(LPVOID*) &g_pDP ) ) )
        MessageBox( hWindow, "Can't Create DPlayPeer", "DirectPlay Error", MB_ICONERROR );

	// Init IDirectPlay8Peer Message Handler
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

	// Create connection complete event for later use
	g_hConnectCompleteEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler()
// Desc: Handles all Direct Play messages
//-----------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer )
{
	HRESULT				hReturn = S_OK;
	PacketChat			*ChatMsg;
	PacketAngle			*pacAngle;
	PacketVelocity		*pacVel;
	PacketPosition		*pacPos;
	PacketBullet		*pacBul;
	PacketScore			*pacScore;
	int					iPlayerID;
	
	switch( dwMessageId ) 
	{
		case DPN_MSGID_CREATE_PLAYER:
		{
			hrCreatePlayer(pvUserContext,pMsgBuffer);
			break;
		}
		
		case DPN_MSGID_DESTROY_PLAYER:
		{
			hrDestroyPlayer(pvUserContext,pMsgBuffer);
			break;
		}
		
		case DPN_MSGID_HOST_MIGRATE:
		{
			PDPNMSG_HOST_MIGRATE pHostMigrateMsg;
			pHostMigrateMsg = (PDPNMSG_HOST_MIGRATE)pMsgBuffer;
			
			// Check to see if we are the new host
			if( pHostMigrateMsg->dpnidNewHost == g_dpnidLocalPlayer ) {
			}
			break;
		}
		
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

			// If it is a chat packet, display its contents
			if( PGen->dwType == PACKET_TYPE_CHAT ) {
				// Convert the packet to a chat packet
				ChatMsg = (PacketChat*)pReceiveMsg->pReceiveData;
				// Output it on our screen
				sprintf(szSystemMessage,ChatMsg->szText);
			}
			else if( PGen->dwType == PACKET_TYPE_ANGLE ) {
				// Convert the packet to a chat packet
				iPlayerID = iGetPlayerID(pReceiveMsg->dpnidSender);
				pacAngle = (PacketAngle*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				PlayerInfo[iPlayerID].fRot = pacAngle->fAngle;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_VELOCITY ) {
				// Convert the packet to a chat packet
				iPlayerID = iGetPlayerID(pReceiveMsg->dpnidSender);
				pacVel = (PacketVelocity*)pReceiveMsg->pReceiveData;
				EnterCriticalSection( &g_csModifyPlayer );
				PlayerInfo[iPlayerID].fVelocity = pacVel->fVelocity;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_POSITION ) {
				// Convert the packet to a chat packet
				pacPos = (PacketPosition*)pReceiveMsg->pReceiveData;
				iPlayerID = iGetPlayerID(pReceiveMsg->dpnidSender);
				EnterCriticalSection( &g_csModifyPlayer );
				PlayerInfo[iPlayerID].vecCurPos.x = pacPos->fx;
				PlayerInfo[iPlayerID].vecCurPos.z = pacPos->fz;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
			else if( PGen->dwType == PACKET_TYPE_BULLET ) {
				// Convert the packet to a chat packet
				pacBul = (PacketBullet*)pReceiveMsg->pReceiveData;
				vCreateBullet(pacBul->Bullet.dpOwner,pacBul->Bullet.fx,pacBul->Bullet.fz,pacBul->Bullet.fVelocity,pacBul->Bullet.fRot);
			}
			else if( PGen->dwType == PACKET_TYPE_SCORE ) {
				// Convert the packet to a chat packet
				pacScore = (PacketScore*)pReceiveMsg->pReceiveData;
				iPlayerID = iGetPlayerID(pReceiveMsg->dpnidSender);
				EnterCriticalSection( &g_csModifyPlayer );
				PlayerInfo[iPlayerID].lScore = pacScore->lScore;
				LeaveCriticalSection( &g_csModifyPlayer );
			}
		}
		
		case DPN_MSGID_CONNECT_COMPLETE:
		{
			PDPNMSG_CONNECT_COMPLETE pConnectCompleteMsg;
			pConnectCompleteMsg = (PDPNMSG_CONNECT_COMPLETE)pMsgBuffer;
			
			g_hrConnectComplete = pConnectCompleteMsg->hResultCode;
			SetEvent( g_hConnectCompleteEvent );
			break;
		}
	}
	
	return hReturn;
}

//-----------------------------------------------------------------------------
// Name: hrCreatePlayer()
// Desc: Function to create a player who joins the session
//-----------------------------------------------------------------------------
HRESULT	hrCreatePlayer( PVOID pvUserContext, PVOID pMsgBuffer )
{
	HRESULT					hReturn = S_OK;
    PDPNMSG_CREATE_PLAYER	pCreatePlayerMsg;
	char					strName[256];
	char					szOutput[256];
	DWORD					dwSize = 0;
	DPN_PLAYER_INFO			*pdpPlayerInfo = NULL;
	int						i;
	void					*packet;
	PacketChat				ChatMsg;
		
	// Get a Create Message pointer to the buffer
	pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;
	
    // Get the peer info and extract its name
    hReturn = g_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );
    if( FAILED(hReturn) && hReturn != DPNERR_BUFFERTOOSMALL ) {
        hReturn = -1;
	}
	else {
		// Allocate memory for the player info
		pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[ dwSize ];
		
		ZeroMemory( pdpPlayerInfo, dwSize );
		pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);
		// Load the player info into the newly allocated data
		hReturn = g_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );
		if( FAILED(hReturn) ) {
			hReturn = -1;
		}
		else {
			EnterCriticalSection( &g_csModifyPlayer );
			
			// Convert player name to ANSI
			DXUtil_ConvertWideStringToGeneric( strName, pdpPlayerInfo->pwszName );
			// Check if we are adding ourselves
			if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_LOCAL ) {
				g_dpnidLocalPlayer = pCreatePlayerMsg->dpnidPlayer;
				g_iMyPlayerId = iAddPlayer(g_dpnidLocalPlayer,D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f,strName);
			}
			else {
				// Add the player to our game				
				i = iAddPlayer(pCreatePlayerMsg->dpnidPlayer,D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f,strName);
				// Send them a welcoming message if we are the host
				if( bHost ) {
					sprintf(szOutput,"Welcome to the game, %s!",strName);
					ChatMsg.dwSize = sizeof(PacketChat);
					ChatMsg.dwType = PACKET_TYPE_CHAT;
					strcpy(ChatMsg.szText,szOutput);
					// Convert the packet to a void stream
					packet = (VOID*)&ChatMsg;
					// Send the chat packet
					hReturn = hrSendPeerMessage(i,PACKET_TYPE_CHAT,packet);
				}
				sprintf(szSystemMessage,"%s Has Joined.", strName);
			}

			SAFE_DELETE_ARRAY( pdpPlayerInfo );
			
			// Update the number of active players in a thread safe way
			InterlockedIncrement( &g_lNumberOfActivePlayers );

			LeaveCriticalSection( &g_csModifyPlayer );
		}
	}
		
	return hReturn;
}

//-----------------------------------------------------------------------------
// Name: hrDestroyPlayer()
// Desc: Function to destroy a player who leaves the session
//-----------------------------------------------------------------------------
HRESULT	hrDestroyPlayer( PVOID pvUserContext, PVOID pMsgBuffer )
{
	PDPNMSG_DESTROY_PLAYER	pDestroyPlayerMsg;
	HRESULT					hReturn = S_OK;
	int						i;
	char					szOutput[256];
		
	// Get a Destroy Message pointer to the buffer
	pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
	
	// Update the number of active players in a thread safe way
	InterlockedDecrement( &g_lNumberOfActivePlayers );

	EnterCriticalSection( &g_csModifyPlayer );

	// Remove Player from list
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].dpnidPlayer == pDestroyPlayerMsg->dpnidPlayer ) {
				PlayerInfo[i].bActive = 0;
				sprintf(szOutput,"<%s> Left The Game",PlayerInfo[i].szPlayerName);
				sprintf(szSystemMessage,szOutput);
				break;
			}
		}
	}
	
	LeaveCriticalSection( &g_csModifyPlayer );
	
	return(hReturn);
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
	if( FAILED( hReturn = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNSETPEERINFO_SYNC ) ) ) {
		return -1;
	}
		
	// Prepare the application description
	ZeroMemory( &dpnAppDesc, sizeof( DPN_APPLICATION_DESC ) );
	dpnAppDesc.dwSize = sizeof( DPN_APPLICATION_DESC );
	dpnAppDesc.guidApplication = DP_SPACEPIRATES;

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
								0,
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
// Name: hrHostGame()
// Desc: Function to host the game
//-----------------------------------------------------------------------------
HRESULT	hrHostGame( HWND hWindow)
{
	HRESULT					hReturn;
	char					szPeerName[256];
	char					szSessionName[256];
	WCHAR					wszPeerName[256];
	WCHAR					wszSessionName[256];
	DPN_APPLICATION_DESC	dnAppDesc;
	char					szIP[6];
	DWORD					dwLength = 256;
	DPN_PLAYER_INFO			dpPlayerInfo;
	DWORD					dwPort = 9000;
	
	// Read some settings from the config file
	FILE *fp = fopen("config.txt","r");
	fgets(szIP,16,fp);
	szIP[strlen(szIP)-1] = '\0';
	fgets(szPeerName,32,fp);
	szPeerName[strlen(szPeerName)-1] = '\0';
	fclose(fp);

	//
	// Setup our player information
	//
	DXUtil_ConvertGenericStringToWide( wszPeerName, szPeerName );
	ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
	dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
	dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
	dpPlayerInfo.pwszName = wszPeerName;
	
	// Set us up to be non-asynchronous
	if( FAILED( hReturn = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNSETPEERINFO_SYNC ) ) ) {
		MessageBox( hWindow, "Failed to SetPeerInfo()", "DirectPlay Error", MB_ICONERROR );
		return -1;
	}
	
	// Setup the application description
	sprintf(szSessionName,"%s's Game",szPeerName);
	DXUtil_ConvertGenericStringToWide( wszSessionName, szSessionName );
	
	ZeroMemory( &dnAppDesc, sizeof(DPN_APPLICATION_DESC) );
	dnAppDesc.dwSize			= sizeof(DPN_APPLICATION_DESC);
	dnAppDesc.guidApplication	= DP_SPACEPIRATES;
	dnAppDesc.pwszSessionName	= wszSessionName;
	dnAppDesc.dwMaxPlayers		= MAX_PLAYERS;
	dnAppDesc.dwFlags			= DPNSESSION_MIGRATE_HOST;
	
	// Set the port number
	dwPort = 6000;
	
	// Add port number to address
	hReturn = g_pDeviceAddress->AddComponent(DPNA_KEY_PORT,&dwPort,sizeof(DWORD),DPNA_DATATYPE_DWORD);
	if( hReturn != S_OK ) {
		MessageBox( hWindow, "Failed to AddComponent()", "hrHostGame()", MB_ICONERROR );
		return -1;
	}
	
	// Host the game
	hReturn = g_pDP->Host(	&dnAppDesc,               
		&g_pDeviceAddress,        
		1,                        
		NULL, 
		NULL,               
		NULL,                     
		NULL );
	if( FAILED( hReturn ) ) {
		if( hReturn == DPNERR_INVALIDPARAM ) 
			MessageBox( hWindow, "Failed to Host()", "Invalid Param", MB_ICONERROR );
		else if( hReturn == DPNERR_INVALIDDEVICEADDRESS  ) 
			MessageBox( hWindow, "Failed to Host()", "Invalid Device Address", MB_ICONERROR );
		else
			MessageBox( hWindow, "Failed to Host()", "DirectPlay Error", MB_ICONERROR );
		return -1;
	}
	
	// Let us know we are the host
	bHost = 1;

	sprintf(szSystemMessage,"Hosting");

	return hReturn;
}

//-----------------------------------------------------------------------------
// Name: hrSendPeerMessage()
// Desc: Used to send messages to other players via Direct Play
//-----------------------------------------------------------------------------
HRESULT	hrSendPeerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer )
{
	DPNHANDLE		hAsync;
    DWORD			dwLength;
	DPN_BUFFER_DESC bufferDesc;
	PacketGeneric	*PGen;

	// Cast to a generic packet to get the size
	PGen = (PacketGeneric*)pMsgBuffer;
	dwLength = PGen->dwSize;

	// Return if an empty packet
	if( dwLength == 0 ) 
		return(0);

	bufferDesc.dwBufferSize = dwLength;
	bufferDesc.pBufferData  = (BYTE*)pMsgBuffer;

	// Broadcast message
	if( player == -1 )
		g_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1, 0, NULL, &hAsync, DPNSEND_NOLOOPBACK );
	// Send to a particular player
	else
		g_pDP->SendTo( PlayerInfo[player].dpnidPlayer, &bufferDesc, 1, 0, NULL, &hAsync, 0 );

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: iGetPlayerID()
// Desc: Returns the player slot that matches the passed ID
//-----------------------------------------------------------------------------
int iGetPlayerID(DPNID dpid)
{
	int i;

	// Remove Player from list
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].dpnidPlayer == dpid ) {
				return(i);
			}
		}
	}
	return(0);
}

//-----------------------------------------------------------------------------
// Name: vUpdateNetwork()
// Desc: Synchronizes Networked Players
//-----------------------------------------------------------------------------
void vUpdateNetwork(void)
{
	void			*packet;
	PacketAngle		pacAngle;
	PacketVelocity	pacVel;
	PacketPosition	pacPos;
	PacketScore		pacScore;
	HRESULT			hReturn;

	if( timeGetTime() > dwUpdateTime+100 ) {
		// Only send packets if other players are in the game
		if( g_lNumberOfActivePlayers > 1 ) {
			// Send our angle
			pacAngle.dwSize = sizeof(PacketAngle);
			pacAngle.dwType = PACKET_TYPE_ANGLE;
			pacAngle.fAngle = PlayerInfo[g_iMyPlayerId].fRot;
			packet = (VOID*)&pacAngle;
			hReturn = hrSendPeerMessage(-1,PACKET_TYPE_ANGLE,packet);		
			// Send our velocity
			pacVel.dwSize = sizeof(PacketVelocity);
			pacVel.dwType = PACKET_TYPE_VELOCITY;
			pacVel.fVelocity = (float)PlayerInfo[g_iMyPlayerId].fVelocity;
			packet = (VOID*)&pacVel;
			hReturn = hrSendPeerMessage(-1,PACKET_TYPE_VELOCITY,packet);
			// Send our position
			pacPos.dwSize = sizeof(PacketPosition);
			pacPos.dwType = PACKET_TYPE_POSITION;
			pacPos.fx = PlayerInfo[g_iMyPlayerId].vecCurPos.x;
			pacPos.fz = PlayerInfo[g_iMyPlayerId].vecCurPos.z;
			packet = (VOID*)&pacPos;
			hReturn = hrSendPeerMessage(-1,PACKET_TYPE_POSITION,packet);
			// Send our Score
			pacScore.dwSize = sizeof(PacketScore);
			pacScore.dwType = PACKET_TYPE_SCORE;
			pacScore.lScore = PlayerInfo[g_iMyPlayerId].lScore;
			packet = (VOID*)&pacScore;
			hReturn = hrSendPeerMessage(-1,PACKET_TYPE_SCORE,packet);
		}
		dwUpdateTime = timeGetTime();
	}
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
