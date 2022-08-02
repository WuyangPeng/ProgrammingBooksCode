/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_tokeniser_perf_test_1.cpp
 *
 * Purpose:     Implementation file for the string_tokeniser_perf_test_1 project.
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
#include <stlsoft/string_tokeniser.hpp>
#include <stlsoft/string_view.hpp>

#include <platformstl/platformstl.hpp>
#include <platformstl/memory_mapped_file.hpp>
#include <platformstl/performance_counter.hpp>

#include <boost/tokenizer.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
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

static void usage(int bExit, char const *reason, int invalidArg, int argc, char **argv);

/* /////////////////////////////////////////////////////////////////////////////
 * Comparators
 */

template<	typename S
		,	typename C
		>
struct ws_comparator
{
public:
    typedef C										delimiter_type;
	typedef ss_typename_type_k S::const_iterator	const_iterator;

public:
	static size_t length(delimiter_type const &)
	{
		return 1;
	}

	static bool not_equal(delimiter_type const &, const_iterator it)
	{
		return !::isspace(*it);
	}
};

/* ////////////////////////////////////////////////////////////////////////// */

template <typename S>
S &operator <<(S &stm, platformstl::performance_counter::interval_type interval)
{
	return stm << static_cast<long>(interval);
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char *argv[])
{
	using platformstl::performance_counter;

    int                 iRet        =   EXIT_SUCCESS;
    int                 bVerbose    =   true;
    performance_counter counter;
	char const			*fileName	=	NULL;
	char const			*repeats	=	NULL;
	int					REPEATS		=	1000;

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
			if(NULL == fileName)
			{
				fileName = arg;
			}
			else if(NULL == repeats)
			{
				repeats = arg;
			}
			else
			{
	            /* other arguments */
		        usage(1, "Invalid argument(s) specified", i, argc, argv);
			}
        }
    }}

	if(NULL != repeats)
	{
		REPEATS = ::atoi(repeats);
	}

    if(NULL == fileName)
	{
        usage(1, "No file specified", -1, argc, argv);
	}
	else
	{
		platformstl::memory_mapped_file		file(fileName);
		performance_counter::interval_type	t_strtok		=	0;
		performance_counter::interval_type	t_fnt			=	0;
		performance_counter::interval_type	t_boost_tok		=	0;
		performance_counter::interval_type	t_stlsoft_tok	=	0;
		performance_counter::interval_type	t_stlsoft_tok_v	=	0;
		size_t								n_strtok		=	0;
		size_t								n_fnt			=	0;
		size_t								n_boost_tok		=	0;
		size_t								n_stlsoft_tok	=	0;
		size_t								n_stlsoft_tok_v	=	0;

		{ for(int WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
		{
			counter.start();
			{ for(size_t i = 0; i < REPEATS; ++i)
			{
				std::vector<char>	copy(static_cast<char const*>(file.memory()), static_cast<char const*>(file.memory()) + 1 + static_cast<size_t>(file.size()));

				copy.back() = '\0';

				char	*token	=	::strtok(&copy[0], " \r\n\t\v\n");
				for(n_strtok = 0; NULL != token; ++n_strtok)
				{
					token = ::strtok(NULL, " \r\n\t\v\n");
				}
			}}
			counter.stop();
			t_strtok	=	counter.get_milliseconds();
		}}

#if 0
		{ for(int WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
		{
			counter.start();
			{ for(size_t i = 0; i < REPEATS; ++i)
			{
				char const	*p0		=	static_cast<char const*>(file.memory());
				char const	*p1		=	p0;
				char const	*end	=	p0 + static_cast<size_t>(file.size());

				for(n_strtok = 0; stlsoft::find_next_token(; ++n_strtok)
				{
					token = ::strtok(NULL, " \r\n\t\v\n");
				}
			}}
			counter.stop();
			t_strtok	=	counter.get_milliseconds();
		}}
#endif /* 0 */

		{ for(int WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
		{
			counter.start();
			{ for(size_t i = 0; i < REPEATS; ++i)
			{
				typedef std::string								string_t;
				typedef boost::tokenizer<	boost::char_separator<char>
										,	string_t::const_iterator
										,	string_t
										>						tokeniser_t;

				char const	*begin	=	static_cast<char const*>(file.memory());
				char const	*end	=	begin + static_cast<size_t>(file.size());

//				boost::char_separator<char>	sep(";");
				tokeniser_t					tokens(begin, end);

				n_boost_tok	=	std::distance(tokens.begin(), tokens.end());
			}}
			counter.stop();
			t_boost_tok	=	counter.get_milliseconds();
		}}

		{ for(int WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
		{
			counter.start();
			{ for(size_t i = 0; i < REPEATS; ++i)
			{
				typedef std::string								string_t;
				typedef stlsoft::string_tokeniser<	string_t
												,	char
												,	stlsoft::skip_blank_tokens<true>
												,	string_t
												,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
												,	ws_comparator<string_t, char>
												>				tokeniser_t;

				tokeniser_t		tokens(static_cast<char const*>(file.memory()), static_cast<size_t>(file.size()), 0);

				n_stlsoft_tok	=	std::distance(tokens.begin(), tokens.end());
			}}
			counter.stop();
			t_stlsoft_tok	=	counter.get_milliseconds();
		}}

		{ for(int WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
		{
			counter.start();
			{ for(size_t i = 0; i < REPEATS; ++i)
			{
				typedef stlsoft::string_view					string_t;
				typedef stlsoft::string_tokeniser<	string_t
												,	char
												,	stlsoft::skip_blank_tokens<true>
												,	string_t
												,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
												,	ws_comparator<string_t, char>
												>				tokeniser_t;

				tokeniser_t		tokens(static_cast<char const*>(file.memory()), static_cast<size_t>(file.size()), 0);

				n_stlsoft_tok_v	=	std::distance(tokens.begin(), tokens.end());
			}}
			counter.stop();
			t_stlsoft_tok_v	=	counter.get_milliseconds();
		}}

		cout << "Results:" << endl;
		cout << "strtok():                                   \t" << t_strtok << "\t" << n_strtok << endl;
		cout << "find_next_token:                            \t" << t_fnt << "\t" << n_fnt << endl;
		cout << "boost::tokeniser:                           \t" << t_boost_tok << "\t" << n_boost_tok << endl;
		cout << "stlsoft::string_tokeniser (w ws_comparator):\t" << t_stlsoft_tok << "\t" << n_stlsoft_tok << endl;
		cout << "stlsoft::string_tokeniser (w ws_c & str vw):\t" << t_stlsoft_tok_v << "\t" << n_stlsoft_tok_v << endl;
	}

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
        cout << "string_tokeniser_perf_test_1: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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

static void usage(int bExit, char const *reason, int invalidArg, int argc, char **argv)
{
    FILE    *stm    =   (NULL == reason) ? stdout : stderr;

    ::fprintf(stm, "\n");

    if(NULL != reason)
    {
        ::fprintf(stm, "  Error: %s\n", reason);
        ::fprintf(stm, "\n");
    }

    if(0 < invalidArg)
    {
        ::fprintf(stm, "  First invalid argument #%d: %s\n", invalidArg, argv[invalidArg]);
        ::fprintf(stm, "  Arguments were (first bad marked *):\n\n");
        for(int i = 1; i < argc; ++i)
        {
            ::fprintf(stm, "  %s%s\n", (i == invalidArg) ? "* " : "  ", argv[i]);
        }
        ::fprintf(stm, "\n");
    }


    if(bExit)
    {
        exit(EXIT_FAILURE);
    }
}

/* ////////////////////////////////////////////////////////////////////////// */
