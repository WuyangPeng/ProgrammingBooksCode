/* /////////////////////////////////////////////////////////////////////////////
 * File:        optimisation_1_test.cpp
 *
 * Purpose:     Implementation file for the optimisation_1_test project.
 *
 * Created:     19th November 2003
 * Updated:     3rd December 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
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

#include <windows.h>
#include <stdio.h>
#include <time.h>

#include <stlsoft.h>

#if !defined(WIN32) && \
    !defined(_WIN32)

# include <unixstl.h>

# include <unixstl_performance_counter.h>

unixstl_ns_using(performance_counter)

#else /* ? operating system */

# include <winstl.h>

# include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
//inline void tstrlen(T const *p)
inline T const *tstrlen(T const *p)
{
#if 0
    for(; *p; ++p)
    {}
#endif /* 0 */

    return ++p;
}

template <typename T>
inline T const volatile &func2(T const volatile &t)
{
  return t;
}

extern int volatile i = 0;

extern "C" void external_loop1(); 
extern "C" int external_loop2(); 

time_t inhibit_optimisation()
{
    static time_t   t   /* =    time(NULL) */;

    return t;
}



int main(int argc, char *argv[])
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    int                 iRet    =   0;
    performance_counter counter;

    int                 i;

    puts("optimisation_1_test: " __STLSOFT_COMPILER_LABEL_STRING);

    for(i = 1; i < argc; ++i)
    {
        const char  *arg    =   argv[i];

        if(arg[0] == '-')
        {
            if(arg[1] == '-')
            {
                /* -- arguments */
            }
            else
            {
                /* - arguments */
            }
        }
        else
        {
            /* other arguments */
        }
    }

    /* . */
    {
        counter.start();
        counter.stop();

        printf("No-op: %lu\n", (unsigned long)counter.get_milliseconds());
    }

    {
        char    x[] = "Hello";

        counter.start();
        for(int /* volatile */ i = 0; i < 0x7fffffff; ++i)
        {
//          /* int  y =  */tstrlen(x);
            iRet = func2(i);

            iRet = inhibit_optimisation();
        }
        counter.stop();

        printf("Empty loop: %lu\n", (unsigned long)counter.get_milliseconds());
    }

    {
        counter.start();
        external_loop1();
        counter.stop();

        printf("ext-loop1: %lu\n", (unsigned long)counter.get_milliseconds());
    }

    {
        counter.start();
        external_loop2();
        counter.stop();

        printf("ext-loop2: %lu\n", (unsigned long)counter.get_milliseconds());
    }

    {
        counter.start();
        iRet = external_loop2();
        counter.stop();

        printf("ext-loop2: %lu\n", (unsigned long)counter.get_milliseconds());
    }


    return iRet;
}


/* ////////////////////////////////////////////////////////////////////////// */
