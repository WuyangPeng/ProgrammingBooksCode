//============================================================================
//
// Listing 16.1
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "VectorClasses.h"


Vector2D CosSin(float f)
{
	// Determine the index i for the lookup table.
	float a = fabs(f) * 40.74366543F;		// 40.74366543 = 256 / 2pi
	float i = floor(a);
	
	// Determine the angle beta.
	float b = (a - i) * 0.0245436926F;		// 0.0245436926 = 2pi / 256
	
	// Look up the sine and cosine of alpha, masking the index with
	// n - 1 so it stays within a single period.
	const Vector2D& alphaCosSin = trigTable[(long) i & 255];
	
	// Calculate the sine and cosine of beta.
	float b2 = b * b;
	float sine_beta = b - b * b2 * (0.1666666667F - b2 * 0.008333333333F);
	float cosine_beta = 1.0F - b2 * (0.5F - b2 * 0.04166666667F);
	
	// Use the angle sum identities to calculate the sine and cosine
	// of theta. If theta < 0, then negate the sine.
	float sine = alphaCosSin.y * cosine_beta + alphaCosSin.x * sine_beta;
	float cosine = alphaCosSin.x * cosine_beta - alphaCosSin.y * sine_beta;
	return (Vector2D(cosine, (f < 0.0F) ? -sine : sine));
}
