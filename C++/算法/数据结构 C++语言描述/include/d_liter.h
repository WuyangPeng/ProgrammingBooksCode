#ifndef MINILIST_ITERATOR_CLASSES
#define MINILIST_ITERATOR_CLASSES

// these classes do not stand alone. the miniList
// class includes this file in its public section

// necessary so iterator classes can access private section
// of miniList
class iterator;
class const_iterator;

friend class iterator;
friend class const_iterator;

// miniList class iterator implementation
class iterator
{
   public:
      friend class miniList<T>;

      // needed by the const_iterator constructor
      // that converts a const iterator to a const_iterator
      friend class const_iterator;

      // constructor
      iterator() {}

      // equality for iterators
      bool operator==
         (const iterator& rhs) const
      {
         // iterators equal if they point to same node
         return nodePtr == rhs.nodePtr;
      }

      // inequality for iterators
      bool operator!=
         (const iterator& rhs) const
      {
         // iterators unequal if they point to different nodes
         return nodePtr != rhs.nodePtr;
      }

      // pointer dereference operator
      T& operator* ()
      {
         // if the node's successor is itself, the list is empty
         if (nodePtr->next == nodePtr)
 				throw
				  referenceError("miniList iterator: reference error");

         return nodePtr->nodeValue;
      }

      // prefix increment. move forward one node
      iterator& operator++ ()
      {
			// move to the successor of nodePtr
			nodePtr = nodePtr->next;

         return *this;  // return new iterator value
      }

      // postfix increment. move forward one node
      iterator operator++ (int)
      {
			// save the current value of the iterator
         iterator tmp = *this;

			// move to the successor of nodePtr
         nodePtr = nodePtr->next;

         return tmp; // return original iterator value
      }

      // prefix decrement. move back one node
      iterator& operator-- ()
      {
			// move to the predecessor of nodePtr
			nodePtr = nodePtr->prev;

         return *this;  // return new iterator value
      }

      // postfix decrement. move back one node
      iterator operator-- (int)
      {
			// save the current value of the iterator
         iterator tmp = *this;

			// move to the predecessor of nodePtr
         nodePtr = nodePtr->prev;

         return tmp; // return original iterator value
      }

   private:
      // pointer to the current list node
      dnode<T> *nodePtr;

		// private constructor. converts p to an iterator
		// by assigning p to nodePtr
		iterator(dnode<T> *p): nodePtr(p)
		{}

};

// type is const_iterator, the list referred to is
// constant and * returns a constant reference
class const_iterator
{
   public:
      friend class miniList<T>;

      const_iterator() {}

      // converts const iterator --> const_iterator
      const_iterator(const iterator& obj)
      {
         nodePtr = obj.nodePtr;
      }

      bool operator==
         (const const_iterator& rhs) const
      {
         return nodePtr == rhs.nodePtr;
      }

      bool operator!=
         (const const_iterator& rhs) const
      {
         return nodePtr != rhs.nodePtr;
      }

      const T& operator* () const
      {
         // if the node's successor is itself, the list
			// is empty
         if (nodePtr->next == nodePtr)
 				throw
				  referenceError("miniList iterator: reference error");

         return nodePtr->nodeValue;
      }

      // prefix increment. move forward one node
      const_iterator& operator++ ()
      {
			// move to the successor of nodePtr
			nodePtr = nodePtr->next;

         return *this;  // return new iterator value
      }

      // postfix increment. move forward one node
      const_iterator operator++ (int)
      {
			// save the current value of the iterator
         const_iterator tmp = *this;

			// move to the successor of nodePtr
         nodePtr = nodePtr->next;

         return tmp; // return original iterator value
      }

      // prefix decrement. move back one node
      const_iterator& operator-- ()
      {
			// move to the predecessor of nodePtr
			nodePtr = nodePtr->prev;

         return *this;  // return new iterator value
      }

      // postfix decrement. move forward one node
      const_iterator operator-- (int)
      {
			// save the current value of the iterator
         const_iterator tmp = *this;

			// move to the predecessor of nodePtr
         nodePtr = nodePtr->prev;

         return tmp; // return original iterator value
      }

   private:
      dnode<T> *nodePtr;

		// converts a dnode pointer to an const_iterator
		const_iterator(dnode<T> *p): nodePtr(p)
		{}

};

#endif	// MINILIST_ITERATOR_CLASSES
