/* 'mrVector2D.cpp' */

/* Complement header file */
#include "mrVector2D.h"

/* Default constructor */
mrVector2D::mrVector2D (void)
{
 Reset ();
}

mrVector2D::mrVector2D (mrVector2D & rkVector)
{
 m_afComponents [0] = rkVector [0];
 m_afComponents [1] = rkVector [1];
}

mrVector2D::mrVector2D (mrReal32 fXComponent, mrReal32 fYComponent)
{
 m_afComponents [0] = fXComponent;
 m_afComponents [1] = fYComponent;
}

mrVector2D::~mrVector2D (void)
{
 Reset ();
}

mrVector2D & mrVector2D::operator = (mrVector2D & rkVector)
{
 m_afComponents [0] = rkVector [0];
 m_afComponents [1] = rkVector [1];
 
 return *this;
}

mrVector2D & mrVector2D::operator += (mrVector2D & rkVector)
{
 m_afComponents [0] += rkVector [0];
 m_afComponents [1] += rkVector [1];
 
 return *this;
}

mrVector2D & mrVector2D::operator -= (mrVector2D & rkVector)
{
 m_afComponents [0] -= rkVector [0];
 m_afComponents [1] -= rkVector [1];
 
 return *this;
}

mrVector2D & mrVector2D::operator *= (mrReal32 iMultiplier)
{
 m_afComponents [0] *= iMultiplier;
 m_afComponents [1] *= iMultiplier;
 
 return *this;
}

mrVector2D & mrVector2D::operator /= (mrReal32 iDivider)
{
 m_afComponents [0] *= iDivider;
 m_afComponents [1] *= iDivider;
 
 return *this;
}

mrVector2D mrVector2D::operator + (mrVector2D & rkVector)
{
 return mrVector2D (m_afComponents [0] + rkVector [0], 
  m_afComponents [1] + rkVector [1]);
}

mrVector2D mrVector2D::operator - (mrVector2D & rkVector)
{
 return mrVector2D (m_afComponents [0] - rkVector [0], 
  m_afComponents [1] - rkVector [1]);
}

mrVector2D mrVector2D::operator * (mrReal32 iMultiplier)
{
 return mrVector2D (m_afComponents [0] * iMultiplier, 
  m_afComponents [1] * iMultiplier);
}

mrVector2D mrVector2D::operator / (mrReal32 iDivider)
{
 return mrVector2D (m_afComponents [0] / iDivider, 
  m_afComponents [1] / iDivider);
}

mrVector2D mrVector2D::operator - (void)
{
 return mrVector2D (-m_afComponents [0], -m_afComponents [1]);
}

mrReal32 & mrVector2D::operator [] (const mrInt IComponent)
{
 return m_afComponents [IComponent];
}

mrReal32 mrVector2D::Length (void)
{
 return (mrReal32) sqrt (m_afComponents[0] * m_afComponents[0] + 
  m_afComponents[1] * m_afComponents[1]);
}

void mrVector2D::Normalize (void)
{
 mrReal32 fLength;
 fLength = Length ();

 if (0 != fLength)
 {
  m_afComponents [0] /= fLength;
  m_afComponents [1] /= fLength;
 }
}

mrVector2D mrVector2D::Perpendicular (void)
{
 return mrVector2D (-m_afComponents [1], m_afComponents [0]); 
}

mrReal32 mrVector2D::DotProduct (mrVector2D & rkVector)
{
 return m_afComponents [0] * rkVector [0] +
        m_afComponents [1] * rkVector [1];
}

mrReal32 mrVector2D::Angle (mrVector2D & rkVector)
{
 return (mrReal32) acos (DotProduct (rkVector) / 
  (Length() * rkVector.Length()));
}

mrReal32 mrVector2D::PerpDotProduct (mrVector2D & rkVector)
{
 return Perpendicular ().DotProduct (rkVector);
}

void mrVector2D::Reset (void)
{
 m_afComponents [0] = 0;
 m_afComponents [1] = 0;
}

void mrVector2D::SetVector (mrVector2D & rkVector)
{
 m_afComponents [0] = rkVector [0];
 m_afComponents [1] = rkVector [1];
}

mrReal32 * mrVector2D::GetVector (void)
{
 return  m_afComponents;
}

