/* /////////////////////////////////////////////////////////////////////////////
 * File:        index_iterator_motivation_test.cpp
 *
 * Purpose:     Implementation file for the index_iterator_motivation_test project.
 *
 * Created:     23rd December 2005
 * Updated:     13th January 2006
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


/* recls Header Files */
#include <recls/stl/search_sequence.hpp>

/* STLSoft Header Files */
#include <stlsoft/integer_to_string.hpp>
#include <stlsoft/iterators/index_iterator.hpp>

/* WinSTL Header Files */
#include <winstl/winstl.h>
#include <winstl/file_functions.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <typeinfo>
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
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void mutable_int_list();
static void mutable_string_vector();
static void immutable_string_vector();
static void recls_test_longhand();
static void recls_test_shorthand();

/* ////////////////////////////////////////////////////////////////////////// */

#if 0

static int main_(int /* argc */, char ** /*argv*/)
{
	recls::stl::search_sequence					files(".", "*.h|*.hpp", recls::RECURSIVE);

	{ for(recls::stl::search_sequence::const_iterator b = files.begin(); b != files.end(); ++b)
	{
		recls::stl::search_sequence::value_type fe	=	*b;

		std::vector<std::string>				lines;

		winstl::readlines(fe.get_path(), lines);

		bool									bUpdated	=	false;

		{ size_t lineNum = 0;
		for(std::vector<std::string>::iterator b = lines.begin(); b != lines.end(); ++b, ++lineNum)
		{
			const std::string	line	=	*b;

			if( line == "#ifdef _STLSOFT_COMPILE_VERBOSE" &&
				std::string::npos != lines[lineNum + 1].find("pragma message(\"This file is now obsolete"))
			{
				bUpdated	=	true;
				*b			=	"#ifdef STLSOFT_CF_PRAGMA_MESSAGE_SUPPORT";
			}
		}}

		if(bUpdated)
		{
			std::ofstream	f(stlsoft::c_str_ptr(fe.get_path()));

			std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(f, "\n"));
		}
	}}

    return EXIT_SUCCESS;
}

#else /* ? 0 */

#if 0
template <typename I2, typename C>
bool inner_worker(I2 from2, I2 to2, C &lines)
{
	bool	bUpdated	=	false;

	{ for(size_t lineNum = 0; from2 != to2; ++from2, ++lineNum)
	{
		const ss_typename_type_k C::value_type	line	=	*from2;

		if( line == "#ifdef _STLSOFT_COMPILE_VERBOSE" &&
			std::string::npos != lines[lineNum + 1].find("pragma message(\"This file is now obsolete"))
		{
			bUpdated	=	true;
			*from2		=	"#ifdef STLSOFT_CF_PRAGMA_MESSAGE_SUPPORT";
		}
	}}

	return bUpdated;
}
#else /* ? 0 */
template <typename I2, typename C>
bool inner_worker(I2 from2, I2 to2, C &lines)
{
	bool	bUpdated	=	false;

	{ for(; from2 != to2; ++from2)
	{
		const ss_typename_type_k C::value_type	line	=	*from2;

		if( line == "#ifdef _STLSOFT_COMPILE_VERBOSE" &&
			std::string::npos != lines[from2.index() + 1].find("pragma message(\"This file is now obsolete"))
		{
			bUpdated	=	true;
			*from2		=	"#ifdef STLSOFT_CF_PRAGMA_MESSAGE_SUPPORT";
		}
	}}

	return bUpdated;
}
#endif /* 0 */

template <typename I>
void outer_worker(I from, I to)
{
	{ for(; from != to; ++from)
	{
		std::vector<std::string>				lines;

		winstl::readlines((*from).get_path(), lines);

#if 0
		if(inner_worker(lines.begin(), lines.end(), lines))
#else /* ? 0 */
		if(inner_worker(stlsoft::indexer(lines.begin()), stlsoft::indexer(lines.end()), lines))
#endif /* 0 */
		{
			std::ofstream	f(stlsoft::c_str_ptr((*from).get_path()));

			std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(f, "\n"));
		}
	}}
}

static void recls_test_longhand()
{
	recls::stl::search_sequence 				files(".", "*.h|*.hpp", recls::RECURSIVE);

	outer_worker(files.begin(), files.end());
}

////////////////////////////////////////////////////////////////////////////////

template <typename I>
void mutate_indexes(I from, I to)
{
	for(; from != to; ++from)
	{
		*from = from.index();
	}
}

static void mutable_int_list()
{
	std::list<int>		list;

	{ for(size_t i = 0; i < 10; ++i)
	{
		list.push_back(-1);
	}}

	cout << "Initial values:" << endl;
	std::copy(list.begin(), list.end(), std::ostream_iterator<int>(cout, ","));
	cout << endl << endl;

	// mutating iterative access
	mutate_indexes(stlsoft::indexer(list.begin()), stlsoft::indexer(list.end()));

	cout << "Values after indexed mutation:" << endl;
	std::copy(list.begin(), list.end(), std::ostream_iterator<int>(cout, ","));
	cout << endl << endl;

	// mutating reverse iterative access
	mutate_indexes(stlsoft::indexer(list.rbegin()), stlsoft::indexer(list.rend()));

	cout << "Values after reverse indexed mutation:" << endl;
	std::copy(list.begin(), list.end(), std::ostream_iterator<int>(cout, ","));
	cout << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////

template <typename I>
void mutate_strings(I from, I to)
{
	for(; from != to; ++from)
	{
		char	sz[21];

		*from = stlsoft::integer_to_string(sz, 21, from.index());
	}
}

static void mutable_string_vector()
{
	std::vector<std::string>		strings(10);

	cout << "Initial values:" << endl;
	std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(cout, ","));
	cout << endl << endl;

	// mutating iterative access
	mutate_strings(stlsoft::indexer(strings.begin()), stlsoft::indexer(strings.end()));

	cout << "Values after indexed mutation:" << endl;
	std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(cout, ","));
	cout << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////

static void immutable_string_vector()
{
}

////////////////////////////////////////////////////////////////////////////////

template<typename I>
void dump_indexed_range(I from, I to)
{
	for(; from != to; ++from)
	{
		cout << from.index() << ": " << *from << endl;
	}
}

static void recls_test_shorthand()
{
	recls::stl::search_sequence	files("/freelibs/pantheios/1.0.x", "*.h|*.hpp", recls::FILES | recls::RECURSIVE);

	dump_indexed_range(stlsoft::indexer(files.begin()), stlsoft::indexer(files.end()));
}

////////////////////////////////////////////////////////////////////////////////

static int main_(int /* argc */, char ** /*argv*/)
{
#if 1
	recls_test_shorthand();
	mutable_string_vector();
	immutable_string_vector();
	mutable_int_list();

#else /* ? 0 */
	recls_test_longhand();
#endif /* 0 */

	return EXIT_SUCCESS;
}

#endif /* 0 */

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
		cout << "index_iterator_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
