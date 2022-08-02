#ifdef __BORLANDC__
// turn off Borland warning message about comparison of signed and
// unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

#ifndef SORTING_ALGORITHMS
#define SORTING_ALGORITHMS

#include <vector>
#include <queue>

#include "d_heap.h"	// heap function library

using namespace std;

// sort an integer array using selection sort
void selectionSort(int arr[], int n);

// sort an array of type T using selection sort
template <typename T>
void selectionSort(T arr[], int n);

// sort a vector of type T using selection sort
template <typename T>
void selectionSort(vector<T>& v);

// sort a vector of type T using insertion sort
template <typename T>
void insertionSort(vector<T>& v);

// sort the elements of a vector of type T in the range
// [first, last) using insertion sort
template <typename T>
void insertionSort(vector<T>& v, int first, int last);

// sort v using the radix sort. each integer has d digits
void radixSort(vector<int>& v, int d);

// sort a vector using heapsort
template <typename T, typename Compare>
void heapSort (vector<T>& v, Compare comp);

// the elements in the ranges [first,mid) and [mid,last) are
// ordered. the function merges the ordered sequences into
// an ordered sequence in the range [first,last)
template <typename T>
void merge(vector<T>& v, int first, int mid, int last);

// sorts v in the index range [first,last) by merging
// ordered sublists
template <typename T>
void mergeSort(vector<T>& v, int first, int last);

// using the value at the midpoint of [first,last) as the pivot,
// locate the pivot in its final location so all elements
// to its left are <= to its value and all elements to the
// right are >= to its value. return the index of the pivot
template <typename T>
int pivotIndex(vector<T>& v, int first, int last);

// sort a vector using quicksort
template <typename T>
void quicksort(vector<T>& v, int first, int last);

// locate the kth largest element of v at index k
template <typename T>
void findK(vector<T>& v, int first, int last, int k);

// IMPLEMENTATIONS

void selectionSort(int arr[], int n)
{
   int smallIndex; // index of smallest element in the sublist
   int pass, j;
	int temp;

   // pass has the range 0 to n-2
   for (pass = 0; pass < n-1; pass++)
   {
		// scan the sublist starting at index pass
		smallIndex = pass;

		// j traverses the sublist arr[pass+1] to arr[n-1]
		for (j = pass+1; j < n; j++)
         // update if smaller element found
			if (arr[j] < arr[smallIndex])
				smallIndex = j;

		// if smallIndex and pass are not the same location,
		// exchange the smallest item in the sublist with arr[pass]
		if (smallIndex != pass)
		{
			temp = arr[pass];
			arr[pass] = arr[smallIndex];
			arr[smallIndex] = temp;
		}
	}
}

template <typename T>
void selectionSort(T arr[], int n)
{
   int smallIndex; // index of smallest element in the sublist
   int pass, j;
	T temp;

   // pass has the range 0 to n-2
   for (pass = 0; pass < n-1; pass++)
   {
		// scan the sublist starting at index pass
		smallIndex = pass;

		// j traverses the sublist arr[pass+1] to arr[n-1]
		for (j = pass+1; j < n; j++)
         // update if smaller element found
			if (arr[j] < arr[smallIndex])
				smallIndex = j;

		// if smallIndex and pass are not the same location,
		// exchange the smallest item in the sublist with arr[pass]
		if (smallIndex != pass)
		{
			temp = arr[pass];
			arr[pass] = arr[smallIndex];
			arr[smallIndex] = temp;
		}
	}
}

template <typename T>
void selectionSort(vector<T>& v)
{
   // index of smallest item in each pass
	int smallIndex;
	// save the vector size in n
	int pass, j, n = v.size();
	T temp;

	// sort v[0]..v[n-2], and arr[n-1] is in place
	for (pass = 0; pass < n-1; pass++)
	{
		// start the scan at index pass; set smallIndex to pass
		smallIndex = pass;
		// j scans the sublist v[pass+1]..v[n-1]
      for (j = pass+1; j < n; j++)
         // update smallIndex if smaller element is found
         if (v[j] < v[smallIndex])
            smallIndex = j;
      // when finished, place smallest item in arr[pass]
      if (smallIndex != pass)
		{
			temp = v[pass];
			v[pass] = v[smallIndex];
			v[smallIndex] = temp;
		}
   }
}

