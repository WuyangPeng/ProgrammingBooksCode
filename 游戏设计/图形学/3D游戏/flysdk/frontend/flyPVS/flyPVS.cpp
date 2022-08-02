#include "../../lib/Fly3D.h"
#include "pvsengine.h"
#include "opengl.h"
#include "resource.h"
#include "time.h"

char *szAppName="flyPVS";
int savelog=0;

HDC hdc=0;
HINSTANCE hInstance;
HWND hWndMain;

int sample_count=0,
	cur_side=0,
	cur=-1,
	fail_nodes=0,
	curcount=0;
time_t t1,t2;
short **face_nodes;
char file[256];
char bsp_file_name[256]="";

float VOLUME_FACTOR=1000000.0f;

void DoFrame()
{
	vector v;
	float vol;
	if (curcount==0)
	{
		cur++;
		if (cur>=flyengine->nleaf)
			DestroyWindow(hWndMain);
		else
		if (((pvsEngine *)flyengine)->get_node_random_point(cur,v))
			{
			static_mesh *so=(static_mesh *)flyengine->leaf[cur]->elem;
			v=so->objmesh->bbox.max-so->objmesh->bbox.min;
			vol=v.x*v.y*v.z;
			curcount=(int)(vol/VOLUME_FACTOR)+1;
			}
		else
			fail_nodes++;
	}
	else
	{
		if (((pvsEngine *)flyengine)->get_node_random_point(cur,v))
			{
			((pvsEngine *)flyengine)->sample_node(flyengine->leaf[cur],v);
			sample_count++;
			}
		curcount--;
	}
}

LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG lRet = 1;
	static PAINTSTRUCT ps;
	static RECT rect;

	switch (uMsg) 
	{
	case WM_KEYDOWN:
		if (wParam==VK_LEFT)
			cur_side=(cur_side==0?5:cur_side-1);
		else 
		if (wParam==VK_RIGHT)
			cur_side=((cur_side+1)%6);
		break;
	case WM_CREATE:
		hdc=GetDC(hWnd);
		if (hdc)
			CreateView(hdc);
		InitView();
		SetWindowPos(hWnd,HWND_TOP,0,0,screen_sx,screen_sy,SWP_SHOWWINDOW);
		break;

	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		ResizeView(rect.right,rect.bottom);
		break;

	case WM_ERASEBKGND:
		return 1;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		DeleteView();
		if (hdc)
			ReleaseDC(hWnd,hdc);
		
		((pvsEngine *)flyengine)->save();

		if(face_nodes)
			{
			for(int i=0;i<flyengine->nfaces;i++)
				delete face_nodes[i];
			delete face_nodes;
			}
		PostQuitMessage(0);
		break;

	default:
		lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
		break;
	}

	return lRet;
}

void MyGetProfile(LPTSTR section, LPTSTR key, LPBYTE lpData, DWORD cbData)
{
	HKEY key1,key2,key3,key4;

	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_READ,&key1))
	{
		if (ERROR_SUCCESS==RegOpenKeyEx(key1,"Paralelo",0,KEY_READ,&key2))
		{
			if (ERROR_SUCCESS==RegOpenKeyEx(key2,"Fly3D",0,KEY_READ,&key3))
			{
				if (ERROR_SUCCESS==RegOpenKeyEx(key3,section,0,KEY_READ,&key4))
				{
					RegQueryValueEx(key4, key, 0, 0, lpData, &cbData);
					RegCloseKey(key4);
				}
				RegCloseKey(key3);
			}
			RegCloseKey(key2);
		}
		RegCloseKey(key1);
	}
}

void MyWriteProfile(LPTSTR section, LPCTSTR key, DWORD dwType, CONST BYTE *lpData, DWORD cbData)
{
	HKEY key1,key2,key3,key4;
	DWORD d;

	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_READ,&key1))
	{
		if (ERROR_SUCCESS==RegCreateKeyEx(key1,"Paralelo",0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key2,&d))
		{
			if (ERROR_SUCCESS==RegCreateKeyEx(key2,"Fly3D",0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key3,&d))
			{
				if (ERROR_SUCCESS==RegCreateKeyEx(key3, section,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key4,&d))
				{
					RegSetValueEx(key4, key, 0, dwType, lpData, cbData);
					RegCloseKey(key4);
				}
				RegCloseKey(key3);
			}
			RegCloseKey(key2);
		}
		RegCloseKey(key1);
	}
}

