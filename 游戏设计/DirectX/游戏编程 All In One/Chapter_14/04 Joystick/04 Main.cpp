 /* '04 Main.cpp' */

 /* Mirus header */
#include "mirus.h"

 /* Input class */
class InputWindow : public mrWindow
{
  /* Input related classes */
 mrInputManager      m_kInputManager;
 mrJoystick             m_kJoystick;

  /* Mirus related classes */
 mrScreen            m_kScreen;
 mrABO               m_kABO;

public:
  /* Constructor / Destructor */
 InputWindow (void);
 ~InputWindow (void);

 void Init (HINSTANCE hInstance);

  /* Window manipulation functions */
 mrBool32 Frame (void);
};

InputWindow::InputWindow (void)
{
}

InputWindow::~InputWindow (void)
{
}

void InputWindow::Init (HINSTANCE hInstance)
{
  /* Initialize the screen and the ABO (a smily) */
 m_kScreen.Init (m_hWindow);
 m_kScreen.SetMode (false, 640, 480, 32, true);
 m_kABO.LoadFromFile ("smile.txt");
 m_kABO.SetSize (60, 60);
 m_kABO.SetPosition (320, 240);
 m_kABO.SetColor (255,255,255,255);

  /* Initialize the input manager and device */
 m_kInputManager.Init (hInstance);
 m_kJoystick.Init (m_hWindow, -10, 10, 1);
}

 /* Render frame */
mrBool32 InputWindow::Frame(void)
{
  /* Start rendering */
 m_kScreen.Clear (0, 0, 0, 0);
 m_kScreen.StartFrame ();

  /* Render */
 m_kABO.Render ();

  /* Get the input and move the smily */
 m_kJoystick.Update ();
 int iX = m_kABO.GetXPosition ();
 int iY = m_kABO.GetYPosition ();
  
 iX += m_kJoystick.GetXAxis ();
 iY += m_kJoystick.GetYAxis ();

 m_kABO.SetPosition (iX, iY);

 m_kScreen.EndFrame ();

 return mrTrue;
}

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  /* Our window */
 InputWindow  kWindow;

  /* Create window */
 kWindow.Create (hInstance, "Joystick");
 kWindow.SetSize (640, 480);
 
 kWindow.Init (hInstance);
 kWindow.Run ();

 return 0;
}
