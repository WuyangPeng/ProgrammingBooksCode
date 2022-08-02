#if !defined (UTIL_H)
#define UTIL_H
// (c) Bartosz Milewski 2000

#include <sstream>
#include <cstring>

template<class T>
inline std::string ToString (T & val)
{
	std::ostringstream out;
	out << val;
	return out.str ();
}

class CstrCmp
{
public:
	bool operator () (char const * s1, char const * s2) const
	{
		return std::strcmp (s1, s2) < 0;
	}
};

#endif
