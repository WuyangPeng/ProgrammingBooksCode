 /* 'mrABO.cpp' */

 /* Complement header file */
#include "mrABO.h"

 /* Default constructor */
mrABO::mrABO (void)
{
 m_pkAnimations      = NULL;
 m_pkTexture         = NULL;
 m_iCurrentAnimation = 0;
 m_iXPosition        = 0;
 m_iYPosition        = 0;
 m_iWidth            = 0;
 m_iHeight           = 0;
 m_fAngle            = 0;
 m_fRadius           = 0;
}

 /* Default destructor */
mrABO::~mrABO (void)
{
 if (NULL != m_pkAnimations)
 {
  delete [] m_pkAnimations;
  m_pkAnimations     = NULL;
 }
 if (NULL != m_pkTexture)
 {
  delete m_pkTexture;
  m_pkTexture        = NULL;
 }
 m_iCurrentAnimation = 0;
 m_iXPosition        = 0;
 m_iYPosition        = 0;
 m_iWidth            = 0;
 m_iHeight           = 0;
 m_fAngle            = 0;
 m_fRadius           = 0;
}

 /* Create ABO */
void mrABO::Create (mrUInt32 iAnimations, mrAnimation * pkAnimations)
{
 m_pkAnimations = new mrAnimation [iAnimations];

 mrUInt32 iAnimation;

 for (iAnimation = 0; iAnimation < iAnimations; iAnimation ++)
 {
  SetAnimation (iAnimation, &pkAnimations [iAnimation]);
 }
}

 /* Set ABO animation */
void mrABO::SetAnimation (mrUInt32 iAnimation, mrAnimation * pkAnimation)
{
 memcpy (&m_pkAnimations [iAnimation], pkAnimation, sizeof (mrAnimation));
 m_pkAnimations [iAnimation].SetCurrentFrame (0);
}

 /* Load ABO from file */
void mrABO::LoadFromFile (LPSTR lpszFilename)
{
 fstream      kABO;

 kABO.open (lpszFilename, ios::in);

 if (kABO.is_open ())
 {
   /* Get texture name and type */
  mrInt8 aTextureName [256];
  kABO >> aTextureName;
  mrUInt32 iTextureType;
  kABO >> iTextureType;

   /* Load the texture image */
  mrRGBAImage kTempImage;

  if (1 == iTextureType)
  {
   kTempImage.LoadFromBitmap (aTextureName);
  }
  if (2 == iTextureType)
  {
   kTempImage.LoadFromTarga (aTextureName);
  }

   /* Read color key information */
  mrUInt32 iRed;
  mrUInt32 iGreen;
  mrUInt32 iBlue;
  kABO >> iRed;
  kABO >> iGreen;
  kABO >> iBlue;

  kTempImage.SetColorKey ((mrUInt8)iRed, (mrUInt8)iGreen, 
                          (mrUInt8)iBlue);
  
   /* Create the texture */
  m_pkTexture = new mrTexture ();
  m_pkTexture->Create (&kTempImage);

   /* Read template set information */
  mrUInt32 iCellWidth;
  mrUInt32 iCellHeight;
  kABO >> iCellWidth;
  kABO >> iCellHeight;

   /* Create the template */
  mrTemplateSet kTempTemplateSet;
  kTempTemplateSet.Create (m_pkTexture, kTempImage.GetWidth (), 
                           kTempImage.GetHeight (), iCellWidth, 
                           iCellHeight);

   /* Read number of animations */
  mrUInt32 iNumberOfAnimations;
  kABO >> iNumberOfAnimations;

  mrAnimation * pkTempAnimations;
  pkTempAnimations = new mrAnimation [iNumberOfAnimations];

  mrUInt32 iAnimation;

   /* For each animation, read the number of frames */
  for (iAnimation = 0; iAnimation < iNumberOfAnimations; iAnimation++)
  {
   mrUInt32 iNumberOfFrames;
   kABO >> iNumberOfFrames;

   mrCellID * pkFramePosition;
   pkFramePosition = new mrCellID [iNumberOfFrames];

   mrUInt32 iPosition;

    /* For each frame, read the frames animation */
   for (iPosition = 0; iPosition < iNumberOfFrames; iPosition++)
   {
    kABO >> pkFramePosition [iPosition].m_iX;
    kABO >> pkFramePosition [iPosition].m_iY;
   }

    /* Create the animation */
   pkTempAnimations [iAnimation].Create (&kTempTemplateSet , 
                                         iNumberOfFrames, 
                                         pkFramePosition);
   delete [] pkFramePosition;
  }

   /* Create the ABO */
  Create (iNumberOfAnimations, pkTempAnimations);

  delete [] pkTempAnimations;

  kABO.close ();
 }
}

 /* Render ABO */
mrError32 mrABO::Render (void)
{
 RECT kRect;

  /* Send position and width as a rectangle */
 kRect.left   = m_iXPosition;
 kRect.top    = m_iYPosition;
 kRect.right  = m_iWidth;
 kRect.bottom = m_iHeight;

 return m_pkAnimations [m_iCurrentAnimation].Render (kRect, m_iColor, 
                                                     m_fAngle);
}

 /* Update ABO animation */
void mrABO::Update (void)
{
 m_pkAnimations [m_iCurrentAnimation].Update ();
}

void mrABO::SetCurrentAnimation (mrUInt32 iAnimation)
{
 m_iCurrentAnimation = iAnimation;
}

 /* Returns ABO current animation */
