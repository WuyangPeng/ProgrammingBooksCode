//============================================================================
//
// Listing 9.2
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "Structures.h"
#include "VectorClasses.h"


const float epsilon = 0.001F;

static long GetNextActive(long x, long vertexCount, const bool *active)
{
	for (;;)
	{
		if (++x == vertexCount) x = 0;
		if (active[x]) return (x);
	}
}

static long GetPrevActive(long x, long vertexCount, const bool *active)
{
	for (;;)
	{
		if (--x == -1) x = vertexCount - 1;
		if (active[x]) return (x);
	}
}

long TriangulatePolygon(long vertexCount, const Point3D *vertex,
		const Vector3D& normal, Triangle *triangle)
{
	bool *active = new bool[vertexCount];
	for (long a = 0; a < vertexCount; a++) active[a] = true;
	
	long triangleCount = 0;
	long start = 0;
	long p1 = 0;
	long p2 = 1;
	long m1 = vertexCount - 1;
	long m2 = vertexCount - 2;
	
	bool lastPositive = false;
	for (;;)
	{
		if (p2 == m2)
		{
			// Only three vertices remain.
			triangle->index[0] = m1;
			triangle->index[1] = p1;
			triangle->index[2] = p2;
			triangleCount++;
			break;
		}
		
		const Point3D& vp1 = vertex[p1];
		const Point3D& vp2 = vertex[p2];
		const Point3D& vm1 = vertex[m1];
		const Point3D& vm2 = vertex[m2];
		bool positive = false;
		bool negative = false;
		
		// Determine whether vp1, vp2, and vm1 form a valid triangle.
		Vector3D n1 = normal % (vm1 - vp2).Normalize();
		if (n1 * (vp1 - vp2) > epsilon)
		{
			positive = true;
			Vector3D n2 = (normal % (vp1 - vm1).Normalize());
			Vector3D n3 = (normal % (vp2 - vp1).Normalize());
			
			for (long a = 0; a < vertexCount; a++)
			{
				// Look for other vertices inside the triangle.
				if ((active[a]) && (a != p1) && (a != p2) && (a != m1))
				{
					const Vector3D& v = vertex[a];
					if ((n1 * (v - vp2).Normalize() > -epsilon)
						&& (n2 * (v - vm1).Normalize() > -epsilon)
						&& (n3 * (v - vp1).Normalize() > -epsilon))
					{
						positive = false;
						break;
					}
				}
			}
		}
		
		// Determine whether vm1, vm2, and vp1 form a valid triangle.
		n1 = normal % (vm2 - vp1).Normalize();
		if (n1 * (vm1 - vp1) > epsilon)
		{
			negative = true;
			Vector3D n2 = (normal % (vm1 - vm2).Normalize());
			Vector3D n3 = (normal % (vp1 - vm1).Normalize());
			
			for (long a = 0; a < vertexCount; a++)
			{
				// Look for other vertices inside the triangle.
				if ((active[a]) && (a != m1) && (a != m2) && (a != p1))
				{
					const Vector3D& v = vertex[a];
					if ((n1 * (v - vp1).Normalize() > -epsilon)
						&& (n2 * (v - vm2).Normalize() > -epsilon)
						&& (n3 * (v - vm1).Normalize() > -epsilon))
					{
						negative = false;
						break;
					}
				}
			}
		}
		
		// If both triangles are valid, choose the one having
		// the larger smallest angle.
		if ((positive) && (negative))
		{
			float pd = (vp2 - vm1).Normalize() * (vm2 - vm1).Normalize();
			float md = (vm2 - vp1).Normalize() * (vp2 - vp1).Normalize();
			if (fabs(pd - md) < epsilon)
			{
				if (lastPositive) positive = false;
				else negative = false;
			}
			else
			{
				if (pd < md) negative = false;
				else positive = false;
			}
		}
		
		if (positive)
		{
			// Output the triangle m1, p1, p2.
			active[p1] = false;
			triangle->index[0] = m1;
			triangle->index[1] = p1;
			triangle->index[2] = p2;
			triangleCount++;
			triangle++;
			
			p1 = GetNextActive(p1, vertexCount, active);
			p2 = GetNextActive(p2, vertexCount, active);
			lastPositive = true;
			start = -1;
		}
		else if (negative)
		{
			// Output the triangle m2, m1, p1.
			active[m1] = false;
			triangle->index[0] = m2;
			triangle->index[1] = m1;
			triangle->index[2] = p1;
			triangleCount++;
			triangle++;
			
			m1 = GetPrevActive(m1, vertexCount, active);
			m2 = GetPrevActive(m2, vertexCount, active);
			lastPositive = false;
			start = -1;
		}
		else
		{
			// Exit if we've gone all the way around the
			// polygon without finding a valid triangle.
			if (start == -1) start = p2;
			else if (p2 == start) break;
			
			// Advance working set of vertices.
			m2 = m1;
			m1 = p1;
			p1 = p2;
			p2 = GetNextActive(p2, vertexCount, active);
		}
	}
	
	delete[] active;
	return (triangleCount);
}
