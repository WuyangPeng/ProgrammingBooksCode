/* /////////////////////////////////////////////////////////////////////////////
 * File:        fs_enum_colls_skip_iterator_test.cpp
 *
 * Purpose:     Implementation file for the fs_enum_colls_skip_iterator_test project.
 *
 * Created:     17th September 2005
 * Updated:     20th November 2005
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
#include <stlsoft.h>
#include <stlsoft/skip_iterator.hpp>

#include <platformstl/platformstl.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl.h>

# define USE_GLOB_SEQUENCE

# ifdef USE_GLOB_SEQUENCE
#  include <unixstl/glob_sequence.hpp>
# else /* ? USE_GLOB_SEQUENCE */
#  include <unixstl/readdir_sequence.hpp>
# endif /* USE_GLOB_SEQUENCE */

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl.h>
# include <winstl/findfile_sequence.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C++ Header Files */
#include <exception>
#include <iostream>

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

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

template<	typename I1
		,	typename I2
		>
void print_elements_in_range(I1 from, I2 to)
{
	for(; from != to; ++from)
	{
#if defined(PLATFORMSTL_OS_IS_UNIX)
		cout << "  " << stlsoft::c_str_ptr(*from) << endl;
#elif defined(PLATFORMSTL_OS_IS_WIN32)
		cout << "  " << (*from).get_path() << endl;
#endif /* operating system */
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if 0
	static const char	HOME[]	=	".";
#else /* ? 0 */
	static const char	HOME[]	=	"/";
#endif /* 0 */



	{
#if defined(PLATFORMSTL_OS_IS_UNIX)
# ifdef USE_GLOB_SEQUENCE
		unixstl::glob_sequence		entries(HOME, "*.*", 0/* , unixstl::glob_sequence::fullPath */);
# else /* ? USE_GLOB_SEQUENCE */
		unixstl::readdir_sequence	entries(HOME, unixstl::readdir_sequence::fullPath | unixstl::readdir_sequence::absolutePath);
# endif /* USE_GLOB_SEQUENCE */
#elif defined(PLATFORMSTL_OS_IS_WIN32)
		winstl::findfile_sequence	entries(HOME, "*.*");
//		winstl::findfile_sequence	entries(".", ".", winstl::findfile_sequence::directories);
#endif /* operating system */

		cout << "Unfiltered:" << endl;
		print_elements_in_range(entries.begin(), entries.end());
		cout << endl;

		cout << "Unfiltered:" << endl;
		print_elements_in_range(stlsoft::skip(entries.begin(), 3, 4, 3, entries.end()), entries.end());
		cout << endl;
	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
		cout << "fs_enum_colls_skip_iterator_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		cerr << "Unhandled error: " << x.what() << endl;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
