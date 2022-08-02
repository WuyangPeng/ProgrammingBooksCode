 /* 'mrScreen.cpp' */

 /* Complement header file */
#include "mrScreen.h"

 /* Singleton object */
mrScreen * mrScreen::m_pkSingleton = NULL;

 /* Default constructor */
mrScreen::mrScreen (void)
{
 m_pkD3D       = NULL;
 m_pkD3DDevice = NULL;
 m_hWindow     = NULL;
 m_iFPS        = 0;

 assert (!m_pkSingleton);
 m_pkSingleton = this;
}

 /* Assigment constructor */
mrScreen::mrScreen (HWND hWindow)
{
 m_pkD3D       = NULL;
 m_pkD3DDevice = NULL;
 m_iFPS        = 0;
 m_hWindow     = hWindow;

 assert (!m_pkSingleton);
 m_pkSingleton = this;

 Init (hWindow);
}

 /* Default destructor */
mrScreen::~mrScreen (void)
{
 if (NULL != m_pkD3DDevice)
 {
  m_pkD3DDevice->Release ();
  m_pkD3DDevice = NULL;
 }
 if (NULL != m_pkD3D)
 {
  m_pkD3D->Release ();
  m_pkD3D = NULL;
 }
 m_iFPS        = 0;

 assert (m_pkSingleton);
 m_pkSingleton = NULL;
}

 /* Initialize Direct3D */
mrError32 mrScreen::Init (HWND hWindow)
{
  /* Create Direct3D object */
 m_pkD3D = Direct3DCreate8 (D3D_SDK_VERSION);
 m_hWindow     = hWindow;

 if (NULL == m_pkD3D)
 {
  return mrErrorInitDirect3D;
 }
 return mrNoError;
}

 /* Sets the display mode / create the Direct3D device */
