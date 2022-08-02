/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_tokeniser_v1_test.cpp
 *
 * Purpose:     Implementation file for the string_tokeniser_v1_test project.
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
#include <stlsoft/ctype_traits.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>
#include <stlsoft/simple_string.hpp>
#include <stlsoft/string_tokeniser.hpp>
#include <stlsoft/string_view.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#if 0
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

static void tokenise_with_single_character_delimiter();
static void tokenise_with_range_of_character_delimiters();
static void tokenise_with_ws_delimiters();
static void tokenise_with_C_identifiers();
static void tokenise_with_single_string_delimiter();
static void tokenise_with_character_delimiter_pair();
static void tokenise_with_string_delimiter_pair();

/* /////////////////////////////////////////////////////////////////////////////
 * Comparators
 */

template <typename S>
struct range_comparator
{
public:
    typedef S										delimiter_type;
	typedef ss_typename_type_k S::const_iterator	const_iterator;

private:

public:
	static size_t length(delimiter_type const &)
	{
		return 1;
	}

	static bool not_equal(delimiter_type const &delim, const_iterator it)
	{
		return delim.end() == std::find(delim.begin(), delim.end(), *it);
	}
};

template<	typename S
		,	typename C
		>
struct ws_comparator
{
public:
    typedef C										delimiter_type;
	typedef ss_typename_type_k S::const_iterator	const_iterator;

private:
	static bool is_wspace_(char ch)
	{
#if 0
		return NULL != ::strpbrk(" \t\r\n\b\v", ch);
#else /* ? 0 */
		return stlsoft::ctype_traits<char>::is_space(ch);
#endif /* 0 */
	}
	static bool is_wspace_(wchar_t ch)
	{
#if 0
		return NULL != ::wcspbrk(" \t\r\n\b\v", ch);
#else /* ? 0 */
		return stlsoft::ctype_traits<wchar_t>::is_space(ch);
#endif /* 0 */
	}

public:
	static size_t length(delimiter_type const &)
	{
		return 1;
	}

	static bool not_equal(delimiter_type const &, const_iterator it)
	{
		return !is_wspace_(*it);
	}
};

template<	typename S
		,	typename C
		>
struct C_identifier_comparator
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
		return '_' == *it || ::isalnum(*it);
	}
};

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	tokenise_with_single_character_delimiter();
	tokenise_with_range_of_character_delimiters();
	tokenise_with_ws_delimiters();
	tokenise_with_C_identifiers();
	tokenise_with_single_string_delimiter();
	tokenise_with_character_delimiter_pair();
	tokenise_with_string_delimiter_pair();

    return EXIT_SUCCESS;
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
        cout << "string_tokeniser_v1_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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

static void tokenise_with_single_character_delimiter()
{
	cout << endl << "Single character delimiter" << endl;

	static const char	str[]	=	";;;abc;;def;;ghi;jkl;";

	{ // With std::string
		typedef std::string									string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	char
										>					tokeniser_t;

		tokeniser_t			tokens(str, ';');

		cout << "  Tokenising \"" << str << "\" with '" << ';' << "', string_t = std::string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::simple_string
		typedef stlsoft::simple_string						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	char
										>					tokeniser_t;

		tokeniser_t			tokens(str, ';');

		cout << "  Tokenising \"" << str << "\" with '" << ';' << "', string_t = stlsoft::simple_string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::string_view
		typedef stlsoft::string_view						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	char
										>					tokeniser_t;

		tokeniser_t			tokens(str, ';');

		cout << "  Tokenising \"" << str << "\" with '" << ';' << "', string_t = stlsoft::string_view:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	cout << endl;
}

static void tokenise_with_range_of_character_delimiters()
{
	cout << endl << "Range of character delimiters" << endl;

	static const char	str[]	=	";:|abc^&def*()ghi$jkl%";

	{ // With std::string
		typedef std::string									string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	range_comparator<string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "<>?:;{}[]|=+!@#$%^&*()");

		cout << "  Tokenising \"" << str << "\" with \"" << "<>?:;{}[]|=+!@#$%^&*()" << "\", string_t = std::string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::simple_string
		typedef stlsoft::simple_string						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	range_comparator<string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "<>?:;{}[]|=+!@#$%^&*()");

		cout << "  Tokenising \"" << str << "\" with \"" << "<>?:;{}[]|=+!@#$%^&*()" << "\", string_t = stlsoft::simple_string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::string_view
		typedef stlsoft::string_view						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	range_comparator<string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "<>?:;{}[]|=+!@#$%^&*()");

		cout << "  Tokenising \"" << str << "\" with \"" << "<>?:;{}[]|=+!@#$%^&*()" << "\", string_t = stlsoft::string_view:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	cout << endl;
}

