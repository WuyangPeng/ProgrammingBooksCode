/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_example_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_example_test project.
 *
 * Created:     28th December 2005
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
#if 1
#include <stlsoft/iterators/transform_iterator.hpp>
#else /* ? 0 */
#include <iterator>
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

namespace stlsoft
{

template< typename I
        , typename F
        >
class transform_iterator
{
// Member Types
public:
  typedef I                                             iterator_type;
  typedef F                                             transform_function_type;
  typedef typename transform_function_type::result_type value_type;
//  typedef std::iterator_traits<I>                       traits_type;
  typedef stdx::iterator_traits<I>                       traits_type;
  typedef typename traits_type::iterator_category       iterator_category;
  typedef typename traits_type::difference_type         difference_type;
  typedef typename traits_type::pointer                 pointer;
  typedef typename traits_type::reference               reference;
  typedef transform_iterator<I, F>                      class_type;
// Construction
public:
  transform_iterator(iterator_type it, transform_function_type fn)
    : m_it(it)
    , m_transformer(fn)
  {}
  transform_iterator()
    : m_it()
    , m_transformer()
  {}
  iterator_type base() const
  {
    return m_it;
  }
// Accessors
public:
  reference operator *()
  {
    return m_transformer(*m_it);
  }
  /* const_ */reference operator *() const
  {
    return m_transformer(*m_it);
  }
// Forward Iterator methods
public:
  class_type &operator ++()
  {
    ++m_it;
    return *this;
  }
  class_type &operator ++(int); // standard boilerplate implementation
// Bidirectional Iterator methods
public:
  class_type &operator --()
  {
    --m_it;
    return *this;
  }
  class_type &operator --(int); // standard boilerplate implementation
// Random Access Iterator methods
public:
  class_type &operator +=(difference_type d)
  {
    m_it += d;
    return *this;
  }
  class_type &operator -=(difference_type d)
  {
    m_it -= d;
    return *this;
  }
  reference operator [](difference_type index)
  {
    return m_transformer(m_it[index]);
  }
  /* const_ */reference operator [](difference_type index) const
  {
    return m_transformer(m_it[index]);
  }
// Comparison
public:
  bool equal(class_type const &rhs) const // Used by ==, != free funcs
  {
    return m_it == rhs.m_it;
  }
  int compare(class_type const &rhs) const // Used by <, <=, >, >= free funcs
  {
    return m_it - rhs.m_it;
  }
  difference_type difference(class_type const &rhs) const // Used by op -() free func
  {
    return m_it - rhs.m_it;
  }
// Members
private:
  iterator_type           m_it;
  transform_function_type m_transformer;
};

template< typename I
        , typename F
        >
transform_iterator<I, F> transformer(I i, F f)
{
  return transform_iterator<I, F>(i, f);
}

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator ==(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.equal(rhs);
}

// operator !=

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator !=(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return !lhs.equal(rhs);
}

#if 0
template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator !=(transform_iterator<I, F> const &lhs, I rhs)
{
    return !lhs.equal(rhs);
}
#endif /* 0 */

#ifndef STLSOFT_ITER_TXFM_ITER_OLD_DW
// operator +

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline transform_iterator<I, F> operator +(transform_iterator<I, F> const &lhs, ss_typename_type_k transform_iterator<I, F>::difference_type rhs)
{
    return transform_iterator<I, F>(lhs) += rhs;
}

// operator -

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
#if 0
inline transform_iterator<I, F> operator -(transform_iterator<I, F> const &lhs, ss_typename_type_k transform_iterator<I, F>::difference_type rhs)
#else /* ? 0 */
inline transform_iterator<I, F> operator -(transform_iterator<I, F> const &lhs, ss_ptrdiff_t rhs)
#endif /* 0 */
{
    return transform_iterator<I, F>(lhs) -= rhs;
}

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_typename_type_k transform_iterator<I, F>::difference_type operator -(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.difference(rhs);
}

// operator <

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator <(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.compare(rhs) < 0;
}

// operator <=

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator <=(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.compare(rhs) <= 0;
}

// operator >

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator >(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.compare(rhs) > 0;
}

// operator >=

template<   ss_typename_param_k I
        ,   ss_typename_param_k F
        >
inline ss_bool_t operator >=(transform_iterator<I, F> const &lhs, transform_iterator<I, F> const &rhs)
{
    return lhs.compare(rhs) >= 0;
}

#endif /* !STLSOFT_ITER_TXFM_ITER_OLD_DW */

} // namespace stlsoft
#endif /* 0 */

/* WinSTL Header Files */
//#include <winstl/file_functions.hpp>

/* Open-RJ Header Files */
#include <openrj/stl/openrj.hpp>
#include <openrj/stl/field.hpp>
#include <openrj/stl/record.hpp>
#include <openrj/stl/database.hpp>

/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* Synesis Header Files */
#include <MWVerInf.h>
#include <MLTxtVer.h>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
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
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void reclstl_to_version();

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	reclstl_to_version();

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

	SynesisWin::WinVer_Init();
    SynesisStd::TextVer_Init();

	try
	{
#if defined(_DEBUG) || \
defined(__SYNSOFT_DBS_DEBUG)
		cout << "transform_iterator_example_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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

	SynesisWin::WinVer_Uninit();
    SynesisStd::TextVer_Uninit();

#if defined(_MSC_VER) && \
	defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

	return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */

struct to_name_and_ver
	: public std::unary_function<recls::stl::search_sequence::value_type, std::string>
{
public:
	typedef std::string		string_type;

public:
	std::string operator ()(recls::stl::search_sequence::value_type const &v) const
	{
		SynesisWin::LPWinVerInfoA	verInfo	=	SynesisWin::WinVer_GetVersionInformationA(v.get_path().c_str());

		if(NULL == verInfo)
		{
			SynesisStd::LPTextVerInfoA  textVerInfo =   SynesisStd::TextVer_GetVersionInformationA(v.get_path().c_str(), 0);

			if(NULL == textVerInfo)
			{
				return v.get_path() + " - no version information";
			}
			else
			{
				char	sz[101];

				::sprintf(&sz[0], "%d.%d.%02d.%04d", textVerInfo->fileVerMajor, textVerInfo->fileVerMinor, textVerInfo->fileVerRevision, textVerInfo->fileVerEdit);

				return v.get_path() + " - " + sz;
			}
		}
		else
		{
			char	sz[101];

			sprintf(&sz[0], "%d.%d.%02d.%04d", verInfo->fileVerMajor, verInfo->fileVerMinor, verInfo->fileVerRevision, verInfo->fileVerBuild);

			SynesisWin::WinVer_CloseVersionInformationA(verInfo);

			return v.get_path() + " - " + sz;
		}
	}
};

static void reclstl_to_version()
{
#if 0
	recls::stl::search_sequence	files(".", "*.h|*.hpp", recls::FILES | recls::RECURSIVE);
#else /* ? 0 */
	recls::stl::search_sequence	files("/freelibs/pantheios/1.0.x", "*.h|*.hpp", recls::FILES | recls::RECURSIVE);
#endif /* 0 */

	std::copy(	stlsoft::transformer(files.begin(), to_name_and_ver())
			,	stlsoft::transformer(files.end(), to_name_and_ver())
			,	std::ostream_iterator<to_name_and_ver::result_type>(cout, "\n"));

//	stlsoft::transformer(files.begin(), to_name_and_ver())->get_path();
}

/* ////////////////////////////////////////////////////////////////////////// */

