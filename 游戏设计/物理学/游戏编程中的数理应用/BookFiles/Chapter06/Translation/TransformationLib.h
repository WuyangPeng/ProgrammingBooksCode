/////////////////////////////////////////////////////////////////////////
// TransformationLib.h
// by Dustin Clingman  1/16/04
//
// Purpose: This library provides functions for working with transformations
//
//////////////////////////////////////////////////////////////////////////

#include "MatrixLib.h"


Matrix3X1 translate3DByAddition(Matrix3X1 start, Matrix3X1 trans);
Matrix3X1 translate2DByMultiplication(Matrix3X1 start, Matrix3X3 trans, float dx, float dy);
Matrix4X1 translate3DByMultiplication(Matrix4X1 start, float dx, float dy, float dz);

Matrix3X1 scale2DByMultiplication(Matrix3X1 start, float dx, float dy);
Matrix4X1 scale3DByMultiplication(Matrix4X1 start, float dx, float dy,float dz);

Matrix3X1 rotate2D(Matrix3X1 start, float theta);

Matrix4X1 rotate3D(Matrix4X1 start, float theta);

Matrix4X1 rotate3DZ(Matrix4X1 start, float theta);
Matrix4X1 rotate3DX(Matrix4X1 start, float theta);
Matrix4X1 rotate3DY(Matrix4X1 start, float theta);

Matrix4X4 createRotationCombo(float thetax,float thetay,float thetaz);
Matrix4X1 rotate3DWithCombo(Matrix4X4 combo, Matrix4X1 vertex);


Matrix3X1 translate3DByAddition(Matrix3X1 start, Matrix3X1 trans)
    {
      Matrix3X1 temp;
      temp = addMatrices(start,trans);
      return temp;
    }

Matrix3X1 translate2DByMultiplication(Matrix3X1 start, float dx, float dy)
    {
        Matrix3X3 temp;
        Matrix3X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed3X3Matrix(0);

        //setup the 3x3 for multiplication;
        temp.x[0][0] = 1;
        temp.x[1][1] = 1;
        temp.x[2][2] = 1;

        //put in the translation amount
        temp.x[0][2] = dx;
        temp.x[1][2] = dy;

        result = multiplyMatrixNxM(temp,start);
        return result;
    }


Matrix4X1 translate3DByMultiplication(Matrix4X1 start, float dx, float dy, float dz)
    {
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //setup the 4X4 for multiplication;
        temp.x[0][0] = 1;
        temp.x[1][1] = 1;
        temp.x[2][2] = 1;
        temp.x[3][3] = 1;

        //put in the translation amount
        temp.x[0][3] = dx;
        temp.x[1][3] = dy;
        temp.x[2][3] = dz;

        result = multiplyMatrixNxM(temp,start);
        return result;
    }



Matrix3X1 scale2DByMultiplication(Matrix3X1 start, float dx, float dy)
    {
        Matrix3X3 temp;
        Matrix3X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed3X3Matrix(0);

        //setup the 3x3 for multiplication;
        temp.x[0][0] = dx;
        temp.x[1][1] = dy;
        temp.x[2][2] = 1;

        result = multiplyMatrixNxM(temp,start);
        return result;
    }
Matrix4X1 scale3DByMultiplication(Matrix4X1 start, float dx, float dy, float dz)
    {
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //setup the 3x3 for multiplication;
        temp.x[0][0] = dx;
        temp.x[1][1] = dy;
        temp.x[2][2] = dz;
        temp.x[3][3] = 1;

        result = multiplyMatrixNxM(temp,start);
        return result;
    }


Matrix3X1 rotate2D(Matrix3X1 start, float theta)
    {
    
        Matrix3X3 temp;
        Matrix3X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed3X3Matrix(0);

        //place the needed rotational values into the matrix based on theta.
        temp.x[0][0] = cos(DegreesToRads(theta));
        temp.x[1][1] = cos(DegreesToRads(theta));
        temp.x[2][2] = 1;

        temp.x[0][1] = -1*(sin(DegreesToRads(theta)));
        temp.x[1][0] = sin(DegreesToRads(theta));
        temp.x[2][2] = 1;

        result = multiplyMatrixNxM(temp,start);
        return result;    
    }

Matrix3X1 rotate2DAtOrigin(float x, float y, float theta)
    {
        Matrix3X3 initial,rotation, invert,temp,temp2;
        Matrix3X1 start, result;

        
        start.x[0] = x;
        start.x[1] = y;
        start.x[2] = 1;

        //initialize matrices
        initial   = createFixed3X3Matrix(0.0f);
        rotation = createFixed3X3Matrix(0.0f);
        invert   = createFixed3X3Matrix(0.0f);
        temp = createFixed3X3Matrix(0.0f);
        temp = createFixed3X3Matrix(0.0f);

        //setup the 3x3 for multiplication;
        initial.x[0][0] = 1;
        initial.x[1][1] = 1;
        initial.x[2][2] = 1;

        //put in the translation amount
        initial.x[0][2] = x;
        initial.x[1][2] = y;
        
        //The rotation Matrix
        rotation.x[0][0] = cos(DegreesToRads(theta));
        rotation.x[1][1] = cos(DegreesToRads(theta));
        rotation.x[2][2] = 1;

        rotation.x[0][1] = -1*(sin(DegreesToRads(theta)));
        rotation.x[1][0] = sin(DegreesToRads(theta));
        rotation.x[2][2] = 1;

        //setup the inversion of dx and dy
        invert.x[0][0] = 1;
        invert.x[1][1] = 1;
        invert.x[2][2] = 1;

        //setup to translate to origin.
        invert.x[0][2] = -1*x;
        invert.x[1][2] = -1*y;

        //We are ready to multiply one at a time. Left to right
        temp  = multiply3X3Matrices(initial,rotation);
        //printMatrix(temp);
        temp2 = multiply3X3Matrices(temp,invert);
        //printMatrix(temp2);
        result= multiplyMatrixNxM(temp2,start);


        return result;
    }



