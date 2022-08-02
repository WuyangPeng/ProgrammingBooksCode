/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_filter_iterator_test.cpp
 *
 * Purpose:     Implementation file for the transform_filter_iterator_test project.
 *
 * Created:     27th December 2005
 * Updated:     2nd January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2006, Synesis Software Pty Ltd.
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
#include <stlsoft/integer_to_string.hpp>
#include <stlsoft/iterators/transform_filter_iterator.hpp>
#include <stlsoft/std/cstdlib.hpp>

/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
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
#include <math.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
	defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

typedef std::string		string_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void test_1();
static void test_2();
static void test_3();
static void test_4();
static void test_5();
static void test_6();

/* /////////////////////////////////////////////////////////////////////////////
 * Functions and Predicates
 */

struct is_odd
	: std::unary_function<int, bool>
{
public:
	bool operator ()(int i) const
	{
		return 0 != (i % 2);
	}
};

struct int_to_string
	: std::unary_function<int, string_t>
{
public:
	string_t operator ()(int i) const
	{
		char	sz[21];

		return stlsoft::integer_to_string(sz, i);
	}
};

struct is_string_odd
	: std::unary_function<string_t, bool>
{
public:
	bool operator ()(string_t const &s) const
	{
		return 0 != (stlsoft::atoi(s) % 2);
	}
};

/* ////////////////////////////////////////////////////////////////////////// */

static void test_1()
{
	cout << "test_1:" << endl;

	int	ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::copy(	stlsoft::transform_filter(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), int_to_string(), is_odd())
			,	stlsoft::transform_filter(&ints[0] + STLSOFT_NUM_ELEMENTS(ints), &ints[0] + STLSOFT_NUM_ELEMENTS(ints), int_to_string(), is_odd())
			,	std::ostream_iterator<string_t>(cout, "\n"));
}

static void test_2()
{
	cout << "test_2:" << endl;

	std::list<int>	ints;

	{ for(int i = 0; i < 10; ints.push_back(i++)) {} }

	std::copy(	stlsoft::transform_filter(ints.begin(), ints.end(), int_to_string(), std::not1(is_odd()))
			,	stlsoft::transform_filter(ints.end(), ints.end(), int_to_string(), std::not1(is_odd()))
			,	std::ostream_iterator<string_t>(cout, "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

static void test_3()
{
	cout << "test_3:" << endl;

	int	ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::copy(	stlsoft::filter_transformer(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_string_odd(), int_to_string())
			,	stlsoft::filter_transformer(&ints[0] + STLSOFT_NUM_ELEMENTS(ints), &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_string_odd(), int_to_string())
			,	std::ostream_iterator<string_t>(cout, "\n"));
}

static void test_4()
{
	cout << "test_4:" << endl;

	std::list<int>	ints;

	{ for(int i = 0; i < 10; ints.push_back(i++)) {} }

	std::copy(	stlsoft::filter_transformer(ints.begin(), ints.end(), std::not1(is_string_odd()), int_to_string())
			,	stlsoft::filter_transformer(ints.end(), ints.end(), std::not1(is_string_odd()), int_to_string())
			,	std::ostream_iterator<string_t>(cout, "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

struct is_even
	: std::unary_function<int, bool>
{
public:
	bool operator ()(int i) const
	{
		return 0 == (i % 2) /* && 0 != i */;
	}
};

struct sqroot
    : std::unary_function<int, double>
{
public:
    double operator ()(int i) const
    {
        return ::sqrt(static_cast<double>(i));
    }
};

/* ////////////////////////////////////////////////////////////////////////// */

template <typename I>
void test_5_fn(I from, I to)
{
	std::copy(	stlsoft::transform_filter(from, to, sqroot(), is_even())
			,	stlsoft::transform_filter(to, to, sqroot(), is_even())
			,	std::ostream_iterator<double>(cout, "\n"));
}

static void test_5()
{
	cout << "test_5:" << endl;

	int	ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#if 1
	test_5_fn(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints));
#else /* ? 0 */
	std::copy(	stlsoft::transform_filter(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), sqroot(), is_even())
			,	stlsoft::transform_filter(&ints[0] + STLSOFT_NUM_ELEMENTS(ints), &ints[0] + STLSOFT_NUM_ELEMENTS(ints), sqroot(), is_even())
			,	std::ostream_iterator<double>(cout, "\n"));
#endif /* 0 */
}

/* ////////////////////////////////////////////////////////////////////////// */

static void test_6()
{
	cout << "test_6:" << endl;

	std::list<int>	ints;

	{ for(int i = 0; i < 10; ints.push_back(i++)) {} }

	std::copy(	stlsoft::transformer(stlsoft::filter(ints.begin(), ints.end(), is_even()), sqroot())
			,	stlsoft::transformer(stlsoft::filter(ints.end(), ints.end(), is_even()), sqroot())
			,	std::ostream_iterator<double>(cout, "\n"));

	std::copy(	stlsoft::transform_filter(ints.begin(), ints.end(), sqroot(), is_even())
			,	stlsoft::transform_filter(ints.end(), ints.end(), sqroot(), is_even())
			,	std::ostream_iterator<double>(cout, "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();

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
		cout << "transform_filter_iterator_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
