/////////////////////////////////////////////////////////////////////////
// MatrixLib.h
// by Dustin Clingman  1/16/04
//
// Purpose: This library provides functions for working with Matrices
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES 
#include <math.h>


#define RadsToDegrees( radian ) ((radian) * (180.0f / M_PI))
#define DegreesToRads( degrees ) ((degrees) * (M_PI/ 180.0f))



//Here are the matrices to use in this set of transformation examples. 
typedef struct{ float x[3];}     Matrix3X1;
typedef struct{ float x[3][3];}  Matrix3X3;

typedef struct{ float x[4];}     Matrix4X1;
typedef struct{ float x[4][4];}  Matrix4X4;


//prototypes
bool areMatricesEqual3X3(Matrix3X3 a , Matrix3X3 b);
bool areMatricesEqual4X4(Matrix4X4 a , Matrix4X4 b);

Matrix3X3 createRandom3X3Matrix(int seed);
Matrix3X1 createRandom3X1Matrix(int seed);
Matrix4X4 createRandom4X4Matrix(int seed);
Matrix3X1 createRandom3X1Matrix(int seed);


Matrix3X1 createMatrix(float x, float y, float z);
Matrix4X1 createMatrix(float x, float y, float z, float a);

Matrix3X3 createFixed3X3Matrix(float value);
Matrix4X4 createFixed4X4Matrix(float value);

Matrix3X1 addMatrices(Matrix3X1 a, Matrix3X1 b);
Matrix3X3 addMatrices(Matrix3X3 a, Matrix3X3 b);
Matrix4X4 addMatrices(Matrix4X4 a, Matrix4X4 b);

Matrix3X3 subtractMatrices(Matrix3X3 a, Matrix3X3 b);
Matrix4X4 subtractMatrices(Matrix4X4 a, Matrix4X4 b);

Matrix3X3 scalarMultiply(Matrix3X3 a, float scale);
Matrix4X4 scalarMultiply(Matrix4X4 a, float scale);

Matrix3X3 multiply3X3Matrices(Matrix3X3 a, Matrix3X3 b);
Matrix4X4 multiply4X4Matrices(Matrix4X4 a, Matrix4X4 b);

Matrix3X1 multiplyMatrixNxM(Matrix3X3 a, Matrix3X1 b);
Matrix4X1 multiplyMatrixNxM(Matrix4X4 a, Matrix4X1 b);

Matrix3X3 transpose3X3Matrix(Matrix3X3 a);
Matrix4X4 transpose4X4Matrix(Matrix4X4 a);

void printMatrix3X3(Matrix3X3 a);
void printMatrix4X4(Matrix4X4 a);
void printMatrix4X1(Matrix4X1 a);

//definitions

//Test two 3by3 matrices for equality
bool areMatricesEqual(Matrix3X3 a, Matrix3X3 b)
    {
       int errorFlag = 0; 

       for(int i = 0;i<3;i++)
         {
          for(int j=0;j<3;j++)
           {
             if((a.x[i][j]) != (b.x[i][j]))
             errorFlag = 1;           
            }
          }
        //test for an error in equality.
        if(errorFlag == 1)
            return false;
        else
            return true;
    }

//Test two 4by4 matrices for equality
bool areMatricesEqual(Matrix4X4 a, Matrix4X4 b)
    {
       int errorFlag = 0; 

       for(int i = 0;i<4;i++)
         {
          for(int j=0;j<4;j++)
           {
             if((a.x[i][j]) != (b.x[i][j]))
             errorFlag = 1;           
            }
          }
        //test for an error in equality.
        if(errorFlag == 1)
            return false;
        else
            return true;
    }


//create a random matrix controlled by the seed
Matrix3X3 createRandom3X3Matrix(int seed)
    {
    Matrix3X3 temp;

        for(int i = 0;i<3;i++)
            {
            for(int j=0;j<3;j++)
                {
                 temp.x[i][j] = rand()%seed;
                }
            }
        return temp;
    }


//create a random matrix controlled by the seed
Matrix3X1 createRandom3X1Matrix(int seed)
    {
    
      Matrix3X1 temp;

      for(int j=0;j<3;j++)
        {
         temp.x[j] = rand()%seed;
        }
            
      return temp;
    }

