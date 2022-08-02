//###################################################################################
//#																					#
//#			Chapter 9 - Direct Play Program											#
//#																					#
//#						Demonstrates Game Hosting and Joining						#
//#																					#
//#						Todd Barron, 12/03/2000										#
//#																					#
//###################################################################################

#include "dpchat.h"

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;
	WNDCLASSEX	wndclass;
	HWND		hWnd;
	HRESULT		hReturn;
	
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
		400,
		340,
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
	
	// Process messages until the program is terminated
	while( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
	return(msg.wParam);
}

//
// Callback function to handle window messages
//
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	char	szMessage[256];
	char	szCompMessage[256];
	HRESULT	hReturn;
	
	switch (iMsg)
    {
		case WM_COMMAND:
		{
			// Check for child window messages
			switch(LOWORD(wParam))
			{
				// Check if the user clicked the button
				case IDC_hBU_Join:
					hrJoinGame( hWnd );
					break;
				case IDC_hBU_Host:
					hrHostGame( hWnd );
					break;
			}
			switch(HIWORD(wParam))
			{
				case EN_UPDATE:
					// Get the text from the edit box
					GetWindowText(hEB_InputField,szMessage,256);
					// Check if they pressed enter
					if( szMessage[strlen(szMessage)-1] == 10 ) {
						// Get rid of trailing garbage
						szMessage[strlen(szMessage)-2] = '\0';
						sprintf(szCompMessage,"<%s> %s", PlayerInfo[0].szPlayerName, szMessage);
						hReturn = hrSendChatMessage(-1,szCompMessage);
						// clear input field
						SetWindowText(hEB_InputField,"");
					}
			}
			break;
		}
		
		case WM_DESTROY:
			// Cleanup System
			vCleanup();
			// Exit out of Windows
			PostQuitMessage(0);
			break;
			
		case WM_TIMER:
			if( wParam == TIMERID_CONNECT_COMPLETE ) {
				// Check if the message is telling us our connection is complete
				if( WAIT_OBJECT_0 == WaitForSingleObject( g_hConnectCompleteEvent, 0 ) ) {
					if( FAILED( g_hrConnectComplete ) ) {
						vShowText(hLB_Output,"<<----CONNECTION IN-COMPLETE---->>");
					}
					else {
						vShowText(hLB_Output,"<<----CONNECTION COMPLETE---->>");
					}
					KillTimer( hWnd, TIMERID_CONNECT_COMPLETE );
				}
			}
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
	// Server IP Text
	hST_TextServerIP = CreateWindow(
		"static","Server IP",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		5,
		5,
		120,
		28,
		hWnd,(HMENU)IDC_hST_TextServerIP,hInstance,NULL);
	
	// Port Text
	hST_TextServerPort = CreateWindow(
		"static","Port",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		125,
		5,
		50,
		28,
		hWnd,(HMENU)IDC_hST_TextServerPort,hInstance,NULL);
	
	// Name Text
	hST_TextName = CreateWindow(
		"static","Player Name",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		250,
		5,
		135,
		28,
		hWnd,(HMENU)IDC_hST_TextName,hInstance,NULL);
	
	// Join Button
	hBU_Join = CreateWindow(
		"BUTTON",
		"Join",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		325,
		280,
		60,
		28,
		hWnd,(HMENU)IDC_hBU_Join,hInstance,NULL);
	
	// Host Button
	hBU_Host = CreateWindow(
		"BUTTON",
		"Host",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		325,
		240,
		60,
		28,
		hWnd,(HMENU)IDC_hBU_Host,hInstance,NULL);
	
	// Output Window
	hLB_Output = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"LISTBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER,
		5,
		50,
		315,
		230,
		hWnd,(HMENU)IDC_hLB_Output,hInstance,NULL);	
	
	// Name
	hEB_InputName = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","Unnamed",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		250,
		20,
		135,
		28,
		hWnd,(HMENU)IDC_hEB_InputName,hInstance,NULL);
	
	// Server IP
	hEB_InputServerIP = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","192.168.0.2",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		5,
		20,
		120,
		28,
		hWnd,(HMENU)IDC_hEB_InputServerIP,hInstance,NULL);
	
	// Server Port
	hEB_InputServerPort = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","6000",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		125,
		20,
		50,
		28,
		hWnd,(HMENU)IDC_hEB_InputServerPort,hInstance,NULL);
	
	// Edit field to enter chat messages into
	hEB_InputField = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		5,
		280,
		315,
		28,
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
	if( g_pDP ) {
		// Close our connection
        g_pDP->Close(0);
		// Release the DirectPlay object
        SAFE_RELEASE( g_pDP );
    }
	
	DeleteCriticalSection( &g_csModifyPlayer );
	CloseHandle( g_hConnectCompleteEvent );
	SAFE_RELEASE( g_pDeviceAddress );
    SAFE_RELEASE( g_pHostAddress );
	
	// Uninitialize the COM library
	CoUninitialize();
}

