/* /////////////////////////////////////////////////////////////////////////////
 * File:        simple_range_test.cpp
 *
 * Purpose:     Implementation file for the simple_range_test project.
 *
 * Created:     20th January 2004
 * Updated:     24th January 2004
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

#include <rangelib/algorithms.h>
#include <rangelib/integral_range.h>
#include <rangelib/sequence_range.h>
#include <rangelib/iterator_range.h>

#include <list>
#include <vector>

#include <numeric>

#include <iostream>
#include <fstream>
#include <iterator>

/* ////////////////////////////////////////////////////////////////////////// */

using stlsoft::integral_range;
using stlsoft::iterator_range;
using stlsoft::sequence_range;
using stlsoft::r_accumulate;
using stlsoft::r_copy;
using stlsoft::r_distance;
using stlsoft::r_for_each;

/* ////////////////////////////////////////////////////////////////////////// */

typedef integral_range<int>     int_range;

typedef std::vector<int>        int_vector_t;
typedef std::list<int>          int_list_t;

/* ////////////////////////////////////////////////////////////////////////// */

void print_int(int value)
{
    printf("%d ", value);
}

/* ////////////////////////////////////////////////////////////////////////// */

//extern "C" void __stdcall Sleep(unsigned );

template <typename R>
struct divisible
    : public R::range_tag_type
{
public:
    typedef divisible                           class_type;
    typedef R                                   filtered_range_type;
    typedef ss_typename_type_k R::value_type    value_type;

public:
    divisible(filtered_range_type r, value_type div)
        : m_r(r)
        , m_div(div)
    {
        for(; m_r && 0 != (*m_r % m_div); ++m_r)
        {}
    }

private:
    STLSOFT_DEFINE_OPERATOR_BOOL_TYPES_T(class_type, operator_bool_generator_type, operator_bool_type);
public:
    operator operator_bool_type() const
    {
        return operator_bool_generator_type::translate(m_r);
    }
    value_type operator *() const
    {
        return *m_r;
    }
    class_type &operator ++()
    {
        for(; m_r && 0 != (*++m_r % m_div); )
        {}

        return *this;
    }

private:
    filtered_range_type m_r;
    value_type const    m_div;
};

struct next_odd_number
{
  next_odd_number(int first)
    : m_current(first - 2)
  {}

