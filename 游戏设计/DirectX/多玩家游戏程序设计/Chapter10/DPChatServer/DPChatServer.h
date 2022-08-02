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
#define	IDC_hLB_Output				40002
#define	IDC_hEB_InputField			40011
// Handles to child windows
HWND		hLB_Output			= NULL;
HWND		hEB_InputField		= NULL;

// Timer Ids
#define TIMERID_CONNECT_COMPLETE    1
#define TIMERID_POLLGAMES			2

// GUID, Needed to identify application
static const GUID GUID_CHATSERVER = { 0xf2b1f801, 0x4829, 0x4bba, { 0xb8, 0x60, 0xb9, 0x10, 0xfa, 0xa2, 0x76, 0x41 } };

// Class name & app name
LPCTSTR		lpszApplicationName = "ChatServer";
LPCTSTR		lpszTitle			= "ChatServer";

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Server*		g_pDPServer;
IDirectPlay8Address*    g_pDeviceAddress;
DPNHANDLE				g_hConnectAsyncOp;
DPNID					g_dpnidLocalPlayer = 0;

#define MAX_PLAYERS		16

struct PLAYER_INFORMATION
{
	bool	bActive;
    DPNID	dpnidPlayer;
    char	szPlayerName[32];
};

PLAYER_INFORMATION	PlayerInfo[MAX_PLAYERS];

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
CRITICAL_SECTION        g_csModifyPlayer;

//-----------------------------------------------------------------------------------
// Miscellaneous Variables
//-----------------------------------------------------------------------------------
LONG	g_lNumberOfActivePlayers = 0;

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
// Function to send chat message
HRESULT	hrSendServerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer );
// Function to handle all incoming Dplay messages
HRESULT WINAPI LoginDirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
// Function to host a game
HRESULT	hrHostGame( HWND hwnd );
// Function called when a player joins the game
HRESULT	hrCreatePlayer( PVOID pvUserContext, PVOID pMsgBuffer );
// Function called when a player leaves the game
HRESULT	hrDestroyPlayer( PVOID pvUserContext, PVOID pMsgBuffer );

