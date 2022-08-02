#if !defined (STRING_H)
#define STRING_H
// Bartosz Milewski (c) 2000
#include <cassert>
#include <cstring>

void StringTest ();

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
#endif
