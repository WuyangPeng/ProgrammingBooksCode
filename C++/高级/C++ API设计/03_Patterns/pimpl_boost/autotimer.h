/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   autotimer.h
/// \author Martin Reddy
/// \brief  An example of Pimpl with a smart pointer.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#include <boost/scoped_ptr.hpp>
#include <string>

namespace apibook
{
    ///
    /// An object that reports how long it was alive for when it
    /// is destroyed.
    /// 报告对象销毁时存活时间的对象。
    ///
    class AutoTimer
    {
    public:
        /// Create a new timer object with a human-readable name
        /// 使用易于理解的名称创建一个新的计时器对象
        explicit AutoTimer(const std::string& name);
        /// On destruction, the timer reports how long it was alive
        ~AutoTimer();

    private:
        class Impl;
        boost::scoped_ptr<Impl> mImpl;
    };

}

#endif
