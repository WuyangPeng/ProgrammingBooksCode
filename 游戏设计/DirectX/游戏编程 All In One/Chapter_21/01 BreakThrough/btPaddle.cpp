 /* 'btPaddle.cpp' */

 /* Complement header file */
#include "btPaddle.h"

 /* Default constructor */
btPaddle::btPaddle (void)
{
 m_iWidth  = 0;
 m_iHeight = 0;
}

 /* Default destructor */
btPaddle::~btPaddle (void)
{
 m_iWidth  = 0;
 m_iHeight = 0;
}

 /* Create the paddle */
void btPaddle::Create (void)
{
  /* Setup the ABOs */
 m_akSidePaddles [0].LoadFromFile ("data/paddleside.txt");
 m_akSidePaddles [0].SetColor (255,255,255,255);
 m_akSidePaddles [1].LoadFromFile ("data/paddleside.txt");
 m_akSidePaddles [1].SetColor (255,255,255,255);

 m_kMainPaddle.LoadFromFile ("data/paddle.txt");
 m_kMainPaddle.SetColor (255,255,255,255);

  /* Setup the initial paddle size */
 SetSize (75, 10);
 
  /* Setup the entity */
 m_kObject.SetMass (10000);
 m_kObject.SetLinearVelocity (mrVector2D (0,0));
 m_kObject.SetCoefficientOfRestitution (1);
 m_kObject.SetStaticFriction (0.62f);
 m_kObject.SetKineticFriction (0.51f);
 m_kObject.SetPosition (mrVector2D (316, 433));

 Synchronize ();
}

 /* Render the paddle */
void btPaddle::Render (void)
{
  /* Render each part of the paddle */
 m_akSidePaddles [0].Render ();
 m_akSidePaddles [1].Render ();
 m_kMainPaddle.Render ();
}

 /* Synchronizes the entity and the ABO positions */
void btPaddle::Synchronize (void)
{
 mrVector2D kPosition;
 
  /* Set correct size for the ABOs */
 m_kMainPaddle.SetSize (m_iWidth - m_akSidePaddles [0].GetWidth (), m_iHeight);
 m_akSidePaddles [0].SetSize (m_iHeight, m_iHeight);
 m_akSidePaddles [1].SetSize (m_iHeight, m_iHeight);

  /* Set correct position for the ABOs */
 kPosition = m_kObject.GetPosition ();

 m_kMainPaddle.SetPosition ((mrUInt32)kPosition [0], 
                            (mrUInt32)kPosition [1]);
 m_akSidePaddles [0].SetPosition ((mrUInt32)kPosition [0] - m_iWidth/2
                                 + m_akSidePaddles [0].GetWidth ()/2, 
                                  (mrUInt32)kPosition [1]);
 m_akSidePaddles [1].SetPosition ((mrUInt32)kPosition [0] + m_iWidth/2 
                                 - m_akSidePaddles [0].GetWidth ()/2, 
                                  (mrUInt32)kPosition [1]);
}

 /* Update the paddle */
void btPaddle::Update (mrReal32 fStep)
{
  /* Apply friction, simulate and synchronize the positions */
 m_kObject.ApplyFriction (59.8f);
 m_kObject.Simulate (fStep); 

 m_kMainPaddle.Update ();

 Synchronize ();
}

 /* Sets the paddle size */
void btPaddle::SetSize (mrUInt32 iWidth, mrUInt32 iHeight)
{
 if (iWidth > 200)
 {
  iWidth = 200;
 }
 if (iWidth < 30)
 {
  iWidth = 30;
 }
 m_iWidth  = iWidth;
 m_iHeight = iHeight;
}

 /* Returns the paddle width */
mrUInt32 btPaddle::GetWidth (void)
{
 return m_iWidth;
}

 /* Returns the paddle height */
mrUInt32 btPaddle::GetHeight (void)
{
 return m_iHeight;
}

 /* Returns the paddle entity */
mrEntity * btPaddle::GetObject (void)
{
 return &m_kObject;
}


