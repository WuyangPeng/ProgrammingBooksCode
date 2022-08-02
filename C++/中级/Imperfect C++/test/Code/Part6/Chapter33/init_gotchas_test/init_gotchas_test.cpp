/* /////////////////////////////////////////////////////////////////////////////
 * File:        init_gotchas_test.cpp
 *
 * Purpose:     Implementation file for the init_gotchas_test project.
 *
 * Created:     16th January 2004
 * Updated:     18th January 2004
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

#include <algorithm>

#include <stlsoft.h>

#define dimensionof     stlsoft_num_elements

namespace stlsoft
{
    template <typename T>
    size_t array_size(T const &)
    {
        return 1;
    }

    template <typename T, size_t N>
    size_t array_size(T (&ar)[N])
    {
        return N * array_size(ar[0]);
    }

} // namespace stlsoft

////////////////////////////////////////////////////////////////////////////////

#include <stlsoft_fixed_array.h>
#include <stlsoft_static_array.h>

#pragma pack(push, 8)

#include <boost/array.hpp>
#include <boost/multi_array.hpp>

namespace stlsoft
{
    template <typename T, size_t N>
    size_t array_size(boost::array<T, N> const &ar)
    {
        return N * array_size(ar[0]);
    }

    template <typename T, size_t N>
    size_t array_size(boost::multi_array<T, N> const &ar)
    {
        return ar.num_elements(); // NOTE: size only returns for current dimension
    }

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

const size_t                DIM1_0  =   10;

const size_t                DIM2_0  =   3;
const size_t                DIM2_1  =   5;

typedef stlsoft::byte_t     element_t;

/* ////////////////////////////////////////////////////////////////////////// */

void print_element(element_t const &element)
{
    printf("[%d], ", element);
}

template <typename I>
void do_dump(I first, I last)
{
    std::for_each(first, last, print_element);
}

template <typename I>
void dump(char const *message, I first, I last)
{
    printf("%s:\n", message);
    do_dump(first, last);
    printf("\n");
}

template <typename C>
void dump(char const *message, C const &c)
{
    dump(message, c.begin(), c.end());
}

template <typename T, size_t N>
void dump(char const *message, T (&ar)[N])
{
    dump(message, &ar[0], &ar[N]);
}

template <typename T, size_t N0, size_t N1>
void dump(char const *message, T (&ar)[N0][N1])
{
    dump(message, &ar[0][0], &ar[N0 - 1][N1]);
}

template <typename T, size_t N0, size_t N1, size_t N2>
void dump(char const *message, T (&ar)[N0][N1][N2])
{
    dump(message, &ar[0][0][0], &ar[N0 - 1][N1 - 1][N2]);
}

template <typename T, size_t N0, size_t N1>
void dump(char const *message, boost::array<boost::array<T, N1>, N0> const &ar)
{
    printf("%s:\n", message);
    std::for_each(&ar[0][0], &ar[N0 - 1][N1], print_element); // This uses the disgusting contiguous layout hack, but is only for debugging
    printf("\n");
}

template <typename T>
void dump(char const *message, boost::multi_array<T, 2> const &ar)
{
    printf("%s:\n", message);
    boost::multi_array<T, 2>::const_iterator    b   =   ar.begin();
    boost::multi_array<T, 2>::const_iterator    e   =   ar.end();
    for(; b != e; ++b)
    {
//      boost::multi_array<T, 2>::value_type const  &v = *b;

        std::for_each(b->begin(), b->end(), print_element);

//      std::for_each(v.begin(), v.end(), print_element);
    }
    printf("\n");
}


/* ////////////////////////////////////////////////////////////////////////// */

using stlsoft::array_size;

/* ////////////////////////////////////////////////////////////////////////// */

