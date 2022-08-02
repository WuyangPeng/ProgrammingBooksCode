 /* 'mrTexture.cpp' */

 /* Complement header file */
#include "mrTexture.h"

 /* Static texture members */
mrUInt32    mrTexture::m_iActiveTexture  = -1;
mrUInt32    mrTexture::m_iCurrentID      = 0;

 /* Default constructor */
mrTexture::mrTexture (void)
{
 m_pkD3DTexture = NULL;
 m_pkRawImage   = NULL;

 m_iHasAlpha    = mrFalse;
 m_iID          = 0;
}

 /* Default destructor */
mrTexture::~mrTexture (void)
{
 if (m_pkD3DTexture != NULL)
 {
  m_pkD3DTexture->Release ();
  m_pkD3DTexture = NULL;
 }
 if (m_pkRawImage != NULL)
 {
  delete m_pkRawImage;
  m_pkRawImage   = NULL;
 }
}

 /* Creates the texture */
mrError32 mrTexture::Create (mrRGBAImage * pkRawImage)
{
  /* Update methods */
 m_iID = m_iCurrentID;
 m_iCurrentID ++;

  /* Set the texture raw image and update the Direct3D texture */
 SetRawImage (pkRawImage);

 return Update ();
}

 /* Updates the Direct3D texture */
