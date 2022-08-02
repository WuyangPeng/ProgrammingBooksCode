#if !defined(AFX_CSTM1DLG_H__40D36E34_7D66_11D2_9263_000021799871__INCLUDED_)
#define AFX_CSTM1DLG_H__40D36E34_7D66_11D2_9263_000021799871__INCLUDED_

// cstm1dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	CListBox	m_classes;
	CEdit	m_classname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM1DLG_H__40D36E34_7D66_11D2_9263_000021799871__INCLUDED_)
