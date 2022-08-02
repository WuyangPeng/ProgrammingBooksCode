#if !defined (HTAB_H)
#define HTAB_H
// (c) Bartosz Milewski 2000
#include "List.h"
#include <cstring>

const int sizeHTable = 4;

// Hash table of strings

class HTable
{
	friend class HSeq;
public:
	// return a short list of candidates
	List const & Find (char const * str) const;
	// add another string->id mapping
	void Add (char const * str, int id);
private:
	// the hashing function
	int hash (char const * str) const;

	List _aList [sizeHTable]; // an array of (short) lists
};

class HSeq
{
public:
	HSeq (HTable const & htab)
		: _aList (htab._aList),
		  _idx (-1),
		  _link (0)
	{
		NextList ();
	}
	bool AtEnd () const { return _idx == sizeHTable && _link == 0; }
	void Advance ();
	int Get () { return _link->Id (); }
private:
	void NextList ();
	
	List const * _aList;
	int			 _idx;
	Link const * _link;
};

#endif
