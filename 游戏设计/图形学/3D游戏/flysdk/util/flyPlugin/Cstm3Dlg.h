#if !defined(AFX_cstm3dlg_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_)
#define AFX_cstm3dlg_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_

// cstm3dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog

class CCustom3Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom3Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom3Dlg)
	enum { IDD = IDD_CUSTOM3 };
	CEdit	m_flysdkpath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom3Dlg)
	afx_msg void OnPaint();
	afx_msg void OnBrowsefly();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_cstm3dlg_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_)
