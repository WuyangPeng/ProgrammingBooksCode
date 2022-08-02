#ifndef LIST_CLASS
#define LIST_CLASS

#include <iostream>
#include <string>

#include "d_dnode.h"		// dnode class
#include "d_except.h"	// exception classes

using namespace std;

template <typename T>
class miniList
{
   public:

// include the iterator nested classes
#include "d_liter.h"

		miniList();
			// constructor. create an empty list
		miniList(int n, const T& item = T());
			// constructor. build a list with n elements, all having
			// the value item
		miniList(T* first, T* last);
			// constructor. build a list whose data comes from the
			// pointer range [first, last)
		miniList(const miniList<T>& obj);
			// copy constructor

      ~miniList();
			// destructor

      miniList<T>& operator= (const miniList<T>& rhs);
			// overloaded assignment operator

      int size() const;
			// return the size of the list
      bool empty() const;
			// is the list empty

		void push_front(const T& item);
			// insert item at the front of the list
			// Postcondition: the list size increases by 1
		void push_back(const T& item);
			// insert item at the back of the list
			// Postcondition: the list size increases by 1
		iterator insert(iterator pos, const T& item);
			// insert item before pos.
			// Postcondition: the list size increases by 1

		void pop_front();
			// erase the front of the list.
			// Precondition: the list is not empty. if the list is
			// empty, the function throws the underflowError exception.
			// Postcondition: the list size decreases by 1
		void pop_back();
			// erase the back of the list.
			// Precondition: the list is not empty. if the list is
			// empty, the function throws the underflowError exception.
			// Postcondition: the list size decreases by 1
		void erase(iterator pos);
			// erase the list element at pos
			// Precondition: the list is not empty. if the list is
			// empty, the function throws the underflowError exception.
			// Postcondition: the list size decreases by 1

		T& front();
			// return a reference to the value at the front of the list.
			// Precondition: the list is not empty. if the list is
			// empty, the function throws the underflowError exception
		const T& front() const;
			// constant version of front()
		T& back();
			// return a reference to the value at the back of the list.
			// Precondition: the list is not empty. if the list is
			// empty, the function throws the underflowError exception
		const T& back() const;
			// constant version of back()

      iterator begin();
			// return an iterator pointing at the first node in the list
			// or end() if the list is empty
      const_iterator begin() const;
			// constant version of begin()

      iterator end();
			// return an iterator pointing just past the last node of
			// the list
      const_iterator end() const;
			// constant version of end()

   private:

      // header (sentinel) node
      dnode<T> *header;

      // number of elements in the list
      int listSize;

      dnode<T> *getDNode(const T& item);
			// allocate a dnode object with the value item and
			// return a pointer to it. throw the memoryAllocationError
			// exception of the memory allocation fails

		dnode<T> *dinsert(dnode<T> *curr, const T& item);
			// insert item before node curr of the linked list and
			// return the address of the new node

		void derase(dnode<T> *curr);
			// erase node curr from the linked list.
			// Precondition: the list is not empty. the functions that
			// call derase() check the precondition
};

template <typename T>
dnode<T> *miniList<T>::getDNode(const T& item)
{
	// pointer to the new node
	dnode<T> *newNode;

	// allocate the new node and verify that the
	// allocation succeeded
	newNode = new dnode<T>(item);
	if (newNode == NULL)
		throw memoryAllocationError("miniList(): memory allocation failure");

	// return the address of the new node
	return newNode;
}

template <typename T>
dnode<T> *miniList<T>::dinsert(dnode<T> *curr, const T& item)
{
	// allocate the new node
	dnode<T> *newNode = getDNode(item);

	// insert newNode before curr
	newNode->prev = curr->prev;
	newNode->next = curr;
	curr->prev->next = newNode;
	curr->prev = newNode;

	return newNode;
}

template <typename T>
void miniList<T>::derase(dnode<T> *curr)
{
	// unlink the node from the list
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;

	// delete the node
	delete curr;
}

// list size is 0
template <typename T>
miniList<T>::miniList(): listSize(0)
{
	// create an empty list
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("miniList(): memory allocation failure");
}

// list size is n
template <typename T>
miniList<T>::miniList(int n, const T& value): listSize(n)
{
	int i;

	// create an empty list
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError
			("miniList(): memory allocation failure");

	// insert n copies of value at the front of the list
	for (i=0;i < n;i++)
		dinsert(header->next, value);
}

// initialize listSize to 0
template <typename T>
miniList<T>::miniList(T* first, T* last): listSize(0)
{
	T *curr = first;

	// create an empty list
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("miniList(): memory allocation failure");

	// insert the values in the range [first, last) at the
	// back of the list. increment listSize in each iteration
	while (curr != last)
	{
		dinsert(header, *curr);
		curr++;
		listSize++;
	}
}

