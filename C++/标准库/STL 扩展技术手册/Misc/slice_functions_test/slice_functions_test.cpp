/* /////////////////////////////////////////////////////////////////////////////
 * File:        slice_functions_test.cpp
 *
 * Purpose:     Implementation file for the slice_functions_test project.
 *
 * Created:     28th April 2005
 * Updated:     20th November 2005
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

#define TEST_std_string
#define TEST_simple_string
//#define TEST_c_style_string
//#define TEST_ACE_String_Base
//#define TEST_CString
//#define TEST_CComBSTR

#define TEST_string_literals_etc

#ifdef TEST_CString
# include <mfcstl.h>
#endif /* TEST_CString */

/* STLSoft Header Files */
#include <stlsoft.h>
#include <stlsoft/char_traits.hpp>
#include <stlsoft/string_access.hpp>
#include <stlsoft/type_traits.hpp>

#ifdef TEST_simple_string
# include <stlsoft/simple_string.hpp>
#endif /* TEST_simple_string */

#ifdef TEST_ACE_String_Base
# include <acestl.h>
# include <ace/String_Base.h>			// ACE_String_Base
# include <ace/SString.h>
# include <acestl/string_access.hpp>
#endif /* TEST_ACE_String_Base */

#ifdef TEST_CComBSTR
# include <atlstl.h>
#endif /* TEST_CComBSTR */

//#ifdef _DEBUG
//# include <comstl.h>
//#endif /* _DEBUG */

#if defined(unix) || \
    defined(__unix__)

//# include <unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

//# include <winstl.h>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C Header Files */
#include <stdio.h>

/* Standard C++ Header Files */
#include <exception>
#include <stdexcept>
#include <iostream>

#ifdef TEST_std_string
# include <string>
#endif /* TEST_std_string */

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* /////////////////////////////////////////////////////////////////////////////
 * Functions
 */

// version 5 - C-style Strings

#define TEST_OUT_OF_RANGE_POS

//#define VALIDATE_LENGTH

#define EXPRESS_CONSTRAINTS

template <typename S>
inline S left(S const &s, size_t n)
{
#ifdef EXPRESS_CONSTRAINTS
# ifdef __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
	stlsoft_static_assert(!stlsoft::base_type_traits<S>::is_pointer);
# endif /* __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
#endif /* EXPRESS_CONSTRAINTS */

#ifdef VALIDATE_LENGTH
    const size_t len    =   s.length();

    if(n > len)
    {
        n = len;
    }

#endif /* VALIDATE_LENGTH */
    return S(s, 0, n);
}

#if 1
// Overloads work, as long as we have the non-const version as well. Without it, 
// literals get passed to the template form
inline std::string left(char const *s, size_t n)
{
	return std::string(s, 0, n);
}

inline std::string left(char *s, size_t n)
{
	return left(const_cast<char const*>(s), n);
}
#else /* ? 0 */

// Separate function template
template< typename S
        , typename C
        >
inline S left(C const *s, size_t n)
{
	puts("Helper");

	const size_t len    =   ::stlsoft::c_str_len(s);
	if(n > len)
	{
		n = len;
	}
	return S(s, n);
}

# if 1
// Overloads work, as long as we have the non-const version as well. Without it, 
// literals get passed to the template form
inline std::string left(char const *s, size_t n)
{
	puts("std::string left(char const *s, size_t n)");

#  if 0
	std::string (*pfn)(char const*, size_t) = &left<std::string, char>;

	return pfn(s, n);
#  else /* ? 0 */
	return left<std::string, char>(s, n);
#  endif /* 0 */
}

# if 0
inline std::string left(char *s, size_t n)
{
	puts("std::string left(char *s, size_t n)");

	return left(const_cast<char const*>(s), n);
}
# endif /* 0 */
# else /* ? 0 */
 // 

#  if 1
#   if 1
template <typename C>
inline std::basic_string<C> left(C const *s, size_t n)
{
	puts("std::basic_string<C> left(C const *s, size_t n)");

	return left<std::basic_string<C>, C>(s, n);
}
#   endif /* 0 */

