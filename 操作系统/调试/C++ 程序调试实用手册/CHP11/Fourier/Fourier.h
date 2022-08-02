// Fourier.h : main header file for the FOURIER application
//

#if !defined(AFX_FOURIER_H__1CA31E16_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
#define AFX_FOURIER_H__1CA31E16_D9F6_11D2_9D69_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFourierApp:
// See Fourier.cpp for the implementation of this class
//

class CFourierApp : public CWinApp
{
public:
	CFourierApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFourierApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFourierApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIER_H__1CA31E16_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
