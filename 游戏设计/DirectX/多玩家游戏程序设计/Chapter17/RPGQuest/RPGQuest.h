//###################################################################################
//#																					#
//#			Chapter 16 - RPGQuest (HEADER FILE)										#		
//#																					#
//#						Complete Client-Server Game									#
//#																					#
//#						Todd Barron, 03/12/2001										#
//#																					#
//###################################################################################

#define WIN32_LEAN_AND_MEAN	// No MFC
#include <dplay8.h>
#include <dinput.h>
#include <mmsystem.h>
#include "Object3DClass.h"
#include "SoundSystem.h"

//-----------------------------------------------------------------------------------
//
// #DEFINES & Constants
//
//-----------------------------------------------------------------------------------
#define MAX_TEXTURES	20
#define MAX_PLAYERS		8
#define IDI_ICON1		101
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define ARENA_SIZE		285.0f
// DPlay
#define TIMERID_CONNECT_COMPLETE    1

// GUID, Needed to identify application
static const GUID GUID_GAMESERVER = { 0xd7336b01, 0x6037, 0x4fba, { 0x97, 0xe5, 0xab, 0x38, 0xe0, 0x4, 0x7b, 0xe9 } };

// D3D
#define PI 3.1415926535897932384626433832795
#define DegToRad(deg) ((deg/180.0f)*PI)
#define VIDEODEVICEERROR_NOCOMPATIBLE	0x82000001
#define VIDEODEVICEERROR_NOWINDOWED		0x82000002
// DInput
#define KEYBOARD_BUFFERSIZE			10
#define INPUTERROR_NODI				0x81000001
#define INPUTERROR_NOKEYBOARD		0x81000002
#define INPUTERROR_KEYBOARDEXISTS	0x81000003

