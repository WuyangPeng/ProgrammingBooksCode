 /* 'mrRGBAImage.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h> 
 /* File stream header file */
#include <fstream.h>

 /* Include this file only once */
#pragma once

 /* Mirus RGBA image class */
class mrRGBAImage
{
protected:
  /* Image size */
	mrUInt32								m_iWidth;
	mrUInt32								m_iHeight;

  /* Image buffer */
	mrUInt32	*						m_piImageBuffer;
	
public:
  /* Constructor / Destructor */
 mrRGBAImage (void);
 ~mrRGBAImage (void);

  /* Operators */
	mrRGBAImage & operator = (mrRGBAImage & rkImage);

  /* Load image from Windows bitmap */
 mrError32 LoadFromBitmap (LPSTR lpszFilename);

  /* Return the timer information */
 mrUInt32 GetWidth (void);
 mrUInt32 GetHeight (void);
	mrUInt32 GetColor (mrUInt32 iX, mrUInt32 iY);
	mrUInt32 * GetImageBuffer (void);
};
