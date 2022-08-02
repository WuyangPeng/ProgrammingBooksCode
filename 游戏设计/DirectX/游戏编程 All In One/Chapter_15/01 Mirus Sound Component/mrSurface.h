 /* 'mrSurface.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Mirus RGBA image header */
#include "mrRGBAImage.h"
 /* Mirus screen header */
#include "mrScreen.h"
/* DirectX Graphics header file */
#include <d3d8.h> 

 /* Include this file only once */
#pragma once

 /* Mirus surface class */
class mrSurface
{
protected:
  /* Direct3D surface */
 LPDIRECT3DSURFACE8 m_pkD3DSurface;
 mrRGBAImage *      m_pkRawImage;

public:
  /* Constructors / Destructor */
 mrSurface (void);
 ~mrSurface (void);

  /* Surface manipulation routines */
 mrError32 Create (mrRGBAImage * pkRawImage);
 mrError32 Update (void);
 mrError32 Render (POINT * pkDestPoint, RECT * pkSourceRect = NULL);

  /* Surface maintainance methods */
 void SetRawImage (mrRGBAImage * pkRawImage);
 mrRGBAImage * GetRawImage (void);
};
