/* /////////////////////////////////////////////////////////////////////////////
 * File:        atomic_functions_test.cpp
 *
 * Purpose:     Implementation file for the atomic_functions_test project.
 *
 * Created:     14th November 2003
 * Updated:     11th December 2003
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

#include <stlsoft.h>

#include <winstl.h>

#include <winstl_atomic_functions.h>
#include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)


//#pragma intrinsic(atomic_preincrement, atomic_postincrement, atomic_predecrement, atomic_postdecrement)

/* /////////////////////////////////////////////////////////////////////////////
 * Atomic functions
 *
 * For X86
 */

#ifndef _WINSTL_NO_NAMESPACE
using winstl::atomic_preincrement;
using winstl::atomic_predecrement;
using winstl::atomic_postincrement;
using winstl::atomic_postdecrement;
using winstl::atomic_write;
using winstl::atomic_read;
using winstl::atomic_postadd;
using winstl::atomic_preadd;
#endif /* _WINSTL_NO_NAMESPACE */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    performance_counter counter;

    puts("atomic_functions_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
#ifdef _DEBUG
    long            MAX =   2;  
#else /* ? _DEBUG */
    long            MAX =   10000000/* 00 */;
#endif /* _DEBUG */
    int             i;
    long volatile   x   =   9;
    long volatile   y   =   0;
    long            z;

    _asm 
    {
        mov eax, 1
        lock xadd dword ptr [x], eax
    }

#if 1
    z   =   ++x;
#else /* ? 0 */
    _asm
    {
        lea ecx, [x]
        inc dword ptr [ecx]
//      mov dword ptr [z], dword ptr [ecx]
    }
#endif /* 0 */

    z   =   atomic_preincrement((__int32 volatile*)&x);

    z   =   ++x;

    z   =   InterlockedExchangeAdd((LPLONG)&x, 10);

    z   =   atomic_postadd((__int32 volatile*)&x, 10);

    z   =   x;

    z   =   atomic_write((__int32 volatile*)&x, 999);

    z   =   atomic_postincrement((__int32 volatile*)&x);

    z   =   atomic_predecrement((__int32 volatile*)&x);

    z   =   atomic_postdecrement((__int32 volatile*)&x);

    z   =   atomic_read((__int32 volatile*)&x);

    {
        for(i = 0,x = 0, y = 0; i < MAX; ++i)
        {
            long    x_  =   ::InterlockedIncrement((LPLONG)&x);
            long    y_  =   ::atomic_preincrement((__int32 volatile*)&y);

            if(x != y)
            {
                printf("Post increment (%d), failure; values:  %d != %d!\n", i, x, y);

                return 1;
            }

            if(x_ != y_)
            {
                printf("Post increment (%d), failure; returns: %d != %d!\n", i, x_, y_);

                return 1;
            }
        }
    }

    {
        counter.start();
        for(x = 0; ::InterlockedIncrement((LPLONG)&x) != MAX;)
        {}
        counter.stop();
        printf("InterlockedIncrement: %d\n", (int)counter.get_milliseconds());

        y += x;

        counter.start();
        for(; InterlockedDecrement((LPLONG)&x) != 0;)
        {}
        counter.stop();
        printf("InterlockedDecrement: %d\n", (int)counter.get_milliseconds());

        y += x;
    }

    {
        counter.start();
        for(x = 0; atomic_preincrement((__int32 volatile*)&x) != MAX;)
        {}
        counter.stop();
        printf("atomic_preincrement: %d\n", (int)counter.get_milliseconds());

        y += x;

        counter.start();
        for(; atomic_predecrement((__int32 volatile*)&x) != 0;)
        {}
        counter.stop();
        printf("atomic_predecrement: %d\n", (int)counter.get_milliseconds());

        y += x;
    }

    {
        counter.start();
        for(x = 0; atomic_postincrement((__int32 volatile*)&x) != MAX;)
        {}
        counter.stop();
        printf("atomic_postincrement: %d\n", (int)counter.get_milliseconds());

        y += x;

        counter.start();
        for(; atomic_postdecrement((__int32 volatile*)&x) != 0;)
        {}
        counter.stop();
        printf("atomic_postdecrement: %d\n", (int)counter.get_milliseconds());

        y += x;
    }

    printf("Complete\n");

#if 0
    y   =   atomic_read(&x);
    printf("%d\n", y);
#endif /* 0 */

    return y;
}

/* ////////////////////////////////////////////////////////////////////////// */
