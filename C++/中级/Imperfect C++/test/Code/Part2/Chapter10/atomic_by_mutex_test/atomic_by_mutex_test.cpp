/* /////////////////////////////////////////////////////////////////////////////
 * File:        atomic_by_mutex_test.cpp
 *
 * Purpose:     Implementation file for the atomic_by_mutex_test project.
 *
 * Created:     19th November 2003
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
#include <stlsoft_nulldef.h>

#include <pthread.h>

#include <stlsoft_lock_scope.h>

stlsoft_ns_using(lock_scope);

#if defined(unix) || \
    defined(__unix__)

# include <unixstl.h>

# include <unixstl_performance_counter.h>

unixstl_ns_using(performance_counter)

# include <unixstl_process_mutex.h>
# include <unixstl_spin_mutex.h>
# include <unixstl_thread_mutex.h>

unixstl_ns_using(process_mutex)
unixstl_ns_using(spin_mutex)
unixstl_ns_using(thread_mutex)

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl.h>

# include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)

# include <winstl_process_mutex.h>
# include <winstl_spin_mutex.h>
# include <winstl_thread_mutex.h>

winstl_ns_using(process_mutex)
winstl_ns_using(spin_mutex)
winstl_ns_using(thread_mutex)

#include <process.h>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef _DEBUG
const int               ITERATIONS  =   100;
#else /* ? _DEBUG */
const int               ITERATIONS  =   100000/* 00 */;
#endif /* _DEBUG */

const size_t    ARRAY_SIZE  =   16;
const size_t    NUM_THREADS =   16;
const size_t    NUM_MUTEXES =   4;

//typedef   process_mutex   mutex_t;
//typedef   spin_mutex  mutex_t;
typedef thread_mutex    mutex_t;

struct ThreadInfo
{
    int             ITERATIONS;
    int volatile    *(*vs)[ARRAY_SIZE];
    int (__stdcall  *pfn)(int volatile *);
};

/* ////////////////////////////////////////////////////////////////////////// */

int __stdcall Atomic_PreIncrement_ByMx1(int volatile *);
int __stdcall Atomic_PreDecrement_ByMx1(int volatile *);

int __stdcall Atomic_PreIncrement_ByMx2(int volatile *);
int __stdcall Atomic_PreDecrement_ByMx2(int volatile *);

int __stdcall Atomic_PreIncrement_ByMx3(int volatile *);
int __stdcall Atomic_PreDecrement_ByMx3(int volatile *);

/* ////////////////////////////////////////////////////////////////////////// */

