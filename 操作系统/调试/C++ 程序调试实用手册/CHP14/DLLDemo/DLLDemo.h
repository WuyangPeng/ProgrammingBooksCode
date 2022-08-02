// DLLDemo.h : main header file for the DLLDEMO application
//

#if !defined(AFX_DLLDEMO_H__D906B1CF_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_DLLDEMO_H__D906B1CF_93B3_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoApp:
// See DLLDemo.cpp for the implementation of this class
//

class CDLLDemoApp : public CWinApp
{
public:
	CDLLDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDLLDemoApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDEMO_H__D906B1CF_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