//create a random matrix controlled by the seed
Matrix4X4 createRandom4X4Matrix(int seed)
    {
    Matrix4X4 temp;

        for(int i = 0;i<4;i++)
            {
            for(int j=0;j<4;j++)
                {
                 temp.x[i][j] = rand()%seed;
                }
            }
        return temp;
    }



Matrix4X1 createRandom4X1Matrix(int seed)
    {
    
      Matrix4X1 temp;

      for(int j=0;j<4;j++)
        {
         temp.x[j] = rand()%seed;
        }
            
      return temp;
    }


Matrix3X1 createMatrix(float x, float y, float z)
    {
      Matrix3X1 temp;
      temp.x[0] = x;
      temp.x[1] = y;
      temp.x[2] = z;
      return temp;
    }

Matrix4X1 createMatrix(float x, float y, float z, float a)
    {
      Matrix4X1 temp;
      temp.x[0] = x;
      temp.x[1] = y;
      temp.x[2] = z;
      temp.x[3] = a;
      return temp;
    }




//takes a fixed value and initialized a 3X3 matrix to it. 
Matrix3X3 createFixed3X3Matrix(float value)
    {
     Matrix3X3 temp;
     for(int i = 0;i<3;i++)
            {
            for(int j=0;j<3;j++)
                {
                 temp.x[i][j] = value;
                }
            }
        return temp;
    }


//takes a fixed value and initialized a 4X4 matrix to it. 
Matrix4X4 createFixed4X4Matrix(float value)
    {
     Matrix4X4 temp;
     for(int i = 0;i<4;i++)
            {
            for(int j=0;j<4;j++)
                {
                 temp.x[i][j] = value;
                }
            }
        return temp;
    }




Matrix3X1 addMatrices(Matrix3X1 a, Matrix3X1 b)
    {
      Matrix3X1 temp;
        for(int i=0;i<3;i++)
          {
            temp.x[i] = (a.x[i] + b.x[i]);
          }
       return temp;
    }

//Add two 3X3 matrices
Matrix3X3 addMatrices(Matrix3X3 a, Matrix3X3 b)
    {
      Matrix3X3 temp;

        for(int i = 0;i<3;i++)
            {
            for(int j=0;j<3;j++)
                {
                temp.x[i][j] = (a.x[i][j] + b.x[i][j]);
                }
            }
        return temp;
    }

//Add two 4X4 matrices
Matrix4X4 addMatrices(Matrix4X4 a, Matrix4X4 b)
    {
      Matrix4X4 temp;

        for(int i = 0;i<4;i++)
            {
            for(int j=0;j<4;j++)
                {
                temp.x[i][j] = (a.x[i][j] + b.x[i][j]);
                }
            }
        return temp;
    }

//Subtract two 3X3 matrices
Matrix3X3 subtractMatrices(Matrix3X3 a, Matrix3X3 b)
{
      Matrix3X3 temp;

        for(int i = 0;i<3;i++)
            {
            for(int j=0;j<3;j++)
                {
                temp.x[i][j] = (a.x[i][j] - b.x[i][j]);
                }
            }
        return temp;
    }

//Subtract two 4X4 matrices
Matrix4X4 subtractMatrices(Matrix4X4 a, Matrix4X4 b)
{
      Matrix4X4 temp;

        for(int i = 0;i<4;i++)
            {
            for(int j=0;j<4;j++)
                {
                temp.x[i][j] = (a.x[i][j] - b.x[i][j]);
                }
            }
        return temp;
    }

//Multiply a matrix by a scalar value.
Matrix3X3 scalarMultiply(Matrix3X3 a, float scale)
    {
      Matrix3X3 temp;

      for(int i = 0;i<3;i++)
        {
        for(int j=0;j<3;j++)
          {
           temp.x[i][j] = (a.x[i][j] * scale);
           }
         }
      return temp;
    }

