//###################################################################################
//#																					#
//#			Chapter 16 - RPGQuest Game Server										#
//#																					#
//#						Demonstrates MMORPG Server (HEADER FILE)					#
//#																					#
//#						Todd Barron, 3/01/2001										#
//#																					#
//###################################################################################
#include "RPGQuestGameServer.h"
#include "..\\Common\\PacketInfo.h"

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;
	WNDCLASSEX	wndclass;
	HWND		hWnd;
	HRESULT		hReturn;
	DWORD		dwGovernor = timeGetTime();
	
	// Set up window attributes
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= fnMessageProcessor;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= lpszApplicationName;	// Registered Class Name
	wndclass.hIconSm		= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
		
	if( RegisterClassEx( &wndclass ) == 0 ) {
		// Do error logic here
		exit(1);
	}
	
	// Create the main window
	hWnd = CreateWindow(	lpszApplicationName,		// Application Name
		lpszTitle,					// Name Displayed on Title Bar
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL );
	//
	// Create Child Objects
	//
	vCreateInterface(hWnd,hInstance);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// Initialize Direct Play
	hReturn = hrInitializeDirectPlay( hWnd );
	if( FAILED(hReturn) ) {
		vCleanup();
		exit(1);
	}

	// Start Hosting
	hrHostGame( hWnd );

	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message != WM_QUIT ) {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
			// Read Player Messages
			vProcessMessages();
			if( timeGetTime() > dwGovernor+33 ) {
				// Update players and execute pending actions
				vUpdateTimeOfDay();
				vUpdatePlayers();
				dwGovernor = timeGetTime();
			}
			
		}
	}

	// Unregister the window class
	UnregisterClass( lpszApplicationName, hInstance );

	return(msg.wParam);
}

//
// Callback function to handle window messages
//
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	char		szMessage[256];
	char		szCompMessage[256];
	void		*packet;
	PacketChat	ChatMsg;
	
	switch (iMsg)
    {
		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case EN_UPDATE:
					// Get the text from the edit box
					GetWindowText(hEB_InputField,szMessage,256);
					// Check if they pressed enter
					if( szMessage[strlen(szMessage)-1] == 10 ) {
						// Get rid of trailing garbage
						szMessage[strlen(szMessage)-2] = '\0';
						sprintf(szCompMessage,"<Server(BROADCAST)> %s", szMessage);
						// clear input field
						SetWindowText(hEB_InputField,"");
						vShowText(hLB_Output,szCompMessage);
						//
						// Send a chat packet to all players
						//
						ChatMsg.dwSize = sizeof(PacketChat);
						ChatMsg.dwType = PACKET_TYPE_CHAT;
						strcpy(ChatMsg.szText,szCompMessage);
						// Convert the packet to a void stream
						packet = (VOID*)&ChatMsg;
						// Send the chat packet to all clients
						hrSendServerMessage(-1,PACKET_TYPE_CHAT,packet);
					}
					break;
			}
			break;
		}
		
		case WM_DESTROY:
			// Cleanup System
			vCleanup();
			// Exit out of Windows
			PostQuitMessage(0);
			break;
			
		default:
			return(DefWindowProc(hWnd, iMsg, wParam, lParam));
	}
	return(0L);
}

//-----------------------------------------------------------------------------------
// Functions to display text in our list box
//-----------------------------------------------------------------------------------
void vShowText(HWND	hChildHandle, char *szText)
{
	int Line;
	
	// add string to the listbox
	SendMessage(hChildHandle,LB_ADDSTRING,0,(LPARAM)szText);
	
	// determine number of items in listbox
	Line = SendMessage(hChildHandle,LB_GETCOUNT,0,0);
	
	// flag last item as the selected item, to scroll listbox down
	SendMessage(hChildHandle,LB_SETCURSEL,Line-1,0);
	
	// unflag all items to eliminate negative highlite
	SendMessage(hChildHandle,LB_SETCURSEL,-1,0);
}

//-----------------------------------------------------------------------------------
// Functions to create child objects in our Window
//-----------------------------------------------------------------------------------
void vCreateInterface(HWND hWnd,HINSTANCE hInstance)
{
	// Output Window
	hLB_Output = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"LISTBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER,
		5,
		5,
		580,
		340,
		hWnd,(HMENU)IDC_hLB_Output,hInstance,NULL);	
	
	// Edit field to enter chat messages into
	hEB_InputField = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		5,
		340,
		580,
		30,
		hWnd,(HMENU)IDC_hEB_InputField,hInstance,NULL);
}

//-----------------------------------------------------------------------------------
// Functions to initialize DirectPlay
//-----------------------------------------------------------------------------------
HRESULT hrInitializeDirectPlay( HWND hWindow ) 
{
	HRESULT	hReturn;
	int		i;
	
	// Initialize COM
	hReturn = CoInitialize( NULL );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Error Initializing COM", "DirectPlay Error", MB_ICONERROR );
		return hReturn;
	}
	
	// Initialize critical sections for multi-threading
	InitializeCriticalSection( &g_csModifyPlayer );
	InitializeCriticalSection( &g_csMessageSection );
	
	// Create IDirectPlay8Server Object
	if( FAILED( hReturn = CoCreateInstance( CLSID_DirectPlay8Server, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IDirectPlay8Server, 
		(LPVOID*) &g_pDPServer ) ) )
        MessageBox( hWindow, "Can't Create DPlayServer", "DirectPlay Error", MB_ICONERROR );
	
	// Init IDirectPlay8Server Message Handler
	if( FAILED( hReturn = g_pDPServer->Initialize( NULL, DirectPlayMessageHandler, 0 ) ) ) {
		MessageBox( hWindow, "Failed to Message Handler", "DirectPlay Error", MB_ICONERROR );
		return -1;
	}

	// Create a device address
	hReturn = CoCreateInstance( CLSID_DirectPlay8Address, NULL,CLSCTX_ALL, IID_IDirectPlay8Address, (LPVOID*) &g_pDeviceAddress );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Failed to Create Device", "CoCreateInstance()", MB_ICONERROR );
		return -1;
	}
	
	// Set our service provider to TCP/IP
	if( FAILED( hReturn = g_pDeviceAddress->SetSP( &CLSID_DP8SP_TCPIP ) ) ) {
		MessageBox( hWindow, "Failed to SetSP() for Device Address", "Invalid Param", MB_ICONERROR );
		return -1;
	}

	vShowText(hLB_Output,"<<--TCP INITED-->>");

	// Init miscellaneous variables
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		PlayerInfo[i].bActive = 0;
	}
	
	return S_OK;
}

