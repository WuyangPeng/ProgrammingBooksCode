//============================================================================
//
// Listing 7.1
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


void CalculateTangentArray(long vertexCount, const Point3D *vertex,
		const Vector3D *normal, const Point2D *texcoord, long triangleCount,
		const Triangle *triangle, Vector4D *tangent)
{
	Vector3D *tan1 = new Vector3D[vertexCount * 2];
	Vector3D *tan2 = tan1 + vertexCount;
	ZeroMemory(tan1, vertexCount * sizeof(Vector3D) * 2);
	
	for (long a = 0; a < triangleCount; a++)
	{
		long i1 = triangle->index[0];
		long i2 = triangle->index[1];
		long i3 = triangle->index[2];
		
		const Point3D& v1 = vertex[i1];
		const Point3D& v2 = vertex[i2];
		const Point3D& v3 = vertex[i3];
		const Point2D& w1 = texcoord[i1];
		const Point2D& w2 = texcoord[i2];
		const Point2D& w3 = texcoord[i3];
		
		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;
		
		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;
		
		float r = 1.0F / (s1 * t2 - s2 * t1);
		Vector3D sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r);
		Vector3D tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r);
		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;
		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
		triangle++;
	}
	
	for (long a = 0; a < vertexCount; a++)
	{
		const Vector3D& n = normal[a];
		const Vector3D& t = tan1[a];
		
		// Gram-Schmidt orthogonalize.
		tangent[a] = (t - n * Dot(n, t)).Normalize();
		
		// Calculate handedness.
		tangent[a].w = (Dot(Cross(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F;
	}
	
	delete[] tan1;
}
