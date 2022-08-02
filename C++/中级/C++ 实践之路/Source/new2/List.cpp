#include "List.h"
// Bartosz Milewski (c) 2000
#include <cassert>
#include <iostream>

LinkAllocator List::Link::_linkAlloc;

void * List::Link::operator new (std::size_t size)
{
	assert (size == sizeof (Link));
	return _linkAlloc.NewLink ();
}

void List::Link::operator delete (void * mem)
{
	if (mem)
		_linkAlloc.Recycle (mem);
}

void List::Link::Purge () { _linkAlloc.Purge (); }

// List

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

// LinkAllocator

void * LinkAllocator::NewLink ()
{
	if (_p == 0)
	{
		std::cout << "\tAllocating a new block\n";
		// use global operator new to allocate a block of links
		char * p = ::new char [sizeof (Block) + BlockLinks * sizeof (List::Link)];
		// add it to the list of blocks
		Block * block = reinterpret_cast<Block *> (p);
		block->SetNext (_blocks);
		_blocks = block;
		// add it to the list of links
		p += sizeof (Block);
		for (int i = 0; i < BlockLinks; ++i)
		{
			List::Link * link = reinterpret_cast<List::Link *> (p);
			link->SetNext (_p);
			_p = link;
			p += sizeof (List::Link);
		}
	}
	void * mem = _p;
	_p = _p->Next ();
	std::cout << "\tGetting link from free list\n";
	return mem;
}

void LinkAllocator::Recycle (void * mem)
{
	std::cout << "\tReturning link to free list\n";
	List::Link * link = static_cast<List::Link *> (mem);
	link->SetNext (_p);
	_p = link;
}

void LinkAllocator::Purge ()
{
	std::cout << "\tPurging link allocator\n";
	while (_blocks != 0)
	{
		// it was allocated as an array of char
		char * mem = reinterpret_cast<char *> (_blocks);
		_blocks = _blocks->Next();
		::delete [] mem;
	}
}