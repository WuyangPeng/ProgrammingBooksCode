#include "../Fly3D.h"

FLY_API directX *directx=0;

FLY_API void init_directx()
{
	free_directx();
	directx=new directX();
}

FLY_API void free_directx()
{
	if (directx)
		delete directx;
	directx=0;
}

void directX::send_message(mp_msg *data,int len,DWORD dpid)
{
	if (lpDP)
		if (data->type&FLYMP_GUARANTEED)
			if (dpid==0)
				lpDP->Send(players[0].dpid,DPID_ALLPLAYERS,DPSEND_GUARANTEED,data,len);
			else lpDP->Send(players[0].dpid,dpid,DPSEND_GUARANTEED,data,len);
		else
			if (dpid==0)
				lpDP->Send(players[0].dpid,DPID_ALLPLAYERS,0,data,len);
			else lpDP->Send(players[0].dpid,dpid,0,data,len);
}

BOOL FAR PASCAL EnumAddressCallback(
	REFGUID guidDataType,DWORD dwDataSize,
	LPCVOID lpData,LPVOID lpContext)
{
	if (guidDataType==DPAID_INet)
	{
		if (((char *)lpContext)[0]!=0)
			strcat((char *)lpContext," , ");
		strcat((char *)lpContext,(char *)lpData);
	}
	return 1;
}

char *directX::get_player_address(DWORD dpid)
{
	static char buf[1024],str[256];
	str[0]=0;
	if (lpDP)
	{
		DWORD size=1024;
		lpDP->GetPlayerAddress(dpid,buf,&size);
		lpDPL->EnumAddress(EnumAddressCallback,buf,size,str);
	}
	return str;
}

int directX::get_num_messages()
{
	DWORD count=0;
	if (lpDP)
		lpDP->GetMessageCount(players[0].dpid,&count);	
	return count;
}

mp_msg *directX::get_message(DWORD *size)
{
	if (lpDP==0)
		return 0;
	static mp_msg msg;
	DWORD idfrom;
	DWORD idto=players[0].dpid;
	if (DP_OK==lpDP->Receive(&idfrom,&idto,DPRECEIVE_TOPLAYER,&msg.type,size))
		return &msg;
	return 0;
}

int directX::init_multiplayer(char *netaddress)
{
	DPCOMPOUNDADDRESSELEMENT addressElements[3];
	DWORD dwElementCount=0;
	char address[512];
	DWORD size=512;

	free_multiplayer();
	CoCreateInstance(CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER,
          IID_IDirectPlay3A,(LPVOID*)&lpDP);
	if (lpDP)
		{
		CoCreateInstance(CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER,
			IID_IDirectPlayLobby2A, (LPVOID *) &lpDPL);

		addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
		addressElements[dwElementCount].dwDataSize = sizeof(GUID);
		addressElements[dwElementCount].lpData = (LPVOID) &DPSPGUID_TCPIP;
		dwElementCount++;
		
		if (netaddress)
			{
			addressElements[dwElementCount].guidDataType = DPAID_INet;
			addressElements[dwElementCount].dwDataSize = strlen(netaddress)+1;
			addressElements[dwElementCount].lpData = netaddress;
			dwElementCount++;
			}

		lpDPL->CreateCompoundAddress(
			addressElements, dwElementCount,
			address, &size);

		if (DP_OK==lpDP->InitializeConnection(address,0))
			return 1;
		}
	free_multiplayer();
	return 0;
}

void directX::free_multiplayer()
{
	if (lpDPL)
		lpDPL->Release();
	if (lpDP)
		lpDP->Release();
	if (lpSD)
		delete lpSD;
	lpSD=0;
	lpDP=0;
	lpDPL=0;
	nplayers=0;
	mpmode=FLYMP_NOMP;
}

BOOL FAR PASCAL EnumPlayersCallback(
	DPID dpId,DWORD dwPlayerType,
	LPCDPNAME lpName,DWORD dwFlags,	LPVOID lpContext)
{
	directX *dx=(directX *)lpContext;

	if (dpId!=DPID_SERVERPLAYER && dpId!=dx->players[0].dpid)
	{
		strcpy(dx->players[dx->nplayers].name,lpName->lpszShortNameA);
		dx->players[dx->nplayers].dpid=dpId;
		dx->nplayers++;
	}
	return 1;
}

int directX::join_game(LPGUID game_guid,char *player_name)
{
	if (lpDP==0) return 0;

	mpmode=0;

	lpSD=new DPSESSIONDESC2;
	memset(lpSD,0,sizeof(DPSESSIONDESC2));
	
	lpSD->guidInstance=guidInstance=*game_guid;
	lpSD->dwSize=sizeof(DPSESSIONDESC2);
	if (DP_OK!=lpDP->Open(lpSD,DPOPEN_JOIN))
		return 0;

	nplayers=1;
	strcpy(players[0].name,player_name);
	players[0].data=0;

	DPNAME pn;
	pn.dwFlags=0;
	pn.dwSize=sizeof(DPNAME);
	pn.lpszShortNameA=players[0].name;
	pn.lpszLongNameA=players[0].name;
	lpDP->CreatePlayer(&players[0].dpid,&pn,0,(void *)&players[0],sizeof(player_data),0);

	lpDP->EnumPlayers(0,EnumPlayersCallback,this,DPENUMPLAYERS_ALL);

	mpmode=1;

	return players[0].dpid;
}

