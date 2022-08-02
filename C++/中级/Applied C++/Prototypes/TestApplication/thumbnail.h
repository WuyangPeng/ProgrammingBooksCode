#ifndef _thumbnail_h_
#define _thumbnail_h_

//  thumbnail.h
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

#include "image.h"

// 标尺
// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

// *****************
// *               *
// *  apThumbNail  *
// *               *
// *****************
//
//  apThumbNail reads an input file and produces an output file
//  which is a specified reduction of the original.
//  apThumbNail读取输入文件并生成输出文件，该文件是原始文件的指定缩小版本。

class apThumbNail
{
public:
    apThumbNail();
    ~apThumbNail();

    // The default copy constructor and assignment operator is ok
    // 默认的复制构造函数和赋值运算符是ok的

    void createThumbNail(const char* inputFile, const char* outputFile, int factor);
    // Create thumbnail with specified reduction factor (2,3,..)
    // 创建具有指定缩小系数（2,3,..）的缩略图

    class invalid
    {
    };
    // Exception we'll throw when an error is detected
    // 检测到错误时将抛出异常

private:
    void readImage(const char* inputFile);
    void writeImage(const char* outputFile) const;
    // Read original image and write thumbnail image.
    // 读取原始图像并写入缩略图。

    unsigned char averagePixels(int x0, int y0, int factor);
    // Produces a single output pixel in the thumbnail image
    // 在缩略图图像中产生一个输出像素

    apImage image_;  // input image（输入像素）
    apImage thumbnail_;  // thumbnail image（缩略图）
};

#endif  // _thumbnail_h_