//-----------------------------------------------------------------------------------
// Functions to cleanup program when exiting
//-----------------------------------------------------------------------------------
void vCleanup(void)
{
	if( g_pDPServer ) {
		// Close our connection
        g_pDPServer->Close(0);
		// Release the DirectPlay object
        SAFE_RELEASE( g_pDPServer );
    }
	
	DeleteCriticalSection( &g_csModifyPlayer );
	DeleteCriticalSection( &g_csMessageSection );
	SAFE_RELEASE( g_pDeviceAddress );
	
	// Uninitialize the COM library
	CoUninitialize();
}

//-----------------------------------------------------------------------------------
// Functions to handle and receive all Direct Play messages
//-----------------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer )
{
	HRESULT					hReturn = S_OK;
	int						iPlayer;
	PDPNMSG_RECEIVE			pReceiveMsg;
	PacketGeneric			*PGen;
	
	switch( dwMessageId ) 
	{
		case DPN_MSGID_CREATE_PLAYER:
		{
			vAddMessage(pMsgBuffer,PACKET_TYPE_CREATEPLAYER,0);
			break;
		}
		
		case DPN_MSGID_DESTROY_PLAYER:
		{
			vAddMessage(pMsgBuffer,PACKET_TYPE_DESTROYPLAYER,0);
			break;
		}
		
		case DPN_MSGID_RECEIVE:
		{
			pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
			// Convert to a generic packet so we can check the type
			PGen = (PacketGeneric*)pReceiveMsg->pReceiveData;

			// Ignore the packet if we sent it originally
			if( pReceiveMsg->dpnidSender == g_dpnidLocalPlayer ) 
				break;

			// Ignore if they are not an active player
			iPlayer = iGetPlayerID(pReceiveMsg->dpnidSender);
			if( iPlayer == -1 )
				break;
				
			// Add the message to the queue for later processing
			vAddMessage(pReceiveMsg->pReceiveData,PGen->dwType,iPlayer);
			break;
		}
	}
	
	return hReturn;
}

//-----------------------------------------------------------------------------------
// Function called when a player needs to be added to the game(including ourselves)
//-----------------------------------------------------------------------------------
HRESULT	hrCreatePlayer( PVOID pMsgBuffer )
{
	HRESULT					hReturn = S_OK;
    PDPNMSG_CREATE_PLAYER	pCreatePlayerMsg;
	char					strName[256];
	char					szOutput[256];
	DWORD					dwSize = 0;
	DPN_PLAYER_INFO			*pdpPlayerInfo = NULL;
	int						i;
		
	// Get a Create Message pointer to the buffer
	pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;
	
    // Get the peer info and extract its name
    hReturn = g_pDPServer->GetClientInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );
    if( FAILED(hReturn) && hReturn != DPNERR_BUFFERTOOSMALL ) {
        if( hReturn == DPNERR_INVALIDPLAYER ) {
			vShowText(hLB_Output,"Adding Ourselves");
		}
		hReturn = -1;
	}
	else {
		pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[ dwSize ];
		
		ZeroMemory( pdpPlayerInfo, dwSize );
		pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);
		
		hReturn = g_pDPServer->GetClientInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );
		if( FAILED(hReturn) ) {
			vShowText(hLB_Output,"Error Getting Client Info");
			hReturn = -1;
		}
		else {
			// Convert player name to ANSI
			DXUtil_ConvertWideStringToGeneric( strName, pdpPlayerInfo->pwszName );
			// Add player to list
			for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
				if( !PlayerInfo[i].bActive ) {
					PlayerInfo[i].bCredentialsAccepted = 0;
					PlayerInfo[i].bActive = 1;
					PlayerInfo[i].dpnidPlayer = pCreatePlayerMsg->dpnidPlayer;
					strcpy(PlayerInfo[i].szPlayerName,strName);
					vRequestPlayerPassword(i);
					break;
				}
			}
			// Check if no free slot found
			if( i == MAX_PLAYERS ) {
				vShowText(hLB_Output,"No free slots in game!");
			}
			// Check if we are adding ourselves
			else if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_LOCAL ) {
				g_dpnidLocalPlayer = pCreatePlayerMsg->dpnidPlayer;
				sprintf(szOutput,"<Slot%d> Added Ourselves",i);
				vShowText(hLB_Output,szOutput);
			}
			else {
				sprintf(szOutput,"<Slot%d><%s> Is In The Game",i,strName);
				vShowText(hLB_Output,szOutput);
			}

			SAFE_DELETE_ARRAY( pdpPlayerInfo );
			
			// Update the number of active players in a thread safe way
			if( i != MAX_PLAYERS )
				InterlockedIncrement( &g_lNumberOfActivePlayers );
		}
	}
		
	return hReturn;
}

