/* /////////////////////////////////////////////////////////////////////////
 * File:        glob_perf.test.cpp
 *
 * Purpose:     Implementation file for the glob_perf.test project.
 *
 * Created:     20th January 2007
 * Updated:     21st January 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <stlsoft/iterators/ostream_iterator.hpp>



/* UNIXSTL Header Files */
#include <unixstl/error/exceptions.hpp>
#include <unixstl/filesystem/glob_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft/algorithms/bounded.hpp>
#include <stlsoft/shims/access/string.hpp>

/* PlatformSTL Header Files */
#include <platformstl/platformstl.hpp>

#include <platformstl/performance/performance_counter.hpp>

platformstl_ns_using(performance_counter)


/* UNIXEm Header Files */
#ifdef PLATFORMSTL_OS_IS_UNIX
# include <unixem/unixem.h>
# include <unixem/implicit_link.h>
#endif /* PLATFORMSTL_OS_IS_UNIX */

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

typedef std::string				string_t;
typedef std::vector<unsigned>	timings_t;

/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static int Operation1(char const *entry);
static int Operation2(char const *entry);
static unsigned test_API(char const *pattern, unsigned NUM_ITERATIONS);
static unsigned test_glob_sequence(char const *pattern, unsigned NUM_ITERATIONS);

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
    int                 iRet        =   EXIT_SUCCESS;
    int                 bVerbose    =   true;
    performance_counter counter;
	timings_t			apiTimings;
	timings_t			gsTimings;

	{ for(unsigned i = 0; i < 200; ++i)
	{
		counter.start();
		test_API("", 0);
		counter.stop();
		apiTimings.push_back(static_cast<unsigned>(counter.get_microseconds()));

		counter.start();
		test_glob_sequence("", 0);
		counter.stop();
		gsTimings.push_back(static_cast<unsigned>(counter.get_microseconds()));
	}}

	std::sort(apiTimings.begin(), apiTimings.end());
	std::sort(gsTimings.begin(), gsTimings.end());

	std::cout << "API:" << std::endl;
	stlsoft::copy_n(apiTimings.begin(), 10, stlsoft::ostream_iterator<int>(std::cout, "\t", "\n"));

	std::cout << "glob_sequence:" << std::endl;
	stlsoft::copy_n(gsTimings.begin(), 10, stlsoft::ostream_iterator<int>(std::cout, "\t", "\n"));

    return iRet;
}

int main(int argc, char *argv[])
{
    int             res;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
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
        puts("glob_perf.test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        res = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        res = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "Unhandled unknown error" << endl;

        res = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return res;
}

/* ////////////////////////////////////////////////////////////////////// */

inline string_t getSTLSoftDir()
{
	return string_t(::getenv("STLSOFT")) += "/include";
}

static int Operation1(char const *entry)
{
	return ::strlen(entry);
}

static int Operation2(char const *entry)
{
	return ::strlen(entry);
}

typedef unixstl::unix_exception	some_exception_class;

static unsigned test_API(char const *pattern, unsigned NUM_ITERATIONS)
{
	std::string stlsoftDir = getSTLSoftDir();
	glob_t      gl;
#ifdef PLATFORMSTL_OS_IS_UNIX
	int         res = ::glob( (stlsoftDir + "/*/*algo*").c_str()
#else /* ? OS */
	int         res = ::glob( (stlsoftDir + "/*.h").c_str()
#endif /* OS */
							, GLOB_MARK
							, NULL
							, &gl);

	if(GLOB_NOMATCH == res)
	{
	  return 0;
	}
	else if(0 != res)
	{
	  throw some_exception_class("glob() failed", res);
	}
	else
	{
	  // First operation 
	  { for(size_t i = 0; i < gl.gl_pathc; ++i)
	  {
		struct stat st;
		if( 0 == ::stat(gl.gl_pathv[i], &st) &&
			S_IFREG == (st.st_mode & S_IFREG))
		{
		  Operation1(gl.gl_pathv[i]);
		}
	  }}
	  // Second operation
	  { for(size_t i = 0; i < gl.gl_pathc; ++i)
	  {
		char const  *item = gl.gl_pathv[gl.gl_pathc - (i + 1)];
		size_t      len   = ::strlen(item);
		if('/' != item[len - 1]) // Not a directory
		{
		  Operation2(item);
		}
	  }}

	  size_t n = gl.gl_pathc;
	  ::globfree(&gl);
	  return n;  
	}
}

static unsigned test_glob_sequence(char const *pattern, unsigned NUM_ITERATIONS)
{
	using unixstl::glob_sequence;
#ifdef PLATFORMSTL_OS_IS_UNIX
	glob_sequence   gls(getSTLSoftDir(), "*/*algo*", glob_sequence::files);
#else /* ? OS */
	glob_sequence   gls(getSTLSoftDir(), "*.h", glob_sequence::files);
#endif /* OS */

	std::for_each(gls.begin(), gls.end(), std::ptr_fun(Operation1));
	std::for_each(gls.rbegin(), gls.rend(), std::ptr_fun(Operation2));

	return gls.size();
}

/* ////////////////////////////////////////////////////////////////////// */
