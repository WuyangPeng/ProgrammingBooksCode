// Framer.h : main header file for the FRAMER DLL
//

#if !defined(AFX_FRAMER_H__D906B1E2_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_FRAMER_H__D906B1E2_93B3_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

__declspec( dllexport ) void WINAPI ThickRectangle(CDC* pDC,
												   int x1,
												   int y1,
												   int x2,
												   int y2,
												   int t);
__declspec( dllexport ) void WINAPI ThickEllipse(CDC* pDC,
												 int x1,
												 int y1,
												 int x2,
												 int y2,
												 int t);
__declspec( dllexport ) void WINAPI ThickPixel(CDC* pDC,
											   int x1,
											   int y1);

/////////////////////////////////////////////////////////////////////////////
// CFramerApp
// See Framer.cpp for the implementation of this class
//

class CFramerApp : public CWinApp
{
public:
	CFramerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFramerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFramerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMER_H__D906B1E2_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
