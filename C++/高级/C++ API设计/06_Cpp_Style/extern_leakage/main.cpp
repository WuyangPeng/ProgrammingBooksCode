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
// ����myobject.cpp���ⲿ����Ԫ��
extern void FreeFunction();
extern int INTERNAL_CONSTANT;
extern std::string Filename;

int main(int, char**)
{
    // call a function hidden within the myobject.cpp module
    // ����������myobject.cppģ���ڵĺ���
    FreeFunction();

    // access a constant defined within myobject.cpp
    // ������myobject.cpp�ж���ĳ���
    std::cout << "Internal constant = " << INTERNAL_CONSTANT << std::endl;

    // change global state within myobject.cpp
    // ��myobject.cpp�и���ȫ��״̬
    Filename = "different.txt";

    return 0;
}
