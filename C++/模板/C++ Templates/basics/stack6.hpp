/* The following code example is taken from the book
 * "C++ Templates - The Complete Guide"
 * by David Vandevoorde and Nicolai M. Josuttis, Addison-Wesley, 2002
 *
 * (C) Copyright David Vandevoorde and Nicolai M. Josuttis 2002.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <stdexcept>

#include "stack6decl.hpp"
#include "stack6assign.hpp"

template <typename T, typename CONT>
void Stack<T,CONT>::push (T const& elem)
{
    elems.push_back(elem);    // append copy of passed elem
}

template<typename T, typename CONT>
void Stack<T,CONT>::pop ()
{
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();         // remove last element
}

template <typename T, typename CONT>
T Stack<T,CONT>::top () const
{
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();      // return copy of last element
}

#endif // STACK_HPP
