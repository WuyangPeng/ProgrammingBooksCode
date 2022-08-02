/* /////////////////////////////////////////////////////////////////////////////
 * File:        static_array_test.cpp
 *
 * Purpose:     Implementation file for the static_array_test project.
 *
 * Created:     14th January 2004
 * Updated:     19th January 2004
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
#include <stlsoft_integer_to_string.h>
#include <stlsoft_simple_string.h>
#include <stlsoft_static_array.h>

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


#include <boost/array.hpp>

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef ITERATIONS
# ifdef _DEBUG
const int   ITERATIONS  =   100;
# else /* ? _DEBUG */
const int   ITERATIONS  =   100000;
# endif /* _DEBUG */
#endif /* !ITERATIONS */

#ifdef DIM0
# error DIM0
#endif // DIM0
#ifdef DIM1
# error DIM1
#endif // DIM1
#ifdef DIM2
# error DIM2
#endif // DIM2

#ifndef DIM0
const int   DIM0        =   10;
#endif /* DIM0 */
#ifndef DIM1
const int   DIM1        =   10;
#endif /* DIM1 */
#ifndef DIM2
const int   DIM2        =   10;
#endif /* DIM2 */

#ifdef USE_STRING
typedef stlsoft::basic_simple_string<char>              element_t;
#else /* ? USE_STRING */
//typedef   double                                          element_t;
typedef int                                             element_t;
#endif /* USE_STRING */

#if 0
# define ATOR_(x)                                       std::allocator<x>
#else /* ? 0 */
# define ATOR_(x)                                       winstl::processheap_allocator<x>
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

void test_1dim()
{
    performance_counter counter;
    unsigned long       time_array;
    unsigned long       time_boost;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_array;
    int                 res_boost;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    const int           DIM     =   DIM0 * DIM1 * DIM2;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef element_t                                   array_t[DIM];
        typedef boost::array<element_t, DIM>                boost_array_t;
        typedef stlsoft::static_array_1d<element_t, DIM>    stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) built-in
        {
            array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(ar));
#endif /* USE_STRING */

            counter.start();
            res_array = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM; ++j)
                {
#ifdef USE_STRING
                    ar[j] += strings[j % stlsoft_num_elements(strings)];
                    res_array += ar[j].length();
#else /* ? USE_STRING */
                    ar[j] += i * j;
                    res_array += ar[j];
#endif /* USE_STRING */
                }
            }
            counter.stop();
            time_array = counter.get_milliseconds();
        }

        // (ii) boost::array
        {
            boost_array_t   ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_boost = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM; ++j)
                {
#ifdef USE_STRING
                    ar[j] += strings[j % stlsoft_num_elements(strings)];
                    res_boost += ar[j].length();
#else /* ? USE_STRING */
                    ar[j] += i * j;
                    res_boost += ar[j];
#endif /* USE_STRING */
                }
            }
            counter.stop();
            time_boost = counter.get_milliseconds();
        }

        // (iii) stlsoft::static_array
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM; ++j)
                {
    #ifdef USE_STRING
                    ar[j] += strings[j % stlsoft_num_elements(strings)];
                    res_stlsoft += ar[j].length();
    #else /* ? USE_STRING */
                    ar[j] += i * j;
                    res_stlsoft += ar[j];
    #endif /* USE_STRING */
                }
            }
            counter.stop();
            time_stlsoft = counter.get_milliseconds();
        }

        // (iv) stlsoft::static_array (at)
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM; ++j)
                {
    #ifdef USE_STRING
                    ar.at(j) += strings[j % stlsoft_num_elements(strings)];
                    res_stlsoft_at += ar.at(j).length();
    #else /* ? USE_STRING */
                    ar.at(j) += i * j;
                    res_stlsoft_at += ar.at(j);
    #endif /* USE_STRING */
                }
            }
            counter.stop();
            time_stlsoft_at = counter.get_milliseconds();
        }

        // (iii) stlsoft::static_array
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at_unchecked = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM; ++j)
                {
    #ifdef USE_STRING
                    ar.at_unchecked(j) += strings[j % stlsoft_num_elements(strings)];
                    res_stlsoft_at_unchecked += ar.at_unchecked(j).length();
    #else /* ? USE_STRING */
                    ar.at_unchecked(j) += i * j;
                    res_stlsoft_at_unchecked += ar.at_unchecked(j);
    #endif /* USE_STRING */
                }
            }
            counter.stop();
            time_stlsoft_at_unchecked = counter.get_milliseconds();
        }
    }

    printf("1 dimension(s); array:      \t%lu\t%d\n", time_array,                   res_array                   );
    printf("1 dimension(s); Boost:      \t%lu\t%d\n", time_boost,                   res_boost                   );
    printf("1 dimension(s); STLSoft:    \t%lu\t%d\n", time_stlsoft,                 res_stlsoft                 );
    printf("1 dimension(s); STLSoft (A):\t%lu\t%d\n", time_stlsoft_at,              res_stlsoft_at              );
    printf("1 dimension(s); STLSoft (U):\t%lu\t%d\n", time_stlsoft_at_unchecked,    res_stlsoft_at_unchecked    );
}

