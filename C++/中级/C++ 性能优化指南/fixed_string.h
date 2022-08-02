# ifndef FIXED_STRING_H
#	define FIXED_STRING_H
#	include <array>

/*  basic_fixed_string was an experiment in creating an object that behaved as 
    a char[], but could be constructed from a literal string. It never was used
	in performance testing.

	basic_fixed_string is a std::array<T>, plus some constructors.
*/

template <unsigned N=10, typename T=char> class basic_fixed_string : public std::array<T,N> {
public:
	basic_fixed_string() {
		for (auto it = begin(); it != end(); ++it) {
			*it = 0;
		}
	}
    basic_fixed_string(T const* p) {
		for (auto it = begin(); it != end(); ++it) {
			*it = *p;
			if (*p) ++p;
		}
	}

	basic_fixed_string& operator=(basic_fixed_string const& rhs) {
		std::copy(rhs.begin(), rhs.end(), begin());
		return *this;
	}

	basic_fixed_string& operator=(T const* rhs) {
		for (auto it = begin(); it != end(); ++it) {
			*it = *rhs;
			if (*rhs) ++rhs;
		}
	}
};
# endif