
// Updated: 23rd February 2006

#define	string_tokeniser		string_tokeniser_1_8

#include <stlsoft/string_tokeniser.hpp>
#include <stlsoft/simple_string.hpp>
//#include <stlsoft/iterators/null_output_iterator.hpp>
#include <stlsoft/tokenising/charset_tokeniser.hpp>

#include <platformstl/performance_counter.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#else /* ? __WATCOMC__ */
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */

#include <stdio.h>

/* ////////////////////////////////////////////////////////////////////////// */

#include "comparators.hpp"

extern "C" void create_test_strings(stlsoft::simple_string	&str1
								,	stlsoft::simple_string	&str2
								,	stlsoft::simple_string	&str3
								,	stlsoft::simple_string	&str4
								,	stlsoft::simple_string	&str5);

extern "C" void time_current(size_t nRepeats, Results &results)
{
	platformstl::performance_counter counter;

	stlsoft::simple_string	str1;
	stlsoft::simple_string	str2;
	stlsoft::simple_string	str3;
	stlsoft::simple_string	str4;
	stlsoft::simple_string	str5;

	cout	<< " default (" 
#ifdef STLSOFT_STRING_TOKENISER_CF_REQUIRE_DELIMITER_INDIRECTION
			<< "pointer"
#else /* ? STLSOFT_STRING_TOKENISER_CF_REQUIRE_DELIMITER_INDIRECTION */
			<< "copy"
#endif /* STLSOFT_STRING_TOKENISER_CF_REQUIRE_DELIMITER_INDIRECTION */
			<< "):" << endl;

#include "tests.hpp"
}

/* ////////////////////////////////////////////////////////////////////////// */
