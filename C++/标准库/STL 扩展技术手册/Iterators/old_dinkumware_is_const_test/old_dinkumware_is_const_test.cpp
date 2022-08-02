/* /////////////////////////////////////////////////////////////////////////////
 * File:        old_dinkumware_is_const_test.cpp
 *
 * Purpose:     Implementation file for the old_dinkumware_is_const_test project.
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
#include <stlsoft/pod_vector.hpp>
#include <stlsoft/iterators/adapted_iterator_traits.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>
#include <stlsoft/meta.hpp>
#include <stlsoft/meta/base_type_traits.hpp>
#include <stlsoft/meta/member_traits.hpp>
#include <stlsoft/string_tokeniser.hpp>
#include <stlsoft/typefixer/pointer.hpp>

#include <winstl/findfile_sequence.hpp>
#include <winstl/reg_key_sequence.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <string>
#include <typeinfo>
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

namespace stdx
{
	template <typename I, int B_IS_DW_OLD_FORM>
	struct Dinkumware_test
	{
		enum { IS_CONST	=	1	};
	};

	template <typename I>
	struct Dinkumware_test<I, 1>
	{
		typedef ss_typename_type_k I::value_type	value_type;

		typedef ss_typename_type_k std::list<value_type>::iterator			list_iterator_type;
		typedef ss_typename_type_k std::list<value_type>::const_iterator	list_const_iterator_type;
		typedef ss_typename_type_k std::set<value_type>::iterator			set_iterator_type;
		typedef ss_typename_type_k std::set<value_type>::const_iterator		set_const_iterator_type;

		// Everything in here is a Dinkumware iterator
		enum
		{
			IS_CONST	=	(	stlsoft::is_same_type<ss_typename_type_k std::list<value_type>::iterator, I>::value ||
								stlsoft::is_same_type<ss_typename_type_k std::set<value_type>::iterator, I>::value)
								?	0
								:	(	stlsoft::is_same_type<ss_typename_type_k std::list<value_type>::const_iterator, I>::value ||
										stlsoft::is_same_type<ss_typename_type_k std::set<value_type>::const_iterator, I>::value)
										?	1
										:	0
		};
	};

	template <typename I>
	struct iterator_mutability_traits
	{
		typedef ss_typename_type_k I::value_type	value_type;

		enum { HAS_MEMBER_DIFFERENCE_TYPE   =   0 != stlsoft::member_traits<I>::has_member_difference_type					};
		enum { IS_DINKUMWARE_OLD_FORM		=	0 != stlsoft::member_traits<I>::has_member_distance_type && 
												0 == HAS_MEMBER_DIFFERENCE_TYPE												};
	    enum { HAS_MEMBER_POINTER           =   0 != stlsoft::member_traits<I>::has_member_pointer							};

		enum { REF_CAT_IS_VOID				=   0 != stlsoft::is_same_type<value_type, void>::value										};
		enum { REF_CAT_IS_BVT				=   0 == REF_CAT_IS_VOID && 
												0 != HAS_MEMBER_POINTER &&
												0 != stlsoft::is_same_type<ss_typename_type_k stlsoft::typefixer::fixer_pointer<I, HAS_MEMBER_POINTER>::pointer, void>::value 
												/* && (0 == IS_DINKUMWARE_OLD_FORM) */										};
		enum { IsConst	=	HAS_MEMBER_POINTER
								? stlsoft::base_type_traits<ss_typename_type_k stlsoft::typefixer::fixer_pointer<I, HAS_MEMBER_POINTER>::pointer>::is_const
								: Dinkumware_test<I, IS_DINKUMWARE_OLD_FORM>::IS_CONST
																															};

	};

//	template <typename T>
//	struct iterator_mutability_traits< typename std::list<T>::iterator>
//	{
//		enum { IsConst	=	0	};
//	};

	template <typename T>
	struct iterator_mutability_traits<T*>
	{
		enum { IsConst	=	0	};
	};

	template <typename T>
	struct iterator_mutability_traits<T const*>
	{
		enum { IsConst	=	1	};
	};


} // namespace stdx

//std::string

template<typename T>
void do_test_(T t, char const *typeName)
{
	printf("%-40s is %s\n", typeName, stdx::iterator_mutability_traits<T>::IsConst ? "const" : "non-const");
}

#define test_(x)	do_test_(x, typeid(x).name())

template<typename T>
void do_test2_(T t, char const *typeName)
{
	printf(	"%-40s:\n\thas difference_type = %d\n\tis Dinkumware Old   = %d\n\thas pointer         = %d\n\tis const            = %d\n\tis Void ER          = %d\n\tis BVT ER           = %d\n\tvalue type          = %s\n\n"
		,	typeName
		,	stdx::iterator_mutability_traits<T>::HAS_MEMBER_DIFFERENCE_TYPE
		,	stdx::iterator_mutability_traits<T>::IS_DINKUMWARE_OLD_FORM
		,	stdx::iterator_mutability_traits<T>::HAS_MEMBER_POINTER
		,	stdx::iterator_mutability_traits<T>::IsConst
		,	stdx::iterator_mutability_traits<T>::REF_CAT_IS_VOID
		,	stdx::iterator_mutability_traits<T>::REF_CAT_IS_BVT
		,	typeid(ss_typename_type_k T::value_type).name());
}

#define test2_(x)	do_test2_(x, typeid(x).name())

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	std::list<int>									l1;
	std::list<int> const							&rl1	=	l1;
	std::list<std::string>							l2;
	stlsoft::string_tokeniser<std::string, char>	toks("", '\0');
	std::ostream_iterator<int>						os1(cout);
	stlsoft::ostream_iterator<int>					os2(cout);
	winstl::findfile_sequence						ffs("*");
	winstl::basic_reg_key_sequence<char>			rks(HKEY_CURRENT_USER, "");
	stlsoft::pod_vector<int>						pv;
	stlsoft::pod_vector<int> const					&rpv	=	pv;

	test_(static_cast<int*>(0));

	test_(static_cast<long const*>(0));

	test_(toks.begin());

	test_(l1.begin());

	cout << endl;
	cout << endl;

	test2_(toks.begin());
	test2_(l1.begin());
	test2_(rl1.begin());
	test2_(os1);
	test2_(os2);
	test2_(ffs.begin());
	test2_(rks.begin());
	test_(pv.begin());
	test_(pv.rbegin());
	test2_(pv.rbegin());
	test_(rpv.rbegin());
	test2_(rpv.rbegin());

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
		cout << "old_dinkumware_is_const_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
