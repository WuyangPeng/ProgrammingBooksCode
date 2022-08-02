// Bartosz Milewski (c) 2000
#include "String.h"
#include <iostream>
#include <cctype>

int main ()
{
	StringVal str1 ("foo");
	StringVal str2 (str1); // copy
	str2.Upcase ();
	std::cout << str1.c_str () << std::endl;
	std::cout << str2.c_str () << std::endl;
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
