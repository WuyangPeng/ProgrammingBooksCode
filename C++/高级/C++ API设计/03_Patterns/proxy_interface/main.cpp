/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   main.cpp
/// \author Martin Reddy
/// \brief  A Proxy design pattern using a common interface.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "proxy.h"

int main(int, char**)
{
    // create a proxy instance and call one of its functions
    // ����һ������ʵ���������亯��֮һ
    Proxy proxy;
    proxy.DoSomething(42);

    return 0;
}
