/* '03 Main.cpp' */

/* Mirus window framework header */
#include "mirus.h"

/* Custom derived class */
class CustomWindow : public mrWindow
{
public:
 /* Mirus related classes */
 mrInputManager      m_kInputManager;
 mrKeyboard          m_kKeyboard;
 mrScreen            m_kScreen;
 
 /* Our balls */
 mrEntity            m_akBalls [4];
 mrABO               m_akBallsABO [4];
 
 /* Constructor / Destructor */
 CustomWindow (void) {};
 ~CustomWindow (void) {};
 
 void Init (HINSTANCE hInstance);
 
 /* Window manipulation functions */
 mrBool32 Frame (void);
};

void CustomWindow::Init (HINSTANCE hInstance)
{
 /* Initialize the screen and the ABO (a smily) */
 m_kScreen.Init (m_hWindow);
 m_kScreen.SetMode (false, 640, 480, 32, true);
 
 /* Load the ball ABO */
 m_akBallsABO [0].LoadFromFile ("ball.txt");
 m_akBallsABO [0].SetSize (32, 32);
 m_akBallsABO [0].SetRadius (16);
 m_akBallsABO [0].SetColor (255,255,255,255);
 
 m_akBallsABO [1].LoadFromFile ("ball.txt");
 m_akBallsABO [1].SetSize (32, 32);
 m_akBallsABO [1].SetRadius (16);
 m_akBallsABO [1].SetColor (255,255,255,255);
 
 m_akBallsABO [2].LoadFromFile ("ball.txt");
 m_akBallsABO [2].SetSize (32, 32);
 m_akBallsABO [2].SetRadius (16);
 m_akBallsABO [2].SetColor (255,255,255,255);
 
 m_akBallsABO [3].LoadFromFile ("ball.txt");
 m_akBallsABO [3].SetSize (32, 32);
 m_akBallsABO [3].SetRadius (16);
 m_akBallsABO [3].SetColor (255,255,255,255);
 
 /* Set each balls physics properties */
 m_akBalls [0].SetMass (10);
 m_akBalls [0].SetPosition (mrVector2D (300, 100));
 m_akBalls [0].SetStaticFriction (0.7f);
 m_akBalls [0].SetStaticFriction (0.6f);
 m_akBalls [0].SetCoefficientOfRestitution (0.4f);
 
 m_akBalls [1].SetMass (10);
 m_akBalls [1].SetPosition (mrVector2D (300, 300));
 m_akBalls [1].SetStaticFriction (0.7f);
 m_akBalls [1].SetStaticFriction (0.6f);
 m_akBalls [1].SetCoefficientOfRestitution (0.4f);
 
 m_akBalls [2].SetMass (10);
 m_akBalls [2].SetPosition (mrVector2D (200, 300));
 m_akBalls [2].SetStaticFriction (0.7f);
 m_akBalls [2].SetStaticFriction (0.6f);
 m_akBalls [2].SetCoefficientOfRestitution (0.4f);
 
 m_akBalls [3].SetMass (10);
 m_akBalls [3].SetPosition (mrVector2D (400, 300));
 m_akBalls [3].SetStaticFriction (0.7f);
 m_akBalls [3].SetStaticFriction (0.6f);
 m_akBalls [3].SetCoefficientOfRestitution (0.4f);
 
 /* Initialize the input manager and device */
 m_kInputManager.Init (hInstance);
 m_kKeyboard.Init (m_hWindow);
}

