#include <windows.h>
#include <stdio.h>
#include "..\\SocketObject\\SocketObject.h"
#include "packets.h"

#define	IDC_hEB_InputField			40000
#define	IDC_hBU_Send				40001
#define	IDC_hLB_Output				40002
#define	IDC_hEB_InputServerIP		40003
#define	IDC_hEB_InputServerPort		40004
#define	IDC_hEB_InputName			40005
#define	IDC_hST_TextServerIP		40006
#define	IDC_hST_TextServerPort		40007
#define	IDC_hST_TextName			40008

// create some global handles for our child window components
HWND	hEB_InputField		= NULL;
HWND	hEB_InputServerIP	= NULL;
HWND	hEB_InputServerPort	= NULL;
HWND	hEB_InputName		= NULL;
HWND	hBU_Send			= NULL;
HWND	hLB_Output			= NULL;
HWND	hST_TextServerIP	= NULL;
HWND	hST_TextServerPort	= NULL;
HWND	hST_TextName		= NULL;

LPCTSTR lpszApplicationName = "WinUberClient";
LPCTSTR lpszTitle			= "WinUberClient";
HINSTANCE hInst;

//
// Packet Information
//
SocketObject				ClientSocketObject;		// Client Socket Object
int							iBytesReceived = 0;		// # of Bytes Received
int							iBytesSent = 0;			// # of Bytes Sent
char						szCommand[128];			// Chat Buffer
char						szPacketBuffer[128000];
int							i;
int							iMyID = 0;
stPlayerIDResponsePacket	stPlayerIDPacket;	
stPacketHeader				stHeaderPacket;
stPlayerCommandPacket		stPlayerCommand;
stTextResponsePacket		stTextResponse;
int							iLastPacketSent = 0;
char						szServerIP[32];
int							iServerListenPort = 6000;
int							iConnected = 0;

// function prototypes
void Initialize(HWND hWnd);
void vShowText(char *szText);
void vShowServerText(char *szServerText);

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);

//
// Function to Create the Window and Display it ( REQUIRED FOR ALL WINDOWS PROGRAMS )
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG			msg;
	HWND		hWnd;
	WNDCLASSEX	wndclass;
	
	// Set up window attributes
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= fnMessageProcessor;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= lpszApplicationName;	// Registered Class Name
	wndclass.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );

	if( RegisterClassEx( &wndclass ) == 0 ) 
	{
		// Do error logic here
		exit(1);
	}

	// Create the window
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
	
	// create our child window controls
	hInst = hInstance;
	Initialize(hWnd);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// Process messages until the program is terminated
	while( TRUE )
	{
		// Check for Windows Events & Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return(msg.wParam);
}

