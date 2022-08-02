 /* 'mrParticleSystem.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus 2D vector header */
#include "mrVector2D.h"
 /* Mirus particle header */
#include "mrParticle.h"
 /* Mirus texture header */
#include "mrTexture.h"
 /* Mirus screen header */
#include "mrScreen.h"

 /* Include this file only once */
#pragma once

 /* Mirus Particle System class */
class mrParticleSystem
{
protected:
 mrParticleSystemParams m_kParameters;

 mrUInt32               m_iParticlesActive;
 mrParticle *           m_pkParticles;
 mrUInt32               m_iMaxParticles;
 mrTexture *            m_pkTexture;

	 /* Creation manipulation */
 mrUInt32               m_iParticlePerSecond;
 mrReal32               m_fResidue;
	mrBool32															m_bDontCreate;

public:

 mrParticleSystem (void);
 ~mrParticleSystem (void);

  /* Particle maintenance methods */
 void Create (mrParticleSystemParams & rkParameters, 
              mrUInt32 iMaxParticles, mrUInt32 iParticlePerSecond,
              mrTexture * pkTexture);
 void Simulate (mrReal32 fStep);
 void Render (void);

 void SetPosition (mrVector2D & rkPosition);
 void SetDontCreate (mrBool32 iDontCreate);
 mrVector2D GetPosition (void);
};
