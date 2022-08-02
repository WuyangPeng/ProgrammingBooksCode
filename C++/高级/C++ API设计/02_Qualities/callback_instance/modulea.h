/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   modulea.h
/// \author Martin Reddy
/// \brief  A module that uses one of its methods as a callback.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef MODULEA_H
#define MODULEA_H

#include <string>

namespace apibook
{
    ///
    /// An object that wishes to receive a callback from another
    /// module. To simplify calling an member function for a
    /// specific instance of this class, a static wrapper function
    /// can be used for the callback. This essentially accepts the
    /// object instance as an additional parameter.
    ///
    /// 希望从另一个模块接收回调的对象。
    /// 为了简化为此类的特定实例调用成员函数的方法，可以将静态包装函数用于回调。
    /// 这实际上接受了对象实例作为附加参数。
    class ModuleA
    {
    public:
        /// A static function that lets you call a member function
        /// 静态函数，可让您调用成员函数
        static void StaticWrapper(void* obj, const std::string& name, void* data);

        /// The member function callback
        /// 成员函数回调
        void InstanceMethod(const std::string& name, void* data);
    };

}

#endif
