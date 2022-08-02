// File: prg3_1.cpp
// the program compares the efficiency of the sequential
// and binary search by timing algorithm execution using the
// timer class. two integer arrays list1 and list2
// of size ARRAY_SIZE are initialized with the same random
// integers in the range 0 to 999,999. initialize the array
// targetList having TARGET_SIZE elements to contain other
// random numbers in the same range. time the selection sort
// as it sorts list2 and output the result. using the
// elements in array targetList as target values for the
// sequential and binary searches, time each algorithm and
// output the results

#include <iostream>

#include "d_search.h"	// generic sequential and binary searches
#include "d_sort.h"		// generic selection sort
#include "d_random.h"	// random number generation
#include "d_timer.h"		// time events

using namespace std;

int main()
{	const int ARRAY_SIZE = 100000, TARGET_SIZE = 50000;

	// arrays for the search
   int list1[ARRAY_SIZE], list2[ARRAY_SIZE], targetList[TARGET_SIZE];
	int i;

	// t used for timing the search algorithms
	timer t;
	// random number object
	randomNumber rnd;

	// initialize the arrays with random numbers in the
   // range 0 to 999,999 
   for (i = 0; i < ARRAY_SIZE; i++)
		list1[i] = list2[i] = rnd.random(1000000);

	// initialize targetList with random numbers in the
   // same range 0 to 999,999 
	for (i=0;i < TARGET_SIZE; i++)
		targetList[i] = rnd.random(1000000);

	// sort list2
   cout << "Timing the Selection Sort" << endl;
	t.start();		// start timer
	selectionSort(list2,ARRAY_SIZE);
	t.stop();		// stop timer
	cout << "Selection Sort takes " << t.time()
		  << " seconds." << endl;

   cout << endl << "Timing the Sequential Search" << endl;
	t.start();		// start timer
	// perform sequential search with elements from list2
 	for (i = 0; i < TARGET_SIZE; i++)
		seqSearch(list1,0,ARRAY_SIZE,targetList[i]);
	t.stop();		// stop timer
	cout << "Sequential Search takes " << t.time()
		  << " seconds." << endl;

	cout << endl << "Timing the Binary Search" << endl;
	t.start();		// start timer
	// perform binary search with elements from list1
 	for (i = 0; i < TARGET_SIZE; i++)
		binSearch(list2,0,ARRAY_SIZE,targetList[i]);
	t.stop();		// stop timer
	cout << "Binary Search takes " << t.time()
		  << " seconds." << endl;

	return 0;
}

/*
Run:

Timing the Selection Sort
Selection Sort takes 126.912 seconds.

Timing the Sequential Search
Sequential Search takes 132.889 seconds.

Timing the Binary Search
Binary Search takes 0.08 seconds.
*/
