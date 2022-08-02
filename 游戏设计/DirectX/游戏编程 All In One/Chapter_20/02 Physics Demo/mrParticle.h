 /* 'mrParticle.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus 2D vector header */
#include "mrVector2D.h"
 /* Mirus screen header */
#include "mrScreen.h"

 /* Include this file only once */
#pragma once

 /* Mirus Particle System setup class */
class mrParticleSystemParams
{
public: 
 mrVector2D     m_kPosition;

 mrReal32       m_fSize;
 mrReal32       m_fFinalSize;

 mrUInt32       m_iColor;
 mrUInt32       m_iFinalColor;

 mrReal32       m_fLifetime;

 mrReal32       m_fDispersion;
 mrReal32       m_fSpeed;
};

 /* Mirus Particle class */
class mrParticle
{
protected:
 mrVector2D     m_kPosition;
 mrVector2D     m_kOldPosition;

 mrVector2D     m_kVelocity;

 mrReal32       m_fSize;
 mrReal32       m_fFinalSize;

 mrReal32       m_fLife;
 mrReal32       m_fLifetime;

 mrUInt32       m_iColor;
 mrUInt32       m_iFinalColor;

  /* Effects attributes */
 mrReal32       m_fDispersion;
 mrReal32       m_fSpeed;

public:
   /* Constructor / Destructor */
 mrParticle (void);
 ~mrParticle (void);

 void Simulate (mrReal32 fStep);
 mrError32 Render (mrVector2D & rkPosition);

  /* Particle maintenance methods */
 void Create (mrParticleSystemParams & rkParams); 
 mrReal32 GetLife (void);
};
