/* /////////////////////////////////////////////////////////////////////////////
 * File:        fixed_array_example.cpp
 *
 * Purpose:     Implementation file for the fixed_array_example project.
 *
 * Created:     18th May 2005
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

/* STLSoft Header Files */
#include <stlsoft.h>
#include <stlsoft/fixed_array.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <numeric>

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */

/* Standard C Header Files */
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */


/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("fixed_array_example: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	stlsoft::fixed_array_2d<int>  ar(10, 10);

	ar[3][3] = 3 * 3;
	ar[9][9] = 9 * 9;

	for(size_t i = 0; i < ar.dimension0(); ++i)
	{
		for(size_t j = 0; j < ar.dimension1(); ++j)
		{
			printf("[%2d][%2d] = %d\n", i, j, ar[i][j]);
		}
	}

	for(stlsoft::fixed_array_2d<int>::const_iterator b = ar.begin(); b != ar.end(); ++b)
	{
		printf("%d\n", *b);
	}

	int	total	=	std::accumulate(ar.begin(), ar.end(), 0);

	printf("total = %d\n", total);

#if 0
	stlsoft::fixed_array_1d<int>  ar1(ar[3]);
#endif /* 0 */

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
