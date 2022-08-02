#include <iostream>
#include <cstring>

class StringVal
{
	friend StringVal operator+ (StringVal const &v1, StringVal const &v2);
public:
	StringVal (char const * cstr)
		:_buf (0)
	{
		std::cout << "Constructor taking char * "
				  << cstr << std::endl;
		Init (cstr);
	}
	StringVal (StringVal const & str)
		:_buf (0)
	{
		std::cout << "Copy constructor "
				  << str.c_str () << std::endl;
		Init (str.c_str ());
	}
	~StringVal ()
	{
		std::cout << "Destructor of " << _buf << std::endl;
		delete _buf;
	}
	StringVal & operator= (StringVal const & str);
	char const * c_str () const { return _buf; }
private:
	StringVal () : _buf (0) {}
	void Init (char const * cstr)
	{
		_buf = new char [std::strlen (cstr) + 1];
		std::strcpy (_buf, cstr);
	}
private:
	char  * _buf;
};

StringVal & StringVal::operator= (StringVal const & str)
{
	std::cout << "Operator = " << str.c_str () << std::endl;
	if (this != &str)
	{
		if (std::strlen (_buf) < std::strlen (str.c_str ()))
		{
			delete _buf;
			Init (str.c_str ());
		}
		else
			std::strcpy (_buf, str.c_str ());
	}
	return *this;
}

inline StringVal operator+ (StringVal const &v1, StringVal const &v2)
{
	std::cout << "  operator + (" << v1.c_str () << ", " 
		<< v2.c_str () << ")\n";
		
	StringVal result; // empty
	int len = std::strlen (v1._buf) + std::strlen (v2._buf);
	char * buf = new char [len + 1];
	std::strcpy (buf, v1.c_str ());
	std::strcat (buf, v2.c_str ());
	result._buf = buf;
	std::cout << "  Returning by value\n";
	return result;
}

StringVal ByValue ();

StringVal ByValue ()
{
	StringVal str ("Bar");
	return str;
}

int main ()
{
	StringVal str ("Foo");
	str = ByValue ();
	StringVal concat = str + "tosz";
	return 0;
}