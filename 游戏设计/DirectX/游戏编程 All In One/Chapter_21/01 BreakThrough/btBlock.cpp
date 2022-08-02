 /* 'btBlock.cpp' */

 /* Complement header file */
#include "btBlock.h"

btBlock::btBlock (void)
{
 m_iWidth   = 0;
 m_iHeight  = 0;
 m_bIsAlive = mrFalse;
 m_iABO     = 0;
 m_iRed     = 0;
 m_iGreen   = 0;
 m_iBlue    = 0;
 m_iAlpha   = 0;
}

btBlock::~btBlock (void)
{
 m_iWidth   = 0;
 m_iHeight  = 0;
 m_bIsAlive = mrFalse;
 m_iABO     = 0;
 m_iRed     = 0;
 m_iGreen   = 0;
 m_iBlue    = 0;
 m_iAlpha   = 0;
}

void btBlock::Create (mrUInt32 iABO, mrVector2D kPosition, 
                      mrUInt8 iRed, mrUInt8 iGreen, 
                      mrUInt8 iBlue, mrUInt8 iAlpha)
{
  /* Setup the ABO */
 m_iABO = iABO;

  /* Setup the color */
 m_iRed   = iRed;
 m_iGreen = iGreen;
 m_iBlue  = iBlue;
 m_iAlpha = iAlpha;

  /* Setup the initial paddle size */
 SetSize (32, 16);

 m_bIsAlive = mrTrue;
 
  /* Setup the entity */
 m_kObject.SetMass (10000000000);
 m_kObject.SetStaticFriction (0.92f);
 m_kObject.SetCoefficientOfRestitution(1);
 m_kObject.SetKineticFriction (0.91f);
 m_kObject.SetPosition (kPosition);
}

void btBlock::Destroy (void)
{
 SetSize (0, 0);
 m_bIsAlive = mrFalse;
}

void btBlock::SetSize (mrUInt32 iWidth, mrUInt32 iHeight)
{
 m_iWidth  = iWidth;
 m_iHeight = iHeight;
}

mrUInt32 btBlock::GetABO (void)
{
 return m_iABO;
}

mrUInt8 btBlock::GetRed (void)
{
 return m_iRed;
}

mrUInt8 btBlock::GetGreen (void)
{
 return m_iGreen;
}

mrUInt8 btBlock::GetBlue (void)
{
 return m_iBlue;
}

mrUInt8 btBlock::GetAlpha (void)
{
 return m_iAlpha;
}

mrUInt32 btBlock::GetWidth (void)
{
 return m_iWidth;
}

mrUInt32 btBlock::GetHeight (void)
{
 return m_iHeight;
}

mrEntity * btBlock::GetObject (void)
{
 return &m_kObject;
}

mrBool32 btBlock::GetIsAlive (void)
{
 return m_bIsAlive;
}
