/* /////////////////////////////////////////////////////////////////////////////
 * File:        leaky_abstr_test.cpp
 *
 * Purpose:     Implementation file for the leaky_abstr_test project.
 *
 * Created:     7th November 2006
 * Updated:     7th November 2006
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



/* Standard C++ Header Files */
#include <exception>
#include <iostream>

/* Standard C Header Files */
#include <stdio.h>
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

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"leaky_abstr_test";

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
	using std::cout;
	using std::endl;

    int arr[] = {0,1};

    {
        int* p = &arr[0];
        ++p;
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = p+1;
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = p++ + 0;
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = p++ - 1;
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = &*p;
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = &(*(p + 1));
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = &(*(1 + p));
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = &p[1];
        cout << &arr[1] << " " << p << endl;
    }

    {
        int* p = &arr[0];
        p = &1[p];
        cout << &arr[1] << " " << p << endl;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	using std::cerr;
	using std::endl;

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
