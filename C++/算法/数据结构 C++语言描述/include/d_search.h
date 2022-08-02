#ifndef SEARCH_FUNCTIONS
#define SEARCH_FUNCTIONS

#include <vector>
#include <list>

using namespace std;

// perform a sequential search of an integer array for a target
// in the index range [first, last). return the index of a
// match or last if the target is not in arr
int seqSearch(const int arr[], int first, int last, int target);

// perform  asequential search for a target in the index range
// [first, last).  return the index of a match or last if the
// target is not in arr
template <typename T>
int seqSearch(const T arr[], int first, int last, const T& target);

// perform a binary search of an integer array for a target
// in the index range [first, last). return the index of a
// match or last if the target is not in arr
int binSearch(const int arr[], int first, int last, int target);

// perform a binary search of an array for a target
// in the index range [first, last). return the index of a
// match or last if the target is not in arr
template <typename T>
int binSearch(const T arr[], int first, int last, const T& target);

// vector version of the sequential search
template <typename T>
int seqSearch(const vector<T>& v, int first, int last, const T& target);

// vector version of the binary search
template <typename T>
int binSearch(const vector<T>& v, int first, int last, const T& target);

// perform the sequential search for target in the list
// iterator range [first, last). return an iterator pointing
// at the target in the list or last if target is not found
template <typename T>
typename list<T>::iterator seqSearch(typename list<T>::iterator first,
									 typename list<T>::iterator last, const T& target);

// perform the sequential search for target in the container
// iterator range [first, last). return an iterator pointing
// at the target in the container or last if target is not
// found
template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& target);

// ***********************************************************
//      search function implementations
// ***********************************************************

int seqSearch(const int arr[], int first, int last, int target)
{
	int i;

   // scan indices in the range first <= i < last
	for(i=first; i < last; i++)
		if (arr[i] == target)
			return i;				// immediately return on a match

	return last;					// return last if target not found
}

template <typename T>
int seqSearch(const T arr[], int first, int last, const T& target)
{
	int i;

   // scan indices in the range first <= i < last
	for(i=first; i < last; i++)
		if (arr[i] == target)	// assume T has the "==" operator
			return i;				// immediately return on a match

	return last;					// return last if target not found
}

int binSearch(const int arr[], int first, int last, int target)
{
	int mid;						// index of the midpoint
	int midValue;				// object that is assigned arr[mid]
	int origLast = last;		// save original value of last
	
	while (first < last)		// test for nonempty sublist
	{
		mid = (first+last)/2;
		midValue = arr[mid];
		if (target == midValue)
			return mid;			// have a match
      // determine which sublist to search
		else if (target < midValue)
			last = mid;			// search lower sublist. reset last
		else
			first = mid+1;		// search upper sublist. reset first
	}

	return origLast;			// target not found
}

template <typename T>
int binSearch(const T arr[], int first, int last, const T& target)
{
	int mid;						// index of the midpoint
	T midValue;					// object that is assigned arr[mid]
	int origLast = last;		// save original value of last
	
	while (first < last)		// test for nonempty sublist
	{
		mid = (first+last)/2;
		midValue = arr[mid];
		if (target == midValue)
			return mid;			// have a match
      // determine which sublist to search
		else if (target < midValue)
			last = mid;			// search lower sublist. reset last
		else
			first = mid+1;		// search upper sublist. reset first
	}

	return origLast;			// target not found
}

template <typename T>
int seqSearch(const vector<T>& v, int first, int last, const T& target)
{
	int i;

   // scan indices in the range first <= i < last
	for(i=first; i < last; i++)
		if (v[i] == target)		// assume T has the "==" operator
			return i;				// immediately return on a match

	return last;					// otherwise return last
}

template <typename T>
int binSearch(const vector<T>& v, int first, int last, const T& target)
{
	int mid;						// index of the midpoint
	T midvalue;					// object that is assigned v[mid]
	int origLast = last;		// save original value of last
	
	while (first < last)		// test for nonempty sublist
	{
		mid = (first+last)/2;
		midvalue = v[mid];
		if (target == midvalue)
			return mid;			// have a match
      // determine which sublist to search
		else if (target < midvalue)
			last = mid;			// search lower sublist. reset last
		else
			first = mid+1;		// search upper sublist. reset first
	}

	return origLast;			// target not found
}

template <typename T>
typename list<T>::iterator seqSearch(typename list<T>::iterator first,
									 typename list<T>::iterator last, const T& target)
{
	// start at location first
	list<T>::iterator iter = first;

	// compare list elements with item until either
	// we arrive at last or locate item 
	while(iter != last && !(*iter == target))
		iter++;

	// iter either points at item or is last
	return iter;
}

template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& target)
{
	Iterator iter = first;

	// scan iterator range [first, last), stopping
	// if the loop locates target
	while (iter != last && *iter != target)
		iter++;

	// if target located, iter points at it; otherwise
	// is has value last
	return iter;
}

#endif   // SEARCH_FUNCTIONS