#   if 1
template <typename C>
inline std::basic_string<C> left(C *s, size_t n)
{
	puts("std::basic_string<C> left(C *s, size_t n)");

	return left<std::basic_string<C>, C>(static_cast<C const*>(s), n);
}
#   endif /* 0 */
#  else /* ? 0 */

template <typename C>
inline std::basic_string<typename stlsoft::base_type_traits<C>::base_type> left(C *s, size_t n)
{
	puts("with base_type_traits");

	typedef typename stlsoft::base_type_traits<C>::base_type	char_base_t;
//	typedef 

	return left<std::basic_string<char_base_t>, char_base_t>(static_cast<char_base_t const*>(s), n);
}

#  endif /* 0 */


# endif /* 0 */

#endif /* 0 */

#if 0
#if 0
// Partial specialisation: not allowed
template<typename C>
inline std::basic_string<C> left(C const *s, size_t n)
{
	return /* left< */std::basic_string<C>/* , C> */(s, n);
}
#else /* ? 0 */
// Full specialisation: allowed
//template<>
inline std::basic_string<char> left/* <char> */(char const *s, size_t n)
{
	return /* left< */std::basic_string<char>/* , C> */(s, n);
}
#endif /* 0 */
#endif /* 0 */





template <typename S>
inline S right(S const &s, size_t n)
{
    const size_t len =   s.length();

    if(n > len)
    {
        n = len;
    }

    return S(s, len - n, n);
}

template <typename S>
inline S mid(S const &s, size_t pos, size_t n)
{
    const size_t len =   s.length();

    if(pos > len)
    {
        pos = len;
    }

#ifdef VALIDATE_LENGTH
    if(n > len - pos)
    {
        n = len - pos;
    }
#endif /* VALIDATE_LENGTH */

    return S(s, pos, n);
}

/* /////////////////////////////////////////////////////////////////////////////
 * Test functions
 */

template <typename S>
void test_left()
{
	const S		base("She loved like diamond");

	if(left(base, 0) != "")
	{
		std::cout << "  left(,0) failed" << std::endl;
	}
	if(left(base, 3) != "She")
	{
		std::cout << "  left(,3) failed" << std::endl;
	}
	if(left(base, 21) != "She loved like diamon")
	{
		std::cout << "  left(,21) failed" << std::endl;
	}
	if(left(base, 22) != "She loved like diamond")
	{
		std::cout << "  left(,22) failed" << std::endl;
	}
	if(left(base, 23) != "She loved like diamond")
	{
		std::cout	<< "  left(,23) failed"
					<< "; [" << left(base, 23) << "]"
					<< std::endl;
	}
	if(left(base, 10000) != "She loved like diamond")
	{
		std::cout << "  left(,10000) failed" << std::endl;
	}
}

template <typename S>
void test_right()
{
	const S		base("That's the price of love");

	if(right(base, 0) != "")
	{
		std::cout << "  right(,0) failed" << std::endl;
	}
	if(right(base, 4) != "love")
	{
		std::cout << "  right(,4) failed" << std::endl;
	}
	if(right(base, 23) != "hat's the price of love")
	{
		std::cout << "  right(,23) failed" << std::endl;
	}
	if(right(base, 24) != "That's the price of love")
	{
		std::cout << "  right(,24) failed" << std::endl;
	}
	if(right(base, 25) != "That's the price of love")
	{
		std::cout << "  right(,25) failed" << std::endl;
	}
	if(right(base, 10000) != "That's the price of love")
	{
		std::cout << "  right(,10000) failed" << std::endl;
	}
}

