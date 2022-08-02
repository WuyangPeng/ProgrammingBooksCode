/* /////////////////////////////////////////////////////////////////////////////
 * File:        cleardirectory_test.cpp
 *
 * Purpose:     Implementation file for the cleardirectory_test project.
 *
 * Created:     27th October 2006
 * Updated:     27th October 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */


/* Pantheios Header Files */
#include <pantheios/pantheios.hpp>
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe.simple.h>
#include <pantheios/implicit_link/be.Win32Console.h>

/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

#include <winstl/error/error_desc.hpp>
#include <winstl/filesystem/findfile_sequence.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C Header Files */
#include <shlobj.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Functions
 */

void ClearDirectory(LPCTSTR lpszDir, LPCTSTR lpszFilePatterns)
{
  typedef winstl::basic_findfile_sequence<TCHAR>  ffs_t;

  pantheios::log_DEBUG( _T("ClearDirectory(\""), lpszDir
                      , _T("\", \""), lpszFilePatterns, _T("\")"));
  ffs_t files(lpszDir, lpszFilePatterns, ';', ffs_t::files);
  { for(ffs_t::const_iterator b = files.begin(); b != files.end(); ++b)
  {
    if(::DeleteFile(stlsoft::c_str_ptr(*b)))
    {
      pantheios::log_INFORMATIONAL(_T("Successfully deleted \""), *b, _T("\""));
      ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, stlsoft::c_str_ptr(*b), NULL); 
    }
    else
    {
      pantheios::log_ERROR(_T("Unable to delete \""), *b
                            , _T("\": "), winstl::error_desc(::GetLastError()));
    }
  }}

  ffs_t directories(lpszDir, _T("*.*"), ffs_t::directories | ffs_t::skipReparseDirs);
  { for(ffs_t::const_iterator b = directories.begin(); b != directories.end(); ++b)
  {
    ClearDirectory(stlsoft::c_str_ptr(*b), lpszFilePatterns);
  }}
}

  void ClearDirectory_recls(LPCTSTR lpszDir, LPCTSTR lpszFilePatterns)
  {
    typedef recls::stl::search_sequence  ffs_t;

    ffs_t files(lpszDir, lpszFilePatterns, recls::FILES);
    { for(ffs_t::const_iterator b = files.begin(); b != files.end(); ++b)
    {
      if(::DeleteFile(stlsoft::c_str_ptr(*b)))
      {
        ::SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, stlsoft::c_str_ptr(*b), NULL); 
      }
    }}
  }

/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"cleardirectory_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void usage(int bExit, char const *reason, int invalidArg, int argc, char **argv);

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
    int                 iRet        =   EXIT_SUCCESS;
    int                 bVerbose    =   true;

    { for(int i = 1; i < argc; ++i)
    {
        char const  *const  arg =   argv[i];

        if(arg[0] == '-')
        {
            if(arg[1] == '-')
            {
                /* -- arguments */
                usage(1, "Invalid argument(s) specified", i, argc, argv);
            }
            else
            {
                /* - arguments */
                switch(arg[1])
                {
                    case    '?':
                        usage(1, NULL, -1, argc, argv);
                        break;
                    case    's':
                        bVerbose    =   false;
                        break;
                    case    'v':
                        bVerbose    =   true;
                        break;
                    default:
                        usage(1, "Invalid argument(s) specified", i, argc, argv);
                        break;
                }
            }
        }
        else
        {
            /* other arguments */
            usage(1, "Invalid argument(s) specified", i, argc, argv);
        }
    }}

    /* . */
	ClearDirectory("H:\\temp", "H:\\temp\\aw\\aw\\*\\impllink.obj");

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
        cout << "cleardirectory_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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

/* ////////////////////////////////////////////////////////////////////////// */

static void usage(int bExit, char const *reason, int invalidArg, int argc, char **argv)
{

    cerr << endl;
    cerr << "  cleardirectory_test" << endl << endl;
    cerr << endl;

    if(NULL != reason)
    {
        cerr << "  Error: " << reason << endl;
        cerr << endl;
    }

    if(0 < invalidArg)
    {
        cerr << "  First invalid argument #" << invalidArg << ": " << argv[invalidArg] << endl;
        cerr << "  Arguments were (first bad marked *):" << endl << endl;
        { for(int i = 1; i < argc; ++i)
        {
            cerr << "  " << ((i == invalidArg) ? "* " : "  ") << argv[i] << endl;
        }}
        cerr << "" << endl;
    }

#if 0
    cerr << "  cleardirectory_test" << endl << endl;
    cerr << "  USAGE: cleardirectory_test [{-w | -p<root-paths> | -h}] [-u] [-d] [{-v | -s}] <search-spec>" << endl;
    cerr << "    where:" << endl << endl;
    cerr << "    -w             - searches from the current working directory. The default" << endl;
    cerr << "    -p<root-paths> - searches from the given root path(s), separated by \';\'," << endl;
    cerr << "                     eg." << endl;
    cerr << "                       -p\"c:\\windows;x:\\bin\"" << endl;
    cerr << "    -r             - deletes readonly files" << endl;
    cerr << "    -h             - searches from the roots of all drives on the system" << endl;
    cerr << "    -d             - displays the path(s) searched" << endl;
    cerr << "    -u             - do not act recursively" << endl;
    cerr << "    -v             - verbose output. Prints time, attributes, size and path. (default)" << endl;
    cerr << "    -s             - succinct output. Prints path only" << endl;
    cerr << "    <search-spec>  - one or more file search specifications, separated by \';\'," << endl;
    cerr << "                     eg." << endl;
    cerr << "                       \"*.exe\"" << endl;
    cerr << "                       \"myfile.ext\"" << endl;
    cerr << "                       \"*.exe;*.dll\"" << endl;
    cerr << "                       \"*.xl?;report.*\"" << endl;
    cerr << endl;
    cerr << "  Contact " << _nameSynesisSoftware << endl;
    cerr << "    at \"" << _wwwSynesisSoftware_SystemTools << "\"," << endl;
    cerr << "    or, via email, at \"" << _emailSynesisSoftware_SystemTools << "\"" << endl;
    cerr << endl;
#endif /* 0 */

    if(bExit)
    {
        exit(EXIT_FAILURE);
    }
}

/* ////////////////////////////////////////////////////////////////////////// */
