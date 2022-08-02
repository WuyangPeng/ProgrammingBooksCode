//============================================================================
//
// Listing 10.1
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


#include "Structures.h"


long BuildEdges(long vertexCount, long triangleCount,
		const Triangle *triangleArray, Edge **edgeArray)
{
	long maxEdgeCount = triangleCount * 3;
	unsigned short *firstEdge =
		new unsigned short[vertexCount + maxEdgeCount];
	unsigned short *nextEdge = firstEdge + vertexCount;

	for (long a = 0; a < vertexCount; a++) firstEdge[a] = 0xFFFF;

	// First pass over all triangles. This finds all the edges satisfying
	// the condition that the first vertex index is less than the second 
	// vertex index when the direction from the first vertex to the second 
	// vertex representsa counterclockwise winding around the triangle to 
	// which the edge belongs. For each edge found, the edge index is
	// stored in a linked list of edges belonging to the lower-numbered
	// vertex index i. This allows us to quickly find an edge in the second
	// pass whose higher-numbered vertex index is i.

	long edgeCount = 0;
	const Triangle *triangle = triangleArray;
	for (long a = 0; a < triangleCount; a++)
	{
		long i1 = triangle->index[2];
		for (long b = 0; b < 3; b++)
		{
			long i2 = triangle->index[b];
			if (i1 < i2)
			{
				Edge *edge = &edgeArray[edgeCount];

				edge->vertexIndex[0] = (unsigned short) i1;
				edge->vertexIndex[1] = (unsigned short) i2;
				edge->faceIndex[0] = (unsigned short) a;
				edge->faceIndex[1] = (unsigned short) a;

				long edgeIndex = firstEdge[i1];
				if (edgeIndex == 0xFFFF)
				{
					firstEdge[i1] = edgeCount;
				}
				else
				{
					for (;;)
					{
						long index = nextEdge[edgeIndex];
						if (index == 0xFFFF)
						{
							nextEdge[edgeIndex] = edgeCount;
							break;
						}

						edgeIndex = index;
					}
				}

				nextEdge[edgeCount] = 0xFFFF;
				edgeCount++;
			}

			i1 = i2;
		}

		triangle++;
	}

	// Second pass over all triangles. This finds all the edges satisfying 
	// the condition that the first vertex index is greater than the second 
	// vertex index when the direction from the first vertex to the second 
	// vertex represents a counterclockwise winding around the triangle to
	// which the edge belongs. For each of these edges, the same edge should
	// have already been found in the first pass for a different triangle. 
	// So we search the list of edges for the higher-numbered vertex index
	// for the matching edge and fill in the second triangle index. The
	// maximum number of comparisons in this search for any vertex is the
	// number of edges having that vertex as an endpoint.

	triangle = triangleArray;
	for (long a = 0; a < triangleCount; a++)
	{
		long i1 = triangle->index[2];
		for (long b = 0; b < 3; b++)
		{
			long i2 = triangle->index[b];
			if (i1 > i2)
			{
				for (long edgeIndex = firstEdge[i2]; edgeIndex != 0xFFFF;
					edgeIndex = nextEdge[edgeIndex])
				{
					Edge *edge = &edgeArray[edgeIndex];
					if ((edge->vertexIndex[1] == i1) &&
						(edge->faceIndex[0] == edge->faceIndex[1]))
					{
						edge->faceIndex[1] = (unsigned short) a;
						break;
					}
				}
			}

			i1 = i2;
		}

		triangle++;
	}

	delete[] firstEdge;
	return (edgeCount);
}
