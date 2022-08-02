#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg15_1.cpp
// the program initializes a vector of integers and a vector of strings.
// it then applies the function mergeSort() to each vector and outputs
// the result 

#include <iostream>
#include <string>
#include <vector>

#include "d_sort.h"		// for mergeSort()
#include "d_util.h"		// for writeContainer()

using namespace std;

int main()
{
	// create an array of integers and of strings for the sort
	int intList[] = {25, 10, 7, 19, 3, 48, 12, 17, 56, 30, 21};

	string strList[] = {"Dallas","Akron","Wausau","Phoenix",
								"Fairbanks","Miami"};

	vector<int> vIntList(intList, intList+11);
	vector<string> vStrList(strList,strList+6);

	// sort and the output each vector 
	mergeSort(vIntList, 0, vIntList.size());
	cout << "Sorted integers: ";
	writeContainer(vIntList.begin(), vIntList.end(), "  ");
	cout << endl;

	mergeSort(vStrList, 0, vStrList.size());
	cout << "Sorted strings:  ";
	writeContainer(vStrList.begin(), vStrList.end() , "  ");
	cout << endl;

	return 0;
}

/*
Run:

Sorted integers: 3  7  10  12  17  19  21  25  30  48  56
Sorted strings:  Akron  Dallas  Fairbanks  Miami  Phoenix  Wausau
*/
