// FontsDlg.h : header file
//

#if !defined(AFX_FONTSDLG_H__28C3E4A5_DCBE_11D3_AC49_0080AD426F27__INCLUDED_)
#define AFX_FONTSDLG_H__28C3E4A5_DCBE_11D3_AC49_0080AD426F27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFontsDlg dialog

class CFontsDlg : public CDialog
{
// Construction
public:
	void DrawBMP();
	CFontsDlg(CWnd* pParent = NULL);	// standard constructor

	LOGFONT lf;

// Dialog Data
	//{{AFX_DATA(CFontsDlg)
	enum { IDD = IDD_FONTS_DIALOG };
	CButton	m_save;
	CButton	m_256;
	CButton	m_128;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFontsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFont();
	afx_msg void OnSave();
	afx_msg void On256();
	afx_msg void On128();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTSDLG_H__28C3E4A5_DCBE_11D3_AC49_0080AD426F27__INCLUDED_)