template <typename S>
void test_mid()
{
	const S		base("Rebel Rebel");

	if(mid(base, 0, 0) != "")
	{
		std::cout << "  mid(,0,0) failed" << std::endl;
	}
	if(mid(base, 10, 0) != "")
	{
		std::cout << "  mid(,,0) failed" << std::endl;
	}
	if(mid(base, 10000, 0) != "")
	{
		std::cout << "  mid(,10000,0) failed" << std::endl;
	}
	if(mid(base, 10000, 1) != "")
	{
		std::cout << "  mid(,10000,1) failed" << std::endl;
	}
	if(mid(base, 4,2) != "l ")
	{
		std::cout << "  mid(,,2) failed" << std::endl;
	}
	if(mid(base, 10,2) != "l")
	{
		std::cout << "  mid(,,2) failed" << std::endl;
	}
	if(mid(base, 1,2) != "eb")
	{
		std::cout << "  mid(,,2) failed" << std::endl;
	}
	if(mid(base, 0, 10) != "Rebel Rebe")
	{
		std::cout << "  mid(,,10) failed" << std::endl;
	}
	if(mid(base, 1, 10) != "ebel Rebel")
	{
		std::cout << "  mid(,,10) failed" << std::endl;
	}
	if(mid(base, 6, 10) != "Rebel")
	{
		std::cout << "  mid(,,10) failed" << std::endl;
	}
	if(mid(base, 0, 11) != "Rebel Rebel")
	{
		std::cout << "  mid(,,11) failed" << std::endl;
	}
	if(mid(base, 0, 12) != "Rebel Rebel")
	{
		std::cout << "  mid(,,12) failed" << std::endl;
	}
	if(mid(base, 0, 10000) != "Rebel Rebel")
	{
		std::cout << "  mid(,10000) failed" << std::endl;
	}
	if(mid(base, 1, 10000) != "ebel Rebel")
	{
		std::cout << "  mid(,10000) failed" << std::endl;
	}
	if(mid(base, 10, 10000) != "l")
	{
		std::cout << "  mid(,10000) failed" << std::endl;
	}
	if(mid(base, 11, 10000) != "")
	{
		std::cout << "  mid(,10000) failed" << std::endl;
	}

	if(mid(base, base.length(), 0) != "")
	{
		std::cout << "  mid(,src.length(), 0) failed" << std::endl;
	}
	if(mid(base, base.length(), 1) != "")
	{
		std::cout << "  mid(,src.length(), 1) failed" << std::endl;
	}
	if(mid(base, base.length(), 100) != "")
	{
		std::cout << "  mid(,src.length(), 100) failed" << std::endl;
	}

#ifdef TEST_OUT_OF_RANGE_POS
	try
	{
		if(mid(base, base.length() + 1, 0) != "")
		{
			std::cout << "  mid(,src.length() + 1, 0) failed" << std::endl;
		}
	}
	catch(std::out_of_range &)
	{}
	try
	{
		if(mid(base, base.length() + 100, 1) != "")
		{
			std::cout << "  mid(,src.length() + 100, 1) failed" << std::endl;
		}
	}
	catch(std::out_of_range &)
	{}
	try
	{
		if(mid(base, base.length() + 100, 100) != "")
		{
			std::cout << "  mid(,src.length() + 100, 100) failed" << std::endl;
		}
	}
	catch(std::out_of_range &)
	{}
#endif /* TEST_OUT_OF_RANGE_POS */
}

template <typename S>
void test_slices()
{
	test_left<S>();
	test_right<S>();
	test_mid<S>();
}

#ifdef TEST_c_style_string
void test_slices(char *)
{
#if 0
	test_left<char*>();
#else /* ? 0 */
	test_left<char const*>();
#endif /* 0 */
}
#endif // TEST_c_style_string