mrError32 mrScreen::SetMode (mrUInt32 iFullscreen, mrUInt16 iWidth, 
                             mrUInt16 iHeight, mrUInt16 iDepth, 
                             bool bHardware)
{
 D3DPRESENT_PARAMETERS kPresentParams; 
 mrUInt32              iDeviceType;

  /* Set type of device to create (hardware or software */
 if (!bHardware)
 {
  iDeviceType = D3DDEVTYPE_REF;
 }
 else
 {
  iDeviceType = D3DDEVTYPE_HAL;
 }

  /* Reset present parameters and set swap effect */
 ZeroMemory (&kPresentParams, sizeof (D3DPRESENT_PARAMETERS) );
 kPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
 
  /* If windowed mode */
 if (!iFullscreen)
 {
  D3DDISPLAYMODE kCurrentMode;

   /* Get current mode information */
  if (FAILED (m_pkD3D->GetAdapterDisplayMode (D3DADAPTER_DEFAULT,
              &kCurrentMode) ))
  {
   return mrErrorGetAdapterDisplayMode;
  }

   /* Set windowed mode and backbuffer format compatible with
      current format */
  kPresentParams.Windowed         = true;
  kPresentParams.BackBufferCount  = 1;
  kPresentParams.BackBufferFormat = kCurrentMode.Format;

   /* Try to create device */
  if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                (D3DDEVTYPE) iDeviceType, 
                                m_hWindow,
                                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                &kPresentParams, &m_pkD3DDevice ) ))
  {
   return mrErrorCreateDevice;
  }
 }
 else
 {
   /* Set full screen mode and full screen information */
  kPresentParams.Windowed         = false;
  kPresentParams.BackBufferCount  = 1;
  kPresentParams.BackBufferWidth  = iWidth;
  kPresentParams.BackBufferHeight = iHeight;

  kPresentParams.FullScreen_RefreshRateInHz = 
                                 D3DPRESENT_RATE_DEFAULT;
  kPresentParams.FullScreen_PresentationInterval = 
                                 D3DPRESENT_INTERVAL_DEFAULT;

   /* If 16 bit, try to create the device using different 16 bit pixel
      color formats */
  if (iDepth == 16)
  {
   kPresentParams.BackBufferFormat = D3DFMT_R5G6B5;
   if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                   (D3DDEVTYPE) iDeviceType, 
                                   m_hWindow,
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &kPresentParams, &m_pkD3DDevice ) ))
   {
    kPresentParams.BackBufferFormat = D3DFMT_X1R5G5B5;
    if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                    (D3DDEVTYPE) iDeviceType, 
                                    m_hWindow,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                    &kPresentParams, &m_pkD3DDevice ) ))
    {
     kPresentParams.BackBufferFormat = D3DFMT_A1R5G5B5;
     if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                     (D3DDEVTYPE) iDeviceType, 
                                     m_hWindow,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                     &kPresentParams, &m_pkD3DDevice ) ))
     {
      return mrErrorCreateDevice;
     }
    }
   }
  }
   /* If 32 bit, try to create the device using different pixel 32
      color formats */
  else
  {
   kPresentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
   if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                   (D3DDEVTYPE) iDeviceType, 
                                   m_hWindow,
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &kPresentParams, &m_pkD3DDevice ) ))
   {
    kPresentParams.BackBufferFormat = D3DFMT_X8R8G8B8;
    if (FAILED (m_pkD3D->CreateDevice (D3DADAPTER_DEFAULT, 
                                    (D3DDEVTYPE) iDeviceType, 
                                    m_hWindow,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                    &kPresentParams, &m_pkD3DDevice ) ))
    {
     return mrErrorCreateDevice;
    }
   }
  }
  
 }
 m_iFormat = kPresentParams.BackBufferFormat;

  /* Set render states */
 m_pkD3DDevice->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);
 m_pkD3DDevice->SetRenderState (D3DRS_LIGHTING, FALSE);
 m_pkD3DDevice->SetRenderState (D3DRS_ALPHABLENDENABLE,   TRUE);
 m_pkD3DDevice->SetRenderState (D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 m_pkD3DDevice->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

  /* Set texture color states */
 m_pkD3DDevice->SetTextureStageState (0, D3DTSS_COLOROP, D3DTOP_MODULATE);
 m_pkD3DDevice->SetTextureStageState (0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

 return mrNoError;
}

 /* Clear the window to color */
mrError32 mrScreen::Clear (mrUInt8 iRed, mrUInt8 iGreen, mrUInt8 iBlue, 
                           mrUInt8 iAlpha)
{
 mrUInt32 iColor;
 iColor = D3DCOLOR_RGBA (iRed, iGreen, iBlue, iAlpha);

  /* Clear the screen to certain color */
 if (FAILED (m_pkD3DDevice->Clear (0, NULL, D3DCLEAR_TARGET, iColor, 
             0, 0) ))
 {
  return mrErrorClear;
 }
 return mrNoError;
}

 /* Start rendering */
mrError32 mrScreen::StartFrame (void)
{
 m_kTimer.Update ();

  /* Start rendering */
 if (FAILED (m_pkD3DDevice->BeginScene () ))
 {
  return mrErrorBeginScene;
 }
 return mrNoError;
}

 /* End rendering */
mrError32 mrScreen::EndFrame (void)
{
  /* End rendering */
 if (FAILED (m_pkD3DDevice->EndScene () ))
 {
  return mrErrorEndScene;
 }

  /* Present data to the screen */
 if (FAILED (m_pkD3DDevice->Present (NULL, NULL, NULL, NULL) ))
 {
  return mrErrorPresent;
 }

  /* Calculate framer per second */
 m_kTimer.Update ();
 m_iFPS = (mrUInt32) (1 / m_kTimer.GetDelta ());

 return mrNoError;
}


mrError32 mrScreen::DrawLine (mrReal32 fX1, mrReal32 fY1, 
                         mrReal32 fX2, mrReal32 fY2,
                         mrUInt8 iRed, mrUInt8 iGreen, 
                         mrUInt8 iBlue, mrUInt8 iAlpha)
{
 mrUInt32 iColor;
 iColor = D3DCOLOR_RGBA (iRed, iGreen, iBlue, iAlpha);

  /* Create rectangle vertices */
 mrVertex kVertices [] =
 {  /* x, y, z, w, color, texture coordinates (u,v) */
  {fX1, fY1, 0, 1.0f, iColor, 0, 0},
  {fX2, fY2, 0, 1.0f, iColor, 0, 0},
 };
 
  /* Draw the line */
 mrScreen::GetSingleton ()->GetDevice ()->SetVertexShader (
                                      D3DFVF_MIRUSVERTEX);
 if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->DrawPrimitiveUP (
                                      D3DPT_LINELIST, 2, kVertices, 
                                      sizeof (mrVertex))) )
 {
  return mrErrorDrawPrimitive;
 }

 return mrNoError;
}

mrError32 mrScreen::DrawRectangle (mrReal32 fX1, mrReal32 fY1,
                                   mrReal32 fX2, mrReal32 fY2, 
                                   mrUInt8 iRed, mrUInt8 iGreen, 
                                   mrUInt8 iBlue, mrUInt8 iAlpha)
{
 mrUInt32 iColor;
 iColor = D3DCOLOR_RGBA (iRed, iGreen, iBlue, iAlpha);
 
  /* Create rectangle vertices */
 mrVertex kVertices [] =
 {  /* x, y, z, w, color, texture coordinates (u,v) */
  {fX1, fY1, 0, 1.0f, iColor, 0, 0},
  {fX2, fY1, 0, 1.0f, iColor, 0, 0},
  {fX2, fY2, 0, 1.0f, iColor, 0, 0},
  {fX1, fY2, 0, 1.0f, iColor, 0, 0},
  {fX1, fY1, 0, 1.0f, iColor, 0, 0},
 };
 
  /* Draw the line */
 mrScreen::GetSingleton ()->GetDevice ()->SetVertexShader (
                                      D3DFVF_MIRUSVERTEX);
 if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->DrawPrimitiveUP (
                                      D3DPT_LINESTRIP, 4, kVertices, 
                                      sizeof (mrVertex))) )
 {
  return mrErrorDrawPrimitive;
 }

 return mrNoError;
}

