#ifndef FIBONACCI_NUMBERS
#define FIBONACCI_NUMBERS

#include <vector>

using namespace std;

// recursive computation of the nth Finonacci number
int fib(int n);

// computation of the nth Fibonacci number using top down
// dynamic programming to avoid redundant recursive
// function calls
int fibDyn(int n, vector<int>& fibList);

int fib(int n)
{
	if (n <= 1)								// stopping conditions
		return n;
	else
		return fib(n-1) + fib(n-2);	// recursive step
}

int fibDyn(int n, vector<int>& fibList)
{
	int fibValue;

	// check for a previously computed result and return
	if (fibList[n] >= 0)
		return fibList[n];
	
	// otherwise execute the recursive algorithm to obtain the result

	// stopping conditions
	if (n <= 1)
		fibValue = n;
	else
		// recursive step
		fibValue = fibDyn(n-1, fibList) + fibDyn(n-2, fibList);
	
	// store the result and return its value
	fibList[n] = fibValue;
	return fibValue; 
}


#endif	// FIBONACCI_NUMBERS
