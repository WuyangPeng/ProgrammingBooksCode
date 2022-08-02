/* /////////////////////////////////////////////////////////////////////////////
 * File:        filter_iterator_v1_test.cpp
 *
 * Purpose:     Implementation file for the filter_iterator_v1_test project.
 *
 * Created:     28th December 2005
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
#include <stlsoft/iterator.hpp>

/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#if 0
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
 * Classes
 */

namespace stdx
{

	template<typename I>
	struct iterator_traits
	{
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T								*pointer;
		typedef T								&reference;
	};

	template<typename T>
	struct iterator_traits<T const*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T const							*pointer;
		typedef T const							&reference;
	};

	template<	typename I
			,	typename V
			,	typename D
			,	typename P
			,	typename R
			>
	struct iterator
	{
		typedef I		iterator_category;
		typedef	V		value_type;
		typedef D		difference_type;
		typedef P		pointer;
		typedef R		reference;
	};

} // namespace stdx


template< typename I // The underlying iterator
        , typename P // The unary predicate which will select the items
        >
class filter_iterator
#if 0
	: std::iterator<typename stdx::iterator_traits<I>::iterator_category
				,	typename std::iterator_traits<I>::value_type
				,	typename std::iterator_traits<I>::difference_type
			    ,	typename std::iterator_traits<I>::pointer
				,	typename std::iterator_traits<I>::reference
				>
#else /* ? 0 */
	: stdx::iterator<typename stdx::iterator_traits<I>::iterator_category
				,	typename stdx::iterator_traits<I>::value_type
				,	typename stdx::iterator_traits<I>::difference_type
			    ,	typename stdx::iterator_traits<I>::pointer
				,	typename stdx::iterator_traits<I>::reference
				>
#endif /* 0 */
{
public: // Member Types
	typedef filter_iterator<I, P>						class_type;
	typedef value_type const							&const_reference;

public: // Construction
	filter_iterator(I it, P pr)
		: m_it(it)
		, m_pr(pr)
	{
		for(; !m_pr(*m_it); ++m_it) // Loop to get first "selected" position
		{}
	}
public: // Forward Iterator methods
	class_type &operator ++()
	{
		for(++m_it; !m_pr(*m_it); ++m_it) // Advance, then loop to get first "selected" position
		{}

		return *this;
	}
	class_type operator ++(int)
	{
		class_type	r(*this);

		operator ++();

		return r;
	}
	reference operator *()
	{
		return *m_it;
	}
	const_reference operator *() const
	{
		return *m_it;
	}

	bool equal(class_type const &rhs) const
	{
		return m_it == rhs.m_it;
	}

private: // Members
	I	m_it;
	P	m_pr;
};

template< typename I // The underlying iterator
        , typename P // The unary predicate which will select the items
        >
inline filter_iterator<I, P> filter(I it, P pr)
{
	return filter_iterator<I, P>(it, pr);
}

template< typename I // The underlying iterator
        , typename P // The unary predicate which will select the items
        >
inline bool operator !=(filter_iterator<I, P> const &lhs, filter_iterator<I, P> const &rhs)
{
	return !lhs.equal(rhs);
}

/* ////////////////////////////////////////////////////////////////////////// */

struct is_readonly
	: std::unary_function<recls::stl::search_sequence::value_type, bool>
{
public:
	bool operator ()(recls::stl::search_sequence::value_type const &entry) const
	{
		return entry.is_readonly();
	}
};

static void func1()
{
	recls::stl::search_sequence	files(".", "*", recls::FILES | recls::RECURSIVE);

	std::copy(filter(files.begin(), is_readonly())
			, filter(files.end(), is_readonly())
			, std::ostream_iterator<recls::stl::search_sequence::value_type>(std::cout, "\n"));
}

static void func2();
static void func3();

static int main_(int /* argc */, char ** /*argv*/)
{
	func2();
	func3();

    return EXIT_SUCCESS;
}

#include <rangelib/algorithms.hpp>
#include <rangelib/filtered_sequence.hpp>

static void func2()
{
	cout << "Filtered sequence (via RangeLib)" << endl;

	recls::stl::search_sequence	files(".", "*", recls::FILES | recls::RECURSIVE);

	rangelib::r_copy(	rangelib::filter_sequence(files, is_readonly())
					,	std::ostream_iterator<recls::stl::search_sequence::value_type>(std::cout, "\n"));
}

struct is_long_enough
	: public std::unary_function<std::string, bool>
{
public:
	bool operator ()(std::string const &s) const
	{
		return s.size() > 4;
	}
};

struct do_reverse
	: public std::unary_function<std::string, std::string>
{
public:
	std::string operator ()(std::string const &s) const
	{
		std::string	r(s);

		std::reverse(r.begin(), r.end());

		return r;
	}
};

static void func3()
{
	std::list<std::string>	strings;

	strings.push_back("abcd");
	strings.push_back("efghijkl");
	strings.push_back("");
	strings.push_back("mnopq");
	strings.push_back("rstu");
	strings.push_back("vwxy");
	strings.push_back("");
	strings.push_back("z");

	cout << "Before transformation:" << endl;
	std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(cout, ","));
	cout << endl;

	std::transform(	stlsoft::filter(strings.begin(), strings.end(), is_long_enough())
				,	stlsoft::filter(strings.end(), strings.end(), is_long_enough())
				,	stlsoft::filter(strings.begin(), strings.end(), is_long_enough())
				,	do_reverse());

	cout << "After transformation:" << endl;
	std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(cout, ","));
	cout << endl;
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
		cout << "filter_iterator_v1_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
