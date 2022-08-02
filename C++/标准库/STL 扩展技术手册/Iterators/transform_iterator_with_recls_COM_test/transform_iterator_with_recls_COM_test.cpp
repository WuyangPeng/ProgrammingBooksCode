/* /////////////////////////////////////////////////////////////////////////////
 * File:        transform_iterator_with_recls_COM_test.cpp
 *
 * Purpose:     Implementation file for the transform_iterator_with_recls_COM_test project.
 *
 * Created:     15th December 2005
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


#define _SYB_ALLOW_UNSAFE_CONVERSION_TO_ANSI

/* recls Header Files */
#include "../mappings/COM/recls.com.h"

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/shim_string.hpp>
#include <stlsoft/iterators/transform_iterator.hpp>

#include <comstl/comstl.h>
#include <comstl/creation_functions.hpp>
#include <comstl/enumerator_sequence.hpp>
#include <comstl/initialisers.hpp>
#include <comstl/interface_traits.hpp>
#include <comstl/method_cast.hpp>
#include <comstl/value_policies.hpp>

#include <winstl/winstl.h>


/* Synesis Software Header Files */
#include <MOBstr.h>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#if 0
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

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static HRESULT  open_search(char const *dir, char const *pattern, long flags, IEnumFileEntry **ppEfe);


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

namespace stdex
{
    template<   typename I1
            ,   typename I2
            ,   typename O
            >
    inline O copy(I1 from, I2 to, O result)
    {
        for(; from != to; ++from, ++result)
        {
            *result = *from;
        }

        return result;
    }

} // namespace stdex

/* /////////////////////////////////////////////////////////////////////////////
 * Function Objects
 */

namespace stlsoft
{
	namespace comstl_project
	{
		template<	typename R
				,	typename I
				,	typename V
				>
		struct property_invoker
			: public std::unary_function<I *, R>
		{
		public:
#if 0
			property_invoker()
				: m_pfn(NULL)
			{}
#endif /* 0 */
			property_invoker(HRESULT (STDAPICALLTYPE I::*pfn)(V *))
				: m_pfn(pfn)
			{}

		public:
			R operator ()(I *p)
			{
#if 0
				R       r	=	R();
				V       v;
				HRESULT	hr	=	(p->*m_pfn)(&v);

				if(SUCCEEDED(hr))
				{
					return transfer_resource(r, v);
				}

				return r;
#else /* ? 0 */
				return comstl::method_cast<R>(p, m_pfn);
#endif /* 0 */
			}

		private:
			HRESULT (STDAPICALLTYPE I::*m_pfn)(V *);
		};

		template<	typename R
				,	typename I
				,	typename V
				>
		inline property_invoker<R, I, V> property_invoke(HRESULT (STDAPICALLTYPE I::*pfn)(V *))
		{
			return property_invoker<R, I, V>(pfn);
		}
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename I>
#if 0
std::iterator_traits<I>::value_type &get_iter_ref(I i)
#else /* ? 0 */
# if 0
typename I::value_type &get_iter_ref(I i)
# else /* ? 0 */
typename I::reference get_iter_ref(I i)
# endif /* 0 */
#endif /* 0 */
{
	return *i;
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
//		const int	ints[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		const int	ints[] = { 0, -1, 2, -3, 4, -5, 6, -7, 8, -9 };

		typedef stlsoft::transform_iterator<int const*
										,	std::pointer_to_unary_function<int, int>
										>		abs_iter_t;

		abs_iter_t	b	=	abs_iter_t(&ints[0], std::ptr_fun(::abs));
		abs_iter_t	e	=	abs_iter_t(&ints[0] + STLSOFT_NUM_ELEMENTS(ints), std::ptr_fun(::abs));

		std::copy(b, e, std::ostream_iterator<int>(cout, " "));
		cout << endl;
		cout << endl;
	}

