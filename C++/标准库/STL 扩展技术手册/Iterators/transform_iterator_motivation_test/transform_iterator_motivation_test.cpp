/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_motivation_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_motivation_test project.
 *
 * Created:     17th December 2005
 * Updated:     29th December 2005
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


#error This test is obsolete, superceded by transform_iterator_performance_motivation_test.cpp


/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/iterators/transform_iterator.hpp>

#include <platformstl/performance_counter.hpp>


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>
#if 0
#include <iterator>
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
#include <stdlib.h>

#if defined(_MSC_VER) && \
	defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Compiler detection
 */

#if defined(STLSOFT_COMPILER_IS_MSVC) && \
	_MSC_VER < 1310
# define NO_RANGE_CTORS
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////////
 * Constants & definitions
 */

#if 0
const size_t	ITERATIONS	=	100;
const size_t	NUM_INTS	=	100000;
#else /* ? 0 */
const size_t	ITERATIONS	=	100000;
const size_t	NUM_INTS	=	100;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void				longhand_version_l();
static void				longhand_version_l_range();
static void				longhand_version_v();
static void				longhand_version_v_range();
static void				shorthand_version();
static void				handcoded_version();
static std::list<int>	make_integers();

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

template<   typename I
        >
inline int calc_abs_sum_v(I from, I to)
{
    std::vector<int>    absolutes;

    std::transform(from, to, std::back_inserter(absolutes), std::ptr_fun(::abs));

    return std::accumulate(absolutes.begin(), absolutes.end(), int(0));
}


template<   typename I
        >
inline int calc_abs_sum_v_range(I from, I to)
{
    std::vector<int>    absolutes(from, to);

    std::transform(absolutes.begin(), absolutes.end(), absolutes.begin(), std::ptr_fun(::abs));

    return std::accumulate(absolutes.begin(), absolutes.end(), int(0));
}

template<	typename I
		>
inline int calc_abs_sum_l_range(I from, I to)
{
	std::list<int>	absolutes(from, to);

    std::transform(absolutes.begin(), absolutes.end(), absolutes.begin(), std::ptr_fun(::abs));

	return std::accumulate(absolutes.begin(), absolutes.end(), int(0));
}

template<	typename I
		>
inline int calc_abs_sum_l_range(I from, I to)
{
	std::list<int>	absolutes(from, to);

    std::transform(absolutes.begin(), absolutes.end(), absolutes.begin(), std::ptr_fun(::abs));

	return std::accumulate(absolutes.begin(), absolutes.end(), int(0));
}


template< typename I
        >
inline int calc_abs_sum_t(I from, I to)
{
	return std::accumulate( stlsoft::transformer(from, std::ptr_fun(::abs))
						,	stlsoft::transformer(to, std::ptr_fun(::abs))
                        ,	int(0));
}

template< typename I
        >
int calc_abs_sum_h(I from, I to)
{
	int sum = 0;
	for(; from != to; ++from)
	{
		sum += ::abs(*from);
	}
	return sum;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Longhand version
 */

static void longhand_version_v()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_v(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (vector):    sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

static void longhand_version_v_range()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_v_range(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (vector-r):  sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

static void longhand_version_l()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_l(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (list):      sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

static void longhand_version_l_range()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_l_range(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (list-r):    sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Shorthand version
 */

static void shorthand_version()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_t(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "shorthand:            sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Hand-coded version
 */

static void handcoded_version()
{
	std::list<int>	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									sum;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			sum = calc_abs_sum_h(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "hand-coded:           sum=" << sum << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

/* ////////////////////////////////////////////////////////////////////////// */

static std::list<int> make_integers()
{
	std::list<int>	ints;

	srand(101);

	{ for(size_t i = 0; i < NUM_INTS; ++i)
	{
		ints.push_back(rand());
	}}

	return ints;
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	cout << "ITERATIONS=" << ITERATIONS	<< ", NUM_INTS=" << NUM_INTS << endl;

	longhand_version_l();
	longhand_version_l_range();
	longhand_version_v();
	longhand_version_v_range();
	shorthand_version();
	handcoded_version();

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
		cout << "transform_iterator_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