Matrix4X1 rotate3D(Matrix4X1 start, float theta)
    {
    
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //place the needed rotational values into the matrix based on theta.
        temp.x[0][0] = cos(DegreesToRads(theta));
        temp.x[1][1] = cos(DegreesToRads(theta));
        temp.x[2][2] = 1;
        temp.x[3][3] = 1;

        temp.x[0][1] = -1*(sin(DegreesToRads(theta)));
        temp.x[1][0] = sin(DegreesToRads(theta));
        temp.x[2][2] = 1;

        result = multiplyMatrixNxM(temp,start);
        return result;    
    }

Matrix4X1 rotate3DZ(Matrix4X1 start, float theta)
    {
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //place the needed rotational values into the matrix based on theta.
        temp.x[0][0] = cos(DegreesToRads(theta));
        temp.x[1][1] = cos(DegreesToRads(theta));
        temp.x[2][2] = 1;
        temp.x[3][3] = 1;

        temp.x[0][1] = -1*(sin(DegreesToRads(theta)));
        temp.x[1][0] = sin(DegreesToRads(theta));
        

        result = multiplyMatrixNxM(temp,start);
        return result;    
    }


Matrix4X1 rotate3DX(Matrix4X1 start, float theta)
    {
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //place the needed rotational values into the matrix based on theta.
        temp.x[0][0] = 1;
        temp.x[1][1] = cos(DegreesToRads(theta));
        temp.x[2][2] = cos(DegreesToRads(theta));
        temp.x[3][3] = 1;

        temp.x[1][2] = -1*(sin(DegreesToRads(theta)));
        temp.x[2][1] = sin(DegreesToRads(theta));
        

        result = multiplyMatrixNxM(temp,start);
        return result;    
    }


Matrix4X1 rotate3DY(Matrix4X1 start, float theta)
    {
        Matrix4X4 temp;
        Matrix4X1 result;

        //Zero out the matrix to make sure nothing is left uninitialized.
        temp = createFixed4X4Matrix(0);

        //place the needed rotational values into the matrix based on theta.
        temp.x[0][0] = cos(DegreesToRads(theta));
        temp.x[1][1] = 1;
        temp.x[2][2] = cos(DegreesToRads(theta));
        temp.x[3][3] = 1;

        temp.x[2][0] = -1*(sin(DegreesToRads(theta)));
        temp.x[0][2] = sin(DegreesToRads(theta));
        

        result = multiplyMatrixNxM(temp,start);
        return result;    
    }

Matrix4X4 createRotationCombo(float thetax,float thetay,float thetaz)
    {
        Matrix4X4 X,Y,Z,temp,result;
    
        X = createFixed4X4Matrix(0.0f);
        Y = createFixed4X4Matrix(0.0f);
        Z = createFixed4X4Matrix(0.0f);
        temp = createFixed4X4Matrix(0.0f);
        result = createFixed4X4Matrix(0.0f);

        //place the needed X rotational values into the matrix based on thetax.
        X.x[0][0] = 1;
        X.x[1][1] = cos(DegreesToRads(thetax));
        X.x[2][2] = cos(DegreesToRads(thetax));
        X.x[3][3] = 1;

        X.x[2][1] = -1*(sin(DegreesToRads(thetax)));
        X.x[1][2] = sin(DegreesToRads(thetax));
      

        //place the needed Y-Axis rotational values into the matrix based on thetay.
        Y.x[0][0] = cos(DegreesToRads(thetay));
        Y.x[1][1] = 1;
        Y.x[2][2] = cos(DegreesToRads(thetay));
        Y.x[3][3] = 1;

        Y.x[2][0] = -1*(sin(DegreesToRads(thetay)));
        Y.x[0][2] = 1;sin(DegreesToRads(thetay));

        //place the needed Z-axis rotational values into the matrix based on thetaz.
        Z.x[0][0]  = cos(DegreesToRads(thetaz));
        Z.x[1][1]  = cos(DegreesToRads(thetaz));
        Z.x[2][2]  = 1;
        Z.x[3][3]  = 1;

        Z.x[0][1]  = -1*(sin(DegreesToRads(thetaz)));
        Z.x[1][0]  = sin(DegreesToRads(thetaz));

        //Now that things are setup, lets create the single Combo Matrix.
        temp = multiply4X4Matrices(Y,X);
        result = multiply4X4Matrices(temp,Z);
        return result;
    
    }

Matrix4X1 rotate3DWithCombo(Matrix4X4 combo, Matrix4X1 vertex)
    {
      Matrix4X1 temp;
      temp = multiplyMatrixNxM(combo,vertex);
      return temp;   
    }


