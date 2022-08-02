/* /////////////////////////////////////////////////////////////////////////////
 * File:        collection_sequence_motivation_test.cpp
 *
 * Purpose:     Implementation file for the collection_sequence_motivation_test project.
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

	#include <MODisp.h>


/* recls Header Files */
#include "../mappings/COM/recls.com.h"

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

#include <comstl/comstl.h>
#include <comstl/creation_functions.hpp>
#include <comstl/collection_sequence.hpp>
#include <comstl/initialisers.hpp>
#include <comstl/interface_traits.hpp>
#include <comstl/method_cast.hpp>
#include <comstl/value_policies.hpp>

#include <winstl/winstl.h>

#include <rangelib/rangelib.hpp>
#include <rangelib/sequence_range.hpp>


/* Synesis Software Header Files */
#include <MOBstr.h>
#include <MODisp.h>

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
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void     long_hand_version();
static void     short_hand_version();
static void     range_version();
static HRESULT  open_search(char const *dir, char const *pattern, long flags, ISearchCollection **ppSrchColl);

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
		puts("collection_sequence_motivation_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        comstl::com_initialiser coinit;

		iRet = main_(argc, argv);
	}
	catch(std::exception &x)
	{
		fprintf(stderr, "Unhandled error: %s\n", x.what());

		iRet = EXIT_FAILURE;
	}
	catch(...)
	{
		fprintf(stderr, "Unhandled unknown error\n");

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
    ISearchCollection	*pSrchColl;
    HRESULT				hr  =   open_search("."
                                    ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
                                    ,   RECLS_F_FILES | RECLS_F_RECURSIVE
                                    ,   &pSrchColl);

    if(SUCCEEDED(hr))
    {
		LPUNKNOWN	punkEnum;

		hr = pSrchColl->get__NewEnum(&punkEnum);

		if(SUCCEEDED(hr))
		{
			IEnumVARIANT	*pEnVar;

//			hr = pSrchColl->QueryInterface(IID_IEnumVARIANT, reinterpret_cast<void**>(&punkEnum));
			hr = punkEnum->QueryInterface(IID_IEnumVARIANT, reinterpret_cast<void**>(&pEnVar));

			if(SUCCEEDED(hr))
			{
				VARIANT	entries[5];
				ULONG	cFetched = 0;

				for(pEnVar->Reset(); SUCCEEDED(pEnVar->Next(STLSOFT_NUM_ELEMENTS(entries), &entries[0], &cFetched)); )
				{
					if(0 == cFetched)
					{
						break;
					}
					else
					{
						for(ULONG i = 0; i < cFetched; ++i)
						{
							if(	VT_UNKNOWN == entries[i].vt ||
								VT_DISPATCH == entries[i].vt)
							{
								IFileEntry	*pFe;

								hr = entries[i].punkVal->QueryInterface(IID_IFileEntry, reinterpret_cast<void**>(&pFe));

								if(SUCCEEDED(hr))
								{
									wcout << comstl::method_cast<comstl::bstr>(pFe, &IFileEntry::get_Path) << endl;

									pFe->Release();
								}
							}

							::VariantClear(&entries[i]);
						}
					}
				}

				pEnVar->Release();
			}

			punkEnum->Release();
		}

		pSrchColl->Release();
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

static void short_hand_version()
{
    ISearchCollection   *pSrchColl;
    HRESULT             hr  =   open_search("."
                                        ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
                                        ,   RECLS_F_FILES | RECLS_F_RECURSIVE
                                        ,   &pSrchColl);

    if(SUCCEEDED(hr))
    {
        typedef comstl::collection_sequence<ISearchCollection
                                        ,   IEnumFileEntry
                                        ,   IFileEntry*
                                        ,   comstl::interface_policy<IFileEntry>
#if 1
										,	IFileEntry*
										,	comstl::input_cloning_policy<IEnumFileEntry>
										,	5
										,	comstl::new_enum_by_dispid_policy<ISearchCollection>
#endif /* 1 */
                                        >       collection_t;

        collection_t            en(pSrchColl, false, 3); // Eat the reference. Does not throw
        collection_t::iterator  b   =   en.begin();

        collection_t::iterator  b2;

        { for(; en.end() != b; ++b)
        {
            wcout << comstl::method_cast<comstl::bstr>(*b, &IFileEntry::get_Path) << endl;
        }}
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

static void range_version()
{
    ISearchCollection	*pSrchColl;
    HRESULT				hr  =   open_search("."
							            ,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
								        ,   RECLS_F_FILES | RECLS_F_RECURSIVE
									    ,   &pSrchColl);

    if(SUCCEEDED(hr))
    {
        typedef comstl::collection_sequence<ISearchCollection
										,	IEnumFileEntry
                                        ,   IFileEntry*
                                        ,   comstl::interface_policy<IFileEntry>
                                        >				collection_t;
        typedef rangelib::sequence_range<   collection_t
                                        ,   rangelib::non_const_sequence_range_traits<collection_t>
                                        >               range_t;

        { for(range_t r(collection_t(pSrchColl, false, 5)); r; ++r)
        {
            wcout << comstl::method_cast<comstl::bstr>(*r, &IFileEntry::get_Path) << endl;
        }}
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

static HRESULT open_search(char const *dir, char const *pattern, long flags, ISearchCollection **ppSrchColl)
{
    COMSTL_ASSERT(NULL != ppSrchColl);

    *ppSrchColl = NULL;

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
            hr = punkColl->QueryInterface(comstl::IID_traits<ISearchCollection>::iid(), reinterpret_cast<void**>(ppSrchColl));

			punkColl->Release();
		}

        pfs->Release();
    }

    return hr;
}

/* ////////////////////////////////////////////////////////////////////////// */
