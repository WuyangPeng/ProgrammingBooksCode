// zorder_dead_window_test.h : main header file for the ZORDER_DEAD_WINDOW_TEST application
//

#if !defined(AFX_ZORDER_DEAD_WINDOW_TEST_H__C2A356D7_FC2B_4524_91B8_2CE9E0001713__INCLUDED_)
#define AFX_ZORDER_DEAD_WINDOW_TEST_H__C2A356D7_FC2B_4524_91B8_2CE9E0001713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZorder_dead_window_testApp:
// See zorder_dead_window_test.cpp for the implementation of this class
//

class CZorder_dead_window_testApp : public CWinApp
{
public:
	CZorder_dead_window_testApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZorder_dead_window_testApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZorder_dead_window_testApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZORDER_DEAD_WINDOW_TEST_H__C2A356D7_FC2B_4524_91B8_2CE9E0001713__INCLUDED_)
