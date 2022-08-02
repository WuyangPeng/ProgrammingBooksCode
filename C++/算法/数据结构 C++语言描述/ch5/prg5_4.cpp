// File: prg5_4.cpp
// the program initializes an integer and a time24 matrix object by
// reading their data from a file. by calling the function matSum(),
// the program outputs the sum of the values in each matrix

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "d_matrix.h"
#include "d_time24.h"

using namespace std;

// return the sum of the entries in mat
template <typename T>
T matSum(const matrix<T>& mat);

int main()
{
	matrix<int> intMat;
	matrix<time24> timeMat;

	int numRows, numCols;
	int i,j;

	ifstream fin("mat.dat");

	if (!fin)
	{
		cerr << "Cannot open 'mat.dat'" << endl;
		exit(1);
	}

	fin >> numRows >> numCols;
	intMat.resize(numRows, numCols);
	for (i = 0; i < numRows; i++)
		for (j = 0; j < numCols; j++)
			fin >> intMat[i][j];
	cout << "Sum of integer matrix is " << matSum(intMat) << endl;


	fin >> numRows >> numCols;
	timeMat.resize(numRows, numCols);
	for (i = 0; i < numRows; i++)
		for (j = 0; j < numCols; j++)
			fin >> timeMat[i][j];
	cout << "Sum of time24 matrix is " << matSum(timeMat) << endl;


	return 0;
}

// return the sum of the entries in mat
template <typename T>
T matSum(const matrix<T>& mat)
{
	// declare sum and initialize it to the default value for T
	T sum = T();
	int i, j;

	// scan the rows and columns, adding each element to the running sum
	for (i = 0; i < mat.rows(); i++)
		for (j = 0; j < mat.cols(); j++)
			sum += mat[i][j];

	// return the sum as object of type T
	return sum;
}

/*
File "mat.dat"
3  4
8    1  7 -2
0   -3  4  6
10 -14  1  0
2  5
1:00   2:30  0:30  0:45  2:00 
3:00   0:15  0:45  1:45  3:15

Run:
Sum of integer matrix is 18
Sum of time24 matrix is 15:45
*/
