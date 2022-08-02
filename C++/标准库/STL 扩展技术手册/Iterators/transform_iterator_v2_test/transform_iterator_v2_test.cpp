/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_v2_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_v2_test project.
 *
 * Created:     29th December 2005
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
#include <stlsoft.h>

#include <iterator>
#include <list>
namespace stdx
{

#if 0
	template<typename I>
	struct iterator_traits/* 
	{
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef typename I::difference_type		difference_type;
		typedef typename I::pointer				pointer;
		typedef typename I::reference			reference;
	} */;
#else /* ? 0 */
	template<typename I>
	struct iterator_traits
	{
		typedef typename I::iterator_category	iterator_category;
		typedef typename I::value_type			value_type;
		typedef ptrdiff_t						difference_type;
		typedef I								*pointer;
		typedef I								&reference;
	};
#endif /* 0 */

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



	template<typename T>
	struct iterator_traits<std::list<T>::iterator>
	{
		typedef std::list<T>::iterator::iterator_category	iterator_category;
		typedef std::list<T>::iterator::value_type			value_type;
		typedef ptrdiff_t									difference_type;
		typedef T											*pointer;
		typedef T											&reference;
	};


	template<typename T, template <typename> class A>
	struct iterator_traits<std::list<T, A<T> >::iterator>
	{
		typedef std::list<T, A<T> >::iterator::iterator_category	iterator_category;
		typedef std::list<T, A<T> >::iterator::value_type			value_type;
		typedef ptrdiff_t											difference_type;
		typedef T													*pointer;
		typedef T													&reference;
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
  typedef value_type                                    *pointer;
  typedef value_type                                    &reference;
  typedef value_type const                              *const_pointer;
  typedef value_type const                              &const_reference;
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
    m_current = m_transformer(*m_it);
    return m_current;
  }
  const_reference operator *() const
  {
    m_current = m_transformer(*m_it);
    return m_current;
  }
  pointer operator ->()
  {
    m_current = m_transformer(*m_it);
    return &reference;
  }
  const_pointer operator ->() const
  {
    m_current = m_transformer(*m_it);
    return &reference;
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
  value_type              m_current;
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


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
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

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	std::list<int>	ints(1);

	*ints.begin() = -1;

	std::copy(	stlsoft::transformer(ints.begin(), std::ptr_fun(::abs))
			,	stlsoft::transformer(ints.end(), std::ptr_fun(::abs))
			,	std::ostream_iterator<int>(cout, " "));

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
		cout << "transform_iterator_v2_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
