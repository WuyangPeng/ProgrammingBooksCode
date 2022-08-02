
#include <iterator>
#include <string>
#include <vector>

#include <stlsoft/iterators/adapted_iterator_traits.hpp>
#include <stlsoft/string/string_tokeniser.hpp>

/* ////////////////////////////////////////////////////////////////////// */

#if 0
template <typename I>
typename std::iterator_traits<I>::value_type& get_iter_ref(I i)
{
  return *i;
}
#else /* ? 0 */
template <typename I>
typename std::iterator_traits<I>::reference get_iter_ref(I i)
//typename stlsoft::adapted_iterator_traits<I>::reference get_iter_ref(I i)
{
  return *i;
}
#endif /* 0 */

#if 0
template <typename I>
typename std::iterator_traits<I>::value_type const& get_iter_const_ref(I i)
{
  return *i;
}
#else /* ? 0 */

template <typename I>
typename stlsoft::adapted_iterator_traits<I>::const_reference get_iter_const_ref(I i)
{
  return *i;
}


#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////// */

int main()
{
	{
		typedef std::vector<std::string>	string_t;

		string_t	strings(1);

		std::string&		r1	=	get_iter_ref(strings.begin());
		STLSOFT_SUPPRESS_UNUSED(r1);

//		std::string const&	r2	=	get_iter_const_ref(strings.begin());
//		STLSOFT_SUPPRESS_UNUSED(r2);
	}

	{
		typedef stlsoft::string_tokeniser<std::string, char>	tokeniser_t;
		
		tokeniser_t	tokens("abc;def", ';');

		std::string&		r1	=	get_iter_ref(tokens.begin());
		STLSOFT_SUPPRESS_UNUSED(r1);

//		std::string const&	r2	=	get_iter_const_ref(tokens.begin());
//		STLSOFT_SUPPRESS_UNUSED(r2);
	}


	return 0;
}
