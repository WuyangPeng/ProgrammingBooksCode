#ifndef HASH_CLASS
#define HASH_CLASS

#include <iostream>
#include <vector>
#include <list>
#include <utility>

#include "d_except.h"

using namespace std;

template <typename T, typename HashFunc>
class hash
{
	public:

#include "d_hiter.h"
			// hash table iterator nested classes

      hash(int nbuckets, const HashFunc& hfunc = HashFunc());
			// constructor specifying the number of buckets in the hash table
			// and the hash function
      
      hash(T *first, T *last, int nbuckets, const HashFunc& hfunc = HashFunc());
			// constructor with arguments including a pointer range
			// [first, last) of values to insert, the number of
			// buckets in the hash table, and the hash function
      
      bool empty() const;
			// is the hash table empty?
      int size() const;
			// return number of elements in the hash table

		iterator find(const T& item);
		const_iterator find(const T& item) const;
			// return an iterator pointing at item if it is in the
			// table; otherwise, return end()

      pair<iterator,bool> insert(const T& item);
			// if item is not in the table, insert it and
			// return a pair whose iterator component points
			// at item and whose bool component is true. if item
			// is in the table, return a pair whose iterator
			// component points at the existing item and whose
			// bool component is false
			// Postcondition: the table size increases by 1 if item
			// is not in the table

		int erase(const T& item);
			// if item is in the table, erase it and return 1;
			// otherwise, return 0
			// Postcondition: the table size decreases by 1 if
			// item is in the table
		void erase(iterator pos);
			// erase the item pointed to by pos.
			// Precondition: the table is not empty and pos points
			// to an item in the table. if the table is empty, the
			// function throws the underflowError exception. if the
			// iterator is invalid, the function throws the
			// referenceError exception.
			// Postcondition: the tree size decreases by 1
		void erase(iterator first, iterator last);
			// erase all items in the range [first, last).
			// Precondition: the table is not empty. if the table
			// is empty, the function throws the underflowError
			// exception.
			// Postcondition: the size of the table decreases by
			// the number of elements in the range [first, last)

      iterator begin();
			// return an iterator positioned at the start of the
			// hash table
      const_iterator begin() const;
			// constant version
      iterator end();
			// return an iterator positioned past the last element of the
			// hash table
      const_iterator end() const;
			// constant version

	private:
		int numBuckets;
			// number of buckets in the table
		vector<list<T> > bucket;
			// the hash table is a vector of lists
		HashFunc hf;
			// hash function
		int hashtableSize;
			// number of elements in the hash table
};

// constructor. create an empty hash table
template <typename T, typename HashFunc>
hash<T, HashFunc>::hash(int nbuckets, const HashFunc& hfunc):
			numBuckets(nbuckets), bucket(nbuckets), hf(hfunc),
			hashtableSize(0)
{}

// constructor. initialize table from pointer range [first, last)
			template <typename T, typename HashFunc>
hash<T, HashFunc>::hash(T *first, T *last, int nbuckets, const HashFunc& hfunc):
			numBuckets(nbuckets), bucket(nbuckets), hf(hfunc),
			hashtableSize(0)
{
	T *p = first;

	while (p != last)
	{
		insert(*p);
		p++;
	}
}

template <typename T, typename HashFunc>
bool hash<T, HashFunc>::empty() const
{
	return hashtableSize == 0;
}

