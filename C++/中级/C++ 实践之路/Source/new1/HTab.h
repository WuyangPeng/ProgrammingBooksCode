#if !defined (HTAB_H)
#define HTAB_H
// (c) Bartosz Milewski 2000
#include "List.h"

// Hash table of strings

class HTable
{
public:
	// The short list sequencer.
	// The client creates this sequencer
	// to search for a given string.
	class Seq: public List::Seq
	{
	public:
		Seq (HTable const & htab, char const * str)
			: List::Seq (htab.Find (str)) {}
	};

	friend class Seq;
public:
	explicit HTable (int size): _size (size)
	{
		_aList = new List [size];
	}
	~HTable ()
	{
		delete []_aList;
		// release memory in free list
		// List::Link::Purge (); // optional
	}	
	// add another string->id mapping
	void Add (char const * str, int id);
private:
	// return a short list of candidates
	List const & Find (char const * str) const;
	// the hashing function
	int hash (char const * str) const;

	List	  * _aList; // an array of (short) lists
	int			_size;
};

#endif
