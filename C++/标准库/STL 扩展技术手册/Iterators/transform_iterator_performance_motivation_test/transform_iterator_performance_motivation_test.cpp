/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_performance_motivation_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_performance_motivation_test project.
 *
 * Created:     27th December 2005
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

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/iterators/transform_iterator.hpp>

#include <platformstl/performance_counter.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <string>
#include <vector>

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
 * Forward declarations
 */

typedef std::list<int>	source_range_t;
//typedef std::vector<int>	source_range_t;


#if (	(	defined(STLSOFT_COMPILER_IS_INTEL) && \
			defined(WIN32)) || \
		defined(STLSOFT_COMPILER_IS_MSVC)) && \
	_MSC_VER < 1310
# define NO_RANGE_CTORS
#endif /* compiler */

static void				longhand_version_l();
static void				longhand_version_v();
#ifndef NO_RANGE_CTORS
static void				longhand_version_l_range();
static void				longhand_version_v_range();
#endif /* !NO_RANGE_CTORS */
static void				shorthand_version();
static void				handcoded_version();
static source_range_t	make_integers();

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

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

namespace x
{
	template<	typename T
			,	typename I
			>
	inline T avg_mean(I from, I to)
	{
		T	sum	=	0;
		T	n	=	0;

		for(; from != to; ++from, ++n)
		{
			sum += *from;
		}

		return (0 == n) ? sum : sum / n;
	}

} // namespace x

/* ////////////////////////////////////////////////////////////////////////// */

template<   typename T
		,	typename I
        >
inline T calc_abs_mean_v(I from, I to)
{
    std::vector<T>	absolutes;

    std::transform(from, to, std::back_inserter(absolutes), std::ptr_fun(::abs));

    return x::avg_mean<T>(absolutes.begin(), absolutes.end());
}

#ifndef NO_RANGE_CTORS
template<   typename T
		,	typename I
        >
inline T calc_abs_mean_v_range(I from, I to)
{
    std::vector<T>	absolutes(from, to);

    std::transform(absolutes.begin(), absolutes.end(), absolutes.begin(), std::ptr_fun(::abs));

    return x::avg_mean<T>(absolutes.begin(), absolutes.end());
}
#endif /* !NO_RANGE_CTORS */

template<	typename T
		,	typename I
		>
inline T calc_abs_mean_l(I from, I to)
{
	std::list<T>	absolutes;

	std::transform(from, to, std::back_inserter(absolutes), std::ptr_fun(::abs));

	return x::avg_mean<T>(absolutes.begin(), absolutes.end());
}

#ifndef NO_RANGE_CTORS
template<	typename T
		,	typename I
		>
inline T calc_abs_mean_l_range(I from, I to)
{
	std::list<T>	absolutes(from, to);

    std::transform(absolutes.begin(), absolutes.end(), absolutes.begin(), std::ptr_fun(::abs));

	return x::avg_mean<T>(absolutes.begin(), absolutes.end());
}
#endif /* !NO_RANGE_CTORS */

template< typename T
		,	typename I
        >
inline T calc_abs_mean_t(I from, I to)
{
#if 0
	return x::avg_mean<T>(	stlsoft::transformer(from, std::ptr_fun(::abs))
						,	stlsoft::transformer(to, std::ptr_fun(::abs)));
#else /* ? 0 */
    return x::avg_mean<T>(  stlsoft::transform_iterator<I, std::pointer_to_unary_function<int, int> >(from, std::ptr_fun(::abs))
                        ,   stlsoft::transform_iterator<I, std::pointer_to_unary_function<int, int> >(to, std::ptr_fun(::abs)));
#endif /* 0 */
}

template<	typename T
		,	typename I
        >
inline T calc_abs_mean_h(I from, I to)
{
    T	sum =   0;
    T	n	=   0;
    for(; from != to; ++from, ++n)
    {
        sum += ::abs(*from);
    }
    return (0 == n) ? sum : sum / n;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Longhand versions
 */

static void longhand_version_v()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_v<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (vector):    mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

#ifndef NO_RANGE_CTORS
static void longhand_version_v_range()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_v_range<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (vector-r):  mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}
#endif /* !NO_RANGE_CTORS */

static void longhand_version_l()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_l<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (list):      mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

#ifndef NO_RANGE_CTORS
static void longhand_version_l_range()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_l_range<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "longhand (list-r):    mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}
#endif /* !NO_RANGE_CTORS */

/* /////////////////////////////////////////////////////////////////////////////
 * Shorthand version
 */

static void shorthand_version()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_t<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "shorthand:            mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

/* /////////////////////////////////////////////////////////////////////////////
 * Hand-coded version
 */

static void handcoded_version()
{
	source_range_t	integers	=	make_integers();

	platformstl::performance_counter	counter;
	int									mean;

	{ for(size_t WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();

		{ for(size_t i = 0; i < ITERATIONS; ++i)
		{
			mean = calc_abs_mean_h<int>(integers.begin(), integers.end());
		}}

		counter.stop();
	}}

	cout << "hand-coded:           mean=" << mean << "; time=" << static_cast<long>(counter.get_milliseconds()) << "ms" << endl;
}

/* ////////////////////////////////////////////////////////////////////////// */

static source_range_t make_integers()
{
	source_range_t	ints;

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
#ifdef WIN32
	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#endif // WIN32

	cout << "ITERATIONS=" << ITERATIONS	<< ", NUM_INTS=" << NUM_INTS << endl;

//	double_check_version

	longhand_version_l();
#ifndef NO_RANGE_CTORS
	longhand_version_l_range();
#endif /* !NO_RANGE_CTORS */
	longhand_version_v();
#ifndef NO_RANGE_CTORS
	longhand_version_v_range();
#endif /* !NO_RANGE_CTORS */
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
		cout << "transform_iterator_performance_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
