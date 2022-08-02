// Fonts.h : main header file for the FONTS application
//

#if !defined(AFX_FONTS_H__28C3E4A3_DCBE_11D3_AC49_0080AD426F27__INCLUDED_)
#define AFX_FONTS_H__28C3E4A3_DCBE_11D3_AC49_0080AD426F27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontsApp:
// See Fonts.cpp for the implementation of this class
//

class CFontsApp : public CWinApp
{
public:
	CFontsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontsApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTS_H__28C3E4A3_DCBE_11D3_AC49_0080AD426F27__INCLUDED_)
