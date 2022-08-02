// johnpaul/john.hpp
#ifndef JOHN_HPP_INCLUDED
#define JOHN_HPP_INCLUDED

void john( ); // Prints "John, "

#endif // JOHN_HPP_INCLUDED

// johnpaul/john.cpp
#include <iostream>
#include "john.hpp"

void john( )
{
   std::cout << "John, ";
}

// johnpaul/paul.hpp
#ifndef PAUL_HPP_INCLUDED
#define PAUL_HPP_INCLUDED

void paul( ); // Prints " Paul, "

#endif // PAUL_HPP_INCLUDED

// johnpaul/paul.cpp
#include <iostream>
#include "paul.hpp"

void paul( )
{
   std::cout << "Paul, ";
}

// johnpaul/johnpaul.hpp
#ifndef JOHNPAUL_HPP_INCLUDED
#define JOHNPAUL_HPP_INCLUDED

void johnpaul( ); // Prints "John, Paul, "

#endif // JOHNPAUL_HPP_INCLUDED

// johnpaul/johnpaul.cpp

#include "john.hpp"
#include "paul.hpp"
#include "johnpaul.hpp"

void johnpaul( )
{
   john( );
   paul( );
}
