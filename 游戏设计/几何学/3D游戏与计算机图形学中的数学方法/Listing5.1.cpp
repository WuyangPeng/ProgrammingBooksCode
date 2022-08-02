//============================================================================
//
// Listing 5.1
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "VectorClasses.h"


inline float sgn(float x)
{
	if (x > 0.0F) return (1.0F);
	if (x < 0.0F) return (-1.0F);
	return (0.0F);
}

void ModifyProjectionMatrix(const Vector4D& clipPlane)
{
	float			matrix[16];
	Vector4D		q;
	
	// Grab the current projection matrix from OpenGL.
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	
	// Calculate the clip-space corner point opposite the clipping plane
	// using Equation (5.64) and transform it into camera space by
	// multiplying it by the inverse of the projection matrix.
	q.x = (sgn(clipPlane.x) + matrix[8]) / matrix[0];
	q.y = (sgn(clipPlane.y) + matrix[9]) / matrix[5];
	q.z = -1.0F;
	q.w = (1.0F + matrix[10]) / matrix[14];
	
	// Calculate the scaled plane vector using Equation (5.68)
	// and replace the third row of the projection matrix.
	Vector4D c = clipPlane * (2.0F / Dot(clipPlane, q));
	matrix[2] = c.x;
	matrix[6] = c.y;
	matrix[10] = c.z + 1.0F;
	matrix[14] = c.w;
	
	// Load it back into OpenGL.
	glMatrixMode(GL_PROJECTION);
	glLoadMatrix(matrix);
}
