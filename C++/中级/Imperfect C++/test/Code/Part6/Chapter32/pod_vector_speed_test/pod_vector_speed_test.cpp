/* /////////////////////////////////////////////////////////////////////////////
 * File:        pod_vector_speed_test.cpp
 *
 * Purpose:     Implementation file for the pod_vector_speed_test project.
 *
 * Created:     2nd January 2004
 * Updated:     3rd January 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
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
#include <stlsoft_pod_vector.h>
#include <stlsoft_malloc_allocator.h>   //  stlsoft's malloc_allocator

stlsoft_ns_using(malloc_allocator)
stlsoft_ns_using(pod_vector)


#if defined(unix) || \
    defined(__unix__)

#include <unixstl.h>

#include <unixstl_performance_counter.h>

unixstl_ns_using(performance_counter)

#elif defined(WIN32) || \
    defined(_WIN32)

#include <winstl.h>

#include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

#include <vector>

stlsoft_ns_using_std(vector)

/* ////////////////////////////////////////////////////////////////////////// */

const size_t    INTERNAL_SIZE   =   96;

typedef malloc_allocator<int>                       int_ator_t;
typedef vector<int, int_ator_t>                     int_vector_t;
typedef pod_vector<int, int_ator_t, INTERNAL_SIZE>  int_pvector_t;


/* ////////////////////////////////////////////////////////////////////////// */

