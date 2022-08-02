// cstring_veneerDlg.h : header file
//

#if !defined(AFX_CSTRING_VENEERDLG_H__9237C3DB_F7B3_408B_8283_45D55A44B6F0__INCLUDED_)
#define AFX_CSTRING_VENEERDLG_H__9237C3DB_F7B3_408B_8283_45D55A44B6F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerDlg dialog

class CCstring_veneerDlg : public CDialog
{
// Construction
public:
    CCstring_veneerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CCstring_veneerDlg)
    enum { IDD = IDD_CSTRING_VENEER_DIALOG };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCstring_veneerDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CCstring_veneerDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTRING_VENEERDLG_H__9237C3DB_F7B3_408B_8283_45D55A44B6F0__INCLUDED_)
