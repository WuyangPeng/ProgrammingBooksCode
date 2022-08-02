#ifndef COMPUTING_COMBINATIONS
#define COMPUTING_COMBINATIONS

#include "d_matrix.h"

using namespace std;

// recursive computation of C(n,k)
int comm(int n, int k);

// computation of C(n,k) using top down dynamic programming
// to avoid redundant recursive function calls
int commDyn(int n, int k, matrix<int>& commMat);

// computation of C(n,k) using bottom up dynamic programming
int commDynB(int n, int k);

int comm(int n, int k)
{
	if (n == k || k == 0)						// stopping condition
		return 1;
	else if (k == 1)
		return n;									// stopping condition
	else
		return comm(n-1,k) + comm(n-1,k-1);	// recursive step
}

int commDyn(int n, int k, matrix<int>& commMat)
{
	int returnValue;

	// check if value is already computed
	if (commMat[n][k] != 0)
		return commMat[n][k];

	if (n == k || k == 0)						
		returnValue = 1;
	else if (k == 1)
		returnValue = n;										
	else
		// carry out the recursive step
		returnValue = commDyn(n-1,k,commMat) + commDyn(n-1,k-1,commMat);
	
	// before returning, assign value to the matrix
	commMat[n][k] = returnValue;

	return returnValue;	
}

int commDynB(int n, int k)
{
	// store all precomputed values. form Pascal's Triangle
	matrix<int> commMat(n+1,n+1);
	int i;

	// set row 0
	commMat[0][0] = 1;
	for (i = 1; i <= n; i++)
	{
		// set first and last entry to 1
		commMat[i][0] = 1;
		commMat[i][i] = 1;

		// use terms from row i-1
		for (int j = 1; j < i; j++)
			commMat[i][j] = commMat[i-1][j-1] + commMat[i-1][j];
	}
	// return value of the function
	return commMat[n][k];
}

#endif	// COMPUTING_COMBINATIONS
