#ifndef C2DMATRIX_H
#define C2DMATRIX_H

//------------------------------------------------------------------------
//
//	Name: C2DMatrix.h
//
//  Author: Mat Buckland 2002
//
//  Desc: 2D Matrix class  
//------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "utils.h"

struct SPoint;

using namespace std;


class C2DMatrix
{
private:
  
  struct S2DMatrix
  {

	  double _11, _12, _13;
	  double _21, _22, _23;
	  double _31, _32, _33;

    S2DMatrix()
	  {
		  _11=0; _12=0; _13=0;
		  _21=0; _22=0; _23=0;
		  _31=0; _32=0; _33=0;
	  }

    friend ostream &operator<<(ostream& os, const S2DMatrix &rhs)
	  {
		  os << "\n" << rhs._11 << "  " << rhs._12 << "  " << rhs._13;

		  os << "\n" << rhs._21 << "  " << rhs._22 << "  " << rhs._23;

		  os << "\n" << rhs._31 << "  " << rhs._32 << "  " << rhs._33;

		  return os;
	  }
  };

  S2DMatrix m_Matrix;

  //multiplies m_Matrix with mIn
  inline void  S2DMatrixMultiply(S2DMatrix &mIn);

public:

  C2DMatrix()
  {
    //initialize the matrix to an identity matrix
    Identity();
  }

  //create an identity matrix
  void Identity();
  
  //create a transformation matrix
  void	Translate(double x, double y);

  //create a scale matrix
  void	Scale(double xScale, double yScale);

  //create a rotation matrix
  void Rotate(double rotation);

   //applys a transformation matrix to a std::vector of points
  inline void TransformSPoints(vector<SPoint> &vPoints);

};

//multiply two matrices together
inline void C2DMatrix::S2DMatrixMultiply(S2DMatrix &mIn)
{
	S2DMatrix mat_temp;
	
	//first row
	mat_temp._11 = (m_Matrix._11*mIn._11) + (m_Matrix._12*mIn._21) + (m_Matrix._13*mIn._31);
	mat_temp._12 = (m_Matrix._11*mIn._12) + (m_Matrix._12*mIn._22) + (m_Matrix._13*mIn._32);
	mat_temp._13 = (m_Matrix._11*mIn._13) + (m_Matrix._12*mIn._23) + (m_Matrix._13*mIn._33);

	//second
	mat_temp._21 = (m_Matrix._21*mIn._11) + (m_Matrix._22*mIn._21) + (m_Matrix._23*mIn._31);
	mat_temp._22 = (m_Matrix._21*mIn._12) + (m_Matrix._22*mIn._22) + (m_Matrix._23*mIn._32);
	mat_temp._23 = (m_Matrix._21*mIn._13) + (m_Matrix._22*mIn._23) + (m_Matrix._23*mIn._33);

	//third
	mat_temp._31 = (m_Matrix._31*mIn._11) + (m_Matrix._32*mIn._21) + (m_Matrix._33*mIn._31);
	mat_temp._32 = (m_Matrix._31*mIn._12) + (m_Matrix._32*mIn._22) + (m_Matrix._33*mIn._32);
	mat_temp._33 = (m_Matrix._31*mIn._13) + (m_Matrix._32*mIn._23) + (m_Matrix._33*mIn._33);

	m_Matrix = mat_temp;
}

//applies a 2D transformation matrix to a std::vector of SPoints
inline void C2DMatrix::TransformSPoints(vector<SPoint> &vPoint)
{
	for (int i=0; i<vPoint.size(); ++i)
	{
		double tempX =(m_Matrix._11*vPoint[i].x) + (m_Matrix._21*vPoint[i].y) + (m_Matrix._31);

		double tempY = (m_Matrix._12*vPoint[i].x) + (m_Matrix._22*vPoint[i].y) + (m_Matrix._32);
	
		vPoint[i].x = tempX;

		vPoint[i].y = tempY;

	}
}

#endif
