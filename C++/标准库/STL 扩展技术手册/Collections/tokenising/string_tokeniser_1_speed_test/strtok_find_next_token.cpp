
// Updated: 23rd February 2006

#include <stlsoft/simple_string.hpp>
//#include <stlsoft/iterators/null_output_iterator.hpp>
#include <stlsoft/tokenising/tokeniser_functions.hpp>

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

extern "C" void time_find_next_token(size_t nRepeats, Results &results)
{
	platformstl::performance_counter counter;

	stlsoft::simple_string	str1;
	stlsoft::simple_string	str2;
	stlsoft::simple_string	str3;
	stlsoft::simple_string	str4;
	stlsoft::simple_string	str5;

	cout	<< " find_next_token():" << endl;

# include "find_next_token_tests.hpp"
}

/* ////////////////////////////////////////////////////////////////////////// */
