// Ex11_02.cpp  An elementary MFC program
#include <afxwin.h>                       // For the class library
     
// Application class definition
class COurApp: public CWinApp
{
public:
  virtual BOOL InitInstance() override;
};
     
// Window class definition
class COurWnd: public CFrameWnd
{
 public:
   // Constructor
   COurWnd()
   {
     Create(nullptr, _T("Our Dumb MFC Application"));
   }
};
     
// Function to create an instance of the main application window
BOOL COurApp::InitInstance(void)
{
  m_pMainWnd = new COurWnd;               // Construct a window object...
  m_pMainWnd->ShowWindow(m_nCmdShow);     // ...and display it
  return TRUE;
}
     
// Application object definition at global scope
COurApp AnApplication;                    // Define an application object
