#ifndef SET_OPERATORS
#define SET_OPERATORS

#include <set>

using namespace std;

// SET FUNCTIONS

#ifndef _MSC_VER
// Microsoft VC++ implements the operator == in <set>. it
// can't be defined twice

// determine if sets lhs and rhs have the same size and
// are equal element by element
template <typename T>
bool operator== (const set<T>& lhs, const set<T>& rhs);
#endif	// _MSC_VER

// return a set containing all elements that are in lhs or rhs
template <typename T>
set<T> operator+ (const set<T>& lhs, const set<T>& rhs);

// return a set containing all elements that are in goth lhs and rhs
template <typename T>
set<T> operator* (const set<T>& lhs, const set<T>& rhs);

// return a set containing all elements that are in lhs but not in rhs
template <typename T>
set<T> operator- (const set<T>& lhs, const set<T>& rhs);


// SET FUNCTION IMPLEMENTATIONS

#ifndef _MSC_VER

template <typename T>
bool operator== (const set<T>& lhs, const set<T>& rhs)
{
	set<T>::const_iterator myself = lhs.begin(), other = rhs.begin();

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
#endif	// _MSC_VER

template <typename T>
set<T> operator+ (const set<T>& lhs, const set<T>& rhs)
{
	// constuct union
	set<T> setUnion;
	// iterators that traverse the sets
	set<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

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
set<T> operator* (const set<T>& lhs, const set<T>& rhs)
{
	// constuct intersection
	set<T> setIntersection;
	// iterators that traverse the sets
	set<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

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
set<T> operator- (const set<T>& lhs, const set<T>& rhs)
{
	// construct difference
	set<T> setDifference;
	// iterators that traverse the sets
	set<T>::const_iterator lhsIter = lhs.begin(), rhsIter = rhs.begin();

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

#endif	// SET_OPERATORS
