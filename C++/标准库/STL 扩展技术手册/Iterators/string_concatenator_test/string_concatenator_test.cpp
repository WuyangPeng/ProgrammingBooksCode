/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_concatenator_test.cpp
 *
 * Purpose:     Implementation file for the string_concatenator_test project.
 *
 * Created:     23rd December 2005
 * Updated:     23rd December 2005
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

#if (	!defined(__BORLANDC__) || \
		__BORLANDC__ < 0x0560) && \
	!defined(__GNUC__)
# include <mfcstl/mfcstl.hpp>
# include <mfcstl/carray_adaptors.hpp>
# include <mfcstl/string_access.hpp>
# include <afxtempl.h>
# include <afxole.h>
#endif /* compiler */

#include <stlsoft/stlsoft.h>
#include <stlsoft/iterators/string_concatenator_iterator.hpp>

#include <comstl/comstl.h>
#include <comstl/string_access.hpp>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl/unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl/winstl.h>

#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>

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

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{	// std::string

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string	result;

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, ""));

			if("abcdefghijklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=char[], it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string	result;

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, ","));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=char[], it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string	result;
			char const	*delim		=	",";

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=char const*, it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string			result;
			const std::string	delim("");

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abcdefghijklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=std::string, it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string			result;
			const std::string	delim(",");

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=std::string, it=char const**] " << endl;
			}
		}
	}

#ifdef COMSTL_INCL_COMSTL_H_COMSTL
	{	// std::string

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string	result;
			VARIANT		delim;

			::VariantInit(&delim);

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, ""));

			if("abcdefghijklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=VARIANT, it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			std::string	result;
			VARIANT		delim;

			::VariantInit(&delim);
			delim.bstrVal	=	::SysAllocString(L",");
			delim.vt		=	VT_BSTR;

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=std::string + D=char[], it=char const**] " << endl;
			}

			::VariantClear(&delim);
		}
	}
#endif /* COMSTL_INCL_COMSTL_H_COMSTL */

#ifdef MFCSTL_INCL_MFCSTL_HPP_MFCSTL
	{	// std::string

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			CString	result;

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, ""));

			if("abcdefghijklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=CString + D=char[], it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			CString	result;

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, ","));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=CString + D=char[], it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			CString		result;
			char const	*delim		=	",";

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=CString + D=char const*, it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			CString			result;
			const CString	delim("");

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abcdefghijklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=CString + D=CString, it=char const**] " << endl;
			}
		}

		{
			char const	*strings[] = 
			{
					"abc"
				,	"defg"
				,	"h"
				,	"i"
				,	"jklm"
			};
			CString			result;
			const CString	delim(",");

			std::copy(	&strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
					,	stlsoft::string_concatenator(result, delim));

			if("abc,defg,h,i,jklm" != result)
			{
				cout << "stlsoft::string_concatenator_iterator failed; [S=CString + D=CString, it=char const**] " << endl;
			}
		}
	}

	{
		typedef CArray<COleVariant, COleVariant const&>   VariantArray_t;

		VariantArray_t	ar;
		CEdit			wnd;	wnd.Create(0, RECT(), CWnd::GetDesktopWindow(), 1900); wnd.SetWindowText(" ");
		CString			result;

		COleVariant	var1("Space");
		COleVariant	var2(long(1999));
		COleVariant	var3("? More like it's");
		COleVariant	var4(COleDateTime(2005, 12, 23, 13, 14, 52));

		ar.Add(var1);
		ar.Add(var2);
		ar.Add(var3);
		ar.Add(var4);

		mfcstl::CArray_iadaptor<VariantArray_t
#if !defined(__STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT)
							,	mfcstl::CArray_specific_traits<	COleVariant
															,	COleVariant const&
															,	VariantArray_t
															>
#endif /* 0 */
							>			arr(ar);

		std::copy(	arr.begin(), arr.end()
				,	stlsoft::string_concatenator(result, wnd));

		cout << static_cast<char const*>(result) << endl;
	}

#endif /* MFCSTL_INCL_MFCSTL_HPP_MFCSTL */

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
		cout << "string_concatenator_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
