//###################################################################################
//#																					#
//#			Chapter 14 - Space Pirates (HEADER FILE)								#		
//#																					#
//#						Complete Peer-To-Peer Game									#
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
#define MAX_BULLETS		128
#define MAX_EXPLOSIONS	128
#define MAX_TEXTURES	20
#define MAX_PLAYERS		8
#define IDI_ICON1		101
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define ARENA_SIZE		240.0f
// DPlay
#define TIMERID_CONNECT_COMPLETE    1
GUID	DP_SPACEPIRATES = { 0x74171a50, 0xe7c0, 0x4257, { 0xa7, 0x8c, 0x14, 0xdb, 0x54, 0xaf, 0x31, 0xa0 } };
#define PACKET_TYPE_GENERIC		0
#define PACKET_TYPE_CHAT		1
#define PACKET_TYPE_ANGLE		2
#define PACKET_TYPE_VELOCITY	3
#define PACKET_TYPE_POSITION	4
#define PACKET_TYPE_BULLET		5
#define PACKET_TYPE_SCORE		6	
// D3D
#define D3DFVF_MYVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
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
	GameSound	*gsExplosion;
	GameSound	*gsFire;
};

struct PLAYER_INFORMATION
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
};

typedef struct MYVERTEX
{
	D3DXVECTOR3 vecPos;
	D3DXVECTOR3 vecNorm;
	DWORD		dwDiffuse;
	float		u;
	float		v;
} MYVERTEX, *LPMYVERTEX;

struct ExplosionObject
{
	bool	bActive;
	float	fx;
	float	fz;
	int		iFrame;
	DWORD	dwFrameTime;
};

struct BulletObject
{
	bool	bActive;
	float	fRot;
	float	fx;
	float	fz;
	float	fVelocity;
	DPNID	dpOwner;
	DWORD	dwFrameTime;
};

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

class	PacketAngle : public PacketGeneric
{
	public:
		float	fAngle;
};

class	PacketVelocity : public PacketGeneric
{
	public:
		float	fVelocity;
};

class	PacketPosition : public PacketGeneric
{
	public:
		float	fx;
		float	fz;
};

class	PacketBullet : public PacketGeneric
{
	public:
		BulletObject	Bullet;
};

class	PacketScore : public PacketGeneric
{
	public:
		long	lScore;
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
int iAddPlayer(DPNID dpid, D3DXVECTOR3 pos, float fRot, char *szName);
void vInitializeObjects(void);
void vInitSoundEngine(HWND hWnd);
void vUpdateObjects(void);
void vUpdateCamera(void);
void vUpdateNetwork(void);
void vCreateBullet(DPNID dpowner, float fx, float fz, float fvel, float frot);
int iGetPlayerID(DPNID dpid);
HRESULT hrInitializeDirectPlay( HWND hWindow );
HRESULT	hrSendPeerMessage( int player, DWORD dwMessageType, PVOID pMsgBuffer );
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
HRESULT	hrHostGame( HWND hwnd );
HRESULT	hrJoinGame( HWND hWnd );
HRESULT	hrCreatePlayer( PVOID pvUserContext, PVOID pMsgBuffer );
HRESULT	hrDestroyPlayer( PVOID pvUserContext, PVOID pMsgBuffer );
BOOL bFindDepthStencilFormat( DWORD dwMinDepth, DWORD dwMinStencil, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat, D3DFORMAT* pDepthStencilFormat );
BOOL bValidateFormat(D3DFORMAT d3dfFormatToTest, UINT iAdapter, D3DDEVTYPE DeviceType, D3DFORMAT TargetFormat);
HRESULT hrBuildDeviceList(HWND hWnd);
HRESULT hrConfirmDevice( D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format );
HRESULT	hrInitDirectInput(void);
HRESULT hrInitKeyboard(HWND hWnd);
BYTE Scan2Ascii(DWORD scancode);
HRESULT hrReadKeyboard( void );

//-----------------------------------------------------------------------------------
//
// Global Variables
//
//-----------------------------------------------------------------------------------
// Windows Globals
const char				*szWndClass		= "SpacePirates";
const char				*szProgramName	= "Space Pirates";
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
LPDIRECT3DVERTEXBUFFER8	lpVertexBuffer = NULL;
LPDIRECT3DTEXTURE8      g_pTexture[MAX_TEXTURES];
MYVERTEX				g_Vertices[4];
Object3DClass			o3dShip[13];

//-----------------------------------------------------------------------------------
// Direct Sound Objects
//-----------------------------------------------------------------------------------
SoundSystem				SoundEngine;
GAME_SOUNDS				g_GameSounds;

//-----------------------------------------------------------------------------------
// Direct Play Objects
//-----------------------------------------------------------------------------------
IDirectPlay8Peer*       g_pDP = NULL;
IDirectPlay8Address*    g_pDeviceAddress = NULL;
IDirectPlay8Address*    g_pHostAddress = NULL;
DPNHANDLE				g_hConnectAsyncOp = NULL;
DPNID					g_dpnidLocalPlayer = 0;
PLAYER_INFORMATION		PlayerInfo[MAX_PLAYERS];
int						g_iMyPlayerId = 0;
LONG					g_lNumberOfActivePlayers = 0;
BOOL					bHost = 0;

//-----------------------------------------------------------------------------------
// Multi-Threading Variables
//-----------------------------------------------------------------------------------
HANDLE                  g_hConnectCompleteEvent = NULL;
HRESULT					g_hrConnectComplete;
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
ExplosionObject			Explosion[MAX_EXPLOSIONS];
BulletObject			Bullet[MAX_BULLETS];
// Font
LPD3DXFONT		pD3DXFont = NULL;
HFONT			hFont = NULL;
char			szSystemMessage[256];
int				g_iCommandMode = 0;
char			szCommand[256];
DWORD			dwUpdateTime = timeGetTime();
DWORD			dwFrameTimer = timeGetTime();
D3DMATERIAL8	mtrlDefault;
char			szHighestScoreWinner[256];
long			g_lHighestScore = 0;
bool			bFireBullet = 0;
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