//Multiply a matrix by a scalar value.
Matrix4X4 scalarMultiply(Matrix4X4 a, float scale)
    {
      Matrix4X4 temp;

      for(int i = 0;i<4;i++)
        {
        for(int j=0;j<4;j++)
          {
           temp.x[i][j] = (a.x[i][j] * scale);
           }
         }
      return temp;
    }

//multiply two 3X3 Matrices together
Matrix3X3 multiply3X3Matrices(Matrix3X3 a, Matrix3X3 b)
     {
      Matrix3X3 temp = createFixed3X3Matrix(0);

       for(int i = 0;i<3;i++)
          {
          for(int j=0;j<3;j++)
             {
             for(int k=0;k<3;k++)
                 {
                    temp.x[i][j] += (a.x[i][k] * b.x[k][j]);
                 }
              }
           }
       return temp;
      }
//Multiply a 3X3 and a 3X1 together
 Matrix3X1 multiplyMatrixNxM(Matrix3X3 a, Matrix3X1 b)
    {
       Matrix3X1 temp;
       temp.x[0] = 0.0f;
       temp.x[1] = 0.0f;
       temp.x[2] = 0.0f;

             for(int i=0;i<3;i++)
             {
              for(int j=0;j<3;j++)
              {  
               temp.x[i] += (a.x[i][j] * b.x[j]);
              }
             }
                     
       return temp;
    }

//Multiply a 4X4 and a 4X1 together
Matrix4X1 multiplyMatrixNxM(Matrix4X4 a, Matrix4X1 b)
 {
       Matrix4X1 temp;
       temp.x[0] = 0.0f;
       temp.x[1] = 0.0f;
       temp.x[2] = 0.0f;
       temp.x[3] = 0.0f;

             for(int i=0;i<4;i++)
             {
              for(int j=0;j<4;j++)
              {  
               temp.x[i] += (a.x[i][j] * b.x[j]);
              }
             }
                     
       return temp;
    }

//multiply two 4X4 Matrices together
Matrix4X4 multiply4X4Matrices(Matrix4X4 a, Matrix4X4 b)
     {
      Matrix4X4 temp = createFixed4X4Matrix(0.0);

         for(int i = 0;i<4;i++)
          {
           for(int j=0;j<4;j++)
             {
              for(int k =0;k<4;k++)
                  {
                    temp.x[i][j] += (a.x[i][k] * b.x[k][j]);
                   // cout<<temp.x[i][j];
                  }
               
              }
           }
       return temp;
      }

 //Automaticaly transpose a 3X3 matrix. 
 Matrix3X3 transpose3X3Matrix(Matrix3X3 a)
     {
      Matrix3X3 temp;
         for(int i = 0;i<3;i++)
          {
           for(int j=0;j<3;j++)
             {
               temp.x[i][j] = a.x[j][i];
              }
           }
       return temp;
      }

//Automaticaly transpose a 4X4 matrix.
Matrix4X4 transpose4X4Matrix(Matrix4X4 a)
     {
      Matrix4X4 temp;
         for(int i = 0;i<4;i++)
          {
           for(int j=0;j<4;j++)
             {
               temp.x[i][j] = a.x[j][i];
              }
           }
       return temp;
      }

 //Print out a matrix
 void printMatrix(Matrix3X3 a)
    {
       for(int i = 0;i<3;i++)
            {
            for(int j=0;j<3;j++)
                {
                float temp = a.x[i][j];
                 cout<<temp<<" ";
                }
             cout<<"\n";
            }
    }

//Print out a matrix
 void printMatrix(Matrix3X1 a)
    {
       for(int i = 0;i<3;i++)
            {
              float temp = a.x[i];
              cout<<temp<<" ";
              cout<<"\n";
            }
    }

//Print out a matrix
 void printMatrix(Matrix4X1 a)
    {
       for(int i = 0;i<4;i++)
            {
              float temp = a.x[i];
              cout<<temp<<" ";
              cout<<"\n";
            }
    }

//Print out a matrix
void printMatrix(Matrix4X4 a)
    {
       for(int i = 0;i<4;i++)
            {
            for(int j=0;j<4;j++)
                {
                float temp = a.x[i][j];
                 cout<<temp<<" ";
                }
             cout<<"\n";
            }
    }

//End MatrixLib.h