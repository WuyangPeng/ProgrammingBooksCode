/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   file.h
/// \author Martin Reddy
/// \brief  Showing static polymorphism using templates.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef FILE_H
#define FILE_H

#include <stdio.h>

namespace apibook
{
    ///
    /// An ASCII text file
    /// ASCII文本文件
    ///
    class TextFile
    {
    public:
        void Open();
    };

    ///
    /// A bitmapped image file
    /// 位图图像文件
    ///
    class ImageFile
    {
    public:
        void Open();
    };

    // function template to open a given file
    // 函数模板以打开给定文件
    template <typename T>
    void open_file(T file)
    {
        file.Open();
    }

}

#endif
