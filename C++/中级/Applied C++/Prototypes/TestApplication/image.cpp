// image.cpp
//
// Copyright (c) 2003 Philip Romanik, Amy Muntz
//
// Permission to use, copy, modify, distribute, and sell this software and
// its documentation for any purpose is hereby granted without fee, provided
// that (i) the above copyright notices and this permission notice appear in
// all copies of the software and related documentation, and (ii) the names
// of Philip Romanik and Amy Muntz may not be used in any advertising or
// publicity relating to the software without the specific, prior written
// permission of Philip Romanik and Amy Muntz.
//
// Use of this software and/or its documentation will be deemed to be
// acceptance of these terms.
//
// THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL PHILIP ROMANIK OR AMY MUNTZ BE LIABLE FOR
// ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
//
// Simple stand-alone thumbnail generator program
// 简单的独立缩略图生成器程序

#include "image.h"

#include <memory.h>  // memcpy

// 标尺
// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

// *************
// *           *
// *  apImage  *
// *           *
// *************

apImage::apImage()
    : width_(0), height_(0), pixels_(nullptr)
{
}

apImage::apImage(int width, int height)
    : width_(width), height_(height), pixels_(nullptr)
{
    init();
}

apImage::apImage(const apImage& src)
    : width_(0), height_(0), pixels_(nullptr)
{
    if (src.isValid())
    {
        // Recreate the information in the source image
        // 在源映像中重新创建信息
        width_ = src.width();
        height_ = src.height();
        init();
        memcpy(pixels_, src.pixels_, width_ * height_);
    }
}

template <class T>
void swap(T& a, T& b)
{
    T copy(a);
    a = b;
    b = copy;
}

void apImage::swap(apImage& src)
{
    ::swap(width_, src.width_);
    ::swap(height_, src.height_);
    ::swap(pixels_, src.pixels_);
}

apImage& apImage::operator=(const apImage& src)
{
    apImage temp(src);
    swap(temp);

    return *this;
}

/* This is the original assignment operator that does not take
   advantage of the Sutter solution
   这是原始的赋值运算符，没有利用Sutter的解决方案

apImage& apImage::operator= (const apImage& src)
{
  if (&src != this) {
    // Delete any existing data and recreate the source image
    // 删除任何现有数据并重新创建源图像
    cleanup ();
    width_  = src.width ();
    height_ = src.height ();
    init ();

    memcpy (pixels_, src.pixels_, width_ * height_);
  }

  return *this;
}
*/

apImage::~apImage()
{
    cleanup();
}

void apImage::cleanup()
{
    // Put the object back into its original, null state.
    // 将对象放回其原始的空状态。
    delete[] pixels_;

    width_ = 0;
    height_ = 0;
    pixels_ = nullptr;
}

void apImage::init()
{
    // All memory allocation passes through this function.
    // 所有内存分配都通过此函数进行。
    if (width_ > 0 && height_ > 0)
    {
        pixels_ = new unsigned char[width_ * height_];
    }
}

void apImage::setPixel(int x, int y, unsigned char pixel)
{
    if (x < 0 || y < 0 || x >= width_ || y >= height_ || !isValid())
    {
        throw rangeError();
    }

    // Image data is stored a row at a time.
    // 图像数据一次存储一行。
    unsigned char* p = pixels_ + y * width_ + x;
    *p = pixel;
}

unsigned char apImage::getPixel(int x, int y) const
{
    if (x < 0 || y < 0 || x >= width_ || y >= height_ || !isValid())
    {
        throw rangeError();
    }

    // Image data is stored a row at a time.
    // 图像数据一次存储一行。
    unsigned char* p = pixels_ + y * width_ + x;
    return *p;
}
