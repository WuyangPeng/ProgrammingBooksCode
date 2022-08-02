/* /////////////////////////////////////////////////////////////////////////////
 * File:        multi_array_test.cpp
 *
 * Purpose:     Implementation file for the multi_array_test project.
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

#ifdef _MSC_VER
# pragma warning(disable : 4786)
#endif /* _MSC_VER */

#include <stdio.h>
#if defined(__DMC__)
# include <iostream.h>
#else /* ? __DMC__ */
# include <iostream>

using std::cout;
using std::cerr;
using std::endl;
#endif /* __DMC__ */

#include <stlsoft.h>
#include <stlsoft_integer_to_string.h>
#include <stlsoft_simple_string.h>
#include <stlsoft_fixed_array.h>

#if defined(unix) || \
    defined(__unix__)

#include <unixstl.h>

# include <unixstl_performance_counter.h>

unixstl_ns_using(performance_counter)

#elif defined(WIN32) || \
    defined(_WIN32)

# include <winstl.h>

# include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)

# include <winstl_processheap_allocator.h>

winstl_ns_using(processheap_allocator)

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

#include <boost/multi_array.hpp>

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef ITERATIONS
# ifdef _DEBUG
const int   ITERATIONS  =   10;
# else /* ? _DEBUG */
const int   ITERATIONS  =   100000;
# endif /* _DEBUG */
#endif /* !ITERATIONS */

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
typedef stlsoft::basic_simple_string<char>  element_t;
#else /* ? USE_STRING */
//typedef   double                              element_t;
typedef int                                 element_t;
#endif /* USE_STRING */

#if 0
# define ATOR_(x)                           std::allocator<x>
#else /* ? 0 */
# define ATOR_(x)                           winstl::processheap_allocator<x>
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

#include <algorithm>

#ifdef _DEBUG
namespace std
{
    template<   typename T
            ,   typename A1
            ,   typename A2
            ,   typename F
            >
            inline F for_each(::std::vector<::std::vector<T, A1>, A2>::iterator from, ::std::vector<::std::vector<T, A1>, A2>::iterator to, F fn)
    {
        for(; from != to; ++from)
        {
            for_each((*from).begin(), (*from).end(), fn);
        }

        return fn;
    }

} // namespace std

void print_element(element_t const &e)
{
#ifdef USE_STRING
    printf("%s ", e.c_str());
#else /* ? USE_STRING */
    printf("%d ", e);
#endif /* USE_STRING */
}
#endif /* _DEBUG */

using std::for_each;

/* ////////////////////////////////////////////////////////////////////////// */

void test_1dim()
{
    performance_counter counter;
    unsigned long       time_vector;
    unsigned long       time_boost;
    unsigned long       time_boost_indexer;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_vector;
    int                 res_boost;
    int                 res_boost_indexer;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    const int           DIM     =   DIM0 * DIM1 * DIM2;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef std::vector<element_t, ATOR_(element_t)>                    std_array_t;
        typedef boost::multi_array<element_t, 1, ATOR_(element_t)>          boost_multi_array_t;
        typedef stlsoft::fixed_array_1d<element_t, ATOR_(element_t)>        stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) std::vector

        counter.start();
        res_vector = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            std_array_t ar(DIM);

            for(int j = 0; j < ar.size(); ++j)
            {
#ifdef USE_STRING
                ar[j] += strings[j % stlsoft_num_elements(strings)];
                res_vector += ar[j].length();
#else /* ? USE_STRING */
                ar[j] += i * j;
                res_vector += ar[j];
#endif /* USE_STRING */
            }
        }
        counter.stop();
        time_vector = counter.get_milliseconds();

        // (ii) boost::multi_array

        counter.start();
        res_boost = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            boost_multi_array_t ar(boost::extents[DIM]);

            for(int j = 0; j < ar.size(); ++j)
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

