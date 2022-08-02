// gltools.h
// Copyright 1998 - 2000 Richard S. Wright Jr..
// Code by Richard S. Wright Jr.
// All Macros prefixed with GLT_, all functions prefixed with glt... This
// should avoid most namespace problems
// Some of these functions allocate memory. Link to Multithreaded runtime
// Report bugs to opengl@bellsouth.net
// Full Sail Students may not redistribute this code, but may use it in any project
// for educational or commercial purposes.

#ifndef __GLTOOLS__
#define __GLTOOLS__

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
// Data structures and containers
typedef float GLT_POINT2[2];		// Point in XY (or st, uv, etc.)
typedef float GLT_POINT3[3];        // Point in XYZ space
typedef float GLT_POINT4[4];		// Point in XYZW space
typedef float GLT_VECTOR3[3];		// Vector of three floats (x, y, z)
typedef float GLT_VECTOR4[4];		// Vector of four floats (x, y, z, w)
									// Can be position, angle, or quaternion
typedef float GLT_MATRIX4[16];		// A 4 X 4 matrix, OpenGL style


///////////////////////////////////////////////////////////////////////////////
// Useful constants
#define GLT_PI (3.14159265358979323846)
#define GLT_PI_DIV_180 (0.017453292519943296)
#define GLT_INV_PI_DIV_180 (57.2957795130823229)


///////////////////////////////////////////////////////////////////////////////
// Useful shortcut macros
#define gltDegToRad(x) ((x)*GLT_PI_DIV_180)
#define gltRadToDeg(x) ((x)*GLT_INV_PI_DIV_180)

#define gltMin(x,y) ((x) <(y)) ? x : y
#define gltMax(x,y) ((x) >(y)) ? x : y



///////////////////////////////////////////////////////////////////////////////
//         THE LIBRARY....
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Vector functions
///////////////////////////////////////////////////////////////////////////////

// Calculates the cross product of two vectors.
inline void gltCrossProduct(GLT_VECTOR3 u, GLT_VECTOR3 v, GLT_VECTOR3 result)
	{
	result[0] = u[1]*v[2] - v[1]*u[2];
	result[1] = -u[0]*v[2] + v[0]*u[2];
	result[2] = u[0]*v[1] - v[0]*u[1];
	}

// Dot product between two vectors
inline float gltDotProduct(GLT_VECTOR3 u, GLT_VECTOR3 v)
    {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
    }

// Given three points, calculate a normal vector. Assumes CCW winding
void gltCalcNormal(GLT_POINT3 point1, GLT_POINT3 point2, GLT_POINT3 point3,	GLT_VECTOR3 result);

// Get a unit normal
void gltScaleToUnit(GLT_VECTOR3 vector);
#define gltNormalize(x)	gltScaleToUnit(x)

// Given three points on a plane (or polygon), calculate the unit normal vector
inline void gltCalcUnitNormal(GLT_POINT3 point1, GLT_POINT3 point2, GLT_POINT3 point3,	
			GLT_VECTOR3 result)
			{
			gltCalcNormal(point1, point2, point3, result);
			gltScaleToUnit(result);
			}


// Returns the angle between the two vectors specified. IMPORTANT!!! - This code assumes
// that the two vectors are unit vectors. Taking into account the length of the vectors
// adds to the computation. Since most operations are going to be performed on unit vectors
// this is a valid optimization, but it must be carefully noted.
// The returned angle is in degrees, not radians
inline double gltGetAngleDeg(GLT_VECTOR3 u, GLT_VECTOR3 v)
    {
    double dTemp = gltDotProduct(u, v);
    dTemp = acos(dTemp);
    return dTemp * 180.0/3.1415926535897932384626433832795;
    }

// Ditto above, but angle is returned in Radians
inline double gltGetAngleRad(GLT_VECTOR3 u, GLT_VECTOR3 v)
    {
    double dTemp = gltDotProduct(u, v);
    return acos(dTemp);
    }


