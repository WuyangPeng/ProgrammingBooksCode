#ifndef LINKEDLIST_FUNCTIONS
#define LINKEDLIST_FUNCTIONS

#include <iostream>
#include <string>

#include "d_node.h"		// use node class
#include "d_dnode.h"		// use dnode class

using namespace std;

// output a singly linked list with each element followed by separator
template <typename T>
void writeLinkedList(node<T> *front, const string& separator);

// output a doubly linked list with each element followed by separator
template <typename T>
void writeDLinkedList(dnode<T> *header, const string& separator);

// insert a new node with value item immediately before node curr
template <typename T>
dnode<T> *insert(dnode<T> *curr, const T& item);

// erase dnode pointed to by curr
template <typename T>
void erase(dnode<T> *curr);

// ***********************************************************
//      FUNCTION IMPLEMENTATIONS
// ***********************************************************

template <typename T>
void writeLinkedList(node<T> *front, const string& separator = "  ")
{
   // front points at first node.  curr moves through the list
   node<T> *curr;

   curr = front;           // set curr to front of the list
   while (curr != NULL)    // continue until and of list
   {
      // output node value and move to the next node
      cout << curr->nodeValue << separator;
      curr = curr->next;
   }
}

template <typename T>
void writeDLinkedList(dnode<T> *header, const string& separator = "  ")
{
   // header points at first dnode.  p moves through the list
   dnode<T> *p = header->next ;

   while (p != header)    // continue until end of list
   {
      // output dnode value and move to the next dnode
      cout << p->nodeValue << separator;
      p = p->next;
   }
}

template <typename T>
dnode<T> *insert(dnode<T> *curr, const T& item)
{
	// declare pointer variables for the new node and the previous node
	dnode<T> *newNode, *prevNode;

	// allocate new dnode with item as initial value
	newNode = new dnode<T>(item);

	// assign prevNode the pointer value of node before p
	prevNode = curr->prev;

	// update pointer fields in newNode
	newNode->prev = prevNode;
	newNode->next = curr;

	// update curr and prevNode to point at newNode
	prevNode->next = newNode;	
	curr->prev = newNode;
	
	return newNode;
}

template <typename T>
void erase(dnode<T> *curr)
{
	// return if the list is empty
	if (curr->next == curr)
		return;

	// declare pointers for the predecessor and successor nodes
	dnode<T> *prevNode = curr->prev, *succNode = curr->next;

	// update pointer fields for predecessor and successor
	prevNode->next = succNode;
	succNode->prev = prevNode;

	// deallocate the memory used by the node
	delete curr;
}

#endif   // LINKEDLIST_FUNCTIONS
