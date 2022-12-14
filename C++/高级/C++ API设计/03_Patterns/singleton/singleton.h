/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   singleton.h
/// \author Martin Reddy
/// \brief  An example of the Singleton design pattern.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>

///
/// A class that enforces the policy that only one
/// instance is ever created.
/// 实现仅创建一个实例的策略的类。
///
class Singleton
{
public:
    /// Return the single instance of this class
    /// 返回此类的单个实例
    static Singleton& GetInstance();

    /// Return some class-specific single-instance state
    /// 返回一些特定于类的单实例状态
    int GetState();

private:
    // Prevent construction and copying of this class
    Singleton();
    ~Singleton();
    Singleton(const Singleton&) = delete;
    const Singleton& operator=(const Singleton&) = delete;
};

#endif