template <class V>
unsigned long test_push_front(int iterations, int num_insertions)
{
    unsigned long   ret =   0;

    for(int i = 0; i < iterations; ++i)
    {
//      int volatile    one =   1;
        V               v;
//      int volatile    two =   2;

        for(int j = 0; j < num_insertions; ++j)
        {
            v.insert(v.begin(), j);

#if 0
            if(1 != one)
            {
                printf("one!!\n");
            }
            if(2 != two)
            {
                printf("two!!\n");
            }
#endif /* 0 */

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}

template <class V>
unsigned long test_push_back(int iterations, int num_insertions)
{
    unsigned long   ret =   0;

    for(int i = 0; i < iterations; ++i)
    {
        V   v;

        for(int j = 0; j < num_insertions; ++j)
        {
            v.insert(v.end(), j);

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}

template <class V>
unsigned long test_push_back_reserve(int iterations, int num_insertions)
{
    unsigned long   ret =   0;

    for(int i = 0; i < iterations; ++i)
    {
        V   v;

        v.reserve(num_insertions);

        for(int j = 0; j < num_insertions; ++j)
        {
            v.insert(v.end(), j);

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}

template <class V>
unsigned long test_erase_front(int iterations, int num_erasures)
{
    unsigned long   ret =   0;

    for(int i = 0; i < iterations; ++i)
    {
        V   v(num_erasures);

        for(int j = 0; j < num_erasures; ++j)
        {
            v.erase(v.begin());

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}

template <class V>
unsigned long test_erase_back(int iterations, int num_erasures)
{
    unsigned long   ret =   0;

    for(int i = 0; i < iterations; ++i)
    {
        V   v(num_erasures);

        for(int j = 0; j < num_erasures; ++j)
        {
#if defined(__STLSOFT_COMPILER_IS_GCC) || \
    defined(__STLSOFT_COMPILER_IS_MWERKS)
            ss_typename_type_k V::iterator  it = v.begin();

            stlsoft_ns_qual_std(advance)(it, v.size() - 1);
#else /* ? 0 */
            ss_typename_type_k V::iterator  it = &v[v.size() - 1];
#endif /* 0 */

            v.erase(it);

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}

template <class V>
unsigned long test_insert_block_back(int iterations, int num_insertions)
{
    unsigned long   ret =   0;

    V       ints_;
    V const &ints   =   ints_;

    ints_.push_back(1);
    ints_.push_back(2);
    ints_.push_back(3);
    ints_.push_back(4);

    for(int i = 0; i < iterations; ++i)
    {
        V   v;

        for(int j = 0; j < num_insertions; ++j)
        {
            v.insert(v.end(), ints.begin(), ints.end());

//          ret += v[0];
            ret += j;
        }
    }

    return ret;
}



/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    int                 iRet            =   0;
    performance_counter counter;
    int                 i;
#ifdef _DEBUG
    int                 ITERATIONS      =   10;
#else /* ? _DEBUG */
    int                 ITERATIONS      =   50000;
#endif /* _DEBUG */
    int                 NUM_INSERTIONS  =   1000;

    puts("pod_vector_speed_test: " __STLSOFT_COMPILER_LABEL_STRING);

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

#if defined(WIN32)
# ifndef BELOW_NORMAL_PRIORITY_CLASS
#  define BELOW_NORMAL_PRIORITY_CLASS   IDLE_PRIORITY_CLASS
# endif /* !BELOW_NORMAL_PRIORITY_CLASS */
# ifndef ABOVE_NORMAL_PRIORITY_CLASS
#  define ABOVE_NORMAL_PRIORITY_CLASS   HIGH_PRIORITY_CLASS
# endif /* !ABOVE_NORMAL_PRIORITY_CLASS */

    ::SetPriorityClass( ::GetCurrentProcess()
# ifdef _DEBUG
                    ,   BELOW_NORMAL_PRIORITY_CLASS
# else /* ? _DEBUG */
                    ,   ABOVE_NORMAL_PRIORITY_CLASS
# endif /* _DEBUG */
                    );
#endif /* WIN32 */

    /* . */
#ifdef _DEBUG
    test_push_front<int_pvector_t>(1, 100);
    test_push_back<int_pvector_t>(1, 100);
    test_push_back_reserve<int_pvector_t>(1, 100);
    test_erase_front<int_pvector_t>(1, 100);
    test_erase_back<int_pvector_t>(1, 100);
    test_insert_block_back<int_pvector_t>(1, 100);
#else /* ? _DEBUG */
#endif /* _DEBUG */

    const int   NUM_INC =   50;
    const int   NUM_MIN =   50;
    const int   NUM_MAX =   150;

#if 0
    try
    {
#endif /* 0 */
        for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
        {
#if 1
            for(int num_push_front = NUM_MIN; num_push_front < NUM_MAX; num_push_front += NUM_INC)
            {
                counter.start();
                test_push_front<int_vector_t>(ITERATIONS, num_push_front);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, push-front (%d) \t%lu\n", num_push_front, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_push_front<int_pvector_t>(ITERATIONS, num_push_front);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, push-front (%d) \t%lu\n", num_push_front, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
#endif /* 0 */
        
            for(int num_push_back = NUM_MIN; num_push_back < NUM_MAX; num_push_back += NUM_INC)
            {
                counter.start();
                test_push_back<int_vector_t>(ITERATIONS, num_push_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, push-back (%d) \t%lu\n", num_push_back, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_push_back<int_pvector_t>(ITERATIONS, num_push_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, push-back (%d) \t%lu\n", num_push_back, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
        
            for(int num_push_back_reserve = NUM_MIN; num_push_back_reserve < NUM_MAX; num_push_back_reserve += NUM_INC)
            {
                counter.start();
                test_push_back_reserve<int_vector_t>(ITERATIONS, num_push_back_reserve);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, push-back-reserve (%d) \t%lu\n", num_push_back_reserve, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_push_back_reserve<int_pvector_t>(ITERATIONS, num_push_back_reserve);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, push-back-reserve (%d) \t%lu\n", num_push_back_reserve, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
        
            for(int num_erasures_front = NUM_MIN; num_erasures_front < NUM_MAX; num_erasures_front += NUM_INC)
            {
                counter.start();
                test_erase_front<int_vector_t>(ITERATIONS, num_erasures_front);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, erase-front (%d) \t%lu\n", num_erasures_front, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_erase_front<int_pvector_t>(ITERATIONS, num_erasures_front);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, erase-front (%d) \t%lu\n", num_erasures_front, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
        
            for(int num_erasures_back = NUM_MIN; num_erasures_back < NUM_MAX; num_erasures_back += NUM_INC)
            {
                counter.start();
                test_erase_back<int_vector_t>(ITERATIONS, num_erasures_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, erase-back (%d) \t%lu\n", num_erasures_back, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_erase_back<int_pvector_t>(ITERATIONS, num_erasures_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, erase-back (%d) \t%lu\n", num_erasures_back, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
        
            for(int num_block_insertions_back = NUM_MIN; num_block_insertions_back < NUM_MAX; num_block_insertions_back += NUM_INC)
            {
                counter.start();
                test_insert_block_back<int_vector_t>(ITERATIONS, num_block_insertions_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("std::vector, insert-block-back (%d) \t%lu\n", num_block_insertions_back, (unsigned long)counter.get_milliseconds());
                }
        
                counter.start();
                test_insert_block_back<int_pvector_t>(ITERATIONS, num_block_insertions_back);
                counter.stop();
                if(1 == WARMUPS)
                {
                    printf("stlsoft::pod_vector, insert-block-back (%d) \t%lu\n", num_block_insertions_back, (unsigned long)counter.get_milliseconds());
                }

                if(1 == WARMUPS)
                {
                    printf("\n");
                    printf("\n");
                }
            }
        }
#if 0
    }
    catch(stlsoft_ns_qual_std(bad_alloc) &x)
    {
        puts(x.what());
    }
#endif /* 0 */

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
