#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_2.cpp
// the program prompts the user for an integer upper limit and calls the
// function sieve() that applies the Sieve of Eratosthenes. it creates a
// set containing all the primes between 2 and the upper limit. using a set
// iterator, the program outputs all the primes, 10 per line

#include <iostream>
#include <iomanip>
#include <set>

using namespace std;

// apply the Sieve of Eratosthenes to remove all non-prime numbers from 
// the integer set s = {2, 3, 4, ..., n}
void sieve(set<int>& s, int n);

int main()
{
	// set to hold the prime numbers
	set<int> primeSet;

	// used to output the final set of primes 10 numbers per line
	set<int>::iterator iter;
	int primeLimit, count = 0;

	cout << "Enter upper limit for the set of primes: ";
	cin >> primeLimit;
	// use the sieve of Eratosthenes to remove the non-primes
	sieve(primeSet, primeLimit);

	// use iterator to scan the resulting set; output 10 elements per line
	iter = primeSet.begin();
	while (iter != primeSet.end())
	{
		count++;
		cout << setw(5) << *iter;
		if (count % 10 == 0)
			cout << endl;
		iter++;
	}
	cout << endl;

	return 0;
}	

void sieve(set<int>& s, int n)
{
	int m, i;

	// erase any previous values in s
	s.erase(s.begin(), s.end());

	// load the set with integers 2, 3, . . ., n
	for (m = 2; m < n; m++)
		s.insert(m);

	// find the primes using the Sieve of Eratosthenes.
	// look at all numbers from m = 2 to m * m > n ( n <= sqrt(n))
	for (m = 2; m * m <= n; m++)
		// check is m is still in the set; if so remove all higher 
		// multiples of m starting with j = 2*m. 
		if(s.find(m) != s.end())
		{
			i = 2 * m;			// i is successive multiples of m
			while (i <= n)
			{
				s.erase(i);
				i += m;			// update i to the next multiple of m
			}
		}
}

/*
Run:

Enter upper limit for the set of primes: 280
    2    3    5    7   11   13   17   19   23   29
   31   37   41   43   47   53   59   61   67   71
   73   79   83   89   97  101  103  107  109  113
  127  131  137  139  149  151  157  163  167  173
  179  181  191  193  197  199  211  223  227  229
  233  239  241  251  257  263  269  271  277
*/
