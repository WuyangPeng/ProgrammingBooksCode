/* /////////////////////////////////////////////////////////////////////////////
 * File:        scatter_vector_test.cpp
 *
 * Purpose:     Implementation file for the scatter_vector_test project.
 *
 * Created:     20th September 2005
 * Updated:     29th April 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2007, Synesis Software Pty Ltd.
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
#include <stlsoft/conversion/sap_cast.hpp>
#include <stlsoft/memory/auto_buffer.hpp>

/* PlatformSTL Header Files */
#define _WIN32_WINNT	0x0400

#include <platformstl/filesystem/path.hpp>
//#include <platformstl/scatter_slice_sequence_1.hpp>
#include <platformstl/scatter_slice_sequence_2.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl/filesystem/filesystem_traits.hpp>

# ifdef _WIN32
#  include <unixem/implicit_link.h>
# endif /* _WIN32 */

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl/error/exceptions.hpp>
# include <winstl/filesystem/filesystem_traits.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


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
#include <sys/types.h>
#if defined(PLATFORMSTL_OS_IS_UNIX)
# include <sys/uio.h>
#elif defined(PLATFORMSTL_OS_IS_WIN32)
# include <winsock2.h>
#endif /* operating system */


/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

template <ss_typename_param_k C>
struct case_swap;

template <>
struct case_swap<stlsoft::byte_t>
{
	stlsoft::byte_t operator ()(stlsoft::byte_t ch) const
	{
		if(islower(ch))
		{
			ch = toupper(ch);
		}
		else if(isupper(ch))
		{
			ch = tolower(ch);
		}

		return ch;
	}
};

/* ////////////////////////////////////////////////////////////////////////// */

#if defined(PLATFORMSTL_INCL_PLATFORMSTL_HPP_SCATTER_SLICE_SEQUENCE_1)

