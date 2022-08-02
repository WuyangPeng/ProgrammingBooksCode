///////////////////////////////////////////////////////////////////////////////
//
// Fib.h
//
// Demonstrates template metaprogramming for Fibonacci sequence
//
// Defines the following template functions, where n is an unsigned int
//
//    FibT( n )
//
// Copyright ?2000 Pete Isensee (PKIsensee@msn.com).
// All rights reserved worldwide.
//
// Permission to copy, modify, reproduce or redistribute this source code is
// granted provided the above copyright notice is retained in the resulting
// source code.
//
// This software is provided "as is" and without any express or implied
// warranties.
//
///////////////////////////////////////////////////////////////////////////////

// Template Fibonacci
template <unsigned N>
struct Fib
{
    enum
    {
        // Recursive definition
        // 递归定义
        Val = static_cast<int>(Fib<N - 1>::Val) + static_cast<int>(Fib<N - 2>::Val)
    };
};

// Specialization for base cases (termination conditions)
// 基本情况的模板特化
// （结束条件）
template <>
struct Fib<0>
{
    enum
    {
        Val = 0
    };
};

template <>
struct Fib<1>
{
    enum
    {
        Val = 1
    };
};

// Make the template appear like a function
// 让该模板形如函数
#define FibT(n) Fib<n>::Val

///////////////////////////////////////////////////////////////////////////////
