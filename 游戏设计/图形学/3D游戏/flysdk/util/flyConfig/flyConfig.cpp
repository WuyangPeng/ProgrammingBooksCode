// flyConfig.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "flyConfig.h"
#include "flyConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigApp

BEGIN_MESSAGE_MAP(CFlyConfigApp, CWinApp)
	//{{AFX_MSG_MAP(CFlyConfigApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigApp construction

CFlyConfigApp::CFlyConfigApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlyConfigApp object

CFlyConfigApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigApp initialization

BOOL CFlyConfigApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	int ret=IDOK;

	while( ret==IDOK )
	{
		CFlyConfigDlg dlg;//=new CFlyConfigDlg;
		ret = dlg.DoModal();
//		delete dlg;
	}

	return FALSE;
}
