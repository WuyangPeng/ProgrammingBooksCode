/////////////////////////////////////////////////////////////////////////
// MatrixDriver.cpp
// by Dustin Clingman  1/16/04
//
// Purpose: This program demonstrates several math usages of matrices.
//
//////////////////////////////////////////////////////////////////////////

#include "MatrixLib.h"

void showSelection();
void testEquality();
void Add();
void Subtract();
void MultiplyByScalar();
void MultiplyMatrices();
void MultiplyDiffMatrices();
void Transpose();

int main()
{
    int choice;

    showSelection();
    cin>>choice;

    while(choice != 9)
    {
      switch(choice)
       {
           case 1:
                 testEquality();
                 break;
           case 2:
                 Add();
                 break;
           case 3:
                 Subtract();
                 break;
           case 4:
                 MultiplyByScalar();
                 break;
           case 5:
                 MultiplyMatrices();
                 break;
           case 6:
                 MultiplyDiffMatrices();
                 break;
           case 7:
                 Transpose();
                 break;
           default:
           cout<<"That is not a valid selection, Please try again.";
           break;
       }
      showSelection();
      cin>>choice;
     }//end while

  return 0;
}

void showSelection()
     {
      cout<<"\n";
      cout<<"Welcome to Matrix Theme Park!\n";
      cout<<"Please select a matrix operation\n"; 
      cout<<"[1] Test two random 3X3 matrices for equality\n";
      cout<<"[2] Add two random 3X3 matrices\n";
      cout<<"[3] Subtract two random 3X3 matrices\n";
      cout<<"[4] Multiply a random matrix by a scalar\n";
      cout<<"[5] Multiply two same size matrices\n";
      cout<<"[6] Multiply two different size matrices\n";
      cout<<"[7] Transpose a random matrix\n";
      cout<<"\n";
	  cout<<"Enter [9] to exit\n";
      cout<<"\n";
    }


void testEquality()
    {
        int seed;
        cout<<"Lets test the equality of two random 3X3 matrices\n";
        cout<<"Please enter a seed for the random function.\n";
        cout<<"\n";
        cin>>seed;
        Matrix3X3 A = createRandom3X3Matrix(seed);
        printMatrix(A);
        cout<<"\n";
        Matrix3X3 B = createRandom3X3Matrix(seed);
        printMatrix(B);
        cout<<"\n";

        if(!areMatricesEqual(A,B))
            cout<<"These Matrices are not equal.\n";
        else
            cout<<"These Matrices are equal.\n";
    }

void Add()
    {
      Matrix3X3 temp;
      int seed;

      cout<<"Lets add two random 3X3 matrices\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"\n";
      Matrix3X3 B = createRandom3X3Matrix(seed);
      printMatrix(B);
      cout<<"\n";
      
      temp = addMatrices(A,B);
      cout<<"The sum of these matrices is:\n";
      printMatrix(temp);
      cout<<"\n";
    
    }
void Subtract()
    {
      Matrix3X3 temp;
      int seed;

      cout<<"Lets subtract two random 3X3 matrices\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"\n";
      Matrix3X3 B = createRandom3X3Matrix(seed);
      printMatrix(B);
      cout<<"\n";
      
      temp = subtractMatrices(B,A);
      cout<<"The difference of these matrices is:\n";
      printMatrix(temp);
      cout<<"\n";
    
    }
void MultiplyByScalar()
    {
      Matrix3X3 temp;
      float scalar;
      int seed;

      cout<<"Lets multiply a random matrix by a scalar value\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"Now enter a scalar value to multiply with\n";
      cin>>scalar;
      cout<<"\n";
      
      temp = scalarMultiply(A,scalar);
      cout<<"The scaled matrix is is:\n";
      printMatrix(temp);
      cout<<"\n";
    
    }
void MultiplyMatrices()
    {
      Matrix3X3 temp;
      int seed;

      cout<<"Lets multiply a two 3X3 random matrices\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"\n";

      Matrix3X3 B = createRandom3X3Matrix(seed);
      printMatrix(B);
      cout<<"\n";
      
      temp = multiply3X3Matrices(A,B);
      cout<<"The multiplied matrix is is:\n";
      printMatrix(temp);
      cout<<"\n";   
    }

void MultiplyDiffMatrices()
    {
    
      Matrix3X1 temp;
      int seed;

      cout<<"Lets multiply random 3X3 and a 3X1  matrices\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"\n";

      Matrix3X1 B = createRandom3X1Matrix(seed);
      printMatrix(B);
      cout<<"\n";
      
      temp = multiplyMatrixNxM(A,B);
      cout<<"The multiplied matrix is is:\n";
      printMatrix(temp);
      cout<<"\n";
    
    }
void Transpose()
    {
      Matrix3X3 temp;
      float scalar;
      int seed;

      cout<<"Lets transpose a random matrix!\n";
      cout<<"Please enter a seed for the random function.\n";
      cout<<"\n";
      cin>>seed;
      Matrix3X3 A = createRandom3X3Matrix(seed);
      printMatrix(A);
      cout<<"\n";
      temp = transpose3X3Matrix(A);
      printMatrix(temp);
      cout<<"\n";

    
    
    }
 
//End MatrixDriver.cpp