static int main_(int argc, char **argv)
{
#if defined(PLATFORMSTL_OS_IS_UNIX)
	typedef platformstl::scatter_slice_sequence<struct iovec>	sss_t;

	if(argc < 2)
	{
		fprintf(stderr, "Must specify file to read\n");
	}
	else
	{
		char const			*fileName	=	argv[1];
		platformstl::path	outPath(fileName);

//		outPath.pop_ext();
		outPath.push_ext(".sss_out");

#elif defined(PLATFORMSTL_OS_IS_WIN32)
	typedef platformstl::scatter_slice_sequence<WSABUF>			sss_t;

	WSADATA	data;

	if(0 != ::WSAStartup(0x0202, &data))
	{
		throw winstl::windows_exception("Cannot initialise WinSock libraries: ", ::GetLastError());

		return EXIT_FAILURE;
	}
	else
	{
#endif /* operating system */

		sss_t				sss(3);
		sss_t::result_type	res;

		char	buff1[32];
		char	buff2[27];
		char	buff3[40];

		sss.set_slice(0, buff1, sizeof(buff1));
		sss.set_slice(1, buff2, sizeof(buff2));
		sss.set_slice(2, buff3, sizeof(buff3));

#if defined(PLATFORMSTL_OS_IS_UNIX)
		int		fd		=	unixstl::filesystem_traits<char>::open_file(fileName, _O_RDONLY, 0);
		size_t	n		=	sss.read(::readv, fd, &res);

		unixstl::filesystem_traits<char>::close_file(fd);

		// Must now test res to determine how many slices were written

		for(size_t j = 0; j < n; ++j)
		{
			char	&ch	=	*stlsoft::sap_cast<char*>(&sss[j]);

			if(islower(ch))
			{
				ch = toupper(ch);
			}
			else if(isupper(ch))
			{
				ch = tolower(ch);
			}
		}

		fd		=	unixstl::filesystem_traits<char>::open_file(outPath.c_str(), _O_WRONLY | _O_CREAT | _O_TRUNC, 0);
		n		=	sss.write(::writev, fd, n, &res);

		unixstl::filesystem_traits<char>::close_file(fd);

#elif defined(PLATFORMSTL_OS_IS_WIN32)

		struct sockaddr_in sin;

		sin.sin_family		=	AF_INET;
		sin.sin_port		=	htons(48001);
		sin.sin_addr.s_addr =	inet_addr("127.0.0.1");

		SOCKET	sk		=	::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		DWORD	flags	=	0;

		::bind(sk, (SOCKADDR *)&sin, sizeof(sin));

		size_t	n		=	sss.read(::WSARecvFrom, sk, flags, &res);

#endif /* operating system */

		fprintf(stdout, "[%.*s][%.*s][%.*s]\n", sizeof(buff1), buff1, sizeof(buff2), buff2, sizeof(buff3), buff3);
	}

    return 0;
}

#elif defined(PLATFORMSTL_INCL_PLATFORMSTL_HPP_SCATTER_SLICE_SEQUENCE_2)

static int main_(int argc, char **argv)
{
#if defined(PLATFORMSTL_OS_IS_UNIX)
	typedef platformstl::scatter_slice_sequence<struct iovec>	sss_t;

	if(argc < 2)
	{
		fprintf(stderr, "Must specify file to read\n");
	}
	else
	{
		char const			*fileName	=	argv[1];
		platformstl::path	outPath(fileName);

//		outPath.pop_ext();
		outPath.push_ext(".sss_out");

#elif defined(PLATFORMSTL_OS_IS_WIN32)
	typedef platformstl::scatter_slice_sequence<WSABUF>			sss_t;

	WSADATA	data;

	if(0 != ::WSAStartup(0x0202, &data))
	{
		throw winstl::windows_exception("Cannot initialise WinSock libraries: ", ::GetLastError());

		return EXIT_FAILURE;
	}
	else
	{
#endif /* operating system */

		sss_t				sss(3);
		sss_t::result_type	res;

		char	buff1[32];
		char	buff2[27];
		char	buff3[40];

		sss.set_slice(0, buff1, sizeof(buff1));
		sss.set_slice(1, buff2, sizeof(buff2));
		sss.set_slice(2, buff3, sizeof(buff3));

#if defined(PLATFORMSTL_OS_IS_UNIX)
		int		fd		=	unixstl::filesystem_traits<char>::open_file(fileName, _O_RDONLY, 0);
		size_t	n		=	sss.read(::readv, fd, &res);

		unixstl::filesystem_traits<char>::close_file(fd);

		// Must now test res to determine how many slices were written

		std::transform(sss.payload().begin(), sss.payload().end(), sss.payload().begin(), case_swap<stlsoft::byte_t>());

		fd		=	unixstl::filesystem_traits<char>::open_file(outPath.c_str(), _O_WRONLY | _O_CREAT | _O_TRUNC, 0);
		n		=	sss.write(::writev, fd, n, &res);

		unixstl::filesystem_traits<char>::close_file(fd);

#elif defined(PLATFORMSTL_OS_IS_WIN32)

		struct sockaddr_in sin;

		sin.sin_family		=	AF_INET;
		sin.sin_port		=	htons(48001);
		sin.sin_addr.s_addr =	inet_addr("127.0.0.1");

		SOCKET	sk		=	::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		DWORD	flags	=	0;

		::bind(sk, (SOCKADDR *)&sin, sizeof(sin));

		size_t	n		=	sss.read(::WSARecvFrom, sk, flags, &res);

#endif /* operating system */

		fprintf(stdout, "[%.*s][%.*s][%.*s]\n", sizeof(buff1), buff1, sizeof(buff2), buff2, sizeof(buff3), buff3);
	}

    return 0;
}

#elif defined(PLATFORMSTL_INCL_PLATFORMSTL_HPP_SCATTER_SLICE_SEQUENCE_3)

#elif defined(PLATFORMSTL_INCL_PLATFORMSTL_HPP_SCATTER_SLICE_SEQUENCE_4)

#else
# error No scatter_slice_sequence class included
#endif

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
		puts("scatter_vector_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
