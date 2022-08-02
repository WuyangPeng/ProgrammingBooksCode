 /* 'mrTexture.h' */

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

 /* Mirus texture class */
class mrTexture
{
protected:
  /* Direct3D surface */
 LPDIRECT3DTEXTURE8 m_pkD3DTexture;
 mrRGBAImage *      m_pkRawImage;

 mrUInt32           m_iID;
 mrBool32           m_iHasAlpha;

  /* Maintenance members */
 static mrUInt32    m_iActiveTexture;
 static mrUInt32    m_iCurrentID;

public:
  /* Constructors / Destructor */
 mrTexture (void);
 ~mrTexture (void);

	 /* Texture manipulation routines */
 mrError32 Create (mrRGBAImage * pkRawImage);
 mrError32 Update (void);

 void SetRawImage (mrRGBAImage * pkRawImage);
 mrRGBAImage * GetRawImage (void);

  /* Texture maintenance methods */
 void SetActiveTexture (void);
 mrUInt32 GetID (void);

 static mrUInt32 GetActiveTexture (void);
};
