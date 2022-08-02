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
//  �򵥵Ķ�������ͼ����������

#include <stdio.h>  // for NULL definition������NULL���壩

// ���
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
//  apImage��һ���򵥵�ͼ���࣬��Ϊ8λ��ɫͼ������ڴ棬�������������ͼ�����ݡ�

class apImage
{
public:
    apImage();
    // Creates a null image, suitable for later assignment
    // ����һ����ͼ���������Ժ�ķ���

    apImage(int width, int height);
    // Creates an image of the specified size
    // ����ָ����С��ͼ��

    ~apImage();

    apImage(const apImage& src);
    apImage& operator=(const apImage& src);
    // We need to define our own copy constructor and assignment
    // operator since a member copy will not suffice.
    // ������Ҫ�����Լ��ĸ��ƹ��캯���͸�ֵ���������Ϊ��Ա�����޷�����Ҫ��

    void swap(apImage& src);
    // Used during assignment (Sutter, Exceptional C++) to make the
    // assignment operator exception safe
    // �ڸ�ֵ�ڼ�ʹ�ã�Sutter��Exceptional C++����ʹ��ֵ������쳣��ȫ��

    void setPixel(int x, int y, unsigned char pixel);
    unsigned char getPixel(int x, int y) const;
    // Write/read an individual pixel.
    // Throws rangeError if the coordinates are invalid.
    // д��/��ȡ�������ء�
    // ���������Ч�����׳�rangeError��

    bool isValid() const
    {
        return pixels_ != nullptr;
    }
    // Tests if the image data exists, and presumably valid.
    // ����ͼ�������Ƿ���ڣ����Ҵ����Ч��

    int width() const
    {
        return width_;
    }
    int height() const
    {
        return height_;
    }
    // Return the extent of the image
    // ����ͼ��ķ�Χ

    class rangeError
    {
    };
    // Error thrown if the requested data is not in the image
    // �����������ݲ���ͼ���У������������

private:
    void cleanup();
    // Reinitialize the object and free allocated memory
    // ���³�ʼ�������ͷ��ѷ�����ڴ�

    void init();
    // Initialize image data
    // ��ʼ��ͼ������

    int width_;  // Image width��ͼ���ȣ�
    int height_;  // Image height��ͼ��߶ȣ�
    unsigned char* pixels_;  // Image data��ͼ�����ݣ�
};

#endif  // _image_h_
