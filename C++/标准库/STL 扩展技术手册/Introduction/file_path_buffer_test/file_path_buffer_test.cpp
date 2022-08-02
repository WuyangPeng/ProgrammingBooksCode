/* /////////////////////////////////////////////////////////////////////////////
 * File:        file_path_buffer_test.cpp
 *
 * Purpose:     Implementation file for the file_path_buffer_test project.
 *
 * Created:     14th September 2005
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

#include <platformstl/platformstl.hpp>
#include <platformstl/filesystem_traits.hpp>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl.h>
# include <unixstl_filesystem_functions.h>

namespace platform_stl	=	unixstl;

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl.h>
# include <winstl/error_desc.hpp>
# include <winstl/filesystem_functions.hpp>

namespace platform_stl	=	winstl;

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C++ Header Files */
#include <exception>
#include <string>

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
 * Typedefs
 */

typedef platformstl::filesystem_traits<char>	traits_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Function declarations
 */

//#define	INCREMENT	(_MAX_DIR - 1)
#define	INCREMENT	(32)

inline std::string slashed(std::string &s)
{
	if(s.size() > _MAX_DIR)
	{
		for(size_t i = INCREMENT; i < s.size(); i += INCREMENT)
		{
			s[i] = '\\';
		}
	}

	return s;
}

inline std::wstring slashed(std::wstring &s)
{
	if(s.size() > _MAX_DIR)
	{
		for(size_t i = INCREMENT; i < s.size(); i += INCREMENT)
		{
			s[i] = L'\\';
		}
	}

	return s;
}

/* ////////////////////////////////////////////////////////////////////////// */

int enableFileDelete(	void							*param
					,	char const						*s
					,	traits_t::stat_data_type const	*st
#if defined(PLATFORMSTL_OS_IS_UNIX)
					,	struct dirent const				*d
#endif /* os */
					,	traits_t::error_type			dw)
{
	size_t	n	=	strlen(s);

	if(~0 == dw)
	{
		fprintf(stdout, "Entering %s\n", s);
	}
#if defined(PLATFORMSTL_OS_IS_WIN32)
	else if(ERROR_SUCCESS == dw)
#else /* ? WIN32 */
	else if(0 == dw)
#endif /* WIN32 */
	{
		if(NULL == st)
		{
			fprintf(stdout, "Deleted: %s\n", s);
		}
		else
		{
//			fprintf(stdout, "Request to delete %s %s\n", (FILE_ATTRIBUTE_DIRECTORY & st->dwFileAttributes) ? "directory" : "file", s);
			return traits_t::is_directory(st);
		}
	}
	else
	{
		if(NULL == st)
		{
#if defined(PLATFORMSTL_OS_IS_WIN32)
			fprintf(stdout, "Failed to delete: %s; reason: %s\n", s, winstl::error_desc(dw).c_str());
#else /* ? WIN32 */
			fprintf(stdout, "Failed to delete: %s; reason: %s\n", s, strerror(dw));
#endif /* WIN32 */
		}
		else
		{
#if defined(PLATFORMSTL_OS_IS_WIN32)
			fprintf(stdout, "Failed to delete: %s; reason: %s; entry: %s\n", s, winstl::error_desc(dw).c_str(), st->cFileName);
#else /* ? WIN32 */
			fprintf(stdout, "Failed to delete: %s; reason: %s; entry: %s\n", s, strerror(dw), d->d_name);
#endif /* WIN32 */
		}
	}

	return true;
}

#if defined(PLATFORMSTL_OS_IS_WIN32)
int enableFileDelete(void *param, wchar_t const *s, WIN32_FIND_DATAW const *st, DWORD dw)
{
	size_t	n	=	wcslen(s);

	if(NULL != st)
	{
		fwprintf(stdout, L"Request to delete %s %s\n", (FILE_ATTRIBUTE_DIRECTORY & st->dwFileAttributes) ? L"directory" : L"file", s);

		return true;
	}
	else
	{
		if(~0 == dw)
		{
			fwprintf(stdout, L"Entering %s\n", s);
		}
		else if(ERROR_SUCCESS == dw)
		{
			fwprintf(stdout, L"Deleted: %s\n", s);
		}
		else
		{
			fwprintf(stdout, L"Failed to delete: %s; reason: %s\n", s, winstl::error_desc_w(dw).c_str());
		}

		return true;
	}
}
#endif /* WIN32 */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		char const	*s	=	"H:\\aa\\bbbb\\cccccc\\dddddddd\\eeeeeeeeee\\ffffffffffff\\gggggggggggggggg\\hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\\iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\\jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
		size_t		len	=	strlen(s);

		if(platform_stl::create_directory_recurse(s))
		{
			platform_stl::remove_directory_recurse("H:\\aa", enableFileDelete, NULL);
			traits_t::get_last_error();
		}
	}

	return 0;

#if defined(PLATFORMSTL_OS_IS_WIN32)
	winstl::remove_directory_recurse(L"\\\\?\\H:\\aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", enableFileDelete, NULL);

	return 0;

#if 0
	{
		const size_t	N	=	_MAX_PATH - 50;
		std::string		long_name(N - 3, L'c');
		std::string		long_path("H:\\" + slashed(long_name));
		BOOL			b	=	winstl::create_directory_recurse(long_path.c_str(), NULL);
		DWORD			dw	=	::GetLastError();

		if(b)
		{
			winstl::remove_directory_recurse(long_path.c_str());
		}

		winstl::remove_directory_recurse("H:\\CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
	}
#else /* ? 0 */
#endif /* 0 */

	{
		const size_t	N	=	/* 32767 */32762;
		std::wstring	long_name(N - 3, L'a');
		std::wstring	long_path(L"H:\\" + slashed(long_name));
		wchar_t const	*s	=	long_path.c_str() + (long_path.size() - 40);
		BOOL			b	=	1 || winstl::create_directory_recurse((L"\\\\?\\" + long_path).c_str(), NULL);
		DWORD			dw	=	::GetLastError();

		if(b)
		{
#if 1
			winstl::remove_directory_recurse((L"\\\\?\\" + long_path).c_str());
#else /* ? 0 */
			b = ::RemoveDirectoryW((L"\\\\?\\" + long_path).c_str());
#endif /* 0 */
			::GetLastError();

			winstl::remove_directory_recurse(L"H:\\aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		}
	}

    return 0;
#endif /* WIN32 */
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
		puts("file_path_buffer_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
