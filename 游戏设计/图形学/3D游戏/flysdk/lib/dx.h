#ifndef STRICT 
#define STRICT
#endif

#define DIRECTINPUT_VERSION 0x0300

#include <windows.h>
#include <stdio.h>
#include "dinput.h"
#include "dsound.h"
#include "dplay.h"
#include "dplay.h"
#include "dplobby.h"

int WaveLoadFile(char *, UINT *, DWORD *, WAVEFORMATEX **, BYTE **);
int WaveLoadFileB(LONG, HPSTR, UINT *, DWORD *, WAVEFORMATEX **, BYTE **);

#define FLYMP_GUARANTEED 0x80000000

#define FLYMP_BROWSETIME 2000
#define FLYMP_PLAYERDATASIZE 40
#define FLYMP_MAXPLAYERS 16
#define FLYMP_MAXSERVICES 16
#define FLYMP_MAXGAMES 16

#define FLYMP_MSG_JOIN 9171|FLYMP_GUARANTEED
#define FLYMP_MSG_QUIT 9172|FLYMP_GUARANTEED
#define FLYMP_MSG_FLYFILE 9173|FLYMP_GUARANTEED

#define FLYMP_NOMP 0
#define FLYMP_CLIENT 1
#define FLYMP_SERVER 2

class FLY_API mp_msg 
{
public:
	DWORD type;
	DWORD from;
	char data[500];
};

class FLY_API mp_games
{
public:
	int num;
	char name[FLYMP_MAXGAMES][128];
	int num_players[FLYMP_MAXGAMES];
	GUID guid[FLYMP_MAXGAMES];
	mp_games() { num=0; };
};

class FLY_API player_data
{
	public:

		DWORD type,dpid;
		char name[32];	
		void *data;

	player_data() { memset(this,0,sizeof(player_data)); };
};

class FLY_API directX
{
		// Direct Input
		LPDIRECTINPUT           lpDI;
		LPDIRECTINPUTDEVICE     lpKeyboard;
		LPDIRECTINPUTDEVICE     lpMouse;

		// Direct Sound
		LPDIRECTSOUND			lpDSound;
		LPDIRECTSOUNDBUFFER		lpDS3dPrimBuf;
		LPDIRECTSOUND3DLISTENER lpDS3dListener;

		// Direct Play
		GUID				guidInstance;
		LPDPSESSIONDESC2	lpSD;
		LPDIRECTPLAY3A		lpDP;
		LPDIRECTPLAYLOBBY2A	lpDPL;

	void Init();
	void Release();

public:

	directX()
	{ 
		lpDI=0;
		lpKeyboard=0;
		lpMouse=0;

		lpDSound=0;
		lpDS3dPrimBuf=0;
		lpDS3dListener=0;

		lpSD=0;
		lpDP=0;
		lpDPL=0;

		Init();
	};
	virtual ~directX()
	{ 
		Release(); 
	};

	int mpmode;
	int nplayers;
	player_data players[FLYMP_MAXPLAYERS];

	unsigned char diks[256];
	DIMOUSESTATE dims;

	void get_input();

	int load_wav_file(LONG cchBuffer,HPSTR pchBuffer,LPDIRECTSOUNDBUFFER *buf,LPDIRECTSOUND3DBUFFER *buf3d);
	void set_listener(float *pos,float *vel,float *Y,float *Z);
	LPDIRECTSOUNDBUFFER clone_sound(LPDIRECTSOUNDBUFFER buf);
	void set_master_volume(int volume);

	int init_multiplayer(char *netaddress=0);
	void free_multiplayer();

	mp_games *enum_games(LPGUID app_guid);
	int join_game(LPGUID game_guid,char *player_name);
	int create_game(LPGUID app_guid,char *game_name);
	char *get_player_address(DWORD dpid);

	void send_message(mp_msg *msg,int len,DWORD dpid=0);
	int get_num_messages();
	mp_msg *get_message(DWORD *size);

	int add_player(char *name,DWORD dpid,void *data);
	void *remove_player(int i);
};

extern FLY_API directX *directx;
FLY_API void init_directx();
FLY_API void free_directx();
