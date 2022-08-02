// plus.hpp
#ifndef PLUS_HPP_INCLUDED
#define PLUS_HPP_INCLUDED

export template<typename T>
T plus(const T& lhs, const T& rhs);

#endif // #ifndef PLUS_HPP_INCLUDED

// plus.cpp:
#include "plus.hpp"

template<typename T>
T plus(const T& lhs, const T& rhs)
{
  return rhs + lhs;
}

// test.cpp:
#include <iostream>
#include "plus.hpp"

int main( )
{
  std::cout << "2 + 2 = " << plus(2, 2) << "\n";
}