	{
		IEnumFileEntry	*pEfe;
		HRESULT         hr  =   open_search("."
										,   "*.c|*.cpp|*.h|*.hpp|*.d|*.rb|*.java|*.cs|*.py"
										,   RECLS_F_FILES | RECLS_F_RECURSIVE
										,   &pEfe);

		if(SUCCEEDED(hr))
		{
			IFileEntry  *entries[5];
			ULONG       numRetrieved = 0;

			typedef stlsoft::transform_iterator<IFileEntry**
											,	comstl::property_invoker<comstl::bstr, IFileEntry, BSTR>
											>		get_path_iter_t;

			for(pEfe->Reset(); SUCCEEDED(pEfe->Next(STLSOFT_NUM_ELEMENTS(entries), &entries[0], &numRetrieved)); )
			{
				if(0 == numRetrieved)
				{
					break;
				}
				get_path_iter_t	b	=	get_path_iter_t(&entries[0], comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path));
				get_path_iter_t	e	=	get_path_iter_t(&entries[0] + numRetrieved, comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path));

				std::copy(b, e, std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
				cout << endl;
			}
		}
		cout << endl;
	}


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
											>       enumerator_t;
			typedef stlsoft::transform_iterator<enumerator_t::iterator
											,	comstl::property_invoker<comstl::bstr, IFileEntry, BSTR>
											>		get_path_iter_t;

			enumerator_t    entries(pEfe, false, 5); // Eat the reference. Does not throw
			get_path_iter_t	b	=	get_path_iter_t(entries.begin(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path));
			get_path_iter_t	e	=	get_path_iter_t(entries.end(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path));

			std::copy(b, e, std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;
		}
		cout << endl;
	}

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
											>       enumerator_t;
			typedef stlsoft::transform_iterator<enumerator_t::iterator
											,	comstl::property_invoker<comstl::bstr, IFileEntry, BSTR>
											>		get_path_iter_t;

			enumerator_t            entries(pEfe, false, 5); // Eat the reference. Does not throw

			std::copy(	get_path_iter_t(entries.begin(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path))
					,	get_path_iter_t(entries.end(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path))
					,	std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;
		}
		cout << endl;
	}

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
											>       enumerator_t;

			enumerator_t            entries(pEfe, false, 5); // Eat the reference. Does not throw

			std::copy(	stlsoft::transformer(entries.begin(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path))
					,	stlsoft::transformer(entries.end(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path))
					,	std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;

#if 0
			if(0)
			{
				cout << get_iter_ref(stlsoft::transformer(entries.begin(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path)));
			}
#endif /* 0 */
		}
		cout << endl;
	}

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
											>       enumerator_t;
			typedef comstl::property_invoker<	comstl::bstr
											,	IFileEntry
											,	BSTR
											>		transform_t;

			enumerator_t            entries(pEfe, false, 5); // Eat the reference. Does not throw

			std::copy(	stlsoft::transformer(entries.begin(), transform_t(&IFileEntry::get_Path))
					,	stlsoft::transformer(entries.end(), transform_t(&IFileEntry::get_Path))
					,	std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;
		}
		cout << endl;
	}

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
											>       enumerator_t;
			typedef comstl::property_invoker<	comstl::bstr
											,	IFileEntry
											,	BSTR
											>		transform_t;

			enumerator_t	entries(pEfe, false, 5); // Eat the reference. Does not throw
			transform_t		tx(&IFileEntry::get_Path);

			std::copy(	stlsoft::transformer(entries.begin(), tx)
					,	stlsoft::transformer(entries.end(), tx)
					,	std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;
		}
		cout << endl;
	}

#if 0
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
											>       enumerator_t;

			enumerator_t            entries(pEfe, false, 5); // Eat the reference. Does not throw

			stdex::copy(	stlsoft::transformer(entries.begin(), comstl::property_invoke<comstl::bstr>(&IFileEntry::get_Path))
					,	/* stlsoft::transformer */(entries.end())
					,	std::ostream_iterator<comstl::bstr, wchar_t>(wcout, L"\n"));
			cout << endl;
		}
		cout << endl;
	}
#endif /* 0 */

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
		cout << "transform_iterator_with_recls_COM_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
