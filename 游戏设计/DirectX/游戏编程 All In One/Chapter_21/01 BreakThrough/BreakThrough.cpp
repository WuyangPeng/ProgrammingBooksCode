 /* 'BreakThrough.cpp' */

 /* Mirus header */
#include "Mirus\mirus.h"

 /* */
#include "btGame.h"

 /* BreakThrough class */
class BreakThroughWindow : public mrWindow
{
  /* Game related classes */
 btGame              m_kGame;

  /* Mirus related classes */
 mrScreen            m_kScreen;

public:


  /* Constructor / Destructor */
 BreakThroughWindow (void);
 ~BreakThroughWindow (void);

 void Init (HINSTANCE hInstance);

  /* Window manipulation functions */
 mrBool32 Frame (void);

};

BreakThroughWindow::BreakThroughWindow (void)
{
}

BreakThroughWindow::~BreakThroughWindow (void)
{
}

void BreakThroughWindow::Init (HINSTANCE hInstance)
{
 m_kScreen.Init (m_hWindow);
 m_kScreen.SetMode (false, 640, 480, 16, true);
 m_kGame.Start (hInstance, m_hWindow);
}

 /* Render frame */
mrBool32 BreakThroughWindow::Frame(void)
{
  /* Start rendering */
 m_kScreen.Clear (0, 0, 0, 0);
 m_kScreen.StartFrame ();

  /* Process and render game */
 if (m_kScreen.GetFPS () != 0)
 {
  if (mrFalse == m_kGame.Process (1 / (mrReal32)m_kScreen.GetFPS ()))
  {
   return mrFalse;
  }
  m_kGame.Render ();
 }

  /* Render particle system and end frame */
 m_kScreen.EndFrame ();

 return mrTrue;
}

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  /* Our window */
 BreakThroughWindow  kWindow;

  /* Create window */
 kWindow.Create (hInstance, "Break Through 1.0");
 kWindow.SetSize (640, 480);
 
 kWindow.Init (hInstance);
 kWindow.Run ();

 return 0;
}
