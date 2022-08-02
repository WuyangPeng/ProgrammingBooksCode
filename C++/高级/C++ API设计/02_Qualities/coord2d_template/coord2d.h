/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   coord2d.h
/// \author Martin Reddy
/// \brief  An example templated 2D coordinate class.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef COORD2D_H
#define COORD2D_H

namespace apibook
{
    ///
    /// A class template to represent a 2D coordinate.
    ///
    /// 表示2D坐标的类模板。
    template <class T>
    class Coord2D
    {
    public:
        /// Construct a new coordinate with specific values
        /// 构造具有特定值的新坐标
        Coord2D(T x, T y);

        /// Return the X coordinate value
        T GetX() const;
        /// Return the Y coordinate value
        T GetY() const;

        /// Set the X coordinate value
        void SetX(T x);
        /// Set the Y coordinate value
        void SetY(T y);

        /// Add dx to the X coordinate and dy to the Y coordinate
        /// 将dx添加到X坐标，将dy添加到Y坐标
        void Add(T dx, T dy);
        /// Multiply the X coordinate by dx and the Y coordinate by dy
        /// X坐标乘以dx，Y坐标乘dy
        void Multiply(T dx, T dy);

    private:
        T mX, mY;
    };

}

// keep all implementation details in a separate header
#include "coord2d_detail.h"

#endif
