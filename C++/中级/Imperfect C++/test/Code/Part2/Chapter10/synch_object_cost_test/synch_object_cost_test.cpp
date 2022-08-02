/* /////////////////////////////////////////////////////////////////////////////
 * File:        synch_object_cost_test.cpp
 *
 * Purpose:     Implementation file for the synch_object_cost_test project.
 *
 * Created:     11th December 2003
 * Updated:     12th December 2003
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

#include <stdio.h>

#include <stlsoft.h>
#include <algorithm>

#if defined(__unix__) || \
    defined(unix)

#if defined(WIN32) && \
    defined(_MT)
# define _REENTRANT
#endif /* WIN32 && _MT */

#include <unixstl.h>

#include <unixstl_atomic_functions.h>

//unixstl_ns_using(atomic_increment)
//unixstl_ns_using(atomic_decrement)

#include <unixstl_performance_counter.h>
#include <unixstl_process_mutex.h>
#include <unixstl_spin_mutex.h>

unixstl_ns_using(performance_counter)
unixstl_ns_using(process_mutex)
unixstl_ns_using(spin_mutex)

#elif defined(WIN32) && \
      defined(_WIN32)

#include <winstl.h>

#include <winstl_performance_counter.h>
#include <winstl_process_mutex.h>
#include <winstl_spin_mutex.h>

winstl_ns_using(performance_counter)
winstl_ns_using(process_mutex)
winstl_ns_using(spin_mutex)

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef _DEBUG
const int   ITERATIONS  =   10000;
#else /* ? _DEBUG */
const int   ITERATIONS  =   10000000;
#endif /* _DEBUG */

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" int null_func_enter(void *pv);
extern "C" int null_func_leave(void *pv);
extern "C" int do_stuff(int volatile *pi);

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    performance_counter counter;

    printf("synch_object_cost_test: %d (%d)\n", __STLSOFT_COMPILER_LABEL_STRING, ITERATIONS);


    int                                 i;
    performance_counter::interval_type  null_cost;
#ifndef _UNIXSTL_INCL_H_UNIXSTL
    performance_counter::interval_type  atom_cost;
    performance_counter::interval_type  cs_cost;
    performance_counter::interval_type  sm_cost;
    performance_counter::interval_type  mx_cost;
    performance_counter::interval_type  sem_cost;
    performance_counter::interval_type  ev_cost;
#else /* ? !_UNIXSTL_INCL_H_UNIXSTL */
    performance_counter::interval_type  sm_cost;
    performance_counter::interval_type  mx_cost;
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */

#ifndef _UNIXSTL_INCL_H_UNIXSTL
    CRITICAL_SECTION    cs;

    ::InitializeCriticalSection(&cs);

    HANDLE              sem =   ::CreateSemaphore(NULL, 1, 1, NULL);
    HANDLE              ev  =   ::CreateEvent(NULL, false, true, NULL);
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */
    spin_mutex          sm;
    process_mutex       mx(true);

#ifndef _UNIXSTL_INCL_H_UNIXSTL
    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            null_func_enter(&i);
            do_stuff(&i);
            null_func_leave(&i);
        }
        counter.stop();
        null_cost = counter.get_milliseconds();

#ifndef _UNIXSTL_INCL_H_UNIXSTL
        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            ::InterlockedIncrement((LPLONG)&i);
            do_stuff(&i);
            ::InterlockedDecrement((LPLONG)&i);
        }
        counter.stop();
        atom_cost = counter.get_milliseconds();

        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            ::EnterCriticalSection(&cs);
            do_stuff(&i);
            ::LeaveCriticalSection(&cs);
        }
        counter.stop();
        cs_cost = counter.get_milliseconds();
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */

        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            sm.lock();
            do_stuff(&i);
            sm.unlock();
        }
        counter.stop();
        sm_cost = counter.get_milliseconds();

        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            mx.lock();
            do_stuff(&i);
            mx.unlock();
        }
        counter.stop();
        mx_cost = counter.get_milliseconds();

#ifndef _UNIXSTL_INCL_H_UNIXSTL
        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            ::WaitForSingleObject(sem, INFINITE);
            do_stuff(&i);
            ::ReleaseSemaphore(sem, 1, NULL);
        }
        counter.stop();
        sem_cost = counter.get_milliseconds();

        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
            ::WaitForSingleObject(ev, INFINITE);
            do_stuff(&i);
            ::SetEvent(ev);
        }
        counter.stop();
        ev_cost = counter.get_milliseconds();
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */
    }

    printf("No-op:             %lu\n", (unsigned long)null_cost);
#ifndef _UNIXSTL_INCL_H_UNIXSTL
    printf("Atomic Operations: %lu\n", (unsigned long)atom_cost);
    printf("Critical Section:  %lu\n", (unsigned long)cs_cost);
    printf("Spin mutex:        %lu\n", (unsigned long)sm_cost);
    printf("Mutex:             %lu\n", (unsigned long)mx_cost);
    printf("Semaphore:         %lu\n", (unsigned long)sem_cost);
    printf("Event:             %lu\n", (unsigned long)ev_cost);
#else /* ? !_UNIXSTL_INCL_H_UNIXSTL */
    printf("Spin mutex:        %lu\n", (unsigned long)sm_cost);
    printf("Mutex:             %lu\n", (unsigned long)mx_cost);
#endif /* !_UNIXSTL_INCL_H_UNIXSTL */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
