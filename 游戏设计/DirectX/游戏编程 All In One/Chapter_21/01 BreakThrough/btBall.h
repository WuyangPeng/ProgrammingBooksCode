 /* 'btBall.h' */

 /* Mirus window framework header */
#include "Mirus\Mirus.h"

 /* Include this file only once */
#pragma once

 /* Break Through ball class */
class btBall
{
protected:
  /* Ball ABO */
 mrABO              m_kBall;

  /* Physics object */
 mrEntity           m_kObject;
 mrReal32           m_fSpeed;

  /* Real size of the ball */
 mrUInt32           m_iRadius;

  /* Particle system */
 mrParticleSystem   m_kParticleSystem;
 mrTimer            m_kTimer;
 mrReal32           m_fTimerCount;
 mrTexture          m_kParticleTexture;

 mrBool32           m_bIsAlive;

public:
  /* Constructor / Destructor */
 btBall (void);
 ~btBall (void);

  /* Ball manipulation routines */
 void Create (void);
 void Destroy (void);
 void Render (void);
 void Synchronize (void);
 void Update (mrReal32 fStep);

  /* Ball maintainance routines */
 void SetSpeed (mrReal32 fSpeed);
 void SetSize (mrUInt32 iRadius);
 mrReal32 GetSpeed (void);
 mrUInt32 GetSize (void);
 mrEntity * GetObject (void);
 mrBool32 GetIsAlive (void); 
};