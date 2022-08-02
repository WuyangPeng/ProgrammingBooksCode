// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "flyEditor.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "flyEditorView.h"
#include "flyRenderView.h"
#include "flyEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFlyRenderView *rv;
extern int active_mode;
CDialogBar *dlgBar=0;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOLS_UNPAKFPK, OnToolsUnpakfpk)
	ON_COMMAND(ID_TOOLS_PAKFPK, OnToolsPakfpk)
	ON_COMMAND(ID_TOOLS_LIGHT, OnToolsLight)
	ON_COMMAND(ID_TOOLS_VIEWPVS, OnToolsViewpvs)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	dlgBar=&m_wndDlgBar;

	m_wndDlgBar.GetDlgItem(IDC_NUM)->EnableWindow(active_mode);
	m_wndDlgBar.GetDlgItem(IDC_SPIN)->EnableWindow(active_mode);
	m_wndDlgBar.GetDlgItem(IDC_ACTIVATE)->EnableWindow(active_mode);
	m_wndDlgBar.GetDlgItem(IDC_DESTROY)->EnableWindow(active_mode);

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 3))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(180, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFlyEditorView), CSize(180, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(CFlyRenderView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	OnViewStyle(ID_VIEW_DETAILS);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CFlyEditorView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CFlyEditorView* pView = DYNAMIC_DOWNCAST(CFlyEditorView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	CFlyEditorView* pView = GetRightPane(); 

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	CFlyEditorView* pView = GetRightPane();

	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMainFrame::OnToolsUnpakfpk() 
{
	CFileDialog fd(TRUE,"fpk",0,OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,"Fly3D Pak (*.fpk)|*.fpk||",this);
	if (fd.DoModal()==IDOK)
	{
		char file[256];
		strcpy(file,GetRightPane()->GetDocument()->flysdkpath);
		strcat(file,"flypak.exe \"");
		strcat(file,fd.GetPathName());
		strcat(file,"\"");
		WinExec(file,SW_SHOW);
	}
}

void CMainFrame::OnToolsPakfpk() 
{
    BROWSEINFO bi;     
	char Buffer[MAX_PATH]; 
    LPITEMIDLIST pidlBrowse;    
	LPMALLOC ppMalloc;
	
	SHGetMalloc( &ppMalloc );

	bi.hwndOwner=m_hWnd;
	bi.pidlRoot = 0; 
    bi.pszDisplayName = Buffer;     
	bi.lpszTitle = "Select directory to convert into a Fly3D Pak file"; 
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;     
	bi.lParam = 0;  

    pidlBrowse = SHBrowseForFolder(&bi);     
	if (pidlBrowse != NULL) 
		{  
        if (SHGetPathFromIDList(pidlBrowse, Buffer)) 
			{
			char file[256];
			strcpy(file,GetRightPane()->GetDocument()->flysdkpath);
			strcat(file,"flypak.exe \"");
			strcat(file,Buffer);
			strcat(file,"\"");
			WinExec(file,SW_SHOW);
			}
		ppMalloc->Free(pidlBrowse);
		}
}

void CMainFrame::OnToolsLight() 
{
	char file[256];
	strcpy(file,GetRightPane()->GetDocument()->flysdkpath);
	strcat(file,"flyLight.exe");
	WinExec(file,SW_SHOW);
}

void CMainFrame::OnToolsViewpvs() 
{
	char file[256];
	strcpy(file,GetRightPane()->GetDocument()->flysdkpath);
	strcat(file,"flyPVS.exe");
	WinExec(file,SW_SHOW);
}

