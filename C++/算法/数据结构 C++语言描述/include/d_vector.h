#ifndef MINI_VECTOR
#define MINI_VECTOR

#include "d_except.h"	// include exception classes

using namespace std;

template <typename T>
class miniVector
{
	public:
		miniVector(int size = 0);
			// constructor.
			// Postconditions: allocates array with size number of elements
			// and capacity. elements are initialized to T(), the default
			// value for type T

		miniVector(const miniVector<T>& obj);
			// copy constructor
			// Postcondition: creates current vector as a copy of obj

		~miniVector();
			// destructor
			// Postcondition: the dynamic array is destroyed

		miniVector& operator= (const miniVector<T>& rhs);
			// assignment operator.
			// Postcondition: current vector holds the same data
			// as rhs

		T& back();
			// return the element at the rear of the vector.
			// Precondition: the vector is not empty. if vector
			// is empty, throws the underflowError exception

		const T& back() const;
			// const version used when miniVector object is a constant

		T& operator[] (int i);
			// provides general access to elements using an index.
			// Precondition: 0 <= i < vSize. if the index is out
			// of range, throws the indexRangeError exception

		const T& operator[] (int i) const;
			// const version used when miniVector object is a constant

		void push_back(const T& item);
			// insert item at the rear of the vector.
			// Postcondition: the vector size is increased by 1

		void pop_back();
			// remove element at the rear of the vector.
			// Precondition: vector is not empty. if the vector is
			// empty, throws the underflowError exception

		int size() const;
			// return current list size

		bool empty() const;
			// return true if vector is empty and false otherwise

		int capacity() const;
			// return the current capacity of the vector

   private:
		int vCapacity;		// amount of available space
		int vSize;			// number of elements in the list
		T *vArr;				// the dynamic array

		void reserve(int n, bool copy);
			// called by public functions only if n > vCapacity. expands
			// the vector capacity to n elements, copies the existing
			// elements to the new space if copy == true, and deletes
			// the old dynamic array. throws the memoryAllocationError
			// exception if memory allocation fails
};

// set the capacity to n elements
template <typename T>
void miniVector<T>::reserve(int n, bool copy)
{
	T *newArr;
	int i;

	// allocate a new dynamic array with n elements
	newArr = new T[n];
	if (newArr == NULL)
		throw memoryAllocationError(
			"miniVector reserve(): memory allocation failure");

	// if copy is true, copy elements from the old list to the new list
	if (copy)
		for(i = 0; i < vSize; i++)
			newArr[i] = vArr[i];

	// delete original dynamic array. if vArr is NULL, the vector was
	// originally empty and there is no memory to delete
	if (vArr != NULL)
		delete [] vArr;

	// set vArr to the value newArr. update vCapacity
	vArr = newArr;
	vCapacity = n;
}

// constructor. initialize vSize and vCapacity.
// allocate a dynamic array of vSize integers
// and initialize the array with T()
template <typename T>
miniVector<T>::miniVector(int size):
	vSize(0), vCapacity(0), vArr(NULL)
{
	int i;

	// if size is 0, vSize/vCapacity are 0 and vArr is NULL.
	// just return
	if (size == 0)
		return;

	// set capacity to size. since we are building the vector,
	// copy is false
	reserve(size, false);
	// assign size to vSize
	vSize = size;

	// copy T() into each vector element
	for (i=0;i < vSize;i++)
		vArr[i] = T();
}

// copy constructor. make the current object a copy of obj.
// for starters, use initialization list to create an empty
// vector
template <typename T>
miniVector<T>::miniVector (const miniVector<T>& obj):
	vSize(0), vCapacity(0), vArr(NULL)
{
   int i;

	// if size is 0, vSize/vCapacity are 0 and vArr is NULL.
	// just return
	if (obj.vSize == 0)
		return;

	// set capacity to obj.vSize. since we are building the vector,
	// copy is false
	reserve(obj.vSize, false);
	// assign size to obj.vSize
	vSize = obj.vSize;

	// copy items from the obj.vArr to the newly allocated array
	for (i = 0; i < vSize; i++)
		vArr[i] = obj.vArr[i];
}

// destructor. deallocate the dynamic array
template <typename T>
miniVector<T>::~miniVector()
{
	if (vArr != NULL)
		// de-allocate memory for the array
		delete [] vArr;
}

// replace existing object (left-hand operand) by
// rhs (right-hand operand)
template <typename T>
miniVector<T>& miniVector<T>::operator= (const miniVector<T>& rhs)
{
   int i;

   // check vCapacity to see if a new array must be allocated
   if (vCapacity < rhs.vSize)
		// make capacity of current object the size of rhs. don't
		// do a copy, since we will replace the old values
		reserve(rhs.vSize, false);

	// assign current object to have same size as rhs
	vSize = rhs.vSize;

   // copy items from rhs.vArr to vArr
   for (i = 0; i < vSize; i++)
      vArr[i] = rhs.vArr[i];

   return *this;
}

// check vSize and throw an underflowError exception if the
// value is 0; otherwise return the element vArr[vSize-1]
template <typename T>
T& miniVector<T>::back()
{
	if (vSize == 0)
		throw underflowError(
			"miniVector back(): vector empty");

	return vArr[vSize-1];
}

template <typename T>
const T& miniVector<T>::back() const
{
	if (vSize == 0)
		throw underflowError(
			"miniVector back(): vector empty");

	return vArr[vSize-1];
}

// provides general access to array elements
template <typename T>
T& miniVector<T>::operator[] (int i)
{
	if (i < 0 || i >= vSize)
		throw indexRangeError(
			"miniVector: index range error", i, vSize);

	return vArr[i];
}

// provides general access to array elements. constant version
template <typename T>
const T& miniVector<T>::operator[] (int i) const
{
	if (i < 0 || i >= vSize)
		throw indexRangeError(
			"miniVector: index range error", i, vSize);

	return vArr[i];
}

// insure that list has sufficient capacity,
// add the new item to the list, and increment vSize
template <typename T>
void miniVector<T>::push_back(const T& item)
{
	T newValue = item;

	// if space is full, allocate more capacity
	if (vSize == vCapacity)
	{
		if (vCapacity == 0)
			// if capacity is 0, set capacity to 1.
			// set copy to false because there are
			// no existing elements
			reserve(1,false);
		else
			// double the capacity
			reserve(2 * vCapacity, true);
	}

	// add item to the list, update vSize
	vArr[vSize] = newValue;
	vSize++;
}

// if not empty, just decrement the size
template <typename T>
void miniVector<T>::pop_back()
{
	if (vSize == 0)
		throw underflowError(
			"miniVector pop_back(): vector is empty");

	vSize--;
}

template <typename T>
int miniVector<T>::size() const
{
	return vSize;
}

template <typename T>
bool miniVector<T>::empty() const
{
	return vSize == 0;
}

template <typename T>
int miniVector<T>:: capacity() const
{
	return vCapacity;
}

#endif   // MINI_VECTOR
