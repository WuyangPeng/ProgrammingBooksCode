 /* 'mrMatrix22.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus 2D vector header */
#include "mrVector2D.h"
 /* C++ math  header file */
#include <math.h> 

 /* Include this file only once */
#pragma once

 /* Mirus matrix 2x2 class */
class mrMatrix22
{
protected:
 mrReal32                 m_aafElements [2][2];

public:
  /* Constructors / destructor */
 mrMatrix22 (void);
 mrMatrix22 (mrMatrix22 & rkMatrix);
 mrMatrix22 (mrReal32 * pMatrix);
 ~mrMatrix22 (void);

  /* Operators */
 mrMatrix22 & operator = (mrMatrix22 & rkMatrix);
 mrMatrix22 & operator += (mrMatrix22 & rkMatrix);
 mrMatrix22 & operator -= (mrMatrix22 & rkMatrix);
 mrMatrix22 & operator *= (mrReal32 fMultiplier);
 mrMatrix22 & operator /= (mrReal32 fDivider);
 mrMatrix22 operator + (mrMatrix22 & rkMatrix);
 mrMatrix22 operator - (mrMatrix22 & rkMatrix);
 mrMatrix22 operator * (mrReal32 fMultiplier);
 mrMatrix22 operator / (mrReal32 fDivider);
 mrMatrix22 operator - (void);
 mrReal32 & operator [] (const mrInt iElement);

  /* Operations */
 void Zero (void);
 void Identity (void);
 void Transpose (void);
 mrMatrix22 Concatenate (mrMatrix22 & rkMatrix);
 void Transform (mrVector2D & rkVector);

  /* Manipulation operations */
 void SetMatrix (mrMatrix22 & rkMatrix);
 mrReal32 * Matrix (void);
};
