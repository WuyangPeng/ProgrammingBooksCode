/* /////////////////////////////////////////////////////////////////////////////
 * File:        indirection_problem_test.cpp
 *
 * Purpose:     Implementation file for the indirection_problem_test project.
 *
 * Created:     26th October 2006
 * Updated:     26th October 2006
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
#include <stlsoft/smartptr/shared_ptr.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <list>

using std::cerr;
using std::cin;
using std::cout;
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

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"indirection_problem_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

struct X
{
	int	x;

	X(int x)
		: x(x)
	{}
};

typedef stlsoft::shared_ptr<X>	X_ptr;
typedef std::list<X_ptr>		X_ptrs_t;
typedef std::list<X*>			X_ptrs2_t;

class ci_t
{
public:
	typedef X					value_type;
	typedef value_type const	*pointer;

public:
	ci_t()
		: m_x(0)
	{}

public:
	pointer operator ->() const
	{
		return &m_x;
	}

private:
	X	m_x;
};

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		X_ptrs_t	ptrs;

		ptrs.push_back(X_ptr(new X(1)));
		ptrs.push_back(X_ptr(new X(2)));

		{ for(X_ptrs_t::const_iterator b = ptrs.begin(); b != ptrs.end(); ++b)
		{
//			cout << b->x << endl;

			X const	*pX	=	b.operator ->()->operator ->();

			cout << b.operator ->()->operator ->()->x << endl;
		}}
	}

	{
		X_ptrs2_t	ptrs;

		ptrs.push_back((new X(1)));
		ptrs.push_back((new X(2)));

		{ for(X_ptrs2_t::const_iterator b = ptrs.begin(); b != ptrs.end(); ++b)
		{
			X const	*pX	=	*b.operator ->();

//			cout << b->x << endl;
		}}
	}

	ci_t	ci;

	ci->x;

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
        cout << "indirection_problem_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

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
