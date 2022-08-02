// File: prg14_2.cpp
// program creates 15-element vector of integers in range 0 to 99.
// a call to heapSort with greater<int>() object sorts vector in
// ascending order; second call to heapSort() with less<int>()
// sorts the list in descending order; output displays original
// list and the ordered lists

#include <iostream>
#include <vector>
#include <functional>

#include "d_sort.h"
#include "d_util.h"
#include "d_random.h"

using namespace std;

int main()
{
	// objects to store the elements and generate random numbers
	vector<int> v;
	randomNumber rnd;
	int i;

	// create a vector with 15 random integers
	for (i = 0; i < 15; i++)
		v.push_back(rnd.random(100));

	// display the original list
	cout << "Original vector" << endl << "   ";
	writeVector(v);
	cout << endl;

	// call heapSort() with greater<int>() and display results
	cout << "Sort in ascending order" << endl << "   ";
	heapSort(v,greater<int>());
	writeVector(v);
	cout << endl;

	// call heapSort() with less<int>() and display results
	cout << "Sort in descending order" << endl << "   ";
	heapSort(v,less<int>());
	writeVector(v);
	cout << endl;

	return 0;
}

/*
Run:

Original vector
   92  77  88  36  19  34  14  49  61  14  1  52  44  77  79

Sort in ascending order
   1  14  14  19  34  36  44  49  52  61  77  77  79  88  92

Sort in descending order
   92  88  79  77  77  61  52  49  44  36  34  19  14  14  1
*/