mrError32 mrTexture::Update (void)
{
 if (m_pkRawImage == NULL)
 {
  return mrErrorInvalidRawImage;
 }

 if (m_pkD3DTexture != NULL)
 {
  m_pkD3DTexture->Release ();
  m_pkD3DTexture = NULL;
 }
 
 m_iHasAlpha = mrTrue;
  /* We are in 32 bit mode */
 if (32 == mrScreen::GetSingleton ()->GetBitdepth ())
 {
   /* Try to create alpha texture */
  if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->CreateTexture (
                   m_pkRawImage->GetWidth (),
                   m_pkRawImage->GetHeight (), 
                   0, 0,
                   D3DFMT_A8R8G8B8,
                   D3DPOOL_MANAGED,
                   &m_pkD3DTexture)) )
  {
    /* If failed, use back buffer format for texture */
   if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->CreateTexture (
                    m_pkRawImage->GetWidth (),
                    m_pkRawImage->GetHeight (), 
                    0, 0,
                    (D3DFORMAT) mrScreen::GetSingleton ()->GetFormat (),
                    D3DPOOL_MANAGED,
                    &m_pkD3DTexture)) )
   {
    m_pkD3DTexture = NULL;
    m_iHasAlpha = mrFalse;
    return mrErrorCreateTexture;
   }
  }
 }
  /* We are in 16 bit mode */
 if (16 == mrScreen::GetSingleton ()->GetBitdepth ())
 {
   /* Try to create alpha texture */
  if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->CreateTexture (
                   m_pkRawImage->GetWidth (),
                   m_pkRawImage->GetHeight (), 
                   0, 0,
                   D3DFMT_A4R4G4B4,
                   D3DPOOL_MANAGED,
                   &m_pkD3DTexture)) )
  {
   m_iHasAlpha = mrFalse;
    /* If failed, use back buffer format for texture */
   if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->CreateTexture (
                    m_pkRawImage->GetWidth (),
                    m_pkRawImage->GetHeight (), 
                    0, 0,
                    (D3DFORMAT) mrScreen::GetSingleton ()->GetFormat (),
                    D3DPOOL_MANAGED,
                    &m_pkD3DTexture)) )
   {
    m_pkD3DTexture = NULL;
    return mrErrorCreateTexture;
   }
  }
 }

  /* Lock Texture */
 D3DLOCKED_RECT kLockedRect;
 m_pkD3DTexture->LockRect (0, &kLockedRect, NULL, 0);

  /* Pointers to locked texture */
 WORD * pi16TextureBuffer;
 DWORD * pi32TextureBuffer;

  /* Use correct pointer depending on depth */
 if (mrScreen::GetSingleton ()->GetBitdepth () == 16)
 {
   /* Cast a 16-bit pointer to point to the first pixel */
  pi16TextureBuffer = (WORD *) kLockedRect.pBits;
 }
 else 
 {
   /* Cast a 32-bit pointer to point to the first pixel */
  pi32TextureBuffer = (DWORD *) kLockedRect.pBits;
 }

  /* Fill «the surface */
 mrUInt32 iX, iY;
 mrUInt32 iDepth;

  /* Get depth in bytes and calculate pitch */
 iDepth = mrScreen::GetSingleton ()->GetBitdepth () / 8;
 mrUInt32 iPitch = kLockedRect.Pitch / iDepth;

 mrUInt8  iRed, iGreen, iBlue, iAlpha;
 mrUInt32 iColor;

 for (iY=0; iY < m_pkRawImage->GetHeight (); iY++)
 {
  for (iX=0; iX < m_pkRawImage->GetWidth (); iX++)
  {
    /* Get color components */
   iColor = m_pkRawImage->GetColor (iX, iY);

   iRed   = (mrUInt8)((iColor & 0xFF000000) >> 24);
   iGreen = (mrUInt8)((iColor & 0x00FF0000) >> 16);
   iBlue  = (mrUInt8)((iColor & 0x0000FF00) >> 8);
   iAlpha = (mrUInt8)((iColor & 0x000000FF));
 
    /* Write color to surface buffer according to mode*/
   if (mrScreen::GetSingleton ()->GetBitdepth () == 16)
   {
    if (mrTrue == m_iHasAlpha)
    {
      pi16TextureBuffer [iX + iY * iPitch] = 
       (mrUInt16)((iAlpha * ((1 << 4)-1) / 255 << 12) | 
                  (iRed   * ((1 << 4)-1) / 255 << 8) | 
                  (iGreen * ((1 << 4)-1) / 255 << 4) | 
                  (iBlue  * ((1 << 4)-1) / 255 ));
    }
    else
    {
     if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_R5G6B5)
     {
      pi16TextureBuffer [iX + iY * iPitch] = 
       (mrUInt16)((iRed   * ((1 << 5)-1) / 255 << 11) | 
                  (iGreen * ((1 << 6)-1) / 255 << 5) | 
                  (iBlue  * ((1 << 5)-1) / 255 ));
     }
     if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_X1R5G5B5)
     {
      pi16TextureBuffer [iX + iY * iPitch] = 
       (mrUInt16)((iRed   * ((1 << 5)-1) / 255  << 10) |
                  (iGreen * ((1 << 5)-1) / 255  << 5) |
                  (iBlue  * ((1 << 5)-1) / 255 ));
     }
     if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_A1R5G5B5)
     {
      pi16TextureBuffer [iX + iY * iPitch] = 
       (mrUInt16)(((iAlpha > 0) ? 1 : 0 << 15) |
                   (iRed   * ((1 << 5)-1) / 255  << 10) |
                   (iGreen * ((1 << 5)-1) / 255  << 5) |
                   (iBlue  * ((1 << 5)-1) / 255 ));
     }
    }
   }
   else
   {
    pi32TextureBuffer [iX + iY * iPitch] = 
                   D3DCOLOR_ARGB (iAlpha, iRed, iGreen, iBlue);
   }
  }
 }

  /* Unlock */
 m_pkD3DTexture->UnlockRect (0);

 return mrNoError;
}

 /* Set the surface raw image */
void mrTexture::SetRawImage (mrRGBAImage * pkRawImage)
{
 if (m_pkRawImage == NULL)
 {
  m_pkRawImage = new mrRGBAImage ();
 }

 m_pkRawImage->SetWidth (pkRawImage->GetWidth ());
 m_pkRawImage->SetHeight (pkRawImage->GetHeight ());
 m_pkRawImage->SetImageBuffer (pkRawImage->GetImageBuffer ());
}

 /* Returns the surface raw image */
mrRGBAImage * mrTexture::GetRawImage (void)
{
 return m_pkRawImage;
}

 /* Set Direct3D active texture */
void mrTexture::SetActiveTexture (void)
{
 if (m_iActiveTexture != m_iID)
 {
  mrScreen::GetSingleton ()->GetDevice ()->SetTexture (0, m_pkD3DTexture);
  m_iActiveTexture = m_iID;
 }
}

 /* Returns texture ID */
mrUInt32 mrTexture::GetID (void)
{
 return m_iID;
}

 /* Returns Direct3D active texture */
mrUInt32 mrTexture::GetActiveTexture (void)
{
 return m_iActiveTexture;
}
