/* /////////////////////////////////////////////////////////////////////////////
 * File:        readdir_sequence_motivation_test.cpp
 *
 * Purpose:     Implementation file for the readdir_sequence_motivation_test project.
 *
 * Created:     2nd September 2005
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


#define UNIXSTL_READDIR_SEQUENCE_DEMONSTRATE_NONCOPYABLE_ITERATOR

#ifdef _WIN32
# define _STLSOFT_FORCE_ANY_COMPILER
#endif /* _WIN32 */

/* STLSoft Header Files */
#include <stlsoft.h>
#include <stlsoft/function_pointer_adaptors.hpp>
#include <stlsoft/scoped_handle.hpp>

#include <unixstl.h>
#if 1
# include <unixstl/readdir_sequence.hpp>
#else /* ? 0 */
# include "./readdir_sequence.hpp"
#endif /* 0 */

#ifdef _WIN32
# include <unixem/implicit_link.h>
#endif /* _WIN32 */


#include <sys/stat.h>
#include <unistd.h>


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

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

#if 0
static const char	HOME[]	=	"/home/matty";
#else /* ? 0 */
static const char	HOME[]	=	"../..";
#endif /* 0 */

std::string getWorkplaceDirectory()
{
	return HOME;
}

std::vector<std::string> longhand_version()
{
  std::string               searchDir = getWorkplaceDirectory();
  std::vector<std::string>  dirNames;
  DIR                       *dir = ::opendir(searchDir.c_str());

  if(NULL != dir)
  {
    struct dirent *entry;
    if('/' != searchDir[searchDir.size() - 1])
    {
      searchDir += '/';
    }
    for(; NULL != (entry = ::readdir(dir)); )
    {
      // Skip dots
      if( '.' == entry->d_name[0] &&
          ( '\0' == entry->d_name[1] ||
            ( '.' == entry->d_name[1] &&
              '\0' == entry->d_name[2])))
      {
        // do nothing
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

  cout << "Dumping subdirectories of " << getWorkplaceDirectory() << endl;
  std::copy(dirNames.begin(), dirNames.end(), std::ostream_iterator<std::string>(cout, "\n"));

  return dirNames;
}

#if 0
std::vector<std::string> shorthand_version()
{
  unixstl::readdir_sequence dir(getWorkplaceDirectory(),    0
                                    |   unixstl::readdir_sequence::directories
#if 0
                                    |   unixstl::readdir_sequence::fullPath
#endif /* 1 */
#if 0
                                    |   unixstl::readdir_sequence::absolutePath
#endif /* 0 */
                                    );
#if 0
  std::vector<std::string>  dirNames(dir.begin(), dir.end());
#else /* ? 0 */
  std::vector<std::string>  dirNames;

  dir.empty();

  { for(unixstl::readdir_sequence::const_iterator b = dir.begin(); b != dir.end(); ++b)
  {
    dirNames.push_back(*b);
  }}
#endif /* 0 */

#ifdef UNIXSTL_READDIR_SEQUENCE_DEMONSTRATE_NONCOPYABLE_ITERATOR
  cout << "Pre-increment:" << endl;
  { for(unixstl::readdir_sequence::const_iterator b = dir.begin(); b != dir.end(); ++b)
  {
    cout << *b << endl;
  }}

  cout << "Pre-increment (stepwise):" << endl;
  { for(unixstl::readdir_sequence::const_iterator b = dir.begin(); b != dir.end(); ++b)
  {
    unixstl::readdir_sequence::const_iterator b2(b);

    cout << *b2 << endl;
  }}

#if 0
  cout << "Post-increment:" << endl;
  { for(unixstl::readdir_sequence::const_iterator b = dir.begin(); b != dir.end(); b++)
  {
    cout << *b << endl;
  }}
#endif /* 0 */
#endif /* UNIXSTL_READDIR_SEQUENCE_DEMONSTRATE_NONCOPYABLE_ITERATOR */

  cout << "Dumping subdirectories of " << getWorkplaceDirectory() << endl;
  std::copy(dirNames.begin(), dirNames.end(), std::ostream_iterator<std::string>(cout, "\n"));

#if 0
  return std::vector<std::string>(dir.begin(), dir.end());
#else /* ? 0 */
  return dirNames;
#endif /* 0 */
}
#endif /* 0 */

void dumb_version()
{
	using unixstl::readdir_sequence;

	readdir_sequence  rds(".", readdir_sequence::files | readdir_sequence::fullPath | readdir_sequence::absolutePath);

#if 0
	std::copy(rds.begin(), rds.end()
		    , std::ostream_iterator<char const*>(cout, "\n"));
#else /* ? 0 */
#if 0
	readdir_sequence::const_iterator	b	=	rds.begin();
	readdir_sequence::const_iterator	e	=	rds.end();

	for(; b != e; ++b)
	{
		cout << *b << endl;
	}
#else /* ? 0 */
#if 1
	rds.empty();

#if 1
	for(readdir_sequence::const_iterator b(rds.begin()); b != rds.end(); ++b)
	{
		cout << *b << endl;
	}
#endif /* 0 */
#else /* ? 0 */
	for(readdir_sequence::const_iterator b = rds.begin(); b != rds.end(); b++)
	{
		cout << *b << endl;
	}
#endif /* 0 */
#endif /* 0 */
#endif /* 0 */
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
		dumb_version();
		return 0;

		longhand_version();
#if 0
		shorthand_version();
#endif /* 0 */
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
		cout << "readdir_sequence_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
