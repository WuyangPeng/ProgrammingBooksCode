/* /////////////////////////////////////////////////////////////////////////////
 * File:        get_full_path_name_test.cpp
 *
 * Purpose:     Implementation file for the get_full_path_name_test project.
 *
 * Created:     15th September 2005
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

#include <platformstl/file_path_buffer.hpp>
#include <platformstl/filesystem_traits.hpp>

/* Standard C++ Header Files */
#include <exception>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

#else /* ? __WATCOMC__ */
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

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	typedef platformstl::filesystem_traits<char>		traits_t;
	typedef platformstl::basic_file_path_buffer<char>	fpb_t;

	fpb_t	buff;
	char	*pFile;
	size_t	n;

	for(n = 0; n < buff.size(); ++n)
	{
		memset(&buff[0], 0, buff.size() * sizeof(char));
		pFile = &buff[0] - 100;

		size_t	r	=	traits_t::get_full_path_name("./../include", n, &buff[0], &pFile);

		if(r > n)
		{
			fprintf(stderr, "Invalid length: requested=%d, returned=%d\n", n, r);
			break;
		}
		else if(r < n)
		{
			break;
		}
		else
		{
			fprintf(stdout, "%d\t[%.*s, %p]\n", n, r, buff.c_str(), pFile);
		}
	}
	for(n = 0; n < buff.size(); ++n)
	{
		fpb_t	buff;
		memset(&buff[0], 0, buff.size() * sizeof(char));
		pFile = &buff[0] - 100;

		size_t	r	=	traits_t::get_full_path_name("\"./../include\"", n, &buff[0], &pFile);

		if(r > n)
		{
			fprintf(stderr, "Invalid length: requested=%d, returned=%d\n", n, r);
			break;
		}
		else if(r < n)
		{
			break;
		}
		else
		{
			fprintf(stdout, "%d\t[%.*s, %p]\n", n, r, buff.c_str(), pFile);
		}
	}
	for(n = 0; n < buff.size(); ++n)
	{
		fpb_t	buff;
		memset(&buff[0], 0, buff.size() * sizeof(char));
		pFile = &buff[0] - 100;

		size_t	r	=	traits_t::get_full_path_name("\"./../include", n, &buff[0], &pFile);

		if(r > n)
		{
			fprintf(stderr, "Invalid length: requested=%d, returned=%d\n", n, r);
			break;
		}
		else if(r < n)
		{
			break;
		}
		else
		{
			fprintf(stdout, "%d\t[%.*s, %p]\n", n, r, buff.c_str(), pFile);
		}
	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
		puts("get_full_path_name_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


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
