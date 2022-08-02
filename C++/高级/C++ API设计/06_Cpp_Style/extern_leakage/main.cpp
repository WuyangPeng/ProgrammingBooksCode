/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   main.cpp
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

// declare the external linkage elements of myobject.cpp
// 声明myobject.cpp的外部链接元素
extern void FreeFunction();
extern int INTERNAL_CONSTANT;
extern std::string Filename;

int main(int, char**)
{
    // call a function hidden within the myobject.cpp module
    // 调用隐藏在myobject.cpp模块内的函数
    FreeFunction();

    // access a constant defined within myobject.cpp
    // 访问在myobject.cpp中定义的常量
    std::cout << "Internal constant = " << INTERNAL_CONSTANT << std::endl;

    // change global state within myobject.cpp
    // 在myobject.cpp中更改全局状态
    Filename = "different.txt";

    return 0;
}
