// georgeringo/george.hpp
#ifndef GEORGE_HPP_INCLUDED
#define GEORGE_HPP_INCLUDED

void george( ); // Prints "George, "

#endif // GEORGE_HPP_INCLUDED

// georgeringo/george.cpp
#include <iostream>
#include "george.hpp"

void george( )
{
   std::cout << "George, ";
}

// georgeringo/ringo.hpp
#ifndef RINGO_HPP_INCLUDED
#define RINGO_HPP_INCLUDED

void ringo( ); // Prints "and Ringo\n"

#endif // RINGO_HPP_INCLUDED

// georgeringo/ringo.cpp
#include <iostream>
#include "ringo.hpp"

void ringo( )
{
   std::cout << "and Ringo\n";
}

// georgeringo/georgeringo.hpp
#ifndef GEORGERINGO_HPP_INCLUDED
#define GEORGERINGO_HPP_INCLUDED
// define GEORGERINGO_DLL when building libgerogreringo.dll
# if defined(_WIN32) && !defined(__GNUC__)
# ifdef GEORGERINGO_DLL
# define GEORGERINGO_DECL _ _declspec(dllexport)
# else
# define GEORGERINGO_DECL _ _declspec(dllimport)
# endif
# endif // WIN32
#ifndef GEORGERINGO_DECL
# define GEORGERINGO_DECL
#endif
// Prints "George, and Ringo\n"
#ifdef __MWERKS__
# pragma export on
#endif

GEORGERINGO_DECL void georgeringo( );

#ifdef __MWERKS__
# pragma export off
#endif
#endif // GEORGERINGO_HPP_INCLUDED

// georgeringo/ georgeringo.cpp
#include "george.hpp"
#include "ringo.hpp"
#include "georgeringo.hpp"

void georgeringo( )
{
   george( );
   ringo( );
}
