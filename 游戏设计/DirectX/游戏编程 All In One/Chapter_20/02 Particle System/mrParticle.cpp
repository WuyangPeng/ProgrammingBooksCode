 /* 'mrParticle.cpp' */

 /* Complement header file */
#include "mrParticle.h"

 /* Default constructor */
mrParticle::mrParticle (void)
{
 m_kPosition      = mrVector2D (0, 0);
 m_kOldPosition   = mrVector2D (0, 0);
 m_kVelocity      = mrVector2D (0, 0);
 m_fSize          = 0;
 m_fFinalSize     = 0;
 m_fLife          = 1.0f;
 m_iColor         = 0;
 m_iFinalColor    = 0;
 m_fDispersion    = 0;
 m_fSpeed         = 0;
}

 /* Default destructor */
mrParticle::~mrParticle (void)
{
 m_kPosition      = mrVector2D (0, 0);
 m_kOldPosition   = mrVector2D (0, 0);
 m_kVelocity      = mrVector2D (0, 0);
 m_fSize          = 0;
 m_fFinalSize     = 0;
 m_fLifetime      = 0;
 m_fLife          = 1.0f;
 m_iColor         = 0;
 m_iFinalColor    = 0;
 m_fDispersion    = 0;
 m_fSpeed         = 0;
}

 /* Simulate (integrate) the particle */
void mrParticle::Simulate (mrReal32 fStep)
{
  /* Integrate variables */
 m_kOldPosition = m_kPosition;
 m_kPosition   += m_kVelocity * fStep;
 m_fLife       += fStep / m_fLifetime;
}

 /* Render the particle */
mrError32 mrParticle::Render (mrVector2D & rkPosition)
{
 mrUInt32 iColor;
 mrReal32 fSize;
 
 mrUInt8 fRed;
 mrUInt8 fGreen;
 mrUInt8 fBlue;
 mrUInt8 fAlpha;

  /* Get the new color of each component */
 fAlpha = (mrUInt8) (((m_iColor & 0xFF000000) >> 24) + 
         ((mrReal32) ((m_iFinalColor & 0xFF000000) >> 24) - 
          (mrReal32) ((m_iColor & 0xFF000000) >> 24)) * m_fLife);

 fRed   = (mrUInt8) (((m_iColor & 0x00FF0000) >> 16) + 
         ((mrReal32) ((m_iFinalColor & 0x00FF0000) >> 16) - 
          (mrReal32) ((m_iColor & 0x00FF0000) >> 16)) * m_fLife);

 fGreen = (mrUInt8) (((m_iColor & 0x0000FF00) >> 8) + 
         ((mrReal32) ((m_iFinalColor & 0x0000FF00) >> 8) - 
          (mrReal32) ((m_iColor & 0x0000FF00) >> 8)) * m_fLife);

 fBlue  =  (mrUInt8) ((m_iColor & 0x000000FF) + 
          ((mrReal32) (m_iFinalColor & 0x000000FF) - 
           (mrReal32) (m_iColor & 0x000000FF)) * m_fLife);

 iColor = D3DCOLOR_RGBA (fRed, fGreen, fBlue, fAlpha);
  /* Get the new size */
 fSize = m_fSize + ((m_fFinalSize - m_fSize) * m_fLife);

  /* Move to absolute position */
 mrReal32 fX = m_kPosition [0] + rkPosition [0];
 mrReal32 fY = m_kPosition [1] + rkPosition [1];

 mrVertex kVertices [] =
 {  /* x, y, z, w, color, texture coordinates (u,v) */
  {fX - fSize, fY - fSize, 0, 1.0f, iColor, 0, 0},
  {fX + fSize, fY - fSize, 0, 1.0f, iColor, 1, 0},
  {fX + fSize, fY + fSize, 0, 1.0f, iColor, 1, 1},
  {fX - fSize, fY + fSize, 0, 1.0f, iColor, 0, 1},
 };
  /* Render particle */
 if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->DrawPrimitiveUP (
                                    D3DPT_TRIANGLEFAN, 2, 
                                    kVertices, sizeof (mrVertex))) )
 {
  return mrErrorDrawPrimitive;
 }

 return mrNoError;
}

 /* Create the particle */
void mrParticle::Create (mrParticleSystemParams & rkParams)
{
  /* Create the particle with the given parameters*/
 m_kPosition      = mrVector2D (0,0);
 m_kOldPosition   = mrVector2D (0,0);
 m_fSize          = rkParams.m_fSize;
 m_fFinalSize     = rkParams.m_fFinalSize;
 m_fLife          = 0;
 m_fLifetime      = rkParams.m_fLifetime;

 m_iColor         = rkParams.m_iColor;
 m_iFinalColor    = rkParams.m_iFinalColor;

 m_fDispersion    = rkParams.m_fDispersion;
 m_fSpeed         = rkParams.m_fSpeed;

  /* Set the particle direction depending on the dispersion 
     If dispersion is one, then a full circle is used, if 
     dispersion is zero, particles will be sent straigth down */

  /* Get circle of dispersion */
 mrReal32 fDispersion;
 mrReal32 fAngle;

 fDispersion = (1 - (2 * ((mrReal32)rand () / (mrReal32)RAND_MAX))) *
               (180 * 0.0174f);
 fAngle = (3.14159f / 2.0f) + fDispersion * m_fDispersion;

  /* Calculate the directions */
 m_kVelocity [0] = (mrReal32)cos (fAngle);
 m_kVelocity [1] = (mrReal32)sin (fAngle);

  /* Now we set the particle speed */
 mrReal32 fNewSpeed;
 fNewSpeed = m_fSpeed * 100 + (rand () / RAND_MAX) * m_fSpeed * 100;
 m_kVelocity *= fNewSpeed;
}

 /* Returns particle life */
mrReal32 mrParticle::GetLife (void)
{
 return m_fLife;
}
