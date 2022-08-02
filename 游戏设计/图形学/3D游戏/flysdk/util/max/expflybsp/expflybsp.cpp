// flyexp.cpp: implementation of the flyexp class.
//
//////////////////////////////////////////////////////////////////////

#include "expflybsp.h"
#include "../../../lib/Fly3D.h"
#include "scene_max.h"
#include "enum_scene.h"
#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lightradius=200,savelog=1,saveobj=1,maxdepth=10,
	bspmode=0,planemode=2,savebsp=1,cartoonlight=0;

int tot_vert,tot_face;

BOOL controlsInit=0;

HINSTANCE hInstance;

BOOL CALLBACK OptionsProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			lightradius=GetDlgItemInt(hWnd,IDC_LIGHTRADIUS,0,0)*10;
			maxdepth=GetDlgItemInt(hWnd,IDC_MAXDEPTH,0,0);
			savelog=IsDlgButtonChecked(hWnd,IDC_SAVETXT);
			saveobj=IsDlgButtonChecked(hWnd,IDC_SAVEOBJ);
			savebsp=IsDlgButtonChecked(hWnd,IDC_SAVEBSP);
			bspmode=IsDlgButtonChecked(hWnd,IDC_AXISALIGNED);
			planemode=IsDlgButtonChecked(hWnd,IDC_FREESPACE)+2;
			cartoonlight=IsDlgButtonChecked(hWnd,IDC_CARTOONLIGHT);
			if (lightradius<0)
				MessageBox(hWnd,"Inavlid light radius!","Fly3D BSP Export",MB_OK);
			else
			if (maxdepth<1 || maxdepth>20)
				MessageBox(hWnd,"Inavlid tree depth!\nMust be from 1 to 20.","Fly3D BSP Export",MB_OK);
			else
				EndDialog(hWnd,1);
			break;
		case IDCANCEL:
			EndDialog(hWnd,0);
			break;
		case IDC_SAVEBSP:
			if (IsDlgButtonChecked(hWnd,IDC_SAVEBSP))
				EnableWindow(GetDlgItem(hWnd,IDC_SAVETXT),1);
			else EnableWindow(GetDlgItem(hWnd,IDC_SAVETXT),0);
			break;
		case IDC_FACEALIGNED:
			bspmode=0;
			EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTH),0);
			EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTHSTATIC),0);
			EnableWindow(GetDlgItem(hWnd,IDC_LANDSCAPE),0);
			EnableWindow(GetDlgItem(hWnd,IDC_FREESPACE),0);
			break;
		case IDC_AXISALIGNED:
			bspmode=1;
			EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTH),1);
			EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTHSTATIC),1);
			EnableWindow(GetDlgItem(hWnd,IDC_LANDSCAPE),1);
			EnableWindow(GetDlgItem(hWnd,IDC_FREESPACE),1);
			break;
		}
		break;

    case WM_INITDIALOG:
		SetDlgItemInt(hWnd,IDC_LIGHTRADIUS,lightradius/10,0);
		SetDlgItemInt(hWnd,IDC_MAXDEPTH,maxdepth,0);
		CheckDlgButton(hWnd,IDC_SAVETXT,savelog);
		CheckDlgButton(hWnd,IDC_SAVEOBJ,saveobj);
		CheckDlgButton(hWnd,IDC_SAVEBSP,savebsp);
		CheckDlgButton(hWnd,IDC_CARTOONLIGHT,cartoonlight);
		CheckRadioButton(hWnd,IDC_FACEALIGNED,IDC_AXISALIGNED,IDC_FACEALIGNED+bspmode);
		CheckRadioButton(hWnd,IDC_LANDSCAPE,IDC_FREESPACE,IDC_LANDSCAPE+planemode-2);
		EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTH),bspmode);
		EnableWindow(GetDlgItem(hWnd,IDC_MAXDEPTHSTATIC),bspmode);
		EnableWindow(GetDlgItem(hWnd,IDC_LANDSCAPE),bspmode);
		EnableWindow(GetDlgItem(hWnd,IDC_FREESPACE),bspmode);
		break;
	}
	return FALSE;
} 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

