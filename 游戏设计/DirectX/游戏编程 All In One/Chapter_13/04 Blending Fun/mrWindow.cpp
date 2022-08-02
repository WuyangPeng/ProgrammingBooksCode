 /* 'mrWindows.cpp' */

 /* Complement header file */
#include "mrWindow.h"

 /* Default constructor */
mrWindow::mrWindow (void)
{
 /* Do nothing */
}

 /* Default destructor */
mrWindow::~mrWindow (void)
{
 /* Do nothing */
}

 /* Create the window */
mrError32 mrWindow::Create (HINSTANCE hInstance, LPSTR szTitle, mrInt iWidth, 
                            mrInt iHeight, mrUInt32 iStyle)
{
  /* 'Visual' proprieties */
 m_kWndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
 m_kWndClass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
 m_kWndClass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);

  /* System proprieties */
 m_kWndClass.hInstance     = hInstance;
 m_kWndClass.lpfnWndProc   = WndProc;
 m_kWndClass.lpszClassName = "Mirus Window";

  /* Extra proprieties */
 m_kWndClass.lpszMenuName  = NULL;

 m_kWndClass.cbClsExtra = NULL;
 m_kWndClass.cbWndExtra = NULL;
 m_kWndClass.style      = NULL;

  /* Try to register class */
 if (!RegisterClass (&m_kWndClass))
 {
  return mrErrorRegisterClass;
 }

  /* Create the window */
 m_hWindow = CreateWindow ("Mirus Window", szTitle, iStyle, CW_USEDEFAULT,
                           CW_USEDEFAULT, iWidth, iHeight, 
                           NULL, NULL, hInstance, (void *) this);
 SetWindowText (m_hWindow, szTitle);

 return mrNoError;
}

 /* Normal message handler - direct messages to our own*/
LRESULT CALLBACK mrWindow::WndProc (HWND hWindow, UINT iMessage, 
                                    WPARAM wParam, LPARAM lParam)
{
 mrWindow * pkWindow   = NULL;
 mrBool32   bProcessed = mrFalse;

 switch (iMessage)
 {
  /* Window is creating - set custom information */
 case WM_NCCREATE:
  SetWindowLong (hWindow, GWL_USERDATA, 
                 (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
  break;
  /* Window message - Let our handler process it */
 default:
   pkWindow = (mrWindow *) GetWindowLong (hWindow, GWL_USERDATA);
   if (NULL != pkWindow)
   {
    bProcessed = pkWindow->MessageHandler (iMessage, wParam, lParam);
   }
  break;
 }
   /* Message not processed - let windows handle it */
 if (mrFalse == bProcessed)
 {
  return DefWindowProc (hWindow, iMessage, wParam, lParam);
 }
 return 0;
}

 /* Real time message loop */
void mrWindow::Run (void)
{
 while (1)
 {
   /* Query to see if there is any message in the queue */
  if (PeekMessage (&m_kMessage, m_hWindow, 0, 0, PM_REMOVE))
  {
    /* If it is the WM_QUIT message, quit the loop */
   if (WM_QUIT == m_kMessage.message)
   {
    break;
   }
    /* Process the message normally */
   else
   {
    TranslateMessage (&m_kMessage);
    DispatchMessage (&m_kMessage);
   }
  }
    /* No message, do frame */
  else
  {
   Frame ();
  }
 }
}

 /* Our message handler */
mrBool32 mrWindow::MessageHandler (UINT iMessage, WPARAM wParam, 
                                   LPARAM lParam)
{
 switch (iMessage)
 {
  /* Close window */
 case WM_CLOSE:
  PostQuitMessage (0);
  return mrTrue;
 break;
  /* Not handled - let Windows handle */
 default:
  return mrFalse;
 break;
 }
}

 /* Set window position */
void mrWindow::SetPosition (mrInt iX, mrInt iY)
{
  /* Set window position */
 SetWindowPos(m_hWindow, HWND_TOP, iX, iY, 0, 0, SWP_NOSIZE);
}

 /* Get window position */
POINT mrWindow::GetPosition (void)
{
 RECT  rcWindow;
 POINT pPosition;
  /* Get window position */
 GetWindowRect (m_hWindow, &rcWindow);

 pPosition.x = rcWindow.left;
 pPosition.y = rcWindow.top;
 
 return pPosition;
}

 /* Set window size */
void mrWindow::SetSize (mrInt iWidth, mrInt iHeight)
{
  /* Set window position */
 SetWindowPos(m_hWindow, HWND_TOP, 0, 0, iWidth, iHeight, SWP_NOMOVE);
}

 /* Gt window size */
POINT mrWindow::GetSize (void)
{
 RECT  rcWindow;
 POINT pSize;
  /* Get window position */
 GetWindowRect (m_hWindow, &rcWindow);

 pSize.x = rcWindow.right  - rcWindow.left;
 pSize.y = rcWindow.bottom - rcWindow.top;
 
 return pSize;
}

 /* Modify window state */
void mrWindow::Show (mrInt iShow)
{
  /* Change window visibility */
 ShowWindow (m_hWindow, iShow);
}

 /* Return window handle */
HWND mrWindow::GetHandle (void)
{
	return m_hWindow;
}



 