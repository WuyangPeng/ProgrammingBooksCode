#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg15_3.cpp
// the program prompts for an integer value n and builds the set
// {1, 2, 3, ..., n}. it then calls the recursive function powerSet()
// that returns the power set of the set. the power set is the set
// of all subsets of the set and has 2^n elements. after displaying
// the size of the power set, the program calls the function
// writeAllSubsets() that outputs each subset using the notation
// {elt1, elt2, ..., eltm}

#include <iostream>
#include <set>

#include "d_pset.h"

using namespace std;

int main()
{
	int n, i;
	// set of integers whose power set we construct
	set<int> s;
	// the power set
	set<set<int> > pSet;

	cout << "Enter a number 'n' between 1 and 6: ";
	cin >> n;

	// build the set {1,2,3,...,n}
	for (i=1;i <= n; i++)
		s.insert(i);

	// build the power set
	pSet = powerSet(s);

	// output the number of subsets and the the subsets
	cout << "Number of subsets is " << pSet.size()
		  << endl << endl;
	writePowerSet(pSet);

	return 0;
}

/*
Run:

Enter a number 'n' between 1 and 6: 4
Number of subsets is 16

{}  {1}  {1, 2}  {1, 2, 3}
{1, 2, 3, 4}  {1, 2, 4}  {1, 3}  {1, 3, 4}
{1, 4}  {2}  {2, 3}  {2, 3, 4}
{2, 4}  {3}  {3, 4}  {4}
*/