// Calculates the distance between a point and a plane. Requires the point, 
// any other point on the plane, and a unit vector from the plane.
inline float gltCalcDistancePointPlane(GLT_POINT3 point, 
				GLT_POINT3 planePoint, GLT_VECTOR3 unitVector) {
	GLT_VECTOR3 pVec;
	pVec[0] = point[0] - planePoint[0];
	pVec[1] = point[1] - planePoint[1];
	pVec[2] = point[2] - planePoint[2];

	return gltDotProduct(pVec, unitVector);
	}

// Overloaded version of above - uses the point and the coefficients of the
// plane equation instead
inline float gltCalcDistancePointPlane(GLT_POINT3 point, GLT_VECTOR4 plane)
	{
	return -((point[0] * plane[0]) + (point[1] * point[1]) + (point[2] + plane[2]) + plane[3]);
	}

// Get the squared distance between two points
inline float gltGetDistance(GLT_POINT3 p1, GLT_POINT3 p2)
	{
	float dist = 0.0f;

	float x = p1[0] - p2[0];
	float y = p1[1] - p2[1];
	float z = p1[2] - p2[2];

	dist = (x * x) + (y * y) + (z * z);
	
	return dist;
	}


///////////////////////////////////////////////////////////////////////////////
// Matrix Functions
///////////////////////////////////////////////////////////////////////////////

// In CrossProduct.cpp
void gltRotationMatrix(float angle, float x, float y, float z, GLT_MATRIX4 m);
void gltTranslationMatrix(float x, float y, float z, GLT_MATRIX4 m);
void gltLoadIdentity(GLT_MATRIX4 m);
void gltMatrixMultiply(GLT_MATRIX4 a, GLT_MATRIX4 b, GLT_MATRIX4 product );
GLboolean gltInvertMatrix(GLT_MATRIX4 m, GLT_MATRIX4 out );

// Transforms the point (p) by the matrix (m). The result is stored in tPoint.
// This longer version is good for transforming points when the rotation
// and translation are combined.
inline void gltTransformVector4f(GLT_VECTOR4 v, GLT_MATRIX4 m, GLT_VECTOR4 vOut)
    {
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];	
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];	
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];	
	vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
    }

// Short version... transforms a GLT_POINT3, saves a few wasted operations if
// there is no need to retain w.
inline void gltTransformPointf(GLT_POINT3 p, GLT_MATRIX4 m, GLT_POINT3 pOut)
	{
    pOut[0] = m[0] * p[0] + m[4] * p[1] + m[8] *  p[2] + m[12];	
    pOut[1] = m[1] * p[0] + m[5] * p[1] + m[9] *  p[2] + m[13];	
    pOut[2] = m[2] * p[0] + m[6] * p[1] + m[10] * p[2] + m[14];	
	}



///////////////////////////////////////////////////////////////////////////////
// Miscellaneous Functions - Mostly pertaining to Windows
///////////////////////////////////////////////////////////////////////////////
HPALETTE gltGet332Palette(HDC hDC);
BYTE* gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight);
bool gltAutoMipmapBMP(const char *szFile, GLint uiFilter, GLuint uiWrap);
bool gltAutoLoadBMP(const char *szFile, GLint uiFilter, GLuint uiWrap);
bool gltAutoMipmapResource(UINT nResource, GLint uiFilter, GLuint uiWrap);
bool gltAutoLoadResource(UINT nResource, GLint uiFilter, GLuint uiWrap);
BYTE* gltResourceBMPBits(UINT nResource, int *nWidth, int *nHeight);
BYTE* gltBGRtoRGB(BYTE *pTexels, int nWidth, int nHeight);
bool gltIsAccelerated(bool *bICD = NULL);
bool gltCopyScreenToClipBoard(HWND hOwner);
bool gltIsExtSupported(const char *extension);
int gltSelectSoftware(HDC hDC);
bool gltSaveScreenAsBitmap(const char *szFileName);
HBITMAP gltCreateBitmapFromScreen(HDC hDC, int *nWidth, int *nHeight);
bool gltFindHardware(HDC hDC);

////////////////////////////////////////////////////////////////////////////////
// Utility functions for drawing stock geometric objects
void gltDrawUnitAxes(void);


#endif