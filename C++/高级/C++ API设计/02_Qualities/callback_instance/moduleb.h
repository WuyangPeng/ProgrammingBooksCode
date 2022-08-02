/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   moduleb.h
/// \author Martin Reddy
/// \brief  A module that invokes a callback method.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef MODULEB_H
#define MODULEB_H

#include <stdlib.h>
#include <string>

namespace apibook
{
    ///
    /// An object that can register a callback function and then
    /// invoke that callback when desired.
    ///
    /// 可以注册回调函数，然后在需要时调用该回调的对象。
    class ModuleB
    {
    public:
        /// A type for the function signature that is accepted as a callback
        /// 接受为回调的函数签名的类型
        typedef void (*CallbackType)(void* obj, const std::string& name, void* data);

        ModuleB();

        /// Set the callback function. Only one callback can be registered.
        /// 设置回调函数。 只能注册一个回调。
        void SetCallback(void* obj, CallbackType cb, void* data);
        /// Call the callback function.
        void DoAction();

    private:
        void* mObject;
        CallbackType mCallback;
        void* mClosure;
    };

}

#endif
