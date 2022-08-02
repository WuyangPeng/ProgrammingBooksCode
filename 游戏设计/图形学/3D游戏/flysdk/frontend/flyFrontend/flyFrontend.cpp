#include "../../lib/Fly3D.h"
#include "resource.h"

ATOM	MyRegisterClass(HINSTANCE hInstance);
BOOL	InitInstance(HINSTANCE, int);

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DlgAbout(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK	DlgVideoModes(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

int OpenFlyFileDialog();
void CommandLine(char *str);

char fly_file_name[256]="";
HCURSOR mousecur=LoadCursor(NULL, IDC_ARROW);
int menuon=0;

HINSTANCE hInst;
HWND hWndMain;

HMENU hMenu=0;
char szTitle[100]="Fly3D";
char szWindowClass[100]="Fly3Dfe";
						 
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if (hPrevInstance)
		return 0;

	hInst=hInstance;

	MSG msg;
	HACCEL hAccelTable;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) 
		return FALSE;

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDR_FLY_ACCEL);

	PostMessage(hWndMain,WM_USER,0,0);

	CommandLine(lpCmdLine);

	while (1) 
		{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) 
			{
			if (GetMessage(&msg, NULL, 0, 0)) 
				{
				if (flyengine)
					if ( (msg.message==WM_CHAR && flyengine->con.mode && msg.wParam!=VK_ESCAPE) || 
						 (msg.message==WM_KEYDOWN && msg.wParam==VK_ESCAPE))
							flyengine->con.key_press(msg.wParam);
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
					{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					}
				}
			else 
				return TRUE;
			}
		
		if (rend && flyengine)
			{
			if (flyengine->step())
				rend->DrawView();
			SetClassLong(hWndMain,GCL_HCURSOR,(long)(flyengine->mouse?mousecur:0));
			}
		}
}

ATOM MyRegisterClass(HINSTANCE hInst)
{
	WNDCLASS wcex;

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon(hInst, (LPCTSTR)IDI_FLY);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDM_FLY;
	wcex.lpszClassName	= szWindowClass;

	return RegisterClass(&wcex);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
   hWndMain = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
      CW_USEDEFAULT, 0, 256, 256, NULL, NULL, hInst, NULL);
   if (!hWndMain)
      return FALSE;

   hMenu=GetMenu(hWndMain);

   ShowWindow(hWndMain, nCmdShow);
   UpdateWindow(hWndMain);

   return TRUE;
}