int directX::create_game(LPGUID app_guid,char *game_name)
{
	if (lpDP==0) return 0;

	lpSD=new DPSESSIONDESC2;
	memset(lpSD,0,sizeof(DPSESSIONDESC2));
	
	CoCreateGuid(&guidInstance);
	lpSD->guidInstance=guidInstance;

	lpSD->dwSize=sizeof(DPSESSIONDESC2);
	lpSD->dwFlags=
		DPSESSION_CLIENTSERVER|
		DPSESSION_KEEPALIVE|
		DPSESSION_NODATAMESSAGES;
	lpSD->guidApplication=*app_guid;
	lpSD->dwMaxPlayers=FLYMP_MAXPLAYERS;
	lpSD->dwCurrentPlayers=0;
	lpSD->lpszSessionNameA=game_name;

	if (DP_OK!=lpDP->Open(lpSD,DPOPEN_CREATE))
		return 0;

	DPNAME pn;
	pn.dwFlags=0;
	pn.dwSize=sizeof(DPNAME);
	nplayers=1;
	players[0].data=0;
	strcpy(players[0].name,"server");
	pn.lpszShortNameA="server";
	pn.lpszLongNameA="server";
	lpDP->CreatePlayer(&players[0].dpid,&pn,0,0,0,DPPLAYER_SERVERPLAYER);
	mpmode=2;

	return 1;
}

BOOL FAR PASCAL EnumSessionsCallback(
	LPCDPSESSIONDESC2 lpThisSD,	LPDWORD lpdwTimeOut,
	DWORD dwFlags,LPVOID lpContext)
{
	if (lpThisSD==0) return 0;
	mp_games *g=(mp_games *)lpContext;
	strcpy(g->name[g->num],lpThisSD->lpszSessionNameA);
	g->guid[g->num]=lpThisSD->guidInstance;
	g->num_players[g->num]=lpThisSD->dwCurrentPlayers-1;
	g->num++;
	return 1;
}

mp_games *directX::enum_games(LPGUID app_guid)
{
	if (lpDP==0) return 0;

	static mp_games g;
	g.num=0;

	DPSESSIONDESC2 sd;
	memset(&sd,0,sizeof(DPSESSIONDESC2));
	sd.dwSize=sizeof(DPSESSIONDESC2);
	sd.guidApplication=*app_guid;
	lpDP->EnumSessions(&sd,FLYMP_BROWSETIME,EnumSessionsCallback,&g,DPENUMSESSIONS_ALL);

	return &g;
}

void directX::Init()
{
    HRESULT hr;
	CoInitialize(0);
    hr = DirectInputCreate(hFlyInst, DIRECTINPUT_VERSION, &lpDI, NULL);
	if (lpDI!=NULL)
	{
    hr = lpDI->CreateDevice(GUID_SysKeyboard, &lpKeyboard, NULL);
	if (lpKeyboard)
		{
		hr = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
		hr = lpKeyboard->SetCooperativeLevel(hFlyWnd, DSSCL_NORMAL);//DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
		}

    hr = lpDI->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
	if (lpMouse)
		{
		hr = lpMouse->SetDataFormat(&c_dfDIMouse);
		hr = lpMouse->SetCooperativeLevel(hFlyWnd, DSSCL_NORMAL);//DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
		}
	}

	if (lpKeyboard) lpKeyboard->Acquire();
	if (lpMouse) lpMouse->Acquire();

	hr = DirectSoundCreate(NULL,&lpDSound,NULL);
	if (lpDSound!=NULL)
	{
	lpDSound->SetCooperativeLevel(hFlyWnd,DSSCL_NORMAL);
	
	DSBUFFERDESC desc;
	memset(&desc,0,sizeof(DSBUFFERDESC));
	desc.dwSize=sizeof(DSBUFFERDESC);
	desc.dwFlags=DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME|DSBCAPS_PRIMARYBUFFER;
	lpDSound->CreateSoundBuffer(&desc,&lpDS3dPrimBuf,0);

	WAVEFORMATEX format;
	format.wFormatTag=WAVE_FORMAT_PCM;
	format.nChannels=1;
	format.nSamplesPerSec=22050;
	format.wBitsPerSample=16;
	format.nBlockAlign=format.nChannels*format.wBitsPerSample/8;
	format.nAvgBytesPerSec=format.nSamplesPerSec*format.nBlockAlign;
	format.cbSize=0;
	lpDS3dPrimBuf->SetFormat(&format);

	lpDS3dPrimBuf->QueryInterface(IID_IDirectSound3DListener, (void **)(&lpDS3dListener));

	lpDS3dListener->SetDistanceFactor(0.1f,DS3D_IMMEDIATE);
	lpDS3dListener->SetDopplerFactor(0.1f,DS3D_IMMEDIATE);
	lpDS3dListener->SetRolloffFactor(0.1f,DS3D_IMMEDIATE);
	}
}