int OpenBspFileDialog(HWND hWnd,char *file)
{
	OPENFILENAME ofn;

	memset(&ofn,0,sizeof(OPENFILENAME));
	char filename[256]="";
	strcpy(filename,file);

	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWnd;
	ofn.hInstance=hInstance;
	ofn.lpstrFilter="bsp fly file (*.bsp)\0*.bsp\0";
	ofn.lpstrDefExt="bsp";
	ofn.lpstrFile=filename;
	ofn.nMaxFile=255;
	ofn.lpstrTitle="Open Fly Scene";
	ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	
	if (GetOpenFileName(&ofn))
	{
		strcpy(file,filename);
		if (filename[0])
			return 1;
	}
	return 0;
}

BOOL FAR PASCAL flypvsProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_INITDIALOG:
		{
		MyGetProfile("viewbsp","filename", (unsigned char *)&bsp_file_name, 256);
		SetWindowText(GetDlgItem(hWnd,IDC_BSPFILE),bsp_file_name);
		if (bsp_file_name[0]==0)
			EnableWindow(GetDlgItem(hWnd,IDOK),0);
		char str[256];
		double d=pow(VOLUME_FACTOR/1000,1.0/3.0);
		sprintf(str,"%.2lf",d);
		SetDlgItemText(hWnd,IDC_SAMPLESVOLUME,str);
		if (screen_sx==128)
			SendDlgItemMessage(hWnd,IDC_SIZE128,BM_SETCHECK,1,0);
		else
		if (screen_sx==256)
			SendDlgItemMessage(hWnd,IDC_SIZE256,BM_SETCHECK,1,0);
		else SendDlgItemMessage(hWnd,IDC_SIZE64,BM_SETCHECK,1,0);
		CheckDlgButton(hWnd,IDC_SAVETXT,savelog);
		}
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BROWSE:
			if (OpenBspFileDialog(hWnd,bsp_file_name))
				if (bsp_file_name[0])
				{
					EnableWindow(GetDlgItem(hWnd,IDOK),1);
					SetDlgItemText(hWnd,IDC_BSPFILE,bsp_file_name);
				}
				else EnableWindow(GetDlgItem(hWnd,IDOK),0);
			break;
		case IDOK:
			{
			char str[256];
			float f;
			GetDlgItemText(hWnd,IDC_SAMPLESVOLUME,str,255);
			sscanf(str,"%f",&f);
			VOLUME_FACTOR=f*f*f*1000.0f;
			if (IsDlgButtonChecked(hWnd,IDC_SIZE128))
				screen_sx=screen_sy=128;
			else 
			if (IsDlgButtonChecked(hWnd,IDC_SIZE256))
				screen_sx=screen_sy=256;
			else screen_sx=screen_sy=64;
			savelog=IsDlgButtonChecked(hWnd,IDC_SAVETXT);
			MyWriteProfile("viewbsp","filename", REG_SZ, (unsigned char *)&bsp_file_name, sizeof(char)*strlen(bsp_file_name)+1);
			EndDialog (hWnd, IDOK);
			}
			break;
		case IDCANCEL:
			EndDialog (hWnd, IDCANCEL);
			break;
		}
		break;
	}
	return FALSE;
} 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	hInstance=hInst;
	
	if (IDCANCEL==DialogBox(hInst,MAKEINTRESOURCE(IDD_FLYPVS),0,(DLGPROC)flypvsProc))
		return 0;

	set_engine(new pvsEngine,0,hInst,FLYAPPID_VIEWBSPGL);
	
	if(((pvsEngine *)flyengine)->opendata(bsp_file_name)==0)
	{
		MessageBox(0, "Could not open scene files!", "ViewBSPgl", MB_OK | MB_ICONEXCLAMATION);
		free_engine();
		return 0;
	}

	MSG msg;
	WNDCLASS wndclass;
	memset(&wndclass,0,sizeof(WNDCLASS));

	wndclass.lpfnWndProc   = (WNDPROC)MainWndProc;
	wndclass.hInstance     = hInst;
	wndclass.hIcon         = 0;
	wndclass.hCursor       = 0;
	wndclass.hbrBackground = 0;
	wndclass.lpszMenuName  = szAppName;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
		return FALSE;

	hWndMain = CreateWindow(szAppName, szAppName,
					WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
					0, 0, screen_sx, screen_sy,	NULL, NULL, hInst, NULL);
	if (!hWndMain)
		return 0;

	time(&t1);

	while (1) 
		{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) 
			{
			if (GetMessage(&msg, NULL, 0, 0)) 
				{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
			else 
				{
				char str[256];
				time(&t2);
				int dt=(int)(t2-t1);
				sprintf(str,
					"Nodes:\t%i\nInvalid:\t%i\nSamples:\t%i\nTime:\t%02i:%02i:%02i",
					flyengine->nleaf,fail_nodes,sample_count,dt/3600,(dt/60)%60,dt%60);
				MessageBox(0,str,"ViewBSPgl",MB_OK|MB_ICONINFORMATION);
				free_engine();
				return 1;
				}
			}
		DoFrame();
		}

	return 0;
}