#if 0
        // (iii) boost::multi_array - indexer

        counter.start();
        res_boost_indexer = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            boost_multi_array_t ar(boost::extents[DIM]);

            for(int j = 0; j < ar.size(); ++j)
            {
#ifdef USE_STRING
                ar[ar.new_idxes[j]] += strings[j % stlsoft_num_elements(strings)];
                res_boost_indexer += ar[boost::extents[j]].length();
#else /* ? USE_STRING */
                ar[boost::indices[j]] += i * j;
                res_boost_indexer += ar[boost::indices[j]];
#endif /* USE_STRING */
            }
        }
        counter.stop();
        time_boost_indexer = counter.get_milliseconds();
#endif /* 0 */

        // (iii) stlsoft::fixed_array

        counter.start();
        res_stlsoft = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM);

            for(int j = 0; j < ar.size(); ++j)
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

        // (iv) stlsoft::fixed_array

        counter.start();
        res_stlsoft_at = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM);

            for(int j = 0; j < ar.size(); ++j)
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

        // (iv) stlsoft::fixed_array

        counter.start();
        res_stlsoft_at_unchecked = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM);

            for(int j = 0; j < ar.size(); ++j)
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

    printf("1 dimension(s); std:        \t%lu\t%d\n", time_vector,                  res_vector                  );
    printf("1 dimension(s); Boost:      \t%lu\t%d\n", time_boost,                   res_boost                   );
//  printf("1 dimension(s); Boost (I):  \t%lu\t%d\n", time_boost_indexer,           res_boost_indexer           );
    printf("1 dimension(s); STLSoft:    \t%lu\t%d\n", time_stlsoft,                 res_stlsoft                 );
    printf("1 dimension(s); STLSoft (A):\t%lu\t%d\n", time_stlsoft_at,              res_stlsoft_at              );
    printf("1 dimension(s); STLSoft (U):\t%lu\t%d\n", time_stlsoft_at_unchecked,    res_stlsoft_at_unchecked    );
}

/* ////////////////////////////////////////////////////////////////////////// */

void test_2dim()
{
    performance_counter counter;
    unsigned long       time_vector;
    unsigned long       time_boost;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_vector;
    int                 res_boost;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    const int           DIM12   =   DIM1 * DIM2;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef std::vector<element_t, ATOR_(element_t)>                std_array_1_t;
        typedef std::vector<std_array_1_t, ATOR_(std_array_1_t)>        std_array_t;
        typedef boost::multi_array<element_t, 2, ATOR_(element_t)>      boost_multi_array_t;
        typedef stlsoft::fixed_array_2d<element_t, ATOR_(element_t)>    stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) std::vector

        counter.start();
        res_vector = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            std_array_t ar(DIM0);

            for(int x = 0; x < ar.size(); ++x)
            {
                ar[x].resize(DIM12);
            }

#ifdef _DEBUG
            for_each<element_t, ATOR_(element_t), ATOR_(std_array_1_t), void (*)(element_t const &)>(ar.begin(), ar.end(), print_element);
//          for_each(ar.begin(), ar.end(), print_element);
#endif /* _DEBUG */

            for(int j = 0; j < DIM0; ++j)
            {
                for(int k = 0; k < DIM12; ++k)
                {
#ifdef USE_STRING
                    ar[j][k] += strings[j % stlsoft_num_elements(strings)];
                    res_vector += ar[j][k].length();
#else /* ? USE_STRING */
                    ar[j][k] += i * j * k;
                    res_vector += ar[j][k];
#endif /* USE_STRING */
                }
            }
        }
        counter.stop();
        time_vector = counter.get_milliseconds();

        // (ii) boost::multi_array

        counter.start();
        res_boost = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            boost_multi_array_t ar(boost::extents[DIM0][DIM12]);

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

        // (iii) stlsoft::fixed_array

        counter.start();
        res_stlsoft = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM12);

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

        // (iv) stlsoft::fixed_array (at)

        counter.start();
        res_stlsoft_at = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM12);

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

        // (v) stlsoft::fixed_array (unchecked)

        counter.start();
        res_stlsoft_at_unchecked = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM12);

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

    printf("2 dimension(s); std:        \t%lu\t%d\n", time_vector,                  res_vector                  );
    printf("2 dimension(s); Boost:      \t%lu\t%d\n", time_boost,                   res_boost                   );
    printf("2 dimension(s); STLSoft:    \t%lu\t%d\n", time_stlsoft,                 res_stlsoft                 );
    printf("2 dimension(s); STLSoft (A):\t%lu\t%d\n", time_stlsoft_at,              res_stlsoft_at              );
    printf("2 dimension(s); STLSoft (U):\t%lu\t%d\n", time_stlsoft_at_unchecked,    res_stlsoft_at_unchecked    );
}

