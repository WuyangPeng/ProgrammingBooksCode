/* /////////////////////////////////////////////////////////////////////////////
 * File:        filter_iterator_motivation_test.cpp
 *
 * Purpose:     Implementation file for the filter_iterator_motivation_test project.
 *
 * Created:     3rd January 2006
 * Updated:     3rd January 2006
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
#include <stlsoft/iterators/filter_iterator.hpp>
#include <stlsoft/iterators/member_selector_iterator.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>

#include <comstl/comstl.h>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl/unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl/winstl.h>

#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


/* Open-RJ Header Files */
#include <openrj/stl/openrj.hpp>
#include <openrj/stl/field.hpp>
#include <openrj/stl/record.hpp>
#include <openrj/stl/database.hpp>

/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <string>
#include <vector>

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
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void test_istream_iterator();
static void test_int_array_in_reverse();
static void test_list_iterator();
static void test_set_iterator_and_member_selection_operator();

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	cout << endl;

	test_istream_iterator();
	test_int_array_in_reverse();
	test_set_iterator_and_member_selection_operator();
	test_list_iterator();

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int				iRet;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState	memState;
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
		cout << "filter_iterator_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl << endl;
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

template<	typename T
		,	typename I
		>
void output_first_slice_to_value(I from, I to, T sentinel, char *prefix, char *suffix)
{
	if(from != to)
	{
		I								it	=	std::find(from, to, sentinel);
		stlsoft::ostream_iterator<T>	o(cout, prefix, suffix);

		for(--it; ; )
		{
			*o++ = *it;

			if(it == from)
			{
				break;
			}
			else
			{
				--it;
			}
		}
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace
{
	struct is_vowel
		: public std::unary_function<char, bool>
	{
	public:
		bool operator ()(char ch) const
		{
			switch(ch)
			{
				case	'a':
				case	'e':
				case	'i':
				case	'o':
				case	'u':
				case	'A':
				case	'E':
				case	'I':
				case	'O':
				case	'U':
					return true;
				default:
					return false;
			}
		}
	};

} // namespace

static void test_istream_iterator()
{
	{
		std::fstream	stm("isi_test.txt", std::fstream::out);

		stm << "abcdefghijklmnopqrstuvwxyz" << endl;
	}

	{
		std::ifstream	stm("isi_test.txt");

		cout << "Contents of istream: " << endl;
		std::copy(std::istream_iterator<char>(stm), std::istream_iterator<char>(), std::ostream_iterator<char>(cout));
		cout << endl;
		cout << endl;
	}

	{
		std::ifstream	stm("isi_test.txt");

		cout << "Contents of istream, filtered for vowels: " << endl;
		std::copy(	stlsoft::filter(std::istream_iterator<char>(stm), std::istream_iterator<char>(), is_vowel())
				,	stlsoft::filter(std::istream_iterator<char>(), std::istream_iterator<char>(), is_vowel())
				,	std::ostream_iterator<char>(cout));
		cout << endl;
		cout << endl;
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

struct is_odd
	: public std::unary_function<int, bool>
{
public:
	bool operator ()(int i) const
	{
		return 1 == (i % 2);
	}
};

static void test_int_array_in_reverse()
{
	int ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

	if( stlsoft::filter(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()) != 
		stlsoft::filter(&ints[1], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()))
	{
		cout << "0th element should be == to 1st element" << endl;
	}
	if( stlsoft::filter(&ints[2], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()) != 
		stlsoft::filter(&ints[3], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()))
	{
		cout << "2nd element should be == to 3rd element" << endl;
	}

	if( stlsoft::filter(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()) == 
		stlsoft::filter(&ints[2], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd()))
	{
		cout << "0th element should be != to 2nd element" << endl;
	}

	cout << "int array in reverse:" << endl;
	output_first_slice_to_value(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), 5, "\t", "\n");
	cout << endl;

	cout << "int array in reverse, filtered for odd elements:" << endl;
	output_first_slice_to_value(stlsoft::filter(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd())
							,	stlsoft::filter(&ints[0] + STLSOFT_NUM_ELEMENTS(ints), &ints[0] + STLSOFT_NUM_ELEMENTS(ints), is_odd())
							,	5, "\t", "\n");
	cout << endl;
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace
{

	struct has_even_digits
		: public std::unary_function<std::string, bool>
	{
	public:
		bool operator ()(std::string const &s) const
		{
			return s.npos != s.find_first_of("02468");
		}
	};

} // namespace

static void test_list_iterator()
{
	typedef std::string		string_t;

	std::list<string_t>	strings;

	{ for(size_t i = 0; i < 10; ++i)
	{
		char	sz[21];

		strings.push_back(string_t("string-") + stlsoft::integer_to_string(sz, STLSOFT_NUM_ELEMENTS(sz), i));
	}}

	{
		cout << "Strings:" << endl;
		std::copy(	strings.begin(), strings.end()
				,	stlsoft::ostream_iterator<string_t>(cout, "\t", "\n"));
		cout << endl;
	}

	{
		cout << "Strings, filtered for elements containing even digits:" << endl;
		std::copy(	stlsoft::filter(strings.begin(), strings.end(), has_even_digits())
				,	stlsoft::filter(strings.end(), strings.end(), has_even_digits())
				,	stlsoft::ostream_iterator<string_t>(cout, "\t", "\n"));
		cout << endl;
	}

	{
		cout << "Strings reversed, filtered for elements containing odd digits:" << endl;
		std::copy(	stlsoft::filter(strings.rbegin(), strings.rend(), std::not1(has_even_digits()))
				,	stlsoft::filter(strings.rend(), strings.rend(), std::not1(has_even_digits()))
				,	stlsoft::ostream_iterator<string_t>(cout, "\t", "\n"));
		cout << endl;
	}

	{
		cout << "Strings, range selected, processed backwards (--):" << endl;
		output_first_slice_to_value<string_t>(strings.begin(), strings.end(), "string-5", "\t", "\n");
		cout << endl;
	}

	{
		cout << "Strings, reversed, range selected, processed backwards (--):" << endl;
		output_first_slice_to_value<string_t>(strings.rbegin(), strings.rend(), "string-5", "\t", "\n");
		cout << endl;
	}

#if 1
	{
		cout << "Strings, filtered for elements containing odd digits, range selected, processed backwards (--):" << endl;
		output_first_slice_to_value<string_t>(	stlsoft::filter(strings.begin(), strings.end(), std::not1(has_even_digits()))
											,	stlsoft::filter(strings.end(), strings.end(), std::not1(has_even_digits()))
											,	"string-5", "\t", "\n");
		cout << endl;
	}

	{
		cout << "Strings, reversed, filtered for elements containing odd digits, range selected, processed backwards (--):" << endl;
		output_first_slice_to_value<string_t>(	stlsoft::filter(strings.rbegin(), strings.rend(), std::not1(has_even_digits()))
											,	stlsoft::filter(strings.rend(), strings.rend(), std::not1(has_even_digits()))
											,	"string-5", "\t", "\n");
		cout << endl;
	}
#endif /* 0 */
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace
{
	struct S
	{
		S(int i)
			: i(i)
		{}

		int i;
	};

	bool operator <(S const &s1, S const &s2)
	{
		return s1.i < s2.i;
	}

	template<	typename I
	//		,	typename T
			>
	void invoke_member_selection_operator(I from, I to)
	{
		for(; from != to; ++from)
		{
			cout << "\t" << from->i << endl;
		}
	}

	struct is_S_odd
		: public std::unary_function<S, bool>
	{
	public:
		bool operator ()(S const &s) const
		{
			return 1 == (s.i % 2);
		}
	};


} // anonymous namespace

static void test_set_iterator_and_member_selection_operator()
{
	std::set<S>	ss;

	{ for(size_t i = 0; i < 10; ++i)
	{
		ss.insert(S(i));
	}}

	{
		cout << "Ss:" << endl;
		std::copy(	stlsoft::member_selector(ss.begin(), &S::i)
				,	stlsoft::member_selector(ss.end(), &S::i)
				,	stlsoft::ostream_iterator<int>(cout, "\t", "\n"));
		cout << endl;
	}

	{
		cout << "Ss, ->() manually:" << endl;
		invoke_member_selection_operator(ss.begin(), ss.end());
	}

	{
		cout << "Ss, reversed, ->() manually:" << endl;
		invoke_member_selection_operator(ss.rbegin(), ss.rend());
	}

	{
		cout << "Ss, ->() manually, filtered for odd values:" << endl;
		invoke_member_selection_operator(	stlsoft::filter(ss.begin(), ss.end(), is_S_odd())
										,	stlsoft::filter(ss.end(), ss.end(), is_S_odd()));
	}

	{
		cout << "Ss, reversed, ->() manually, filtered for odd values:" << endl;
		invoke_member_selection_operator(	stlsoft::filter(ss.rbegin(), ss.rend(), is_S_odd())
										,	stlsoft::filter(ss.rend(), ss.rend(), is_S_odd()));
	}
}

/* ////////////////////////////////////////////////////////////////////////// */
