/* /////////////////////////////////////////////////////////////////////////////
 * File:        local_ftor_test.cpp
 *
 * Purpose:     Implementation file for the local_ftor_test project.
 *
 * Created:     11th November 2003
 * Updated:     23rd January 2004
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

#ifdef __DMC__
# include <iostream.h>
#else /* ? __DMC__ */
# include <iostream>
# ifndef __WATCOMC__
using std::cout;
using std::endl;
# endif /* __WATCOMC__ */
#endif /* __DMC__ */
#include <algorithm>
#if !defined(__DMC__) && \
    !defined(__WATCOMC__)
using std::for_each;
#endif /* !__DMC__ && !__WATCOMC__ */

#include <stlsoft.h>
#include <stlsoft_simple_algorithms.h>

#include <list>

/* ////////////////////////////////////////////////////////////////////////// */

void print_int(int const &i)
{
    cout << i << endl;
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace
{
    struct int_processor
    {
    public:
        virtual void operator ()(int const &i) const = 0;
    };
} // namespace

struct int_processor_st
{
public:
    virtual void operator ()(int const &i) const = 0;
};


template<   ss_typename_param_k F
        ,   ss_typename_param_k I
        >
inline F for_each_l(I first, I last, F fn)
{
#if 0
    for(; first != last; ++first)
    {
        fn(*first);
    }

    return fn;
#else /* ? 0 */
    return stlsoft_ns_qual_std(for_each)<I, F>(first, last, fn);
#endif /* 0 */
}



/* 
template <typename T>
struct local_ftor_traits
{
    typedef typename T::base_functor_type   base_functor_type;
};

template <typename T>
typename T::base_functor_type const &get_ftor_base(T const &t)
{
    return t;
}
 */
int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    cout << "local_ftor_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;

    /* . */
    int const   ari[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for_each(&ari[0], &ari[10], print_int);

#ifdef IN_X
    class X
    {
    public:
#endif /* IN_X */
        struct int_printer
            : /* public  */int_processor
        {
        public:
/*          typedef int_processor   base_functor_type;
            typedef int_printer     class_type;
 */
            void operator ()(int const &i) const
            {
                print_int(i);
            }

/*          static base_functor_type const &get_ftor_base(class_type const &this_)
            {
                return this_;
            }
 */     };
#ifdef IN_X
    };
#endif /* IN_X */

    cout
        << "Via the nested functor "
#ifdef IN_X
        << "X::"
#endif /* IN_X */
        << "int_printer()"
        << endl;

#if 0
#ifdef IN_X
    for_each(&ari[0], &ari[10], X::int_printer());
#else /* ? IN_X */
    for_each(&ari[0], &ari[10], int_printer());
#endif /* IN_X */
#else /* ? 0 */
//  for_each<int*, int_processor const &>(&ari[0], &ari[10], int_printer());
    for_each<int const *, int_processor const &>(&ari[0], &ari[10], int_printer());
    for_each_l<int_processor const &>(&ari[0], &ari[10], int_printer());
//  for_each(&ari[0], &ari[10], static_cast<int_processor const&>(int_printer()));
//  for_each(&ari[0], &ari[10], int_printer::get_ftor_base(int_printer()));
#endif /* 0 */

    std::list<int>      li;

    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);

    for_each<std::list<int>::const_iterator, int_processor const &>(li.begin(), li.end(), int_printer());

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
