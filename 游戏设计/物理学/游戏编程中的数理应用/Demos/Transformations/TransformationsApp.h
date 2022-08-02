// TransformationsApp.h : main header file for the TransformationsApp application
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
//////////////
// INCLUDES //
//////////////
#include "resource.h"					// main symbols

/////////////
// CLASSES //
/////////////
class CTransformationsApp : public CWinApp
{
public:
	CTransformationsApp();				// Constructor

	~CTransformationsApp();				// Destructor

	RECT rect;							// Client Rect

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
public:
	afx_msg void OnAppAbout();
	afx_msg void OnStats();
	afx_msg void OnButtonMatrix();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonRedo();
	afx_msg void OnButtonUndo();
	afx_msg void OnButtonTrace();
	afx_msg void OnButtonQuad();
	afx_msg void OnButtonUndoUpdate(CCmdUI* pCmdUI);
	afx_msg void OnButtonRedoUpdate(CCmdUI* pCmdUI);
	afx_msg void OnButtonTraceUpdate(CCmdUI* pCmdUI);
	afx_msg void OnButtonQuadUpdate(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

extern CTransformationsApp theApp;