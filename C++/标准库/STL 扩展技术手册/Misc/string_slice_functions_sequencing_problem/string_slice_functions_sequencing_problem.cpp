/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_slice_functions_sequencing_problem.cpp
 *
 * Purpose:     Implementation file for the string_slice_functions_sequencing_problem project.
 *
 * Created:     30th April 2005
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

/* STLSoft Header Files */
#include <stlsoft.h>
#include <stlsoft/simple_string.hpp>
#include <stlsoft/string_access.hpp>


/* Standard C Header Files */
#include <stdio.h>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

template <typename S>
inline S &left(S const &s, size_t n, S &result)
{
#if 0
    const size_t len	=	s.size();

    if(n > len)
    {
        n = len;
    }

#endif /* 0 */
    return result.assign(s, 0, n);
}

template <typename S>
inline S &right(S const &s, size_t n, S &result)
{
    const size_t len =   s.size();

    if(n > len)
    {
        n = len;
    }

    return result.assign(s, len - n, n);
}

template <typename S>
inline S &mid(S const &s, size_t pos, size_t n, S &result)
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

    return result.assign(s, pos, n);
}

template <typename S, typename C>
inline S &mid(C const *s, size_t pos, size_t n, S &result)
{
    const size_t len =   stlsoft::c_str_len(s);

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

    return result.assign(s, pos, n);
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("string_slice_functions_sequencing_problem: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	stlsoft::simple_string s("Block Rockin' Beats");
	stlsoft::simple_string dummy; // Not used in the client code at all. Dreary

#if 1
	std::cout << left(s, 5, dummy)
			  << mid("Block Rockin' Beats", 5, 9, dummy)
			  << right(s, 5, dummy);
#else /* ? 0 */
	std::cout << left(s, 5, dummy);
	std::cout << mid("Block Rockin' Beats", 5, 9, dummy);
	std::cout << right(s, 5, dummy);
#endif /* 0 */
	std::cout << std::endl;

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
