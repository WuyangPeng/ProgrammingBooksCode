/* /////////////////////////////////////////////////////////////////////////////
 * File:        alloc_gran_test.cpp
 *
 * Purpose:     Implementation file for the alloc_gran_test project.
 *
 * Created:     6th February 2006
 * Updated:     8th February 2006
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
#include <winstl/performance_counter.hpp>


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

static int	s_numCtors		=	0;
static int	s_numAssigns	=	0;

class CStringX
	: public CString
{
public:
	CStringX()
	{
		++s_numCtors;
	}
	CStringX(char const *s)
		: CString(s)
	{
		++s_numCtors;
	}
private:
	CStringX(CStringX const &rhs);
public:

	CStringX &operator =(CStringX const &rhs)
	{
		CString::operator =(rhs);

		++s_numAssigns;

		return *this;
	}

};

//typedef CString							string_t;
typedef CStringX							string_t;
typedef CArray<string_t, string_t const &>	string_array_t;
typedef mfcstl::CArray_iadaptor<string_array_t
							,	mfcstl::CArray_specific_traits<	string_t
															,	string_t const &
															,	string_array_t
															>
							>				adaptor_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */


struct Scenario
{
	char const	*name;
	int			initialSize;
	bool		useAdaptor;
};

#ifdef NUM_ELS
const int N	=	NUM_ELS;
#else
//const int	N	=	10;
//const int	N	=	20;
const int	N	=	100;
//const int	N	=	200;
//const int	N	=	1000;
#endif

static int main_(int /* argc */, char ** /*argv*/)
{
    /* . */
	winstl::performance_counter	counter;
	size_t						numAllocations	=	0;

	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	static Scenario	scenarios[] = 
	{
			{	"0", 0, false	}
#if 1
		,	{	"1", 1, false	}
		,	{	"10", 10, false	}
		,	{	"20", 20, false	}
#endif /* 0 */
		,	{	"-1", -1, true	}
		,	
	};

	{ for(size_t scx = 0; scx < STLSOFT_NUM_ELEMENTS(scenarios); ++scx)
	{
		Scenario const	&scenario	=	scenarios[scx];

		{ for(size_t WARMUPS = 2; WARMUPS; --WARMUPS)
		{
			counter.start();

			{ for(size_t INCREMENT = 0; INCREMENT < 100000; ++INCREMENT)
			{
				numAllocations	=	0;
				s_numCtors		=	0;
				s_numAssigns	=	0;

				string_array_t	sa;
				void const		*last			=	NULL;

				if(scenario.initialSize >= 0)
				{
					sa.SetSize(0, scenario.initialSize);
				}

				{ for(size_t i = 1; i <= N; ++i)
				{
					if(scenario.useAdaptor)
					{
						adaptor_t(sa).resize(i);
					}
					else
					{
						sa.SetSize(i);
					}

					if(sa.GetData() != last)
					{
						++numAllocations;

						last = sa.GetData();
					}

					adaptor_t	sai(sa);

#ifdef _DEBUG
					cout	<< "size=" << sai.size() 
							<< "; capacity=" << sai.capacity() 
							<< "; growIncrement=" << sai.grow_increment() 
							<< endl;
#else /* ? _DEBUG */
#endif /* _DEBUG */
				}}
			}}

			counter.stop();
		}}

		cout << endl;
		cout << "Scenario:     " << scenario.name << endl;
		cout << "#allocations: " << numAllocations << endl;
		cout << "#ctors:       " << s_numCtors << endl;
		cout << "#assigns:     " << s_numAssigns << endl;
		cout << "Time:         " << static_cast<unsigned long>(counter.get_milliseconds()) << endl;
	}}

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
        cout << "alloc_gran_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
