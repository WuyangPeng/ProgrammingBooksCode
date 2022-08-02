//###################################################################################
//#																					#
//#			Chapter 10 - Direct Play Program										#
//#																					#
//#						Demonstrates Client/Server Model							#
//#																					#
//#						Todd Barron, 1/21/2000										#
//#																					#
//###################################################################################

#include "DPChatServer.h"

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

	// Process messages until the program is terminated
	while( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
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
						hrSendServerMessage(DPNID_ALL_PLAYERS_GROUP,PACKET_TYPE_CHAT,packet);
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
	
	// Create IDirectPlay8Server Object
	if( FAILED( hReturn = CoCreateInstance( CLSID_DirectPlay8Server, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IDirectPlay8Server, 
		(LPVOID*) &g_pDPServer ) ) )
        MessageBox( hWindow, "Can't Create DPlayServer", "DirectPlay Error", MB_ICONERROR );
	
	// Init IDirectPlay8Server Message Handler
	if( FAILED( hReturn = g_pDPServer->Initialize( NULL, LoginDirectPlayMessageHandler, 0 ) ) ) {
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
	EnterCriticalSection( &g_csModifyPlayer );
	for( i = 0 ; i < MAX_PLAYERS ; i++ ) {
		PlayerInfo[i].bActive = 0;
	}
	LeaveCriticalSection( &g_csModifyPlayer );
	
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
	SAFE_RELEASE( g_pDeviceAddress );
	
	// Uninitialize the COM library
	CoUninitialize();
}

//-----------------------------------------------------------------------------------
// Functions to handle and receive all Direct Play messages
//-----------------------------------------------------------------------------------
HRESULT WINAPI LoginDirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer )
{
	HRESULT	hReturn = S_OK;
	
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
		
		case DPN_MSGID_RECEIVE:
		{
			PDPNMSG_RECEIVE pReceiveMsg;
			PacketGeneric	*PGen;

			pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
			PGen = (PacketGeneric*)pReceiveMsg->pReceiveData;

			// Ignore the packet if we sent it originally
			if( pReceiveMsg->dpnidSender == g_dpnidLocalPlayer ) 
				break;
			
			// If it is a chat packet, send it out to all of the players
			if( PGen->dwType == PACKET_TYPE_CHAT ) {
				void		*packet;
				PacketChat	*ChatMsg;
				// Convert the packet to a void stream
				ChatMsg = (PacketChat*)pReceiveMsg->pReceiveData;
				packet = (VOID*)ChatMsg;
				// Send the chat packet to all clients
				hrSendServerMessage(DPNID_ALL_PLAYERS_GROUP,PACKET_TYPE_CHAT,packet);
				// Output it on our screen
				vShowText(hLB_Output,ChatMsg->szText);
			}
			break;
		}
	}
	
	return hReturn;
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
			}

			SAFE_DELETE_ARRAY( pdpPlayerInfo );
			
			// Update the number of active players in a thread safe way
			if( i != MAX_PLAYERS )
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
	// Setup our player information
	//
	DXUtil_ConvertGenericStringToWide( wszServerName, "DPChat Server" );
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
	DXUtil_ConvertGenericStringToWide( wszSessionName, "DPChat Session" );
	
	ZeroMemory( &dnAppDesc, sizeof(DPN_APPLICATION_DESC) );
	dnAppDesc.dwSize			= sizeof(DPN_APPLICATION_DESC);
	dnAppDesc.guidApplication	= GUID_CHATSERVER;
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
	// Host the Login Server
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
	
	vShowText(hLB_Output,"<- Login Server Listening ->");
	
	return hReturn;
}

//-----------------------------------------------------------------------------------
// Functions to send a server message
//-----------------------------------------------------------------------------------
HRESULT	hrSendServerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer )
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

	// Broadcast it if player set to zero
	if( player == DPNID_ALL_PLAYERS_GROUP ) 
		g_pDPServer->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1, 0, NULL, &hAsync, DPNSEND_NOLOOPBACK );
	else
		g_pDPServer->SendTo( PlayerInfo[player].dpnidPlayer, &bufferDesc, 1, 0, NULL, &hAsync, 0 );

	return S_OK;
}


