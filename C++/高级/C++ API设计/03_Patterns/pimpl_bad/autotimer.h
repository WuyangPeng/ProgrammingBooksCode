/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   autotimer.h
/// \author Martin Reddy
/// \brief  A poor API that can be improved by Pimpl.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#include <string>
// Bad: only need iostream because of implementation code
// 仅由于实现代码而需要iostream
#include <iostream>

// Bad: exposes platform specifics in your header 
// 在头文件中公开平台细节
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

namespace apibook
{
    class AutoTimer
    {
    public:
        // Bad: exposes (and inlines) implementation details
        // 使用易于理解的名字创建新定时器
        explicit AutoTimer(const std::string& name)
            : mName(name)
        {
#ifdef _WIN32
            mStartTime = GetTickCount();
#else
            gettimeofday(&mStartTime, NULL);
#endif
        }

        /// 在销毁时，定时器报告生存时间。
        ~AutoTimer()
        {
            std::cout << mName << ": took " << GetElapsed()
                      << " secs" << std::endl;
        }

    private:
        // 返回对象已经存在了多长时间。
        // Bad: no need to expose this function publicly
        double GetElapsed() const
        {
#ifdef _WIN32
            return (GetTickCount() - mStartTime) / 1e3;
#else
            struct timeval end_time;
            gettimeofday(&end_time, NULL);
            double t1 = mStartTime.tv_usec / 1e6 + mStartTime.tv_sec;
            double t2 = end_time.tv_usec / 1e6 + end_time.tv_sec;
            return t2 - t1;
#endif
        }

        // Bad: data members should always be private
        std::string mName;
#ifdef _WIN32
        DWORD mStartTime;
#else
        struct timeval mStartTime;
#endif
    };

}

#endif
