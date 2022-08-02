//###################################################################################
//#																					#
//#			Chapter 16 - RPGQuest Game Server										#
//#																					#
//#						Demonstrates MMORPG Server (HEADER FILE)					#
//#																					#
//#						Todd Barron, 3/01/2001										#
//#																					#
//###################################################################################
#define INITGUID
#include <windows.h>
#include <dplay8.h>
#include <stdio.h>
#include "DXUtil.h"
#include <d3dx8.h>
#include <mmsystem.h>

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
static const GUID GUID_GAMESERVER = { 0xd7336b01, 0x6037, 0x4fba, { 0x97, 0xe5, 0xab, 0x38, 0xe0, 0x4, 0x7b, 0xe9 } };

// Class name & app name
LPCTSTR		lpszApplicationName = "RPGGameServer";
LPCTSTR		lpszTitle			= "RPGGameServer";

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Server*		g_pDPServer;
IDirectPlay8Address*    g_pDeviceAddress;
DPNHANDLE				g_hConnectAsyncOp;
DPNID					g_dpnidLocalPlayer = 0;

#define MAX_PLAYERS		64
#define MAX_ZONES		16
#define ARENA_SIZE		285.0f
#define PI 3.1415926535897932384626433832795
#define DegToRad(deg) ((deg/180.0f)*PI)

struct SERVER_PLAYER_INFORMATION
{
	bool		bActive;
    DPNID		dpnidPlayer;
	D3DXVECTOR3 vecCurPos;
	D3DXVECTOR3 vecLastPos;
	double		fVelocity;
	long		lScore;
	int			iFrame;
	float		fRot;
    char		szPlayerName[32];
	char		szPassword[32];
	int			iZone;
	int			iZoneMap;
	bool		bCredentialsAccepted;
};

struct CLIENT_PLAYER_INFORMATION
{
	bool		bActive;
	D3DXVECTOR3 vecCurPos;
	D3DXVECTOR3 vecLastPos;
	double		fVelocity;
	long		lScore;
	int			iFrame;
	float		fRot;
	int			iZone;
	int			iZoneMap;
	int			iPlayerID;
    char		szPlayerName[32];
};
SERVER_PLAYER_INFORMATION	PlayerInfo[MAX_PLAYERS];

struct ZONE_INFORMATION
{
	int		iZoneID;
	char	szName[32];
	int		iNumbPlayers;
	bool	bActive;
};
ZONE_INFORMATION	ZoneInfo[MAX_ZONES];

//-----------------------------------------------------------------------------------
// Multi-Threading Variables
//-----------------------------------------------------------------------------------
CRITICAL_SECTION        g_csModifyPlayer;
CRITICAL_SECTION		g_csMessageSection;

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
HRESULT	hrInitializeGameServer(void);
// Game specific functions
void vSendUniqueMessage(int iplayer, char *szmessage, D3DCOLOR color);
void vRequestPlayerPassword(int iplayer);
bool bValidatePlayer(int iplayer, char *szpassword);
int iGetPlayerID(DPNID dpid);
bool bReadPlayerInfo(int iplayer);
void vUpdatePlayerPosition(int iplayer);
bool bSavePlayerInfo(int iplayer);
void vCreatePlayerAccount(int iplayer, char *szpassword);
int iValidatePlayerPosition(int i, int iZone, float x, float y, float z);
void vZonePlayer(int iplayer, int inewzone);
void vZonePlayer(int iplayer);
int iGetNumberOfPlayers(int izone);
void vSendPlayerInformation(int iplayer, int ireceive);
void vUpdateTimeOfDay(void);
void vInformOfRemoval(int iplayer);
void vSendPlayerAttitude( int iplayer, bool bEcho = 0 );
void vGetVelocity( float fAngle, float &vx, float &vz );
void vUpdatePlayers(void);
void vAddMessage( void *data, int itype, int iplayer );
int iGetMessage( void );
void vProcessMessages(void);

//-----------------------------------------------------------------------------------
// DirectPlay Functions
//-----------------------------------------------------------------------------------

// Function to initialize direct play system
HRESULT hrInitializeDirectPlay( HWND hWindow );
// Function to send chat message
HRESULT	hrSendServerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer, DWORD flags = 0 );
// Function to handle all incoming Dplay messages
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
// Function to host a game
HRESULT	hrHostGame( HWND hwnd );
// Function called when a player joins the game
HRESULT	hrCreatePlayer( PVOID pMsgBuffer );
// Function called when a player leaves the game
HRESULT	hrDestroyPlayer( PVOID pMsgBuffer );

DWORD	dwDayTimer = 0;
int		iTimeValue = 255;
int		iTimeDirection = 0;

class GameMessage
{
		void vFreeData(void);
	public:
		unsigned char	*byteMessageBuffer;
		int		iType;
		int		iPlayerID;
		GameMessage();
		~GameMessage();
};

GameMessage::GameMessage()
{
	byteMessageBuffer = new unsigned char[4096];
	memset(byteMessageBuffer,0,4096);
}

GameMessage::~GameMessage()
{
	vFreeData();
}

void GameMessage::vFreeData(void)
{
	if( byteMessageBuffer ) {
		delete [] byteMessageBuffer;
		byteMessageBuffer = NULL;
	}
}

GameMessage		gameMessage[1000];
int				iCurMessage = 0;
int				iLastMessage = 0;
