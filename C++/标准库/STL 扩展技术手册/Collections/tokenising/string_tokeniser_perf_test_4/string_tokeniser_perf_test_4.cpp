/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_tokeniser_perf_test_4.cpp
 *
 * Purpose:     Implementation file for the string_tokeniser_perf_test_4 project.
 *
 * Created:     29th January 2006
 * Updated:     29th January 2006
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
 *              This source code is placed into the public domain 2006
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

#include <stlsoft/stlsoft.h>
#include <stlsoft/frequency_map.hpp>
#include <stlsoft/string_tokeniser.hpp>

#include <platform/performance_counter.hpp>

#include <boost/tokenizer.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#endif /* 0 */

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#else /* ? __WATCOMC__ */
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void usage(int bExit, char const *reason, int iInvalidArg, int argc, char **argv);

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
    int                 iRet        =   EXIT_SUCCESS;
    int                 bVerbose    =   true;

    performance_counter counter;

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

	generate a set of huge strings, a la Path, and tokenise compute-bound.


    return iRet;
}

int main(int argc, char *argv[])
{
    int             iRet;

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
        puts("string_tokeniser_perf_test_4: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


        iRet = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        iRet = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "Unhandled unknown error" << endl;

        iRet = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */

static void usage(int bExit, char const *reason, int iInvalidArg, int argc, char **argv)
{

    cerr << endl;
    cerr << "  string_tokeniser_perf_test_4" << endl << endl;
    cerr << endl;

    if(NULL != reason)
    {
        cerr << "  Error: " << reason << endl;
        cerr << endl;
    }

    if(0 < iInvalidArg)
    {
        cerr << "  First invalid argument #" << iInvalidArg << ": " << argv[iInvalidArg] << endl;
        cerr << "  Arguments were (first bad marked *):" << endl << endl;
        { for(int i = 1; i < argc; ++i)
        {
            cerr << "  " << ((i == iInvalidArg) ? "* " : "  ") << argv[i] << endl;
        }}
        cerr << "" << endl;
    }

#if 0
    cerr << "  string_tokeniser_perf_test_4" << endl << endl;
    cerr << "  USAGE: string_tokeniser_perf_test_4 [{-w | -p<root-paths> | -h}] [-u] [-d] [{-v | -s}] <search-spec>" << endl;
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
