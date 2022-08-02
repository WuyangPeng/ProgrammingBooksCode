/* /////////////////////////////////////////////////////////////////////////////
 * File:        optional_collections_methods_test.cpp
 *
 * Purpose:     Implementation file for the optional_collections_methods_test project.
 *
 * Created:     14th December 2005
 * Updated:     14th December 2005
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


/* Standard C++ Header Files */
#include <exception>
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#endif /* 0 */

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

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

/* ////////////////////////////////////////////////////////////////////////// */

class NoCount
{
public:
	void Common()
	{
		printf("NoCount::Common()\n");
	}
};

class CountProp
{
public:
	void Common()
	{
		printf("CountProp::Common()\n");
	}

	long get_Count()
	{
		printf("CountProp::get_Count()\n");
	}
};

class CountMethod
{
public:
	void Common()
	{
		printf("CountMethod::Common()\n");
	}

	long Count()
	{
		printf("CountMethod::Count()\n");
	}
};

/* ////////////////////////////////////////////////////////////////////////// */





struct IndirectRoot
{
public:
	void get_Count(IndirectRoot*, IndirectRoot**, IndirectRoot***, IndirectRoot****);
	void Count(IndirectRoot*, IndirectRoot**, IndirectRoot***, IndirectRoot****);
};

struct IndirectChild
	: IndirectRoot
{
};

template <class I>
struct Count_Tester
	: public IndirectChild
	, public I
{
};



template <typename C>
char[1] call_Count(long (C::*);


template <class C>
class Wrapper
{
public:
	Wrapper(C *obj)
		: m_obj(obj)
	{}

public:
	void do_Common()
	{
		m_obj->Common();
	}

public:
	long do_Count()
	{
//		typedef Count_Tester<C>		tester_t;

//		&tester_t::get_Count;

//		return call_Count(m_obj);

		return 0;
	}

private:
	C	*m_obj;
};

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
	/* . */

	{
		typedef Wrapper<NoCount>	NoCount_wrapper;

		NoCount				obj;
		NoCount_wrapper		w(&obj);

		w.do_Common();
	}

	{
		typedef Wrapper<CountProp>	CountProp_wrapper;

		CountProp			obj;
		CountProp_wrapper	w(&obj);

		w.do_Common();

		w.do_Count();
	}

	{
		typedef Wrapper<CountMethod>	CountMethod_wrapper;

		CountMethod			obj;
		CountMethod_wrapper	w(&obj);

		w.do_Common();
	}

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
		puts("optional_collections_methods_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


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
