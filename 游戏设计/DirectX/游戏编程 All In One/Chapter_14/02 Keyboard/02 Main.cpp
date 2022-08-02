 /* '02 Main.cpp' */

 /* Mirus header */
#include "mirus.h"

 /* Input class */
class InputWindow : public mrWindow
{
  /* Input related classes */
 mrInputManager      m_kInputManager;
 mrKeyboard          m_kKeyboard;

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
 m_kKeyboard.Init (m_hWindow);
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
 m_kKeyboard.Update ();
 int iX = m_kABO.GetXPosition ();
 int iY = m_kABO.GetYPosition ();
  
 if (m_kKeyboard.IsButtonDown (DIK_UP))
 {
  iY -= 1;
 }
 if (m_kKeyboard.IsButtonDown (DIK_DOWN))
 {
  iY += 1;
 }
 if (m_kKeyboard.IsButtonDown (DIK_RIGHT))
 {
  iX += 1;
 }
 if (m_kKeyboard.IsButtonDown (DIK_LEFT))
 {
  iX -= 1;
 }
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
 kWindow.Create (hInstance, "Keyboard");
 kWindow.SetSize (640, 480);
 
 kWindow.Init (hInstance);
 kWindow.Run ();

 return 0;
}
