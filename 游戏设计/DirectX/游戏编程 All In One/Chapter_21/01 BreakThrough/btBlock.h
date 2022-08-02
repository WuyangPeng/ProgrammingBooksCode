 /* 'btBlock.h' */

 /* Mirus window framework header */
#include "Mirus\Mirus.h"

 /* Include this file only once */
#pragma once

 /* Break Through ball class */
class btBlock
{
protected:
  /* Physics object */
 mrEntity           m_kObject;

  /* Real size of block */
 mrUInt32           m_iWidth;
 mrUInt32           m_iHeight;

  /* Is block alive */
 mrBool32           m_bIsAlive;

  /* Block ABO ID */
 mrUInt32           m_iABO;

  /* Block colors */
 mrUInt8            m_iRed;
 mrUInt8            m_iGreen;
 mrUInt8            m_iBlue;
 mrUInt8            m_iAlpha;

public:
  /* Constructor / Destructor */
 btBlock (void);
 ~btBlock (void);

  /* Block manipulation routines */
 void Create (mrUInt32 iABO, mrVector2D kPosition, mrUInt8 iRed, 
              mrUInt8 iGreen, mrUInt8 iBlue, mrUInt8 iAlpha);
 void Destroy (void);

  /* Block maintainance routines */
 void SetSize (mrUInt32 iWidth, mrUInt32 iHeight);
 mrUInt32 GetABO (void);

 mrUInt8 GetRed (void);
 mrUInt8 GetGreen (void);
 mrUInt8 GetBlue (void);
 mrUInt8 GetAlpha (void);

 mrUInt32 GetWidth (void);
 mrUInt32 GetHeight (void);
 mrEntity * GetObject (void);
 mrBool32 GetIsAlive (void); 
};