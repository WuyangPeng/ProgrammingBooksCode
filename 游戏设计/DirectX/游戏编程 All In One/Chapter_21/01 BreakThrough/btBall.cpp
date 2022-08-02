 /* 'btBall.cpp' */

 /* Complement header file */
#include "btBall.h"
 
 /* Default constructor */
btBall::btBall (void)
{
 m_fTimerCount = 0;
 m_iRadius     = 0;
 m_bIsAlive    = mrFalse;
}

 /* Default destructor */
btBall::~btBall (void)
{
 m_fTimerCount = 0;
 m_iRadius     = 0;
 m_bIsAlive    = mrFalse;
}

 /* Create the ball */
void btBall::Create (void)
{
  /* Setup the ABO */
 m_kBall.LoadFromFile ("data/ball.txt");
 m_kBall.SetColor (255,255,255,255);
  
  /* Setup the initial ball size */
 m_iRadius = 10;

  /* Setup the entity */
 m_kObject.SetInertia (1);
 m_kObject.SetMass (1);
 m_kObject.SetPosition (mrVector2D (316, 400));
 m_kObject.SetCoefficientOfRestitution (1);

  /* Setup ball attributes */
 m_bIsAlive    = mrTrue;
 m_fTimerCount = 0;
 
  /* Setup ball direction */
 mrVector2D kVelocity;
 mrReal32 fAngle;
 fAngle = 0;

  /* Randomize */
 srand (GetTickCount ());

  /* To prevent the ball from going almost straight up, we get a random
     angle until it suits what we want */
 while ((fAngle < 0.15f) && (fAngle > -0.15f))
 {
  fAngle = (1 - (2 * ((mrReal32)rand () / (mrReal32)RAND_MAX))) *
           (40 * 0.0174f);
 }
 fAngle -= (90 * 0.0174f);

  /* Calculate the direction */
 kVelocity [0] = (mrReal32)cos (fAngle);
 kVelocity [1] = (mrReal32)sin (fAngle);

 m_kObject.SetLinearVelocity (kVelocity);
 SetSpeed (250);

  /* Setup the particle system */
 if (m_kParticleTexture.GetID ()==0)
 {
   /* Load the texture */
  mrRGBAImage rkImage;
  rkImage.LoadFromBitmap ("Graphics/flare.bmp");

  m_kParticleTexture.Create (&rkImage);

   /* Setup particle system parameters */
  mrParticleSystemParams kParameters;

  kParameters.m_fSize       = 6;
  kParameters.m_fLifetime   = 0.40f;
  kParameters.m_iColor      = D3DCOLOR_RGBA (255, 208, 51, 255);
  kParameters.m_iFinalColor = D3DCOLOR_RGBA (255, 0, 0, 0);
  kParameters.m_kPosition   = mrVector2D (310,230);
  kParameters.m_fFinalSize  = 9;
  kParameters.m_fSpeed      = 0.25f;
  kParameters.m_fDispersion = 1;

   /* Create the particle system */
  m_kParticleSystem.Create (kParameters, 50, 100, &m_kParticleTexture);
  m_kParticleSystem.SetDontCreate (mrTrue);
 }
 Synchronize ();
}


 /* Destroy the ball */
void btBall::Destroy (void)
{
  /* Setup necessary variables to destroy the ball */
 m_bIsAlive    = mrFalse;
 m_fTimerCount = 0;
 SetSpeed (0);
 SetSize (0);

  /* Move ball to correct position so it doesn't disapear */
 mrVector2D kPosition;
 kPosition     = m_kObject.GetPosition ();
 kPosition [1] = 443;

  /* Modify particle system */
 m_kParticleSystem.SetDontCreate (mrFalse);
 m_kParticleSystem.SetPosition (kPosition);
}

 /* Render the ball */
void btBall::Render (void)
{
 m_kBall.Render ();
 m_kParticleSystem.Render ();
}

 /* Synchronizes the entity and the ABO position */
void btBall::Synchronize (void)
{
 mrVector2D kPosition;

  /* Set correct size for the ABO */
 m_kBall.SetSize (m_iRadius, m_iRadius);

  /* Set correct position for the ABO */
 kPosition = m_kObject.GetPosition ();
 m_kBall.SetPosition ((mrUInt32)kPosition [0], 
                      (mrUInt32)kPosition [1]);
}

 /* Update the ball */
void btBall::Update (mrReal32 fStep)
{
  /* Simulate and synchornize */
 m_kObject.Simulate (fStep);
 Synchronize ();

  /* Update timer and stop particle system if needed */
 m_fTimerCount += fStep;

 if (m_fTimerCount >= 0.25f)
 {
  m_kParticleSystem.SetDontCreate (mrTrue);
 }
 m_kParticleSystem.Simulate (fStep);
}

 /* Sets the ball speed */
void btBall::SetSpeed (mrReal32 fSpeed)
{
 m_fSpeed = fSpeed;
  /* Get the direction of the ball and scale it by the speed */
 mrVector2D kVelocity;
 kVelocity = m_kObject.GetLinearVelocity ();
 kVelocity.Normalize ();
 kVelocity *= m_fSpeed;
 m_kObject.SetLinearVelocity (kVelocity);
}

 /* Sets the ball size */
void btBall::SetSize (mrUInt32 iRadius)
{
 m_iRadius = iRadius;
}

 /* Returns the ball speed */
mrReal32 btBall::GetSpeed (void)
{
 return m_fSpeed;
}

 /* Returns the ball size */
mrUInt32 btBall::GetSize (void)
{
 return m_iRadius;
}

 /* Returns the ball entity */
mrEntity * btBall::GetObject (void)
{
 return &m_kObject;
}

 /* Returns if the ball is alive */
mrBool32 btBall::GetIsAlive (void)
{
 return m_bIsAlive;
}