//-----------------------------------------------------------------------------------
// Function called when a player needs to be removed from game
//-----------------------------------------------------------------------------------
HRESULT	hrDestroyPlayer( PVOID pMsgBuffer )
{
	PDPNMSG_DESTROY_PLAYER	pDestroyPlayerMsg;
	HRESULT					hReturn = S_OK;
	int						i;
	char					szOutput[256];
		
	// Get a Destroy Message pointer to the buffer
	pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
	
	// Update the number of active players in a thread safe way
	InterlockedDecrement( &g_lNumberOfActivePlayers );

	// Remove Player from list
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].dpnidPlayer == pDestroyPlayerMsg->dpnidPlayer ) {
				PlayerInfo[i].bActive = 0;
				sprintf(szOutput,"<Slot%d><%s> Left The Game",i,PlayerInfo[i].szPlayerName);
				vShowText(hLB_Output,szOutput);
				// Save the player information for next login
				bSavePlayerInfo(i);
				vInformOfRemoval(i);
				break;
			}
		}
	}

	return(hReturn);
}

//-----------------------------------------------------------------------------------
// Functions called when player wants to host a game
//-----------------------------------------------------------------------------------
HRESULT	hrHostGame( HWND hWindow)
{
	HRESULT					hReturn;
	WCHAR					wszServerName[256];
	WCHAR					wszSessionName[256];
	DPN_APPLICATION_DESC	dnAppDesc;
	DWORD					dwLength = 256;
	DPN_PLAYER_INFO			dpPlayerInfo;
	DWORD					dwPort = 6000;
	
	//
	// Setup the server information
	//
	DXUtil_ConvertGenericStringToWide( wszServerName, "RPGQuest Server" );
	ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
	dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
	dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
	dpPlayerInfo.pwszName = wszServerName;
	
	// Set us up to be non-asynchronous
	if( FAILED( hReturn = g_pDPServer->SetServerInfo( &dpPlayerInfo, NULL, NULL, DPNSETSERVERINFO_SYNC ) ) ) {
		MessageBox( hWindow, "Failed to SetServerInfo()", "Unknown Error", MB_ICONERROR );
		return -1;
	}
	
	// Setup the application description
	DXUtil_ConvertGenericStringToWide( wszSessionName, "RPGQuest Session" );
	
	ZeroMemory( &dnAppDesc, sizeof(DPN_APPLICATION_DESC) );
	dnAppDesc.dwSize			= sizeof(DPN_APPLICATION_DESC);
	dnAppDesc.guidApplication	= GUID_GAMESERVER;
	dnAppDesc.pwszSessionName	= wszSessionName;
	dnAppDesc.dwMaxPlayers		= MAX_PLAYERS;
	dnAppDesc.dwFlags			= DPNSESSION_CLIENT_SERVER;
	
	//
	// Add port number to host address
	//
	hReturn = g_pDeviceAddress->AddComponent(DPNA_KEY_PORT,&dwPort,sizeof(DWORD),DPNA_DATATYPE_DWORD);
	if( hReturn != S_OK ) {
		MessageBox( hWindow, "Failed to AddComponent()", "hrHostGame()", MB_ICONERROR );
		return -1;
	}
	
	//
	// Host the Server
	//
	hReturn = g_pDPServer->Host(	&dnAppDesc,               
									&g_pDeviceAddress,        
									1,                        
									NULL, 
									NULL,               
									NULL,                     
									NULL );
	if( FAILED( hReturn ) ) {
		MessageBox( hWindow, "Failed to Host()", "DirectPlay Error", MB_ICONERROR );
		return -1;
	}
	
	vShowText(hLB_Output,"<- Server Listening ->");
	
	return hReturn;
}

//-----------------------------------------------------------------------------------
// Functions to send a server message
//-----------------------------------------------------------------------------------
HRESULT	hrSendServerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer, DWORD flags )
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

	// Broadcast it if player set to -1
	if( player == -1 ) 
		g_pDPServer->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1, 0, NULL, &hAsync, flags | DPNSEND_NOLOOPBACK);
	else
		g_pDPServer->SendTo( PlayerInfo[player].dpnidPlayer, &bufferDesc, 1, 0, NULL, &hAsync, flags | DPNSEND_NOLOOPBACK);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: iGetPlayerID()
// Desc: Returns the player slot that matches the passed DPNID
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
	return(-1);
}

//-----------------------------------------------------------------------------
// Name: vSendUniqueMessage()
// Desc: Sends a message to a player
//-----------------------------------------------------------------------------
void vSendUniqueMessage(int iplayer, char *szmessage, D3DCOLOR color)
{
	void			*packet;
	PacketMessage	pacMes;
	char			szMessage[256];

	sprintf(szMessage,"[SERVER] %s",szmessage);
	
	pacMes.dwSize = sizeof(PacketMessage);
	pacMes.dwType = PACKET_TYPE_MESSAGE;
	strcpy(pacMes.szMessage,szMessage);
	pacMes.color = color;
	packet = (VOID*)&pacMes;
	hrSendServerMessage(iplayer,pacMes.dwType,packet);
}

//-----------------------------------------------------------------------------
// Name: vRequestPlayerPassword()
// Desc: Sends a password request to a player
//-----------------------------------------------------------------------------
void vRequestPlayerPassword(int iplayer)
{
	void			*packet;
	PacketGeneric	pacPass;
	
	vSendUniqueMessage(iplayer,"Server Requesting Credentials",D3DCOLOR_RGBA(255, 255, 255, 255));

	pacPass.dwSize = sizeof(PacketMessage);
	pacPass.dwType = PACKET_TYPE_REQUESTPASSWORD;
	packet = (VOID*)&pacPass;
	hrSendServerMessage(iplayer,pacPass.dwType,packet,DPNSEND_GUARANTEED);
}

