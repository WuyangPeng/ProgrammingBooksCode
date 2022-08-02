/* /////////////////////////////////////////////////////////////////////////////
 * File:        indirection_problem_2_test.cpp
 *
 * Purpose:     Implementation file for the indirection_problem_2_test project.
 *
 * Created:     5th November 2006
 * Updated:     5th November 2006
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
#include <stlsoft/smartptr/shared_ptr.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#if 0
#include <algorithm>
#include <iterator>
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

class Value
{
public:
	Value(char const *s)
		: m_s(s)
	{}

public:
	void release()
	{
		m_s = "";
	}

public:
	char const *c_str() const
	{
		return m_s.c_str();
	}

private:
	std::string	m_s;
};

typedef stlsoft::shared_ptr<Value>	Value_ptr;

//typedef stlsoft::ref_ptr<

/* /////////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"indirection_problem_2_test";

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

static void f0()
{
	typedef std::list<Value_ptr>	Values_t;
//	typedef std::vector<Value_ptr>	Values_t;

	typedef Values_t				C;
	typedef Values_t::iterator		I;

	C	cont_;

	cont_.push_back(Value_ptr(new Value("abc")));

    /* . */
	C   cont = cont_;
	I   i    = cont.begin();
//	i->release();
	i->close();
}

static void f1()
{
//	typedef std::list<Value*>		Values_t;
	typedef std::vector<Value*>		Values_t;

	typedef Values_t				C;
	typedef Values_t::iterator		I;

	C	cont_;

	cont_.push_back(new Value("abc"));

    /* . */
	C   cont = cont_;
	I   i    = cont.begin();
//	i->release();
//	i->close();
	i->c_str();
}

static int main_(int /* argc */, char ** /*argv*/)
{
	f0();
	f1();

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
        puts("indirection_problem_2_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