//-----------------------------------------------------------------------------------
// Functions to handle and receive all Direct Play messages
//-----------------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer )
{
	HRESULT	hReturn = S_OK;
	
	switch( dwMessageId ) 
	{
		case DPN_MSGID_CREATE_PLAYER:
		{
			vShowText(hLB_Output,"Creating Player");
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
			vShowText(hLB_Output,"Migrate Host");
			PDPNMSG_HOST_MIGRATE pHostMigrateMsg;
			pHostMigrateMsg = (PDPNMSG_HOST_MIGRATE)pMsgBuffer;
			
			// Check to see if we are the new host
			if( pHostMigrateMsg->dpnidNewHost == g_dpnidLocalPlayer ) {
				vShowText(hLB_Output,"(HOSTING)");
			}
			break;
		}
		
		case DPN_MSGID_TERMINATE_SESSION:
		{
			vShowText(hLB_Output,"<-Terminating Session->");
			PDPNMSG_TERMINATE_SESSION pTerminateSessionMsg;
			pTerminateSessionMsg = (PDPNMSG_TERMINATE_SESSION)pMsgBuffer;
			break;
		}
		
		case DPN_MSGID_RECEIVE:
		{
			PDPNMSG_RECEIVE pReceiveMsg;
			pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
			
			vShowText(hLB_Output,(char*)pReceiveMsg->pReceiveData);
			
			break;
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

//-----------------------------------------------------------------------------------
// Functions to send chat message to everyone
//-----------------------------------------------------------------------------------
HRESULT	hrSendChatMessage(int player, char	*szmessage)
{
	PACKET_CHAT		msgChat;
	DPNHANDLE		hAsync;
    DWORD			dwLength = strlen(szmessage);
	DPN_BUFFER_DESC bufferDesc;
	
	// If no message to send, then just return
    if( dwLength == 0 )
		return S_OK;
	
	// Copy the message to send into our packet
	strcpy(msgChat.szText,szmessage);
	// Set the size of the packet to send
    bufferDesc.dwBufferSize = sizeof(PACKET_CHAT) + dwLength;
	// Copy our packet into the send buffer
    bufferDesc.pBufferData  = (BYTE*) &msgChat;
	// Send message to everyone including ourselves if -1 passed
	if( player == -1 )
		g_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1, 0, NULL, &hAsync, 0 );
	// Send to specific player otherwise
	else
		g_pDP->SendTo( PlayerInfo[player].dpnidPlayer, &bufferDesc, 1, 0, NULL, &hAsync, 0 );
		
    return S_OK;
}

//-----------------------------------------------------------------------------------
// Function called when a player needs to be added to the game(including ourselves)
//-----------------------------------------------------------------------------------
HRESULT	hrCreatePlayer( PVOID pvUserContext, PVOID pMsgBuffer )
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
			// Add player to list
			for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
				if( !PlayerInfo[i].bActive ) {
					PlayerInfo[i].bActive = 1;
					PlayerInfo[i].dpnidPlayer = pCreatePlayerMsg->dpnidPlayer;
					strcpy(PlayerInfo[i].szPlayerName,strName);
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
				// Send them a welcoming message if we are the host
				sprintf(szOutput,"Welcome to the game, %s!",strName);
				if( bHost ) {
					hrSendChatMessage(i,szOutput);	
				}
			}

			SAFE_DELETE_ARRAY( pdpPlayerInfo );
			
			// Update the number of active players in a thread safe way
			InterlockedIncrement( &g_lNumberOfActivePlayers );

			LeaveCriticalSection( &g_csModifyPlayer );
		}
	}
		
	return hReturn;
}

