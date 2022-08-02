/* /////////////////////////////////////////////////////////////////////////////
 * File:        synchronized_test.cpp
 *
 * Purpose:     Implementation file for the synchronized_test project.
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

#include <stdio.h>
#include <pthread.h>

#include <stlsoft.h>
#include <stlsoft_lock_scope.h>

#if !defined(WIN32) && \
    !defined(_WIN32)

# include <unixstl.h>

# include <unixstl_thread_mutex.h>

unixstl_ns_using(thread_mutex)

#else /* ? operating system */

#include <winstl.h>

# include <winstl_thread_mutex.h>

winstl_ns_using(thread_mutex)

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

#if 0

#define SYNCHRONIZED_BEGIN(T, v)    \
    { stlsoft::lock_scope<T> __lock__(v);

#define SYNCHRONIZED_END()  \
    }

#else /* ? 0 */

template <typename T>
struct synchronized_lock
    : public T
{
public:
    synchronized_lock()
        : m_bLooped(false)
    {}
#if 1
    template <typename U>
    synchronized_lock(U &u)
        : T(u)
        , m_bLooped(false)
    {}
#endif /* 0 */

public:
    operator bool () const
    {
        return !m_bLooped;
    }

public:
    void end_loop()
    {
        m_bLooped = true;
    }

private:
    bool    m_bLooped;
};

#define __concat__(x, y)    x ## y
#define _concat_(x, y)  __concat__(x, y)

// -I%PTHREADS_WIN32% ..\synchronized_test.cpp

#if defined(__STLSOFT_COMPILER_IS_GCC)  || \
    defined(__STLSOFT_COMPILER_IS_VECTORC)
# define SYNCHRONIZED_BEGIN(T, v)   \
    for(synchronized_lock<stlsoft::lock_scope<T> > _concat_(__lock__, __LINE__)  (v); _concat_(__lock__, __LINE__); _concat_(__lock__, __LINE__)  .end_loop())
#elif defined(__STLSOFT_COMPILER_IS_BORLAND)  || \
      defined(__STLSOFT_COMPILER_IS_COMO)  || \
      defined(__STLSOFT_COMPILER_IS_DMC)  || \
      defined(__STLSOFT_COMPILER_IS_INTEL)  || \
      defined(__STLSOFT_COMPILER_IS_MSVC)  || \
      defined(__STLSOFT_COMPILER_IS_MWERKS)  || \
      defined(__STLSOFT_COMPILER_IS_WATCOM)
# define SYNCHRONIZED_BEGIN(T, v)   \
    for(synchronized_lock<stlsoft::lock_scope<T> > _concat_(__lock__, __LINE__) ## (v); _concat_(__lock__, __LINE__); _concat_(__lock__, __LINE__) ## .end_loop())
#else /* ? compiler */
# error Compiler not discriminated
#endif /* compiler */

#define SYNCHRONIZED_END()

#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef _DEBUG
const int ITERATIONS    =   10000;
#else /* ? _DEBUG */
const int ITERATIONS    =   10000000;
#endif /* _DEBUG */

/* ////////////////////////////////////////////////////////////////////////// */

thread_mutex    tmx;
int             x;

void *thread_proc(void *pv)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        SYNCHRONIZED_BEGIN(thread_mutex, tmx)
        {
            (NULL == pv) ? ++x : --x;

            if(0 == (i % 1000))
            {
                ::Sleep(0);
            }
        }
        SYNCHRONIZED_END()

        SYNCHRONIZED_BEGIN(thread_mutex, tmx)
        {
            (NULL == pv) ? ++x : --x;

            if(0 == (i % 1000))
            {
                ::Sleep(0);
            }
        }
        SYNCHRONIZED_END()
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("synchronized_test: " __STLSOFT_COMPILER_LABEL_STRING);

    int i   =   10;
    int j   =   20;

    i ^= j ^= i ^= j;

    /* . */
    pthread_t   ids[4];

    pthread_create(&ids[0], NULL, thread_proc, NULL);
    pthread_create(&ids[1], NULL, thread_proc, ids);
    pthread_create(&ids[2], NULL, thread_proc, NULL);
    pthread_create(&ids[3], NULL, thread_proc, ids);

    pthread_join(ids[0], NULL);
    pthread_join(ids[1], NULL);
    pthread_join(ids[2], NULL);
    pthread_join(ids[3], NULL);

    printf("x: %d\n", x);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
