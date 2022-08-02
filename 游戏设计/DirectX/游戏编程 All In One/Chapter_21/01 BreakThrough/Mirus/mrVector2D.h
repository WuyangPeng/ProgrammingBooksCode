 /* 'mrVector2D.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* C++ math  header file */
#include <math.h> 

 /* Include this file only once */
#pragma once

 /* Mirus vector 2D class */
class mrVector2D
{
protected:
 mrReal32   m_afComponents [2];

public:
	 /* Constructors / Destructor */
 mrVector2D (void);
 mrVector2D (mrVector2D & rkVector);
 mrVector2D (mrReal32 fXComponent, mrReal32 fYComponent);
 ~mrVector2D (void);
  
		/* Operators */
	mrVector2D & operator = (mrVector2D & rkVector);
	mrVector2D & operator += (mrVector2D & rkVector);
	mrVector2D & operator -= (mrVector2D & rkVector);
	mrVector2D & operator *= (mrReal32 iMultiplier);
	mrVector2D & operator /= (mrReal32 iDivider);
	mrVector2D operator + (mrVector2D & rkVector);
	mrVector2D operator - (mrVector2D & rkVector);
	mrVector2D operator * (mrReal32 iMultiplier);
	mrVector2D operator / (mrReal32 iDivider);
	mrVector2D operator - (void);
	mrReal32 & operator [] (const mrInt IComponent);
 
		/* Linear algebra operations */
	mrReal32 Length (void);
	void Normalize (void);
	mrVector2D Perpendicular (void);
	mrReal32 DotProduct (mrVector2D & rkVector);
	mrReal32 Angle (mrVector2D & rkVector);
	mrReal32 PerpDotProduct (mrVector2D & rkVector);
 
		/* Manipulation operations */
	void Reset (void);
	void SetVector (mrVector2D & rkVector);
	mrReal32 * GetVector (void);
};
