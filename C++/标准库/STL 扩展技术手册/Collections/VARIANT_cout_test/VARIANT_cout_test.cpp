/* /////////////////////////////////////////////////////////////////////////////
 * File:        VARIANT_cout_test.cpp
 *
 * Purpose:     Implementation file for the VARIANT_cout_test project.
 *
 * Created:     31st October 2006
 * Updated:     31st October 2006
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
 * ////////////////////////////////////////////////////////////////////////// */


/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/smartptr/ref_ptr.hpp>

#include <comstl/comstl.h>
#include <comstl/error/errorinfo_desc.hpp>
#include <comstl/util/creation_functions.hpp>
#include <comstl/util/initialisers.hpp>
#include <comstl/shims/access/string/variant.hpp>

#include <winstl/winstl.h>
#include <winstl/error/error_desc.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::wcout;
using std::endl;

/* Standard C Header Files */
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"VARIANT_cout_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{

#if 0
VARIANT       var;
IEnumVARIANT  *pen = . . .
for(pen->Reset(); S_OK == pen->Next(1, &var, NULL); )
{
  wcout << L"VARIANT type: " << var.vt << endl;
  ::VariantFree(&var);
}
#else /* ? 0 */
VARIANT       var;

var.vt		=	VT_I4;
var.lVal	=	23;

  wcout << L"VARIANT type: " << var.vt << endl;

  wcout << L"VARIANT: " << stlsoft::c_str_ptr(var) << endl;

#endif /* 0 */

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
        cout << "VARIANT_cout_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

        comstl::com_initialiser coinit;

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

/* ////////////////////////////////////////////////////////////////////////// */
