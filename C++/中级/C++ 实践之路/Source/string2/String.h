#if !defined (STRING_H)
#define STRING_H
// Bartosz Milewski (c) 2000
#include <cassert>
#include <cstring>

void StringTest ();

template <class T>
class RefPtr
{
public:
	RefPtr (RefPtr<T> const & p)
	{
		_p = p._p;
		_p->IncRefCount ();
	}
	~RefPtr ()
	{
		Release ();
	}
	RefPtr<T> const & operator= (RefPtr<T> const & p)
	{
		if (this != &p)
		{
			Release ();
			_p = p._p;
			_p->IncRefCount ();
		}
		return *this;
	}
protected:
	RefPtr (T * p) : _p (p) {}
	void Release ()
	{
		if (_p->DecRefCount () == 0)
			delete _p;
	}

	T * _p;
};

class RefCounted
{
public:
	RefCounted () : _count (1) {}
	int GetRefCount () const { return _count; }
	void IncRefCount () const { _count++; }
	int DecRefCount () const { return --_count; }
private:
	mutable int _count;
};

class StringVal
{
public:
	StringVal (char const * cstr = 0)
		:_buf (0)
	{
		if (cstr != 0)
			Init (cstr);
	}
	StringVal (StringVal const & str)
		:_buf (0)
	{
		if (str.c_str () != 0)
			Init (str.c_str ());
	}
	~StringVal ()
	{
		delete _buf;
	}
	StringVal & operator= (StringVal const & str);
	char const * c_str () const { return _buf; }
	void Upcase ();
private:
	void Init (char const * cstr)
	{
		assert (cstr != 0);
		_buf = new char [std::strlen (cstr) + 1];
		std::strcpy (_buf, cstr);
	}
private:
	char  * _buf;
};

class StringRep: public RefCounted
{
public:
	StringRep (char const * cstr)
		:_string (cstr)
	{}
	char const * c_str () const { return _string.c_str (); }
	void Upcase ()
	{
		_string.Upcase ();
	}
private:
	StringVal _string;
};

class StringRef: public RefPtr<StringRep> 
{ 
public: 
	StringRef (char const * cstr) 
		: RefPtr<StringRep> (new StringRep (cstr)) 
	{}
	StringRef (StringRef const & str) 
		: RefPtr<StringRep> (str) 
	{} 
	char const * c_str () const { return _p->c_str (); } 
	void Upcase () 
	{ 
		_p->Upcase (); 
	} 
};

#endif
