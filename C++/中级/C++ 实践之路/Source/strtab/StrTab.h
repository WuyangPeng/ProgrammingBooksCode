#if !defined (SYMTAB_H)
#define SYMTAB_H
// (c) Bartosz Milewski 2000
#include "List.h"
#include <cstring>

const int maxBufSize = 500;

class StringBuffer
{
public:
	StringBuffer () : _curOffset (0) {}
	bool WillFit (int len) const
	{
		return _curOffset + len + 1 < maxBufSize;
	}
	void Add (char const * str)
	{
		// std::strcpy (_buf + _curOffset, str);
		std::strcpy (&_buf [_curOffset], str);
		_curOffset += std::strlen (str) + 1;
	}
	int GetOffset () const
	{
		return _curOffset;
	}
	bool IsEqual (int offStr, char const * str) const
	{
		// char const * strStored = _buf + offStr;
		char const * strStored = &_buf [offStr];
		// std::strcmp returns 0 when strings are equal
		return std::strcmp (str, strStored) == 0;
	}
	char const * GetString (int offStr) const
	{
		//return _buf + offStr;
		return &_buf [offStr];
	}
private:
	char    _buf [maxBufSize];
	int     _curOffset;
};

const int sizeHTable = 127;

// Hash table of strings

class HTable
{
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


const int idNotFound = -1;

const int maxStrings = 100;

// String table maps strings to ints
// and ints to strings

class StringTable
{
public:
	StringTable ();
	int ForceAdd (char const * str);
	int Find (char const * str) const;
	char const * GetString (int id) const;
private:
	HTable         _htab;  // string -> ids
	int            _offStr [maxStrings]; // id -> offset
	int            _curId;
	StringBuffer   _strBuf; // offset -> string
};

#endif
