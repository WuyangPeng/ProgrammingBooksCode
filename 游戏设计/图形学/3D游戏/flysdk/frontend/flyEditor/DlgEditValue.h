#if !defined(AFX_DLGEDITVALUE_H__4D311241_C748_11D2_8077_C40F0427032D__INCLUDED_)
#define AFX_DLGEDITVALUE_H__4D311241_C748_11D2_8077_C40F0427032D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditValue dialog

class CDlgEditValue : public CDialog
{
// Construction
public:
	char value[256];
	param_desc * pd;
	CDlgEditValue(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditValue)
	enum { IDD = IDD_EDITVALUE };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditValue)
	afx_msg void OnKillfocusEdit1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITVALUE_H__4D311241_C748_11D2_8077_C40F0427032D__INCLUDED_)
