/* /////////////////////////////////////////////////////////////////////////////
 * File:        CArray_sorting_examples.cpp
 *
 * Purpose:     Implementation file for the CArray_sorting_examples project.
 *
 * Created:     9th August 2005
 * Updated:     21st January 2006
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

/* STLSoft Header Files */
#include <stlsoft.h>

#include <afxtempl.h>
#include <mfcstl.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>

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
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

int compare_CStrings(void const *pv1, void const *pv2)
{
#if 0
	return static_cast<CString const*>(pv1)->Compare(static_cast<LPCTSTR>(pv2));
#else /* ? 0 */
	return static_cast<CString const*>(pv1)->Compare(static_cast<LPCTSTR>(*static_cast<CString const*>(pv2)));
#endif /* 0 */
}; 

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("CArray_sorting_examples: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	{
		CStringArray  ar;

		// . . . // code to populate ar
		ar.Add("String 2");
		ar.Add("String 3");
		ar.Add("String 1");

		::qsort(ar.GetData(), static_cast<size_t>(ar.GetSize()), sizeof(CString), compare_CStrings);

		cout << "0: " << (char const *)ar[0] << endl;
		cout << "1: " << (char const *)ar[1] << endl;
		cout << "2: " << (char const *)ar[2] << endl;
	}

	{
		CArray<CString, LPCTSTR>	ar;

		ar.Add("String 2");
		ar.Add("String 3");
		ar.Add("String 1");

	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	::Sleep(100000);
#endif /* 0 */

	try
	{
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
