#ifndef MINISET_CLASS
#define MINISET_CLASS

#include <utility>

#include "d_stree.h"	// stree class

using namespace std;

// implements a set which does not contain duplicate data values
template <typename T>
class miniSet
{
	public:

		typedef typename stree<T>::iterator iterator;
		typedef typename stree<T>::const_iterator const_iterator;
			// miniSet iterators are simply stree iterators

		miniSet();
			// default constructor

		miniSet(T *first, T *last);
			// build a set whose data are determined by pointer range
			// [first, last)

		bool empty() const;
			// is the set empty?

		int size() const;
			// return the number of elements in the set

		iterator find (const T& item);
			// search for item in the set and return an iterator
			// pointing at it, or end() if it is not found

		const_iterator find (const T& item) const;
			// constant version

		pair<iterator,bool> insert(const T& item);
			// if item is not in the set, insert it and return a pair
			// whose first element is an iterator pointing to the
			// new element and whose second element is true.
			// otherwise, return a pair whose first element is an
			// iterator pointing at the existing element and whose
			// second element is false
			// Postcondition: the set size increases by 1 if item is
			// not in the set

		int erase(const T& item);
			// if item is in the set, erase it and return 1;
			// otherwise, return 0
			// Postcondition: the set size decreases by 1 if item is
			// in the set

		void erase(iterator pos);
			// erase the item pointed to by pos.
			// Preconditions: the set is not empty and pos points
			// to an item in the set. if the set is empty, the
			// function throws the underflowError exception. if the
			// iterator is invalid, the function throws the referenceError
			// exception.
			// Postcondition: the set size decreases by 1

		void erase(iterator first, iterator last);
			// erase the elements in the range [first, last)
			// Precondition: the set is not empty. if the set is empty,
			// the function throws the underflowError exception.
			// Postcondition: the set size decreases by the number
			// elements in the range

		iterator begin();
			// return an iterator pointing at the first member
			// in the set

		const_iterator begin() const;
			// constant version of begin()

		iterator end();
			// return an iterator pointing just past the last
			// member in the set

		const_iterator end() const;
			// constant version of end()

	private:
		// set implemented using a binary search tree
		stree<T> t;
};

// CONSTRUCTORS

template <typename T>
miniSet<T>::miniSet()
{}

template <typename T>
miniSet<T>::miniSet(T *first, T *last): t(first, last)
{}

template <typename T>
bool miniSet<T>::empty() const
{
	return t.empty();
}

template <typename T>
int miniSet<T>::size() const
{
	return t.size();
}

template <typename T>
miniSet<T>::iterator miniSet<T>::find (const T& item)
{
	// return stree iterator which is a miniSet iterator
	return t.find(item);
}

template <typename T>
miniSet<T>::const_iterator miniSet<T>::find (const T& item) const
{
	// return stree iterator which is a miniSet iterator
	return t.find(item);
}

template <typename T>
pair<miniSet<T>::iterator,bool> miniSet<T>::insert(const T& item)
{
	// insert item into the binary search tree and return
	// the iterator-bool pair
	return t.insert(item);
}

template <typename T>
int miniSet<T>::erase(const T& item)
{
	// erase item from the tree
	return t.erase(item);
}

template <typename T>
void miniSet<T>::erase(iterator pos)
{
	if (t.size() == 0)
 		throw
			underflowError("miniSet erase(): set is empty");

	if (pos == end())
 		throw
			referenceError("miniSet erase(): invalid iterator");

	// erase the item in the tree pointed to by pos
	t.erase(pos);
}

template <typename T>
void miniSet<T>::erase(iterator first, iterator last)
{
	if (t.size() == 0)
 		throw
			underflowError("miniSet erase(): set is empty");

	// erase range [first, last) in the tree
	t.erase(first, last);
}

template <typename T>
miniSet<T>::iterator miniSet<T>::begin()
{
	// a miniSet iterator is an stree iterator
	return t.begin();
}

template <typename T>
miniSet<T>::const_iterator miniSet<T>::begin() const
{
	return t.begin();
}

template <typename T>
miniSet<T>::iterator miniSet<T>::end()
{
	return t.end();
}

template <typename T>
miniSet<T>::const_iterator miniSet<T>::end() const
{
	return t.end();
}

