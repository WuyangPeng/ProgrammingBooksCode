#if !defined (SYNTAXERR_H)
#define SYNTAXERR_H
// Bartosz Milewski (c) 2000
#include <string>

class Syntax 
{
public:
	Syntax (std::string const & str)
		: _str (str)
	{}
	Syntax (char const * str = "")
		: _str (str)
	{}
	char const * GetString () const
	{
		if (_str.length () == 0)
			return "Syntax error.";
		return _str.c_str ();
	}
private:
	std::string _str;
};

#endif
