// Bartosz Milewski (c) 2000
#include "String.h"
#include <iostream>
#include <cctype>

int main ()
{
	StringRef strOriginal ("text");
	StringRef strCopy (strOriginal);
	strCopy.Upcase ();
	// The original will be upper-cased!
	std::cout << "The original: " << strOriginal.c_str () << std::endl;
}

StringVal & StringVal::operator= (StringVal const & str)
{
	if (this != &str)
	{
		char const * cstr = str.c_str ();
		if (cstr == 0)
		{
			delete _buf;
			_buf = 0;
		}
		else
		{
			unsigned len = std::strlen (cstr);
			if (_buf == 0 || std::strlen (_buf) < len)
			{
				delete _buf;
				Init (cstr);
			}
			else
				std::strcpy (_buf, cstr);
		}
	}
	return *this;
}

void StringVal::Upcase ()
{
	if (_buf)
	{
		int len = std::strlen (_buf);
		for (int i = 0; i < len; ++i)
			_buf [i] = std::toupper (_buf [i]);
	}
}
