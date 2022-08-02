 /* 'mrRGBAImage.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h> 
 /* File stream header file */
#include <fstream.h>
 /* DirectX Graphics header file */
#include <d3d8.h> 

 /* Include this file only once */
#pragma once

 /* Mirus RGBA image class */
class mrRGBAImage
{
protected:
  /* Image size */
 mrUInt32        m_iWidth;
 mrUInt32        m_iHeight;

  /* Image buffer */
 mrUInt32 *      m_piImageBuffer;
 
public:
  /* Constructor / Destructor */
 mrRGBAImage (void);
 ~mrRGBAImage (void);

  /* Operators */
 mrRGBAImage & operator = (mrRGBAImage & rkImage);

  /* Load image from Windows bitmap */
 mrError32 LoadFromBitmap (LPSTR lpszFilename);
 mrError32 LoadFromTarga (LPSTR lpszFilename);

  /* Image manipulation */
 void SetColorKey (mrUInt8 iRed, mrUInt8 iGreen, mrUInt8 iBlue);

 void SetWidth (mrUInt32);
 void SetHeight (mrUInt32);
 void SetColor (mrUInt32 iX, mrUInt32 iY, mrUInt8 iRed, 
																mrUInt8 iGreen, mrUInt8 iBlue, 
																mrUInt8 iAlpha);
 void SetImageBuffer (mrUInt32 * pImage);

 mrUInt32 GetWidth (void);
 mrUInt32 GetHeight (void);
 mrUInt32 GetColor (mrUInt32 iX, mrUInt32 iY);
 mrUInt32 * GetImageBuffer (void);
};