template <typename T>
void insertionSort(vector<T>& v)
{
   int i, j, n = v.size();
   T target;

	// place v[i] into the sublist
	//   v[0] ... v[i-1], 1 <= i < n,
	// so it is in the correct position
   for (i = 1; i < n; i++)
   {
      // index j scans down list from v[i] looking for
      // correct position to locate target. assigns it to
      // v[j]
      j = i;
      target = v[i];
      // locate insertion point by scanning downward as long
      // as target < v[j-1] and we have not encountered the
      // beginning of the list
      while (j > 0 && target < v[j-1])
      {
         // shift elements up list to make room for insertion
         v[j] = v[j-1];
         j--;
      }
      // the location is found; insert target
      v[j] = target;
   }
}

template <typename T>
void insertionSort(vector<T>& v, int first, int last)
{
   int i, j;
   T target;

	// place v[i] into the sublist
	//   v[first] ... v[i-1], first <= i < last,
	// so it is in the correct position
   for (i = first+1; i < last; i++)
   {
      // index j scans down list from v[i] looking for
      // correct position to locate target. assigns it to
      // v[j]
      j = i;
      target = v[i];
      // locate insertion point by scanning downward as long
      // as target < v[j-1] and we have not encountered the
      // beginning of the range
      while (j > first && target < v[j-1])
      {
         // shift elements up list to make room for insertion
         v[j] = v[j-1];
         j--;
      }
      // the location is found; insert target
      v[j] = target;
   }
}

// support function for radixSort()
// distribute vector elements into one of 10 queues
// using the digit corresponding to power
//   power = 1    ==> 1's digit
//   power = 10   ==> 10's digit
//   power = 100  ==> 100's digit
//   ...
void distribute(const vector<int>& v, queue<int> digitQueue[],
                int power)
{
	int i;

	// loop through the vector, inserting each element into
	// the queue (v[i] / power) % 10
	for (i = 0; i < v.size(); i++)
		digitQueue[(v[i] / power) % 10].push(v[i]);
}

// support function for radixSort()
// gather elements from the queues and copy back to the vector
void collect(queue<int> digitQueue[], vector<int>& v)
{
	int i = 0, digit;

	// scan the vector of queues using indices 0, 1, 2, etc.
	for (digit = 0; digit < 10; digit++)
		// collect items until queue empty and copy items back
		// to the vector
		while (!digitQueue[digit].empty())
		{
			v[i] = digitQueue[digit].front();
			digitQueue[digit].pop();
			i++;
		}
}

void radixSort(vector<int>& v, int d)
{
	int i;
	int power = 1;
	queue<int> digitQueue[10];

	for (i=0;i < d;i++)
	{
		distribute(v, digitQueue, power);
		collect(digitQueue, v);
		power *= 10;
	}
}

template <typename T, typename Compare>
void heapSort (vector<T>& v, Compare comp)
{
	// "heapify" the vector v
	makeHeap(v, comp);

	int i, n = v.size();

	// iteration that determines elements v[n-1] ... v[1]
	for(i = n; i > 1;i--)
	{
		// call popHeap() to move next largest to v[n-1]
		popHeap(v, i, comp);
	}
}

template <typename T>
void merge(vector<T>& v, int first, int mid, int last)
{
	// temporary vector to merge the sorted sublists
	vector<T> tempVector;
	int indexA, indexB, indexV;

	// set indexA to scan sublistA (index range [first,mid)
	// and indexB to scan sublistB (index range [mid, last)
	indexA = first;
	indexB = mid;

	// while both sublists are not exhausted, compare v[indexA] and
	// v[indexB]copy the smaller to vector temp using push_back()
	while (indexA < mid && indexB < last)
		if (v[indexA] < v[indexB])
		{
			tempVector.push_back(v[indexA]);	// copy element to temp
			indexA++;								// increment indexA
		}
		else
		{
			tempVector.push_back(v[indexB]);	// copy element to temp
			indexB++;								// increment indexB
		}

	// copy the tail of the sublist that is not exhausted
	while (indexA < mid)
	{
		tempVector.push_back(v[indexA]);
		indexA++;
	}

	while (indexB < last)
	{
		tempVector.push_back(v[indexB]);
		indexB++;
	}

	// copy vector tempVector using indexV to vector v using indexA
	// which is initially set to first
	indexA = first;

	// copy elements from temporary vector to original list
	for (indexV = 0; indexV < tempVector.size(); indexV++)
	{
		v[indexA] = tempVector [indexV];
		indexA++;
	}
}