//-----------------------------------------------------------------------------------
// Function called when a player needs to be removed from game
//-----------------------------------------------------------------------------------
HRESULT	hrDestroyPlayer( PVOID pvUserContext, PVOID pMsgBuffer )
{
	PDPNMSG_DESTROY_PLAYER	pDestroyPlayerMsg;
	HRESULT					hReturn = S_OK;
	int						i;
	char					szOutput[256];
		
	// Get a Destroy Message pointer to the buffer
	pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
	
	if( pDestroyPlayerMsg->dwReason == DPNDESTROYPLAYERREASON_NORMAL ) {
		vShowText(hLB_Output,"Player Left Normally");
	}
	else if( pDestroyPlayerMsg->dwReason == DPNDESTROYPLAYERREASON_CONNECTIONLOST  ) {
		vShowText(hLB_Output,"Connection Lost w/Player");
	}
	else if( pDestroyPlayerMsg->dwReason == DPNDESTROYPLAYERREASON_SESSIONTERMINATED  ) {
		vShowText(hLB_Output,"Player Terminated Session");
	}
	else if( pDestroyPlayerMsg->dwReason == DPNDESTROYPLAYERREASON_HOSTDESTROYEDPLAYER  ) {
		vShowText(hLB_Output,"Player Kicked By Host");
	}
	
	// Update the number of active players in a thread safe way
	InterlockedDecrement( &g_lNumberOfActivePlayers );

	EnterCriticalSection( &g_csModifyPlayer );

	// Remove Player from list
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		if( PlayerInfo[i].bActive ) {
			if( PlayerInfo[i].dpnidPlayer == pDestroyPlayerMsg->dpnidPlayer ) {
				PlayerInfo[i].bActive = 0;
				sprintf(szOutput,"<Slot%d><%s> Left The Game",i,PlayerInfo[i].szPlayerName);
				vShowText(hLB_Output,szOutput);
				break;
			}
		}
	}
	
	LeaveCriticalSection( &g_csModifyPlayer );
	
	return(hReturn);
}

//-----------------------------------------------------------------------------------
// Function called when it is time to connect to a game
//-----------------------------------------------------------------------------------
HRESULT hrJoinGame( HWND hWnd )
{
	HRESULT					hReturn = S_OK;
	WCHAR					wszHostName[256];
	WCHAR					wszPeerName[256];
	char					szPeerName[256];
	char					szIP[256];
	char					szPort[256];
	DWORD					dwPort;
	DWORD					dwLength = 256;
	DPN_APPLICATION_DESC	dpnAppDesc;
	DPN_PLAYER_INFO			dpPlayerInfo;

	vShowText(hLB_Output,"Attempting Connection...");

	// Set the peer info
	GetWindowText(hEB_InputName,szPeerName,36);	// Get name from Window Edit Box
	DXUtil_ConvertGenericStringToWide( wszPeerName, szPeerName );
	
	ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
	dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
	dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
	dpPlayerInfo.pwszName = wszPeerName;
	
	// Make this a synchronous call
	if( FAILED( hReturn = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNSETPEERINFO_SYNC ) ) ) {
		vShowText(hLB_Output,"Failed to set peer info");
		return -1;
	}
		
	// Prepare the application description
	ZeroMemory( &dpnAppDesc, sizeof( DPN_APPLICATION_DESC ) );
	dpnAppDesc.dwSize = sizeof( DPN_APPLICATION_DESC );
	dpnAppDesc.guidApplication = DP_CHAT;

	// Get IP from edit box
	GetWindowText(hEB_InputServerIP,szIP,32);
	// Get Port from edit box
	GetWindowText(hEB_InputServerPort,szPort,6);
	// Convert the IP to a wide string
	DXUtil_ConvertGenericStringToWide( wszHostName, szIP );
	// Convert the port string to a DWORD
	dwPort = atol(szPort);

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
		vShowText(hLB_Output,"Failed to Connect");
		return -1;
	}
	SetTimer( hWnd, TIMERID_CONNECT_COMPLETE, 100, NULL );

	return(hReturn);
}

//-----------------------------------------------------------------------------------
// Functions called when player wants to host a game
//-----------------------------------------------------------------------------------
HRESULT	hrHostGame( HWND hWindow)
{
	HRESULT					hReturn;
	char					szPeerName[256];
	char					szSessionName[256];
	WCHAR					wszPeerName[256];
	WCHAR					wszSessionName[256];
	DPN_APPLICATION_DESC	dnAppDesc;
	char					szPort[6];
	DWORD					dwLength = 256;
	DPN_PLAYER_INFO			dpPlayerInfo;
	DWORD					dwPort = 9000;
	
	//
	// Setup our player information
	//
	GetWindowText(hEB_InputName,szPeerName,36);	// Get name from Window Edit Box
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
	dnAppDesc.guidApplication	= DP_CHAT;
	dnAppDesc.pwszSessionName	= wszSessionName;
	dnAppDesc.dwMaxPlayers		= MAX_PLAYERS;
	dnAppDesc.dwFlags			= DPNSESSION_MIGRATE_HOST;
	
	// Get Port from edit box
	GetWindowText(hEB_InputServerPort,szPort,6);
	// Convert the port string to a DWORD
	dwPort = atol(szPort);
	
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
	
	vShowText(hLB_Output,"<- Hosting ->");
	
	return hReturn;
}




