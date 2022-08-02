// zorder_dead_window_testDlg.h : header file
//

#if !defined(AFX_ZORDER_DEAD_WINDOW_TESTDLG_H__9D761B56_722D_4792_9A5F_0DFD8F65D987__INCLUDED_)
#define AFX_ZORDER_DEAD_WINDOW_TESTDLG_H__9D761B56_722D_4792_9A5F_0DFD8F65D987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZorder_dead_window_testDlg dialog

class CZorder_dead_window_testDlg : public CDialog
{
// Construction
public:
	CZorder_dead_window_testDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZorder_dead_window_testDlg)
	enum { IDD = IDD_ZORDER_DEAD_WINDOW_TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZorder_dead_window_testDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZorder_dead_window_testDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZORDER_DEAD_WINDOW_TESTDLG_H__9D761B56_722D_4792_9A5F_0DFD8F65D987__INCLUDED_)
