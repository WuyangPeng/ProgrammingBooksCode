#if !defined(AFX_FOURIERDLG2_H__B0E31BB4_DD58_11D2_9D69_0080AE000001__INCLUDED_)
#define AFX_FOURIERDLG2_H__B0E31BB4_DD58_11D2_9D69_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FourierDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FourierDlg2 dialog

class FourierDlg2 : public CDialog
{
// Construction
public:
	FourierDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FourierDlg2)
	enum { IDD = IDD_DIALOG2 };
	// WHM added this code
	BOOL m_check1;
	BOOL m_check2;
	BOOL m_check3;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FourierDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FourierDlg2)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIERDLG2_H__B0E31BB4_DD58_11D2_9D69_0080AE000001__INCLUDED_)
