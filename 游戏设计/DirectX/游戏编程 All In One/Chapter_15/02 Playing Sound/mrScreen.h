 /* 'mrScreen.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrTimer.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h> 
 /* DirectX Graphics header file */
#include <d3d8.h> 
 /* C++ math  header file */
#include <math.h> 
 /* Assert header file */
#include <assert.h> 

 /* Include this file only once */
#pragma once

 /* Mirus custom vertex structure */
class mrVertex
{
public:
  /* Transformed postion */ 
 FLOAT m_fX, m_fY, m_fZ, m_fRHW;
  /* Color */
 DWORD m_iColor;
  /* Texture coordinates */
 FLOAT m_ftU, m_ftV;
};

 /* Mirus custom vertex type */
#define D3DFVF_MIRUSVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

 /* Mirus screen class */
class mrScreen
{
protected:
 LPDIRECT3D8        m_pkD3D;
 LPDIRECT3DDEVICE8  m_pkD3DDevice;

 mrUInt32           m_iFPS;
 HWND               m_hWindow;

 mrTimer            m_kTimer;

 mrUInt32           m_iFormat;

  /* Singleton */
 static mrScreen *  m_pkSingleton;

public:
  /* Constructors / Destructor */
 mrScreen (void);
 mrScreen (HWND hWindow);

 ~mrScreen (void);

  /* Screen manipulation routines */
 mrError32 Init (HWND hWindow);
 mrError32 SetMode (mrUInt32 iFullscreen, mrUInt16 iWidth, 
                    mrUInt16 iHeight, mrUInt16 iDepth, 
                    bool bHardware); 

  /* Render routines */
 mrError32 Clear (mrUInt8 iRed, mrUInt8 iGreen, mrUInt8 iBlue, 
                  mrUInt8 iAlpha);
 mrError32 StartFrame (void);
 mrError32 EndFrame (void);

  /* Draw routines */
 mrError32 DrawLine (mrReal32 fX1, mrReal32 fY1, 
                     mrReal32 fX2, mrReal32 fY2, 
                     mrUInt8 iRed, mrUInt8 iGreen, 
                     mrUInt8 iBlue, mrUInt8 iAlpha);
 mrError32 DrawRectangle (mrReal32 fX1, mrReal32 fY1, 
                          mrReal32 fX2, mrReal32 fY2, 
                          mrUInt8 iRed, mrUInt8 iGreen, 
                          mrUInt8 iBlue, mrUInt8 iAlpha);
 mrError32 DrawCircle (mrReal32 fCenterX, mrReal32 fCenterY, 
                       mrReal32 iRadius, mrUInt8 iRed, 
                       mrUInt8 iGreen, mrUInt8 iBlue, mrUInt8 iAlpha,
                       mrUInt32 iVertices);

  /* Miscellaneous routines */
 mrBool32 IsModeSupported (mrUInt16 iWidth, mrUInt16 iHeight, 
                           mrUInt16 iDepth);
 void ShowCursor (mrUInt32 iShowCursor);

  /* Maintaince methods */
 LPDIRECT3DDEVICE8 GetDevice (void);
 mrUInt32 GetFPS (void);
 mrUInt32 GetFormat (void);
 
 mrUInt32 GetBitdepth (void);

  /* Singleton */
 static mrScreen * GetSingleton (void);
};
