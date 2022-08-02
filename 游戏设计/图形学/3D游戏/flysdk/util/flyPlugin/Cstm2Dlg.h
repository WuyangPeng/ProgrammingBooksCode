#if !defined(AFX_CSTM2DLG_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_)
#define AFX_CSTM2DLG_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_

// cstm2dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog

class CCustom2Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom2Dlg();
	virtual BOOL OnDismiss();
	char *GetParamClass(int type);
	char *GetParamType(int type);
	void InitDialog();

// Dialog Data
	//{{AFX_DATA(CCustom2Dlg)
	enum { IDD = IDD_CUSTOM2 };
	CListBox	m_param;
	CEdit	m_paramname;
	CComboBox	m_paramtype;
	CComboBox	m_classes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom2Dlg)
	afx_msg void OnPaint();
	afx_msg void OnParamDelete();
	afx_msg void OnParamNew();
	afx_msg void OnParamDown();
	afx_msg void OnParamUp();
	afx_msg void OnSelchangeClasses();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeParameters();
	afx_msg void OnChangeParamName();
	afx_msg void OnSelchangeParamType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM2DLG_H__40D36E36_7D66_11D2_9263_000021799871__INCLUDED_)
