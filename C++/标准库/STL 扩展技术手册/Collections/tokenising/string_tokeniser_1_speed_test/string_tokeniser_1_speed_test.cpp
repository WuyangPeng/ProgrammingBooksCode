/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_tokeniser_1_speed_test.cpp
 *
 * Purpose:     Implementation file for the string_tokeniser_1_speed_test project.
 *
 * Created:     18th February 2006
 * Updated:     23rd February 2006
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
#include <stlsoft/integer_to_string.hpp>
#include <stlsoft/simple_string.hpp>
#include <stlsoft/string_tokeniser.hpp>

#include <platformstl/platformstl.h>
#include <platformstl/performance_counter.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl/unixstl.h>

unixstl_ns_using(performance_counter)

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl/winstl.h>
# include <winstl/exceptions.hpp>

winstl_ns_using(performance_counter)

#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


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

#include "comparators.hpp"

static void usage(int bExit, char const *reason, int iInvalidArg, int argc, char **argv);
extern "C" void time_current(size_t nRepeats, Results &results);
extern "C" void time_ptr_only(size_t nRepeats, Results &results);
extern "C" void time_current_1_9(size_t nRepeats, Results &results);
extern "C" void time_strtok(size_t nRepeats, Results &results);
extern "C" void time_strtok_r(size_t nRepeats, Results &results);
extern "C" void time_sstream(size_t nRepeats, Results &results);
extern "C" void time_find_next_token(size_t nRepeats, Results &results);
extern "C" void time_boost(size_t nRepeats, Results &results);
extern "C" void time_current_1_9_s_v(size_t nRepeats, Results &results);
extern "C" void time_current_1_9_v_s(size_t nRepeats, Results &results);
extern "C" void time_current_1_9_v_v(size_t nRepeats, Results &results);

static void dump_res(char const *label, Results const &results);

void (*s_pfnConsume)(char const *, size_t)	=	NULL;

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
    int		iRet        =   EXIT_SUCCESS;
    int		bVerbose    =   true;
	size_t	REPEATS		=	0;

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
#if 0
            /* other arguments */
            usage(1, "Invalid argument(s) specified", i, argc, argv);
#else /* ? 0 */
			REPEATS	=	atoi(arg);
