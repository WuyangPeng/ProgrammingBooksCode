/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   stack.h
/// \author Martin Reddy
/// \brief  An example of a pre-processor based API.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef STACK_H
#define STACK_H

#include <string>
#include <vector>

/// A macro to declare a stack of any type
/// �����κ����͵�stack�ĺ�
#define DECLARE_STACK(Prefix, T) \
    class Prefix##Stack          \
    {                            \
    public:                      \
        void Push(T val);        \
        T Pop();                 \
        bool IsEmpty() const;    \
                                 \
    private:                     \
        std::vector<T> mStack;   \
    };

// Use the above macro to define stacks of ints, strings, and doubles
// ʹ������ĺ궨��int��string��double��stacks
DECLARE_STACK(Int, int);
DECLARE_STACK(String, std::string);
DECLARE_STACK(Double, double);

#endif
