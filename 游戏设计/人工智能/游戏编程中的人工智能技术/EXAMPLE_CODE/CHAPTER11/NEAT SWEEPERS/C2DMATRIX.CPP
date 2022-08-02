#include "C2DMatrix.h"

/////////////////////////////////////////////////////////////////////
//
//	Matrix functions
//
/////////////////////////////////////////////////////////////////////
//create an identity matrix
void C2DMatrix::Identity()
{
	m_Matrix._11 = 1; m_Matrix._12 = 0; m_Matrix._13 = 0;

	m_Matrix._21 = 0; m_Matrix._22 = 1; m_Matrix._23 = 0;

	m_Matrix._31 = 0; m_Matrix._32 = 0; m_Matrix._33 = 1;

	}

//create a transformation matrix
void C2DMatrix::Translate(double x, double y)
{
	S2DMatrix mat;
	
	mat._11 = 1; mat._12 = 0; mat._13 = 0;
	
	mat._21 = 0; mat._22 = 1; mat._23 = 0;
	
	mat._31 = x;    mat._32 = y;    mat._33 = 1;
	
	//and multiply
  S2DMatrixMultiply(mat);
}

//create a scale matrix
void C2DMatrix::Scale(double xScale, double yScale)
{
	S2DMatrix mat;
	
	mat._11 = xScale; mat._12 = 0; mat._13 = 0;
	
	mat._21 = 0; mat._22 = yScale; mat._23 = 0;
	
	mat._31 = 0; mat._32 = 0; mat._33 = 1;
	
	//and multiply
  S2DMatrixMultiply(mat);
}


//create a rotation matrix
void C2DMatrix::Rotate(double rot)
{
	S2DMatrix mat;

	double Sin = sin(rot);
	double Cos = cos(rot);
	
	mat._11 = Cos;  mat._12 = Sin; mat._13 = 0;
	
	mat._21 = -Sin; mat._22 = Cos; mat._23 = 0;
	
	mat._31 = 0; mat._32 = 0;mat._33 = 1;
	
	//and multiply
  S2DMatrixMultiply(mat);
}

