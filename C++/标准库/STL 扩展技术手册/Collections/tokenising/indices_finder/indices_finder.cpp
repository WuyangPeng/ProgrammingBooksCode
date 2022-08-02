/* /////////////////////////////////////////////////////////////////////////////
 * File:        indices_finder.cpp
 *
 * Purpose:     Implementation file for the indices_finder project.
 *
 * Created:     23rd February 2006
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
#include <stlsoft/string_tokeniser_2.hpp>
#include <stlsoft/string_view.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>

#include <platformstl/platformstl.h>
#include <platformstl/memory_mapped_file.hpp>
#include <platformstl/performance_counter.hpp>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl/unixstl.h>

# include <unixstl/performance_counter.hpp>

unixstl_ns_using(performance_counter)

#elif defined(WIN32) || \
      defined(_WIN32)

#include <winstl/winstl.h>

#include <winstl/performance_counter.hpp>

winstl_ns_using(performance_counter)

#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

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

namespace
{
	struct char_pair_delimiter
	{
	public:
		char_pair_delimiter(char leading, char trailing)
			: m_leading(leading)
			, m_trailing(trailing)
		{}

	public:
		const char	m_leading;
		const char	m_trailing;
	};

	struct char_pair_comparator
	{
		typedef char_pair_delimiter	delimiter_type;

		static size_t length(delimiter_type const &delimiter)
		{
			return 1;
		}

		template <typename const_iterator>
		static bool test_start_token_advance(const_iterator &it, const_iterator end, delimiter_type const &delimiter)
		{
			STLSOFT_ASSERT(it != end);

			if(delimiter.m_leading == *it)
			{
				++it;

				return true;
			}

			return false;
		}

		template <typename const_iterator>
		static bool test_end_token_advance(const_iterator &it, const_iterator end, delimiter_type const &delimiter)
		{
			if( end != it &&
				delimiter.m_trailing == *it)
			{
				++it;

				return true;
			}

			return false;
		}

		template <typename const_iterator>
		static const_iterator nonskip_move_to_start(const_iterator it, const_iterator end, delimiter_type const &delimiter)
		{
			STLSOFT_ASSERT(it != end);

			if(delimiter.m_leading == *it)
			{
				++it;
			}

			return it;
		}

		template <typename const_iterator>
		static bool test_end_token(const_iterator it, const_iterator end, delimiter_type const &delimiter)
		{
			STLSOFT_ASSERT(it != end);

			return delimiter.m_trailing == *it;
		}

		template <typename const_iterator>
		static const_iterator find_next_start(const_iterator it, const_iterator end, delimiter_type const &delimiter)
		{
			STLSOFT_ASSERT(test_end_token(it, end, delimiter));

            STLSOFT_ASSERT(it != end);

			if(delimiter.m_trailing == *it)
			{
				++it;
			}

			return it;
		}
	};

	struct char_pair
		: public char_pair_delimiter
		, public char_pair_comparator
	{
	public:
		char_pair(char_pair_delimiter const &rhs)
			: char_pair_delimiter(rhs)
		{}
	};
}

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
	recls::stl::search_sequence					files(".", "*.h|*.hpp|*.cpp", recls::RECURSIVE);
	recls::stl::search_sequence::const_iterator	b;

	for(b = files.begin(); b != files.end(); ++b)
	{
		platformstl::memory_mapped_file		mmf(*b);
		stlsoft::string_view				contents(static_cast<char const*>(mmf.memory()), mmf.size());

		typedef stlsoft::string_tokeniser<	stlsoft::string_view
										,	char_pair
										,	stlsoft::skip_blank_tokens<true>
										,	stlsoft::string_view
										,	stlsoft::string_tokeniser_type_traits<stlsoft::string_view, stlsoft::string_view>
										,	char_pair
										>			tokeniser_t;

		tokeniser_t	tokens(contents, char_pair_delimiter('[', ']'));

		cout << "File: " << *b << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<stlsoft::string_view>(cout, "\t[", "]\n"));
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
        cout << "indices_finder: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
    cerr << "  indices_finder" << endl << endl;
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
    cerr << "  indices_finder" << endl << endl;
    cerr << "  USAGE: indices_finder [{-w | -p<root-paths> | -h}] [-u] [-d] [{-v | -s}] <search-spec>" << endl;
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
