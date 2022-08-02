/* /////////////////////////////////////////////////////////////////////////////
 * File:        member_selector_iterator_test.cpp
 *
 * Purpose:     Implementation file for the member_selector_iterator_test project.
 *
 * Created:     29th May 2005
 * Updated:     31st December 2005
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
//#define STLSOFT_UNITTEST
#include <stlsoft/iterators/member_selector_iterator.hpp>


/* Standard C Header Files */

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

struct S
{
	int i;
};

struct CS
{
	const int i;

public:
	CS(int i)
		: i(i)
	{}
};

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
struct doubler
{
public:
	T operator ()(T const &t) const
	{
		return 2 * t;
	}
};

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
#if 1/* defined(STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT) */
	{
		S as[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout	<< "Accessing non-const members of non-const array"
					<< std::endl;

		std::copy(	stlsoft::member_selector(&as[0], &S::i)
				,	stlsoft::member_selector(&as[0], &S::i) + STLSOFT_NUM_ELEMENTS(as)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;

// Test incompatibility
//		int	ints[] = { 0, 1 };
//		std::distance(	stlsoft::member_selector(&ints[0], &S::i)
//					,	stlsoft::member_selector(&ints[0], &S::i) + STLSOFT_NUM_ELEMENTS(ints));
	}
#endif /* 0 */

#if 1
	{
		const S as[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout	<< "Accessing non-const members of const array"
					<< std::endl;

		std::copy(	stlsoft::member_selector(&as[0], &S::i)
				,	stlsoft::member_selector(&as[0] + STLSOFT_NUM_ELEMENTS(as), &S::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310)
	{
		S as[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout	<< "Modifying non-const members of non-const array"
					<< std::endl;

		std::transform(	stlsoft::member_selector(&as[0], &S::i)
					,	stlsoft::member_selector(&as[0], &S::i) + STLSOFT_NUM_ELEMENTS(as)
					,	stlsoft::member_selector(&as[0], &S::i)
					,	doubler<int>());

		std::copy(	stlsoft::member_selector(&as[0], &S::i)
				,	stlsoft::member_selector(&as[0], &S::i) + STLSOFT_NUM_ELEMENTS(as)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310)
	{
		S				as_[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#if 0
		std::list<S>	l(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_));
#else /* ? 0 */
		std::list<S>	l; std::copy(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_), std::back_inserter(l));
#endif /* 0 */

		std::cout	<< "Accessing non-const members of non-const list"
					<< std::endl;

		std::transform(	stlsoft::member_selector(l.begin(), &S::i)
					,	stlsoft::member_selector(l.end(), &S::i)
					,	stlsoft::member_selector(l.begin(), &S::i)
					,	doubler<int>());

		std::copy(	stlsoft::member_selector(l.begin(), &S::i)
				,	stlsoft::member_selector(l.end(), &S::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310) //&& !defined(STLSOFT_COMPILER_IS_BORLAND)
	{
		S					as_[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#if 0
		const std::list<S>	l(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_));
#else /* ? 0 */
		const std::list<S>	l; /* std::copy(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_), std::back_inserter(l)); */
#endif /* 0 */

		STLSOFT_SUPPRESS_UNUSED(as_);

		std::cout	<< "Accessing non-const members of const list"
					<< std::endl;

		std::copy(	stlsoft::member_selector(l.begin(), &S::i)
				,	stlsoft::member_selector(l.end(), &S::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310)
	{
		S				as_[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#if 0
		std::list<S>	l(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_));
#else /* ? 0 */
		std::list<S>	l; std::copy(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_), std::back_inserter(l));
#endif /* 0 */

		std::cout	<< "Modifying non-const members of non-const list"
					<< std::endl;

		std::transform(	stlsoft::member_selector(l.begin(), &S::i)
					,	stlsoft::member_selector(l.end(), &S::i)
					,	stlsoft::member_selector(l.begin(), &S::i)
					,	doubler<int>());
		std::cout << std::endl;

		std::copy(	stlsoft::member_selector(l.begin(), &S::i)
				,	stlsoft::member_selector(l.end(), &S::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1
	{
		CS acs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout	<< "Accessing const members of non-const array"
					<< std::endl;

		std::copy(	stlsoft::member_selector(&acs[0], &CS::i)
				,	stlsoft::member_selector(&acs[0], &CS::i) + STLSOFT_NUM_ELEMENTS(acs)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1
	{
		const CS acs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		std::cout	<< "Accessing const members of const array"
					<< std::endl;

		std::copy(	stlsoft::member_selector(&acs[0], &CS::i)
				,	stlsoft::member_selector(&acs[0], &CS::i) + STLSOFT_NUM_ELEMENTS(acs)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && !defined(STLSOFT_COMPILER_IS_DMC) && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310)
	{
		CS				as_[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#if 0
		std::list<CS>	l(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_));
#else /* ? 0 */
		std::list<CS>	l; std::copy(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_), std::back_inserter(l));
#endif /* 0 */

		std::cout	<< "Accessing const members of non-const list"
					<< std::endl;

		std::copy(	stlsoft::member_selector(l.begin(), &CS::i)
				,	stlsoft::member_selector(l.end(), &CS::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

#if 1 && !defined(STLSOFT_COMPILER_IS_DMC) && (!defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1310)
	{
		CS					as_[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#if 0
		const std::list<CS>	l(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_));
#else /* ? 0 */
		const std::list<CS>	l; /* std::copy(&as_[0], &as_[0] + STLSOFT_NUM_ELEMENTS(as_), std::back_inserter(l)); */
#endif /* 0 */

		std::cout	<< "Accessing const members of const list"
					<< std::endl;

		std::copy(	stlsoft::member_selector(l.begin(), &CS::i)
				,	stlsoft::member_selector(l.end(), &CS::i)
				,	std::ostream_iterator<int>(cout, " "));
		std::cout << std::endl;
	}
#endif /* 0 */

    return 0;
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
		cout << "member_selector_iterator_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
