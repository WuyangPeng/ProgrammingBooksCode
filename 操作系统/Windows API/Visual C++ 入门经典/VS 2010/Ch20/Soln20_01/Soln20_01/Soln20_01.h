
// Soln20_01.h : main header file for the Soln20_01 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSketchViewApp:
// See Soln20_01.cpp for the implementation of this class
//

class CSketchViewApp : public CWinAppEx
{
public:
	CSketchViewApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSketchViewApp theApp;
