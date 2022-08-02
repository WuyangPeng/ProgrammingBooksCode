// flypluginaw.cpp : implementation file
//

#include "stdafx.h"
#include "flyplugin.h"
#include "flypluginaw.h"
#include "chooser.h"
#include <COMDEF.H>

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CFlypluginAppWiz::InitCustomAppWiz()
{
	Flypluginaw.m_Dictionary["PROJTYPE_DLL"]="1";

	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);
}

// This is called just before the custom AppWizard is unloaded.
void CFlypluginAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CFlypluginAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CFlypluginAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CFlypluginAppWiz::CustomizeProject(IBuildProject* pProject)
{
	long i,j;
	char str[256];
	_bstr_t tool1("cl.exe"),tool2("link.exe");

	IConfigurations *confs;
	IConfiguration *conf;

	pProject->get_Configurations(&confs);
	confs->get_Count(&i);

	for( j=0;j<i;j++ )
	{
		VARIANT v;
		v.vt=VT_I4;
		v.lVal=j+1;
		conf=0;
		confs->Item(v,&conf);
		if (conf)
			{
			sprintf(str,"/I %s",Flypluginaw.m_Dictionary["FLYSDKPATH"]);
			strcat(str,"lib");
			_bstr_t cmnd1(str);
			conf->AddToolSettings((wchar_t *)tool1,(wchar_t *)cmnd1,v);

			sprintf(str,"/libpath:%s",Flypluginaw.m_Dictionary["FLYSDKPATH"]);
			strcat(str,"lib");
			_bstr_t cmnd2(str);
			conf->AddToolSettings((wchar_t *)tool2,(wchar_t *)cmnd2,v);

			strcpy(str,"Fly3D.lib OpenGL32.lib glu32.lib dxguid.lib ddraw.lib dinput.lib dsound.lib dplayx.lib winmm.lib gdi32.lib ole32.lib user32.lib");
			_bstr_t cmnd3(str);
			conf->AddToolSettings((wchar_t *)tool2,(wchar_t *)cmnd3,v);
			
			conf->Release();
			}
	}

	confs->Release();

	// TODO: Add code here to customize the project.  If you don't wish
	//  to customize project, you may remove this virtual override.
	
	// This is called immediately after the default Debug and Release
	//  configurations have been created for each platform.  You may customize
	//  existing configurations on this project by using the methods
	//  of IBuildProject and IConfiguration such as AddToolSettings,
	//  RemoveToolSettings, and AddCustomBuildStep. These are documented in
	//  the Developer Studio object model documentation.

	// WARNING!!  IBuildProject and all interfaces you can get from it are OLE
	//  COM interfaces.  You must be careful to release all new interfaces
	//  you acquire.  In accordance with the standard rules of COM, you must
	//  NOT release pProject, unless you explicitly AddRef it, since pProject
	//  is passed as an "in" parameter to this function.  See the documentation
	//  on CCustomAppWiz::CustomizeProject for more information.
}


// Here we define one instance of the CFlypluginAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Flypluginaw.
CFlypluginAppWiz Flypluginaw;