////////////////////////////////////////////////////////////////////////////////

void test_3dim()
{
    performance_counter counter;
    unsigned long       time_vector;
    unsigned long       time_boost;
    unsigned long       time_stlsoft;
    unsigned long       time_stlsoft_at;
    unsigned long       time_stlsoft_at_unchecked;

    int                 res_vector;
    int                 res_boost;
    int                 res_stlsoft;
    int                 res_stlsoft_at;
    int                 res_stlsoft_at_unchecked;

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        typedef std::vector<element_t, ATOR_(element_t)>                std_array_1_t;
        typedef std::vector<std_array_1_t, ATOR_(std_array_1_t)>        std_array_2_t;
        typedef std::vector<std_array_2_t, ATOR_(std_array_2_t)>        std_array_t;
        typedef boost::multi_array<element_t, 3, ATOR_(element_t)>      boost_multi_array_t;
        typedef stlsoft::fixed_array_3d<element_t, ATOR_(element_t)>    stlsoft_array_t;

        int         i;
#ifdef USE_STRING
        string_t    strings[20];

        for(i = 0; i < stlsoft_num_elements(strings); ++i)
        {
            char    sz[101];

            strings[i].assign(stlsoft::integer_to_string(sz, stlsoft_num_elements(sz), i));
        }
#endif /* 0 */

        // (i) std::vector

        counter.start();
        res_vector = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            std_array_t ar(DIM0);

            for(int x = 0; x < ar.size(); ++x)
            {
                ar[x].resize(DIM1);

                for(int y = 0; y < ar[x].size(); ++y)
                {
                    ar[x][y].resize(DIM2);
                }
            }

            for(int j = 0; j < DIM0; ++j)
            {
                for(int k = 0; k < DIM1; ++k)
                {
                    for(int l = 0; l < DIM2; ++l)
                    {
#ifdef USE_STRING
                        ar[j][k][l] += strings[j % stlsoft_num_elements(strings)];
                        res_vector += ar[j][k][l].length();
#else /* ? USE_STRING */
                        ar[j][k][l] += i * j * k * l;
                        res_vector += ar[j][k][l];
#endif /* USE_STRING */

                    }
                }
            }
        }
        counter.stop();
        time_vector = counter.get_milliseconds();

        // (ii) boost::multi_array

        counter.start();
        res_boost = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            boost_multi_array_t ar(boost::extents[DIM0][DIM1][DIM2]);

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

        // (iii) stlsoft::fixed_array

        counter.start();
        res_stlsoft = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM1, DIM2);

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

        // (iv) stlsoft::fixed_array (unchecked)

        counter.start();
        res_stlsoft_at = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM1, DIM2);

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

        // (v) stlsoft::fixed_array (unchecked)

        counter.start();
        res_stlsoft_at_unchecked = 0;
        for(i = 0; i < ITERATIONS; ++i)
        {
            stlsoft_array_t ar(DIM0, DIM1, DIM2);

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

    printf("3 dimension(s); std:        \t%lu\t%d\n",   time_vector,                res_vector                  );
    printf("3 dimension(s); Boost:      \t%lu\t%d\n",   time_boost,                 res_boost                   );
    printf("3 dimension(s); STLSoft:    \t%lu\t%d\n",   time_stlsoft,               res_stlsoft                 );
    printf("3 dimension(s); STLSoft (A):\t%lu\t%d\n",   time_stlsoft_at,            res_stlsoft_at              );
    printf("3 dimension(s); STLSoft (U):\t%lu\t%d\n",   time_stlsoft_at_unchecked,  res_stlsoft_at_unchecked    );
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    int                 iRet        =   0;
    int                 i;

    cout << "multi_array_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;

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
    test_1dim();
    test_2dim();
    test_3dim();

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
