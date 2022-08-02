// MLeak.h : main header file for the MLEAK application
//

#if !defined(AFX_MLEAK_H__7D597DA4_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_MLEAK_H__7D597DA4_8B14_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMLeakApp:
// See MLeak.cpp for the implementation of this class
//

class CMLeakApp : public CWinApp
{
public:
	CMLeakApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLeakApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMLeakApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLEAK_H__7D597DA4_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
