/* /////////////////////////////////////////////////////////////////////////////
 * File:        spin_mutex_test.cpp
 *
 * Purpose:     Implementation file for the spin_mutex_test project.
 *
 * Created:     12th December 2003
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

#include <windows.h>
#include <stdio.h>

#include <stlsoft.h>

#include <pthread.h>

#if !defined(WIN32) && \
    !defined(_WIN32)

#include <unixstl.h>

#include <unixstl_performance_counter.h>
#include <unixstl_process_mutex.h>
#include <unixstl_spin_mutex.h>
#include <unixstl_thread_mutex.h>

unixstl_ns_using(performance_counter)
unixstl_ns_using(process_mutex)
unixstl_ns_using(spin_mutex)
unixstl_ns_using(thread_mutex)

#else /* ? operating system */

#include <winstl.h>

#include <winstl_performance_counter.h>
#include <winstl_process_mutex.h>
#include <winstl_spin_mutex.h>
#include <winstl_thread_mutex.h>

winstl_ns_using(performance_counter)
winstl_ns_using(process_mutex)
winstl_ns_using(spin_mutex)
winstl_ns_using(thread_mutex)

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" int do_stuff(int volatile *pi);

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef ITERATIONS
# ifdef _DEBUG
const int ITERATIONS    =   10000;
# else /* ? _DEBUG */
const int ITERATIONS    =   1000000;
# endif /* _DEBUG */
#endif /* !ITERATIONS */

/* ////////////////////////////////////////////////////////////////////////// */

spin_mutex      s_sm;
thread_mutex    s_tm;
process_mutex   s_pm;

void *sm_proc(void *)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        s_sm.lock();

        do_stuff(&i);

        s_sm.unlock();
    }

    return 0;
}

void *tm_proc(void *)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        s_tm.lock();

        do_stuff(&i);

        s_tm.unlock();
    }

    return 0;
}

void *pm_proc(void *)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        s_pm.lock();

        do_stuff(&i);

        s_pm.unlock();
    }

    return 0;
}


int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    performance_counter counter;

    puts("spin_mutex_test: " __STLSOFT_COMPILER_LABEL_STRING);

    // Lock them all here
    s_sm.lock();
    s_tm.lock();
    s_pm.lock();

    pthread_t       threads[6];

    pthread_create (&threads[0], /* &attr */ NULL, sm_proc, NULL);
    pthread_create (&threads[1], /* &attr */ NULL, sm_proc, NULL);
    pthread_create (&threads[2], /* &attr */ NULL, tm_proc, NULL);
    pthread_create (&threads[3], /* &attr */ NULL, tm_proc, NULL);
    pthread_create (&threads[4], /* &attr */ NULL, pm_proc, NULL);
    pthread_create (&threads[5], /* &attr */ NULL, pm_proc, NULL);

//  for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        // Spin mutex
        printf("Spin:");
        counter.start();
        s_sm.unlock();
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        counter.stop();

        printf("\t%lu\n", (unsigned long)counter.get_milliseconds());

        // Thread mutex
        printf("Thread:");
        counter.start();
        s_tm.unlock();
        pthread_join(threads[2], NULL);
        pthread_join(threads[3], NULL);
        counter.stop();

        printf("\t%lu\n", (unsigned long)counter.get_milliseconds());

        // Process mutex
        printf("Process:");
        counter.start();
        s_pm.unlock();
        pthread_join(threads[4], NULL);
        pthread_join(threads[5], NULL);
        counter.stop();

        printf("\t%lu\n", (unsigned long)counter.get_milliseconds());
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