static element_t next_()
{
    static element_t    s_element;
    element_t           element =   s_element;

    s_element = (s_element + 1) % 10;

    return element;
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
void element_fill(T *p, const T &t, size_t n)
{
    std::fill_n(p, n, t);
}

#if 0
template <typename T, size_t N>
void element_fill(T (&ar)[N], const T &t)
{
    std::fill_n(&ar[0], N, t);
}

template <typename T, size_t N0, size_t N1>
void element_fill(T (&ar)[N0][N1], const T &t)
{
    std::fill_n(&ar[0], N0 * N1, t);
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long );

static void memset_1d();
static void fill_1d();

static void memset_2d();
static void fill_2d();

#include <io.h>

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("init_gotchas_test: " __STLSOFT_COMPILER_LABEL_STRING);

#if 0
    int     ai[10][30][2][5][6];
    size_t  size = array_size(ai);

    _dup(size);
#endif /* 0 */

    memset_1d();
    fill_1d();

    memset_2d();
    fill_2d();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

void memset_1d()
{
    // (i) 1 dimension
    {
        element_t       a1[DIM1_0];

        memset(a1, next_(), sizeof(a1));
        dump("built-in: memset(a1, ..., sizeof(a1))", a1);
        memset(&a1, next_(), sizeof(a1));
        dump("built-in: memset(&a1, ..., sizeof(a1))", a1);
        memset(&a1[0], next_(), sizeof(a1));
        dump("built-in: memset(&a1[0], ..., sizeof(a1))", a1);

        memset(a1, next_(), array_size(a1) * sizeof(element_t));
        dump("built-in: memset(a1, ..., array_size(a1))", a1);
        memset(&a1, next_(), array_size(a1) * sizeof(element_t));
        dump("built-in: memset(&a1, ..., array_size(a1))", a1);
        memset(&a1[0], next_(), array_size(a1) * sizeof(element_t));
        dump("built-in: memset(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        boost::array<element_t, DIM1_0>                 a1;

// DNC  memset(a1, next_(), sizeof(a1));
// DNC  dump("boost::array: memset(a1, ..., sizeof(a1))", a1);
        memset(&a1, next_(), sizeof(a1));
        dump("boost::array: memset(&a1, ..., sizeof(a1))", a1);
        memset(&a1[0], next_(), sizeof(a1));
        dump("boost::array: memset(&a1[0], ..., sizeof(a1))", a1);

// DNC  memset(a1, next_(), array_size(a1) * sizeof(element_t));
// DNC  dump("boost::array: memset(a1, ..., array_size(a1))", a1);
        memset(&a1, next_(), array_size(a1) * sizeof(element_t));
        dump("boost::array: memset(&a1, ..., array_size(a1))", a1);
        memset(&a1[0], next_(), array_size(a1) * sizeof(element_t));
        dump("boost::array: memset(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        stlsoft::static_array_1d<element_t, DIM1_0>     a1;

// DNC  memset(a1, next_(), sizeof(a1));
// DNC  dump("stlsoft::static_array_1d: memset(a1, ..., sizeof(a1))", a1);
        memset(&a1, next_(), sizeof(a1));
        dump("stlsoft::static_array_1d: memset(&a1, ..., sizeof(a1))", a1);
        memset(&a1[0], next_(), sizeof(a1));
        dump("stlsoft::static_array_1d: memset(&a1[0], ..., sizeof(a1))", a1);

// DNC  memset(a1, next_(), array_size(a1) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: memset(a1, ..., array_size(a1))", a1);
        memset(&a1, next_(), array_size(a1) * sizeof(element_t));
        dump("stlsoft::static_array_1d: memset(&a1, ..., array_size(a1))", a1);
        memset(&a1[0], next_(), array_size(a1) * sizeof(element_t));
        dump("stlsoft::static_array_1d: memset(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        boost::multi_array<element_t, 1>                a1(boost::extents[DIM1_0]);

// DNC  memset(a1, next_(), sizeof(a1));
// DNC  dump("boost::array: memset(a1, ..., sizeof(a1))", a1);
// C    memset(&a1, next_(), sizeof(a1));
// C    dump("boost::multi_array: memset(&a1, ..., sizeof(a1))", a1);
// C    memset(&a1[0], next_(), sizeof(a1));
// C    dump("boost::multi_array: memset(&a1[0], ..., sizeof(a1))", a1);

// DNC  memset(a1, next_(), array_size(a1) * sizeof(element_t));
// DNC  dump("boost::array: memset(a1, ..., array_size(a1))", a1);
// C    memset(&a1, next_(), array_size(a1) * sizeof(element_t));
// C    dump("boost::multi_array: memset(&a1, ..., array_size(a1))", a1);
        memset(&a1[0], next_(), array_size(a1) * sizeof(element_t));
        dump("boost::multi_array: memset(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        stlsoft::fixed_array_1d<element_t>              a1(DIM1_0);

// DNC  memset(a1, next_(), sizeof(a1));
// DNC  dump("stlsoft::static_array_1d: memset(a1, ..., sizeof(a1))", a1);
// C    memset(&a1, next_(), sizeof(a1));
// C    dump("stlsoft::static_array_1d: memset(&a1, ..., sizeof(a1))", a1);
/* UW */memset(&a1[0], next_(), sizeof(a1));
/* UW */dump("stlsoft::static_array_1d: memset(&a1[0], ..., sizeof(a1))", a1);

// DNC  memset(a1, next_(), array_size(a1) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: memset(a1, ..., array_size(a1))", a1);
// C    memset(&a1, next_(), array_size(a1) * sizeof(element_t));
// C    dump("stlsoft::static_array_1d: memset(&a1, ..., array_size(a1))", a1);
        memset(&a1[0], next_(), array_size(a1) * sizeof(element_t));
        dump("stlsoft::static_array_1d: memset(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
}

void fill_1d()
{
    // (i) 1 dimension
    {
        element_t       a1[DIM1_0];

        element_fill(a1, next_(), sizeof(a1) / sizeof(element_t));
        dump("built-in: element_fill(a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// DNC  element_fill(&a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("built-in: element_fill(&a1, ..., sizeof(a1) / sizeof(element_t))", a1);
        element_fill(&a1[0], next_(), sizeof(a1) / sizeof(element_t));
        dump("built-in: element_fill(&a1[0], ..., sizeof(a1) / sizeof(element_t))", a1);

        element_fill(a1, next_(), array_size(a1));
        dump("built-in: element_fill(a1, ..., array_size(a1))", a1);
// DNC  element_fill(&a1, next_(), array_size(a1));
// DNC  dump("built-in: element_fill(&a1, ..., array_size(a1))", a1);
        element_fill(&a1[0], next_(), array_size(a1));
        dump("built-in: element_fill(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        boost::array<element_t, DIM1_0>                 a1;

// DNC  element_fill(a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// DNC  element_fill(&a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(&a1, ..., sizeof(a1) / sizeof(element_t))", a1);
        element_fill(&a1[0], next_(), sizeof(a1) / sizeof(element_t));
        dump("boost::array: element_fill(&a1[0], ..., sizeof(a1) / sizeof(element_t))", a1);
        
// DNC  element_fill(a1, next_(), array_size(a1));
// DNC  dump("boost::array: element_fill(a1, ..., array_size(a1))", a1);
// DNC  element_fill(&a1, next_(), array_size(a1));
// DNC  dump("boost::array: element_fill(&a1, ..., array_size(a1))", a1);
        element_fill(&a1[0], next_(), array_size(a1));
        dump("boost::array: element_fill(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        stlsoft::static_array_1d<element_t, DIM1_0>     a1;

// DNC  element_fill(a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: element_fill(a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// DNC  element_fill(&a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: element_fill(&a1, ..., sizeof(a1) / sizeof(element_t))", a1);
        element_fill(&a1[0], next_(), sizeof(a1) / sizeof(element_t));
        dump("stlsoft::static_array_1d: element_fill(&a1[0], ..., sizeof(a1) / sizeof(element_t))", a1);
        
// DNC  element_fill(a1, next_(), array_size(a1));
// DNC  dump("stlsoft::static_array_1d: element_fill(a1, ..., array_size(a1))", a1);
// DNC  element_fill(&a1, next_(), array_size(a1));
// DNC  dump("stlsoft::static_array_1d: element_fill(&a1, ..., array_size(a1))", a1);
        element_fill(&a1[0], next_(), array_size(a1));
        dump("stlsoft::static_array_1d: element_fill(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        boost::multi_array<element_t, 1>                a1(boost::extents[DIM1_0]);

// DNC  element_fill(a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// DNC  element_fill(&a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("boost::multi_array: element_fill(&a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// C    element_fill(&a1[0], next_(), sizeof(a1) / sizeof(element_t));
// C    dump("boost::multi_array: element_fill(&a1[0], ..., sizeof(a1) / sizeof(element_t))", a1);
        
// DNC  element_fill(a1, next_(), array_size(a1));
// DNC  dump("boost::array: element_fill(a1, ..., array_size(a1))", a1);
// DNC  element_fill(&a1, next_(), array_size(a1));
// DNC  dump("boost::multi_array: element_fill(&a1, ..., array_size(a1))", a1);
        element_fill(&a1[0], next_(), array_size(a1));
        dump("boost::multi_array: element_fill(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
    {
        stlsoft::fixed_array_1d<element_t>              a1(DIM1_0);

// DNC  element_fill(a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: element_fill(a1, ..., sizeof(a1) / sizeof(element_t))", a1);
// DNC  element_fill(&a1, next_(), sizeof(a1) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_1d: element_fill(&a1, ..., sizeof(a1) / sizeof(element_t))", a1);
        element_fill(&a1[0], next_(), sizeof(a1) / sizeof(element_t));
        dump("stlsoft::static_array_1d: element_fill(&a1[0], ..., sizeof(a1) / sizeof(element_t))", a1);
        
// DNC  element_fill(a1, next_(), array_size(a1));
// DNC  dump("stlsoft::static_array_1d: element_fill(a1, ..., array_size(a1))", a1);
// DNC  element_fill(&a1, next_(), array_size(a1));
// DNC  dump("stlsoft::static_array_1d: element_fill(&a1, ..., array_size(a1))", a1);
        element_fill(&a1[0], next_(), array_size(a1));
        dump("stlsoft::static_array_1d: element_fill(&a1[0], ..., array_size(a1))", a1);

        printf("\n");
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

void memset_2d()
{
    // (i) 2 dimension
    {
        element_t       a2[DIM2_0][DIM2_1];

        memset(a2, next_(), sizeof(a2));
        dump("built-in: memset(a2, ..., sizeof(a2))", a2);
        memset(&a2, next_(), sizeof(a2));
        dump("built-in: memset(&a2, ..., sizeof(a2))", a2);
        memset(&a2[0], next_(), sizeof(a2));
        dump("built-in: memset(&a2[0], ..., sizeof(a2))", a2);
        memset(&a2[0][0], next_(), sizeof(a2));
        dump("built-in: memset(&a2[0][0], ..., sizeof(a2))", a2);

        memset(a2, next_(), array_size(a2) * sizeof(element_t));
        dump("built-in: memset(a2, ..., array_size(a2))", a2);
        memset(&a2, next_(), array_size(a2) * sizeof(element_t));
        dump("built-in: memset(&a2, ..., array_size(a2))", a2);
        memset(&a2[0], next_(), array_size(a2) * sizeof(element_t));
        dump("built-in: memset(&a2[0], ..., array_size(a2))", a2);
        memset(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("built-in: memset(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        boost::array<boost::array<element_t, DIM2_1>, DIM2_0>   a2;

// DNC  memset(a2, next_(), sizeof(a2));
// DNC  dump("boost::array: memset(a2, ..., sizeof(a2))", a2);
        memset(&a2, next_(), sizeof(a2));
        dump("boost::array: memset(&a2, ..., sizeof(a2))", a2);
        memset(&a2[0], next_(), sizeof(a2));
        dump("boost::array: memset(&a2[0], ..., sizeof(a2))", a2);
        memset(&a2[0][0], next_(), sizeof(a2));
        dump("boost::array: memset(&a2[0][0], ..., sizeof(a2))", a2);
        
// DNC  memset(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: memset(a2, ..., array_size(a2))", a2);
        memset(&a2, next_(), array_size(a2) * sizeof(element_t));
        dump("boost::array: memset(&a2, ..., array_size(a2))", a2);
        memset(&a2[0], next_(), array_size(a2) * sizeof(element_t));
        dump("boost::array: memset(&a2[0], ..., array_size(a2))", a2);
        memset(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("boost::array: memset(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        stlsoft::static_array_2d<element_t, DIM2_0, DIM2_1>     a2;

// DNC  memset(a2, next_(), sizeof(a2));
// DNC  dump("stlsoft::static_array_2d: memset(a2, ..., sizeof(a2))", a2);
        memset(&a2, next_(), sizeof(a2));
        dump("stlsoft::static_array_2d: memset(&a2, ..., sizeof(a2))", a2);
// C    memset(&a2[0], next_(), sizeof(a2));
// C    dump("stlsoft::static_array_2d: memset(&a2[0], ..., sizeof(a2))", a2);
        memset(&a2[0][0], next_(), sizeof(a2));
        dump("stlsoft::static_array_2d: memset(&a2[0][0], ..., sizeof(a2))", a2);

// DNC  memset(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: memset(a2, ..., array_size(a2))", a2);
        memset(&a2, next_(), array_size(a2) * sizeof(element_t));
        dump("stlsoft::static_array_2d: memset(&a2, ..., array_size(a2))", a2);
// C    memset(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// C    dump("stlsoft::static_array_2d: memset(&a2[0], ..., array_size(a2))", a2);
        memset(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("stlsoft::static_array_2d: memset(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        boost::multi_array<element_t, 2>                a2(boost::extents[DIM2_0][DIM2_1]);

// DNC  memset(a2, next_(), sizeof(a2));
// DNC  dump("boost::array: memset(a2, ..., sizeof(a2))", a2);
// C    memset(&a2, next_(), sizeof(a2));
// C    dump("boost::multi_array: memset(&a2, ..., sizeof(a2))", a2);
// C    memset(&a2[0], next_(), sizeof(a2));
// C    dump("boost::multi_array: memset(&a2[0], ..., sizeof(a2))", a2);
// C    memset(&a2[0][0], next_(), sizeof(a2));
// C    dump("boost::multi_array: memset(&a2[0][0], ..., sizeof(a2))", a2);

// DNC  memset(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: memset(a2, ..., array_size(a2))", a2);
// C    memset(&a2, next_(), array_size(a2) * sizeof(element_t));
// C    dump("boost::multi_array: memset(&a2, ..., array_size(a2))", a2);
// C    memset(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// C    dump("boost::multi_array: memset(&a2[0], ..., array_size(a2))", a2);
        memset(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("boost::multi_array: memset(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        stlsoft::fixed_array_2d<element_t>              a2(DIM2_0, DIM2_1);

// DNC  memset(a2, next_(), sizeof(a2));
// DNC  dump("stlsoft::static_array_2d: memset(a2, ..., sizeof(a2))", a2);
// C    memset(&a2, next_(), sizeof(a2));
// C    dump("stlsoft::static_array_2d: memset(&a2, ..., sizeof(a2))", a2);
// C    memset(&a2[0], next_(), sizeof(a2));
// C    dump("stlsoft::static_array_2d: memset(&a2[0], ..., sizeof(a2))", a2);
// C    memset(&a2[0][0], next_(), sizeof(a2));
// C    dump("stlsoft::static_array_2d: memset(&a2[0][0], ..., sizeof(a2))", a2);

// DNC  memset(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: memset(a2, ..., array_size(a2))", a2);
// C    memset(&a2, next_(), array_size(a2) * sizeof(element_t));
// C    dump("stlsoft::static_array_2d: memset(&a2, ..., array_size(a2))", a2);
// C    memset(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// C    dump("stlsoft::static_array_2d: memset(&a2[0], ..., array_size(a2))", a2);
        memset(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("stlsoft::static_array_2d: memset(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
}

void fill_2d()
{
    // (i) 2 dimension
    {
        element_t       a2[DIM2_0][DIM2_1];

// DNC  element_fill(a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("built-in: element_fill(a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("built-in: element_fill(&a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2[0], next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("built-in: element_fill(&a2[0], ..., sizeof(a2) / sizeof(element_t))", a2);
        element_fill(&a2[0][0], next_(), sizeof(a2) / sizeof(element_t));
        dump("built-in: element_fill(&a2[0][0], ..., sizeof(a2) / sizeof(element_t))", a2);

// DNC  element_fill(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("built-in: element_fill(a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("built-in: element_fill(&a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("built-in: element_fill(&a2[0], ..., array_size(a2))", a2);
        element_fill(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("built-in: element_fill(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        boost::array<boost::array<element_t, DIM2_1>, DIM2_0>   a2;

// DNC  element_fill(a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(&a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2[0], next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(&a2[0], ..., sizeof(a2) / sizeof(element_t))", a2);
        element_fill(&a2[0][0], next_(), sizeof(a2) / sizeof(element_t));
        dump("boost::array: element_fill(&a2[0][0], ..., sizeof(a2) / sizeof(element_t))", a2);
        
// DNC  element_fill(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: element_fill(a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: element_fill(&a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: element_fill(&a2[0], ..., array_size(a2))", a2);
        element_fill(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("boost::array: element_fill(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        stlsoft::static_array_2d<element_t, DIM2_0, DIM2_1>     a2;

// DNC  element_fill(a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2[0], next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2[0], ..., sizeof(a2) / sizeof(element_t))", a2);
        element_fill(&a2[0][0], next_(), sizeof(a2) / sizeof(element_t));
        dump("stlsoft::static_array_2d: element_fill(&a2[0][0], ..., sizeof(a2) / sizeof(element_t))", a2);

// DNC  element_fill(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2[0], ..., array_size(a2))", a2);
        element_fill(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("stlsoft::static_array_2d: element_fill(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        boost::multi_array<element_t, 2>                a2(boost::extents[DIM2_0][DIM2_1]);

// DNC  element_fill(a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::array: element_fill(a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::multi_array: element_fill(&a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2[0], next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("boost::multi_array: element_fill(&a2[0], ..., sizeof(a2) / sizeof(element_t))", a2);
// C    element_fill(&a2[0][0], next_(), sizeof(a2) / sizeof(element_t));
// C    dump("boost::multi_array: element_fill(&a2[0][0], ..., sizeof(a2) / sizeof(element_t))", a2);

// DNC  element_fill(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::array: element_fill(a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::multi_array: element_fill(&a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("boost::multi_array: element_fill(&a2[0], ..., array_size(a2))", a2);
        element_fill(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("boost::multi_array: element_fill(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
    {
        stlsoft::fixed_array_2d<element_t>              a2(DIM2_0, DIM2_1);

// DNC  element_fill(a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2, next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2, ..., sizeof(a2) / sizeof(element_t))", a2);
// DNC  element_fill(&a2[0], next_(), sizeof(a2) / sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2[0], ..., sizeof(a2) / sizeof(element_t))", a2);
// C    element_fill(&a2[0][0], next_(), sizeof(a2) / sizeof(element_t));
// C    dump("stlsoft::static_array_2d: element_fill(&a2[0][0], ..., sizeof(a2) / sizeof(element_t))", a2);

// DNC  element_fill(a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2, next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2, ..., array_size(a2))", a2);
// DNC  element_fill(&a2[0], next_(), array_size(a2) * sizeof(element_t));
// DNC  dump("stlsoft::static_array_2d: element_fill(&a2[0], ..., array_size(a2))", a2);
        element_fill(&a2[0][0], next_(), array_size(a2) * sizeof(element_t));
        dump("stlsoft::static_array_2d: element_fill(&a2[0][0], ..., array_size(a2))", a2);

        printf("\n");
    }
}

/* ////////////////////////////////////////////////////////////////////////// */
