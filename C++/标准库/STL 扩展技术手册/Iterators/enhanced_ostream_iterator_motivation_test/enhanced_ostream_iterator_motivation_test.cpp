/* /////////////////////////////////////////////////////////////////////////////
 * File:        enhanced_ostream_iterator_motivation_test.cpp
 *
 * Purpose:     Implementation file for the enhanced_ostream_iterator_motivation_test project.
 *
 * Created:     17th December 2005
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



#include <mfcstl.h>


/* STLSoft Header Files */
#include <stlsoft.h>

//#define STLSOFT_ALLOCATOR_SELECTOR_NO_USE_STLSOFT_MALLOC_ALLOCATOR
//#define STLSOFT_ALLOCATOR_SELECTOR_NO_USE_STLSOFT_NEW_ALLOCATOR
//#define STLSOFT_ALLOCATOR_SELECTOR_NO_USE_STD_ALLOCATOR

#include <stlsoft/allocator_selector.hpp>



typedef stlsoft::allocator_selector<int>::allocator_type	ator_t;


/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft.h>

#include <stlsoft/iterators/ostream_iterator.hpp>

#include <stlsoft/type_traits.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
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
 * Forward declarations
 */

template <typename T>
inline void print_type(T )
{
	printf("%s is %san array\n", typeid(T).name(), stlsoft::base_type_traits_array_detector<T>::value ? "" : "not ");
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		int			i		=	0;
		int			*pi		=	0;
		int			ai[1];

		print_type(i);
		print_type(pi);
		print_type(ai);

	}


	/* . */
	{
		using recls::stl::search_sequence;
		using recls::RECLS_F_RECURSIVE;

		cout << "With std::ostream_iterator:" << endl << endl;

		search_sequence	headers(".", "*.h|*.hpp", RECLS_F_RECURSIVE);
		search_sequence	impls(".", "*.c|*.cpp", RECLS_F_RECURSIVE);

		cout << "Header Files:" << endl << "\t";
		std::copy(headers.begin(), headers.end()
				, std::ostream_iterator<search_sequence::value_type>(cout, "\n\t"));
		cout << "\r";

		cout << "Implementation Files:" << endl << "\t";
		std::copy(impls.begin(), impls.end()
				, std::ostream_iterator<search_sequence::value_type>(cout, "\n\t"));
		cout << "\r";
	}

	{
		using recls::stl::search_sequence;
		using recls::RECLS_F_RECURSIVE;

		cout << "With stlsoft::ostream_iterator:" << endl << endl;

		search_sequence	headers(".", "*.h|*.hpp", RECLS_F_RECURSIVE);
		search_sequence	impls(".", "*.c|*.cpp", RECLS_F_RECURSIVE);

		cout << "Header Files:" << endl;
		std::copy(headers.begin(), headers.end()
				, stlsoft::ostream_iterator<search_sequence::value_type>(cout, "\t", "\n"));

		cout << "Implementation Files:" << endl;
		std::copy(impls.begin(), impls.end()
				, stlsoft::ostream_iterator<search_sequence::value_type>(cout, "\t", "\n"));
	}

	{
		stlsoft::ostream_iterator<int>	o1(cout);
		stlsoft::ostream_iterator<int>	o2(cout, "suffix");
		stlsoft::ostream_iterator<int>	o3(cout, "prefix", "suffix");

		std::string						prefix("prefix");
		stlsoft::simple_string			suffix("suffix");

		stlsoft::ostream_iterator<int>	o4(cout, suffix);
		stlsoft::ostream_iterator<int>	o5(cout, prefix/* , "" */);
		stlsoft::ostream_iterator<int>	o6(cout, prefix, "suffix");
		stlsoft::ostream_iterator<int>	o7(cout, "prefix", suffix);
		stlsoft::ostream_iterator<int>	o8(cout, prefix, suffix);
	}

#if 1
	{
#if 0
		using std::ostream_iterator;
#else /* ? 0 */
		using stlsoft::ostream_iterator;
#endif /* 0 */

		ostream_iterator<int>		s1(std::cout, " ");

		ostream_iterator<int>		s2(std::cout, L" ");
	}
#endif /* 0 */

#if 1
	if(0) // Don't enable this!
	{
		using recls::stl::basic_search_sequence;
		using recls::RECLS_F_RECURSIVE;

		CArchive	ar(NULL, 0);


		basic_search_sequence<char>	headers(".", "*.h|*.hpp", RECLS_F_RECURSIVE);
		reclstl::basic_search_sequence<char>::value_type	v = *headers.begin();

		ar << int(0);
		ar << v;

	}
#endif /* 0 */


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
		cout << "enhanced_ostream_iterator_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
