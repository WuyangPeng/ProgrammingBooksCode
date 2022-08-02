/* /////////////////////////////////////////////////////////////////////////////
 * File:        glob_sequence_motivation_test.cpp
 *
 * Purpose:     Implementation file for the glob_sequence_motivation_test project.
 *
 * Created:     29th August 2005
 * Updated:     13th December 2005
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
#include <stlsoft/function_pointer_adaptors.hpp>
#include <stlsoft/scoped_handle.hpp>

#ifdef _WIN32
# define _STLSOFT_FORCE_ANY_COMPILER
#endif /* _WIN32 */

#include <unixstl.h>
#include <unixstl/glob_sequence.hpp>

#ifdef _WIN32
# include <unixem/implicit_link.h>
#endif /* _WIN32 */

#include <sys/stat.h>
#include <glob.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

std::string getSTLSoftDir();

std::string Operation1(char const *);
void		Operation2(char const *);

int longhand_version()
{
	cout << endl << "longhand_version()" << endl;

    std::string stlsoftDir = getSTLSoftDir();
    glob_t      gl;
#ifdef _WIN32
#if 0
    int         res = ::glob( (stlsoftDir + "\\*.h").c_str()
#else /* ? 0 */
    int         res = ::glob( stlsoftDir.append("\\a*.*").c_str()
#endif /* 0 */
#else /* ? 0 */
    int         res = ::glob( (stlsoftDir + "/*/*algo*").c_str()
#endif /* 0 */
                            , GLOB_MARK
                            , NULL
                            , &gl);

    if(GLOB_NOMATCH == res)
    {
      return 0;
    }
    else if(0 != res)
    {
      throw std::runtime_error("glob() failed");
    }
    else
    {
      stlsoft::scoped_handle<glob_t*>   r(&gl, ::globfree);

      // First operation 
      { for(size_t i = 0; i < gl.gl_pathc; ++i)
      {
        struct stat st;
        if( 0 == stat(gl.gl_pathv[i], &st) &&
            S_IFREG == (st.st_mode & S_IFREG))
        {
          Operation1(gl.gl_pathv[i]);
        }
      }}
      // Second operation
      { for(size_t i = 0; i < gl.gl_pathc; ++i)
      {
        char const  *item = gl.gl_pathv[gl.gl_pathc - (i + 1)];
        size_t      len   = strlen(item);
        if('/' != item[len - 1]) // Not a directory
        {
          Operation2(item);
        }
      }}

      size_t n = gl.gl_pathc;

//      globfree(&gl);

      return n;
    }

#ifdef STLSOFT_COMPILER_IS_DMC
	return 0;
#endif /* compiler */
}

int shorthand_version()
{
	cout << endl << "shorthand_version()" << endl;

#ifdef _WIN32
	unixstl::glob_sequence  gls(getSTLSoftDir(), "*.h"
#else /* ? 0 */
	unixstl::glob_sequence  gls(getSTLSoftDir(), "*/*algo*"
#endif /* 0 */
#if 0
							  , unixstl::glob_sequence::files);
#else /* ? 0 */
							  , unixstl::glob_sequence::files | unixstl::glob_sequence::absolutePath);
#endif /* 0 */

	std::for_each(gls.begin(), gls.end(), std::ptr_fun(Operation1));
#if !defined(STLSOFT_CF_COMPILER_SUPPORTS_RETURN_VOID)
	std::for_each(gls.rbegin(), gls.rend(), stlsoft::ptr_fun_void(Operation2));
#else /* ? 0 */
	std::for_each(gls.rbegin(), gls.rend(), stlsoft::ptr_fun(Operation2));
#endif /* 0 */

	return gls.size();
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		longhand_version();
		shorthand_version();
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
		cout << "glob_sequence_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */


		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		cerr << "Unhandled error: " << x.what() << endl;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */

std::string getSTLSoftDir()
{
#if 0
	return getenv("STLSOFT_INCLUDE");
#else /* ? 0 */
	return "../..";
#endif /* 0 */
}

std::string Operation1(char const *s)
{
	cout << "[Operation 1: " << s << "]" << endl;

	return s;
}

void		Operation2(char const *s)
{
	cout << "[Operation 2: " << s << "]" << endl;
}

/* ////////////////////////////////////////////////////////////////////////// */
