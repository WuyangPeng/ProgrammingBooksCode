/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   myobject.h
/// \author Martin Reddy
/// \brief  A simple class to demonstrate shared pointers.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <boost/shared_ptr.hpp>

namespace apibook
{
    /// A reference-counted pointer to MyObject
    /// 引用计数的指向MyObject的指针
    typedef boost::shared_ptr<class MyObject> MyObjectPtr;

    ///
    /// A class that lets you create reference-counted
    /// pointers to itself via a factory method. The
    /// constructor is declared to be private, so you
    /// have to use CreateInstance() instead of new to
    /// create instances of MyObject.
    ///
    /// 一个类，使您可以通过工厂方法创建指向其自身的引用计数的指针。 
    /// 构造函数被声明为私有的，因此您必须使用CreateInstance()而不是new来创建MyObject的实例。
    class MyObject
    {
    public:
        /// Create a new (reference-counted) instance of MyObject
        static MyObjectPtr CreateInstance(int id);
        ~MyObject();

    private:
        MyObject(int id);
        int mID;
    };

}

#endif
