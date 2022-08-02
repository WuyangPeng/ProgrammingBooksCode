/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   proxy.cpp
/// \author Martin Reddy
/// \brief  A Proxy design pattern using a common interface.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "original.h"
#include "proxy.h"
#include <iostream>

using std::cout;
using std::endl;

Proxy::Proxy()
    : mOrig(new Original)
{
    cout << "Allocated new Original object inside Proxy" << endl;
}

Proxy::~Proxy()
{
    delete mOrig;
    cout << "Destroyed Original object inside Proxy" << endl;
}

bool Proxy::DoSomething(int value)
{
    cout << "About to call Original::DoSomething from Proxy" << endl;
    return mOrig->DoSomething(value);
}
