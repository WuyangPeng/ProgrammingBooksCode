 /* 'mrAnimation.cpp' */

 /* Complement header file */
#include "mrAnimation.h"

 /* Default constructor */
mrAnimation::mrAnimation (void)
{
 m_pkFramesID    = NULL;
 m_iFrames       = 0;
 m_iCurrentFrame = 0;
}

 /* Default destructor */
mrAnimation::~mrAnimation (void)
{
 m_pkFramesID    = NULL;
 m_iFrames       = 0;
 m_iCurrentFrame = 0;

 if (NULL != m_pkFramesID)
 {
  delete [] m_pkFramesID;
 }
}

 /* Create animation */
void mrAnimation::Create (mrTemplateSet * pkTemplateSet, 
                          mrUInt32 iFrames, mrCellID * pkFramesID)
{
 m_iFrames       = iFrames;
 m_iCurrentFrame = 0;

 m_pkFramesID = new mrCellID [iFrames];

 memcpy (&m_kTemplateSet, pkTemplateSet, sizeof (mrTemplateSet));
 memcpy (m_pkFramesID, pkFramesID, sizeof (mrCellID) * iFrames);
}

 /* Update the animation (moves frame) */
void mrAnimation::Update (void)
{
 m_iCurrentFrame ++;
 if (m_iCurrentFrame >= m_iFrames)
 {
  m_iCurrentFrame = 0;
 }
}

 /* Render the animation */
mrError32 mrAnimation::Render (RECT kDestRect, mrUInt32 iColor, 
                               mrReal32 fAngle)
{
 mrRectText kTextCoord;

 mrReal32 fX1;
 mrReal32 fY1;
 mrReal32 fX2;
 mrReal32 fY2;
 mrReal32 fX3;
 mrReal32 fY3;
 mrReal32 fX4;
 mrReal32 fY4;
 
 if (fAngle != 0)
 {
  /* Convert degrees to radians */
 fAngle *= 0.0174f;

  /* Create relative rectangle */
 RECT       kRotRect;
 kRotRect.left   = - (kDestRect.right >> 1);
 kRotRect.top    = - (kDestRect.bottom >> 1);
 kRotRect.right  =   (kDestRect.right >> 1);
 kRotRect.bottom =   (kDestRect.bottom >> 1);
 
  /* Rotate all the vertices */
 fX1 = (mrReal32)(kRotRect.left * cos (fAngle) + 
                           kRotRect.top * sin (fAngle));
 fY1 = (mrReal32)(kRotRect.left * sin (fAngle) - 
                  kRotRect.top * cos (fAngle));

 fX2 = (mrReal32)(kRotRect.right * cos (fAngle) + 
                           kRotRect.top * sin (fAngle));
 fY2 = (mrReal32)(kRotRect.right * sin (fAngle) - 
                  kRotRect.top * cos (fAngle));

 fX3 = (mrReal32)(kRotRect.left * cos (fAngle) + 
                  kRotRect.bottom * sin (fAngle));
 fY3 = (mrReal32)(kRotRect.left * sin (fAngle) - 
                           kRotRect.bottom * cos (fAngle));

 fX4 = (mrReal32)(kRotRect.right * cos (fAngle) + 
                  kRotRect.bottom * sin (fAngle));
 fY4 = (mrReal32)(kRotRect.right * sin (fAngle) - 
                  kRotRect.bottom * cos (fAngle));
 }
  /* Don't rotate */
 else
 {
  fX1 = (mrReal32) -(kDestRect.right >> 1);
  fY1 = (mrReal32)  (kDestRect.bottom >> 1);
  fX2 = (mrReal32)  (kDestRect.right >> 1);
  fY2 = (mrReal32)  (kDestRect.bottom >> 1);
  fX3 = (mrReal32) -(kDestRect.right >> 1);
  fY3 = (mrReal32) -(kDestRect.bottom >> 1);
  fX4 = (mrReal32)  (kDestRect.right >> 1);
  fY4 = (mrReal32) -(kDestRect.bottom >> 1);
 }

  /* Translate to absolute coordinates */
 fX1 += kDestRect.left;
 fY1 += kDestRect.top;
 fX2 += kDestRect.left;
 fY2 += kDestRect.top;
 fX3 += kDestRect.left;
 fY3 += kDestRect.top;
 fX4 += kDestRect.left;
 fY4 += kDestRect.top;

  /* Get UV rectangle from template set */
 m_kTemplateSet.GetUV (m_pkFramesID [m_iCurrentFrame], &kTextCoord);

  /* Create rectangle vertices */
 mrVertex kVertices [] =
 {  /* x, y, z, w, color, texture coordinates (u,v) */
  {fX3, fY3, 0, 1.0f, iColor, kTextCoord.m_fLeft, kTextCoord.m_fTop},
  {fX4, fY4, 0, 1.0f, iColor, kTextCoord.m_fRight, kTextCoord.m_fTop},
  {fX2, fY2, 0, 1.0f, iColor, kTextCoord.m_fRight, kTextCoord.m_fBottom},
  {fX1, fY1, 0, 1.0f, iColor, kTextCoord.m_fLeft, kTextCoord.m_fBottom},
 };
 
  /* Set as active texture */
 m_kTemplateSet.SetActiveTexture ();

  /* Draw the rotated rectangle */
 mrScreen::GetSingleton ()->GetDevice ()->SetVertexShader (
                                      D3DFVF_MIRUSVERTEX);
 if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->DrawPrimitiveUP (
                                      D3DPT_TRIANGLEFAN, 2, kVertices, 
                                      sizeof (mrVertex))) )
 {
  return mrErrorDrawPrimitive;
 }

 return mrNoError;
}

 /* Sets the current frame */
void mrAnimation::SetCurrentFrame (mrUInt32 iFrame)
{
 m_iCurrentFrame = iFrame;
}

 /* Returns the current frame */
mrUInt32 mrAnimation::GetCurrentFrame (void)
{
 return m_iCurrentFrame;
} 
