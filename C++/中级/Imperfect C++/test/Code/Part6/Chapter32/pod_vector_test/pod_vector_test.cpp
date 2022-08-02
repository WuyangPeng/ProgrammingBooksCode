/* /////////////////////////////////////////////////////////////////////////////
 * File:        pod_vector_test.cpp
 *
 * Purpose:     Implementation file for the pod_vector_test project.
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

#include <stdio.h>

#include <stlsoft.h>
#include <stlsoft_pod_vector.h>
#include <stlsoft_malloc_allocator.h>   //  stlsoft's malloc_allocator

stlsoft_ns_using(auto_buffer)
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

#ifndef __STLSOFT_COMPILER_IS_WATCOM
# include <vector>

stlsoft_ns_using_std(vector)
#endif /* !__STLSOFT_COMPILER_IS_WATCOM */

/* ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
 * alloca?
 */

#ifdef TEST_ALLOCA
# undef TEST_ALLOCA
#endif /* TEST_ALLOCA */

#if defined(__STLSOFT_COMPILER_IS_BORLAND) || \
    defined(__STLSOFT_COMPILER_IS_COMO) || \
    defined(__STLSOFT_COMPILER_IS_DMC) || \
    defined(__STLSOFT_COMPILER_IS_GCC) || \
    defined(__STLSOFT_COMPILER_IS_INTEL) || \
    defined(__STLSOFT_COMPILER_IS_MWERKS) || \
    defined(__STLSOFT_COMPILER_IS_MSVC) || \
    defined(__STLSOFT_COMPILER_IS_WATCOM)
# define TEST_ALLOCA
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////////
 * VLA?
 */

#ifdef TEST_VLA
# undef TEST_VLA
#endif /* TEST_VLA */

#if defined(__STLSOFT_COMPILER_IS_COMO) || \
    defined(__STLSOFT_COMPILER_IS_DMC) || \
    defined(__STLSOFT_COMPILER_IS_GCC)
# define TEST_VLA
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////////
 * printf() format string
 */

#if defined(__STLSOFT_COMPILER_IS_BORLAND) || \
    defined(__STLSOFT_COMPILER_IS_GCC) || \
    defined(__STLSOFT_COMPILER_IS_INTEL) || \
    defined(__STLSOFT_COMPILER_IS_MSVC) || \
    defined(__STLSOFT_COMPILER_IS_WATCOM)
# define test_printf_fmt    "%I64d"
#else
# define test_printf_fmt    "%lld"
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////////
 * Constants and definitions
 */

const int       WARMUPS                     =   2;
#if 0
const size_t    AUTO_BUFFER_INTERNAL_SIZE   =   64;
#else
const size_t    AUTO_BUFFER_INTERNAL_SIZE   =   512;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

typedef union Automatic
{
    char    _100[100];
    char    _1000[1000];
    char    _10000[10000];

} Automatic;

/* /////////////////////////////////////////////////////////////////////////////
 * Globals
 */

//extern volatile char  **s_p   =   0;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

int test_automatic(size_t alloc_size, int iterations);
int test_malloc(size_t alloc_size, int iterations);
int test_new(size_t alloc_size, int iterations);
int test_alloca(size_t alloc_size, int iterations, bool bTryAllocA);
int test_vector(size_t alloc_size, int iterations);
int test_vla(size_t alloc_size, int iterations, bool bVLA);
int test_auto_buffer(size_t alloc_size, int iterations);
int test_pod_vector(size_t alloc_size, int iterations);

int main(int argc, char **argv)
{
    int iRet = 0;

    fprintf(stdout, "auto_buffer<> test: %s\n", __STLSOFT_COMPILER_LABEL_STRING);

    if(argc < 3)
    {
usage:
        fprintf(stderr, "  USAGE: Listing4 [-a] [-v] <alloc-size> <iterations>\n");
        fprintf(stderr, "    -a              -   do an alloca() test (likely to\n");
        fprintf(stderr, "                    -     crash with insufficient stack)\n");
        fprintf(stderr, "    -v              -   do a VLA test (likely to\n");
        fprintf(stderr, "                    -     crash with insufficient stack)\n");
        fprintf(stderr, "    <alloc-size>    -   the amount of memory to allocate\n");
        fprintf(stderr, "    <iterations>    -   number of times to execute the test loop\n");

        iRet = 1;
    }
    else
    {
        char const  *pcszAllocSize  =   NULL;
        char const  *pcszIterations =   NULL;
        bool        bTryAllocA      =   false;
        bool        bVLA            =   false;

        for(int i = 1; i < argc; ++i)
        {
            char const  *arg    =   argv[i];

            if(arg[0] == '-')
            {
                switch(arg[1])
                {
                    case    'a':
                        bTryAllocA = true;
                        break;
                    case    'v':
                        bVLA = true;
                        break;
                    default:
                        goto usage;
                }
            }
            else
            {
                if(NULL == pcszAllocSize)
                {
                    pcszAllocSize = arg;
                }
                else if(NULL == pcszIterations)
                {
                    pcszIterations = arg;
                }
            }
        }

#ifdef _DEBUG
        puts(pcszAllocSize);
        puts(pcszIterations);
#endif /* _DEBUG */

        size_t  alloc_size  =   static_cast<size_t>(atoi(pcszAllocSize));
        int     iterations  =   atoi(pcszIterations);

        fprintf(stdout, "internal size: %d; block size: %d\n", AUTO_BUFFER_INTERNAL_SIZE, alloc_size);

#ifdef WIN32
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
#endif // WIN32

        if(alloc_size > sizeof(Automatic))
        {
            fprintf(stderr, "Size of buffer allocation cannot be larger than %d for this implementation!\n", sizeof(Automatic));
        }
        else
        {
            iRet += test_automatic(alloc_size, iterations);
            iRet += test_malloc(alloc_size, iterations);
            iRet += test_new(alloc_size, iterations);
            iRet += test_vector(alloc_size, iterations);
            iRet += test_auto_buffer(alloc_size, iterations);
            iRet += test_pod_vector(alloc_size, iterations);
            iRet += test_alloca(alloc_size, iterations, bTryAllocA);
            iRet += test_vla(alloc_size, iterations, bVLA);
#if 1
            fprintf(stdout, "Total: %d\n", iRet);
#endif /* 0 */
        }
    }

    return iRet;
}


