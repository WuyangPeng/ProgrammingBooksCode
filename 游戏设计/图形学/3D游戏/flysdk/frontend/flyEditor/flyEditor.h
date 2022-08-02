// flyEditor.h : main header file for the FLYEDITOR application
//

#if !defined(AFX_FLYEDITOR_H__5A2CCB23_B946_11D2_8077_D12CBD47771D__INCLUDED_)
#define AFX_FLYEDITOR_H__5A2CCB23_B946_11D2_8077_D12CBD47771D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorApp:
// See flyEditor.cpp for the implementation of this class
//

class CFlyEditorApp : public CWinApp
{
public:
	CFlyEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlyEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFlyEditorApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYEDITOR_H__5A2CCB23_B946_11D2_8077_D12CBD47771D__INCLUDED_)
