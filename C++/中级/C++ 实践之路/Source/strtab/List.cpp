// (c) Bartosz Milewski 2000
#include "List.h"
#include <iostream>

List::~List ()
{
	// free the list
	while ( _pHead != 0 )
	{
		Link* pLink = _pHead;
		_pHead = _pHead->Next(); // unlink pLink
		delete pLink;
	}
}

void List::Add ( int id )
{
	// add in front of the list
	Link * pLink = new Link (_pHead, id);
	_pHead = pLink;
}
