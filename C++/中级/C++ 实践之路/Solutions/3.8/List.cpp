#include "List.h"
#include <iostream>
#include <cassert>

int main ()
{
	List list;
	list.Add (1);
	list.Add (2);
	list.Add (3);
	UnlinkSeq seq (list);
	while (!seq.AtEnd ())
	{
		if (seq.Id () == 2)
			break;
		seq.Advance ();
	}
	seq.Unlink ();
	for (ListSeq seq (list); !seq.AtEnd (); seq.Advance ())
	{
		std::cout << seq.Id () << std::endl;
	}
	return 0;
}

void UnlinkSeq::Unlink ()
{
	assert (_cur != 0);
	if (_prev == 0)
	{
		assert (_cur == _list._pHead);
		_list._pHead = _cur->Next ();
	}
	else
	{
		_prev->SetNext (_cur->Next ());
	}
	delete _cur;
	_cur = 0;
}

void List::Add (int id)
{
	// add in front of the list
	Link * pLink = new Link (_pHead, id);
	_pHead = pLink;
}

List::~List ()
{
	// free the list
	while (_pHead != 0)
	{
		Link * pLinkTmp = _pHead;
		_pHead = _pHead->Next(); // unlink pLink
		delete pLinkTmp;
	}
}