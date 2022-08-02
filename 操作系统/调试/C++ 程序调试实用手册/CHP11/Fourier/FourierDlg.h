#if !defined(AFX_FOURIERDLG_H__1CA31E26_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
#define AFX_FOURIERDLG_H__1CA31E26_D9F6_11D2_9D69_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FourierDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FourierDlg dialog

class FourierDlg : public CDialog
{
// Construction
public:
	FourierDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FourierDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_text;
	UINT	m_terms;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FourierDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FourierDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIERDLG_H__1CA31E26_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
