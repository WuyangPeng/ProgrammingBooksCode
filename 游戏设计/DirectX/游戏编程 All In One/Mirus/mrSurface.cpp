 /* 'mrSurface.cpp' */

 /* Complement header file */
#include "mrSurface.h"

 /* Default constructor */
mrSurface::mrSurface (void)
{
 m_pkD3DSurface = NULL;
 m_pkRawImage   = NULL;
}

 /* Default destructor */
mrSurface::~mrSurface (void)
{
 if (m_pkD3DSurface != NULL)
 {
  m_pkD3DSurface->Release ();
  m_pkD3DSurface = NULL;
 }
 if (m_pkRawImage != NULL)
 {
  delete m_pkRawImage;
  m_pkRawImage   = NULL;
 }
}

 /* Creates the surface */
mrError32 mrSurface::Create (mrRGBAImage * pkRawImage)
{
  /* Set the surface raw image and update the Direct3D surface */
 SetRawImage (pkRawImage);

 return Update ();
}

 /* Updates the Direct3D surface */
mrError32 mrSurface::Update (void)
{
 if (m_pkD3DSurface != NULL)
 {
  m_pkD3DSurface->Release ();
		m_pkD3DSurface = NULL;
 }

 if (m_pkRawImage == NULL)
 {
  return mrErrorInvalidRawImage;
 }
 
  /* Create the surface */
 if (FAILED(mrScreen::GetSingleton ()->GetDevice ()->CreateImageSurface(
                  m_pkRawImage->GetWidth (),
                  m_pkRawImage->GetHeight (), 
                  (D3DFORMAT) mrScreen::GetSingleton ()->GetFormat (),
                  &m_pkD3DSurface ) ) )

 {
  m_pkD3DSurface = NULL;
  return mrErrorCreateImageSurface;
 }

  /* Lock surface */
 D3DLOCKED_RECT kLockedRect;
 m_pkD3DSurface->LockRect (&kLockedRect, NULL, 0);

  /* Pointers to locked surface */
 WORD * pi16SurfaceBuffer;
 DWORD * pi32SurfaceBuffer;

  /* Use correct pointer depending on depth */
 if (mrScreen::GetSingleton ()->GetBitdepth () == 16)
 {
   /* Cast a pointer to point to the first pixel */
  pi16SurfaceBuffer = (WORD *) kLockedRect.pBits;
 }
 else 
 {
   /* Cast a pointer to point to the first pixel */
  pi32SurfaceBuffer = (DWORD *) kLockedRect.pBits;
 }

  /* Fill surface */
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
    if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_R5G6B5)
    {
     pi16SurfaceBuffer [iX + iY * iPitch] = 
              (mrUInt16)( (iRed   * ((1 << 5)-1) / 255 << 11) | 
                  (iGreen * ((1 << 6)-1) / 255  << 5) | 
                  (iBlue  * ((1 << 5)-1) / 255 ));
    }
    if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_X1R5G5B5)
    {
     pi16SurfaceBuffer [iX + iY * iPitch] = 
      (mrUInt16)((iRed   * ((1 << 5)-1) / 255  << 10) |
                  (iGreen * ((1 << 5)-1) / 255  << 5) |
                  (iBlue  * ((1 << 5)-1) / 255 ));
    }
    if (mrScreen::GetSingleton ()->GetFormat () == D3DFMT_A1R5G5B5)
    {
     pi16SurfaceBuffer [iX + iY * iPitch] = 
      (mrUInt16)(((iAlpha > 0) ? 1 : 0 << 15) |
                  (iRed   * ((1 << 5)-1) / 255  << 10) |
                  (iGreen * ((1 << 5)-1) / 255  << 5) |
                  (iBlue  * ((1 << 5)-1) / 255 ));
    }
   }
   else
   {
    pi32SurfaceBuffer [iX + iY * iPitch] = 
     D3DCOLOR_ARGB (iAlpha, iRed, iGreen, iBlue);
   }
  }
 }
  
  /* Unlock */
 m_pkD3DSurface->UnlockRect ();

 return mrNoError;
}

 /* Draw the surface */
mrError32 mrSurface::Render (POINT * pkDestPoint, RECT * pkSourceRect)
{
  /* Get back buffer */
 if (m_pkD3DSurface != NULL)
 {
  LPDIRECT3DSURFACE8 pBackBuffer;
  mrScreen::GetSingleton ()->GetDevice ()->GetBackBuffer (
                                            0, D3DBACKBUFFER_TYPE_MONO,
                                            &pBackBuffer);
   /* Copy the surface to the screen */
  if (pkSourceRect != NULL)
  {
   mrScreen::GetSingleton ()->GetDevice ()->CopyRects (m_pkD3DSurface, pkSourceRect, 1,
                                         pBackBuffer, pkDestPoint);
  }
  else
  {
   RECT kImageRect;
    /* Use entire image */
   kImageRect.left   = 0;
   kImageRect.top    = 0;
   kImageRect.right  = m_pkRawImage->GetWidth () - 1;
   kImageRect.bottom = m_pkRawImage->GetHeight () - 1;

   mrScreen::GetSingleton ()->GetDevice ()->CopyRects (m_pkD3DSurface, &kImageRect, 1,
                                         pBackBuffer, pkDestPoint);
  }
   /* Release back buffer */
  pBackBuffer->Release ();
 }
 return mrNoError;
}

 /* Set the surface raw image */
void mrSurface::SetRawImage (mrRGBAImage * pkRawImage)
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
mrRGBAImage * mrSurface::GetRawImage (void)
{
 return m_pkRawImage;
}