// sorts v in the index range [first,last) by merging
// ordered sublists
template <typename T>
void mergeSort(vector<T>& v, int first, int last)
{
	// if the sublist has more than 1 element continue
	if (first + 1 < last)
  {
		// for sublists of size 2 or more, call mergeSort()
		// for the left and right sublists and then
		// merge the sorted sublists using merge()
		int midpt = (last + first) / 2;

		mergeSort(v, first, midpt);
		mergeSort(v, midpt, last);
		merge(v, first, midpt, last);
   }
}


template <typename T>
int pivotIndex(vector<T>& v, int first, int last)
{
	// index for the midpoint of [first,last) and the
	// indices that scan the index range in tandem
	int mid, scanUp, scanDown;
	// pivot value and object used for exchanges
	T pivot, temp;

	if (first == last)
		return last;
	else if (first == last-1)
		return first;
	else
	{
		mid = (last + first)/2;
		pivot = v[mid];

		// exchange the pivot and the low end of the range
		// and initialize the indices scanUp and scanDown.
		v[mid] = v[first];
		v[first] = pivot;

		scanUp = first + 1;
		scanDown = last - 1;

		// manage the indices to locate elements that are in
		// the wrong sublist; stop when scanDown <= scanUp
		for(;;)
		{
			// move up lower sublist; stop when scanUp enters
			// upper sublist or identifies an element >= pivot
			while (scanUp <= scanDown && v[scanUp] < pivot)
				scanUp++;

			// scan down upper sublist; stop when scanDown locates
			// an element <= pivot; we guarantee we stop at arr[first]
			while (pivot < v[scanDown])
				scanDown--;

			// if indices are not in their sublists, partition complete
			if (scanUp >= scanDown)
				break;

			// indices are still in their sublists and identify
			// two elements in wrong sublists. exchange
			temp = v[scanUp];
			v[scanUp] = v[scanDown];
			v[scanDown] = temp;

			scanUp++;
			scanDown--;
		}

		// copy pivot to index (scanDown) that partitions sublists
		// and return scanDown
		v[first] = v[scanDown];
		v[scanDown] = pivot;
		return scanDown;
	}
}

template <typename T>
void quicksort(vector<T>& v, int first, int last)
{
   // index of the pivot
   int pivotLoc;
	// temp used for an exchange when [first,last) has
	// two elements
	T temp;

   // if the range is not at least two elements, return
   if (last - first <= 1)
		return;

	// if sublist has two elements, compare v[first] and
	// v[last-1] and exchange if necessary
   else if (last - first == 2)
	{
		if (v[last-1] < v[first])
		{
			temp = v[last-1];
			v[last-1] = v[first];
			v[first] = temp;
		}
		return;
	}
   else
	{
		pivotLoc = pivotIndex(v, first, last);

		// make the recursive call
		quicksort(v, first, pivotLoc);

		// make the recursive call
		quicksort(v, pivotLoc +1, last);
	}
}

template <typename T>
void findK(vector<T>& v, int first, int last, int k)
{
	int index;

	// partition range [first,last) in v about the
	// pivot v[index]
	index = pivotIndex(v, first, last);

	// if index == k, we are done. kth largest is v[k]
	if (index == k)
		return;
	else if(k < index)
		// search in lower sublist [first,index)
		findK(v, first, index, k);
	else
		// search in upper sublist [index+1,last)
		findK(v, index+1, last, k);
}

#endif   // SORTING_ALGORITHMS
