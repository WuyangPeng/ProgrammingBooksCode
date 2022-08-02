// GraphicsUtil.cpp : Source File for the GraphicsUtil Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#include "stdafx.h"
#include "GraphicsUtil.h"

// Addition operator
//
// In:	vec	The Vector to add to us
//
// Return:	The result of the addition
Vec4 Vec4::operator +(const Vec4 &rVec)
{
	Vec4 temp;
	temp.vector[0] = vector[0] + rVec.vector[0];
	temp.vector[1] = vector[1] + rVec.vector[1];
	temp.vector[2] = vector[2] + rVec.vector[2];
	temp.vector[3] = vector[3] + rVec.vector[3];

	return temp;
}

// Subtraction operator
//
// In:	vec	The Vector to subtract from us
//
// Return:	The result of the subtraction
Vec4 Vec4::operator -(const Vec4 &rVec)
{
	Vec4 temp;
	temp.vector[0] = vector[0] - rVec.vector[0];
	temp.vector[1] = vector[1] - rVec.vector[1];
	temp.vector[2] = vector[2] - rVec.vector[2];
	temp.vector[3] = vector[3] - rVec.vector[3];

	return temp;
}

// Division operator - by some scalar
//
// In:	double - the scaling factor
//
// Return:	The resultant scaled vector
Vec4 Vec4::operator /(const double &scale)
{
	Vec4 temp;
	temp.vector[0] = vector[0] / scale;
	temp.vector[1] = vector[1] / scale;
	temp.vector[2] = vector[2] / scale;
	temp.vector[3] = vector[3] / scale;

	return temp;
}

Vec4 Vec4::operator *(const double num)
{
	Vec4 temp;
	temp.vector[0] = vector[0] * num;
	temp.vector[1] = vector[1] * num;
	temp.vector[2] = vector[2] * num;
	temp.vector[3] = vector[3] * num;

	return temp;

}

/*
	mat[0]	mat[4]	mat[8]	mat[12]
	mat[1]	mat[5]	mat[9]	mat[13]
	mat[2]	mat[6]	mat[10]	mat[14]
	mat[3]	mat[7]	mat[11]	mat[15]
*/

// This will return a row from the matrix as a vector
//
// In:	row	The row of the matrix to return 0 - 3
//
// Return:	The row of the matrix as a Vector
Vec4 Matrix4::getrow(int row) const
{
	Vec4 temp;

	for (int i = 0; i < 4; i++)
	{
		temp.vector[i] = mat[row + (i * 4)];
	}

	return temp;
}

// This will return a column from the matrix as a vector
//
// In:	column	The column of the matrix to return 0 - 3
//
// Return:	The column of the matrix as a Vector
Vec4 Matrix4::getcol(int col)  const
{
	Vec4 temp;

	for (int i = 0; i < 4; i++)
	{
		temp.vector[i] = mat[(col * 4) + i];
	}

	return temp;
}

// Multiplication operator
//
// In:	mat	The Matrix to multiply
//
// Return:	The result of the multiplication
Matrix4 Matrix4::operator *(const Matrix4* mat)
{
	Matrix4 temp;

	temp.mat[0] = DotProduct(&getrow(0), &mat->getcol(0));
	temp.mat[1] = DotProduct(&getrow(1), &mat->getcol(0));
	temp.mat[2] = DotProduct(&getrow(2), &mat->getcol(0));
	temp.mat[3] = DotProduct(&getrow(3), &mat->getcol(0));

	temp.mat[4] = DotProduct(&getrow(0), &mat->getcol(1));
	temp.mat[5] = DotProduct(&getrow(1), &mat->getcol(1));
	temp.mat[6] = DotProduct(&getrow(2), &mat->getcol(1));
	temp.mat[7] = DotProduct(&getrow(3), &mat->getcol(1));
	
	temp.mat[8] = DotProduct(&getrow(0), &mat->getcol(2));
	temp.mat[9] = DotProduct(&getrow(1), &mat->getcol(2));
	temp.mat[10] = DotProduct(&getrow(2), &mat->getcol(2));
	temp.mat[11] = DotProduct(&getrow(3), &mat->getcol(2));

	temp.mat[12] = DotProduct(&getrow(0), &mat->getcol(3));
	temp.mat[13] = DotProduct(&getrow(1), &mat->getcol(3));
	temp.mat[14] = DotProduct(&getrow(2), &mat->getcol(3));
	temp.mat[15] = DotProduct(&getrow(3), &mat->getcol(3));

	return temp;
}

// Multiplication operator
//
// In:	vec	The Vector to multiply
//
// Return:	The result of the multiplication
Vec4 Matrix4::operator *(Vec4* vec)
{
	Vec4 temp;

	temp.vector[0] = DotProduct(&getrow(0), vec);
	temp.vector[1] = DotProduct(&getrow(1), vec);
	temp.vector[2] = DotProduct(&getrow(2), vec);
	temp.vector[3] = DotProduct(&getrow(3), vec);
							
	return temp;
}

void Vertex::InitVert(Vec4* lpos, Vec3* lcol)
{
	for (int i = 0; i < 4; i++)
	{
		pos.vector[i] = lpos->vector[i];
	}
	for (i = 0; i < 3; i++)	
		col.vector[i] = lcol->vector[i];
}

double VecLength(Vec4 vec)
{
	return sqrt((vec.vector[0] * vec.vector[0]) + (vec.vector[1] * vec.vector[1])
		+ (vec.vector[2] * vec.vector[2]) + (vec.vector[3] * vec.vector[3]));
}

Vec4 Normalize(Vec4 vec)
{
	return vec / VecLength(vec);    
}

double DotProduct(Vec4* vec1, Vec4* vec2)
{
	return ((vec1->vector[0] * vec2->vector[0]) + (vec1->vector[1] * vec2->vector[1]) + 
		(vec1->vector[2] * vec2->vector[2]) + (vec1->vector[3] * vec2->vector[3]));
}

// IdentityMat
Matrix4* IdentityMat()
{
	Matrix4* temp = new Matrix4;
	temp->mat[0] = 1.0f; temp->mat[4] = 0.0f; temp->mat[8] = 0.0f; temp->mat[12] = 0.0f;
	temp->mat[1] = 0.0f; temp->mat[5] = 1.0f; temp->mat[9] = 0.0f; temp->mat[13] = 0.0f;
	temp->mat[2] = 0.0f; temp->mat[6] = 0.0f; temp->mat[10] = 1.0f; temp->mat[14] = 0.0f;
	temp->mat[3] = 0.0f; temp->mat[7] = 0.0f; temp->mat[11] = 0.0f; temp->mat[15] = 1.0f;

	return temp;
}