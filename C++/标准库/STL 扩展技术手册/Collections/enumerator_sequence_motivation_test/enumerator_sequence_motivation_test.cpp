/* /////////////////////////////////////////////////////////////////////////////
 * File:        enum_sequence_motivation_test.cpp
 *
 * Purpose:     Implementation file for the enum_sequence_motivation_test project.
 *
 * Created:     14th December 2005
 * Updated:     1st February 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2007, Synesis Software Pty Ltd.
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
#include "../mappings/COM/recls.com.h"

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/shim_string.hpp>

#include <comstl/comstl.h>
#include <comstl/creation_functions.hpp>
#include <comstl/enumerator_sequence.hpp>
#include <comstl/initialisers.hpp>
#include <comstl/interface_traits.hpp>
#include <comstl/method_cast.hpp>
#include <comstl/value_policies.hpp>

#include <winstl/winstl.h>
#include <winstl/control_functions.h>
#include <winstl/listbox_sequence.hpp>

#include <rangelib/rangelib.hpp>
#include <rangelib/sequence_range.hpp>


/* Synesis Software Header Files */
#include <MOBstr.h>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

using std::cerr;
using std::cin;
using std::cout;
using std::wcout;
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

////////////////////////////////////////////////////////////////////////////////

namespace comstl
{
    inline comstl::bstr &transfer_resource(comstl::bstr &r, BSTR v)
    {
        comstl_message_assert("Resource destination not empty!", r.IsEmpty());
        r.Attach(v);

        return r;
    }
}

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void     long_hand_version();
static void     short_hand_version();
static void     range_version();
static HRESULT  open_search(char const *dir, char const *pattern, long flags, IEnumFileEntry **ppEfe);

/* ////////////////////////////////////////////////////////////////////////// */

inline stlsoft::basic_shim_string<OLECHAR> c_str_ptr(IFileEntry *fe, HRESULT (__stdcall IFileEntry::*pfn)(BSTR *))
{
	BSTR	bstr;
	HRESULT	hr	=	(fe->*pfn)(&bstr);

	if(FAILED(hr))
	{
		return stlsoft::basic_shim_string<OLECHAR>(NULL, 0);
	}

	stlsoft::basic_shim_string<OLECHAR>	s(bstr);

	::SysFreeString(bstr);

	return s;
}

struct fe_cstr
{
};

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	cout << endl;
    long_hand_version();

	cout << endl;
    short_hand_version();

	cout << endl;
    range_version();

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
        cout << "enum_sequence_motivation_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

        comstl::com_initialiser coinit;

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