static void tokenise_with_ws_delimiters()
{
	cout << endl << "Whitespace delimiters" << endl;

	static const char	str[]	=	" \r\nabc\r\ndef \r\nghi\njkl\t";

	{ // With std::string
		typedef std::string									string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	char
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	ws_comparator<string_t, char>
										>					tokeniser_t;

		tokeniser_t			tokens(str, 0);

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "whitespace" << "\", string_t = std::string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::simple_string
		typedef stlsoft::simple_string						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	ws_comparator<string_t, string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "");

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "whitespace" << "\", string_t = stlsoft::simple_string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::string_view
		typedef stlsoft::string_view						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	ws_comparator<string_t, string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "");

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "whitespace" << "\", string_t = stlsoft::string_view:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	cout << endl;
}

static void tokenise_with_C_identifiers()
{
	cout << endl << "C-identifiers delimiters" << endl;

	static const char	str[]	=	" \r\nident0-ident1\r\nident2 \r\nident3\nident4";

	{ // With std::string
		typedef std::string									string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	char
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	C_identifier_comparator<string_t, char>
										>					tokeniser_t;

		tokeniser_t			tokens(str, 0);

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "C-identifier" << "\", string_t = std::string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::simple_string
		typedef stlsoft::simple_string						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	C_identifier_comparator<string_t, string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "");

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "C-identifier" << "\", string_t = stlsoft::simple_string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::string_view
		typedef stlsoft::string_view						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										,	stlsoft::skip_blank_tokens<true>
										,	string_t
										,	stlsoft::string_tokeniser_type_traits<string_t, string_t>
										,	C_identifier_comparator<string_t, string_t>
										>					tokeniser_t;

		tokeniser_t			tokens(str, "");

		cout << "  Tokenising \"" << " \\r\\nabc\\r\\ndef \\r\\nghi\\njkl\\t" << "\" with \"" << "C-identifier" << "\", string_t = stlsoft::string_view:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	cout << endl;
}

static void tokenise_with_single_string_delimiter()
{
	cout << endl << "Single string delimiter" << endl;

	static const char	str[]	=	"%%%%%%abc%%%%def%%%%ghi%%jkl%%";

	{ // With std::string
		typedef std::string									string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										>					tokeniser_t;

		tokeniser_t			tokens(str, "%%");

		cout << "  Tokenising \"" << str << "\" with \"" << "%%" << "\", string_t = std::string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::simple_string
		typedef stlsoft::simple_string						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										>					tokeniser_t;

		tokeniser_t			tokens(str, "%%");

		cout << "  Tokenising \"" << str << "\" with \"" << "%%" << "\", string_t = stlsoft::simple_string:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	{ // With stlsoft::string_view
		typedef stlsoft::string_view						string_t;
		typedef stlsoft::string_tokeniser<	string_t
										,	string_t
										>					tokeniser_t;

		tokeniser_t			tokens(str, "%%");

		cout << "  Tokenising \"" << str << "\" with \"" << "%%" << "\", string_t = stlsoft::string_view:" << endl;
		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<string_t>(std::cout, "\t[", "]\n"));
	}

	cout << endl;
}

static void tokenise_with_character_delimiter_pair()
{
}

static void tokenise_with_string_delimiter_pair()
{
}

/* ////////////////////////////////////////////////////////////////////////// */
