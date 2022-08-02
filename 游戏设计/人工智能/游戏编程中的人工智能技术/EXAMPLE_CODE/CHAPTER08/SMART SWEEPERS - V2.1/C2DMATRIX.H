#ifndef C2DMATRIX_H
#define C2DMATRIX_H
//------------------------------------------------------------------------
//
//	Name: C2DMatrix.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Matrix class for 'Smart Sweeper' example from the book Game AI 
//  Programming with Neural Nets and Genetic Algorithms.. 
//
//------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "utils.h"

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
		  _11=0.0f; _12=0.0f; _13=0.0f;
		  _21=0.0f; _22=0.0f; _23=0.0f;
		  _31=0.0f; _32=0.0f; _33=0.0f;
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

  //multiplies m_Matrix with the passed matrix
  void  S2DMatrixMultiply(S2DMatrix &mIn);

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
  void TransformSPoints(vector<SPoint> &vPoints);

	

};


#endif
