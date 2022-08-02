//============================================================================
//
// Listing 16.7
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "MatrixClasses.h"


const float epsilon = 1.0e-10F;
const int maxSweeps = 32;

void CalculateEigensystem(const Matrix3D& m, float *lambda, Matrix3D& r)
{
	float m11 = m(0,0);
	float m12 = m(0,1);
	float m13 = m(0,2);
	float m22 = m(1,1);
	float m23 = m(1,2);
	float m33 = m(2,2);
	
	r.SetIdentity();
	for (int a = 0; a < maxSweeps; a++)
	{
		// Exit if off-diagonal entries small enough.
		if ((Fabs(m12) < epsilon) && (Fabs(m13) < epsilon) &&
			(Fabs(m23) < epsilon)) break;
		
		// Annihilate (1,2) entry.
		if (m12 != 0.0F)
		{
			float u = (m22 - m11) * 0.5F / m12;
			float u2 = u * u;
			float u2p1 = u2 + 1.0F;
			float t = (u2p1 != u2) ?
				((u < 0.0F) ? -1.0F : 1.0F) * (sqrt(u2p1) - fabs(u))
				: 0.5F / u;
			float c = 1.0F / sqrt(t * t + 1.0F);
			float s = c * t;
			m11 -= t * m12;
			m22 += t * m12;
			m12 = 0.0F;
			
			float temp = c * m13 - s * m23;
			m23 = s * m13 + c * m23;
			m13 = temp;
			
			for (int i = 0; i < 3; i++)
			{
				float temp = c * r(i,0) - s * r(i,1);
				r(i,1) = s * r(i,0) + c * r(i,1);
				r(i,0) = temp;
			}
		}
		
		// Annihilate (1,3) entry.
		if (m13 != 0.0F)
		{
			float u = (m33 - m11) * 0.5F / m13;
			float u2 = u * u;
			float u2p1 = u2 + 1.0F;
			float t = (u2p1 != u2) ?
				((u < 0.0F) ? -1.0F : 1.0F) * (sqrt(u2p1) - fabs(u))
				: 0.5F / u;
			float c = 1.0F / sqrt(t * t + 1.0F);
			float s = c * t;
			
			m11 -= t * m13;
			m33 += t * m13;
			m13 = 0.0F;
			
			float temp = c * m12 - s * m23;
			m23 = s * m12 + c * m23;
			m12 = temp;
			
			for (int i = 0; i < 3; i++)
			{
				float temp = c * r(i,0) - s * r(i,2);
				r(i,2) = s * r(i,0) + c * r(i,2);
				r(i,0) = temp;
			}
		}
		
		// Annihilate (2,3) entry.
		if (m23 != 0.0F)
		{
			float u = (m33 - m22) * 0.5F / m23;
			float u2 = u * u;
			float u2p1 = u2 + 1.0F;
			float t = (u2p1 != u2) ?
				((u < 0.0F) ? -1.0F : 1.0F) * (sqrt(u2p1) - fabs(u))
				: 0.5F / u;
			float c = 1.0F / sqrt(t * t + 1.0F);
			float s = c * t;
			
			m22 -= t * m23;
			m33 += t * m23;
			m23 = 0.0F;
			
			float temp = c * m12 - s * m13;
			m13 = s * m12 + c * m13;
			m12 = temp;
			
			for (int i = 0; i < 3; i++)
			{
				float temp = c * r(i,1) - s * r(i,2);
				r(i,2) = s * r(i,1) + c * r(i,2);
				r(i,1) = temp;
			}
		}
	}
	
	lambda[0] = m11;
	lambda[1] = m22;
	lambda[2] = m33;
}
