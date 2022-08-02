 /* 'btGame.h' */

 /* Mirus window framework header */
#include "Mirus\Mirus.h"

 /* Include this file only once */
#pragma once

 /* Break Through paddle class */
class btPaddle
{
protected:
  /* Paddle is made up of three parts */
 mrABO         m_kMainPaddle;
 mrABO         m_akSidePaddles [2];

  /* Physics object */
 mrEntity      m_kObject;

  /* Real size (all parts) of the paddle */
 mrUInt32      m_iWidth;
 mrUInt32      m_iHeight;


public:
  /* Constructor / Destructor */
 btPaddle (void);
 ~btPaddle (void);

  /* Paddle manipulation routines */
 void Create (void);
 void Render (void);
 void Synchronize (void);
 void Update (mrReal32 fStep);

  /* Paddle maintainance routines */
 void SetSize (mrUInt32 iWidth, mrUInt32 iHeight);
 mrUInt32 GetWidth (void);
 mrUInt32 GetHeight (void);
 mrEntity * GetObject (void);
};