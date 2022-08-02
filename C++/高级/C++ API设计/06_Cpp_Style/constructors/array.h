/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   array.h
/// \author Martin Reddy
/// \brief  An example of using constructors and assignment.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef ARRAY_H
#define ARRAY_H

#include <string>

namespace apibook
{
    ///
    /// An array of elements.
    ///
    class Array
    {
    public:
        /// default constructor
        Array();
        /// non-default constructor
        explicit Array(int size);
        /// destructor
        ~Array();
        /// copy constructor
        Array(const Array& in_array);
        /// assignment operator
        Array& operator=(const Array& in_array);

        /// Return the element at the given array index
        /// 返回给定数组索引处的元素
        std::string Get(int index) const;
        /// Set the element at the given array index
        /// 设置为给定的数组索引的元素
        bool Set(int index, const std::string& str);
        /// Return the number of elements in the array
        /// 返回数组中的元素数
        int Size() const;
        /// Output the array contents to stdout
        /// 将数组内容输出到stdout
        void Print() const;

    private:
        int mSize;
        std::string* mArray;
    };

}

#endif