void WndCommand(int wmId,int wmEvent)
{
	switch (wmId)
	{
	case ID_SAVESCR:
		if (rend)
		{
			static int count=1;

			picture p;
			p.CreatePicture24(screen_sx,screen_sy);

			glPixelTransferf(GL_RED_SCALE,1);
			glPixelTransferf(GL_GREEN_SCALE,1);
			glPixelTransferf(GL_BLUE_SCALE,1);
			glReadPixels(0,0,p.sx,p.sy,GL_RGB,GL_UNSIGNED_BYTE,p.buf[0]);
			glPixelTransferf(GL_RED_SCALE,brightness);
			glPixelTransferf(GL_GREEN_SCALE,brightness);
			glPixelTransferf(GL_BLUE_SCALE,brightness);

			unsigned char *buf=new unsigned char[p.sx*3];
			for( int i=0;i<p.sy/2;i++ )
			{
				memcpy( buf,p.buf[i],p.sx*3 );
				memcpy( p.buf[i],p.buf[p.sy-i-1],p.sx*3 );
				memcpy( p.buf[p.sy-i-1],buf,p.sx*3 );
			}
			delete buf;

			char str[256];
			strcpy(str,flyengine->flydatapath);
			sprintf(&str[strlen(str)],"screen%03i.tga",count);
			p.SaveTGA(str);
			
			sprintf(str,"SAVED 'SCREEN%03i.TGA'",count);
			flyengine->set_status_msg(str);
			count++;
		}
		break;
	case ID_VIDEOMODE:
		DialogBox(hInst,MAKEINTRESOURCE(IDD_VIDEOMODES),0,(DLGPROC)DlgVideoModes);
		break;
	case ID_FULLSCREEN:
		fullscreen=!fullscreen;
		rend->SetFullScreen();
		if (fullscreen)
			SetMenu(hWndMain,0);
		else SetMenu(hWndMain,hMenu);
		break;
	case ID_MENU:
		if (strcmp(flyengine->flyfile,"menu/menu.fly"))
			flyengine->con.command_exec("map menu/menu.fly");
		break;
	case ID_FOG:
		flyengine->fog=!flyengine->fog;
		flyengine->set_status_msg(flyengine->fog?"FOG ON":"FOG OFF");
		break;
	case ID_WIREFRAME:
		flyengine->wireframe=!flyengine->wireframe;
		flyengine->set_status_msg(flyengine->wireframe?"WIRE ON":"WIRE OFF");
		break;
	case ID_NODEONLY:
		flyengine->nodeonly=!flyengine->nodeonly;
		flyengine->set_status_msg(flyengine->nodeonly?"NODEONLY ON":"NODEONLY OFF");
		break;
	case ID_PVS:
		flyengine->pvsoff=!flyengine->pvsoff;
		flyengine->set_status_msg(flyengine->pvsoff?"PVS OFF":"PVS ON");
		break;
	case ID_TEXTUREINTERPOLATION:
		textfilter=!textfilter;
		flyengine->set_status_msg(textfilter?"FILTERING ON":"FILTERING OFF");
		flyengine->close_texture_cache();
		flyengine->init_texture_cache();
		break;
	case ID_STATUS:
		flyengine->status=!flyengine->status;
		break;
	case ID_CLEARBKGND:
		flyengine->clearbk=!flyengine->clearbk;
		flyengine->set_status_msg(flyengine->clearbk?"CLEAR BKGND ON":"CLEAR BKGND OFF");
		break;
	case ID_MULTITEXTURE:
		if (ntextureunits>1)
			{
			flyengine->multitexture=!flyengine->multitexture;
			flyengine->set_status_msg(flyengine->multitexture?"MULTITEXT ON":"MULTITEXT OFF");
			}
		break;
	case ID_MAPMODE:
		flyengine->mapmode=(flyengine->mapmode+1)%MAPPING_OPTIONS;
		flyengine->set_status_msg("MAPMODE %i",flyengine->mapmode);
		break;
	case ID_MIPMAP:
		mipmap=!mipmap;
		flyengine->set_status_msg(mipmap?"MIPMAP ON":"MIPMAP OFF");
		flyengine->close_texture_cache();
		flyengine->init_texture_cache();
		break;
	case ID_MUTE:
		flyengine->mute=!flyengine->mute;
		flyengine->set_status_msg(flyengine->mute?"MUTE ON":"MUTE OFF");
		break;
	case ID_ABOUT:
		DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUTBOX),0,(DLGPROC)DlgAbout);
		break;
	case ID_FILE_OPEN:
		flyengine->close_multiplayer();
		flyengine->close_fly_file();
		InvalidateRect(hWndMain,0,0);
		if (OpenFlyFileDialog())
		{
			char str[256];
			strcpy(str,flyengine->flysdkpath);
			strcat(str,"data\\");
			strlwr(fly_file_name);
			if (strncmp(fly_file_name,str,strlen(str))==0)
				flyengine->open_fly_file(&fly_file_name[strlen(str)]);
			if (flyengine->flyfile[0]==0)
				{
				strcpy(str,"Could not load file:\n");
				strcat(str,fly_file_name);
				MessageBox(hWndMain,str,"Fly3D",MB_OK|MB_ICONEXCLAMATION);
				}
		}
		InvalidateRect(hWndMain,0,0);
		flyengine->set_status_msg("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
		break;
	case ID_MULTIPLAYER:
		flyengine->close_multiplayer();
		flyengine->close_fly_file();
		InvalidateRect(hWndMain,0,0);
		flyengine->join_multiplayer();
		InvalidateRect(hWndMain,0,0);
		flyengine->set_status_msg("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
		break;
	case ID_FILE_CLOSE:
		flyengine->close_multiplayer();
		flyengine->close_fly_file();
		InvalidateRect(hWndMain,0,0);
		flyengine->set_status_msg("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
		break;
	case ID_EXIT:
		DestroyWindow(hWndMain);
		break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static HDC hdc;
	static RECT rect;

	switch (message) 
	{
		case WM_USER:
			{
			init_engine(hWnd,hInst,FLYAPPID_FLY);
			init_directx();
			init_render(FLY_RENDER_OPENGL);

			if (fly_file_name[0])
			{
				flyengine->open_fly_file(fly_file_name);
				if (flyengine->flyfile[0]==0)
					{
					char str[256];
					strcpy(str,"Could not load file:\n");
					strcat(str,fly_file_name);
					MessageBox(hWndMain,str,"Fly3D",MB_OK|MB_ICONEXCLAMATION);
					}
			}

			if (fullscreen)
			{
				fullscreen=0;
				PostMessage(hWnd,WM_COMMAND,ID_FULLSCREEN,0);
			}

			InvalidateRect(hWndMain,0,0);
			}
			break;
		case WM_COMMAND:
			WndCommand(LOWORD(wParam),HIWORD(wParam));
			break;
		case WM_DESTROY:
			if (flyengine)
				{
				flyengine->close_multiplayer();
				flyengine->close_fly_file();
				}
			free_engine();
			free_render();
			free_directx();
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			if (rend)
				rend->ResizeView(LOWORD(lParam),HIWORD(lParam));
			break;
		case WM_ACTIVATE:
			if (flyengine)
				if (LOWORD(wParam)==WA_INACTIVE || flyengine->con.mode)
					flyengine->noinput=1;
				else flyengine->noinput=0;
			break;
		case WM_SETCURSOR:
			if (menuon==1)
				SetCursor(mousecur);
			else if (flyengine)
					SetCursor(flyengine->mouse?mousecur:0);
			break;
		case WM_ENTERMENULOOP:
			InvalidateRect(hWnd,0,0);
			SetCursor(mousecur);
			flyengine->noinput=1;
			menuon=1;
			break;
		case WM_EXITMENULOOP:
			if (flyengine->con.mode==0)
				flyengine->noinput=0;
			menuon=0;
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_ERASEBKGND:
			{
			if (rend==0 || flyengine==0 || flyengine->bsp==0)
				{
				RECT rect;
				GetClientRect(hWnd,&rect);
				FillRect((HDC)wParam,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
				}
			return 1;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK DlgAbout(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case WM_CLOSE:
		EndDialog(hWnd,IDCANCEL);
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			EndDialog(hWnd,IDOK);
			break;
		}
		break;
	}
	return 0;
}

LRESULT CALLBACK DlgVideoModes(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case WM_INITDIALOG:
		{
			int i;
			char str[256];
			for( i=0;i<numvideomodes;i++ )
			{
				if (videomodes[i].dmDisplayFrequency!=0)
					sprintf(str,"%ix%i %i bits/pixel %i hz",
						videomodes[i].dmPelsWidth,videomodes[i].dmPelsHeight,videomodes[i].dmBitsPerPel,videomodes[i].dmDisplayFrequency);
				else 
					sprintf(str,"%ix%i %i bits/pixel",
						videomodes[i].dmPelsWidth,videomodes[i].dmPelsHeight,videomodes[i].dmBitsPerPel);
				SendDlgItemMessage(hWnd,IDC_VIDEOMODELIST,LB_ADDSTRING,0,(LPARAM)str);
			}
			SendDlgItemMessage(hWnd,IDC_VIDEOMODELIST,LB_SETCURSEL,selvideomode,0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd,IDCANCEL);
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDCANCEL:
			EndDialog(hWnd,IDCANCEL);
			break;
		case IDOK:
			selvideomode=SendDlgItemMessage(hWnd,IDC_VIDEOMODELIST,LB_GETCURSEL,0,0);
			EndDialog(hWnd,IDOK);
			break;
		}
		break;
	}
	return 0;
}

void CommandLine(char *str)
{
	char *c1=str,*c2;
	while(c1)
	{
		c2=strchr(c1,' ');
		if (c2) 
			*c2=0;
		if (c1[0]!='/' && c1[0]!='-')
			strcpy(fly_file_name,c1);
		else
		if (!stricmp(&c1[1],"fullscreen"))
			fullscreen=1;
		if (c2)
			c1=c2+1;
		else c1=0;
	}
}

int OpenFlyFileDialog()
{
	OPENFILENAME ofn;

	memset(&ofn,0,sizeof(OPENFILENAME));
	char filename[256]="";

	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWndMain;
	ofn.hInstance=hInst;
	ofn.lpstrFilter="Fly scene (*.fly)\0*.fly\0";
	ofn.lpstrDefExt="fly";
	ofn.lpstrFile=filename;
	ofn.nMaxFile=255;
	ofn.lpstrTitle="Open Fly3D Scene";
	ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		strcpy(fly_file_name,filename);
		if (filename[0])
			return 1;
	}
	return 0;
}
