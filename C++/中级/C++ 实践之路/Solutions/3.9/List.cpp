#include "List.h"
#include <iostream>
#include <cassert>

int main ()
{
	List list;
	list.Put (1);
	list.Put (2);
	list.Put (3);
	std::cout << list.Get () << std::endl;
	std::cout << list.Get () << std::endl;
	std::cout << list.Get () << std::endl;
	list.Put (4);
	list.Put (5);
	std::cout << list.Get () << std::endl;
	std::cout << list.Get () << std::endl;
	return 0;
}

void DLink::Unlink ()
{
	assert (_pNext != 0);
	assert (_pPrev != 0);
	_pNext->SetPrev (_pPrev);
	_pPrev->SetNext (_pNext);
	_pPrev = this;
	_pNext = this;
}

void List::Put (int id)
{
	DLink * pLink = new DLink (id);
	if (_pHead == 0)
		_pHead = pLink;
	else
	{
		pLink->SetNext (_pHead);
		pLink->SetPrev (_pHead->Prev ());
		_pHead->Prev ()->SetNext (pLink);
		_pHead->SetPrev (pLink);
		_pHead = pLink;
	}
}

int List::Get ()
{
	assert (_pHead != 0);
	DLink * pLink = _pHead->Prev ();
	if (pLink == _pHead) // last one
		_pHead = 0;
	pLink->Unlink ();
	int result = pLink->Id ();
	delete pLink;
	return result;
}

List::~List ()
{
	if (_pHead != 0)
	{
		DLink * pLast = _pHead->Prev ();
		while (_pHead !=pLast)
		{
			DLink * pLinkTmp = _pHead;
			_pHead = _pHead->Next();
			delete pLinkTmp;
		}
	}
}