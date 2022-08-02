// File: prg4_2.cpp
// the program generates 12 random integers in the range
// 100 to 999. add each number value to vector vSmall if
// value < 400, to vector vMedium if 400 <= value < 700
// and to vLarge if 700 <= value < 1000. apply the insertion
// sort to order each vector. use join() so that vSmall is
// the concatenation of the three vectors. sort the final list
// in vSmall by using the insertion sort. display the initial
// set of elements in each vector and the final sorted list
// by calling writeVector()

#include <iostream>
#include <vector>

#include "d_random.h"		// for randomNumber
#include "d_sort.h"			// for insertionSort()
#include "d_util.h"			// for writeVector()

using namespace std;

// attach vB onto the end of vA
template <typename T>
void join (vector<T> &vA, const vector<T>& vB);

int main()
{
	// declare 3 integer vectors
   vector<int> vSmall, vMedium, vLarge;
	// use a random number generator
	randomNumber rnd;

   int i, value;

	for (i = 0; i < 12; i++)
	{
		value = rnd.random(900) + 100;

		if (value < 400)
			vSmall.push_back(value);
		else if (value < 700 )
			vMedium.push_back(value);
		else
			vLarge.push_back(value);
	}

	// sort the vector of integers in the range
	// 100 <= n < 400 and output
	insertionSort(vSmall);
	cout << "Small:   ";
	writeVector(vSmall);

	// sort the vector of integers in the range
	// 400 <= n < 700 and output
	insertionSort(vMedium);
	cout << "Medium:  ";
	writeVector(vMedium);

	// sort the vector of integers in the range
	// 700 <= n < 1000 and output
	insertionSort(vLarge);
	cout << "Large:   ";
	writeVector(vLarge);

	// join vMedium onto the end of vSmall
	join(vSmall, vMedium);
	// join vLarge onto the end of the modified vSmall
	join(vSmall, vLarge);

	// output the new vector
	cout << "Sorted:  ";
	writeVector(vSmall);

	return 0;
}

template <typename T>
void join (vector<T> &vA, const vector<T>& vB)
{
	// capture the size of vB in sizeB
	int i, sizeB = vB.size();

	// use index i to access the elements of vB and push_back()
	// to add the elements to the rear of vA
   for (i = 0; i < sizeB; i++)
      vA.push_back(vB[i]);
}

/*
Run:

Small:   176  213  269  287  357
Medium:  482  535  551  649  687
Large:   843  901
Sorted:  176  213  269  287  357  482  535  551  649  687  843  901
*/
