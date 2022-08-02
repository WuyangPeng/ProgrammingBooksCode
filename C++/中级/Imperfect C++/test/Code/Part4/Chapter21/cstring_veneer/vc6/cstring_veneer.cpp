// cstring_veneer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "cstring_veneer.h"
#include "cstring_veneerDlg.h"

#include <stlsoft_first_class_promoter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _MSC_VER
#include <cstdint>
#include <cassert>

using   std::uint16_t;
using   std::uint32_t;
using   std::sint64_t;
#else
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef signed __int64  sint64_t;
#endif /* 0 */

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerApp

BEGIN_MESSAGE_MAP(CCstring_veneerApp, CWinApp)
    //{{AFX_MSG_MAP(CCstring_veneerApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerApp construction

struct UInteger32
{
#ifdef BIG_ENDIAN
  uint16_t  high;
  uint16_t  low;
#else
  uint16_t  low;
  uint16_t  high;
#endif
};

struct LargeInteger
    : public stlsoft::first_class_promoter<LARGE_INTEGER>
//  : public LARGE_INTEGER
{
// Construction
public:
//  . . .

// Conversion
public:
  operator sint64_t &()
  {
      LARGE_INTEGER &li =   *this;

      return li.QuadPart;
  }
  operator sint64_t const &() const
  {
      LARGE_INTEGER const &li   =   *this;

      return li.QuadPart;
  }
};

CCstring_veneerApp::CCstring_veneerApp()
{
    uint32_t   v1   = 0x76543210;
    UInteger32 ui32 = *reinterpret_cast<UInteger32*>(&v1);
    uint32_t   v2   = *reinterpret_cast<uint32_t*>(&ui32);

    LargeInteger    li1;
    LargeInteger    li2;
    LargeInteger    li3;

    li1 = li2 + li3;

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCstring_veneerApp object

CCstring_veneerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerApp initialization

BOOL CCstring_veneerApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

    CCstring_veneerDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
