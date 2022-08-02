// cstring_veneerDlg.cpp : implementation file
//
// Updated: 28th January 2003

#include "stdafx.h"
#include "cstring_veneer.h"
#include "cstring_veneerDlg.h"

#include <stlsoft_constraints.h>

#include <stlsoft_string_tokeniser.h>

stlsoft_ns_using(string_tokeniser)
stlsoft_ns_using(string_tokeniser_type_traits)

#include <winstl_environment_variable.h>

winstl_ns_using(environment_variable)

/////////////////////////////////////////////////////////////////////////////

#if 0
namespace stlsoft
{

template <>
struct string_tokeniser_type_traits<CString>
{
  typedef TCHAR   value_type;
  typedef LPTSTR  iterator_type;
  typedef LPCTSTR const_iterator_type;
  typedef size_t  size_type;

  static const_iterator_type begin(CString const &s)
  {
    return s;
  }

  static const_iterator_type end(CString const &s)
  {
    return begin(s) + s.GetLength();
  }

  static T create(const_iterator_type f, const_iterator_type t)
  {
    return CString(f, t - f);
  }
};

} // namespace stlsoft

typedef CString CString_t;

#else

class CString_veneer
#ifdef _MFCSTL_CSTRING_VENEER_INHERIT_AS_PUBLIC
  : public CString
#else
  : protected CString
#endif /* _MFCSTL_CSTRING_VENEER_INHERIT_AS_PUBLIC */
  , protected stlsoft::is_veneer<CString, CString_veneer>
{
protected:
    typedef CString parent_class_type;
public:
    typedef TCHAR   value_type;
    typedef LPTSTR  iterator;
    typedef LPCTSTR const_iterator;
    typedef LPTSTR  pointer;
    typedef LPCTSTR const_pointer;
    typedef size_t  size_type;

// Construction
public:
    CString_veneer()
        : parent_class_type()
    {}
    CString_veneer(CString_veneer const &rhs)
        : parent_class_type(rhs)
    {}
    explicit CString_veneer(CString const &rhs)
        : parent_class_type(rhs)
    {}
    explicit CString_veneer(LPCSTR s)
        : parent_class_type(s)
    {}
    explicit CString_veneer(LPCWSTR s)
        : parent_class_type(s)
    {}
    explicit CString_veneer(unsigned char const *s)
        : parent_class_type(s)
    {}
    CString_veneer(LPCTSTR from, LPCTSTR to)
        : parent_class_type(from, to - from)
    {}
    CString_veneer(LPCTSTR from, int length)
        : parent_class_type(from, length)
    {}

// Iteration
public:
    const_iterator  begin() const
    {
        return *this;
    }
    const_iterator  end() const
    {
        return begin() + GetLength();
    }

// Access
public:
    const_pointer c_str() const
    {
        return *this;
    }
};

namespace winstl
{
inline TCHAR const *c_str_ptr(CString_veneer const &s)
{
    return s.c_str();
}
}

typedef CString_veneer  CString_t;

#endif /* 0 */

////////////////////////////////////////////////////////////////////////////////

#include <winstl_control_functionals.h>

winstl_ns_using(listbox_back_inserter)

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerDlg dialog

CCstring_veneerDlg::CCstring_veneerDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCstring_veneerDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CCstring_veneerDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCstring_veneerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCstring_veneerDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCstring_veneerDlg, CDialog)
    //{{AFX_MSG_MAP(CCstring_veneerDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCstring_veneerDlg message handlers

BOOL CCstring_veneerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    HWND    hwndListBox =   ::GetDlgItem(m_hWnd, IDC_PATHS);

    typedef string_tokeniser<CString_t, TCHAR>  CString_tokeniser_t;

    CString_tokeniser_t tokens(environment_variable<char>("PATH"), ';');

    std::for_each(tokens.begin(), tokens.end(), listbox_back_inserter(hwndListBox));

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    // TODO: Add extra initialization here
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCstring_veneerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCstring_veneerDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCstring_veneerDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}
