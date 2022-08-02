// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5A2CCB27_B946_11D2_8077_D12CBD47771D__INCLUDED_)
#define AFX_MAINFRM_H__5A2CCB27_B946_11D2_8077_D12CBD47771D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlyEditorView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	CSplitterWnd	m_wndSplitter;
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CReBar			m_wndReBar;
	CDialogBar		m_wndDlgBar;

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CFlyEditorView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnToolsUnpakfpk();
	afx_msg void OnToolsPakfpk();
	afx_msg void OnToolsLight();
	afx_msg void OnToolsViewpvs();
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5A2CCB27_B946_11D2_8077_D12CBD47771D__INCLUDED_)