void directX::Release()
{
	free_multiplayer();
    if (lpKeyboard) 
		{
        lpKeyboard->Unacquire();
        lpKeyboard->Release();
        lpKeyboard = NULL;
		}
    if (lpMouse) 
		{
        lpMouse->Unacquire();
        lpMouse->Release();
        lpMouse = NULL;
		}
    if (lpDI) 
		{
        lpDI->Release();
        lpDI = NULL;
		}
	if (lpDSound)
		{
		lpDS3dListener->Release();
		lpDS3dPrimBuf->Release();
        lpDSound->Release();
        lpDSound = NULL;
		}
	CoUninitialize();
}

int directX::load_wav_file(LONG cchBuffer, HPSTR pchBuffer, LPDIRECTSOUNDBUFFER *buf, LPDIRECTSOUND3DBUFFER *buf3d)
{
	if (lpDSound==0)
		return 0;

	UINT Size;
	DWORD Samples;
	WAVEFORMATEX *Info;
	BYTE *Data;
	DSBUFFERDESC desc;

	if (WaveLoadFileB(cchBuffer,pchBuffer,&Size,&Samples,&Info,&Data))
		return 0;
	desc.dwSize=sizeof(DSBUFFERDESC);
	desc.dwFlags=DSBCAPS_STATIC|DSBCAPS_CTRLVOLUME;
	if (buf3d)
		desc.dwFlags|=DSBCAPS_CTRL3D;//|DSBCAPS_MUTE3DATMAXDISTANCE;
	desc.dwBufferBytes=Size;
    desc.lpwfxFormat=Info;
	desc.dwReserved=0;

	lpDSound->CreateSoundBuffer(&desc,buf,0);
	if (*buf)
		{
		LPVOID blk1,blk2;
		DWORD size1,size2;

		(*buf)->QueryInterface(IID_IDirectSound3DBuffer,(void **)(buf3d));

		(*buf)->Lock(0,Size,&blk1,&size1,&blk2,&size2,0);
		CopyMemory(blk1,Data,size1);
		if (Size>size1)
			CopyMemory(blk2,Data+size1,size2);
		(*buf)->Unlock(blk1,size1,blk2,size2);
		}

	Size=Size*1000/Info->nAvgBytesPerSec;
	if (Info)
		GlobalFree(Info);
	if (Data)
		GlobalFree(Data);
	Info=0;
	Data=0;
	return Size;
}

void directX::get_input()
{
	if (lpDI==0) return;

	HRESULT hr;

	if (lpKeyboard) 
	{
		hr = lpKeyboard->GetDeviceState(sizeof(diks), diks);
		if (hr == DIERR_INPUTLOST) 
			{
			hr = lpKeyboard->Acquire();
			if (SUCCEEDED(hr)) 
				hr = lpKeyboard->GetDeviceState(sizeof(diks), diks);
			}
	}
	if (lpMouse) 
	{
		hr=lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &dims);
		if (hr == DIERR_INPUTLOST) 
			{
			hr = lpMouse->Acquire();
			if (SUCCEEDED(hr)) 
				hr = lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &dims);
			}
	}
}

void directX::set_listener(float *pos,float *vel,float *Y,float *Z)
{
	if (lpDS3dListener)
	{
		if (pos)
		lpDS3dListener->SetPosition(
			pos[0],pos[1],pos[2],
			DS3D_DEFERRED);
		if (vel)
		lpDS3dListener->SetVelocity(
			vel[0],vel[1],vel[2],
			DS3D_DEFERRED);
		if (Y && Z)
		lpDS3dListener->SetOrientation(
			Z[0],Z[1],Z[2],
			Y[0],Y[1],Y[2],
			DS3D_DEFERRED);
		lpDS3dListener->CommitDeferredSettings();
	}
}

LPDIRECTSOUNDBUFFER directX::clone_sound(LPDIRECTSOUNDBUFFER buf)
{
	if (lpDSound==0) return 0;
	static LPDIRECTSOUNDBUFFER dup_buf;
	lpDSound->DuplicateSoundBuffer(buf,&dup_buf);
	return dup_buf;
}

int directX::add_player(char *name,DWORD dpid,void *data)
{
	if (nplayers<FLYMP_MAXPLAYERS)
	{
		strcpy(players[nplayers].name,name);
		players[nplayers].dpid=dpid;
		players[nplayers].data=data;
		return nplayers++;
	}
	else return -1;
}

void *directX::remove_player(int i)
{
	if (i<nplayers)
	{
		void *data=players[i].data;
		memcpy(&players[i],&players[i+1],sizeof(player_data)*(nplayers-i-1));
		nplayers--;
		return data;
	}
	else return 0;
}

void directX::set_master_volume(int volume)
{
	if (lpDS3dPrimBuf)
		lpDS3dPrimBuf->SetVolume(volume);
}
