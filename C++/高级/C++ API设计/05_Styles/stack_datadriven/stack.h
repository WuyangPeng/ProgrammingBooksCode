/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   stack.h
/// \author Martin Reddy
/// \brief  An example of a data-driven style API.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef STACK_H
#define STACK_H

#include "arglist.h"
#include <vector>

namespace apibook
{
    ///
    /// A data-driven interface for a stack of values.
    ///
    class Stack
    {
    public:
        /// Perform a named operation on this stack with an optional
        /// list of arguments. The supported operations include:
        /// 使用可选的参数列表在此stack上执行命名操作。支持的操作包括：
        ///
        ///  - "Push": accepts a single integer argument
        ///  - "Pop": returns the integer on the top of the stack
        ///  - "IsEmpty": returns true if the stack contains no values
        ///  - "Push":接受单个整数参数
        ///  - "Pop": 返回stack顶部的整数
        ///  - "IsEmpty": 如果stack不包含任何值，则返回true
        Arg Command(const std::string& cmd, const ArgList& args = ArgList());

    private:
        std::vector<int> mStack;
    };

}

#endif
