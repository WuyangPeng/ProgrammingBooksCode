/* /////////////////////////////////////////////////////////////////////////
 * File:        to_string_control_shim_test.cpp
 *
 * Purpose:     Implementation file for the to_string_control_shim_test project.
 *
 * Created:     3rd February 2007
 * Updated:     3rd February 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2007-2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */




/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#endif /* 0 */

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

/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////
 * Globals
 */


/* /////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

namespace my_shims
{
  inline std::string to_string(char const *s)
  {
    return std::string(s);
  }
  inline std::string const& to_string(std::string const &s)
  {
    return s;
  }
  inline std::string to_string(int i)
  {
    char buf[21];
    return std::string(&buf[0], size_t(::sprintf(&buf[0], "%d", i)));
  }
}  // namespace my_shims

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	int	const			i	=	101;
	char const*	const	cs	=	"abc";
	const std::string	str("def");

	{
		::puts(my_shims::to_string(i).c_str());
		::puts(my_shims::to_string(cs).c_str());
		::puts(my_shims::to_string(str).c_str());
	}

	{
		std::string const	&str1	=	my_shims::to_string(i);
		std::string const	&str2	=	my_shims::to_string(cs);
		std::string const	&str3	=	my_shims::to_string(str);

		::puts(str1.c_str());
		::puts(str2.c_str());
		::puts(str3.c_str());
	}

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int             res;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
#endif /* _MSC_VER && _MSC_VER */

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER && _MSC_VER */

#if 0
    { for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    try
    {
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
        puts("to_string_control_shim_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        res = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        res = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "Unhandled unknown error" << endl;

        res = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return res;
}

/* ////////////////////////////////////////////////////////////////////// */