//----------------------------------------------------------------------------
// Name: bValidatePlayer()
// Desc: Validates a players credentials or creates a new account
//-----------------------------------------------------------------------------
bool bValidatePlayer(int iplayer, char *szpassword)
{
	bool iRet = 0;

	vSendUniqueMessage(iplayer,"Validating Credentials",D3DCOLOR_RGBA(255, 255, 255, 255));
		
	// Check if new player or not
	if( !bReadPlayerInfo(iplayer)) {
		vCreatePlayerAccount(iplayer,szpassword);
		return( 0 );
	}

	// Check if password matches
	if( stricmp(PlayerInfo[iplayer].szPassword,szpassword) ) {
		vSendUniqueMessage(iplayer,"Credentials Rejected, Try Another Password or UserName",D3DCOLOR_RGBA(255, 55, 55, 255));
		return( 0 );
	}

	PlayerInfo[iplayer].bCredentialsAccepted = 1;
	
	return( 1 );
}

//-----------------------------------------------------------------------------
// Name: vCreatePlayerAccount()
// Desc: Creates a new player account
//-----------------------------------------------------------------------------
void vCreatePlayerAccount(int iplayer, char *szpassword)
{
	PlayerInfo[iplayer].bCredentialsAccepted = 1;
	strcpy(PlayerInfo[iplayer].szPassword,szpassword);
	PlayerInfo[iplayer].iZone = 0;
	bSavePlayerInfo(iplayer);
	vSendUniqueMessage(iplayer,"New Player Account Created!",D3DCOLOR_RGBA(255, 55, 255, 255));
}	

//-----------------------------------------------------------------------------
// Name: bReadPlayerInfo()
// Desc: Reads information from a player file
//-----------------------------------------------------------------------------
bool bReadPlayerInfo(int iplayer)
{
	FILE *fp;
	char szFileName[256];
	char szBuffer[512];

	sprintf(szFileName,"Data\\PlayerData\\%s.txt",PlayerInfo[iplayer].szPlayerName);

	fp = fopen(szFileName,"r");
	if( !fp ) 
		return(0);

	// Read in the data
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	PlayerInfo[iplayer].fRot = (float)atof(szBuffer);
	// X
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	PlayerInfo[iplayer].vecCurPos.x = (float)atof(szBuffer);
	// Y
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	PlayerInfo[iplayer].vecCurPos.y = (float)atof(szBuffer);
	// Z
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	PlayerInfo[iplayer].vecCurPos.z = (float)atof(szBuffer);
	// Zone
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	PlayerInfo[iplayer].iZone = atoi(szBuffer);
	PlayerInfo[iplayer].iZoneMap = atoi(szBuffer);
	// Passwrd
	fgets(szBuffer,512,fp);
	szBuffer[strlen(szBuffer)-1] = '\0';
	strcpy(PlayerInfo[iplayer].szPassword,szBuffer);
	//
	fclose(fp);
	return(1);
}

//-----------------------------------------------------------------------------
// Name: bSavePlayerInfo()
// Desc: Saves information about a player
//-----------------------------------------------------------------------------
bool bSavePlayerInfo(int iplayer)
{
	FILE *fp;
	char szFileName[256];

	sprintf(szFileName,"Data\\PlayerData\\%s.txt",PlayerInfo[iplayer].szPlayerName);

	fp = fopen(szFileName,"w");
	if( !fp ) 
		return(0);

	// Read in the data
	fprintf(fp,"%f\n",PlayerInfo[iplayer].fRot);
	fprintf(fp,"%f\n",PlayerInfo[iplayer].vecCurPos.x);
	fprintf(fp,"%f\n",PlayerInfo[iplayer].vecCurPos.y);
	fprintf(fp,"%f\n",PlayerInfo[iplayer].vecCurPos.z);
	fprintf(fp,"%d\n",PlayerInfo[iplayer].iZone);
	fprintf(fp,"%s\n",PlayerInfo[iplayer].szPassword);
	//
	fclose(fp);
	return(1);
}

