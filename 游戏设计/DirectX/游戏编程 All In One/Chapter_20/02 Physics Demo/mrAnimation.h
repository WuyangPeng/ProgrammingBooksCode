 /* 'mrAnimation.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Mirus template set header */
#include "mrTemplateSet.h"
 /* Mirus screen header */
#include "mrScreen.h"
/* DirectX Graphics header file */
#include <d3d8.h> 

 /* Include this file only once */
#pragma once

 /* Mirus Animation class */
class mrAnimation
{
protected:
 mrTemplateSet    m_kTemplateSet;
 mrUInt32         m_iFrames;
 mrUInt32         m_iCurrentFrame;

 mrCellID *       m_pkFramesID;

public:
  /* Constructors / Destructor */
 mrAnimation (void);
 ~mrAnimation (void);

  /* Animation manipulation methods */
 void Create (mrTemplateSet * pkTemplateSet, mrUInt32 iFrames, 
              mrCellID * pkPosition);
 void Update (void);
 mrError32 Render (RECT kDestRect, mrUInt32 iColor, mrReal32 fAngle);

  /* Animation maintenance methods */
 void SetCurrentFrame (mrUInt32 iFrame);
 mrUInt32 GetCurrentFrame (void);
};
