//============================================================================
//
// Basic Geometric Structures
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


struct Edge
{
	unsigned short		vertexIndex[2];
	unsigned short		faceIndex[2];
};


struct Triangle
{
	unsigned short		index[3];
	
	void Set(unsigned long i1, unsigned long i2, unsigned long i3)
	{
		index[0] = (unsigned short) i1;
		index[1] = (unsigned short) i2;
		index[2] = (unsigned short) i3;
	}
};