unsigned __stdcall proc(ThreadInfo &info)
{
    for(int i = 0; i < info.ITERATIONS; ++i)
    {
        for(int j = 0; j < ARRAY_SIZE; ++j)
        {
            (*info.pfn)((*info.vs)[j]);
        }
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    performance_counter     counter;

    printf("atomic_by_mutex_test (%s); array: %d; threads: %d; mutexes: %d\n", __STLSOFT_COMPILER_LABEL_STRING, ARRAY_SIZE, NUM_THREADS, NUM_MUTEXES);

    /* . */
    int             i;
    HANDLE          threads[NUM_THREADS];
    ThreadInfo      infos[2];
    unsigned        ids[NUM_THREADS];
    int volatile    *vs[ARRAY_SIZE];

    for(i = 0; i < stlsoft_num_elements(vs); ++i)
    {
        vs[i] = new int(-1);
#ifdef _DEBUG
        printf("0x%08x\n", vs[i]);
#endif /* _DEBUG */
    }
#ifdef _DEBUG
    printf("Sizeof(ThreadInfo): %u\n", sizeof(ThreadInfo));
#endif /* _DEBUG */

    // Mx1
    {
        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            *vs[i] = 0;
        }
        infos[0].ITERATIONS =   ITERATIONS;
        infos[0].vs         =   &vs;
        infos[0].pfn        =   Atomic_PreIncrement_ByMx1;
        infos[1].ITERATIONS =   ITERATIONS;
        infos[1].vs         =   &vs;
        infos[1].pfn        =   Atomic_PreDecrement_ByMx1;

        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            stlsoft_assert(vs[i] == (*infos[0].vs)[i]);
            stlsoft_assert(vs[i] == (*infos[1].vs)[i]);
        }
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            threads[i] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))proc, &infos[i % 2], CREATE_SUSPENDED, &ids[i]);
        }

        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::SetThreadPriority(threads[i], THREAD_PRIORITY_ABOVE_NORMAL);
        }

        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
        counter.start();
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::ResumeThread(threads[i]);
        }

        ::WaitForMultipleObjects(stlsoft_num_elements(threads), &threads[0], true, INFINITE);
        counter.stop();
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::CloseHandle(threads[i]);
        }

        int v;
        for(i = 0, v = 0; i < stlsoft_num_elements(vs); ++i)
        {
            v += *vs[i];
        }

        printf("Mx1:\t%d\t%lu\n", v, (unsigned long)counter.get_milliseconds());
    }

    // Mx2
    {
        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            *vs[i] = 0;
        }
        infos[0].ITERATIONS =   ITERATIONS;
        infos[0].vs         =   &vs;
        infos[0].pfn        =   Atomic_PreIncrement_ByMx2;
        infos[1].ITERATIONS =   ITERATIONS;
        infos[1].vs         =   &vs;
        infos[1].pfn        =   Atomic_PreDecrement_ByMx2;

        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            stlsoft_assert(vs[i] == (*infos[0].vs)[i]);
            stlsoft_assert(vs[i] == (*infos[1].vs)[i]);
        }
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            threads[i] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))proc, &infos[i % 2], CREATE_SUSPENDED, &ids[i]);
        }

        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::SetThreadPriority(threads[i], THREAD_PRIORITY_ABOVE_NORMAL);
        }

        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
        counter.start();
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::ResumeThread(threads[i]);
        }

        ::WaitForMultipleObjects(stlsoft_num_elements(threads), &threads[0], true, INFINITE);
        counter.stop();
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::CloseHandle(threads[i]);
        }

        int v;
        for(i = 0, v = 0; i < stlsoft_num_elements(vs); ++i)
        {
            v += *vs[i];
        }

        printf("Mx2:\t%d\t%lu\n", v, (unsigned long)counter.get_milliseconds());
    }

    // Mx3
    {
        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            *vs[i] = 0;
        }
        infos[0].ITERATIONS =   ITERATIONS;
        infos[0].vs         =   &vs;
        infos[0].pfn        =   Atomic_PreIncrement_ByMx3;
        infos[1].ITERATIONS =   ITERATIONS;
        infos[1].vs         =   &vs;
        infos[1].pfn        =   Atomic_PreDecrement_ByMx3;

        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            stlsoft_assert(vs[i] == (*infos[0].vs)[i]);
            stlsoft_assert(vs[i] == (*infos[1].vs)[i]);
        }
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            threads[i] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))proc, &infos[i % 2], CREATE_SUSPENDED, &ids[i]);
        }

        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::SetThreadPriority(threads[i], THREAD_PRIORITY_ABOVE_NORMAL);
        }

        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
        counter.start();
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::ResumeThread(threads[i]);
        }

        ::WaitForMultipleObjects(stlsoft_num_elements(threads), &threads[0], true, INFINITE);
        counter.stop();
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::CloseHandle(threads[i]);
        }

        int v;
        for(i = 0, v = 0; i < stlsoft_num_elements(vs); ++i)
        {
            v += *vs[i];
        }

        printf("Mx3:\t%d\t%lu\n", v, (unsigned long)counter.get_milliseconds());
    }

    // Interlocked
    {
        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            *vs[i] = 0;
        }
        infos[0].ITERATIONS =   ITERATIONS;
        infos[0].vs         =   &vs;
        infos[0].pfn        =   (int (__stdcall *)(int volatile *))InterlockedIncrement;
        infos[1].ITERATIONS =   ITERATIONS;
        infos[1].vs         =   &vs;
        infos[1].pfn        =   (int (__stdcall *)(int volatile *))InterlockedDecrement;

        for(i = 0; i < stlsoft_num_elements(vs); ++i)
        {
            stlsoft_assert(vs[i] == (*infos[0].vs)[i]);
            stlsoft_assert(vs[i] == (*infos[1].vs)[i]);
        }
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            threads[i] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))proc, &infos[i % 2], CREATE_SUSPENDED, &ids[i]);
        }

        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::SetThreadPriority(threads[i], THREAD_PRIORITY_ABOVE_NORMAL);
        }

        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
        counter.start();
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::ResumeThread(threads[i]);
        }

        ::WaitForMultipleObjects(stlsoft_num_elements(threads), &threads[0], true, INFINITE);
        counter.stop();
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
        for(i = 0; i < stlsoft_num_elements(threads); ++i)
        {
            ::CloseHandle(threads[i]);
        }

        int v;
        for(i = 0, v = 0; i < stlsoft_num_elements(vs); ++i)
        {
            v += *vs[i];
        }

        printf("Interlocked:\t%d\t%lu\n", v, (unsigned long)counter.get_milliseconds());
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace Mx1
{
    mutex_t mx;
};

int __stdcall Atomic_PreIncrement_ByMx1(int volatile *v)
{
    lock_scope<mutex_t> lock(Mx1::mx);

    return ++*(v);
}

int __stdcall Atomic_PreDecrement_ByMx1(int volatile *v)
{
    lock_scope<mutex_t> lock(Mx1::mx);

    return --(*v);
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace Mx2
{
    mutex_t mx_a;
    mutex_t mx_b;
};

int __stdcall Atomic_PreIncrement_ByMx2(int volatile *v)
{
    lock_scope<mutex_t> lock(Mx2::mx_a);

    return ++*(v);
}

int __stdcall Atomic_PreDecrement_ByMx2(int volatile *v)
{
    lock_scope<mutex_t> lock(Mx2::mx_b);

    return --(*v);
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace Mx3
{
    mutex_t mxs[NUM_MUTEXES];

    const size_t    SHIFT   =   7;

    inline size_t index_from_ptr(void volatile *v, size_t range)
    {
        return (((unsigned)v) >> Mx3::SHIFT) % range;
    }
};

int __stdcall Atomic_PreIncrement_ByMx3(int volatile *v)
{
    size_t          index   =   Mx3::index_from_ptr(v, stlsoft_num_elements(Mx3::mxs));

#ifdef _DEBUG
    printf("index: %u\n", index);
#endif /* _DEBUG */

    lock_scope<mutex_t> lock(Mx3::mxs[index]);

    return ++*(v);
}

int __stdcall Atomic_PreDecrement_ByMx3(int volatile *v)
{
    size_t          index   =   Mx3::index_from_ptr(v, stlsoft_num_elements(Mx3::mxs));

    lock_scope<mutex_t> lock(Mx3::mxs[index]);

    return --(*v);
}

/* ////////////////////////////////////////////////////////////////////////// */

void unlock_instance(mutex_t &mx)
{
    mx.unlock();
}

/* ////////////////////////////////////////////////////////////////////////// */
