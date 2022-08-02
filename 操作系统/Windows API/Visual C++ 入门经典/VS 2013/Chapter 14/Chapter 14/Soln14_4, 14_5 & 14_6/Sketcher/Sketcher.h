
// Sketcher.h : main header file for the Sketcher application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSketcherApp:
// See Sketcher.cpp for the implementation of this class
//

class CSketcherApp : public CWinApp
{
public:
	CSketcherApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSketcherApp theApp;