#endif /* 0 */
        }
    }}

	HINSTANCE	hinst	=	::LoadLibrary("unoptimisable_consumer.dll");

	if(NULL == hinst)
	{
		throw winstl::windows_exception("Could not load library \"unoptimisable_consumer.dll\"", ::GetLastError());
	}

	((FARPROC&)s_pfnConsume)	=	::GetProcAddress(hinst, "consume_string");

	if(NULL == s_pfnConsume)
	{
		throw winstl::windows_exception("Could not locate procedure \"consume_string\"", ::GetLastError());
	}


	if(0 == REPEATS)
	{
#ifdef _DEBUG
		REPEATS = 1;
#else /* ? _DEBUG */
		REPEATS = 100000;
#endif /* _DEBUG */
	}

	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	cout << "v1 speed test: " << STLSOFT_COMPILER_VERSION_STRING << endl;

	Results		results_string_tokeniser;
	Results		results_string_tokeniser_ptr;
	Results		results_string_tokeniser_1_9;
	Results		results_strtok;
	Results		results_strtok_r;
	Results		results_sstream;
	Results		results_find_next_token;
	Results		results_boost;
	Results		results_string_tokeniser_1_9_s_v;
	Results		results_string_tokeniser_1_9_v_s;
	Results		results_string_tokeniser_1_9_v_v;

    time_current(REPEATS,           results_string_tokeniser);
    time_ptr_only(REPEATS,          results_string_tokeniser_ptr);
    time_current_1_9(REPEATS,       results_string_tokeniser_1_9);
    time_strtok(REPEATS,            results_strtok);
    time_strtok_r(REPEATS,          results_strtok_r);
	time_sstream(REPEATS,           results_sstream);
    time_find_next_token(REPEATS,   results_find_next_token);
    time_boost(REPEATS,             results_boost);
    time_current_1_9_s_v(REPEATS,   results_string_tokeniser_1_9_s_v);
    time_current_1_9_v_s(REPEATS,   results_string_tokeniser_1_9_v_s);
    time_current_1_9_v_v(REPEATS,   results_string_tokeniser_1_9_v_v);

	dump_res("string_tokeniser, v1", results_string_tokeniser);
	dump_res("string_tokeniser, v1 (ptr)", results_string_tokeniser_ptr);
	dump_res("string_tokeniser, v2", results_string_tokeniser_1_9);
	dump_res("strtok()", results_strtok);
	dump_res("strtok_r()", results_strtok_r);
	dump_res("std::stringstream", results_sstream);
	dump_res("stlsoft::find_next_token()", results_find_next_token);
	dump_res("boost::tokenizer", results_boost);
	dump_res("string_tokeniser, v2 (S, V)", results_string_tokeniser_1_9_s_v);
	dump_res("string_tokeniser, v2 (V, S)", results_string_tokeniser_1_9_v_s);
	dump_res("string_tokeniser, v2 (V, V)", results_string_tokeniser_1_9_v_v);

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
        puts("string_tokeniser_1_speed_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
    cerr << "  string_tokeniser_1_speed_test" << endl << endl;
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
    cerr << "  string_tokeniser_1_speed_test" << endl << endl;
    cerr << "  USAGE: string_tokeniser_1_speed_test [{-w | -p<root-paths> | -h}] [-u] [-d] [{-v | -s}] <search-spec>" << endl;
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

extern "C" void create_test_strings(stlsoft::simple_string	&str1
								,	stlsoft::simple_string	&str2
								,	stlsoft::simple_string	&str3
								,	stlsoft::simple_string	&str4
								,	stlsoft::simple_string	&str5)
{
	const size_t	BIG_FACTOR	=	10/* 00 *//* 000 */;

	str1	=	"abc;def;;;";
	str2	=	";abc;def;;ghi;;;;;;jkl;mno;pqr;;;";

	{ for(size_t i = 0; i < BIG_FACTOR; ++i)
	{
		str3 += str2;
	}}

	str4	=	"\r\nabc\r\ndef\r\n\r\nghi\r\n\r\n\r\n\r\n\r\n\r\njkl\r\nmno\r\npqr\r\n\r\n\r\n";

	{ for(size_t i = 0; i < BIG_FACTOR; ++i)
	{
		str5 += str4;
	}}
}

static char const *get_result(char *sz, size_t cb, unsigned long v)
{
	if(v == ~0)
	{
		return "";
	}
	else
	{
		return stlsoft::integer_to_string(sz, cb, (unsigned int)v);
	}
}

static void dump_res(char const *label, Results const &results)
{
	char	sz1[21];
	char	sz2[21];
	char	sz3[21];
	char	sz4[21];
	char	sz5[21];
	char	sz6[21];
	char	sz7[21];
	char	sz8[21];
	char	sz9[21];

	::fprintf(	stderr
			,	"%s:\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n"
			,	label
			,	get_result(sz1, STLSOFT_NUM_ELEMENTS(sz1), results.t1)
			,	get_result(sz2, STLSOFT_NUM_ELEMENTS(sz2), results.t2)
			,	get_result(sz3, STLSOFT_NUM_ELEMENTS(sz3), results.t3)
			,	get_result(sz4, STLSOFT_NUM_ELEMENTS(sz4), results.t4)
			,	get_result(sz5, STLSOFT_NUM_ELEMENTS(sz5), results.t5)
			,	get_result(sz6, STLSOFT_NUM_ELEMENTS(sz6), results.t6)
			,	get_result(sz7, STLSOFT_NUM_ELEMENTS(sz7), results.t7)
			,	get_result(sz8, STLSOFT_NUM_ELEMENTS(sz8), results.t8)
			,	get_result(sz9, STLSOFT_NUM_ELEMENTS(sz9), results.t9));
}

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" void consume(char const *s, size_t len)
{
	s_pfnConsume(s, len);
}

/* ////////////////////////////////////////////////////////////////////////// */
