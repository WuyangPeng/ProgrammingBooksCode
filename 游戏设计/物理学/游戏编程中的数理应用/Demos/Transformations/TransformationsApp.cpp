// TransformationsApp.cpp : Defines the class behaviors for the application.
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand

/////////////
// INCLUDE //
/////////////
#include "stdafx.h"
#include "TransformationsApp.h"
#include "MainFrm.h"
#include "OpenGL.h"
#include "CMatrixCreate.h"
#include "EntityManager.h"

/////////////////
// MESSAGE MAP //
/////////////////
BEGIN_MESSAGE_MAP(CTransformationsApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_STATS, OnStats)
	ON_COMMAND(ID_BUTTON_MATRIX, OnButtonMatrix)
	ON_COMMAND(ID_BUTTON_RESET, OnButtonReset)
	ON_COMMAND(ID_BUTTON_UNDO, OnButtonUndo)
	ON_COMMAND(ID_BUTTON_REDO, OnButtonRedo)
	ON_COMMAND(ID_BUTTON_TRACE, OnButtonTrace)
	ON_COMMAND(ID_BUTTON_QUAD, OnButtonQuad)
		
	ON_UPDATE_COMMAND_UI(ID_BUTTON_UNDO, OnButtonUndoUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_REDO, OnButtonRedoUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TRACE, OnButtonTraceUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_QUAD, OnButtonQuadUpdate)
END_MESSAGE_MAP()


// CTransformationsApp construction
CTransformationsApp::CTransformationsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// CTransformationsApp destructore
CTransformationsApp::~CTransformationsApp()
{
	// Lets Call some routines to Clean up some memory
	EntityManager* EMan = EntityManager::getInstance();
	EMan->DestroyEntityManager();
	OpenGL* view = OpenGL::getInstance();
	view->DestroyOpenGL();

	delete m_pMainWnd;
};

// The one and only CTransformationsApp object
CTransformationsApp theApp;

// CTransformationsApp initialization
BOOL CTransformationsApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

//////////////////////
// MESSAGE HANDLERS //
//////////////////////

// Redo a previous action
void CTransformationsApp::OnButtonRedo()
{
	EntityManager* EMan = EntityManager::getInstance();
	OpenGL* view = OpenGL::getInstance();
	EMan->selected->redo(EMan->selected->undoActions.front());

	// Redraw
	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

// Undo the last action
void CTransformationsApp::OnButtonUndo()
{
	EntityManager* EMan = EntityManager::getInstance();
	OpenGL* view = OpenGL::getInstance();
	EMan->selected->undo(EMan->selected->actions.front());

	// Redraw
	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

// Trace the currently seclected quad
void CTransformationsApp::OnButtonTrace()
{
	EntityManager* EMan = EntityManager::getInstance();
	OpenGL* view = OpenGL::getInstance();
	EMan->selected->traces.push_back(EMan->selected->transMats.size());
	EMan->selected->actions.push_front(2);

	for (EMan->selected->matItr = 
			EMan->selected->undoMats.begin(); 
			EMan->selected->matItr != 
			EMan->selected->undoMats.end(); 
			EMan->selected->matItr++)
	{
		delete (*EMan->selected->matItr);
	}
	EMan->selected->undoMats.clear();

	EMan->selected->undoActions.clear();
	
	// Redraw
	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

// 
void CTransformationsApp::OnButtonQuad()
{
	EntityManager* EMan = EntityManager::getInstance();
	OpenGL* view = OpenGL::getInstance();
	EMan->selected->selection = false;
	EMan->selected = EMan->newEntity();
	EMan->selected->selection = true;
	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

// CTransformationsApp message handlers
void CTransformationsApp::OnButtonMatrix()
{
	EntityManager* EMan = EntityManager::getInstance();
	OpenGL* view = OpenGL::getInstance();
	CMatrixCreate matDlg;
	matDlg.DoModal();
	EMan->selected->actions.push_front(1);

	for (EMan->selected->matItr = 
			EMan->selected->undoMats.begin(); 
			EMan->selected->matItr != 
			EMan->selected->undoMats.end(); 
			EMan->selected->matItr++)
	{
		delete (*EMan->selected->matItr);
	}
	EMan->selected->undoMats.clear();

	EMan->selected->undoActions.clear();

	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

void CTransformationsApp::OnButtonReset()
{
	EntityManager* EMan = EntityManager::getInstance();
	
	EMan->entities.clear();
	
	EMan->newEntity();

	m_pMainWnd->GetClientRect(&rect);
	InvalidateRect(m_pMainWnd->GetSafeHwnd(),&rect, true);
}

void CTransformationsApp::OnButtonUndoUpdate(CCmdUI* pCmdUI)
{
	EntityManager* EMan = EntityManager::getInstance();
	if (EMan->selected != NULL)
	{
		if (EMan->selected->actions.size() == 0)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
}
void CTransformationsApp::OnButtonRedoUpdate(CCmdUI* pCmdUI)
{
	EntityManager* EMan = EntityManager::getInstance();
	
	if (EMan->selected != NULL)
	{
		if (EMan->selected->undoActions.size() == 0)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
}

void CTransformationsApp::OnButtonQuadUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CTransformationsApp::OnButtonTraceUpdate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CTransformationsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAboutDlg dialog used for App About

class CStatsDlg : public CDialog
{
public:
	CStatsDlg();

// Dialog Data
	enum { IDD = IDD_STATS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CStatsDlg::CStatsDlg() : CDialog(CStatsDlg::IDD)
{
}

void CStatsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	CString str;
	EntityManager* EMan = EntityManager::getInstance();

	str.Format(_T("Red Corner(Origin):\tX = %g, Y = %g"), EMan->selected->transVerts[0].pos.vector[0],
		EMan->selected->transVerts[0].pos.vector[1]);
	
	DDX_Text(pDX, IDC_POINT1, str);

	str.Format(_T("Yellow Corner:\t\tX = %g, Y = %g"), EMan->selected->transVerts[1].pos.vector[0],
		EMan->selected->transVerts[1].pos.vector[1]);
	
	DDX_Text(pDX, IDC_POINT2, str);

	str.Format(_T("Green Corner:\t\tX = %g, Y = %g"), EMan->selected->transVerts[2].pos.vector[0],
		EMan->selected->transVerts[2].pos.vector[1]);
	
	DDX_Text(pDX, IDC_POINT3, str);

	str.Format(_T("Blue Corner:\t\tX = %g, Y = %g"), EMan->selected->transVerts[3].pos.vector[0],
		EMan->selected->transVerts[3].pos.vector[1]);
	
	DDX_Text(pDX, IDC_POINT4, str);
}

BEGIN_MESSAGE_MAP(CStatsDlg, CDialog)
END_MESSAGE_MAP()

void CTransformationsApp::OnStats()
{
	CStatsDlg statsDlg;
	statsDlg.DoModal();
}