// -------------------------------------------------------------------------------
LRESULT CALLBACK fnMessageProcessor ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	char	szMessage[200];
	
	switch (iMsg)
    {
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				// Check if player wants to connect to the server
				case IDC_hBU_Send:
					// Get connection information from text boxes
					GetWindowText(hEB_InputServerIP,szServerIP,32);
					GetWindowText(hEB_InputServerPort,szMessage,32);
					iServerListenPort = atoi(szMessage);
					vShowText("Connecting to Server");
					if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) )
					{
						vShowText("Connected, Waiting for ID");
						// Create the connection thread
						ClientSocketObject.stReceive.skSocket = ClientSocketObject.skSocket;
						ClientSocketObject.stReceive.szBuffer[0] = NULL;
						ClientSocketObject.stReceive.iReadPos = 0;
						ClientSocketObject.stReceive.iWritePos = 0;
						ClientSocketObject.stReceive.iTerminate = 0;

						// Create the thread to receive data
						CreateThread(
							NULL,  
							NULL,                        
							(LPTHREAD_START_ROUTINE ) &ClientSocketObject.thrReceiveThread,     
							&ClientSocketObject.stReceive,          
							NULL,									
							&ClientSocketObject.dwReceiveHandle
						);

						// Loop until we get an ID packet back from the server
						while( 1 ) {
							iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
							//  Process the Packet
							if( iBytesReceived ) {
								// Check the header
								memcpy(&stHeaderPacket,szPacketBuffer,sizeof(stHeaderPacket));
								// Check if type equals ID packet
								if( stHeaderPacket.iType == PACKET_PLAYERID ) {
									memcpy(&stPlayerIDPacket,szPacketBuffer,sizeof(stPlayerIDPacket));
									iMyID = stPlayerIDPacket.iID;
									sprintf(szMessage,"Received, ID = %d", iMyID);
									vShowText(szMessage);
									vShowText("==============================================");
									vShowText("                   Welcome to UberAdventure!  ");
									vShowText("                       Windows Client v1.0    ");
									vShowText("                                              ");
									vShowText("                        Command ? For Help    ");
									vShowText("==============================================");
									iConnected = 1;
									DestroyWindow(hBU_Send);
									break;
								}
							}
						}
						//
						// Create the command window
						//
						hEB_InputField = CreateWindowEx(
							WS_EX_CLIENTEDGE,
							"EDIT",NULL,
							WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
							5,
							280,
							380,
							28,
							hWnd,(HMENU)IDC_hEB_InputField,hInst,NULL);
					}
					else {
						vShowText("--> Unable to Connect to Server <--");
					}
					break;
			}
			switch(HIWORD(wParam))
			{
				case EN_UPDATE:
					// Get the text from the edit box
					GetWindowText(hEB_InputField,szMessage,200);
					// Check if they pressed enter
					if( szMessage[strlen(szMessage)-1] == 10 ) {
						// Dont send a message if just the enter key
						if( strlen(szMessage) > 2 ) {
							szMessage[strlen(szMessage)-2] = '\0';
							// display the text locally
							vShowText(szMessage);
							// Find the end of the command segment
							i = 0;
							while( szMessage[i] != 32 ) {
								if( szMessage[i] == '\0' ) {
									// Invalid target
									i = -1;
									break;
								}
								i++;
							}
							//
							// Send The Packet
							//
							
							// Setup Header Information
							stPlayerCommand.stHeader.iID = iLastPacketSent;
							stPlayerCommand.stHeader.iType = PACKET_PLAYERCOMMAND;
							stPlayerCommand.stHeader.iLength = 96;
							stPlayerCommand.stHeader.iSender = iMyID;
							stPlayerCommand.stHeader.iCheckSum = ((iLastPacketSent+PACKET_PLAYERCOMMAND+96));
							
							// Fill in target if one was specified
							if( i != -1 ) {
								sprintf(stPlayerCommand.szTarget,&szMessage[(i+1)]);
							}
							else {
								sprintf(stPlayerCommand.szTarget,"");
							}
							sprintf(stPlayerCommand.szCommand,szMessage);
							stPlayerCommand.szCommand[i] = '\0';
							sprintf(stPlayerCommand.szPlayerID,"%d",iMyID);
							memcpy(szPacketBuffer,&stPlayerCommand,sizeof(stPlayerCommand));
							// Send data
							iBytesSent = ClientSocketObject.Send(szPacketBuffer, sizeof(stPlayerCommand), 0);
							iLastPacketSent++;
							
							// Check for server disconnection
							if( iBytesSent == -1 ) {
								break;
							}
							else {
								// Loop until we get a response from the server
								while( 1 ) {
									iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
									//  Process the Packet
									if( iBytesReceived ) {
										// Check the header
										memcpy(&stHeaderPacket,szPacketBuffer,sizeof(stHeaderPacket));
										// Check if a text response packet
										if( stHeaderPacket.iType == PACKET_TEXTRESPONSE ) {
											memcpy(&stTextResponse,&szPacketBuffer,sizeof(stTextResponse));
											SendMessage(hLB_Output,LB_RESETCONTENT,0,0);
											vShowText("==============================================");
											vShowServerText(stTextResponse.szResponse);
											vShowText("==============================================");
											break;
										}
									}
								}
							}
						}
						// clear input field
						SetWindowText(hEB_InputField,"");
					}
					break;
			}
			break;
		case WM_KEYDOWN:
			break;
		case WM_CREATE:
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			
		default:
			return(DefWindowProc(hWnd, iMsg, wParam, lParam));
    }
	return(0L);
}

