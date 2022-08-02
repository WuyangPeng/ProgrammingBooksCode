/* /////////////////////////////////////////////////////////////////////////
 * File:        CArray_motivation.test.cpp
 *
 * Purpose:     Implementation file for the CArray_motivation.test project.
 *
 * Created:     8th February 2007
 * Updated:     8th February 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2007-2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* MFCSTL Header Files */
#include <mfcstl/collections/carray_adaptors.hpp>
#include <mfcstl/collections/clist_adaptors.hpp>

/* STLSoft Header Files */
#include <stlsoft/iterators/ostream_iterator.hpp>

/* WinSTL Header Files */
#include <winstl/error/error_desc.hpp>


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

/* /////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////
 * Globals
 */


/* /////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void readLines(char const *fileName, CStringArray &arr);
static void motivation_MFC_way(char const *fileName, CStringList &lst);
static void motivation_MFCSTL_way(char const *fileName, CStringList &lst);

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	TCHAR const	fileName[]	=	"";

	CStringList	lst1;
	CStringList	lst2;

	motivation_MFC_way(fileName, lst1);
	motivation_MFCSTL_way(fileName, lst2);

    return EXIT_SUCCESS;
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
        puts("CArray_motivation.test: " __STLSOFT_COMPILER_LABEL_STRING);
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

inline std::ostream &operator <<(std::ostream &stm, CString const &str)
{
	return stm << static_cast<LPCTSTR>(str);
}

int compare_CStrings(void const* pv1, void const* pv2)
{
  return static_cast<CString const*>(pv1)->Compare(static_cast<LPCTSTR>(pv2));
//  return static_cast<CString const*>(pv1)->Compare(*static_cast<CString const*>(pv2));
}; 


static void readLines(char const *fileName, CStringArray &arr)
{
	arr.Add("String #8");
	arr.Add("String #1");
	arr.Add("String #5");
}

static void motivation_MFC_way(char const *fileName, CStringList &lst)
{
	std::cout << endl << "Via MFC:" << endl;

CStringArray	arr;
readLines(fileName, arr);
::qsort(arr.GetData(), static_cast<size_t>(arr.GetSize())
      , sizeof(CString), compare_CStrings);
lst.RemoveAll();
{ for(int i = 0; i < arr.GetSize(); ++i)
{
	lst.AddTail(arr[i]);
}}

{ for(POSITION pos = lst.GetHeadPosition(); NULL != pos; )
{
	std::cout << "\t" << lst.GetNext(pos) << std::endl;
}}
}

static void motivation_MFCSTL_way(char const *fileName, CStringList &lst)
{
	using mfcstl::CArray_cadaptor;
	using mfcstl::CArray_iadaptor;
	using mfcstl::CArray_traits;
	using mfcstl::CList_cadaptor;
	using mfcstl::CList_iadaptor;
	using mfcstl::CList_traits;

	std::cout << endl << "Via MFCSTL:" << endl;

CArray_cadaptor<CStringArray, CArray_traits<CStringArray> >		arr;
readLines(fileName, arr);
std::sort(arr.begin(), arr.end());
CList_iadaptor<CStringList, CList_traits<CStringList> >			la(lst);
#if 1
std::copy(arr.begin(), arr.end(), std::back_inserter(la));
#else /* ? 0 */
la.assign(arr.begin(), arr.end());
#endif /* 0 */

	{
		mfcstl::CList_iadaptor<CStringList, mfcstl::CList_traits<CStringList> >	la(lst);

		std::copy(	la.begin(), la.end()
				,	stlsoft::ostream_iterator<LPCTSTR>(std::cout, "\t", "\n"));
		;
	}
}

/* ////////////////////////////////////////////////////////////////////// */
