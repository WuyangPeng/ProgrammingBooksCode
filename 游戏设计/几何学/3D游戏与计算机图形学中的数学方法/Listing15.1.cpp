//============================================================================
//
// Listing 15.1
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "VectorClasses.h"


class Fluid
{
	private:
		
		long			width;
		long			height;
		
		Vector3D		*buffer[2];
		long			renderBuffer;
		
		Vector3D		*normal;
		Vector3D		*tangent;
		float			k1, k2, k3;
	
	public:
		
		Fluid(long n, long m, float d, float t, float c, float mu);
		~Fluid();
		
		void Evaluate(void);
};

Fluid::Fluid(long n, long m, float d, float t, float c, float mu)
{
	width = n;
	height = m;
	long count = n * m;
	
	buffer[0] = new Vector3D[count];
	buffer[1] = new Vector3D[count];
	renderBuffer = 0;
	
	normal = new Vector3D[count];
	tangent = new Vector3D[count];
	
	// Precompute constants for Equation (15.25).
	float f1 = c * c * t * t / (d * d);
	float f2 = 1.0F / (mu * t + 2);
	k1 = (4.0F - 8.0F * f1) * f2;
	k2 = (mu * t - 2) * f2;
	k3 = 2.0F * f1 * f2;
	
	// Initialize buffers.
	long a = 0;
	for (long j = 0; j < m; j++)
	{
		float y = d * j;
		for (long i = 0; i < n; i++)
		{
			buffer[0][a].Set(d * i, y, 0.0F);
			buffer[1][a] = buffer[0][a];
			normal[a].Set(0.0F, 0.0F, 2.0F * d);
			tangent[a].Set(2.0F * d, 0.0F, 0.0F);
			a++;
		}
	}
}

Fluid::~Fluid()
{
	delete[] tangent;
	delete[] normal;
	delete[] buffer[1];
	delete[] buffer[0];
}

void Fluid::Evaluate(void)
{
	// Apply Equation (15.25).
	for (long j = 1; j < height - 1; j++)
	{
		const Vector3D *crnt = buffer[renderBuffer] + j * width;
		Vector3D *prev = buffer[1 - renderBuffer] + j * width;
		
		for (long i = 1; i < width - 1; i++)
		{
			prev[i].z = k1 * crnt[i].z + k2 * prev[i].z +
				k3 * (crnt[i + 1].z + crnt[i - 1].z +
				crnt[i + width].z + crnt[i - width].z);
		}
	}
	
	// Swap buffers.
	renderBuffer = 1 - renderBuffer;
	
	// Calculate normals and tangents.
	for (long j = 1; j < height - 1; j++)
	{
		const Vector3D *next = buffer[renderBuffer] + j * width;
		Vector3D *nrml = normal + j * width;
		Vector3D *tang = tangent + j * width;
		
		for (long i = 1; i < width - 1; i++)
		{
			nrml[i].x = next[i - 1].z - next[i + 1].z;
			nrml[i].y = next[i - width].z - next[i + width].z;
			tang[i].z = next[i + 1].z - next[i - 1].z;
		}
	}
}
