//###################################################################################
//#																					#
//#			Chapter 10 - Direct Play Program										#
//#																					#
//#						Demonstrates Client/Server Model							#
//#																					#
//#						Todd Barron, 1/21/2000										#
//#																					#
//###################################################################################
#include "dpchatclient.h"

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
	char		szMessage[256];
	char		szCompMessage[256];
	char		szMyName[32];
	HRESULT		hReturn;
	void		*packet;
	PacketChat	ChatMsg;
	
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
						GetWindowText(hEB_InputName,szMyName,32);
						sprintf(szCompMessage,"<%s> %s", szMyName, szMessage);
						// clear input field
						SetWindowText(hEB_InputField,"");
						//
						// Send a chat packet to the server
						//
						ChatMsg.dwSize = sizeof(PacketChat);
						ChatMsg.dwType = PACKET_TYPE_CHAT;
						strcpy(ChatMsg.szText,szCompMessage);
						// Convert the packet to a void stream
						packet = (VOID*)&ChatMsg;
						// Send the chat packet
						hReturn = hrSendClientMessage(PACKET_TYPE_CHAT,packet);
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
	
	// Initialize COM
	hReturn = CoInitialize( NULL );
	if( FAILED(hReturn) ) {
		MessageBox( hWindow, "Error Initializing COM", "DirectPlay Error", MB_ICONERROR );
		return hReturn;
	}
	
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

	// Create connection complete event for later use
	g_hConnectCompleteEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	vShowText(hLB_Output,"<<--TCP INITED-->>");

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
	HRESULT		hReturn = S_OK;
	PacketChat	*ChatMsg;
	
	switch( dwMessageId ) 
	{
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
			PacketGeneric	*PGen;

			pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
			
			// Cast it to a generic packet so we can check the type
			PGen = (PacketGeneric*)pReceiveMsg->pReceiveData;

			// If it is a chat packet, display its contents
			if( PGen->dwType == PACKET_TYPE_CHAT ) {
				// Convert the packet to a chat packet
				ChatMsg = (PacketChat*)pReceiveMsg->pReceiveData;
				// Output it on our screen
				vShowText(hLB_Output,ChatMsg->szText);
			}
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
// Function called when it is time to connect to a game
//-----------------------------------------------------------------------------------
HRESULT hrJoinGame( HWND hWnd )
{
	HRESULT					hReturn = S_OK;
	WCHAR					wszHostName[256];
	WCHAR					wszClientName[256];
	char					szClientName[256];
	char					szIP[256];
	char					szPort[256];
	DWORD					dwPort;
	DWORD					dwLength = 256;
	DPN_APPLICATION_DESC	dpnAppDesc;
	DPN_PLAYER_INFO			dpPlayerInfo;

	vShowText(hLB_Output,"Attempting Connection...");

	// Set the Client info
	GetWindowText(hEB_InputName,szClientName,36);	// Get name from Window Edit Box
	DXUtil_ConvertGenericStringToWide( wszClientName, szClientName );
	
	ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
	dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
	dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
	dpPlayerInfo.pwszName = wszClientName;
	
	// Make this a synchronous call
	if( FAILED( hReturn = g_pDP->SetClientInfo( &dpPlayerInfo, NULL, NULL, DPNSETCLIENTINFO_SYNC ) ) ) {
		vShowText(hLB_Output,"Failed to set client info");
		return -1;
	}
		
	// Prepare the application description
	ZeroMemory( &dpnAppDesc, sizeof( DPN_APPLICATION_DESC ) );
	dpnAppDesc.dwSize = sizeof( DPN_APPLICATION_DESC );
	dpnAppDesc.guidApplication = GUID_CHATSERVER;

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
// Functions to send a message to the server
//-----------------------------------------------------------------------------------
HRESULT	hrSendClientMessage( DWORD dwMessageType, PVOID pMsgBuffer )
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

	g_pDP->Send( &bufferDesc, 1, 0, NULL, &hAsync, 0 );

	return S_OK;
}



