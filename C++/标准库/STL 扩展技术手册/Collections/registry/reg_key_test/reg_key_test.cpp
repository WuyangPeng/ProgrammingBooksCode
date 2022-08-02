/* /////////////////////////////////////////////////////////////////////////////
 * File:        reg_key_test.cpp
 *
 * Purpose:     Implementation file for the reg_key_test project.
 *
 * Created:     8th February 2006
 * Updated:     1st May 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006-2007, Synesis Software Pty Ltd.
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

#include <winstl/winstl.h>
#include <winstl/registry/reg_key.hpp>
#include <winstl/registry/reg_value.hpp>

#include <winstl/registry/reg_key_sequence.hpp>
#include <winstl/registry/reg_value_sequence.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
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

typedef std::string     string_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	winstl::reg_key		key(HKEY_CURRENT_USER, "SOFTWARE\\Synesis Software");
	winstl::reg_key		_scratch(key, "_scratch");

	_scratch.set_value("", "Arch");
	_scratch.set_value("v1", "Arch");
	_scratch.set_value("v2", 1);
	_scratch.set_value(string_t(""), "Arch");
	_scratch.set_value(string_t("v1"), "Arch");
	_scratch.set_value(string_t("v2"), 1);

	static const char *strings[] = 
	{
			"string 1"
		,	"string 2"
		,	"string 3"
	};

	_scratch.set_value("mul1", strings, WINSTL_NUM_ELEMENTS(strings));

	DWORD	totalSize	=	0;
	LONG	l			=	::RegQueryMultipleValues(_scratch.get(), NULL, 0, NULL, &totalSize);

	winstl::reg_value		v2		=	_scratch.get_value("v2");
	winstl::reg_string_t	name	=	v2.name();
	winstl::reg_string_t	val_1	=	v2.value_sz();
	winstl::reg_string_t	val_2	=	v2.value_expand_sz();

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
        cout << "reg_key_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
