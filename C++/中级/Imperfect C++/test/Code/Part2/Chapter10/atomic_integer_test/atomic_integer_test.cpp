/* /////////////////////////////////////////////////////////////////////////////
 * File:        atomic_integer_test.cpp
 *
 * Purpose:     Implementation file for the atomic_integer_test project.
 *
 * Created:     12th November 2003
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

#include <pthread.h>

#include <winstl.h>
#include <winstl_atomic_functions.h>

//#define   __STLSOFT_MULTITHREADED


/* ////////////////////////////////////////////////////////////////////////// */

#ifdef _DEBUG
const int   ITERATIONS  =   10000;
#else /* ? _DEBUG */
const int   ITERATIONS  =   1000000;
#endif /* _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 *
 */

#if 0
class atomic_integer_1
{
public:
    typedef long                value_type;
    typedef atomic_integer_1    class_type;
public:
    atomic_integer_1(value_type const &value = value_type())
#if 1
        : m_value(value)
    {}
#else /* ? 0 */
    {
        atomic_t value_ =   ATOMIC_INIT(value);
        m_value = 
    }
#endif /* 0 */



};

#endif /* 0 */


#if 0
#error Strategies:
#error (i) Have it return another atomic_integer and do all the normal things - this needs a mutex
#error (ii) Have a limited number of semantics. ++ returns a raw int, using atomic integer primitives
#error (ii) Have a fuller set of semantics; using mutexes
#endif /* 0 */

//#define   STRATEGY_1
#define STRATEGY_2
//#define   STRATEGY_3

#ifdef STRATEGY_1
class atomic_int_t
{
public:
    typedef stlsoft::int32_t    value_type;
    typedef atomic_integer      class_type;

public:
    atomic_int_t(value_type const &value = value_type())
        : m_value(value)
    {
        stlsoft_message_assert("Value out of range", value != sentinel_());
    }
};
#elif defined(STRATEGY_2)

class atomic_integer
#ifdef __SYNSOFT_DBS_COMPILER_SUPPORTS_PRAGMA_MESSAGE
# pragma message(_sscomp_fileline_message("This will be an STLSoft template, parameterised with an atomic_traits from winstl, unixstl"))
#endif /* __SYNSOFT_DBS_COMPILER_SUPPORTS_PRAGMA_MESSAGE */
{
public:
    typedef stlsoft::int32_t    value_type;
    typedef atomic_integer      class_type;

/// \name Construction
/// @{
public:
    /// Constructor
    ///
    ///
    /// \note This is deliberately not explicit
    atomic_integer(value_type const &value = value_type())
        : m_value(value)
    {}

    atomic_integer(atomic_integer const volatile &rhs)
        : m_value(rhs)
    {}

    class_type &operator =(value_type const &value)
    {
        (void)winstl::atomic_write(&m_value, value);

        return *this;
    }
/// @}

/// \name Access
/// @{
public:
    operator value_type const () const volatile
    {
        return winstl::atomic_read(&m_value);
    }
/// @}

/// \name Increment
/// @{
public:
    class_type volatile &operator ++() volatile
    {
        winstl::atomic_increment(&m_value);

        return *this;
    }
    const class_type volatile operator ++(int) volatile
    {
        return class_type(winstl::atomic_postincrement(&m_value));
    }

    class_type volatile &operator --() volatile
    {
        winstl::atomic_decrement(&m_value);

        return *this;
    }
    const class_type volatile operator --(int) volatile
    {
        return class_type(winstl::atomic_postdecrement(&m_value));
    }
/// @}

/// \name Arithmetic
/// @{
public:
    class_type volatile &operator += (value_type const &value) volatile
    {
        winstl::atomic_postadd(&m_value, value);

        return *this;
    }
    class_type volatile &operator -= (value_type const &value) volatile
    {
        winstl::atomic_postadd(&m_value, -value);

        return *this;
    }
/// @}

private:
    volatile value_type m_value;
};

#endif

/* ////////////////////////////////////////////////////////////////////////// */

volatile atomic_integer s_test;
volatile atomic_integer s_count;

void *thread_proc(void *)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        if(1 == ++s_test)
        {
            s_count += 1;
        }

        if((i % s_count) == 0)
        {
            ::Sleep((unsigned long)(i % 2));
        }

        --s_test;
    }

    return NULL;
}


struct thread_info
{
    pthread_t   tid;
};

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    (void)puts("atomic_integer_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    atomic_integer  x(-1);

    if(0 == ++x)
    {
        (void)printf("First time\n");
    }

    thread_info ti[10];
    size_t      i;

    for(i = 0; i < stlsoft_num_elements(ti); ++i)
    {
        if(0 != pthread_create(&ti[i].tid, NULL, thread_proc, NULL))
        {
            fprintf(stderr, "Failed to create thread\n");

            return 1;
        }
    }

    for(i = 0; i < stlsoft_num_elements(ti); ++i)
    {
        pthread_join(ti[i].tid, NULL);

        printf("Count: %d\n", (int)s_count);
    }

    printf("Count: %d; ITERATIONS: %d\n", (int)s_count, ITERATIONS);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
