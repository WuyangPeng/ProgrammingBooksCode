 /* 'mrParticleSystem.cpp' */

 /* Complement header file */
#include "mrParticleSystem.h"

 /* Default constructor */
mrParticleSystem::mrParticleSystem (void)
{
 ZeroMemory (&m_kParameters, sizeof (mrParticleSystemParams));
 m_iParticlesActive   = 0;
 m_iMaxParticles      = 0;
 m_iParticlePerSecond = 0;
 m_fResidue           = 0;
	m_bDontCreate								= mrFalse;
 m_pkTexture          = NULL;
 m_pkParticles        = NULL;
}

 /* Default destructor */
mrParticleSystem::~mrParticleSystem (void)
{
 ZeroMemory (&m_kParameters, sizeof (mrParticleSystemParams));
 m_iParticlesActive   = 0;
 m_iMaxParticles      = 0;
 m_iParticlePerSecond = 0;
 m_fResidue           = 0;
	m_bDontCreate								= mrFalse;
 
 m_pkTexture          = NULL;

  /* If there are particles, delete them */
 if (NULL != m_pkParticles)
 { 
  delete [] m_pkParticles;
  m_pkParticles = NULL;
 }
}

 /* Create the particle system */
void mrParticleSystem::Create (mrParticleSystemParams & rkParameters,
                               mrUInt32 iMaxParticles,
                               mrUInt32 iParticlePerSecond,
                               mrTexture * pkTexture)
{
  /* Create the particle system with the required attributes */
 memcpy (&m_kParameters, &rkParameters, sizeof(mrParticleSystemParams));
 m_pkParticles        = new mrParticle [iMaxParticles];
 m_iMaxParticles      = iMaxParticles;
 m_iParticlePerSecond = iParticlePerSecond;
 m_pkTexture          = pkTexture;
}

 /* Simulate the particle system */
void mrParticleSystem::Simulate (mrReal32 fStep)
{
 mrUInt32 iParticle;
 mrInt32  iParticlesToCreate;

 iParticlesToCreate = 0;

  /* Check how many particles we need to create */
 iParticlesToCreate = mrUInt32(m_iParticlePerSecond * fStep + m_fResidue);
  /* Store residue of particles (partial particles) */
 m_fResidue = (m_iParticlePerSecond * fStep + m_fResidue) - iParticlesToCreate;

 for (iParticle = 0; iParticle < m_iMaxParticles; iParticle++)
 {
   /* Simulate the particle */
  if (m_pkParticles [iParticle].GetLife () < 1.0f) 
  {
   m_pkParticles [iParticle].Simulate (fStep);
  }
   /* If particle is dead, try to recreate it */
  else
  {
			if (mrFalse == m_bDontCreate)
			{
					/* Only create the particle if we haven't reached the limit */
				if (iParticlesToCreate > 0)
				{
					m_pkParticles [iParticle].Create (m_kParameters);
					iParticlesToCreate --;
				}
			}
  }
 }
}

 /* Render particle system */
void mrParticleSystem::Render (void)
{
 mrUInt32   iParticle;
  /* Set as active texture */
 m_pkTexture->SetActiveTexture ();

  /* Set alpha blending to particle mode */
 mrScreen::GetSingleton ()->GetDevice ()->SetRenderState (
                            D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 mrScreen::GetSingleton ()->GetDevice ()->SetRenderState (
                            D3DRS_DESTBLEND, D3DBLEND_ONE);

  /* Draw the particles */
 mrScreen::GetSingleton ()->GetDevice ()->SetVertexShader (
                                      D3DFVF_MIRUSVERTEX);

  /* Render each particle */
 for (iParticle = 0; iParticle < m_iMaxParticles; iParticle++)
 {
  if (m_pkParticles [iParticle].GetLife () < 1.0f) 
  {
   m_pkParticles [iParticle].Render (m_kParameters.m_kPosition);
  }
 }

   /* Set alpha blending to normal mode */
 mrScreen::GetSingleton ()->GetDevice ()->SetRenderState (
                            D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 mrScreen::GetSingleton ()->GetDevice ()->SetRenderState (
                            D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

 /* Set particle emmiter position */
void mrParticleSystem::SetPosition (mrVector2D & rkPosition)
{
 m_kParameters.m_kPosition = rkPosition;
}

 /* Set particle creation */
void mrParticleSystem::SetDontCreate (mrBool32 iDontCreate)
{
 m_bDontCreate = iDontCreate;
}


 /* Returns particle emmiter position */
mrVector2D mrParticleSystem::GetPosition (void)
{
 return m_kParameters.m_kPosition;
}
