 /* '01 Main.cpp' */

 /* Mirus window framework header */
#include "mrWindow.h"
 /* Direct3D header */
#include <d3d8.h>

 /* Custom derived class */
class D3DWindow : public mrWindow
{
  /* Direct 3D interfaces */
 LPDIRECT3D8             m_pD3D;
 LPDIRECT3DDEVICE8       m_pD3DDevice;
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
 
  /* Create the device */
 if (FAILED (m_pD3D->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                   m_hWindow, 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &d3dpp, 
                                   &m_pD3DDevice ) ) )
 {
  return E_FAIL;
 }

 return D3D_OK;
}

 /* Shutdowns Direct3D */
HRESULT D3DWindow::KillDirect3D (void)
{
   /* If any of the Direct3D objects exist, release them */
 if ( NULL != m_pD3D)
 {
  m_pD3D->Release ();
 }
 if ( NULL != m_pD3DDevice)
 {
  m_pD3DDevice->Release ();
 }

 return D3D_OK;

}

 /* Clears the screen to blue */
mrBool32 D3DWindow::Frame (void)
{
  /* Clear the window to blue */
 m_pD3DDevice->Clear (0, NULL, D3DCLEAR_TARGET, 
                      D3DCOLOR_XRGB (0,0,255), 1.0f, 0);

  /* Start rendering */
 m_pD3DDevice->BeginScene();
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
 kWindow.Create (hInstance, "Init and Shutdown");

  /* Setup Direct3D */
 kWindow.SetupDirect3D ();

  /* Enter message loop */
 kWindow.Run ();

  /* Shutdown Direct3D */
 kWindow.KillDirect3D ();

 return 0;
}