 /* '03 Main.cpp' */

 /* Mirus window framework header */
#include "mrWindow.h"
 /* Direct3D header */
#include <d3d8.h>
 /* C++ math header */
#include <math.h>

 /* Our custom vertex structure */
class CustomVertex
{
public:
  /* Transformed postion */ 
 FLOAT x, y, z, rhw;
  /* Color */
 DWORD Color;
  /* Texture coordinates */
 FLOAT tU, tV;
};

 /* Our custom vertex type */
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

 /* Custom derived class */
class D3DWindow : public mrWindow
{
  /* Direct 3D interfaces */
 LPDIRECT3D8             m_pD3D;
 LPDIRECT3DDEVICE8       m_pD3DDevice;

  /* Direct3D texture interface */
 LPDIRECT3DTEXTURE8      m_pD3DTexture;
  /* Direct3D current format */
 mrUInt32                m_iD3DFormat;

  /* Vertices */
 CustomVertex           m_kVertices [4];

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

  /* Create the texture */  
 if (FAILED (m_pD3DDevice->CreateTexture (128, 128, 0, 0, 
                                          (D3DFORMAT) m_iD3DFormat,
                                          D3DPOOL_MANAGED, 
                                          &m_pD3DTexture ) ) )

 {
  return E_FAIL;
 }

  /* Lock texture */
 D3DLOCKED_RECT kLockedRect;
 m_pD3DTexture->LockRect (0, &kLockedRect, NULL, 0);

  /* Cast a pointer to point to the first pixel */
 DWORD * piTextureBuffer = (DWORD *) kLockedRect.pBits;

  /* Fill texture */
 int iX, iY;
 for (iY=0; iY<128; iY++)
 {
  for (iX=0; iX<128; iX++)
  {
    /* Form pattern */
   int iPower = (int)(sin (iY * iX) * 128 + cos (iY * -iX) * 128);
   piTextureBuffer [iX + iY* (kLockedRect.Pitch >> 2)] = 
                    D3DCOLOR_XRGB (iPower, iPower, iPower);
  }
 }
  
  /* Unlock */
 m_pD3DTexture->UnlockRect (0);

  /* Setup a temporary vertices information */
 CustomVertex kVertices [] =
 {  /* x, y, z, w, color, texture coordinates (u,v) */
  {0.0f,  0.0f,  0.5f, 1.0f, D3DCOLOR_ARGB (255, 255, 0,   0),   0, 0}, 
  {50.0f, 0.0f,  0.5f, 1.0f, D3DCOLOR_ARGB (255, 255, 255, 0),   1, 0},
  {50.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_ARGB (255, 255, 0,   255), 1, 1},
  {0.0f,  50.0f, 0.5f, 1.0f, D3DCOLOR_ARGB (255, 255, 255, 255), 0, 1},
 };

  /* Copy the vertices information to the vertex buffer */
 memcpy (m_kVertices, kVertices, sizeof(kVertices));
 
  /* Don't cull polygons */
 m_pD3DDevice->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);

  /* Don't use lighting */
 m_pD3DDevice->SetRenderState (D3DRS_LIGHTING, FALSE);
 
  /* Set texture states */
 m_pD3DDevice->SetTextureStageState (0, D3DTSS_COLOROP,   D3DTOP_MODULATE);

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
 if (NULL != m_pD3DTexture)
 {
  m_pD3DTexture->Release ();
 }

 return D3D_OK;
}

 /* Draw the entire frame */
mrBool32 D3DWindow::Frame (void)
{
  /* Clear the window to blue */
 m_pD3DDevice->Clear (0, NULL, D3DCLEAR_TARGET, 
                      D3DCOLOR_XRGB (0,0,255), 1.0f, 0);

  /* Start rendering */
 m_pD3DDevice->BeginScene();

  /* Set texture source */
 m_pD3DDevice->SetTexture (0, m_pD3DTexture);
  
  /* Set vertex source */
 m_pD3DDevice->SetVertexShader (D3DFVF_CUSTOMVERTEX) ;
 m_pD3DDevice->DrawPrimitiveUP (D3DPT_TRIANGLEFAN, 2, m_kVertices, 
                                sizeof (CustomVertex));

  /* End rendering */
 m_pD3DDevice->EndScene();

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
 kWindow.Create (hInstance, "Textures");

  /* Setup Direct3D */
 kWindow.SetupDirect3D ();

  /* Enter message loop */
 kWindow.Run ();

  /* Shutdown Direct3D */
 kWindow.KillDirect3D ();

 return 0;
}