/* ////////////////////////////////////////////////////////////////////////// */

void test_2dim()
{
    performance_counter counter;
    unsigned long       time_array;
    unsigned long       time_boost;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_array;
    int                 res_boost;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    const int           DIM12   =   DIM1 * DIM2;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef element_t                                           array_t[DIM0][DIM12];
        typedef boost::array<element_t, DIM12>                      boost_array_t_;
        typedef boost::array<boost_array_t_, DIM0>                  boost_array_t;
        typedef stlsoft::static_array_2d<element_t, DIM0, DIM12>    stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) built-in array

        {
            array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(ar));
#endif /* USE_STRING */

            counter.start();
            res_array = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM12; ++k)
                    {
#ifdef USE_STRING
                        ar[j][k] += strings[j % stlsoft_num_elements(strings)];
                        res_array += ar[j][k].length();
#else /* ? USE_STRING */
                        ar[j][k] += i * j * k;
                        res_array += ar[j][k];
#endif /* USE_STRING */
                    }
                }
            }
            counter.stop();
            time_array = counter.get_milliseconds();
        }

        // (ii) boost::array

        {
            boost_array_t   ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0], 0, sizeof(element_t) * ar.size() * ar[0].size());
#endif /* USE_STRING */

            counter.start();
            res_boost = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM12; ++k)
                    {
#ifdef USE_STRING
                        ar[j][k] += strings[j % stlsoft_num_elements(strings)];
                        res_boost += ar[j][k].length();
#else /* ? USE_STRING */
                        ar[j][k] += i * j * k;
                        res_boost += ar[j][k];
#endif /* USE_STRING */
                    }
                }
            }
            counter.stop();
            time_boost = counter.get_milliseconds();
        }

        // (iii) stlsoft::static_array

        {
            stlsoft_array_t ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM12; ++k)
                    {
#ifdef USE_STRING
                        ar[j][k] += strings[j % stlsoft_num_elements(strings)];
                        res_stlsoft += ar[j][k].length();
#else /* ? USE_STRING */
                        ar[j][k] += i * j * k;
                        res_stlsoft += ar[j][k];
#endif /* USE_STRING */
                    }
                }
            }
            counter.stop();
            time_stlsoft = counter.get_milliseconds();
        }

        // (iv) stlsoft::static_array (at)

        {
            stlsoft_array_t ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM12; ++k)
                    {
#ifdef USE_STRING
                        ar.at(j, k) += strings[j % stlsoft_num_elements(strings)];
                        res_stlsoft_at += ar.at(j, k).length();
#else /* ? USE_STRING */
                        ar.at(j, k) += i * j * k;
                        res_stlsoft_at += ar.at(j, k);
#endif /* USE_STRING */
                    }
                }
            }
            counter.stop();
            time_stlsoft_at = counter.get_milliseconds();
        }

        // (v) stlsoft::static_array (unchecked)

        {
            stlsoft_array_t ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at_unchecked = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM12; ++k)
                    {
#ifdef USE_STRING
                        ar.at_unchecked(j, k) += strings[j % stlsoft_num_elements(strings)];
                        res_stlsoft_at_unchecked += ar.at_unchecked(j, k).length();
#else /* ? USE_STRING */
                        ar.at_unchecked(j, k) += i * j * k;
                        res_stlsoft_at_unchecked += ar.at_unchecked(j, k);
#endif /* USE_STRING */
                    }
                }
            }
            counter.stop();
            time_stlsoft_at_unchecked = counter.get_milliseconds();
        }
    }

    printf("2 dimension(s); array:      \t%lu\t%d\n", time_array,                   res_array                   );
    printf("2 dimension(s); Boost:      \t%lu\t%d\n", time_boost,                   res_boost                   );
    printf("2 dimension(s); STLSoft:    \t%lu\t%d\n", time_stlsoft,                 res_stlsoft                 );
    printf("2 dimension(s); STLSoft (A):\t%lu\t%d\n", time_stlsoft_at,              res_stlsoft_at              );
    printf("2 dimension(s); STLSoft (U):\t%lu\t%d\n", time_stlsoft_at_unchecked,    res_stlsoft_at_unchecked    );
}

////////////////////////////////////////////////////////////////////////////////

void test_3dim()
{
    performance_counter counter;
    unsigned long       time_array;
    unsigned long       time_boost;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_array;
    int                 res_boost;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef element_t                                               array_t[DIM0][DIM1][DIM2];
        typedef boost::array<element_t, DIM2>                           boost_array_t_;
        typedef boost::array<boost_array_t_, DIM1>                      boost_array_t__;
        typedef boost::array<boost_array_t__, DIM0>                     boost_array_t;
        typedef stlsoft::static_array_3d<element_t, DIM0, DIM2, DIM2>   stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) built-in array
        {
            array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0], 0, sizeof(ar));
