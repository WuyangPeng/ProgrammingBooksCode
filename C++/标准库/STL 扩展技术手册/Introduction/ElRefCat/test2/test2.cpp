
#include <stlsoft/stlsoft.h>


#include <iterator>
#include <string>
#include <vector>

//#include <stlsoft/iterators/adapted_iterator_traits.hpp>
#include <stlsoft/string/string_tokeniser.hpp>

/* ////////////////////////////////////////////////////////////////////// */

std::string	make_str()
{
	return "non-const";
}

std::string	const make_cstr()
{
	return "const";
}


#if 0
#if 0
std::string& get_str()
{
	return make_str();
}
#else /* ? 0 */
std::string const& get_str()
{
	return make_cstr();
}
#endif /* 0 */
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////// */

#if 1


template <typename I>
typename std::iterator_traits<I>::value_type& get_iter_val(I it)
{
	return *it;
}

#else /* ? 0 */

template <typename T>
void use_val(T &t)
{
	STLSOFT_SUPPRESS_UNUSED(t);
}

template <typename I>
void use_iter_val(I it)
{
  typename std::iterator_traits<I>::value_type&   v = *it;

  use_val(v);

  STLSOFT_SUPPRESS_UNUSED(v);
//  . . .  
}

#endif /* 0 */

std::string const &testSafety()
{
  return std::string("Is it safe? Zzzz");
}

/* ////////////////////////////////////////////////////////////////////// */

int main()
{
	{
//		std::string&			s1	=	make_str();
		std::string const&		s2	=	make_cstr();

//		STLSOFT_SUPPRESS_UNUSED(s1);
		STLSOFT_SUPPRESS_UNUSED(s2);
	}


	{
		typedef std::vector<std::string>	string_t;

		string_t	strings(1);

//		std::string&		r1	=	get_iter_val(strings.begin());
//		STLSOFT_SUPPRESS_UNUSED(r1);

//		use_iter_val(strings.begin());

//		std::string const&	r2	=	get_iter_const_ref(strings.begin());
//		STLSOFT_SUPPRESS_UNUSED(r2);
	}

	{
		typedef stlsoft::string_tokeniser<std::string, char>	tokeniser_t;
		
		tokeniser_t	tokens("abc;def", ';');

//		std::string&		r1	=	get_iter_val(tokens.begin());
//		STLSOFT_SUPPRESS_UNUSED(r1);

//		use_iter_val(tokens.begin());

//		std::string const&	r2	=	get_iter_const_ref(tokens.begin());
//		STLSOFT_SUPPRESS_UNUSED(r2);
	}

	{
		std::string const& rs = std::string("Is it safe? Zzzz");

		rs.size();
	}

	{
		std::string const &rs = testSafety();

		rs.size();

	}

	return 0;
}

/* ////////////////////////////////////////////////////////////////////// */
