/* /////////////////////////////////////////////////////////////////////////////
 * File:        assignable_test.cpp
 *
 * Purpose:     Implementation file for the assignable_test project.
 *
 * Created:     6th February 2006
 * Updated:     6th February 2006
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

#define MFCSTL_ARRAY_ADAPTORS_ALLOW_CAPACITY_PEEK

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

#include <mfcstl/mfcstl.hpp>
#include <mfcstl/carray_adaptors.hpp>
#include <mfcstl/string_access.hpp>

#include <afxtempl.h>

#include <winstl/winstl.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <stack>

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
 * Typedefs
 */

class CStringX
	: public CString
{
public:
	CStringX()
	{}
	CStringX(char const *s)
		: CString(s)
	{}
private:
	CStringX(CStringX const &rhs);
public:


};

//typedef CString	string_t;
typedef CStringX	string_t;

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
    typedef std::stack< string_t
                    ,   mfcstl::CArray_cadaptor<CArray<string_t, string_t const&>
											,	mfcstl::CArray_specific_traits<string_t, string_t const&, CArray<string_t, string_t const&> >
											>
                    >       stack_t;

    stack_t stk;

    stk.push("String 1");
    stk.push("String 2");
    stk.push("String 3");
    stk.push("String 4");
    stk.push("String 5");

    stack_t stk2(stk);

    for(; !stk.empty(); stk.pop())
    {
        cout << stk.top() << endl;

		if(0)
		{
			CArchive	*par	=	(0 == ::GetTickCount()) ? static_cast<CArchive*>(0) : static_cast<CArchive*>(0);
			CArchive	&ar		=	*par;

			ar << stk.top();
		}
    }

	{
		mfcstl::CArray_cadaptor<CStringArray>	car1;
		mfcstl::CArray_cadaptor<CStringArray>	car2(10);
		mfcstl::CArray_cadaptor<CStringArray>	car3(10, "str");
		mfcstl::CArray_cadaptor<CStringArray>	car4(car2);
		mfcstl::CArray_cadaptor<CStringArray>	car5(car2.get_CArray());
		mfcstl::CArray_cadaptor<CStringArray>	car6(car2.begin(), car2.end());
	}

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
        cout << "assignable_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