template <typename T, typename HashFunc>
int hash<T, HashFunc>::size() const
{
	return hashtableSize;
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::iterator hash<T, HashFunc>::find(const T& item)
{
   // hashIndex is the bucket number (index of the linked list)
   int hashIndex = int(hf(item) % numBuckets);
   // use alias for bucket[hashIndex] to avoid indexing
   list<T>& myBucket = bucket[hashIndex];
   // use to traverse the list bucket[hashIndex]
   list<T>::iterator bucketIter;
   // returned if we find item

	// traverse list and look for a match with item
	bucketIter = myBucket.begin();
   while(bucketIter != myBucket.end())
	{
      // if locate item, return an iterator positioned in
      // bucket hashIndex at location bucketIter
      if (*bucketIter == item)
         return iterator(this, hashIndex, bucketIter);

		bucketIter++;
	}

   // return iterator positioned at the end of the hash table
   return end();
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::const_iterator
hash<T, HashFunc>::find(const T& item) const
{
   // hashIndex is the bucket number (index of the linked list)
   int hashIndex = int(hf(item) % numBuckets);
   // use alias for bucket[hashIndex] to avoid indexing
   const list<T>& myBucket = bucket[hashIndex];
   // use to traverse the list bucket[hashIndex]
   list<T>::const_iterator bucketIter;
   // returned if we find item

	// traverse list and look for a match with item
	bucketIter = myBucket.begin();
   while(bucketIter != myBucket.end())
	{
      // if locate item, return an iterator positioned in
      // bucket hashIndex at location bucketIter
      if (*bucketIter == item)
         return const_iterator(this, hashIndex, bucketIter);

		bucketIter++;
	}

   // return iterator positioned at the end of the hash table
   return end();
}

template <typename T, typename HashFunc>
pair<hash<T, HashFunc>::iterator,bool>
hash<T, HashFunc>::insert(const T& item)
{
   // hashIndex is the bucket number
   int hashIndex = int(hf(item) % numBuckets);
	// for convenience, make myBucket an alias for bucket[hashIndex]
   list<T>& myBucket = bucket[hashIndex];
   // use iterator to traverse the list myBucket
   list<T>::iterator bucketIter;
	// specifies whether or not we do an insert
	bool success;

	// traverse list until we arrive at the end of
	// the bucket or find a match with item
	bucketIter = myBucket.begin();
	while (bucketIter != myBucket.end())
		if (*bucketIter == item)
			break;
		else
			bucketIter++;

	if (bucketIter == myBucket.end())
	{
		// at the end of the list, so item is not
		// in the hash table. call list class insert()
		// and assign its return value to bucketIter
		bucketIter = myBucket.insert(bucketIter, item);
		success = true;
		// increment the hash table size 
		hashtableSize++;
	}
	else
		// item is in the hash table. duplicates not allowed.
		// no insertion
		success = false;

   // return a pair with iterator pointing at the new or
	// pre-existing item and success reflecting whether
	// an insert took place
   return pair<iterator,bool>
				(iterator(this, hashIndex, bucketIter), success);
}

template <typename T, typename HashFunc>
void hash<T, HashFunc>::erase(iterator pos)
{
	if (hashtableSize == 0)
		throw underflowError("hash erase(pos): hash table empty");

	if (pos.currentBucket == -1)
		throw referenceError("hash erase(pos): invalid iterator");


	// go to the bucket (list object) and erase the list item
	// at pos.currentLoc 
   bucket[pos.currentBucket].erase(pos.currentLoc);
}

template <typename T, typename HashFunc>
void hash<T, HashFunc>::erase(typename hash<T, HashFunc>::iterator first,
									  typename hash<T, HashFunc>::iterator last)
{
	if (hashtableSize == 0)
		throw underflowError("hash erase(first,last): hash table empty");

	// call erase(pos) for each item in the range
	while (first != last)
		erase(first++);
}

template <typename T, typename HashFunc>
int hash<T, HashFunc>::erase(const T& item)
{
	iterator iter;
	int numberErased = 1;
	
	iter = find(item);
	if (iter != end())
		erase(iter);
	else
		numberErased = 0;

	return numberErased;
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::iterator hash<T, HashFunc>::begin()
{
	hash<T, HashFunc>::iterator tmp;

	tmp.hashTable = this;
   tmp.currentBucket = -1;
	// start at index -1 + 1 = 0 and search for a non-empty
	// list
	tmp.findNext();

   return tmp;
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::const_iterator hash<T, HashFunc>::begin() const
{
	hash<T, HashFunc>::const_iterator tmp;

	tmp.hashTable = this;
   tmp.currentBucket = -1;
	// start at index -1 + 1 = 0 and search for a non-empty
	// list
	tmp.findNext();

   return tmp;
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::iterator hash<T, HashFunc>::end()
{
	hash<T, HashFunc>::iterator tmp;

	tmp.hashTable = this;
	// currentBucket of -1 means we are at end of the table
   tmp.currentBucket = -1;

   return tmp;
}

template <typename T, typename HashFunc>
typename hash<T, HashFunc>::const_iterator hash<T, HashFunc>::end() const
{
	hash<T, HashFunc>::const_iterator tmp;

	tmp.hashTable = this;
	// currentBucket of -1 means we are at end of the table
   tmp.currentBucket = -1;

   return tmp;
}

#endif   // HASH_CLASS
