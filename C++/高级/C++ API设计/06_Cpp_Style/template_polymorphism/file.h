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
    /// ASCII�ı��ļ�
    ///
    class TextFile
    {
    public:
        void Open();
    };

    ///
    /// A bitmapped image file
    /// λͼͼ���ļ�
    ///
    class ImageFile
    {
    public:
        void Open();
    };

    // function template to open a given file
    // ����ģ���Դ򿪸����ļ�
    template <typename T>
    void open_file(T file)
    {
        file.Open();
    }

}

#endif
