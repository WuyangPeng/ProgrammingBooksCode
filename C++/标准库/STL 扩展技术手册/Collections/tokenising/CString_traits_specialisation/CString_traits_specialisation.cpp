/* /////////////////////////////////////////////////////////////////////////////
 * File:        CString_traits_specialisation.cpp
 *
 * Purpose:     Implementation file for the CString_traits_specialisation project.
 *
 * Created:     22nd February 2006
 * Updated:     22nd February 2006
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
#include <stlsoft/string_tokeniser.hpp>
#include <stlsoft/iterators/ostream_iterator.hpp>
#include <stlsoft/tokenising/charset_tokeniser.hpp>

#include <mfcstl/mfcstl.hpp>
#include <mfcstl/string_access.hpp>


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#if 0
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

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

namespace stlsoft
{
	struct string_tokeniser_type_traits<CString, CString>
	{
	public:
		typedef TCHAR       value_type;
		typedef LPCTSTR     const_iterator_type;

	public:
		static const_iterator_type begin(CString const &s)
		{
			return s;
		}
		static const_iterator_type end(CString const &s)
		{
			return begin(s) + s.GetLength();
		}

		static CString create(const_iterator_type f, const_iterator_type t)
		{
			return CString(f, t - f);
		}
	};
} // namespace stlsoft


namespace stlsoft
{
    template<   ss_typename_param_k S
    #ifdef STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT
            ,   ss_typename_param_k B = skip_blank_tokens<true>
            ,   ss_typename_param_k V = S
            ,   ss_typename_param_k T = string_tokeniser_type_traits<S, V>
            ,   ss_typename_param_k D = S
            ,   ss_typename_param_k P = charset_comparator<S>
    #else /* ? STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
            ,   ss_typename_param_k B
            ,   ss_typename_param_k V
            ,   ss_typename_param_k T
            ,   ss_typename_param_k D
            ,   ss_typename_param_k P
    #endif /* STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
            >
    struct charset_tokeniser_selector
    {
    public:
        typedef string_tokeniser<S, D, B, V, T, P>  tokeniser_type;
    };
} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		stlsoft::string_tokeniser<	CString
								,	char
								>	tokens("abc;def;ghi;;jkl;;;", ';');

		std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<CString>(cout, "\t[", "]\n"));
		cout << endl;
	}

	{
        stlsoft::charset_tokeniser_selector<std::string>::tokeniser_type    tokens("\rabc def\nghi\tjkl  ", " \r\n\t");

        std::copy(tokens.begin(), tokens.end(), stlsoft::ostream_iterator<std::string>(cout, "\t[", "]\n"));
        cout << endl;
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
        puts("CString_traits_specialisation: " __STLSOFT_COMPILER_LABEL_STRING);
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
