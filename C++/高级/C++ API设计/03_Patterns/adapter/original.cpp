/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   original.cpp
/// \author Martin Reddy
/// \brief  An original class to be wrapped by an Adapter.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "original.h"
#include <iostream>

using std::cout;
using std::endl;

void Original::DoOperation(int value, bool extra_arg)
{
    cout << "In Original::DoSomething with value " << value;
    cout << " and flag " << extra_arg << endl;
}
