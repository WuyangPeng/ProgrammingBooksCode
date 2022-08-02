/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   main.cpp
/// \author Martin Reddy
/// \brief  An example using Boost shared pointers.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "myobject.h"
#include <iostream>

using std::cout;
using std::endl;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    cout << "> main()" << endl;

    {
        apibook::MyObjectPtr ptr;

        // create a new instance of MyObject
        // 创建一个MyObject的新实例
        cout << "> CreateInstance(1)" << endl;
        ptr = apibook::MyObject::CreateInstance(1);

        // create another instance of MyObject
        cout << "> CreateInstance(2)" << endl;
        ptr = apibook::MyObject::CreateInstance(2);
    }
    // both instances get deleted when they go out of scope
    // 两个实例超出范围时都将被删除

    cout << "> exit()" << endl;
    return 0;
}
