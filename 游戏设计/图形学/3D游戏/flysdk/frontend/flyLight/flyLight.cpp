#include "../../lib/Fly3D.h"
#include "lightengine.h"
#include "resource.h"
#include "time.h"
#include <commctrl.h>

#define MAXLMPIXELSIZE 100

HINSTANCE hInst;
HWND hWndHC,hWndProgress,hWndStatus;
int lightvalue=-1,shadows=2,connectivity=1,ambient=32;
float lmpixelsize=50.0;
int mapsize=128;

float lightradius=0.0f;
char fly_file_name[256]="";

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
	HINSTANCE hInstance;

	hInstance=(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);
	
	memset(&ofn,0,sizeof(OPENFILENAME));
	char filename[256]="";
	strcpy(filename,fly_file_name);

	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWnd;
	ofn.hInstance=hInstance;
	ofn.lpstrFilter="Fly scene (*.fly)\0*.fly\0";
	ofn.lpstrDefExt="fly";
	ofn.lpstrFile=filename;
	ofn.nMaxFile=255;
	ofn.lpstrTitle="Open Fly3D Scene";
	ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	
	if (GetOpenFileName(&ofn))
	{
		strcpy(file,filename);
		if (filename[0])
			return 1;
	}
	return 0;
}

BOOL FAR PASCAL lightbspProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_INITDIALOG:
		hWndStatus=GetDlgItem(hWnd,IDC_STATUS);
		hWndProgress=GetDlgItem(hWnd,IDC_PROGRESS);
		EnableWindow(GetDlgItem(hWnd,IDOK),0);
		if (lightradius!=0.0f)
			{
			SetDlgItemInt(hWnd,IDC_LIGHTRADIUSEDIT,(int)lightradius,1);
			EnableWindow(GetDlgItem(hWnd,IDC_LIGHTRADIUSEDIT),1);
			}
		else EnableWindow(GetDlgItem(hWnd,IDC_LIGHTRADIUSEDIT),0);

		CheckDlgButton(hWnd,IDC_SHADOWS,shadows?1:0);
		CheckDlgButton(hWnd,IDC_CONNECTIVITY,connectivity?1:0);
		
		if (lightvalue!=-1)
			{
			SetDlgItemInt(hWnd,IDC_LIGHTVALUEEDIT,lightvalue,1);
			EnableWindow(GetDlgItem(hWnd,IDC_LIGHTVALUEEDIT),1);
			}
		else EnableWindow(GetDlgItem(hWnd,IDC_LIGHTVALUEEDIT),0);

		SetWindowText(GetDlgItem(hWnd,IDC_BSPFILE),fly_file_name);
		if (fly_file_name[0])
			EnableWindow(GetDlgItem(hWnd,IDOK),1);
		else EnableWindow(GetDlgItem(hWnd,IDOK),0);

		{
		char str[256];
		GetPrivateProfileString("fly", "amblight", "", str, 255, fly_file_name);
		sscanf(str, "%i", &ambient);
		GetPrivateProfileString("fly", "lmpxsize", "", str, 255, fly_file_name);
		sscanf(str, "%f", &lmpixelsize);
		GetPrivateProfileString("fly", "mapsize", "", str, 255, fly_file_name);
		sscanf(str, "%i", &mapsize);
		SetDlgItemInt(hWnd,IDC_AMBLIGHT,ambient,1);
		sprintf(str,"%.2f",lmpixelsize/10.0f);
		SetDlgItemText(hWnd,IDC_LMPIXELSIZE,str);
		SetDlgItemInt(hWnd,IDC_MAPSIZE,mapsize,1);
		}
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BROWSE:
			if (OpenBspFileDialog(hWnd,fly_file_name))
				if (fly_file_name[0])
				{
					char str[256];

					GetPrivateProfileString("fly", "amblight", "", str, 255, fly_file_name);
					sscanf(str, "%i", &ambient);
					GetPrivateProfileString("fly", "lmpxsize", "", str, 255, fly_file_name);
					sscanf(str, "%f", &lmpixelsize);
					GetPrivateProfileString("fly", "mapsize", "", str, 255, fly_file_name);
					sscanf(str, "%i", &mapsize);

					SetDlgItemInt(hWnd,IDC_AMBLIGHT,ambient,1);
					sprintf(str,"%.2f",lmpixelsize/10.0f);
					SetDlgItemText(hWnd,IDC_LMPIXELSIZE,str);
					SetDlgItemInt(hWnd,IDC_MAPSIZE,mapsize,1);
				
					EnableWindow(GetDlgItem(hWnd,IDOK),1);
				SetDlgItemText(hWnd,IDC_BSPFILE,fly_file_name);
				}
			else EnableWindow(GetDlgItem(hWnd,IDOK),0);
			break;
		case IDOK:
			{
			char str[256];
			int i;

			shadows=IsDlgButtonChecked(hWnd,IDC_SHADOWS)*2;
			connectivity=IsDlgButtonChecked(hWnd,IDC_CONNECTIVITY);

			if (IsDlgButtonChecked(hWnd,IDC_LIGHTRADIUS))
				{
				i=GetDlgItemInt(hWnd,IDC_LIGHTRADIUSEDIT,0,1);
				lightradius=(float)(i<0?0:i);
				SetDlgItemInt(hWnd,IDC_LIGHTRADIUSEDIT,(int)lightradius,1);
				}
			else lightradius=0.0f;
			if (IsDlgButtonChecked(hWnd,IDC_LIGHTVALUE))
				{
				i=GetDlgItemInt(hWnd,IDC_LIGHTVALUEEDIT,0,1);
				lightvalue=(i<0?0:i>255?255:i);
				SetDlgItemInt(hWnd,IDC_LIGHTVALUEEDIT,lightvalue,1);
				}
			else lightvalue=-1;
			
			i=GetDlgItemInt(hWnd,IDC_AMBLIGHT,0,1);
			ambient=(i<0?0:i>255?255:i);

			mapsize=GetDlgItemInt(hWnd,IDC_MAPSIZE,0,1);
			
			GetDlgItemText(hWnd,IDC_LMPIXELSIZE,str,255);
			sscanf(str,"%f",&lmpixelsize);
			lmpixelsize*=10.0f;
			
			EnableWindow(GetDlgItem(hWnd,IDOK),0);
			
			set_engine(new lightEngine,hWnd,hInst,FLYAPPID_LIGHTBSP);
			init_directx();
			flyengine->shadows=shadows;
			((lightEngine *)flyengine)->light(fly_file_name);
			free_engine();
			free_directx();

			EnableWindow(GetDlgItem(hWnd,IDOK),1);
			}
			break;
		case IDC_LIGHTRADIUS:
			if (IsDlgButtonChecked(hWnd,IDC_LIGHTRADIUS))
				EnableWindow(GetDlgItem(hWnd,IDC_LIGHTRADIUSEDIT),1);
			else EnableWindow(GetDlgItem(hWnd,IDC_LIGHTRADIUSEDIT),0);
			break;
		case IDC_LIGHTVALUE:
			if (IsDlgButtonChecked(hWnd,IDC_LIGHTVALUE))
				EnableWindow(GetDlgItem(hWnd,IDC_LIGHTVALUEEDIT),1);
			else EnableWindow(GetDlgItem(hWnd,IDC_LIGHTVALUEEDIT),0);
			break;
		case IDCANCEL:
			EndDialog (hWnd, IDCANCEL);
			break;
		}
		break;
	}
	return FALSE;
} 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	hInst=hInstance;

	MyGetProfile("lightbsp","filename", (unsigned char *)&fly_file_name, 256);

	DialogBox(hInst,MAKEINTRESOURCE(IDD_LIGHTBSP),0,(DLGPROC)lightbspProc);

	MyWriteProfile("lightbsp","filename", REG_SZ, (unsigned char *)&fly_file_name, sizeof(char)*strlen(fly_file_name)+1);

	return 0;
}

