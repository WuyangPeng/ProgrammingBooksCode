/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   facade.h
/// \author Martin Reddy
/// \brief  An example of the Facade design pattern.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef FACADE_H
#define FACADE_H

///
/// An facade that wraps access to a sub-system.
/// 包含对子系统的访问权的外观。
///
class Facade
{
public:
    Facade();
    ~Facade();

    /// Call various functions in the sub-system to aggregate its functionality
    /// 调用子系统中的各种函数以汇总其功能
    bool DoSomething();

private:
    Facade(const Facade&) = delete;
    const Facade& operator=(const Facade&) = delete;

    class Impl;
    Impl* mImpl;
};

#endif