/* /////////////////////////////////////////////////////////////////////////////
 * Test functions
 */

int test_automatic(size_t alloc_size, int iterations)
{
    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "automatic:     ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            Automatic   _buffer;
            char        *buffer =   _buffer._1000;

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Nothing to do
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
}

int test_malloc(size_t alloc_size, int iterations)
{
    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "malloc():      ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            char    *buffer =   (char*)malloc(alloc_size);

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            free(buffer);
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
}

int test_new(size_t alloc_size, int iterations)
{
    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "operator new:  ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            char    *buffer =   new char[alloc_size];

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            delete [] buffer;
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
}

int test_alloca(size_t alloc_size, int iterations, bool bTryAllocA)
{
#ifdef TEST_ALLOCA
    if(!bTryAllocA)
#endif /* !TEST_ALLOCA */
    {
        return fprintf(stdout, "alloca():       -\n");
    }

#ifdef TEST_ALLOCA
    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "alloca():      ");
    fflush(stdout);

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
#ifdef _MSC_VER
            char    *buffer =   (char*)_alloca(alloc_size);
#elif defined(__STLSOFT_COMPILER_IS_GCC)
            char    *buffer =   (char*)__builtin_alloca(alloc_size);
#else
            char    *buffer =   (char*)alloca(alloc_size);
#endif // _MSC_VER

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Nothing to do
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
#endif /* TEST_ALLOCA */
}

int test_vector(size_t alloc_size, int iterations)
{
#ifdef __STLSOFT_COMPILER_IS_WATCOM
    return fprintf(stdout, "vector<>:      \n");
#else
#ifdef __STLSOFT_COMPILER_IS_DMC
    typedef vector<char>                            vector_t;
#else
    typedef vector<char, malloc_allocator<char> >   vector_t;
#endif /* __STLSOFT_COMPILER_IS_DMC */

    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "vector<>:      ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            vector_t    buffer(alloc_size);

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Destructor will handle
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
#endif /* __STLSOFT_COMPILER_IS_WATCOM */
}

int test_vla(size_t alloc_size, int iterations, bool bVLA)
{
#ifdef TEST_VLA
    if(!bVLA)
#endif /* TEST_VLA */
    {
        return fprintf(stdout, "VLA:            -\n");
    }

#ifdef TEST_VLA
    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "VLA:           ");
    fflush(stdout);

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            char    buffer[alloc_size];

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Nothing to do
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
#else
    STLSOFT_SUPPRESS_UNUSED(alloc_size);
    STLSOFT_SUPPRESS_UNUSED(iterations);
    STLSOFT_SUPPRESS_UNUSED(bVLA);

    return 0;
#endif /* TEST_VLA */
}

int test_auto_buffer(size_t alloc_size, int iterations)
{
    typedef auto_buffer<char, malloc_allocator<char>, AUTO_BUFFER_INTERNAL_SIZE>    buffer_t;

    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "auto_buffer<>: ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            buffer_t    buffer(alloc_size);

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Destructor will handle
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
}

int test_pod_vector(size_t alloc_size, int iterations)
{
    typedef pod_vector<char, malloc_allocator<char>, AUTO_BUFFER_INTERNAL_SIZE> vector_t;

    int                 i;
    int                 j;
    int                 iRet;
    performance_counter counter;

    fprintf(stdout, "pod_vector<>:  ");

    for(j = 0; j < WARMUPS; ++j)
    {
        counter.start();
        for(i = 0, iRet = 0; i < iterations; ++i)
        {
            // (i) Allocate
            vector_t    buffer(alloc_size);

            // (ii) Use
//          s_p = const_cast<volatile char**>(&buffer);

            // Help to avoid compiler optimising away our code, by touching 
            // last element in the array ...
            buffer[alloc_size - 1] += i;
            // ... and testing the next to last one
            iRet ^= buffer[alloc_size - 1];

            // (iii) Deallocate
            ; // Destructor will handle
        }
        counter.stop();
    }

    fprintf(stdout, " " test_printf_fmt "\n", counter.get_milliseconds());

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
