#ifndef POWERSET_FUNCTIONS
#define POWERSET_FUNCTIONS

#include <iostream>
#include <set>

#include "d_setops.h"	// for set union (+)

using namespace std;

// return the power set of s
template <typename T>
set<set<T> > powerSet(set<T>& s);

// output the power set of a set with n elements
template <typename T>
void writePowerSet(set<set<T> >& pSet);

template <typename T>
set<set<T> > powerSet(set<T>& s)
{
	// empty set
	set<T> empty;
	// sPrime is power set not containing 1st element of s.
	// sPrimePlus is the collection of the subsets created
	// from sPrime by adding 1st element of s to each set
	// in sPrime
	set<set<T> > sPrime, sPrimePlus;
	// will be the power set
	set<set<T> > pset;

	if (s.size() == 0)
		// s is empty, so sPrime contains the empty set
		pset.insert(empty);
	else
	{
		// record the 1st value in s
		T temp = *(s.begin());

		// erase the first value from s and compute the
		// the power set, sPrime, of the modified set
		s.erase(s.begin());
		sPrime = powerSet(s);

		// iterator that moves through sPrime
		set<set<T> >::iterator sIter;
		// tempSet is a set in sPrime
		set<T> tempSet;

		// move through sPrime
		sIter = sPrime.begin();
		while (sIter != sPrime.end())
		{
			// get current subset from sPrime
			tempSet = *sIter;
			// insert temp into it
			tempSet.insert(temp);
			// insert the subset into sPrimePlus
			sPrimePlus.insert(tempSet);
			// move the iterator forward
			sIter++;
		}

		// the power set for s is the union of sPrime
		// and sPrimePlus
		pset = sPrime + sPrimePlus;
	}

	// return the power set
	return pset;
}

template <typename T>
void writePowerSet(set<set<T> >& pSet)
{
	int count = 0;
	set<T> s;
	set<T>::iterator sIter;
	set<set<T> >::iterator pSetIter;

	// iterator through the set of sets
	for (pSetIter = pSet.begin(); pSetIter != pSet.end(); pSetIter++)
	{
		// get a set s and increment count
		s = *pSetIter;
		count++;

		if (s.empty())
			// {} indicates s is the empty set
			cout << "{}" << "  ";
		else
		{
			// output s in the format {e1, e2, ..., em}
			sIter = s.begin();
			cout << "{";
			do
			{
				cout << *sIter;
				sIter++;
				if(sIter != s.end())
					cout << ", ";
			} while (sIter != s.end());
			cout << "}" << "  ";
		}
		// output 4 sets per line
		if (count % 4 == 0)
			cout << endl;
	}
	cout << endl;
}

#endif	// POWERSET_FUNCTIONS
