/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   myobject.cpp
/// \author Martin Reddy
/// \brief  Showing how "internal" details can be leaked.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "myobject.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

// Uncomment the next line to prevent external linkage leakage
// 取消注释下一行以防止外部链接泄漏
// namespace {

// an integer constant with external linkage
// 具有外部链接的整数常量
int INTERNAL_CONSTANT = 42;

// a string constant with external linkage
// 具有外部链接的字符串常量
std::string Filename = "file.txt";

// a non-static function with external linkage
// 具有外部链接的非静态函数
void FreeFunction()
{
    cout << "Free function called" << endl;
}

// Uncomment the next line to prevent external linkage leakage
//}

namespace apibook
{
    void MyObject::SetValue(int value)
    {
        mValue = value;
    }

    int MyObject::GetValue() const
    {
        return mValue;
    }

}
