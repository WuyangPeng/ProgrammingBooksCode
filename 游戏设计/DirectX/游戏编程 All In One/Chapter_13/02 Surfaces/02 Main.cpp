 /* '02 Main.cpp' */

 /* Mirus window framework header */
#include "mrWindow.h"
 /* Direct3D header */
#include <d3d8.h>
 /* C++ math header */
#include <math.h>

 /* Custom derived class */
class D3DWindow : public mrWindow
{
  /* Direct 3D interfaces */
 LPDIRECT3D8             m_pD3D;
 LPDIRECT3DDEVICE8       m_pD3DDevice;

  /* Direct3D surface interface */
 LPDIRECT3DSURFACE8      m_pD3DSurface;
  /* Direct3D current format */
 mrUInt32                m_iD3DFormat;

public:
  /* Constructor / Destructor */
 D3DWindow (void) {};
 ~D3DWindow (void) {};

  /* Setup and shutdown Direct3D */
 HRESULT SetupDirect3D (void);
 HRESULT KillDirect3D (void);

  /* Window manipulation functions */
 mrBool32 Frame (void);
};

 /* Initializes Direct3D */
HRESULT D3DWindow::SetupDirect3D (void)
{
  /* Create the Direct3D object */
 if (NULL == (m_pD3D = Direct3DCreate8 (D3D_SDK_VERSION) ) )
 {
  return E_FAIL;
 }
 
  /* Get the current display mode so we can know what bitdepth 
     we are */
 D3DDISPLAYMODE d3ddm;
 if (FAILED (m_pD3D->GetAdapterDisplayMode (D3DADAPTER_DEFAULT, 
                                            &d3ddm) ) )
 {
  return E_FAIL;
 }
 
  /* Fill in the present paramenters */
 D3DPRESENT_PARAMETERS d3dpp; 
 ZeroMemory( &d3dpp, sizeof(d3dpp) );
  /* We want windowed mode */
 d3dpp.Windowed   = TRUE;
  /* Discard this */
 d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  /* Same format as the current format 
     (we got this from g_pD3D->GetAdapterDisplayMode)  */
 d3dpp.BackBufferFormat = d3ddm.Format;
  /* Save the format */
 m_iD3DFormat = d3ddm.Format;
 
  /* Create the device */
 if (FAILED (m_pD3D->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                   m_hWindow, 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &d3dpp, 
                                   &m_pD3DDevice ) ) )
 {
  return E_FAIL;
 }

  /* Create the surface */  
 if (FAILED (m_pD3DDevice->CreateImageSurface (256, 256, 
                                               (D3DFORMAT) m_iD3DFormat,
                                               &m_pD3DSurface ) ) )

 {
  return E_FAIL;
 }

  /* Lock surface */
 D3DLOCKED_RECT kLockedRect;
 m_pD3DSurface->LockRect (&kLockedRect, NULL, 0);

  /* Cast a pointer to point to the first pixel */
 DWORD * piSurfaceBuffer = (DWORD *) kLockedRect.pBits;

  /* Fill surface */
 int iX, iY;
 for (iY=0; iY<256; iY++)
 {
  for (iX=0; iX<256; iX++)
  {
    /* Form pattern */
   int iPower = (int)(sin (iY * iX) * 128 + cos (iY * -iX) * 128);
   piSurfaceBuffer [iX + iY* (kLockedRect.Pitch >> 2)] = 
                    D3DCOLOR_XRGB (iPower, iPower, iPower);
  }
 }
  
  /* Unlock */
 m_pD3DSurface->UnlockRect ();

 return D3D_OK;
}

 /* Shutdowns Direct3D */
HRESULT D3DWindow::KillDirect3D (void)
{
   /* If any of the Direct3D objects exist, release them */
 if (NULL != m_pD3D)
 {
  m_pD3D->Release ();
 }
 if (NULL != m_pD3DDevice)
 {
  m_pD3DDevice->Release ();
 }

 if (NULL != m_pD3DSurface)
 {
  m_pD3DSurface->Release ();
 }

 return D3D_OK;

}

 /* Draw the surface */
mrBool32 D3DWindow::Frame (void)
{
  /* Clear the window to blue */
 m_pD3DDevice->Clear (0, NULL, D3DCLEAR_TARGET, 
                      D3DCOLOR_XRGB (0,0,255), 1.0f, 0);
 
  /* Get back buffer */
 LPDIRECT3DSURFACE8 pBackBuffer;
 m_pD3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

  /* Start rendering */
 m_pD3DDevice->BeginScene();
  /* Copy the surface to the screen */
 m_pD3DDevice->CopyRects (m_pD3DSurface, NULL, 0, pBackBuffer, NULL);
  /* End rendering */
 m_pD3DDevice->EndScene();

  /* Release back buffer */
 pBackBuffer->Release ();

  /* Present the rendered scene to the screen */
 m_pD3DDevice->Present (NULL, NULL, NULL, NULL);

 return mrTrue;
}

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  /* Our window */
 D3DWindow  kWindow;

  /* Create window */
 kWindow.Create (hInstance, "Surfaces");

  /* Setup Direct3D */
 kWindow.SetupDirect3D ();

  /* Enter message loop */
 kWindow.Run ();

  /* Shutdown Direct3D */
 kWindow.KillDirect3D ();

 return 0;
}