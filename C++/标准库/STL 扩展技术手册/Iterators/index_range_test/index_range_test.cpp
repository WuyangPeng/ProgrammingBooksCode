/* /////////////////////////////////////////////////////////////////////////////
 * File:        index_range_test.cpp
 *
 * Purpose:     Implementation file for the index_range_test project.
 *
 * Created:     29th December 2005
 * Updated:     2nd January 2006
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


/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/iterators/index_iterator.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>

#include <winstl/winstl.h>


/* Standard C++ Header Files */
#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <set>
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
 * Version
 */

#ifndef STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MAJOR
# define STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MAJOR	STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEX_ITERATOR_MAJOR
#endif
#ifndef STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MINOR
# define STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MINOR	STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEX_ITERATOR_MINOR
#endif
#ifndef STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_REVISION
# define STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_REVISION	STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEX_ITERATOR_REVISION
#endif

#define VER_HIGH	(STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MAJOR << 16)
#define VER_MID		(STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_MINOR << 8)
#define VER_LOW		(STLSOFT_VER_STLSOFT_ITERATORS_HPP_INDEXED_ITERATOR_REVISION << 0)

#define VER			(VER_HIGH | VER_MID | VER_LOW)

#if (VER < 0x010002)
namespace stlsoft
{
	template<   ss_typename_param_k I
			>
	inline indexed_iterator<I> indexer(I i)
	{
		return indexed_iterator<I>(i);
	}

#define index_iterator	indexed_iterator

} // namespace stlsoft
#endif

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void test_1();
static void test_2();
static void test_3();
static void test_4();

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	test_1();
	test_2();
	test_3();
	test_4();

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
		cout << "index_range_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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

struct int_tester
{
public:
	int_tester(int )
	{}
private:
	int_tester(...);
};


template <typename T, typename I>
void test_fn(I from, I to)
{
	ptrdiff_t	dist	=	std::distance(from, to);

	cout << "Range has " << dist << " elements" << endl;

	cout << "Elements: " << endl;
	std::copy(from, to, stlsoft::ostream_iterator<T>(cout, "\t", "\n"));

	cout << "Reversing: " << endl;
	std::reverse(from, to);
	std::copy(from, to, stlsoft::ostream_iterator<T>(cout, "\t", "\n"));

	if(from != to)
	{
//		int_tester(*from.operator ->());
	}
}

template <typename T, typename I>
void test_fn_ra(I from, I to)
{
	test_fn<T>(from, to);

	cout << "Sorting: " << endl;
	std::sort(from, to);
	std::copy(from, to, stlsoft::ostream_iterator<T>(cout, "\t", "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename I>
void test_1_fn(I from, I to)
{
#if 0
	int		i	=	0;
	short	s	=	0;
	double	d	=	0;
	long	l	=	0;
	void	*p	=	0;

	int_tester	test1(i);
	int_tester	test2(p);
#endif /* 0 */

	test_fn_ra<int>(from, to);
}

static void test_1()
{
	int		ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << endl << "array of int:" << endl;

	test_1_fn(	stlsoft::indexer(&ints[0])
			,	stlsoft::indexer(&ints[0]) + STLSOFT_NUM_ELEMENTS(ints));
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename I>
void test_2_fn(I from, I to)
{
	test_fn<int>(from, to);
}

static void test_2()
{
	std::list<int>	ints;

	for(size_t i = 0; i < 10; ++i)
	{
		ints.push_back(i);
	}

	cout << endl << "std::list<int>, forward:" << endl;

	test_2_fn(	stlsoft::indexer(ints.begin())
			,	stlsoft::indexer(ints.end()));
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename I>
void test_3_fn(I from, I to)
{
	test_fn<int>(from, to);
}

static void test_3()
{
	std::list<int>	ints;

	for(size_t i = 0; i < 10; ++i)
	{
		ints.push_back(i);
	}

	cout << endl << "std::list<int>, reverse:" << endl;

	test_3_fn(	stlsoft::indexer(ints.rbegin())
			,	stlsoft::indexer(ints.rend()));
}

/* ////////////////////////////////////////////////////////////////////////// */

struct S
{
public:
	S(int i = 0)
		: i(i)
	{
	}

public:
	int	i;
};

inline bool operator <(S const &s1, S const &s2)
{
	return s1.i < s2.i;
}

template <typename I>
void test_4_fn(I from, I to)
{
	ptrdiff_t	dist	=	std::distance(from, to);

	cout << "Range has " << dist << " elements" << endl;

	cout << "Elements: " << endl;
//std::copy(from, to, stlsoft::ostream_iterator<int>(cout, "\t", "\n"));

#ifdef STLSOFT_INDEX_ITERATOR_MEM_SEL_OP_SUPPORT
	{ for(I from2 = from; from2 != to; ++from2)
	{
		int	i	=	from2->i;

		cout << "\t" << i << endl;
	}}
#endif /* STLSOFT_INDEX_ITERATOR_MEM_SEL_OP_SUPPORT */
}

template <typename I>
void test_4_fn_rev(I from, I to)
{
	test_4_fn(from, to);

#ifdef STLSOFT_INDEX_ITERATOR_MEM_SEL_OP_SUPPORT
	std::reverse(from, to);

	{ for(I from2 = from; from2 != to; ++from2)
	{
		int	i	=	from2->i;

		cout << "\t" << i << endl;
	}}
#endif /* STLSOFT_INDEX_ITERATOR_MEM_SEL_OP_SUPPORT */
}

static void test_4()
{
#if !defined(STLSOFT_COMPILER_IS_DMC)
	{
		std::set<S>	ss;

		for(size_t i = 0; i < 10; ++i)
		{
			ss.insert(i);
		}

		cout << endl << "std::set<S>, forward:" << endl;

		test_4_fn(	stlsoft::indexer(ss.begin())
				,	stlsoft::indexer(ss.end()));

		cout << endl << "std::set<S>, reverse:" << endl;

#if 0	// std::set is not mutable in some implementations, since it'd break the ordering

		std::reverse(stlsoft::indexer(ss.rbegin())
				,	stlsoft::indexer(ss.rend()));
#endif /* 0 */

		test_4_fn(	stlsoft::indexer(ss.rbegin())
				,	stlsoft::indexer(ss.rend()));
	}
#endif /* 0 */

	{
		std::vector<S>	ss;

		for(size_t i = 0; i < 10; ++i)
		{
			ss.push_back(i);
		}

		cout << endl << "std::vector<S>, forward:" << endl;

		test_4_fn_rev(	stlsoft::indexer(ss.begin())
					,	stlsoft::indexer(ss.end()));

		cout << endl << "std::vector<S>, reverse:" << endl;

		test_4_fn_rev(	stlsoft::indexer(ss.rbegin())
					,	stlsoft::indexer(ss.rend()));
	}

	{
		std::deque<S>	ss;

		for(size_t i = 0; i < 10; ++i)
		{
			ss.push_back(i);
		}

		cout << endl << "std::deque<S>, forward:" << endl;

		test_4_fn_rev(	stlsoft::indexer(ss.begin())
					,	stlsoft::indexer(ss.end()));

		cout << endl << "std::deque<S>, reverse:" << endl;

		test_4_fn_rev(	stlsoft::indexer(ss.rbegin())
					,	stlsoft::indexer(ss.rend()));
	}
}

/* ////////////////////////////////////////////////////////////////////////// */