flyexp::flyexp()
{
}

flyexp::~flyexp()
{
}

#ifdef MAX3
int flyexp::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)	// max 3.x
#endif
#ifdef MAX2
int flyexp::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts)					// max 2.x
#endif
#ifdef MAX1
int flyexp::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i)										// max 1.x
#endif
{
	if (IDOK==DialogBox(hInstance,MAKEINTRESOURCE(IDD_OPTIONS),i->GetMAXHWnd(),(DLGPROC)OptionsProc))
		{
		enum_scene_count e0;
		enum_scene e1;

		e0.time=i->GetTime();
		tot_face=0;
		tot_vert=0;
		ei->theScene->EnumTree( &e0 );

		if (saveobj)
			_mkdir("objects");

		e1.vert=new vector[tot_vert];
		e1.faces=new face[tot_face];

		e1.time=i->GetTime();
		ei->theScene->EnumTree( &e1 );

		if (savebsp && e1.nfaces)
			{
			e1.compute_scene_normals();
			e1.compute_light();
			e1.build_bsptree();
			e1.nleaf=0;
			e1.enum_leaf(e1.bsp);
			e1.save((char *)name);
			}

		delete e1.faces;
		delete e1.vert;
		if (e1.vertcolor)
			delete e1.vertcolor;
		e1.vertcolor=0;
		e1.faces=0;
		e1.vert=0;
		
		}
	
	return 1;
}

TCHAR *GetString(int id)
	{
	static TCHAR buf[256];
	if (hInstance)
		return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;
	return NULL;
	}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
{
	hInstance = hinstDLL;

	if ( !controlsInit ) 
		{
		controlsInit = TRUE;
		
		// jaguar controls
//		InitCustomControls(hInstance);

		// initialize Chicago controls
		InitCommonControls();
		}
	switch(fdwReason) 
		{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		}
	return(TRUE);
}


//------------------------------------------------------

class flyClassDesc:public ClassDesc {
	public:
	int 			IsPublic() { return 1; }
	void *			Create(BOOL loading = FALSE) { return new flyexp; }
	const TCHAR *	ClassName() { return GetString(IDS_APPNAME); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(0x1bbd4eb2, 0x6f94405c); }
	const TCHAR* 	Category() { return GetString(IDS_CATEGORY);  }
	};

static flyClassDesc desc;

__declspec( dllexport ) const TCHAR *
LibDescription() { return GetString(IDS_LONG_DESC); }

__declspec( dllexport ) int
LibNumberClasses() { return 1; }

__declspec( dllexport ) ClassDesc *
LibClassDesc(int i) {
	switch(i) {
		case 0: return &desc; break;
		default: return 0; break;
		}
	}

__declspec( dllexport ) ULONG 
LibVersion() { return VERSION_3DSMAX; }

int
flyexp::ExtCount() {
	return 1;
	}

const TCHAR *
flyexp::Ext(int n) {	
	switch(n) {
		case 0:
			return _T("bsp");
		}
	return _T("");
	}

const TCHAR *
flyexp::LongDesc() {	
	return GetString(IDS_LONG_DESC);
	}
	
const TCHAR *
flyexp::ShortDesc() {	
	return GetString(IDS_SHORT_DESC);
	}

const TCHAR *
flyexp::AuthorName() {	
	return GetString(IDS_AUTHOR);
	}

const TCHAR *
flyexp::CopyrightMessage() {	
	return GetString(IDS_COPYRIGHT);
	}

const TCHAR *
flyexp::OtherMessage1() {		
	return _T("");
	}

const TCHAR *
flyexp::OtherMessage2() {		
	return _T("");
	}

unsigned int
flyexp::Version() {				
	return 55;
	}

void
flyexp::ShowAbout(HWND hWnd) {	
 	}
