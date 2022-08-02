  /* 'mrMatrix22.cpp' */

  /* Complement header file */
#include "mrMatrix22.h"

  /* Default constructor */
mrMatrix22::mrMatrix22 (void)
{
	Identity ();
}

mrMatrix22::mrMatrix22 (mrMatrix22 & rkMatrix)
{
	*this = rkMatrix;
}

mrMatrix22::mrMatrix22 (mrReal32 * pMatrix)
{
 mrInt8  iI;
 mrInt8  iJ;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   m_aafElements [iJ][iI] = pMatrix [iJ * 2 + iI];
  }
 }
}

mrMatrix22::~mrMatrix22 (void)
{
 Zero ();
}

mrMatrix22 & mrMatrix22::operator = (mrMatrix22 & rkMatrix)
{
	SetMatrix (rkMatrix);

	return *this;
}

mrMatrix22 & mrMatrix22::operator += (mrMatrix22 & rkMatrix)
{
	*this = *this + rkMatrix;

	return *this;
}

mrMatrix22 & mrMatrix22::operator -= (mrMatrix22 & rkMatrix)
{
	*this = *this - rkMatrix;

	return *this;
}

mrMatrix22 & mrMatrix22::operator *= (mrReal32 fMultiplier)
{
	*this = *this * fMultiplier;

	return *this;
}

mrMatrix22 & mrMatrix22::operator /= (mrReal32 fDivider)
{
	*this = *this / fDivider;

	return *this;
}

mrMatrix22 mrMatrix22::operator + (mrMatrix22 & rkMatrix)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = m_aafElements [iJ][iI] + rkMatrix [iJ * 2 + iI];
  }
 }
 return kMatrix;
}

mrMatrix22 mrMatrix22::operator - (mrMatrix22 & rkMatrix)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = m_aafElements [iJ][iI] - rkMatrix [iJ * 2 + iI];
  }
 }
 return kMatrix;
}

mrMatrix22 mrMatrix22::operator * (mrReal32 fMultiplier)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;
 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = m_aafElements [iJ][iI] * fMultiplier;
  }
 }
 return kMatrix;
}

mrMatrix22 mrMatrix22::operator / (mrReal32 fDivider)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = m_aafElements [iJ][iI] / fDivider;
  }
 }
 return kMatrix;
}

mrMatrix22 mrMatrix22::operator - (void)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = - m_aafElements [iJ][iI];
  }
 }
 return kMatrix;
}

mrReal32 & mrMatrix22::operator [] (const mrInt iElement)
{
 return (&(m_aafElements [0][0])) [iElement];
}

void mrMatrix22::Zero (void)
{
 mrInt8  iI;
 mrInt8  iJ;
 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   m_aafElements [iJ][iI] = 0;
  }
 }
}

void mrMatrix22::Identity (void)
{
 mrInt8  iIdentity;
 Zero ();
 for (iIdentity = 0; iIdentity < 2; iIdentity++)
 {
  m_aafElements [iIdentity][iIdentity];
 }
}

void mrMatrix22::Transpose (void)
{
 mrReal32   fTransposedValue;
 fTransposedValue = m_aafElements [0][1];

 m_aafElements [0][1] = m_aafElements [1][0];
 m_aafElements [1][0] = fTransposedValue;
}

mrMatrix22 mrMatrix22::Concatenate (mrMatrix22 & rkMatrix)
{
 mrInt8  iI;
 mrInt8  iJ;
 mrMatrix22 kMatrix;
 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   kMatrix [iJ * 2 + iI] = m_aafElements [0][iI] * rkMatrix [iJ * 2 + 0] + 
                           m_aafElements [1][iI] * rkMatrix [iJ * 2 + 1];
  }
 }
 return kMatrix;
}

void mrMatrix22::Transform (mrVector2D & rkVector)
{
 mrVector2D  kVector;
 kVector [0] = kVector [0] * m_aafElements [0][0] + kVector [1] * m_aafElements [0][1];
 kVector [1] = kVector [0] * m_aafElements [1][0] + kVector [1] * m_aafElements [1][1];
}

void mrMatrix22::SetMatrix (mrMatrix22 & rkMatrix)
{
 mrInt8  iI;
 mrInt8  iJ;

 for (iJ = 0; iJ < 2; iJ++)
 {
  for (iI = 0; iI < 2; iI++)
  {
   m_aafElements [iJ][iI] = rkMatrix [iJ * 2 + iI];
  }
 }
}

mrReal32 * mrMatrix22::Matrix (void)
{
	return (float *)&(m_aafElements [0][0]);
}