//-----------------------------------------------------------------------------------
//
// Structures & Classes
//
//-----------------------------------------------------------------------------------
struct GAME_SOUNDS
{
	GameSound	*gsFire;
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

struct D3DModeInfo
{
    DWORD      Width; 
    DWORD      Height;
    D3DFORMAT  Format;
    DWORD      dwBehavior; 
    D3DFORMAT  DepthStencilFormat;
};

struct D3DDeviceInfo
{
    D3DDEVTYPE	DeviceType;
    D3DCAPS8	d3dCaps; 
    char		szDesc[32];
    BOOL		bCanDoWindowed;
    DWORD		dwNumModes;
    D3DModeInfo	modes[150];
    DWORD		dwCurrentMode;
    BOOL		bWindowed;
    D3DMULTISAMPLE_TYPE MultiSampleType;
};

struct D3DAdapterInfo
{
    D3DADAPTER_IDENTIFIER8 d3dAdapterIdentifier;
    D3DDISPLAYMODE d3ddmDesktop; 
    DWORD          dwNumDevices;
    D3DDeviceInfo  devices[5];
    DWORD          dwCurrentDevice;
};

//-----------------------------------------------------------------------------------
//
// Function Prototypes
//
//-----------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT hrInit3D( HWND hWnd );
void vCleanup(void);
void vRenderScene(void);
void vSetupView(void);
void vInitGeometry(void);
void vCreateLights(void);
void vGetVelocity( float fAngle, float &vx, float &vz );
int iAddPlayer(int id, CLIENT_PLAYER_INFORMATION pinfo);
void vRemovePlayer(int id);
void vInitializeObjects(void);
void vInitSoundEngine(HWND hWnd);
void vUpdateObjects(void);
void vUpdateCamera(void);
void vUpdateNetwork(void);
int iGetPlayerID(int id);
HRESULT hrInitializeDirectPlay( HWND hWindow );
HRESULT	hrSendClientMessage( DWORD dwMessageType, PVOID pMsgBuffer, DWORD flags = 0 );
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
HRESULT	hrHostGame( HWND hwnd );
HRESULT	hrJoinGame( HWND hWnd );
BOOL bFindDepthStencilFormat( DWORD dwMinDepth, DWORD dwMinStencil, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat );
BOOL bValidateFormat(D3DFORMAT d3dfFormatToTest, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat);
HRESULT hrBuildDeviceList(HWND hWnd);
HRESULT hrConfirmDevice( D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format );
HRESULT	hrInitDirectInput(void);
HRESULT hrInitKeyboard(HWND hWnd);
BYTE Scan2Ascii(DWORD scancode);
HRESULT hrReadKeyboard( void );
void vAddMessage(char *szmessage, D3DCOLOR color);
void vUpdateTimeOfDay(int newtime);
void vSubmitPassword(void);

//-----------------------------------------------------------------------------------
//
// Global Variables
//
//-----------------------------------------------------------------------------------
// Windows Globals
const char				*szWndClass		= "RPG";
const char				*szProgramName	= "RPGQuest";
HINSTANCE				g_hInstance;

//-----------------------------------------------------------------------------------
// Direct 3D Objects
//-----------------------------------------------------------------------------------
LPDIRECT3D8				pD3D = NULL;
LPDIRECT3DDEVICE8		pd3dDevice = NULL;
D3DXMATRIX				matProj;		// Projection Data
D3DXMATRIX				matCameraView;	// Camera Data
D3DXVECTOR3				vecCameraSource;
D3DXVECTOR3				vecCameraTarget;
LPDIRECT3DTEXTURE8      g_pTexture[MAX_TEXTURES];
Object3DClass			o3dPlayer;
Object3DClass			o3dZone[4];

//-----------------------------------------------------------------------------------
// Direct Sound Objects
//-----------------------------------------------------------------------------------
SoundSystem				SoundEngine;
GAME_SOUNDS				g_GameSounds;

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Client*     g_pDP = NULL;
IDirectPlay8Address*    g_pDeviceAddress = NULL;
IDirectPlay8Address*    g_pHostAddress = NULL;
DPNHANDLE				g_hConnectAsyncOp = NULL;
DPNID					g_dpnidLocalPlayer = 0;
CLIENT_PLAYER_INFORMATION		PlayerInfo[MAX_PLAYERS];
CLIENT_PLAYER_INFORMATION		LocalPlayer;
int						g_iMyPlayerId = 0;
LONG					g_lNumberOfActivePlayers = 0;
BOOL					bHost = 0;

//-----------------------------------------------------------------------------------
// Multi-Threading Variables
//-----------------------------------------------------------------------------------
CRITICAL_SECTION        g_csModifyPlayer;

//-----------------------------------------------------------------------------------
// Direct Input Objects
//-----------------------------------------------------------------------------------
LPDIRECTINPUT8			pDI = NULL;         
LPDIRECTINPUTDEVICE8	pKeyboard = NULL; 
BYTE					diks[256];
BYTE					ascKeys[256];
HKL						g_Layout;

//-----------------------------------------------------------------------------------
// Miscellaneous Variables
//-----------------------------------------------------------------------------------
// Font
LPD3DXFONT		pD3DXFont = NULL;
HFONT			hFont = NULL;
bool			bTurnLeft = 0;
bool			bTurnRight = 0;
bool			bAccelerate = 0;
bool			bDeaccelerate = 0;
// Video
D3DAdapterInfo  g_Adapters[10];
DWORD           g_dwNumAdapters = 0;
DWORD           g_dwAdapter = 0;
BOOL            g_bUseDepthBuffer = TRUE;
BOOL			g_bWindowed = TRUE;
int				iZone = 0;
int				iZoneMap = 0;

struct GAME_MESSAGE
{
	char		szMessage[128];
	D3DCOLOR	color;		
};

int				iLastMessage = 0;
int				iMessageLogPos = 0;
GAME_MESSAGE	MessageLog[64];	// 64 messages
int				iTimeOfDay = 0;
bool			bUpdateTime = 0;
D3DCOLOR		colorTimeColor;
int				iUpdates = 0;	// Frame Update Counter
