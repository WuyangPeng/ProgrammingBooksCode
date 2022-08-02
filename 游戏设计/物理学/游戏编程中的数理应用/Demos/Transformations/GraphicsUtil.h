// GraphicsUtil.h : main header file for the GraphicsUtil Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#pragma once

#define _USE_MATH_DEFINES 1
#include <math.h>

/////////////
// PRAGMAS //
/////////////
#pragma intrinsic(sqrt)

/////////////
// CLASSES //
/////////////
class Vec3
{
public:
	// Explicit constructor so that no implicit casts can take place
	Vec3() {  };

	Vec3(double x, double y, double z) 
	{
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
	}

	// Here is our 3x1 Vector, public for easy access.
	double vector[3];
};

class Vec4
{
public:
	// Explicit constructor so that no implicit casts can take place
	Vec4() {  };

	Vec4(double x, double y, double z, double w) 
	{
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
		vector[3] = w;
	}

	// Here is our 3x1 Vector, public for easy access.
	double vector[4];

	// Addition operator
	//
	// In:	vec	The Vector to add to us
	//
	// Return:	The result of the addition
	Vec4 operator +(const Vec4 &rVec);

	// Subtraction operator
	//
	// In:	vec	The Vector to subtract from us
	//
	// Return:	The result of the subtraction
	Vec4 operator -(const Vec4 &rVec);

	// Division operator - by some scalar
	//
	// In:	double - the scaling factor
	//
	// Return:	The resultant scaled vector
	Vec4 operator /(const double &scale);

	// Multiplication operator
	//
	// In:	num	The Scaler to multiply
	//
	// Return:	The result of the multiplication
	Vec4 operator *(const double num);
};

class Matrix4
{
public:
	double mat[16];							// 16 floats representing a 4x4 matrix
	/*
	mat[0]	mat[4]	mat[8]	mat[12]
	mat[1]	mat[5]	mat[9]	mat[13]
	mat[2]	mat[6]	mat[10]	mat[14]
	mat[3]	mat[7]	mat[11]	mat[15]
	*/
	
	// This will return a row from the matrix as a vector
	//
	// In:	row	The row of the matrix to return
	//
	// Return:	The row of the matrix as a Vector
	Vec4 getrow(int row) const;

	// This will return a column from the matrix as a vector
	//
	// In:	column	The column of the matrix to return
	//
	// Return:	The column of the matrix as a Vector
	Vec4 getcol(int col) const;

	// Multiplication operator
	//
	// In:	mat	The Matrix to multiply
	//
	// Return:	The result of the multiplication
	Matrix4 operator *(const Matrix4* mat);

	// Multiplication operator
	//
	// In:	vec	The Vector to multiply
	//
	// Return:	The result of the multiplication
	Vec4 Matrix4::operator *(Vec4* vec);
};

// Data Stored in each vertex
class Vertex 
{
public:
	Vec4 pos;					// Position in 3D space
	Vec3 col;					// Color of the vertex

	void InitVert(Vec4* lpos, Vec3* lcol);
};

double VecLength(Vec4 vec);

// Normalize
Vec4 Normalize(Vec4 vec);

// Dot Product
double DotProduct(Vec4* vec1, Vec4* vec2);

// IdentityMat
Matrix4* IdentityMat();