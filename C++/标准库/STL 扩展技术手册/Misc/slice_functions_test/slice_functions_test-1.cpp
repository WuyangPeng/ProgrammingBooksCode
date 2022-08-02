/* /////////////////////////////////////////////////////////////////////////////
 * File:        slice_functions_test.cpp
 *
 * Purpose:     Implementation file for the slice_functions_test project.
 *
 * Created:     28th April 2005
 * Updated:     30th December 2005
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
//#define TEST_simple_string
//#define TEST_ACE_String_Base
//#define TEST_CString
//#define TEST_CComBSTR

#ifdef TEST_CString
# include <mfcstl.h>
#endif /* TEST_CString */

/* STLSoft Header Files */
#include <stlsoft.h>

#ifdef TEST_simple_string
# include <stlsoft/simple_string.hpp>
#endif /* TEST_simple_string */

#ifdef TEST_ACE_String_Base
# include <acestl.h>
# include <ace/String_Base.h>			// ACE_String_Base
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

// version 1 - std::string

inline std::string left(std::string const &s, size_t n)
{
#if 0
    const size_t len	=	s.size();

    if(n > len)
    {
        n = len;
    }

#endif /* 0 */
    return std::string(s, 0, n);
}

inline std::string right(std::string const &s, size_t n)
{
    const size_t len =   s.size();

    if(n > len)
    {
        n = len;
    }

    return std::string(s, len - n, n);
}

inline std::string mid(std::string const &s, size_t pos, size_t n)
{
    const size_t len =   s.size();

#if 0
    if(pos > len)
    {
        pos = len;
    }

    if(n > len - pos)
    {
        n = len - pos;
    }
#else
    if(pos > len)
    {
        pos = len;
    }
#endif /* 0 */

    return std::string(s, pos, n);
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
		std::cout << "  left(,23) failed" << std::endl;
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
		std::cout << "  mid(,,0) failed" << std::endl;
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
}

template <typename S>
void test_slices()
{
	test_left<S>();
	test_right<S>();
	test_mid<S>();
}

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

	/* . */
#ifdef TEST_std_string
	std::cout << "Testing std::string" << std::endl;
	test_slices<std::string>();
#endif TEST_std_string

#ifdef TEST_simple_string
#endif TEST_simple_string

#ifdef TEST_ACE_String_Base
#endif TEST_ACE_String_Base

#ifdef TEST_CString
#endif TEST_CString

#ifdef TEST_CComBSTR
#endif TEST_CComBSTR

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
