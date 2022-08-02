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

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter9-example35.exe example35.cpp
        

*/
#include <vector>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


#include <iterator>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/iterator/iterator_traits.hpp>   

template <class Iterator>
typename boost::enable_if<
    boost::is_arithmetic<               // enabling condition
       typename boost::iterator_value<Iterator>::type
    >
  , typename                            // return type
      boost::iterator_value<Iterator>::type    
>::type
sum(Iterator start, Iterator end)
{
    typename boost::iterator_value<Iterator>::type x(0);
    for (;start != end; ++start)
        x += *start;
    return x;
}


// given an Iterator that points to a container, get the
// value_type of that container's iterators.
template <class Iterator>
struct inner_value
  : boost::iterator_value<
      typename boost::iterator_value<Iterator>::type::iterator
    >
{};

template <class Iterator>
typename boost::lazy_disable_if<
    boost::is_arithmetic<               // disabling condition
       typename boost::iterator_value<Iterator>::type
    >
  , inner_value<Iterator>               // result metafunction
>::type
sum(Iterator start, Iterator end)
{
    typename inner_value<Iterator>::type x(0);

    for (;start != end; ++start)
        x += sum(start->begin(), start->end());

    return x;
}

    #include <boost/iterator/counting_iterator.hpp>
    #include <cassert>
    
    std::vector<int> x(
        boost::make_counting_iterator(3)
      , boost::make_counting_iterator(15)
    );

    std::vector<std::vector<int> > y(3, x);
    int main()
    {
         assert(sum(x.begin(), x.end()) == 102);
         assert(sum(y.begin(), y.end()) == 102 * 3);
    }
    

