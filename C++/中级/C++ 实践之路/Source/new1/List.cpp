#include "List.h"
#include <iostream>
// Bartosz Milewski (c) 2000

List::Free List::Link::_freeList;

List::List ()
	: _pHead (0)
{}

List::~List ()
{
	while ( _pHead != 0 )
	{
		Link * pLink = _pHead;
		_pHead = _pHead->Next (); // unlink pLink
		delete pLink;
	}
}

void List::Add (int value)
{
	Link * pLink = new Link (_pHead, value);
	_pHead = pLink;
}

void * List::Free::NewLink ()
{
	if (_p != 0)
	{
		void * mem = _p;
		_p = _p->_pNext;
		std::cout << "Allocation from free list\n";
		return mem;
	}
	else
	{
		// use global operator new
		std::cout << "Allocation using new\n";
		return ::new char [sizeof (Link)];
	}
}

void List::Free::Recycle (void * mem)
{
	Link * link = static_cast<Link *> (mem);
	link->_pNext = _p;
	_p = link;
}

List::Free::~Free ()
{
	Purge ();
}

void List::Free::Purge ()
{
	while (_p != 0)
	{
		// it was allocated as an array of char
		char * mem = reinterpret_cast<char *> (_p);
		_p = _p->Next();
		::delete [] mem;
	}
}