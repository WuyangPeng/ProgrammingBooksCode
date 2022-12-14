/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It was built successfully with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter3-example13.o example13.cpp
        

*/

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
    namespace mpl
    {
    }
}
namespace mpl = boost::mpl;

#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/vector_c.hpp>
namespace
{
    typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
    typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;  // or position
    typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
    typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> angle;

}

// base dimension:        m l  t ...
typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;  // l/t
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;  // l/(t2)
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;  // ml/t
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;  // ml/(t2)

typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;

template <class T, class Dimensions>
struct quantity
{
    // converting constructor
    template <class OtherDimensions>
    quantity(quantity<T, OtherDimensions> const& rhs)
        : m_value(rhs.value())
    {
    }
    // ...

    explicit quantity(T x)
        : m_value(x)
    {
    }

    T value() const
    {
        return m_value;
    }

private:
    T m_value;
};

quantity<float, length> l(1.0f);
quantity<float, mass> m13(2.0f);

template <class T, class D>
quantity<T, D>
    operator+(quantity<T, D> x, quantity<T, D> y)
{
    return quantity<T, D>(x.value() + y.value());
}

template <class T, class D>
quantity<T, D>
    operator-(quantity<T, D> x, quantity<T, D> y)
{
    return quantity<T, D>(x.value() - y.value());
}

void test1()
{
    quantity<float, length> len1(1.0f);
    quantity<float, length> len2(2.0f);

    len1 = len1 + len2;  // OK
}

template <class Sequence1, class Sequence2, class BinaryOperation>
struct transform;  // returns a Sequence

#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;

BOOST_STATIC_ASSERT((mpl::plus<mpl::int_<2>, mpl::int_<3>>::type::value == 5));

struct plus_f
{
    template <class T1, class T2>
    struct apply
    {
        typedef typename mpl::plus<T1, T2>::type type;
    };
};

template <class T, class D1, class D2>
quantity<
    T, typename mpl::transform<D1, D2, plus_f>::type  // new dimensions
    >
    operator*(quantity<T, D1> x, quantity<T, D2> y)
{
    typedef typename mpl::transform<D1, D2, plus_f>::type dim;
    return quantity<T, dim>(x.value() * y.value());
}

void bogus2(quantity<float, mass> m, quantity<float, acceleration> a)
{
    // Should yield a force, not a mass!
    quantity<float, mass> bogus = m * a;
}
