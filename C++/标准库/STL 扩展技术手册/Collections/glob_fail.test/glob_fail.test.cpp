/* /////////////////////////////////////////////////////////////////////////
 * File:        glob_fail_test.cpp
 *
 * Purpose:     Implementation file for the glob_fail_test project.
 *
 * Created:     21st January 2007
 * Updated:     21st January 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */




/* STLSoft Header Files */
#define STLSOFT_INCL_STLSOFT_MEMORY_HPP_ALLOCATOR_SELECTOR

#include <stlsoft/memory/malloc_allocator.hpp>
#include <stlsoft/memory/allocator_adaptor.hpp>
#include <stlsoft/memory/random_fail_policy.hpp>

namespace stlsoft
{
	template <ss_typename_param_k T>
	struct allocator_selector
	{
		typedef malloc_allocator<T>                 allocator_base_type;
		typedef allocator_adaptor<	allocator_base_type
								,	random_fail_policy<T, 1>
								>					allocator_type;
	};

} // namespace stlsoft

#include <stlsoft/iterators/ostream_iterator.hpp>
#include <stlsoft/memory/auto_buffer.hpp>

/* UNIXSTL Header Files */
#include <unixstl/error/exceptions.hpp>
#include <unixstl/filesystem/glob_sequence.hpp>

/* PlatformSTL Header Files */
#include <platformstl/platformstl.hpp>


/* UNIXEm Header Files */
#ifdef PLATFORMSTL_OS_IS_WIN32
# include <unixem/unixem.h>
# include <unixem/implicit_link.h>
#endif /* PLATFORMSTL_OS_IS_WIN32 */

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
    using unixstl::glob_sequence;

	::srand(::time(NULL));

	{
		glob_sequence	files("/dev/include/S*.h", glob_sequence::files);

		cout << "files:" << endl;
		std::copy(	files.begin(), files.end()
				,	stlsoft::ostream_iterator<char const*>(std::cout, "\t", "\n"));
	}

	{
		glob_sequence	files("/dev/incpriv/S*.h");

		cout << "files:" << endl;
		std::copy(	files.begin(), files.end()
				,	stlsoft::ostream_iterator<char const*>(std::cout, "\t", "\n"));
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
        puts("glob_fail_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