//
// Function to Initialize child objects
//
void Initialize(HWND hWnd)
{
	// hEB_InputServerIP
	hST_TextServerIP = CreateWindow(
		"static","Server IP",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		5,
		5,
		120,
		28,
		hWnd,(HMENU)IDC_hST_TextServerIP,hInst,NULL);

	// hEB_InputServerIP
	hST_TextServerPort = CreateWindow(
		"static","Port",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		125,
		5,
		50,
		28,
		hWnd,(HMENU)IDC_hST_TextServerPort,hInst,NULL);

	// hEB_InputServerIP
	hST_TextName = CreateWindow(
		"static","Player Name",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		250,
		5,
		135,
		28,
		hWnd,(HMENU)IDC_hST_TextName,hInst,NULL);

	// hEB_InputServerIP
	hEB_InputServerIP = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","192.168.0.2",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		5,
		20,
		120,
		28,
		hWnd,(HMENU)IDC_hEB_InputServerIP,hInst,NULL);

	// hEB_InputServerPort
	hEB_InputServerPort = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","6000",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		125,
		20,
		50,
		28,
		hWnd,(HMENU)IDC_hEB_InputServerPort,hInst,NULL);

	// hEB_InputName
	hEB_InputName = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT","Avatar",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		250,
		20,
		135,
		28,
		hWnd,(HMENU)IDC_hEB_InputName,hInst,NULL);

	// hLB_Output
	hLB_Output = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"LISTBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER,
		5,
		47,
		380,
		230,
		hWnd,(HMENU)IDC_hLB_Output,hInst,NULL);	
	
	// hBU_SendIcon
	hBU_Send = CreateWindow(
		"BUTTON",
		"Connect",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		285,
		280,
		100,
		28,
		hWnd,(HMENU)IDC_hBU_Send,hInst,NULL);
}

//
// Function to display text into the edit window
//
void vShowText(char *szText)
{
	int Line;
	
	// add string to the listbox
	SendMessage(hLB_Output,LB_ADDSTRING,0,(LPARAM) szText);
	
	// determine number of items in listbox
	Line = SendMessage(hLB_Output,LB_GETCOUNT,0,0);
	
	// flag last item as the selected item, to scroll listbox down
	SendMessage(hLB_Output,LB_SETCURSEL,Line-1,0);
	
	// unflag all items to eliminate negative highlite
	SendMessage(hLB_Output,LB_SETCURSEL,-1,0);
}

void vShowServerText(char *szServerText)
{
	int		Line;
	int		i;
	char	szTempSend[32768];
	int		iBegin = 0,iEnd = 0;

	for( i = 0 ;i < (signed)strlen(szServerText); i++ ) {
		// Look for line feeds
		if( szServerText[i] == '\n' ) {
			sprintf(szTempSend,&szServerText[iBegin]);
			szTempSend[i-iBegin] = '\0';
			// add string to the listbox
			SendMessage(hLB_Output,LB_ADDSTRING,0,(LPARAM) szTempSend);
			
			// determine number of items in listbox
			Line = SendMessage(hLB_Output,LB_GETCOUNT,0,0);
			
			// flag last item as the selected item, to scroll listbox down
			SendMessage(hLB_Output,LB_SETCURSEL,Line-1,0);
			
			// unflag all items to eliminate negative highlite
			SendMessage(hLB_Output,LB_SETCURSEL,-1,0);
			iBegin = (i+1);
		}
	}
}
