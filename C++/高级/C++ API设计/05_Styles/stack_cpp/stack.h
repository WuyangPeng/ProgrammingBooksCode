/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   stack.h
/// \author Martin Reddy
/// \brief  An example of an object-oriented C++ style API.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef STACK_H
#define STACK_H

#include <vector>

namespace apibook
{
    ///
    /// A C++ class for a stack of integers.
    /// 整数stack的C++类。
    ///
    class IntStack
    {
    public:
        /// Push a new integer to the stack
        /// 将新的整数压入stack
        void Push(int val);
        /// Pop the last integer off the stack
        /// 将最后一个整数弹出stack
        int Pop();
        /// Return true if the stack contains no values
        /// 如果stack不包含任何值，则返回true
        bool IsEmpty() const;

    private:
        std::vector<int> mStack;
    };

}

#endif
