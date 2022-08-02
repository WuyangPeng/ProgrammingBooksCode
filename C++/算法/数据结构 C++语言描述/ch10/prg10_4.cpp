// File: prg10_4.cpp
// the program initializes the vector, v, with values from the
// integer array, arr, that contains duplicates. a call to
// removeDuplicates() with argument v removes the duplicate values.
// the program concludes by displaying the unique values in v using
// writeVector()

#include <iostream>
#include <vector>

#include "d_stree.h"		// stree class
#include "d_util.h"		// for writeVector()

using namespace std;

// remove duplicate values from v and leave
// the remaining values in sorted order
template <typename T>
void removeDuplicates(vector<T>& v);

int main()
{
	int arr[] = {3, 6, 3, 33, 55, 5, 55, 15, 25, 3, 5, 2, 5, 3, 55};
	int arrSize = sizeof(arr)/sizeof(int);
	vector<int> v(arr, arr+arrSize);

	// remove duplicates and sort
	removeDuplicates(v);
	// output the modified vector
	writeVector(v);
	cout << endl;

	return 0;
}

template <typename T>
void removeDuplicates(vector<T>& v)
{
   // insert vector data into binary search tree t
   stree<T> t;
   // declare iterators for t and v
	stree<T>::iterator treeIter;
	vector<T>::iterator vectorIter;
   
   // insert each vector element into the search tree,
	// ignoring duplicate values
   vectorIter = v.begin();
	while (vectorIter != v.end())
	{
	  t.insert(*vectorIter);
	  vectorIter++;
	}
   
	// clear the vector
	v.resize(0);

   // traverse tree in ascending order, pushing each element
	// onto the back of v using push_back()
   treeIter = t.begin();
	
	while (treeIter != t.end())
	{
      v.push_back(*treeIter);
		treeIter++;
	}
}

/*
Run:

2  3  5  6  15  25  33  55
*/
