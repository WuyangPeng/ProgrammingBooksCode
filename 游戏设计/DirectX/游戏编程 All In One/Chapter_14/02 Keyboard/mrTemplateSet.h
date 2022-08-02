 /* 'mrTemplateSet.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Mirus RGBA image header */
#include "mrRGBAImage.h"
 /* Mirus screen header */
#include "mrScreen.h"
 /* Mirus texture header */
#include "mrTexture.h"

 /* Include this file only once */
#pragma once

 /* Mirus texture rectangle class */
class mrRectText
{
public:
 mrReal32         m_fLeft;
 mrReal32         m_fTop;
 mrReal32         m_fRight;
 mrReal32         m_fBottom;
};

 /* Mirus template set cell id class */
class mrCellID
{
public:
 mrUInt32      m_iX;
 mrUInt32      m_iY;
};

 /* Mirus template set class */
class mrTemplateSet
{
protected:
  /* Texture information */
 mrTexture *        m_pkTexture;
 mrUInt32           m_iTextureWidth;
 mrUInt32           m_iTextureHeight;

  /* Cell information */
 mrUInt32           m_iCellWidth;
 mrUInt32           m_iCellHeight;

public:
  /* Constructors / Destructor */
 mrTemplateSet (void);
 ~mrTemplateSet (void);

  /* Template manipulation routines */
 void Create (mrTexture * pkTexture, mrUInt32 iTextureWidth, 
              mrUInt32 iTextureHeight, mrUInt32 iCellWidth, 
              mrUInt32 iCellHeight); 

 void GetUV (mrCellID kPosition, mrRectText * pkUVRect);

  /* Texture maintainance routines */
 void SetActiveTexture (void);

 mrUInt32 GetTextureWidth (void);
 mrUInt32 GetTextureHeight (void);
 mrUInt32 GetCellWidth (void);
 mrUInt32 GetCellHeight (void);
};
