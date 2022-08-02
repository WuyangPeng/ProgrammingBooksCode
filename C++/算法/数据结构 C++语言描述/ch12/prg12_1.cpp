// File: prg12_1.cpp
// the program demonstrates the use of function object types.
// it declares the function object types greaterThan and lessThan,
// whose objects evaluate the operators > and < respectively.
// a modified version of the insertion sort takes a second
// template argument that corresponds to a function object
// type. the function object is used to order elements. in
// this way, the function can sort a vector in either ascending
// or descending order. the program declares a vector and calls
// insertionSort() to order the values both ways. in each case,
// writeVector() outputs the sorted values

#include <iostream>
#include <vector>

#include "d_util.h"		// for writeVector()

using namespace std;

// objects of type greaterThan<T> evaluate x > y
template<typename T>
class greaterThan 
{
	public:
		bool operator() (const T& x, const T& y) const
		{
			return x > y;
		}
};

// objects of type lessThan<T> evaluate x < y
template<typename T>
class lessThan 
{
	public:
		bool operator() (const T& x, const T& y) const
		{
			return x < y;
		}
};

// use the insertion sort to order v using function object comp 
template <typename T, typename Compare>
void insertionSort(vector<T>& v, Compare comp);

int main()
{
	int arr[] = {2, 1, 7, 8, 12, 15, 3, 5};
	int arrSize = sizeof(arr)/sizeof(int);
	vector<int> v(arr, arr+arrSize);

	// put the vector in ascending order 
	insertionSort(v, lessThan<int>());
	// output it
	writeVector(v);
	cout << endl;

	// put the vector in descending order 
	insertionSort(v, greaterThan<int>());
	// output it
	writeVector(v);
	cout << endl;

	return 0;
}


template <typename T, typename Compare>
void insertionSort(vector<T>& v, Compare comp)
{
   int i, j, n = v.size();
   T temp;

	// place v[i] into the sublist
	//   v[0] ... v[i-1], 1 <= i <= n-1,
	// so it is in the correct position
   for (i = 1; i < n; i++) 
   {
      // index j scans down list from v[i] looking for
      // correct position to locate target. assigns it to
      // v[j]
      j = i;
      temp = v[i];
      // locate insertion point by scanning downward as long
      // as comp(temp, v[j-1]) is true and we have not encountered
		// the beginning of the list
      while (j > 0 && comp(temp, v[j-1]))
      { 
         // shift elements up list to make room for insertion
         v[j] = v[j-1];
         j--;
      }
      // the location is found; insert temp
      v[j] = temp;
   }
}

/*
Run:

1  2  3  5  7  8  12  15

15  12  8  7  5  3  2  1
*/
