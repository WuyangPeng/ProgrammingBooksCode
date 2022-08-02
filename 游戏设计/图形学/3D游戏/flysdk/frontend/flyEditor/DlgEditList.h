#if !defined(AFX_DLGEDITLIST_H__4D311240_C748_11D2_8077_C40F0427032D__INCLUDED_)
#define AFX_DLGEDITLIST_H__4D311240_C748_11D2_8077_C40F0427032D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditList dialog

class CDlgEditList : public CDialog
{
// Construction
public:
	param_desc * pd;
	CDlgEditList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditList)
	enum { IDD = IDD_EDITLIST };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITLIST_H__4D311240_C748_11D2_8077_C40F0427032D__INCLUDED_)