#ifdef TEST_string_literals_etc
void test_literals_etc()
{
	using ::left;

	char		*pch	=	"She Loved Like Diamond";
	char		arch[]	=	"She Loved Like Diamond";
	char const	*pcch	=	"She Loved Like Diamond";
	const char	arcch[]	=	"She Loved Like Diamond";

# define SHE_LOVED_LIKE_DIAMOND		"She loved like diamond"
# define SHE_LOVED_LIKE_DIAMOND_c	static_cast<char const*>("She loved like diamond")

#if 1
	// char*
	printf("char*:        %s\n", stlsoft::c_str_ptr(left(pch, 3)));
		// With template <typename C> inline std::basic_string<C> left(C const *s, size_t n)
			// Borland: ambiguity between string and c-string forms
			// CW: goes to string class form (compile error)
			// Comeau: goes to string class form (compile error)
			// DMC++: ambiguity between string and c-string forms
			// GCC: goes to string class form (compile error)
			// Intel: goes to string class form (compile error)
			// VC6: totally confused
			// VC7.1: goes to string class form (compile error)

		// With template <typename C> inline std::basic_string<C> left(C *s, size_t n)
			// Borland: compiles left() and runs ok
			// CW: ambiguity between string and c-string forms
			// Comeau: compiles left() and runs ok
			// DMC++: compiles left() and runs ok
			// GCC: compiles left() and runs ok
			// Intel: compiles left() and runs ok
			// VC6: totally confused
			// VC7.1: compiles left() and runs ok
#endif /* 0 */

#if 1
	// char[]
	printf("char[]:       %s\n", stlsoft::c_str_ptr(left(arch, 3)));
		// With template <typename C> inline std::basic_string<C> left(C const *s, size_t n)
			// Borland: ambiguity between string and c-string forms
			// CW: goes to string class form (compile error)
			// Comeau: goes to string class form (compile error)
			// DMC++: ambiguity between string and c-string forms
			// GCC: goes to string class form (compile error)
			// Intel: goes to string class form (compile error)
			// VC6: ambiguous
			// VC7.1: compiles left() and runs ok

		// With template <typename C> inline std::basic_string<C> left(C *s, size_t n)
			// Borland: compiles left() and runs ok
			// CW: ambiguity between string and c-string forms
			// Comeau: compiles left() and runs ok
			// DMC++: compiles left() and runs ok
			// GCC: compiles left() and runs ok
			// Intel: compiles left() and runs ok
			// VC6: ambiguous
			// VC7.1: compiles left() and runs ok
#endif /* 0 */

#if 1
	// char const*
	printf("char const*:  %s\n", stlsoft::c_str_ptr(left(pcch, 3)));
		// With template <typename C> inline std::basic_string<C> left(C const *s, size_t n)
			// Borland: compiles left() and runs ok
			// CW: goes to string class form (compile error)
			// Comeau: compiles left() and runs ok
			// DMC++: compiles left() and runs ok
			// GCC: compiles left() and runs ok
			// Intel: compiles left() and runs ok
			// VC6: totally confused
			// VC7.1: compiles left() and runs ok

		// With template <typename C> inline std::basic_string<C> left(C *s, size_t n)
			// Borland: compile error inside std library
			// CW: ambiguity between string and c-string forms
			// Comeau: compile error inside std library
			// DMC++: no match
			// GCC: compile error inside std library
			// Intel: compile error inside std library
			// VC6: compile error inside std library
			// VC7.1: compile error inside std library
#endif /* 0 */

#if 1
	// char const[]
	printf("char const[]: %s\n", stlsoft::c_str_ptr(left(arcch, 3)));
		// With template <typename C> inline std::basic_string<C> left(C const *s, size_t n)
			// Borland: ambiguity between string and c-string forms
			// CW: ambiguity between string and c-string forms
			// Comeau: compiles left() and runs ok
			// DMC++: compiles left() and runs ok
			// GCC: compiles left() and runs ok
			// Intel: compiles left() and runs ok
			// VC6: ambiguity
			// VC7.1: compiles left() and runs ok

		// With template <typename C> inline std::basic_string<C> left(C *s, size_t n)
			// Borland: ambiguity between string and c-string forms
			// CW: ambiguity between string and c-string forms
			// Comeau: compile error inside std library
			// DMC++: no match
			// GCC: compile error inside std library
			// Intel: compile error inside std library
			// VC6: compile error inside std library
			// VC7.1: compile error inside std library
#endif /* 0 */

#if 1
	// literal
	printf("literal:      %s\n", stlsoft::c_str_ptr(left(SHE_LOVED_LIKE_DIAMOND, 3)));
		// With template <typename C> inline std::basic_string<C> left(C const *s, size_t n)
			// Borland: ambiguity between string and c-string forms
			// CW: ambiguity between string and c-string forms
			// Comeau: compiles left() and runs ok
			// DMC++: ambiguity between string and c-string forms
			// GCC: compiles left() and runs ok
			// Intel: compiles left() and runs ok
			// VC6: ambiguity
			// VC7.1: compiles left() and runs ok

		// With template <typename C> inline std::basic_string<C> left(C *s, size_t n)
			// Borland: compiles left() and runs ok
			// CW: ambiguity between string and c-string forms
			// Comeau: compile error inside std library
			// DMC++: compiles left() and runs ok
			// GCC: compile error inside std library
			// Intel: compile error inside std library
			// VC6: compile error inside std library
			// VC7.1: compile error inside std library
#endif /* 0 */

	STLSOFT_SUPPRESS_UNUSED(pch);
	STLSOFT_SUPPRESS_UNUSED(arch);
	STLSOFT_SUPPRESS_UNUSED(pcch);
	STLSOFT_SUPPRESS_UNUSED(arcch);
}
#endif // TEST_string_literals_etc

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("slice_functions_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	unsigned	ten		=	10;
	unsigned	hundred	=	100;

	unsigned	ur		=	ten - hundred;
	signed		sr		=	ten - hundred;

	STLSOFT_SUPPRESS_UNUSED(ur);
	STLSOFT_SUPPRESS_UNUSED(sr);

#if 0
	typedef std::basic_string<char, stlsoft::char_traits_safe<char> >	safe_string_t;

	const safe_string_t		ssafe0("Be Near Me (Munich Disco Mix)");

	std::cout << "Safe string: " << left(ssafe0, 10).c_str() << std::endl;

	typedef safe_string_t	mystring_t;

	left(std::string("Acrobat"), 100);
#ifdef TEST_simple_string
	right(stlsoft::simple_string("Voodoo Dance"), 5);
#endif /* TEST_simple_string */
	mid(mystring_t("Even Better Than The Real Thing"), 5, 6);
#endif /* 0 */

	////////////////////////////////////

#if 0
	{
		std::wcout << left<std::wstring>(L"Don't Take It Away From Me", 10) << std::endl;
	}
#endif /* 0 */

#if 0
	{
#if 0
		char const	*s	=	"Don't Take It Away From Me";

		std::cout << left(s, 10) << std::endl;
#else /* ? 0 */
		std::cout << left("Don't Take It Away From Me", 10) << std::endl;
#endif /* 0 */
	}
#endif /* 0 */

	////////////////////////////////////
	// String tests

	// std::string
#ifdef TEST_std_string
	std::cout << "Testing std::string" << std::endl;
	test_slices<std::string>();
#endif // TEST_std_string

	// stlsoft::simple_string
#ifdef TEST_simple_string
	std::cout << "Testing stlsoft::simple_string" << std::endl;
	test_slices<stlsoft::simple_string>();
#endif // TEST_simple_string

	// c-string
#ifdef TEST_c_style_string
	std::cout << "Testing c-style string" << std::endl;
	test_slices(static_cast<char*>(0));
#endif // TEST_c_style_string

	// ACE_String_Base
#ifdef TEST_ACE_String_Base
	std::cout << "Testing ACE_CString" << std::endl;
	test_slices<ACE_CString>();
#endif // TEST_ACE_String_Base

#ifdef TEST_CString
#endif // TEST_CString

#ifdef TEST_CComBSTR
#endif // TEST_CComBSTR

	////////////////////////////////////
	// String tests

#ifdef TEST_string_literals_etc
	std::cout << "Testing string literals and c-style strings" << std::endl;
	test_literals_etc();
#endif // TEST_string_literals_etc

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	::Sleep(100000);
#endif /* 0 */

	try
	{
		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		fprintf(stderr, "Unhandled error: %s\n", x.what());
	}
	catch(...)
	{
		fprintf(stderr, "Unhandled unknown error\n");
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