template <typename T>
miniList<T>::miniList(const miniList<T>& obj): listSize(obj.listSize)
{
	// curr moves through the nodes in obj, and end marks the finish
	// of a traversal through obj
	dnode<T> *curr = obj.header->next, *end = obj.header;

	// create an empty list
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError
			("miniList(): memory allocation failure");

	// insert the values in the linked list obj.header
	// at the back of the current list
	while (curr != end)
	{
		dinsert(header, curr->nodeValue);
		curr = curr->next;
	}
}

template <typename T>
miniList<T>::~miniList()
{
	// erase the front of the list until it is empty
	while (header->next != header)
		derase(header->next);

	// the list has no nodes
	listSize = 0;

	// delete the header node
	delete header;
}

template <typename T>
miniList<T>& miniList<T>::operator=(const miniList<T>& rhs)
{
	// curr moves through the nodes in rhs, and end marks the finish
	// of a traversal through rhs
	dnode<T> *curr = rhs.header->next, *end = rhs.header;

   // can't assign list to itself
   if (this == &rhs)
		return *this;

	// erase the current list
	while (header->next != header)
		derase(header->next);

	// insert the elements of rhs at the back of the list
	while (curr != end)
	{
		dinsert(header, curr->nodeValue);
		curr = curr->next;
	}

	// list size is the size of rhs
	listSize = rhs.listSize;

   return *this;
}

template <typename T>
int miniList<T>::size() const
{
	return listSize;
}

template <typename T>
bool miniList<T>::empty() const
{
	return listSize == 0;
}

template <typename T>
void miniList<T>::push_front(const T& item)
{
	// insert at the front
	dinsert(header->next, item);

	// increment the list size
	listSize++;
}

template <typename T>
void miniList<T>::push_back(const T& item)
{
	// insert at the back
	dinsert(header, item);

	// increment the list size
	listSize++;
}

template <typename T>
typename miniList<T>::iterator miniList<T>::insert(iterator pos, const T& item)
{
	// record the current node's address in curr. newNode will be
	// the address of the node we insert
	dnode<T> *curr = pos.nodePtr, *newNode;

	// insert item before curr and capture the new node's address
	newNode = dinsert(curr, item);

	// increment the list size
	listSize++;

	// constructor converts newNode to an iterator
	return iterator(newNode);
}


template <typename T>
void miniList<T>::pop_front()
{
	if (listSize == 0)
		throw underflowError("miniList pop_front(): list is empty");

	// erase the front
	derase(header->next);

	// decrement the list size
	listSize--;
}

template <typename T>
void miniList<T>::pop_back()
{
	if (listSize == 0)
		throw underflowError("miniList pop_back(): list is empty");

	// erase the back
	derase(header->prev);

	// decrement the list size
	listSize--;
}

template <typename T>
void miniList<T>::erase(iterator pos)
{
	if (listSize == 0)
		throw underflowError("miniList erase(): list is empty");

	// retrieve the address of the node to be erased
	dnode<T> *curr = pos.nodePtr;

	// erase the node from the list
	derase(curr);

	// decrement the list size
	listSize--;
}

template <typename T>
T& miniList<T>::front()
{
	if (listSize == 0)
		throw underflowError("miniList front(): list is empty");

	return header->next->nodeValue;
}

template <typename T>
const T& miniList<T>::front() const
{
	if (listSize == 0)
		throw underflowError("miniList front(): list is empty");

	return header->next->nodeValue;
}

template <typename T>
T& miniList<T>::back()
{
	if (listSize == 0)
		throw underflowError("miniList back(): list is empty");

	return header->prev->nodeValue;
}

template <typename T>
const T& miniList<T>::back() const
{
	if (listSize == 0)
		throw underflowError("miniList back(): list is empty");

	return header->prev->nodeValue;
}

// note that in each of begin() and end(), a
// private iterator/const_iterator constructor converts
// the pointer into an iterator

template <typename T>
typename miniList<T>::iterator miniList<T>::begin()
{
	// private iterator constructor builds an iterator object
	// from the dnode pointer
	return iterator(header->next);
}

template <typename T>
typename miniList<T>::const_iterator miniList<T>::begin() const
{
	// private constructor builds a const_iterator object
	// from the dnode pointer
	return const_iterator(header->next);
}

template <typename T>
typename miniList<T>::iterator miniList<T>::end()
{
	// private constructor builds an iterator object
	// from the dnode pointer
	return iterator(header);
}

template <typename T>
typename miniList<T>::const_iterator miniList<T>::end() const
{
	// private constructor builds a const_iterator object
	// from the dnode pointer
	return const_iterator(header);
}

#endif   // LIST_CLASS
