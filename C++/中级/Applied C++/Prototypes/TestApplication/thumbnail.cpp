// thumbnail.cpp
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

#include "thumbnail.h"

#include <memory.h>
#include <stdio.h>

#include <iomanip>  // setw() manipulator（setw()操纵器）
#include <iostream>

// 标尺
// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

/*****************
 *               *
 *  apThumbNail  *
 *               *
 *****************/

apThumbNail::apThumbNail()
{
}

apThumbNail::~apThumbNail()
{
}

void apThumbNail::createThumbNail(const char* inputFile, const char* outputFile, int factor)
{
    // Validate the arguments
    // 验证参数
    if (inputFile == nullptr || outputFile == nullptr || factor <= 1)
    {
        throw invalid();
    }

    // Read the source image
    // 读取原始图片
    readImage(inputFile);
    if (!image_.isValid())
    {
        throw invalid();
    }

    // Create our internal thumbnail image
    // 创建我们的内部缩略图
    thumbnail_ = apImage(image_.width() / factor, image_.height() / factor);

    // Turn any rangeErrors from apImage into our invalid error
    // 将apImage中的所有rangeErrors转换为我们的无效错误
    try
    {
        for (int y = 0; y < thumbnail_.height(); y++)
        {
            for (int x = 0; x < thumbnail_.width(); x++)
            {
                // Convert to image_ coordinates to find the average
                // 转换为图像坐标以找到平均值
                unsigned char pixel = averagePixels(x * factor, y * factor, factor);
                thumbnail_.setPixel(x, y, pixel);
            }
        }
    }
    catch (apImage::rangeError)
    {
        throw invalid();
    }

    writeImage(outputFile);
}

unsigned char apThumbNail::averagePixels(int x0, int y0, int factor)
{
    int sum = 0;

    // Average factor x factor pixels in the input image
    // 输入图像中的平均因数像素
    try
    {
        for (int y = 0; y < factor; y++)
        {
            for (int x = 0; x < factor; x++)
            {
                sum += image_.getPixel(x + x0, y + y0);
            }
        }
    }
    catch (apImage::rangeError)
    {
        throw invalid();
    }

    // This cast is very safe
    // 这种转换是非常安全的
    return static_cast<unsigned char>(sum / (factor * factor));
}

void apThumbNail::readImage(const char* /*inputFile*/)
{
    // We'll discuss this step later.  For now just assume that
    // the image is read from the file and placed in the image
    // as a two dimensional array of data. The following code
    // will create a synthetic 64x64 image.
    // 我们将在稍后讨论此步骤。 现在，仅假定从文件中读取图像并将其作为二维数据数组放置在图像中。
    // 以下代码将创建一个合成的64x64图像。

    image_ = apImage(64, 64);

    try
    {
        for (int y = 0; y < image_.height(); y++)
        {
            for (int x = 0; x < image_.width(); x++)
            {
                image_.setPixel(x, y, (unsigned char)(y % 255));
            }
        }
    }
    catch (apImage::rangeError)
    {
        throw invalid();
    }
}

void apThumbNail::writeImage(const char* /*outputFile*/) const
{
    // We'll discuss this step later.  For now just assume that
    // the thumnail image is written to the file.  The following
    // code will display the image as hex values
    // We will also exercise our assignment operator;
    // 我们将在稍后讨论此步骤。 现在，仅假设缩略图图像已写入文件。
    // 以下代码将图像显示为十六进制值。
    apImage output = thumbnail_;

    // Save formatting state of stream
    // 保存流的格式化状态
    std::ios_base::fmtflags flags = std::cout.flags(std::cout.hex);
    auto width = std::cout.width(2);

    for (int y = 0; y < output.height(); y++)
    {
        for (int x = 0; x < output.width(); x++)
        {
            // (int) makes sure we are displayed as a number, not a char.
            // (int)确保我们显示为数字，而不是字符。
            std::cout << (int)output.getPixel(x, y) << " ";
        }

        std::cout << std::endl;
    }

    std::cout.flags(flags);
    std::cout.width(width);
}
