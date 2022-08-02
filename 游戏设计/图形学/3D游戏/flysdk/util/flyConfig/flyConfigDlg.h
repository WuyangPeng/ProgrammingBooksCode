// flyConfigDlg.h : header file
//

#if !defined(AFX_FLYCONFIGDLG_H__74738EE7_F88D_46AA_9AF2_E8248F9929FC__INCLUDED_)
#define AFX_FLYCONFIGDLG_H__74738EE7_F88D_46AA_9AF2_E8248F9929FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigDlg dialog

class CFlyConfigDlg : public CDialog
{
// Construction
public:
	CFlyConfigDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlyConfigDlg)
	enum { IDD = IDD_FLYCONFIG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlyConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void init();
	void free();
	int init_gl();
	void free_gl();

	// Generated message map functions
	//{{AFX_MSG(CFlyConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnTest();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnKillfocusBrightness();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYCONFIGDLG_H__74738EE7_F88D_46AA_9AF2_E8248F9929FC__INCLUDED_)