mrError32 mrScreen::DrawCircle (mrReal32 iCenterX, mrReal32 iCenterY, 
                                mrReal32 iRadius, mrUInt8 iRed, 
                                mrUInt8 iGreen, mrUInt8 iBlue, 
                                mrUInt8 iAlpha, mrUInt32 iVertices)
{
 mrUInt32 iColor;
 iColor = D3DCOLOR_RGBA (iRed, iGreen, iBlue, iAlpha);

 mrVertex * pkVertices;
  /* Allocate needed vertices */
 pkVertices = new mrVertex [iVertices + 1];

 mrReal32 fAngle = 0;
 mrReal32 fComplete;

 mrUInt32 iVertex;

  /* Calculate each vertice position */
 for (iVertex = 0; iVertex < iVertices; iVertex ++)
 {
   /* Percentage of circle already drawn */
  fComplete = (mrReal32)iVertex / (mrReal32)iVertices;
  pkVertices [iVertex].m_fX = (mrReal32) ((mrReal32)iCenterX + 
                ((mrReal32)iRadius * cos (6.2831f*fComplete)));
  pkVertices [iVertex].m_fY = (mrReal32) ((mrReal32)iCenterY + 
                ((mrReal32)iRadius * sin (6.2831f*fComplete)));

  pkVertices [iVertex].m_fZ     = 0;
  pkVertices [iVertex].m_fRHW   = 1.0f;
  pkVertices [iVertex].m_iColor = iColor;
  pkVertices [iVertex].m_ftU    = 0;
  pkVertices [iVertex].m_ftV    = 0;
 }

  /* Close the circle */
 pkVertices [iVertex].m_fX = pkVertices [0].m_fX;
 pkVertices [iVertex].m_fY = pkVertices [0].m_fY;

 pkVertices [iVertex].m_fZ     = 0;
 pkVertices [iVertex].m_fRHW   = 1.0f;
 pkVertices [iVertex].m_iColor = iColor;
 pkVertices [iVertex].m_ftU    = 0;
 pkVertices [iVertex].m_ftV    = 0;

  /* Draw the circle */
 mrScreen::GetSingleton ()->GetDevice ()->SetVertexShader (
                                      D3DFVF_MIRUSVERTEX);
 if (FAILED (mrScreen::GetSingleton ()->GetDevice ()->DrawPrimitiveUP (
                                      D3DPT_LINESTRIP, iVertices,
                                      pkVertices, sizeof (mrVertex))) )
 {
  return mrErrorDrawPrimitive;
 }
 delete [] pkVertices;
 return mrNoError;
}

 /* Check if mode is supported */
mrBool32 mrScreen::IsModeSupported (mrUInt16 iWidth, mrUInt16 iHeight,
                                    mrUInt16 iDepth)
{
 mrUInt32       iNumberOfModes;
 mrUInt32       iMode;
 D3DDISPLAYMODE kMode;

  /* Get number of available modes */
 iNumberOfModes = m_pkD3D->GetAdapterModeCount (D3DADAPTER_DEFAULT);

  /* For each mode check if mode is equal */
 for (iMode = 0; iMode < iNumberOfModes; iMode ++)
 {
   /* Get mode information */
  m_pkD3D->EnumAdapterModes (D3DADAPTER_DEFAULT, iMode, &kMode);

   /* Compare dimensions */
  if ((iWidth == kMode.Width) && (iHeight == kMode.Height))
  {
    /* Compare bit depth */
   if (iDepth == 16)
   {
    if ((kMode.Format == D3DFMT_R5G6B5) || 
        (kMode.Format == D3DFMT_X1R5G5B5) || 
        (kMode.Format == D3DFMT_A1R5G5B5) )
    {
     return mrTrue;
    }
   }
   else
   {
    if ((kMode.Format == D3DFMT_A8R8G8B8) || 
        (kMode.Format == D3DFMT_X8R8G8B8))
    {
     return mrTrue;
    }  
   }
  }
 }

 return mrFalse;
}

 /* Shows or hides the cursor */
void mrScreen::ShowCursor (mrUInt32 iShowCursor)
{
 m_pkD3DDevice->ShowCursor (iShowCursor);
}

 /* Returns the Direct3D device */
LPDIRECT3DDEVICE8 mrScreen::GetDevice (void)
{
 return m_pkD3DDevice;
}

 /* Returns the frames per second */
mrUInt32 mrScreen::GetFPS (void)
{
 return m_iFPS;
}

 /* Returns the backbuffer format */
mrUInt32 mrScreen::GetFormat (void)
{
 return m_iFormat;
}

 /* Returns the backbuffer depth */
mrUInt32 mrScreen::GetBitdepth (void)
{
 mrUInt32 iBitdepth;

 switch (m_iFormat)
 {
 case D3DFMT_R5G6B5:
 case D3DFMT_X1R5G5B5:
 case D3DFMT_A1R5G5B5:
  iBitdepth = 16;
  break;
 case D3DFMT_A8R8G8B8:
 case D3DFMT_X8R8G8B8:
  iBitdepth = 32;
  break;
 }

 return iBitdepth;
}

 /* Returns the mrScreen singleton */
mrScreen * mrScreen::GetSingleton (void)
{
 assert (m_pkSingleton);
 return m_pkSingleton;
}