#endif /* USE_STRING */

            counter.start();
            res_array = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM1; ++k)
                    {
                        for(int l = 0; l < DIM2; ++l)
                        {
#ifdef USE_STRING
                            ar[j][k][l] += strings[j % stlsoft_num_elements(strings)];
                            res_array += ar[j][k][l].length();
#else /* ? USE_STRING */
                            ar[j][k][l] += i * j * k * l;
                            res_array += ar[j][k][l];
#endif /* USE_STRING */

                        }
                    }
                }
            }
            counter.stop();
            time_array = counter.get_milliseconds();
        }

        // (ii) boost::array
        {
            boost_array_t   ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0][0], 0, sizeof(element_t) * ar.size() * ar[0].size() * ar[0][0].size());
#endif /* USE_STRING */

            counter.start();
            res_boost = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM1; ++k)
                    {
                        for(int l = 0; l < DIM2; ++l)
                        {
#ifdef USE_STRING
                            ar[j][k][l] += strings[j % stlsoft_num_elements(strings)];
                            res_boost += ar[j][k][l].length();
#else /* ? USE_STRING */
                            ar[j][k][l] += i * j * k * l;
                            res_boost += ar[j][k][l];
#endif /* USE_STRING */
                        }
                    }
                }
            }
            counter.stop();
            time_boost = counter.get_milliseconds();
        }

        // (iii) stlsoft::static_array
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM1; ++k)
                    {
                        for(int l = 0; l < DIM2; ++l)
                        {
#ifdef USE_STRING
                            ar[j][k][l] += strings[j % stlsoft_num_elements(strings)];
                            res_stlsoft += ar[j][k][l].length();
#else /* ? USE_STRING */
                            ar[j][k][l] += i * j * k * l;
                            res_stlsoft += ar[j][k][l];
#endif /* USE_STRING */
                        }
                    }
                }
            }
            counter.stop();
            time_stlsoft = counter.get_milliseconds();
        }

        // (iv) stlsoft::static_array (at)
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM1; ++k)
                    {
                        for(int l = 0; l < DIM2; ++l)
                        {
#ifdef USE_STRING
                            ar.at(j, k, l) += strings[j % stlsoft_num_elements(strings)];
                            res_stlsoft_at += ar.at(j, k, l).length();
#else /* ? USE_STRING */
                            ar.at(j, k, l) += i * j * k * l;
                            res_stlsoft_at += ar.at(j, k, l);
#endif /* USE_STRING */
                        }
                    }
                }
            }
            counter.stop();
            time_stlsoft_at = counter.get_milliseconds();
        }

        // (v) stlsoft::static_array (unchecked)
        {
            stlsoft_array_t     ar;

#ifdef USE_STRING
#else /* ? USE_STRING */
            memset(&ar[0][0][0], 0, sizeof(element_t) * ar.size());
#endif /* USE_STRING */

            counter.start();
            res_stlsoft_at_unchecked = 0;
            for(i = 0; i < ITERATIONS; ++i)
            {
                for(int j = 0; j < DIM0; ++j)
                {
                    for(int k = 0; k < DIM1; ++k)
                    {
                        for(int l = 0; l < DIM2; ++l)
                        {
#ifdef USE_STRING
                            ar.at_unchecked(j, k, l) += strings[j % stlsoft_num_elements(strings)];
                            res_stlsoft_at_unchecked += ar.at_unchecked(j, k, l).length();
#else /* ? USE_STRING */
                            ar.at_unchecked(j, k, l) += i * j * k * l;
                            res_stlsoft_at_unchecked += ar.at_unchecked(j, k, l);
#endif /* USE_STRING */
                        }
                    }
                }
            }
            counter.stop();
            time_stlsoft_at_unchecked = counter.get_milliseconds();
        }
    }

    printf("3 dimension(s); std:        \t%lu\t%d\n", time_array,                   res_array                   );
    printf("3 dimension(s); Boost:      \t%lu\t%d\n", time_boost,                   res_boost                   );
    printf("3 dimension(s); STLSoft:    \t%lu\t%d\n", time_stlsoft,                 res_stlsoft                 );
    printf("3 dimension(s); STLSoft (A):\t%lu\t%d\n", time_stlsoft_at,              res_stlsoft_at              );
    printf("3 dimension(s); STLSoft (U):\t%lu\t%d\n", time_stlsoft_at_unchecked,    res_stlsoft_at_unchecked    );
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("static_array_test: " __STLSOFT_COMPILER_LABEL_STRING);

    char    ar[10];

    memset(ar, 0, sizeof(ar));
    memset(&ar, 1, sizeof(ar));
    memset(&ar[0], 2, sizeof(ar));

    /* . */
    test_1dim();
    test_2dim();
    test_3dim();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