// determine if sets lhs and rhs have the same size and
// are equal element by element
template <typename T>
bool operator== (const miniSet<T>& lhs, const miniSet<T>& rhs);

// return a miniSet object containing all elements that
// are in lhs or rhs
template <typename T>
miniSet<T> operator+ (const miniSet<T>& lhs, const miniSet<T>& rhs);

// return a miniSet object containing all elements that
// are in goth lhs and rhs
template <typename T>
miniSet<T> operator* (const miniSet<T>& lhs, const miniSet<T>& rhs);

// return a miniSet object containing all elements that
// are in lhs but not in rhs
template <typename T>
miniSet<T> operator- (const miniSet<T>& lhs, const miniSet<T>& rhs);


// SET FUNCTION IMPLEMENTATIONS

template <typename T>
bool operator== (const miniSet<T>& lhs, const miniSet<T>& rhs)
{
	miniSet<T>::const_iterator myself = lhs.begin(), other = rhs.begin();

	// return false if the sets do not have the same size
	if (lhs.size() == rhs.size())
	{
		// compare until encounter end of the sets or
		// find two elements that are not equal
		while (myself != lhs.end() && *myself++ == *other++);

		// if we left the loop before reaching the end
		// of the sets, they are not equal
		if (myself != lhs.end())
			return false;
		else
			return true;
	}
	else
		return false;
}

template <typename T>
miniSet<T> operator+ (const miniSet<T>& lhs, const miniSet<T>& rhs)
{
	// constuct union
	miniSet<T> setUnion;
	// iterators that traverse the sets
	miniSet<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

	// move forward as long as we have not reached the end of
	// either set
	while (lhsIter != lhs.end() && rhsIter != rhs.end())
		if (*lhsIter < *rhsIter)
			// *lhsIter belongs to the union. insert and
			// move iterator forward
			setUnion.insert(*lhsIter++);
		else if (*rhsIter < *lhsIter)
			// *rhsIter belongs to the union. insert and
			// move iterator forward
			setUnion.insert(*rhsIter++);
		else
		{
			// the two values are equal. insert just one and
			// move both itertors forward
			setUnion.insert(*lhsIter++);
			rhsIter++;
		}
	
		// flush any remaining items
		if (lhsIter != lhs.end())
			while (lhsIter != lhs.end())
				setUnion.insert(*lhsIter++);
		else if (rhsIter != rhs.end())
			while (rhsIter != rhs.end())
				setUnion.insert(*rhsIter++);

	return setUnion;
}

template <typename T>
miniSet<T> operator* (const miniSet<T>& lhs, const miniSet<T>& rhs)
{
	// constuct intersection
	miniSet<T> setIntersection;
	// iterators that traverse the sets
	miniSet<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

	// move forward as long as we have not reached the end of
	// either set
	while (lhsIter != lhs.end() && rhsIter != rhs.end())
		if (*lhsIter < *rhsIter)
			// *lhsIter is in lhs and not in rhs. move iterator
			// forward
			lhsIter++;
		else if (*rhsIter < *lhsIter)
			// *rhsIter is in rhs and not in lhs. move iterator
			// forward
			rhsIter++;
		else
		{
			// the same value is in both sets. insert one value
			// and move the iterators forward
			setIntersection.insert(*lhsIter);
			lhsIter++;
			rhsIter++;
		}
	
		return setIntersection;
}

template <typename T>
miniSet<T> operator- (const miniSet<T>& lhs, const miniSet<T>& rhs)
{
	// construct difference
	miniSet<T> setDifference;
	// iterators that traverse the sets
	miniSet<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

	// move forward as long as we have not reached the end of
	// either set
	while (lhsIter != lhs.end() && rhsIter != rhs.end())
		if (*lhsIter < *rhsIter)
			// *lhsIter belongs to lhs but not to rhs. put it in
			// the difference
			setDifference.insert(*lhsIter++);
		else if (*rhsIter < *lhsIter)
			// *rhsIter is in the rhs but not in the lhs. pass
			// over it
			rhsIter++;
		else
		{
			// the same value is in both sets. move the
			// iterators forward
			lhsIter++;
			rhsIter++;
		}
	
		// flush any remaining items from lhs
		if (lhsIter != lhs.end())
			while (lhsIter != lhs.end())
				setDifference.insert(*lhsIter++);

	return setDifference;
}

#endif	// MINISET_CLASS