/* Render frame */
mrBool32 CustomWindow::Frame(void)
{
 mrVector2D  kTempPosition;
 /* Start rendering */
 m_kScreen.Clear (0, 0, 0, 0);
 m_kScreen.StartFrame ();
 
 /* Simulate according to elapsed time */
 if (m_kScreen.GetFPS () != 0)
 {
  /* Move main ball */
  kTempPosition = m_akBalls [0].GetPosition ();
  m_kKeyboard.Update ();
  if (m_kKeyboard.IsButtonDown (DIK_UP))
  {
   kTempPosition [1] -= 1;
  }
  if (m_kKeyboard.IsButtonDown (DIK_DOWN))
  {
   kTempPosition [1] += 1;
  }
  if (m_kKeyboard.IsButtonDown (DIK_LEFT))
  {
   kTempPosition [0] -= 1;
  }
  if (m_kKeyboard.IsButtonDown (DIK_RIGHT))
  {
   kTempPosition [0] += 1;
  }
  m_akBalls [0].SetPosition (kTempPosition);
  /* Apply main force */
  if (m_kKeyboard.IsButtonDown (DIK_SPACE))
  {
   m_akBalls [0].ApplyLinearForce (mrVector2D (0, 15000));
  }
  
  /* Apply friction */
  m_akBalls [0].ApplyFriction (9.8f);
  m_akBalls [1].ApplyFriction (9.8f);
  m_akBalls [2].ApplyFriction (9.8f);
  m_akBalls [3].ApplyFriction (9.8f);
  
  /* Simulate first ball */
  if (m_akBallsABO [0].Collide (m_akBallsABO [1], true))
  {
   m_akBalls [0].HandleCollision (m_akBalls [1], 
    (m_akBalls [1].GetPosition () - m_akBalls [0].GetPosition ()));
  }
  if (m_akBallsABO [0].Collide (m_akBallsABO [2], true))
  {
   m_akBalls [0].HandleCollision (m_akBalls [2], 
    (m_akBalls [2].GetPosition () - m_akBalls [0].GetPosition ()));
  }
  if (m_akBallsABO [0].Collide (m_akBallsABO [3], true))
  {
   m_akBalls [0].HandleCollision (m_akBalls [3], 
    (m_akBalls [3].GetPosition () - m_akBalls [0].GetPosition ()));
  }
  /* Simulate second ball */
  if (m_akBallsABO [1].Collide (m_akBallsABO [2], true))
  {
   m_akBalls [1].HandleCollision (m_akBalls [2], 
    -m_akBalls [1].GetPosition () - m_akBalls [1].GetPosition ());
  }
  if (m_akBallsABO [1].Collide (m_akBallsABO [3], true))
  {
   m_akBalls [1].HandleCollision (m_akBalls [3], 
    -m_akBalls [1].GetPosition () - m_akBalls [1].GetPosition ());
  }
  /* Simulate third ball */
  if (m_akBallsABO [2].Collide (m_akBallsABO [3], true))
  {
   m_akBalls [2].HandleCollision (m_akBalls [3], 
    -m_akBalls [2].GetPosition () - m_akBalls [2].GetPosition ());
  }
  /* Simulate fourth ball */
  m_akBalls [0].Simulate (1/(mrReal32)m_kScreen.GetFPS ());
  m_akBalls [1].Simulate (1/(mrReal32)m_kScreen.GetFPS ());
  m_akBalls [2].Simulate (1/(mrReal32)m_kScreen.GetFPS ());
  m_akBalls [3].Simulate (1/(mrReal32)m_kScreen.GetFPS ());
 }
 /* Modify the ABO's so they use the same position as the entities */
 kTempPosition = m_akBalls [0].GetPosition ();
 m_akBallsABO [0].SetPosition ((mrUInt32)kTempPosition [0], 
  (mrUInt32)kTempPosition [1]);
 kTempPosition = m_akBalls [1].GetPosition ();
 m_akBallsABO [1].SetPosition ((mrUInt32)kTempPosition [0], 
  (mrUInt32)kTempPosition [1]);
 kTempPosition = m_akBalls [2].GetPosition ();
 m_akBallsABO [2].SetPosition ((mrUInt32)kTempPosition [0], 
  (mrUInt32)kTempPosition [1]);
 kTempPosition = m_akBalls [3].GetPosition ();
 m_akBallsABO [3].SetPosition ((mrUInt32)kTempPosition [0], 
  (mrUInt32)kTempPosition [1]);
 
 /* Render balls */
 m_akBallsABO [0].Render ();
 m_akBallsABO [1].Render ();
 m_akBallsABO [2].Render ();
 m_akBallsABO [3].Render ();
 m_kScreen.EndFrame ();
 
 return mrTrue;
}

/* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
 /* Our window */
 CustomWindow  kWindow;
 
 /* Create window */
 kWindow.Create (hInstance, "02 Physics Demo");
 kWindow.SetSize (640, 480);
 
 kWindow.m_kScreen.Init (kWindow.GetHandle ());
 kWindow.m_kScreen.SetMode (false, 640,480,32,true);
 
 kWindow.Init (hInstance);
 
 kWindow.Run ();
 return 0;
}