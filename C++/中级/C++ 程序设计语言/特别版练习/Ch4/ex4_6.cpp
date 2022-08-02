/* Code for exercise 4.6.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

/*

This file may cause all sorts of problems for various compilers and
associated tools. Here is one message of a compiler that attempted
processing of this file. It speaks for itself:
   External symbol too long, truncated from 14328 to 4000 bytes,
   f__FP8DoublifyXT8DoublifyXT8DoublifyXT8DoublifyXT8DoublifyXT8DoublifyXT8Dou
   blifyXT8DoublifyXT8DoublifyXT8DoublifyXTdTd_T8Doublif...

*/

template<typename T, typename U>
struct Doublify {};
template<int N>
struct Exponential {
   typedef Doublify<typename Exponential<N-1>::LongType,
                    typename Exponential<N-1>::LongType>
           LongType;
};

template<>
struct Exponential<0> {
   typedef double LongType;
};

int f(Exponential<10>::LongType*) {
   return 3;
}

