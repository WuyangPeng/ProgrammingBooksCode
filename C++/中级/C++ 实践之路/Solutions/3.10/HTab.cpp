// (c) Bartosz Milewski 2000
#include "HTab.h"
#include <cassert>
#include <iostream>

// Find the list in the hash table that may contain
// the id of the string we are looking for

List const & HTable::Find (char const * str) const
{
	int i = hash (str);
	return _aList [i];
}

void HTable::Add (char const * str, int id)
{
	int i = hash (str);
	_aList [i].Add (id);
}

int HTable::hash (char const * str) const
{
	// no empty strings, please
	assert (str != 0 && str [0] != 0);
	unsigned h = str [0];
	for (int i = 1; str [i] != 0; ++i)
		h = (h << 4) + str [i];
	return h % sizeHTable; // remainder
}

void HSeq::Advance ()
{
	_link = _link->Next ();
	if (_link == 0)
		NextList ();
}

void HSeq::NextList ()
{
	assert (_link == 0);
	do
	{
		++_idx;
	} while (_aList [_idx].IsEmpty ());
	
	if (_idx < sizeHTable)
		_link = _aList [_idx].GetHead ();
	else
		_link = 0;
}

int main ()
{
	HTable htab;
	htab.Add ("alpha", 0);
	htab.Add ("beta", 1);
	htab.Add ("gamma", 2);
	htab.Add ("delta", 3);
	htab.Add ("epsilon", 4);
	for (HSeq seq (htab); !seq.AtEnd (); seq.Advance ())
		std::cout << seq.Get () << std::endl;
}