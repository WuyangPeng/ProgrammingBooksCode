//###################################################################################
//#																					#
//#			Chapter 10 - Direct Play Program										#
//#																					#
//#						Demonstrates Client/Server Model							#
//#																					#
//#						Todd Barron, 1/21/2000										#
//#																					#
//###################################################################################
#define INITGUID
#include <windows.h>
#include <dplay8.h>
#include <stdio.h>
#include "DXUtil.h"

//-----------------------------------------------------------------------------------
// Windows Globals
//-----------------------------------------------------------------------------------

// Icon Resource
#define IDI_ICON1					101
// ID's for child windows
#define	IDC_hBU_Join				40001
#define	IDC_hLB_Output				40002
#define	IDC_hEB_InputServerIP		40005
#define	IDC_hEB_InputServerPort		40006
#define	IDC_hEB_InputName			40007
#define	IDC_hST_TextServerIP		40008
#define	IDC_hST_TextServerPort		40009
#define	IDC_hST_TextName			40010
#define	IDC_hEB_InputField			40011
// Handles to child windows
HWND		hBU_Join			= NULL;
HWND		hLB_Output			= NULL;
HWND		hEB_InputServerIP	= NULL;
HWND		hEB_InputServerPort	= NULL;
HWND		hEB_InputName		= NULL;
HWND		hEB_InputField		= NULL;
HWND		hST_TextServerIP	= NULL;
HWND		hST_TextServerPort	= NULL;
HWND		hST_TextName		= NULL;

// Timer Ids
#define TIMERID_CONNECT_COMPLETE    1

// GUID, Needed to identify application
static const GUID GUID_CHATSERVER = { 0xf2b1f801, 0x4829, 0x4bba, { 0xb8, 0x60, 0xb9, 0x10, 0xfa, 0xa2, 0x76, 0x41 } };

// Class name & app name
LPCTSTR		lpszApplicationName = "DPChatClient";
LPCTSTR		lpszTitle			= "DPChatClient";

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Client*		g_pDP;
IDirectPlay8Address*	g_pDeviceAddress;
IDirectPlay8Address*	g_pHostAddress;
DPNHANDLE				g_hConnectAsyncOp;
DPNID					g_dpnidLocalPlayer = 0;

//-----------------------------------------------------------------------------------
// Packet Structures
//-----------------------------------------------------------------------------------
#define PACKET_TYPE_GENERIC 0
#define PACKET_TYPE_CHAT	1

class	PacketGeneric
{
	public:
		DWORD	dwType;
		DWORD	dwSize;
};

class	PacketChat : public PacketGeneric
{
	public:
		char	szText[128];
};

//-----------------------------------------------------------------------------------
// Multi-Threading Variables
//-----------------------------------------------------------------------------------
HANDLE                  g_hConnectCompleteEvent;
HRESULT					g_hrConnectComplete;

//-----------------------------------------------------------------------------------
// Functions for our Windows Interface
//-----------------------------------------------------------------------------------

// Message Loop CallBack Function prototype ( REQUIRED FOR ALL WINDOWS PROGRAMS )
LRESULT CALLBACK fnMessageProcessor (HWND, UINT, WPARAM, LPARAM);

// Function to display text in the output box
void vShowText(HWND	hChildHandle, char *szText);
// Function to setup display of GUI
void vCreateInterface(HWND hWnd,HINSTANCE hInstance);
// Function called when program exits, cleans up allocated objects
void vCleanup(void);

//-----------------------------------------------------------------------------------
// DirectPlay Functions
//-----------------------------------------------------------------------------------

// Function to initialize direct play system
HRESULT hrInitializeDirectPlay( HWND hWindow );
// Function to handle all incoming Dplay messages
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
// Function to join a game
HRESULT	hrJoinGame( HWND hWnd );
// Function to send a message to the server
HRESULT	hrSendClientMessage( DWORD dwMessageType, PVOID pMsgBuffer );