  int operator ()()
  {
    return ++++m_current;
  }

private:
  int m_current;
};

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("simple_range_test: " __STLSOFT_COMPILER_LABEL_STRING);


    {
        {
            int_vector_t    ints(49);

            std::generate(ints.begin(), ints.end(), next_odd_number(1));

            printf("Enumerating range created by std::generate()\n");
            std::for_each(ints.begin(), ints.end(), print_int);
            puts("");
        }

        {
            int_vector_t    ints;

            ints.reserve(49); // No problem if this is wrong.

            r_copy(int_range(1, 99, 2), std::back_inserter(ints));

            printf("Enumerating range created by int_range\n");
            std::for_each(ints.begin(), ints.end(), print_int);
            puts("");
        }
    }



    // Using an int_range
    {
        std::cout << std::endl << "Testing integral_range<>" << std::endl;

    //  int_range   ir(10, 20);
        int_range   ir(10, 12, 2);

        printf("Enumerating int_range via r_for_each()\n");
        r_for_each(ir, print_int);
        puts("");

        printf("Enumerating int_range manually\n");
        for(; ir; ++ir)
        {
            print_int(*ir);
        }
        puts("");
    }

    // Using an int_range
    {
        std::cout << std::endl << "Testing integral_range<> + filter" << std::endl;

    //  int_range               ir(10, 20);
        int_range               ir_(1, 99, 2);
        divisible<int_range>    ir(ir_, 3);


        printf("Enumerating int_range via r_for_each()\n");
        r_for_each(divisible<int_range>(int_range(1, 25, 2), 3), print_int);
        puts("");

        printf("Enumerating int_range manually\n");
        for(; ir; ++ir)
        {
            print_int(*ir);
        }
        puts("");
    }

    // Using a range adaptor on a vector<int> instance
    {
        int_vector_t    vi;

#if 0
        { // Initialise the vector<int> with an int_range
            for(int_range ir(0, 20, 2); ir; vi.push_back(*ir), ++ir);
        }
#else /* ? 0 */
        r_copy(int_range(0, 20, 2), std::back_inserter(vi));
#endif /* 0 */

        int sum_1   =   std::accumulate(vi.begin(), vi.end(), int(0));
        int sum_2   =   r_accumulate(int_range(0, 20, 2), int(0));

        // Now we adapt the vector<int> into a range
        sequence_range<int_vector_t>    vir(vi);

        printf("Enumerating sequence_range<int_vector_t> manually\n");
        for(; vir; ++vir)
        {
            print_int(*vir);
        }
        puts("");

        printf("Enumerating sequence_range<int_vector_t> via r_for_each()\n");
        r_for_each(vir, print_int);
        puts("");

        // Using an int_range
        {
            sequence_range<int_vector_t>    vir(vi);

            printf("Enumerating sequence_range<int_vector_t> via r_for_each()\n");
            r_for_each(vir, print_int);
            puts("");
        }
    }

    // Make a file for using in the rest of the test prog
    {
        int                 i
            ,               iarray[] = { 1,3,5,7,11,13,17,19 };
        std::fstream        my_file("vector.dat", std::ios::out);// Add |ios::nocreate to avoid 
                                               // creation if it doesn't exist
        std::vector<int>    v1
            ,               v2;

        for(i = 0; i < sizeof(iarray) / sizeof(iarray[0]); ++i)
        {
            v1.push_back(iarray[i]);
        }

        //  Write v1 to file
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(my_file, " "));
//      std::cout << "Wrote vector v1 to file vector.dat" << std::endl;

        //  Close file
        my_file.close();
    }

    // Using the iterator_range
    {
        std::cout << std::endl << "Testing vector<>" << std::endl;

        int_vector_t    vi;

        for(int_range ir(0, 20, 2); ir; vi.push_back(*ir), ++ir);

        {
            iterator_range<int_vector_t::iterator>  r(vi.begin(), vi.end());

            std::cout << "Count: " << r_distance(r) << std::endl;
            for(; r; ++r)
            {
                print_int(*r);

                ++*r;

                print_int(*r);
            }
            puts("");
        }

        {
            iterator_range<int_vector_t::const_iterator>    r(vi.begin(), vi.end());

            for(; r; ++r)
            {
                print_int(*r);
            }
            puts("");
        }

        {
            iterator_range<int_vector_t::const_iterator>    r(vi.begin(), vi.end());

            r_for_each(r, print_int);
            puts("");
        }
    }

    // Using the iterator_range
    {
        std::cout << std::endl << "Testing list<>" << std::endl;

        int_list_t  vi;

        for(int_range ir(0, 20, 2); ir; vi.push_back(*ir), ++ir);

        {
            iterator_range<int_list_t::iterator>    r(vi.begin(), vi.end());

            std::cout << "Count: " << r_distance(r) << std::endl;
            for(; r; ++r)
            {
                print_int(*r);

                ++*r;

                print_int(*r);
            }
            puts("");
        }

        {
            iterator_range<int_list_t::const_iterator>  r(vi.begin(), vi.end());

            for(; r; ++r)
            {
                print_int(*r);
            }
            puts("");
        }

        {
            iterator_range<int_list_t::const_iterator>  r(vi.begin(), vi.end());

            r_for_each(r, print_int);
            puts("");
        }
    }

    // Using the iterator_range
#if !defined(_MSC_VER) || \
    _MSC_VER >= 1300
    {
        std::cout << std::endl << "Testing istream_iterator<>" << std::endl;

        typedef std::istream_iterator<int>      isit;
        typedef std::iterator_traits<isit>      isit_traits;

        typedef isit_traits::pointer            p;

        std::fstream my_file;

        my_file.open("vector.dat", std::ios::in|std::ios::out);

#if defined(__GNUC__) || \
    defined(_MSC_VER) || \
    defined(__INTEL_COMPILER)
        iterator_range<isit>    r(*&isit(my_file), isit());
#else /* ? compiler */
        iterator_range<isit>    r(isit(my_file), isit());
#endif /* compiler */

        std::cout << "Dumping contents of vector.dat: ";
        for(; r; ++r)
        {
            std::cout << (*r) << " ";
        }

        std::cout << std::endl;
    }
#endif /* !_MSC_VER || _MSC_VER >= 1300 */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
