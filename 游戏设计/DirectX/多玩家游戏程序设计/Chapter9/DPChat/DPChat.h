//###################################################################################
//#																					#
//#			Chapter 9 - DPChat, HEADER FILE											#		
//#																					#
//#						Demonstrates Game Hosting and Joining						#
//#																					#
//#						Todd Barron, 12/03/2000										#
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
#define	IDC_hBU_Host				40004
#define	IDC_hEB_InputServerIP		40005
#define	IDC_hEB_InputServerPort		40006
#define	IDC_hEB_InputName			40007
#define	IDC_hST_TextServerIP		40008
#define	IDC_hST_TextServerPort		40009
#define	IDC_hST_TextName			40010
#define	IDC_hEB_InputField			40011
// Handles to child windows
HWND		hBU_Join			= NULL;
HWND		hBU_Host			= NULL;
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
GUID DP_CHAT = { 0x2ae835d, 0x9179, 0x485f, { 0x83, 0x43, 0x90, 0x1d, 0x32, 0x7c, 0xe7, 0x94 } };

// Class name & app name
LPCTSTR		lpszApplicationName = "DPChat";
LPCTSTR		lpszTitle			= "DPChat";

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Peer*       g_pDP;
IDirectPlay8Address*    g_pDeviceAddress;
IDirectPlay8Address*    g_pHostAddress;
DPNHANDLE				g_hConnectAsyncOp;
DPNID					g_dpnidLocalPlayer = 0;

#define MAX_PLAYERS		4

struct PLAYER_INFORMATION
{
	bool	bActive;
    DPNID	dpnidPlayer;
    char	szPlayerName[32];
};

PLAYER_INFORMATION	PlayerInfo[MAX_PLAYERS];

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
BOOL	bHost = 0;

//-----------------------------------------------------------------------------------
// Packet Structures
//-----------------------------------------------------------------------------------
struct PACKET_CHAT
{
	char	szText[256];
};

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
HRESULT	hrSendChatMessage(int player, char	*szmessage);
// Function to handle all incoming Dplay messages
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
// Function to host a game
HRESULT	hrHostGame( HWND hwnd );
// Function to join a game
HRESULT	hrJoinGame( HWND hWnd );
// Function called when a player joins the game
HRESULT	hrCreatePlayer( PVOID pvUserContext, PVOID pMsgBuffer );
// Function called when a player leaves the game
HRESULT	hrDestroyPlayer( PVOID pvUserContext, PVOID pMsgBuffer );


