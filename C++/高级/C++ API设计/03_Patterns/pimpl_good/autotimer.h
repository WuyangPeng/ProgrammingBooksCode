/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   autotimer.h
/// \author Martin Reddy
/// \brief  An example of an API using the Pimpl idiom.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#include <string>

namespace apibook
{
    ///
    /// An object that reports how long it was alive for when it
    /// is destroyed.
    /// �����������ʱ���ʱ��Ķ���
    ///
    class AutoTimer
    {
    public:
        /// Create a new timer object with a human-readable name
        /// ʹ�������������ƴ���һ���µļ�ʱ������
        explicit AutoTimer(const std::string& name);
        /// On destruction, the timer reports how long it was alive
        /// ����ʱ����ʱ������������ʱ��
        ~AutoTimer();

    private:
        // Make this object be noncopyable because it holds a pointer
        AutoTimer(const AutoTimer&) = delete;
        const AutoTimer& operator=(const AutoTimer&) = delete;

        class Impl;
        Impl* mImpl;
    };

}

#endif