static void long_hand_version()
{
	HWND			hwndListBox	=	::CreateWindowExW(0, L"LISTBOX", L"", 0, 0,0,0,0, NULL, NULL, NULL, NULL);

    IEnumFileEntry  *pEfe;
    HRESULT         hr  =   open_search("."
                                    ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
                                    ,   RECLS_F_FILES | RECLS_F_RECURSIVE
                                    ,   &pEfe);

    if(SUCCEEDED(hr))
    {
        IFileEntry  *entries[5];
        ULONG       numRetrieved = 0;

        for(pEfe->Reset(); SUCCEEDED(pEfe->Next(STLSOFT_NUM_ELEMENTS(entries), &entries[0], &numRetrieved)); )
        {
            if(0 == numRetrieved)
            {
                break;
            }
            for(ULONG i = 0; i < numRetrieved; ++i)
            {
				winstl::listbox_addstring(hwndListBox, comstl::method_cast<comstl::bstr>(entries[i], &IFileEntry::get_Path));

#if 0
#if 0
                wcout <<  << endl;
#else /* ? 0 */

				winstl::listbox_front_inserter	lins(hwndListBox);
				
				lins(comstl::method_cast<comstl::bstr>(entries[i], &IFileEntry::get_Path));
#endif /* 0 */
#endif /* 0 */

                entries[i]->Release();
            }
        }

        pEfe->Release();
    }


	winstl::listbox_sequence<std::string>	lbs(hwndListBox);

	std::copy(lbs.begin(), lbs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

static void short_hand_version()
{
	HWND			hwndListBox	=	::CreateWindowExW(0, L"LISTBOX", L"", 0, 0,0,0,0, NULL, NULL, NULL, NULL);

    IEnumFileEntry  *pEfe;
    HRESULT         hr  =   open_search("."
                                    ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
                                    ,   RECLS_F_FILES | RECLS_F_RECURSIVE
                                    ,   &pEfe);

    if(SUCCEEDED(hr))
    {
        typedef comstl::enumerator_sequence<IEnumFileEntry
                                        ,   IFileEntry*
                                        ,   comstl::interface_policy<IFileEntry>
                                        ,   IFileEntry*
										,	comstl::input_cloning_policy<IEnumFileEntry>
                                        >       enumerator_t;

        enumerator_t            entries(pEfe, false, 5); // Eat the reference. Does not throw
#if 1
        enumerator_t::iterator  b   =   entries.begin();

#if 1
		enumerator_t::iterator  b2;

		b2	=	b;
		b	=	b;
		b	=	b2;
#endif /* 0 */

        for(; entries.end() != b; ++b)
        {
            wcout << comstl::method_cast<comstl::bstr>(*b, &IFileEntry::get_Path) << endl;
        }
#else /* ? 0 */
		std::copy(entries.begin(), entries.end(), std::bind1st(fe_cstr winstl::listbox_front_inserter(hwndListBox));
#endif /* 0 */
    }


	winstl::listbox_sequence<std::string>	lbs(hwndListBox);

	std::copy(lbs.begin(), lbs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

/* ////////////////////////////////////////////////////////////////////////// */

static void range_version()
{
    IEnumFileEntry  *pEfe;
    HRESULT         hr  =   open_search("."
                                    ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
                                    ,   RECLS_F_FILES | RECLS_F_RECURSIVE
                                    ,   &pEfe);

    if(SUCCEEDED(hr))
    {
        typedef comstl::enumerator_sequence<IEnumFileEntry
                                        ,   IFileEntry*
                                        ,   comstl::interface_policy<IFileEntry>
                                        >               enumerator_t;
        typedef rangelib::sequence_range<   enumerator_t
#if !defined(STLSOFT_CF_HAS_MEMBER_TYPE_SUPPORTED)
                                        ,   rangelib::non_const_sequence_range_traits<enumerator_t>
#endif /* !STLSOFT_CF_HAS_MEMBER_TYPE_SUPPORTED */
                                        >               range_t;

        { for(range_t r(enumerator_t(pEfe, false, 5)); r; ++r)
        {
            wcout << comstl::method_cast<comstl::bstr>(*r, &IFileEntry::get_Path) << endl;
        }}
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

static HRESULT open_search(char const *dir, char const *pattern, long flags, IEnumFileEntry **ppEfe)
{
    COMSTL_ASSERT(NULL != ppEfe);

    *ppEfe = NULL;

    IFileSearch *pfs;
    HRESULT     hr = comstl::co_create_instance(CLSID_FileSearch, &pfs);

    if(SUCCEEDED(hr))
    {
        LPUNKNOWN    punkColl;

        hr = pfs->Search(   comstl::bstr(dir)
                        ,   comstl::bstr(pattern)
                        ,   flags
                        ,   &punkColl);

        if(SUCCEEDED(hr))
        {
            ISearchCollection   *pSrchColl;

            hr = punkColl->QueryInterface(comstl::IID_traits<ISearchCollection>::iid(), reinterpret_cast<void**>(&pSrchColl));

            if(SUCCEEDED(hr))
            {
                LPUNKNOWN   punkEnum;

                hr = pSrchColl->get__NewEnum(&punkEnum);
                    
                if(SUCCEEDED(hr))
                {
                    hr = punkEnum->QueryInterface(comstl::IID_traits<IEnumFileEntry>::iid(), reinterpret_cast<void**>(ppEfe));

                    punkEnum->Release();
                }

                pSrchColl->Release();
            }

            punkColl->Release();
        }


        pfs->Release();
    }

    return hr;
}

/* ////////////////////////////////////////////////////////////////////////// */
