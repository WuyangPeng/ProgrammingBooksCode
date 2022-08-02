/* /////////////////////////////////////////////////////////////////////////////
 * File:        scoped_handle_test.cpp
 *
 * Purpose:     Implementation file for the scoped_handle_test project.
 *
 * Created:     6th November 2006
 * Updated:     6th November 2006
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
#include <stlsoft/smartptr/scoped_handle.hpp>

#include <unixstl/unixstl.h>


/* UNIXEm Header Files */
#include <unixem/unixem.h>
#include <unixem/implicit_link.h>

/* Standard C++ Header Files */
#include <exception>

/* Standard C Header Files */
#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
# include <fcntl.h>
# include <io.h>
#endif /* _MSC_VER) && _DEBUG */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

//extern "C" const char	FE_SIMPLE_PROCESS_IDENTITY[]	=	"scoped_handle_test";

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
    {
        int                                 fh = ::open("filename.ext", O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);

        if(-1 != fh)
        {
            ::stlsoft::scoped_handle<int>   h1(fh, ::close, -1);

			::write(fh, "abc", 3);
        }
    }

    {
         FILE                               *file = ::fopen("file.ext", "r");
         ::stlsoft::scoped_handle<FILE*>    h2(file, ::fclose);
    }

    {
        void                                *pv =   ::malloc(100);
        ::stlsoft::scoped_handle<void*>     h3(pv, ::free);
    }

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
        puts("scoped_handle_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        res = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        fprintf(stderr, "Unhandled error: %s\n", x.what());

        res = EXIT_FAILURE;
    }
    catch(...)
    {
        fprintf(stderr, "Unhandled unknown error\n");

        res = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return res;
}

/* ////////////////////////////////////////////////////////////////////////// */
