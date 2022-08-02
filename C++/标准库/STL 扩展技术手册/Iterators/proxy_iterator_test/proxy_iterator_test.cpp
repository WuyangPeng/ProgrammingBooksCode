/* /////////////////////////////////////////////////////////////////////////////
 * File:        proxy_iterator_test.cpp
 *
 * Purpose:     Implementation file for the proxy_iterator_test project.
 *
 * Created:     22nd September 2005
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


#if 0
# include <stlsoft/proxy_iterator.hpp>
#else /* ? 0 */
# include <stlsoft/iadaptor_iterator.hpp>
#endif /* 0 */

# include <stlsoft/algorithms.hpp>

/* PlatformSTL Header Files */
#include <platformstl/platformstl.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl.h>
# include <unixstl/readdir_sequence.hpp>

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl.h>
# include <winstl/findfile_sequence.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C++ Header Files */
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

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
#include <ctype.h>
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Functions
 */

class ansi_char_2_ucs16_char
{
public:
	wchar_t operator ()(char const &ch) const
	{
		return toupper(ch);
	}
};

void test_builtin_array()
{
	char	string1[]	=	"string1";
	wchar_t	string2[]	=	L"       ";

	stlsoft::copy_n(&string1[0], STLSOFT_NUM_ELEMENTS(string1) - 1, &string2[0]);

	stlsoft_assert(0 == wcscmp(L"string1", string2));

#if 0
	stlsoft::copy_n(stlsoft::iadaptor_iterator<	char const*
											,	ansi_char_2_ucs16_char
											,	wchar_t
											,	std::input_iterator_tag
											>(&string1[0])
				,	STLSOFT_NUM_ELEMENTS(string1) - 1
				,	&string2[0]);
#else /* ? 0 */
	stlsoft::copy_n(stlsoft::iadapt_iterator(&string1[0], ansi_char_2_ucs16_char()/* , std::input_iterator_tag() */)
				,	STLSOFT_NUM_ELEMENTS(string1) - 1
				,	&string2[0]);
#endif /* 0 */

	stlsoft_assert(0 == wcscmp(L"STRING1", string2));
}

#if defined(PLATFORMSTL_OS_IS_WIN32)

class ffs_vt_2_std_string_traits
	: std::unary_function<winstl::findfile_sequence::value_type, std::string>
{
public:
	std::string operator ()(winstl::findfile_sequence::value_type const &vt) const
	{
		return std::string(vt.get_short_filename());
	}
};

void test_winstl_ffs()
{
	winstl::findfile_sequence	ffs("*.*");

#if 0
	typedef stlsoft::iadaptor_iterator<	winstl::findfile_sequence::const_iterator
									,	ffs_vt_2_std_string_traits
									,	std::string
									,	winstl::findfile_sequence::const_iterator::iterator_category
									>		pi_t;

	pi_t		b(ffs.begin());
	pi_t		e(ffs.end());

	for(; b != e; ++b)
	{
		cout << *b << endl;
	}
#else /* ? 0 */
	std::copy(	stlsoft::iadapt_iterator<std::string>(ffs.begin(), ffs_vt_2_std_string_traits()/* , std::input_iterator_tag() */)
			,	stlsoft::iadapt_iterator<std::string>(ffs.end(), ffs_vt_2_std_string_traits(), std::input_iterator_tag())
			,	std::ostream_iterator<std::string>(cout, "\n"));
#endif /* 0 */
}
#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	test_builtin_array();

#if defined(PLATFORMSTL_OS_IS_WIN32)
	test_winstl_ffs();
#endif /* operating system */


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
		puts("proxy_iterator_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
