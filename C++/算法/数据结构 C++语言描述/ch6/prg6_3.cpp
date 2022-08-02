// File: prg6_3.cpp
// the program declares an unordered integer array,
// arr, containing duplicate values. it builds the
// ordered list, intList, by inserting each element
// of arr into the list using insertOrder(). calling
// removeDuplicates() transforms intList into a list
// of unique values. the program uses writeSeqList()
// to output the list before and after removing
// duplicates

#include <iostream>
#include <list>

#include "d_listl.h"		// for insertOrder() and removeDuplicates()
#include "d_util.h"		// for writeList()

using namespace std;

int main()
{
	// declare an unordered array with duplicate values
	int arr[] = {7, 2, 2, 9, 3, 5, 3, 9, 7, 2}, i;
	int arrSize = sizeof(arr)/sizeof(int);
	list<int> intList;

	// build the ordered list using elements from the array 
	for (i = 0; i < arrSize; i++)
		insertOrder(intList, arr[i]);

	// output the ordered list with duplicates
	cout << "Ordered list with duplicates: ";
	writeList(intList);

	// remove duplicate values
	removeDuplicates(intList);

	// output the ordered list that has no duplicates
	cout << "Ordered list without duplicates: ";
	writeList(intList);

	return 0;
}

/*
Run:

Ordered list with duplicates: 2  2  2  3  3  5  7  7  9  9
Ordered list without duplicates: 2  3  5  7  9
*/