mrUInt32 mrABO::GetCurrentAnimation (void)
{
 return m_iCurrentAnimation;
}

 /* See if two ABOs collide */
mrBool32 mrABO::Collide (mrABO & rkABO, mrUInt32 iUseSphere)
{
  /* Use bounding sphere method */
 if (iUseSphere)
 {
   /* Get distance from one ABO to other */
  mrReal32 fXDelta = (mrReal32)m_iXPosition - (mrReal32)rkABO.GetXPosition ();
  mrReal32 fYDelta = (mrReal32)m_iYPosition - (mrReal32)rkABO.GetYPosition ();

  mrReal32 fDistance;
  fDistance = (mrReal32) sqrt (fXDelta * fXDelta + fYDelta * fYDelta);

  mrReal32 fRadius1, fRadius2;
 
    /* Get radius of each ABO */
  if (m_fRadius != 0)
  {
   fRadius1 = m_fRadius;
  }
  else
  {
   fRadius1 = (mrReal32) sqrt ( ((m_iWidth / 2) * (m_iWidth / 2)) + 
                                ((m_iHeight / 2) * (m_iHeight / 2)));
  }
  if (rkABO.GetRadius () != 0)
  {
   fRadius2 = rkABO.GetRadius ();
  }
  else
  {
   fRadius2 = (mrReal32) sqrt ( 
               ((rkABO.GetWidth () / 2) * (rkABO.GetWidth () / 2)) + 
               ((rkABO.GetHeight () / 2) * (rkABO.GetHeight () / 2)));
  }

   /* If distance is smaller than the sum of the radius, return false */
  if (fDistance > (fRadius1 + fRadius2))
  {
   return mrFalse;
  }
  else
  {
   return mrTrue;
  }
 }
 else
 {
   /* Bounding rectangle */
  mrInt32 iX0;
  mrInt32 iY0;
  mrInt32 iX1;
  mrInt32 iY1;

  iX0 = m_iXPosition - m_iWidth / 2;
  iY0 = m_iYPosition - m_iHeight / 2;
  iX1 = m_iXPosition + m_iWidth / 2;
  iY1 = m_iYPosition + m_iHeight / 2;

   /* Check all the vertices for containment */
  if (rkABO.ContainsPoint (iX0, iY0))
  {
   return mrTrue;
  }
  if (rkABO.ContainsPoint (iX0, iY1))
  {
   return mrTrue;
  }
  if (rkABO.ContainsPoint (iX1, iY1))
  {
   return mrTrue;
  }
  if (rkABO.ContainsPoint (iX1, iY0))
  {
   return mrTrue;
  }
  
   /* If no point was inside return false */
  return mrFalse;
 }
}

 /* Checks is a point is within the area */
mrBool32 mrABO::ContainsPoint (mrInt32 iX, mrInt32 iY)
{
  /* Bounding rectangle */
 mrInt32 iX0;
 mrInt32 iY0;
 mrInt32 iX1;
 mrInt32 iY1;

 iX0 = m_iXPosition - m_iWidth / 2;
 iY0 = m_iYPosition - m_iHeight / 2;
 iX1 = m_iXPosition + m_iWidth / 2;
 iY1 = m_iYPosition + m_iHeight / 2;

  /* See if point is inside the rectangle */
 if ((iX >= iX0) && (iX <= iX1))
 {
  if ((iY >= iY0) && (iY <= iY1))
  {
   return mrTrue;
  }
 }
 return mrFalse;
}

 /* Sets ABO position */
void mrABO::SetPosition (mrUInt32 iX, mrUInt32 iY)
{
 m_iXPosition = iX;
 m_iYPosition = iY;
}

 /* Sets ABO size */
void mrABO::SetSize (mrUInt32 iWidth, mrUInt32 iHeight)
{
 m_iWidth  = iWidth;
 m_iHeight = iHeight;
}

 /* Sets ABO color */
void mrABO::SetColor (mrUInt8 iAlpha, mrUInt8 iRed, mrUInt8 iGreen, 
                      mrUInt8 iBlue)
{
 m_iColor = D3DCOLOR_ARGB (iAlpha, iRed, iGreen, iBlue);
}

 /* Sets ABO color */
void mrABO::SetRadius (mrReal32 fRadius)
{
 m_fRadius = fRadius;
}

 /* Rotate ABO */
void mrABO::Rotate (mrReal32 fAngle, mrUInt32 iAccumulate)
{
 if (iAccumulate)
 {
  m_fAngle += fAngle;
 }
 else
 {
  m_fAngle = fAngle;
 }
}

 /* Returns ABO horizontal position */
mrUInt32 mrABO::GetXPosition (void)
{
 return m_iXPosition;
}

 /* Returns ABO vertical position */
mrUInt32 mrABO::GetYPosition (void)
{
 return m_iYPosition;
}

 /* Returns ABO height */
mrUInt32 mrABO::GetHeight (void)
{
 return m_iHeight;
}

 /* Returns ABO width */
mrUInt32 mrABO::GetWidth (void)
{
 return m_iWidth;
}

 /* Returns ABO color */
mrUInt32 mrABO::GetColor (void)
{
 return m_iColor;
}

 /* Returns ABO direction */
mrReal32 mrABO::GetDirection (void)
{
 return m_fAngle;
}

 /* Returns ABO collision radius */
mrReal32 mrABO::GetRadius (void)
{
 return m_fRadius;
}
