///////////////////////////////////////////////////////////////////////////////
//
// Fact.h
//
// Demonstrates template metaprogramming for Factorials
//
// Defines the following template functions, where n is an unsigned int
//
//    FactT( n )
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

// Template Factorial
// 模板化阶乘（n）
template <unsigned N>
struct Fact
{
    enum
    {
        Val = N * Fact<N - 1>::Val
    };
};

// Specialization for base cases (termination conditions)
// 基本情况的模板特化
template <>
struct Fact<0>
{
    enum
    {
        Val = 1
    };
};

template <>
struct Fact<1>
{
    enum
    {
        Val = 1
    };
};

// Make the template appear like a function
// 让模板形如函数
#define FactT(n) Fact<n>::Val

///////////////////////////////////////////////////////////////////////////////
