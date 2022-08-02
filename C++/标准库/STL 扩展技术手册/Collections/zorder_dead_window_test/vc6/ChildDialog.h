#if !defined(AFX_CHILDDIALOG_H__F76728FD_48DF_45F8_9910_C43852BAF2C0__INCLUDED_)
#define AFX_CHILDDIALOG_H__F76728FD_48DF_45F8_9910_C43852BAF2C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildDialog.h : header file
//
// Updated: 13th January 2006

/////////////////////////////////////////////////////////////////////////////
// CChildDialog dialog

class CChildDialog : public CDialog
{
// Construction
public:
	CChildDialog(CWnd* pParent = NULL);   // standard constructor

	static BOOL Create(CString const &caption, CWnd *pParent)
	{
		CChildDialog	*cd	=	new CChildDialog(pParent);

		if(!cd->CDialog::Create(IDD, pParent))
		{
			return false;
		}

		cd->SetWindowText(caption);

		cd->ShowWindow(SW_SHOW);

		return true;
	}

// Dialog Data
	//{{AFX_DATA(CChildDialog)
	enum { IDD = IDD_CHILDDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChildDialog)
	afx_msg void OnClose();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDDIALOG_H__F76728FD_48DF_45F8_9910_C43852BAF2C0__INCLUDED_)
