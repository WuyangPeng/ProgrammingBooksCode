/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_composite_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_composite_test project.
 *
 * Created:     29th December 2005
 * Updated:     13th January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2005
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/iterators/transform_iterator.hpp>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl/unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl/winstl.h>
# include <winstl/time_string_access.hpp>

#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
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
#include <stdlib.h>

#if defined(_MSC_VER) && \
	defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

struct entry_to_mod_time
    : public std::unary_function<recls::stl::search_sequence::value_type, recls::recls_time_t>
{
    recls::recls_time_t operator ()(recls::stl::search_sequence::value_type const &entry) const
    {
        OutputDebugStringA(entry.c_str());
        OutputDebugStringA("\n");

        return entry.get_modification_time();
    }
};

struct time_to_string
    : public std::unary_function<recls::recls_time_t, std::string>
{
    std::string operator ()(recls::recls_time_t const &tm) const
    {
        return stlsoft::c_str_ptr(tm);
    }
};

static int main_(int /* argc */, char ** /*argv*/)
{
#if 0
    recls::stl::search_sequence files(".", "*.h|*.hpp", recls::FILES | recls::RECURSIVE);
#else /* ? 0 */
    recls::stl::search_sequence files("/freelibs/pantheios/1.0.x", "*.h|*.hpp", recls::FILES | recls::RECURSIVE);
#endif /* 0 */

    std::copy(  stlsoft::transformer(stlsoft::transformer(files.begin(), entry_to_mod_time()), time_to_string())
            ,   stlsoft::transformer(stlsoft::transformer(files.end(), entry_to_mod_time()), time_to_string())
            ,   std::ostream_iterator<time_to_string::result_type>(cout, "\n"));

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int				iRet;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState	memState;
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
		cout << "transform_iterator_composite_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */


		iRet = main_(argc, argv);
	}
	catch(std::exception &x)
	{
		cerr << "Unhandled error: " << x.what() << endl;

		iRet = EXIT_FAILURE;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;

		iRet = EXIT_FAILURE;
	}

#if defined(_MSC_VER) && \
	defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

	return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
