#include "../Fly3D.h"
#include "flyMultiplayer.h"

FLY_API GUID
FLYGUID = { /* e29ac960-09f8-11d2-9262-000021799871 */
    0xe29ac960,
    0x09f8,
    0x11d2,
    {0x92, 0x62, 0x00, 0x00, 0x21, 0x79, 0x98, 0x71}
  };

FLY_API BOOL FAR PASCAL MultiplayerProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	static mp_games *g=0;
	switch (uiMsg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_SEARCH:
			{
			char ip[256];
			GetDlgItemText(hWnd,IDC_IP,ip,255);
			SendDlgItemMessage(hWnd,IDC_GAMES,LB_RESETCONTENT,0,0);
			directx->init_multiplayer(ip);
			g=directx->enum_games(&FLYGUID);
			if (g)
				{
				int i,j;
				char str[256];
				for( i=0;i<g->num;i++ )
					{
					sprintf(str,"%s (%i)",g->name[i],g->num_players[i]);
					j=SendDlgItemMessage(hWnd,IDC_GAMES,LB_ADDSTRING,0,(DWORD)str);
					SendDlgItemMessage(hWnd,IDC_GAMES,LB_SETITEMDATA,j,(DWORD)i);
					}
				if (g->num)
					{
					SendDlgItemMessage(hWnd,IDC_GAMES,LB_SETCURSEL,0,0);
					EnableWindow(GetDlgItem(hWnd,IDOK),1);
					SetFocus(GetDlgItem(hWnd,IDOK));
					}
				else EnableWindow(GetDlgItem(hWnd,IDOK),0);
				}
			}
			break;
		case IDOK:
			{
			char playername[64];
			GetDlgItemText(hWnd,IDC_PLAYERNAME,playername,64);
			if (strlen(playername)==0)
				{
				MessageBox(hWnd,"Please enter a player name.","Fly3D",MB_OK);
				break;
				}
			int j=SendDlgItemMessage(hWnd,IDC_GAMES,LB_GETCURSEL,0,0);
			if (j==-1)
				{
				MessageBox(hWnd,"Please select a game to join.","Fly3D",MB_OK);
				break;
				}
			j=SendDlgItemMessage(hWnd,IDC_GAMES,LB_GETITEMDATA,j,0);
			j=directx->join_game(&g->guid[j],playername);
			EndDialog(hWnd,IDOK);
			}
			break;
		case IDCANCEL:
			directx->free_multiplayer();
			EndDialog(hWnd,IDCANCEL);
			break;
		}
		break;

    case WM_INITDIALOG:
		SetFocus(GetDlgItem(hWnd,IDC_PLAYERNAME));
		EnableWindow(GetDlgItem(hWnd,IDOK),0);
		directx->init_multiplayer();
		break;
	}
	return FALSE;
} 

void flyEngine::close_multiplayer()
{
	int i;
	for( i=1;i<directx->nplayers;i++ )
	{
		bsp_object *obj=(bsp_object *)directx->players[i].data;
		obj->life=-1;
	}
	directx->free_multiplayer();
}

int flyEngine::join_multiplayer()
{
	close_multiplayer();
	close_fly_file();
	if (IDOK==DialogBox(hFlyInst,MAKEINTRESOURCE(IDD_MULTIPLAYER),hFlyWnd,(DLGPROC)MultiplayerProc))
	{
		int maxtime=5000;

		while(maxtime>0)
		{
		maxtime-=500;
		Sleep(500);
		check_multiplayer();
		if (flyfile[0]!=0) break;
		}
		if (flyfile[0]==0)
			close_multiplayer();
		directx->players[0].data=player;
	}
	return 0;
}

void flyEngine::check_multiplayer()
{
	int i,j,num,from;
	mp_msg *msg;
	DWORD size;

	num=directx->get_num_messages();
	for( i=0;i<num;i++ )
	{
		size=500;
		msg=directx->get_message(&size);
		if (msg)
		{
		for( from=0;from<directx->nplayers;from++ )
			if (directx->players[from].dpid==msg->from)
				break;
		if (from==directx->nplayers)
			from=-1;
		switch(msg->type)
			{
			case DPSYS_CREATEPLAYERORGROUP:
				{
					DPMSG_CREATEPLAYERORGROUP *info=(DPMSG_CREATEPLAYERORGROUP *)&msg->type;

					mp_msg msgflyfile;
					strcpy(msgflyfile.data,flyfile);
					msgflyfile.type=FLYMP_MSG_FLYFILE;
					msgflyfile.from=DPID_SERVERPLAYER;
					directx->send_message(&msgflyfile,strlen(flyfilename)+9,info->dpId);
					
					player_data pd;
					pd.type=FLYMP_MSG_JOIN;
					pd.dpid=info->dpId;
					strcpy(pd.name,info->dpnName.lpszShortNameA);
					dll.send_message(FLYM_MPMESSAGE,-1,&pd);

					directx->players[directx->nplayers-1].type=FLYMP_MSG_JOIN;
					for( i=1;i<directx->nplayers-1;i++ )
						{
						directx->players[i].type=FLYMP_MSG_JOIN;
						directx->send_message((mp_msg *)&directx->players[i],FLYMP_PLAYERDATASIZE,info->dpId);
						directx->send_message((mp_msg *)&directx->players[directx->nplayers-1],FLYMP_PLAYERDATASIZE,directx->players[i].dpid);
						}
				}
				break;
			case DPSYS_DESTROYPLAYERORGROUP:
				{
					DPMSG_DESTROYPLAYERORGROUP *info=(DPMSG_DESTROYPLAYERORGROUP *)&msg->type;
					for( j=0;j<directx->nplayers;j++ )
						if (directx->players[j].dpid==info->dpId)
							break;
					if (j<directx->nplayers)
						{
						directx->players[j].type=FLYMP_MSG_QUIT;
						directx->send_message((mp_msg *)&directx->players[j],FLYMP_PLAYERDATASIZE);
						dll.send_message(FLYM_MPMESSAGE,j,&directx->players[j]);
						}
				}
				break;
			case DPSYS_SESSIONLOST:
				close_multiplayer();
				return;
			case FLYMP_MSG_FLYFILE:
				open_fly_file(msg->data);
				break;
			default:
				dll.send_message(FLYM_MPMESSAGE,from,msg);
				if (directx->mpmode==FLYMP_SERVER)
					directx->send_message(msg,size);
			}
		}
	}
}
