#ifndef _image_h_
#define _image_h_

// image.h
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
//  Simple stand-alone thumbnail generator program
//  简单的独立缩略图生成器程序

#include <stdio.h>  // for NULL definition（对于NULL定义）

// 标尺
// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

// *************
// *           *
// *  apImage  *
// *           *
// *************
//
//  apImage is a simple image class that allocates memory for an
//  8-bit monochrome image and allows random access to the image
//  data.
//  apImage是一个简单的图像类，可为8位单色图像分配内存，并允许随机访问图像数据。

class apImage
{
public:
    apImage();
    // Creates a null image, suitable for later assignment
    // 创建一个空图像，适用于以后的分配

    apImage(int width, int height);
    // Creates an image of the specified size
    // 创建指定大小的图像

    ~apImage();

    apImage(const apImage& src);
    apImage& operator=(const apImage& src);
    // We need to define our own copy constructor and assignment
    // operator since a member copy will not suffice.
    // 我们需要定义自己的复制构造函数和赋值运算符，因为成员复制无法满足要求。

    void swap(apImage& src);
    // Used during assignment (Sutter, Exceptional C++) to make the
    // assignment operator exception safe
    // 在赋值期间使用（Sutter，Exceptional C++）以使赋值运算符异常安全。

    void setPixel(int x, int y, unsigned char pixel);
    unsigned char getPixel(int x, int y) const;
    // Write/read an individual pixel.
    // Throws rangeError if the coordinates are invalid.
    // 写入/读取单个像素。
    // 如果坐标无效，则抛出rangeError。

    bool isValid() const
    {
        return pixels_ != nullptr;
    }
    // Tests if the image data exists, and presumably valid.
    // 测试图像数据是否存在，并且大概有效。

    int width() const
    {
        return width_;
    }
    int height() const
    {
        return height_;
    }
    // Return the extent of the image
    // 返回图像的范围

    class rangeError
    {
    };
    // Error thrown if the requested data is not in the image
    // 如果请求的数据不在图像中，则会引发错误

private:
    void cleanup();
    // Reinitialize the object and free allocated memory
    // 重新初始化对象并释放已分配的内存

    void init();
    // Initialize image data
    // 初始化图像数据

    int width_;  // Image width（图像宽度）
    int height_;  // Image height（图像高度）
    unsigned char* pixels_;  // Image data（图像数据）
};

#endif  // _image_h_
