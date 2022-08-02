/* /////////////////////////////////////////////////////////////////////////
 * File:        rds_perf.test.cpp
 *
 * Purpose:     Implementation file for the rds_perf.test project.
 *
 * Created:     20th January 2007
 * Updated:     22nd January 2007
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
#include <unixstl/filesystem/readdir_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft/algorithms/bounded.hpp>
#include <stlsoft/shims/access/string.hpp>

/* PlatformSTL Header Files */
#include <platformstl/platformstl.hpp>

#include <platformstl/performance/performance_counter.hpp>
#include <platformstl/system/environment_map.hpp>

platformstl_ns_using(performance_counter)

/* UNIXEm Header Files */
#if defined(PLATFORMSTL_OS_IS_WIN32)
# include <unixem/unixem.h>
# include <unixem/implicit_link.h>
#endif /* OS */

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

static std::string              getWorkplaceDirectory();
static std::vector<std::string>	getWorkplaceSubdirectories_API();
static std::vector<std::string> getWorkplaceSubdirectories_rds();

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
		getWorkplaceSubdirectories_API();
		counter.stop();
		apiTimings.push_back(static_cast<unsigned>(counter.get_microseconds()));

		counter.start();
		getWorkplaceSubdirectories_rds();
		counter.stop();
		gsTimings.push_back(static_cast<unsigned>(counter.get_microseconds()));
	}}

	std::sort(apiTimings.begin(), apiTimings.end());
	std::sort(gsTimings.begin(), gsTimings.end());

	std::cout << "API:" << std::endl;
	stlsoft::copy_n(apiTimings.begin(), 10, stlsoft::ostream_iterator<int>(std::cout, "\t", "\n"));

	std::cout << "readdir_sequence:" << std::endl;
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
        puts("rds_perf.test: " __STLSOFT_COMPILER_LABEL_STRING);
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

typedef unixstl::unix_exception	some_exception_class;

static std::string getWorkplaceDirectory()
{
	platformstl::environment_map	ENV;

#if defined(PLATFORMSTL_OS_IS_UNIX)
//	return "~";
	return std::string(ENV["STLSOFT"]).append("/include");
#elif defined(PLATFORMSTL_OS_IS_WIN32)
//	return std::string(platformstl::environment_variable("HOMEDRIVE").c_str()).append(platformstl::environment_variable("HOMEPATH").c_str());
	return std::string(ENV["STLSOFT"]).append("/include");
#else
# error Operating system not discriminated
#endif /* PLATFORMSTL_OS_IS_WIN32 */

}

static std::vector<std::string> getWorkplaceSubdirectories_API()
{
  std::string               searchDir = getWorkplaceDirectory();
  std::vector<std::string>  dirNames;
  DIR                       *dir = ::opendir(searchDir.c_str());
  if(NULL == dir)
  {
    throw some_exception_class("Cannot enumerate Workplace", errno);
  }
  else
  {
    struct dirent *entry;
    if('/' != searchDir[searchDir.size() - 1])
    {
      searchDir += '/';
    }
    for(; NULL != (entry = ::readdir(dir)); )
    {
      if( '.' == entry->d_name[0] &&
          ( '\0' == entry->d_name[1] ||    // "."
            ( '.' == entry->d_name[1] &&
              '\0' == entry->d_name[2])))  // ".."
      {
        // dots directory, so skip it
      }
      else
      {
        struct stat st;
        std::string entryPath = searchDir + entry->d_name;
        if(0 == ::stat(entryPath.c_str(), &st))
        {
          if(S_IFDIR == (st.st_mode & S_IFDIR))
          {
            dirNames.push_back(entryPath);
          }
        }
      }
    }
    ::closedir(dir);
  }
  return dirNames;
}

static std::vector<std::string> getWorkplaceSubdirectories_rds()
{
	using unixstl::readdir_sequence;
	readdir_sequence  rds(getWorkplaceDirectory()
				   , readdir_sequence::directories | readdir_sequence::fullPath);
#if defined(STLSOFT_CF_STD_LIBRARY_IS_DINKUMWARE_VC) && \
	STLSOFT_CF_STD_LIBRARY_DINKUMWARE_VC_VERSION < STLSOFT_CF_DINKUMWARE_VC_VERSION_7_1

	std::vector<std::string>	v;

	std::copy(rds.begin(), rds.end(), std::back_inserter(v));

	return v;

#else /* ? std */
	return std::vector<std::string>(rds.begin(), rds.end());
#endif /* std */
}

/* ////////////////////////////////////////////////////////////////////// */
