#ifdef __BORLANDC__
// suppress the warning message that functions containing for are not
// expanded inline
#pragma warn -8027
#endif	// __BORLANDC__

class iterator;
friend class iterator;

class const_iterator;
friend class const_iterator;
	// give the iterator classes access to private
	// section of hash

class iterator
{
	public:

		friend class hash<T,HashFunc>;
		friend class const_iterator;

		iterator()
		{}

		bool operator== (const iterator& rhs) const
		{
			if (currentBucket == rhs.currentBucket)
				if (currentBucket == -1)
					// when bucket locations are = -1, don't
					// care about currentLoc
					return true;
				else
					// compare locations in the bucket
					return currentLoc == rhs.currentLoc;
			else
				return false;
		}

		bool operator!= (const iterator& rhs) const
		{
			if (currentBucket != rhs.currentBucket)
				return true;
			else
				if (currentBucket == -1)
					// when bucket locations are = -1, don't
					// care about currentLoc. consider iterators
					// as equal
					return false;
				else
					// compare locations in the bucket
					return currentLoc != rhs.currentLoc;
		}

		T& operator* ()
		{
			if (currentBucket == -1)
				throw referenceError("hash iterator operator *: "
						  "invalid reference");

			// return the data in the list element
			return *currentLoc;
		}

		iterator& operator++ ()
		{
			// move to the next data value or the end of
			// the list
			currentLoc++;

			// if at end of list, call findNext() to
			// identify the next non-empty bucket in the table
			// and set currentLoc to its first element
			if (currentLoc == hashTable->bucket[currentBucket].end())
				findNext();

			return *this;
		}

		iterator operator++ (int)
		{
			// record the current state of the iterator
			iterator tmp = *this;

			// move to the next data value or the end of
			// the list
			currentLoc++;

			// if at end of list, call findNext() to
			// identify the next non-empty bucket in the table
			// and set currentLoc to its first element
			if (currentLoc == hashTable->bucket[currentBucket].end())
				findNext();

			// return the original iterator state
			return tmp;
		}

	private:

		// points to the hash table container
		hash<T,HashFunc> *hashTable;

		// index of current bucket being traversed
		int currentBucket;
		// points to the current element in the current bucket
		typename list<T>::iterator currentLoc;

		iterator(hash<T,HashFunc> *ht, int b,typename list<T>::iterator loc):
			hashTable(ht), currentBucket(b), currentLoc(loc)
		{}

		// find next non-empty bucket and set currentLoc
		// to point at its first element
		void findNext()
		{
			int i;

			// search from the next bucket to end of
			// table for a non-empty bucket
			for(i=currentBucket+1; i < hashTable->numBuckets;i++)
				if (!hashTable->bucket[i].empty())
				{
					// found a non-empty bucket. set
					// currentBucket index to i and
					// currentLoc to point at the first
					// element of the list
					currentBucket = i;
					currentLoc = hashTable->bucket[i].begin();
					return;
				}

			// we are at end()
			currentBucket = -1;
		}
};

// the constant iterator class
class const_iterator
{
	public:
		friend class hash<T,HashFunc>;

		const_iterator()
		{}

		// converts a const iterator to a const_iterator
		const_iterator (const iterator& x):
			hashTable(x.hashTable),
			currentBucket(x.currentBucket),
			currentLoc(x.currentLoc)
		{}

		bool operator== (const const_iterator& rhs) const
		{
			if (currentBucket == rhs.currentBucket)
				if (currentBucket == -1)
					// when bucket locations are = -1, don't
					// care about currentLoc
					return true;
				else
					// compare locations in the bucket
					return currentLoc == rhs.currentLoc;
			else
				return false;
		}

		bool operator!= (const const_iterator& rhs) const
		{
			if (currentBucket != rhs.currentBucket)
				return true;
			else
				if (currentBucket == -1)
					// when bucket locations are = -1, don't
					// care about currentLoc. consider Const_iterators
					// as equal
					return false;
				else
					// compare locations in the bucket
					return currentLoc != rhs.currentLoc;
		}

		const T& operator* () const
		{
			if (currentBucket == -1)
			{
				// const_iterator does not refer to valid data
				cerr << "hash const_iterator operator *: "
						  "invalid reference" << endl;
				exit(1);
			}

			// return the data in the list element
			return *currentLoc;
		}

		const_iterator& operator++ ()
		{
			// move to the next data value or the end of
			// the list
			currentLoc++;

			// if at end of list, call findNext() to
			// identify the next non-empty bucket in the table
			// and set currentLoc to its first element
			if (currentLoc == hashTable->bucket[currentBucket].end())
				findNext();

			return *this;
		}

		const_iterator operator++ (int)
		{
			// record the current state of the const_iterator
			const_iterator tmp = *this;

			// move to the next data value or the end of
			// the list
			currentLoc++;

			// if at end of list, call findNext() to
			// identify the next non-empty bucket in the table
			// and set currentLoc to its first element
			if (currentLoc == hashTable->bucket[currentBucket].end())
				findNext();

			// return the original const_iterator state
			return tmp;
		}

	private:

		// points to the constant hash table container
		const hash<T,HashFunc> *hashTable;

		// index of current bucket being traversed
		int currentBucket;
		// points to the current element in the current bucket
		typename list<T>::const_iterator currentLoc;

		// used to construct an iterator return value
		const_iterator(const hash<T,HashFunc> *ht, int b,
							typename list<T>::const_iterator loc):
			hashTable(ht), currentBucket(b), currentLoc(loc)
		{}

		// find next non-empty bucket and set currentLoc
		// to point at its first element
		void findNext()
		{
			int i;

			// search from the next bucket to end of
			// table for a non-empty bucket
			for(i=currentBucket+1; i < hashTable->numBuckets;i++)
				if (!hashTable->bucket[i].empty())
				{
					// found a non-empty bucket. set
					// currentBucket index to i and
					// currentLoc to point at the first
					// element of the list
					currentBucket = i;
					currentLoc = hashTable->bucket[i].begin();
					return;
				}

			// we are at end()
			currentBucket = -1;
		}
};
