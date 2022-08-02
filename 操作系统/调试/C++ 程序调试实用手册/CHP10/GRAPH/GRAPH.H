// graph.h : main header file for the GRAPH application
//

#if !defined(AFX_GRAPH_H__3732B2A6_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_GRAPH_H__3732B2A6_8DDB_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphApp:
// See graph.cpp for the implementation of this class
//

class CGraphApp : public CWinApp
{
public:
	CGraphApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__3732B2A6_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
