// cstring_veneer.h : main header file for the CSTRING_VENEER application
//

#if !defined(AFX_CSTRING_VENEER_H__9AF65E9B_C334_4016_9666_72790607CAFE__INCLUDED_)
#define AFX_CSTRING_VENEER_H__9AF65E9B_C334_4016_9666_72790607CAFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerApp:
// See cstring_veneer.cpp for the implementation of this class
//

class CCstring_veneerApp : public CWinApp
{
public:
    CCstring_veneerApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCstring_veneerApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CCstring_veneerApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTRING_VENEER_H__9AF65E9B_C334_4016_9666_72790607CAFE__INCLUDED_)