//-----------------------------------------------------------------------------
// Name: iValidatePlayerPosition()
// Desc: Validates player position
//-----------------------------------------------------------------------------
int iValidatePlayerPosition(int i, int iZone, float x, float y, float z)
{
	int bRet = 1;

	if( iZone == 0 ) {
		// Check Stinkys
		if( x > -200.0f && x < -29.0f ) {
			if( z > 57.0f && z < 206.0f ) {
				bRet = 0;
			}
		}
		// Check Senor Tacos
		if( x > 30.0f && x < 201.0f ) {
			if( z > 57.0f && z < 206.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > -270.0f && x < -200.0f ) {
			if( z > 200.0f && z < 270.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > 200.0f && x < 270.0f ) {
			if( z > 200.0f && z < 270.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > -270.0f && x < -200.0f ) {
			if( z > -270.0f && z < -200.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > 200.0f && x < 270.0f ) {
			if( z > -270.0f && z < -200.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > -98.0f && x < -28.0f ) {
			if( z > -270.0f && z < -200.0f ) {
				bRet = 0;
			}
		}
		// Check Pillar
		if( x > 30.0f && x < 100.0f ) {
			if( z > -270.0f && z < -200.0f ) {
				bRet = 0;
			}
		}
		// Check Boxes
		if( x > 25.0f && x < 97.0f ) {
			if( z > -91.0f && z < -24.0f ) {
				bRet = 0;
			}
		}
		// Check Senor Left Door
		if( x > 98.0f && x < 103.0f ) {
			if( z > 17.0f && z < 70.0f ) {
				bRet = 0;
			}
		}
		// Check Senor Right Door
		if( x > 140.0f && x < 147.0f ) {
			if( z > 17.0f && z < 70.0f ) {
				bRet = 0;
			}
		}
		// Check Stinkys Left Door
		if( x > -134.0f && x < -127.0f ) {
			if( z > 17.0f && z < 70.0f ) {
				bRet = 0;
			}
		}
		// Check Stinkys Right Door
		if( x > -91.0f && x < -85.0f ) {
			if( z > 17.0f && z < 70.0f ) {
				bRet = 0;
			}
		}
		
		// Check Exit Right Wall
		if( x > -300.0f && x < -258.0f ) {
			if( z > 17.0f && z < 40.0f ) {
				bRet = 0;
			}
		}
		// Check Exit Left Wall
		if( x > -300.0f && x < -258.0f ) {
			if( z > -40.0f && z < -18.0f ) {
				bRet = 0;
			}
		}
		// Check Zoning
		if( x > -300.0f && x < -258.0f ) {
			if( z > -18.0f && z < 17.0f ) {
				return( 3 );
			}
		}
		// Check Zoning
		if( x > 258.0f && x < 300.0f ) {
			if( z > -18.0f && z < 17.0f ) {
				return( 4 );
			}
		}

		// Check Exit Right Wall
		if( x > 258.0f && x < 300.0f ) {
			if( z > 17.0f && z < 40.0f ) {
				bRet = 0;
			}
		}
		// Check Exit Left Wall
		if( x > 258.0f && x < 300.0f ) {
			if( z > -40.0f && z < -18.0f ) {
				bRet = 0;
			}
		}
	}
	else if ( iZone == 1 ) {
		// Check Exit Right Wall
		if( x > 258.0f && x < 300.0f ) {
			if( z > 17.0f && z < 40.0f ) {
				bRet = 0;
			}
		}
		// Check Exit Left Wall
		if( x > 258.0f && x < 300.0f ) {
			if( z > -40.0f && z < -18.0f ) {
				bRet = 0;
			}
		}
		// Check Zoning
		if( x > 258.0f && x < 300.0f ) {
			if( z > -18.0f && z < 17.0f ) {
				return( 2 );
			}
		}
		// Check Railing
		if( x > 56.0f && x < 300.0f ) {
			if( z > 14.0f && z < 22.0f ) {
				bRet = 0;
			}
		}
		if( x > 56.0f && x < 300.0f ) {
			if( z > -20.0f && z < -13.0f ) {
				bRet = 0;
			}
		}
		if( x > -19.0f && x < 62.0f ) {
			if( z > 74.0f && z < 82.0f ) {
				bRet = 0;
			}
		}
		if( x > -19.0f && x < 62.0f ) {
			if( z > -83.0f && z < -72.0f ) {
				bRet = 0;
			}
		}
		if( x > -22.0f && x < -11.0f ) {
			if( z > -83.0f && z < 83.0f ) {
				bRet = 0;
			}
		}
		if( x > 54.0f && x < 62.0f ) {
			if( z > 14.0f && z < 83.0f ) {
				bRet = 0;
			}
		}
		if( x > 54.0f && x < 62.0f ) {
			if( z > -82.0f && z < -12.0f ) {
				bRet = 0;
			}
		}
	}
	else if ( iZone == 2 ) {
		// Check Zoning
		if( x > 258.0f && x < 300.0f ) {
			if( z > -18.0f && z < 17.0f ) {
				return( 2 );
			}
		}
		// Check Exit Right Wall
		if( x > -300.0f && x < -258.0f ) {
			if( z > 17.0f && z < 40.0f ) {
				bRet = 0;
			}
		}
		// Check Exit Left Wall
		if( x > -300.0f && x < -258.0f ) {
			if( z > -40.0f && z < -18.0f ) {
				bRet = 0;
			}
		}
	}
	return( bRet );
}

//-----------------------------------------------------------------------------
// Name: vZonePlayer()
// Desc: Send a player to another zone
//---------------------------------------------------------------------------
void vZonePlayer(int iplayer, int inewzone)
{
	void				*packet;
	PacketZoneChange	pacZone;
	char				szMessage[256];
	int					i;

	memset(&pacZone,0,sizeof(pacZone));
	
	vSendUniqueMessage(iplayer,"Zoning...",D3DCOLOR_RGBA(155, 255, 155, 255));

	if( inewzone == 0 ) {
		// Coming from the waste area
		if( PlayerInfo[iplayer].iZone == 1 ) {
			pacZone.fRot = 270.0f;
			pacZone.fXPos = -250.0f;
		}
		// Coming from the sactuary
		else if( PlayerInfo[iplayer].iZone == 2 ) {
			pacZone.fRot = 90.0f;
			pacZone.fXPos = 250.0f;
		} 
		pacZone.fZPos = 0.0f;
		pacZone.iZone = 0;
		pacZone.iZoneMap = 0;
		vSendUniqueMessage(iplayer,"Entering The Merchant Zone",D3DCOLOR_RGBA(55, 255, 55, 255));
	}
	else if( inewzone == 1 ) {
		pacZone.fRot = 90.0f;
		pacZone.fXPos = 250.0f;
		pacZone.fZPos = 0.0f;
		pacZone.iZone = 1;
		pacZone.iZoneMap = 1;
		vSendUniqueMessage(iplayer,"Entering The Waste Facility",D3DCOLOR_RGBA(55, 255, 55, 255));
	}
	else if( inewzone == 2 ) {
		pacZone.fRot = 90.0f;
		pacZone.fXPos = 250.0f;
		pacZone.fZPos = 0.0f;
		pacZone.iZone = 2;
		pacZone.iZoneMap = 2;
		vSendUniqueMessage(iplayer,"Entering The Arena",D3DCOLOR_RGBA(55, 255, 55, 255));
		
	}
	pacZone.dwSize = sizeof(PacketZoneChange);
	pacZone.dwType = PACKET_TYPE_ZONECHANGE;
	pacZone.lNumbPlayers = (iGetNumberOfPlayers(pacZone.iZone)+1);
	packet = (VOID*)&pacZone;
	hrSendServerMessage(iplayer,pacZone.dwType,packet,DPNSEND_GUARANTEED);

	// Update player information

	PlayerInfo[iplayer].iZone = inewzone;
	PlayerInfo[iplayer].iZoneMap = inewzone;
	PlayerInfo[iplayer].vecCurPos.x = pacZone.fXPos;
	PlayerInfo[iplayer].vecCurPos.y = 0.0;
	PlayerInfo[iplayer].vecCurPos.z = pacZone.fZPos;
	PlayerInfo[iplayer].fRot = pacZone.fRot;
	
	vUpdatePlayerPosition(iplayer);
	// Save the player information
	bSavePlayerInfo(iplayer);

	sprintf(szMessage,"%d Players Are In The Zone",pacZone.lNumbPlayers);
	vSendUniqueMessage(iplayer,szMessage,D3DCOLOR_RGBA(155, 255, 155, 255));

	// Send information about all of the players in the zone
	for(i=0;i<MAX_PLAYERS;i++) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].iZone == PlayerInfo[iplayer].iZone ) {
				if( i != iplayer ) {
					// Send the new player information about all others
					vSendPlayerInformation(i, iplayer);
					// Send all others information about the new player
					vSendPlayerInformation(iplayer, i);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Name: vZonePlayer()
// Desc: Send a player to another zone ( Method2 )
//---------------------------------------------------------------------------
void vZonePlayer(int iplayer)
{
	void				*packet;
	PacketZoneChange	pacZone;
	char				szMessage[256];
	int					i;

	memset(&pacZone,0,sizeof(pacZone));
	
	pacZone.fXPos = PlayerInfo[iplayer].vecCurPos.x;
	pacZone.fZPos = PlayerInfo[iplayer].vecCurPos.z;
	pacZone.fRot = PlayerInfo[iplayer].fRot;
	pacZone.iZone = PlayerInfo[iplayer].iZone;
	pacZone.iZoneMap = PlayerInfo[iplayer].iZone;
	
	pacZone.dwSize = sizeof(PacketZoneChange);
	pacZone.dwType = PACKET_TYPE_ZONECHANGE;
	pacZone.lNumbPlayers = iGetNumberOfPlayers(PlayerInfo[iplayer].iZone);
	packet = (VOID*)&pacZone;
	hrSendServerMessage(iplayer,pacZone.dwType,packet,DPNSEND_GUARANTEED);

	if( PlayerInfo[iplayer].iZoneMap == 0 )
		vSendUniqueMessage(iplayer,"Entering The Merchant Zone",D3DCOLOR_RGBA(55, 255, 55, 255));
	else if( PlayerInfo[iplayer].iZoneMap == 1 )
		vSendUniqueMessage(iplayer,"Entering The Waste Facility",D3DCOLOR_RGBA(55, 255, 55, 255));
	else if( PlayerInfo[iplayer].iZoneMap == 2 )
		vSendUniqueMessage(iplayer,"Entering The Arena",D3DCOLOR_RGBA(55, 255, 55, 255));

	sprintf(szMessage,"%d Players Are In The Zone",pacZone.lNumbPlayers);
	vSendUniqueMessage(iplayer,szMessage,D3DCOLOR_RGBA(155, 255, 155, 255));

	// Update player position
	vUpdatePlayerPosition(iplayer);

	// Send information about all of the players in the zone
	for(i=0;i<MAX_PLAYERS;i++) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].iZone == PlayerInfo[iplayer].iZone ) {
				if( i != iplayer ) {
					// Send the new player information about all others
					vSendPlayerInformation(i, iplayer);
					// Send all others information about the new player
					vSendPlayerInformation(iplayer, i);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Name: vUpdatePlayerPosition()
// Desc: Tell a player what their position is
//---------------------------------------------------------------------------
void vUpdatePlayerPosition(int iplayer)
{
	void				*packet;
	PacketPosition		pacPos;

	pacPos.dwSize = sizeof(PacketPosition);
	pacPos.dwType = PACKET_TYPE_CHANGEPOSITION;
	pacPos.fx = PlayerInfo[iplayer].vecCurPos.x;
	pacPos.fz = PlayerInfo[iplayer].vecCurPos.z;
	packet = (VOID*)&pacPos;
	hrSendServerMessage(iplayer,pacPos.dwType,packet);
}

//-----------------------------------------------------------------------------
// Name: iGetNumberOfPlayers()
// Desc: Count how many players are in a zone
//---------------------------------------------------------------------------
int iGetNumberOfPlayers(int izone)
{
	int i;
	int iCount = 0;

	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].iZone == izone ) {
				iCount++;
			}
		}
	}
	return( iCount);
}

//-----------------------------------------------------------------------------
// Name: vSendPlayerInformation()
// Desc: Send all pertitent information about a player
//---------------------------------------------------------------------------
void vSendPlayerInformation(int iplayer, int ireceive)
{
	PacketPlayerInfo	pacPInfo;
	void				*packet;

	pacPInfo.dwSize = sizeof(pacPInfo);
	pacPInfo.dwType = PACKET_TYPE_ADDPLAYER;
	pacPInfo.iPlayerID = iplayer;
	pacPInfo.piInfo.fRot = PlayerInfo[iplayer].fRot;
	pacPInfo.piInfo.vecCurPos.x = PlayerInfo[iplayer].vecCurPos.x;
	pacPInfo.piInfo.vecCurPos.y = PlayerInfo[iplayer].vecCurPos.y;
	pacPInfo.piInfo.vecCurPos.z = PlayerInfo[iplayer].vecCurPos.z;
	pacPInfo.piInfo.fVelocity = PlayerInfo[iplayer].fVelocity;
	pacPInfo.piInfo.iFrame = PlayerInfo[iplayer].iFrame;
	pacPInfo.piInfo.iZone = PlayerInfo[iplayer].iZone;
	pacPInfo.piInfo.iZoneMap = PlayerInfo[iplayer].iZoneMap;
	strcpy(pacPInfo.piInfo.szPlayerName,PlayerInfo[iplayer].szPlayerName);
	packet = (VOID*)&pacPInfo;
	hrSendServerMessage(ireceive,pacPInfo.dwType,packet,DPNSEND_GUARANTEED);
}

//-----------------------------------------------------------------------------
// Name: vUpdateTimeOfDay()
// Desc: Update the game time and brightness value
//---------------------------------------------------------------------------
void vUpdateTimeOfDay(void)
{
	void				*packet;
	PacketTimeChange	pacTime;

	if( timeGetTime() > dwDayTimer ) {
		dwDayTimer = (timeGetTime()+500);
		if( !iTimeDirection ) 
			iTimeValue--;
		else 
			iTimeValue++;
		// Check for sunrise
		if( iTimeValue < 0 ) {
			iTimeValue = 1;
			iTimeDirection = 1;
			// Make midnight last a while
			dwDayTimer = (timeGetTime()+10000);
		}
		// Check for sunset
		else if( iTimeValue > 255 ) {
			iTimeValue = 254;
			iTimeDirection = 0;
			// Make high-noon last a while
			dwDayTimer = (timeGetTime()+10000);
		}
		pacTime.dwSize = sizeof(PacketTimeChange);
		pacTime.dwType = PACKET_TYPE_TIMECHANGE;
		pacTime.iTime = iTimeValue;
		packet = (VOID*)&pacTime;
		hrSendServerMessage(-1,pacTime.dwType,packet);
	}
}

//-----------------------------------------------------------------------------
// Name: vInformOfRemoval()
// Desc: Let a player know that someone has left the zone
//---------------------------------------------------------------------------
void vInformOfRemoval(int iplayer)
{
	PacketRemovePlayer	pacRemove;
	void				*packet;
	int					i;

	pacRemove.dwSize = sizeof(PacketRemovePlayer);
	pacRemove.dwType = PACKET_TYPE_REMOVEPLAYER;
	pacRemove.iPlayerID = iplayer;
	packet = (VOID*)&pacRemove;
	for(i=0;i<MAX_PLAYERS;i++) {
		if( PlayerInfo[i].bActive ) {
			if( i != iplayer ) {
				hrSendServerMessage(i,pacRemove.dwType,packet);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Name: vSendPlayerAttitude()
// Desc: Send player information to all involved
//---------------------------------------------------------------------------
void vSendPlayerAttitude(int iplayer, bool bEcho )
{
	PacketAttitude		pacAttitude;
	void				*packet;
	int					i;

	pacAttitude.dwSize = sizeof(PacketAttitude);
	pacAttitude.dwType = PACKET_TYPE_ATTITUDE;
	pacAttitude.iPlayerID = iplayer;
	pacAttitude.fx = PlayerInfo[iplayer].vecCurPos.x;
	pacAttitude.fz = PlayerInfo[iplayer].vecCurPos.z;
	pacAttitude.fRot = PlayerInfo[iplayer].fRot;
	pacAttitude.fVelocity = (float)PlayerInfo[iplayer].fVelocity;
	packet = (VOID*)&pacAttitude;

	// Send to everyone in the same zone
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( (PlayerInfo[i].bActive && PlayerInfo[i].iZone == PlayerInfo[iplayer].iZone) && i != iplayer ) {
			hrSendServerMessage(i,pacAttitude.dwType,packet);
		}
	}
	if( bEcho ) {
		// Send the message to the player
		pacAttitude.iPlayerID = -1;
		hrSendServerMessage(iplayer,pacAttitude.dwType,packet,DPNSEND_GUARANTEED);
	}
}

//-----------------------------------------------------------------------------
// Name: vUpdatePlayers()
// Desc: Update player positions and check for collisions
//-----------------------------------------------------------------------------
void vUpdatePlayers(void)
{
	int		iZone, i;
	float	fx,fz;
	int		iRet = 0;

	for( iZone = 0 ; iZone < 3 ; iZone++ ) {
		for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
			// Update the player if active
			if( PlayerInfo[i].bActive ) {
				// Update the player if in the zone
				if( PlayerInfo[i].iZone == iZone ) {
					vGetVelocity(PlayerInfo[i].fRot,fx,fz);

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
						PlayerInfo[i].vecCurPos.x -= (float)(fx*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].vecCurPos.z -= (float)(fz*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].fVelocity = 0.0f;
						vSendPlayerAttitude(i,1);
					}
					else if( PlayerInfo[i].vecCurPos.x < -ARENA_SIZE ) {
						PlayerInfo[i].vecCurPos.x -= (float)(fx*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].vecCurPos.z -= (float)(fz*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].fVelocity = 0.0f;
						vSendPlayerAttitude(i,1);
					}
					if( PlayerInfo[i].vecCurPos.z > ARENA_SIZE ) {
						PlayerInfo[i].vecCurPos.x -= (float)(fx*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].vecCurPos.z -= (float)(fz*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].fVelocity = 0.0f;
						vSendPlayerAttitude(i,1);
					}
					else if( PlayerInfo[i].vecCurPos.z < -ARENA_SIZE ) {
						PlayerInfo[i].vecCurPos.x -= (float)(fx*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].vecCurPos.z -= (float)(fz*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].fVelocity = 0.0f;
						vSendPlayerAttitude(i,1);
					}
					iRet = iValidatePlayerPosition(i,PlayerInfo[i].iZone,PlayerInfo[i].vecCurPos.x,0.0f,PlayerInfo[i].vecCurPos.z);
					if( !iRet ) {
						PlayerInfo[i].vecCurPos.x -= (float)(fx*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].vecCurPos.z -= (float)(fz*PlayerInfo[i].fVelocity)*-1;
						PlayerInfo[i].fVelocity = 0.0f;
						vSendPlayerAttitude(i,1);
					}
					else if ( iRet > 1 ) {
						vZonePlayer(i,(iRet-2));
						
					}
					PlayerInfo[i].fVelocity *= 0.5f;
				}
			}
		}
	}

	// Send Game Update Packet
	PacketGeneric		pacGeneric;
	void				*packet;

	pacGeneric.dwSize = sizeof(PacketGeneric);
	pacGeneric.dwType = PACKET_TYPE_GAMEUPDATE;
	packet = (VOID*)&pacGeneric;

	// Send to everyone in the game
	hrSendServerMessage(-1,pacGeneric.dwType,packet);
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
// Name: vAddMessage()
// Desc: Adds a message to the network queue
//-----------------------------------------------------------------------------
void vAddMessage( void *data, int itype, int iplayer )
{
	int isize = 0;

	if( itype == PACKET_TYPE_SUBMITPASSWORD ) 
		isize = sizeof(PacketPasswordSubmit);
	else if( itype == PACKET_TYPE_ANGLE ) 
		isize = sizeof(PacketAngle);
	else if( itype == PACKET_TYPE_VELOCITY ) 
		isize = sizeof(PacketVelocity);
	else if( itype == PACKET_TYPE_CREATEPLAYER ) 
		isize = sizeof(DPNMSG_CREATE_PLAYER);
	else if( itype == PACKET_TYPE_DESTROYPLAYER ) 
		isize = sizeof(DPNMSG_DESTROY_PLAYER);
	else if( itype == PACKET_TYPE_REQUESTPLAYERINFO ) 
		isize = sizeof(PacketPlayerInfo);
	else
		return;

	EnterCriticalSection( &g_csMessageSection );
	memcpy(gameMessage[iLastMessage].byteMessageBuffer,data,isize);
	gameMessage[iLastMessage].iType = itype;
	gameMessage[iLastMessage].iPlayerID = iplayer;
	iLastMessage++;

	// Circulate the message buffer
	if( iLastMessage == 999 ) {
		iLastMessage = 0;
	}
	LeaveCriticalSection( &g_csMessageSection );
}

//-----------------------------------------------------------------------------
// Name: iGetMessage()
// Desc: Retrieve the next message in the network queue
//-----------------------------------------------------------------------------
int iGetMessage( void )
{
	int	iRet = 0;

	// Return out if there are no messages to process
	if( iCurMessage == iLastMessage ) 
		return( -1 );

	EnterCriticalSection( &g_csMessageSection );
	if( iCurMessage < 999 ) {
		iRet = iCurMessage;
		iCurMessage++;
	}
	else if( iCurMessage == 999 ) {
		iRet = iCurMessage;
		iCurMessage = 0;
	}
	LeaveCriticalSection( &g_csMessageSection );

	return( iRet );
}

//-----------------------------------------------------------------------------
// Name: vProcessMessages()
// Desc: Process messages in the network queue
//-----------------------------------------------------------------------------
void vProcessMessages(void)
{
	int						iCount = 0;
	int						iPlayerID;
	int						iMessage = 0;
	HRESULT					hReturn = S_OK;
	PacketPasswordSubmit	*pacPass;
	PacketAngle				*pacRot;
	PacketGeneric			*PGen;
	PacketVelocity			*pacVel;
	PacketRequestPlayerInfo	*pacRequestPlayerInfo;
	
	// Read in the next 50 messages
	while( (iMessage = iGetMessage()) != -1 && iCount < 250 ) {
		iCount++;
		// Handle new players
		if( gameMessage[iMessage].iType == PACKET_TYPE_CREATEPLAYER ) {
			vShowText(hLB_Output,"Creating Player");
			hrCreatePlayer(gameMessage[iMessage].byteMessageBuffer);	
			continue;
		}
		// Handle players leaving
		else if( gameMessage[iMessage].iType == PACKET_TYPE_DESTROYPLAYER ) {
			vShowText(hLB_Output,"Destroying Player");
			hrDestroyPlayer(gameMessage[iMessage].byteMessageBuffer);	
			continue;
		}
		
		PGen = (PacketGeneric*)gameMessage[iMessage].byteMessageBuffer;
		iPlayerID = gameMessage[iMessage].iPlayerID;

		if( PGen->dwType == PACKET_TYPE_SUBMITPASSWORD ) {
			pacPass = (PacketPasswordSubmit*)gameMessage[iMessage].byteMessageBuffer;
			// Validate the password
			vShowText(hLB_Output,"Validating Credentials");
			if( (bValidatePlayer(iPlayerID,pacPass->szPassword)) == 1 ) {
				vSendUniqueMessage(iPlayerID,"Credentials Accepted",D3DCOLOR_RGBA(255, 255, 55, 255));
				vZonePlayer(iPlayerID);
				vShowText(hLB_Output,"Credentials Accepted");
			}
		}
		else if( PGen->dwType == PACKET_TYPE_ANGLE ) {
			pacRot = (PacketAngle*)gameMessage[iMessage].byteMessageBuffer;
			// Update The Players Orientation
			PlayerInfo[iPlayerID].fRot = pacRot->fAngle;
			// Send the attitude to all its friends
			vSendPlayerAttitude(iPlayerID);
		}
		else if( PGen->dwType == PACKET_TYPE_VELOCITY ) {
			pacVel = (PacketVelocity*)gameMessage[iMessage].byteMessageBuffer;
			// Update The Players Orientation
			PlayerInfo[iPlayerID].fVelocity = pacVel->fVelocity;
			// Send the attitude to all its friends
			vSendPlayerAttitude(iPlayerID);
		}
		else if( PGen->dwType == PACKET_TYPE_REQUESTPLAYERINFO ) {
			pacRequestPlayerInfo = (PacketRequestPlayerInfo*)gameMessage[iMessage].byteMessageBuffer;
			vSendPlayerInformation(iPlayerID,pacRequestPlayerInfo->iPlayerID);
			vShowText(hLB_Output,"Sending Player Information");
			vSendUniqueMessage(iPlayerID,"Sending Player Information",D3DCOLOR_RGBA(255, 255, 55, 255));
		}
	}
}
