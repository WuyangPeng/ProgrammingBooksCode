/* /////////////////////////////////////////////////////////////////////////////
 * File:        ostream_iterator_and_VARIANT_test.cpp
 *
 * Purpose:     Implementation file for the ostream_iterator_and_VARIANT_test project.
 *
 * Created:     13th November 2006
 * Updated:     13th November 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */


/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#if 0
# include <stlsoft/iterators/ostream_iterator.hpp>
#else /* ? 0 */
# include "./ostream_iterator.hpp"
#endif /* 0 */
#include <stlsoft/smartptr/ref_ptr.hpp>

#include <comstl/comstl.h>
#include <comstl/error/errorinfo_desc.hpp>
#include <comstl/util/creation_functions.hpp>
#include <comstl/util/initialisers.hpp>
#include <comstl/util/variant.hpp>

#include <winstl/winstl.h>
#include <winstl/error/error_desc.hpp>
#include <winstl/shims/access/string.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <vector>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
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

/* /////////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"ostream_iterator_and_VARIANT_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void f0()
{
	std::vector<int>	ints(2);
#if 0
	comstl::variant		prefix(100); 
	comstl::variant		suffix(L"200");
#else /* ? 0 */
	HWND				prefix	=	::CreateWindow("STATIC", "\t", WS_CHILD, 0, 0, 0, 0, ::GetDesktopWindow(), NULL, NULL, NULL);
	HWND				suffix	=	::CreateWindow("STATIC", "\n", WS_CHILD, 0, 0, 0, 0, ::GetDesktopWindow(), NULL, NULL, NULL);
#endif /* 0 */

	stlsoft::ostream_iterator<int>  osi(std::cout, prefix, suffix); // Shims live and die here!

	std::copy(ints.begin(), ints.end(), osi); // Crash and burn!
}

static void f1()
{
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
    f0();

    f1();

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
        puts("ostream_iterator_and_VARIANT_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        comstl::com_initialiser coinit;

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

/* ////////////////////////////////////////////////////////////////////////// */
