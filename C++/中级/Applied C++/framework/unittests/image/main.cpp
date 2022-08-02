// main.cpp
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
// Unit Test for image class

#include "image/image.h"
#include "image/convolve.h"
#include "image/imageTransform.h"
#include "image/morphology.h"

#include "unitTest.h"

#include "fastTiming.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ********************
// *                  *
// *  Test Functions  *
// *                  *
// ********************

template<class T1>
bool testImage(const apImage<T1>& image, T1 value)
{
  typename apImage<T1>::row_iterator i;
  long w = image.width ();
  const T1* p;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    p = i->p;
    for (int x=0; x<w; x++)
      if (*p++ != value)
        return false;
  }

  return true;
}


template<class T>
void dumpImage(const apImage<T>& image)
{
  typename apImage<T>::row_iterator i;
  long w = image.width ();
  const T* p;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    p = i->p;
    for (int x=0; x<w; x++)
      std::cout << (int) *p++ << " ";
    std::cout << std::endl;
  }
}

UTFUNC (templatePel8)
{
  setDescription ("Template Pel8 instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<Pel8> image1 (boundary);
  apImage<Pel8> image2 (boundary);
  image1.set (1);
  image2.set (2);
  VERIFY (testImage(image1, (Pel8)1));
  VERIFY (testImage(image2, (Pel8)2));

  apImage<Pel8> image3;

  image1.mul (3);
  VERIFY (testImage(image1, (Pel8)3));
  image1.div (3);
  VERIFY (testImage(image1, (Pel8)1));
  image1.add (2);
  VERIFY (testImage(image1, (Pel8)3));
  image1.sub (1);
  VERIFY (testImage(image1, (Pel8)2));

  image3 = image1 - image2;
  VERIFY (testImage(image3, (Pel8)0));

  image3 = image1 + image2;
  VERIFY (testImage(image3, (Pel8)4));

  image2 = unsharpMask<Pel32s> (image1, 2.0);
  laplacian3x3<Pel32s> (image1, image2);
  lopass3x3<Pel32s> (image1, image2);
  hipass3x3<Pel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<Pel32s> (image1, kernel, 3, 9, image2);
}

UTFUNC (templatePel82)
{
  setDescription ("Template Pel82 instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<Pel8> image1 (boundary);
  apImage<Pel8> image2 (boundary);
  apImage<Pel8> image3;

  image1.set (1);
  image1.mul (1);
  image1.div (1);
  image1.add (1);
  image1.sub (1);

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<Pel8> (image1, 2.0);
  laplacian3x3<Pel8> (image1, image2);
  lopass3x3<Pel8> (image1, image2);
  hipass3x3<Pel8> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<Pel8> (image1, kernel, 3, 9, image2);
}


UTFUNC (templatePel16)
{
  setDescription ("Template Pel16 instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<Pel16> image1 (boundary);
  apImage<Pel16> image2 (boundary);
  apImage<Pel16> image3;

  image1.set (1);
  image1.mul (1);
  image1.div (1);
  image1.add (1);
  image1.sub (1);

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<Pel32s> (image1, 20);
  laplacian3x3<Pel32s> (image1, image2);
  lopass3x3<Pel32s> (image1, image2);
  hipass3x3<Pel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<Pel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC (templatePel32s)
{
  setDescription ("Template Pel32s instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<Pel32s> image1 (boundary);
  apImage<Pel32s> image2 (boundary);
  apImage<Pel32s> image3;

  image1.set (1);
  image1.mul (1);
  image1.div (1);
  image1.add (1);
  image1.sub (1);

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<Pel32s> (image1, 2.0);
  laplacian3x3<Pel32s> (image1, image2);
  lopass3x3<Pel32s> (image1, image2);
  hipass3x3<Pel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<Pel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC (templateapRGB)
{
  setDescription ("Template apRGB instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<apRGB> image1 (boundary);
  apImage<apRGB> image2 (boundary);
  apImage<apRGB> image3;

  image1.set (apRGB(1));
  image1.mul (apRGB(1));
  image1.div (apRGB(1));
  image1.add (apRGB(1));
  image1.sub (apRGB(1));

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<apRGBPel32s> (image1, 2.0);
  laplacian3x3<apRGBPel32s> (image1, image2);
  lopass3x3<apRGBPel32s> (image1, image2);
  hipass3x3<apRGBPel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<apRGBPel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC (templateapRGB2)
{
  setDescription ("Template apRGB2 instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<apRGB> image1 (boundary);
  apImage<apRGB> image2 (boundary);
  apImage<apRGB> image3;

  image1.set (apRGB(1));
  image1.mul (apRGB(1));
  image1.div (apRGB(1));
  image1.add (apRGB(1));
  image1.sub (apRGB(1));

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<apRGB> (image1, 2.0);
  laplacian3x3<apRGB> (image1, image2);
  lopass3x3<apRGB> (image1, image2);
  hipass3x3<apRGB> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<apRGB> (image1, kernel, 3, 9, image2);
}


UTFUNC (templateapRGBPel32s)
{
  setDescription ("Template apRGBPel32s instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<apRGBPel32s> image1 (boundary);
  apImage<apRGBPel32s> image2 (boundary);
  apImage<apRGBPel32s> image3;

  image1.set (apRGBPel32s(1));
  image1.mul (apRGBPel32s(1));
  image1.div (apRGBPel32s(1));
  image1.add (apRGBPel32s(1));
  image1.sub (apRGBPel32s(1));

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<apRGBPel32s> (image1, 2.0);
  laplacian3x3<apRGBPel32s> (image1, image2);
  lopass3x3<apRGBPel32s> (image1, image2);
  hipass3x3<apRGBPel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<apRGBPel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC (templateClampedPel8)
{
  setDescription ("Template apClampedPel8 instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<apClampedPel8> image1 (boundary);
  apImage<apClampedPel8> image2 (boundary);
  apImage<apClampedPel8> image3;

  image1.set (1);
  image1.mul (1);
  image1.div (1);
  image1.add (1);
  image1.sub (1);

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<apClampedPel32s> (image1, 2.0);
  laplacian3x3<apClampedPel32s> (image1, image2);
  lopass3x3<apClampedPel32s> (image1, image2);
  hipass3x3<apClampedPel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<apClampedPel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC (templateClampedPel32s)
{
  setDescription ("Template apClampedPel32s instantiation");

  apRect boundary (0, 0, 16, 16);

  apImage<apClampedPel32s> image1 (boundary);
  apImage<apClampedPel32s> image2 (boundary);
  apImage<apClampedPel32s> image3;

  image1.set (1);
  image1.mul (1);
  image1.div (1);
  image1.add (1);
  image1.sub (1);

  image3 = image1 - image2;
  image3 = image1 + image2;

  image2 = unsharpMask<apClampedPel32s> (image1, 2.0);
  laplacian3x3<apClampedPel32s> (image1, image2);
  lopass3x3<apClampedPel32s> (image1, image2);
  hipass3x3<apClampedPel32s> (image1, image2);

  char kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  convolve<apClampedPel32s> (image1, kernel, 3, 9, image2);
}


UTFUNC(apRGB)
{
  setDescription ("apRGB tests");

  Pel8 b = 250;
  apClampedPel8 bc = 250;

  b += 10;
  bc += 10;

  std::cout << "b = " << (long)b << std::endl;
  std::cout << "bc = " << bc << std::endl;

  apRGB rgb (250);
  rgb += 10;
  std::cout << "rgb = " << rgb << std::endl;

  apRGBTmpl<Pel8> rgb1 (1,2,3);
  std::cout << rgb1 << std::endl;
  rgb1 += rgb1;
  std::cout << rgb1 << std::endl;

  apRGBTmpl<Pel32s> rgb2 (4,5,6);
  std::cout << rgb2 << std::endl;

  rgb2 += rgb1;
  std::cout << rgb2 << std::endl;
}

/*
  {
  apRect b1 (0, 0, 16, 16);
  apImage<apRGB> image (b1);
  image.set (250);
  image.add (10);
  apImage<apRGB>::row_iterator i;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }
  }
*/


UTFUNC(ctor)
{
  setDescription ("Constructor and simple accessor tests");

  apRect boundary (0, 0, 640, 480);

  apImage<Pel8> Pel8Image1;
  apImage<Pel8> Pel8Image2 (boundary);
  apImage<Pel8> Pel8Image3 (boundary, 
                            apRectImageStorage::eQuadWordAlign);

  VERIFY (Pel8Image1.isNull());
  VERIFY (!Pel8Image2.isNull());
  VERIFY (!Pel8Image3.isNull());
  VERIFY (Pel8Image2.boundary() == boundary);
  VERIFY (Pel8Image3.boundary() == boundary);
  VERIFY (Pel8Image2.bytesPerPixel() == sizeof (Pel8));
  VERIFY (Pel8Image3.bytesPerPixel() == sizeof (Pel8));
  VERIFY (Pel8Image2.xoffset() == 0);
  VERIFY (Pel8Image3.xoffset() == 0);
  VERIFY (Pel8Image2.yoffset() == 0);
  VERIFY (Pel8Image3.yoffset() == 0);



  apImage<Pel32s> longImage1;
  apImage<Pel32s> longImage2 (boundary);
  apImage<Pel32s> longImage3 (boundary, 
                            apRectImageStorage::eQuadWordAlign);

  VERIFY (longImage1.isNull());
  VERIFY (!longImage2.isNull());
  VERIFY (!longImage3.isNull());
  VERIFY (longImage2.boundary() == boundary);
  VERIFY (longImage3.boundary() == boundary);
  VERIFY (longImage2.bytesPerPixel() == sizeof (Pel32s));
  VERIFY (longImage3.bytesPerPixel() == sizeof (Pel32s));
  VERIFY (longImage2.xoffset() == 0);
  VERIFY (longImage3.xoffset() == 0);
  VERIFY (longImage2.yoffset() == 0);
  VERIFY (longImage3.yoffset() == 0);



  apImage<apRGB> apRGBImage1;
  apImage<apRGB> apRGBImage2 (boundary);
  apImage<apRGB> apRGBImage3 (boundary, 
                          apRectImageStorage::eQuadWordAlign);

  VERIFY (apRGBImage1.isNull());
  VERIFY (!apRGBImage2.isNull());
  VERIFY (!apRGBImage3.isNull());
  VERIFY (apRGBImage2.boundary() == boundary);
  VERIFY (apRGBImage3.boundary() == boundary);
  VERIFY (apRGBImage2.bytesPerPixel() == sizeof (apRGB));
  VERIFY (apRGBImage3.bytesPerPixel() == sizeof (apRGB));
  VERIFY (apRGBImage2.xoffset() == 0);
  VERIFY (apRGBImage3.xoffset() == 0);
  VERIFY (apRGBImage2.yoffset() == 0);
  VERIFY (apRGBImage3.yoffset() == 0);
}


UTFUNC(setPel8)
{
  setDescription ("set Pel8");

  int i;
  apRect boundary (0, 0, 1024, 1024);

  apImage<Pel8> Pel8Image1 (boundary);
  for (i=0; i<100; i++)
    Pel8Image1.set (0);

  apImage<Pel8> Pel8Image2 = Pel8Image1;
  VERIFY (Pel8Image1 == Pel8Image2);
}


UTFUNC(setlong)
{
  setDescription ("set Pel32s");

  int i;
  apRect boundary (0, 0, 1024, 1024);

  apImage<Pel32s> longImage1 (boundary);
  for (i=0; i<100; i++)
    longImage1.set (0);

  apImage<Pel32s> longImage2 = longImage1;
  VERIFY (longImage1 == longImage2);
}

UTFUNC(setRGB)
{
  setDescription ("set apRGB");

  int i;
  apRect boundary (0, 0, 1024, 1024);

  apImage<apRGB> apRGBImage1 (boundary);
  for (i=0; i<100; i++)
    apRGBImage1.set (apRGB(0));

  apImage<apRGB> apRGBImage2 = apRGBImage1;
  VERIFY (apRGBImage1 == apRGBImage2);
}


UTFUNC(mixed)
{
  setDescription ("Mixed");

  apRect boundary (0, 0, 1024, 1024);

  apImage<Pel8> Pel8Image1 (boundary);
  Pel8Image1.set (1);

  apImage<Pel32s> longImage1 (boundary);
  longImage1.set (0);

  add (Pel8Image1, longImage1);
  VERIFY (testImage(longImage1, (Pel32s)1));

  longImage1 += Pel8Image1;
  VERIFY (testImage(longImage1, (Pel32s)2));

  sub (Pel8Image1, longImage1);
  VERIFY (testImage(longImage1, (Pel32s)1));

  longImage1 -= Pel8Image1;
  VERIFY (testImage(longImage1, (Pel32s)0));

  apImage<Pel32s> longImage2 (boundary);
  longImage1.set (1);
  longImage2.set (1);
  VERIFY (testImage(longImage2, (Pel32s)1));

  // Copy unlike images
  apImage<Pel8> Pel8Image2;
  copy (longImage2, Pel8Image2);

  VERIFY (longImage1 == longImage2);
  VERIFY (Pel8Image1 == Pel8Image2);
  VERIFY (testImage(Pel8Image2, (Pel8)1));

  // Copy like images
  apImage<Pel8> Pel8Image3;
  copy (Pel8Image2, Pel8Image3);
  VERIFY (Pel8Image2 == Pel8Image3);
  VERIFY (Pel8Image2.base() != Pel8Image3.base());
  VERIFY (testImage(Pel8Image3, (Pel8)1));

  // Simple copy
  apImage<Pel8> Pel8Image4 = copy (Pel8Image3);
  VERIFY (Pel8Image3 == Pel8Image4);
  VERIFY (Pel8Image3.base() != Pel8Image4.base());

  // Boundary behavior (wrapping)
  Pel8Image1.set (255);
  Pel8Image2.set (1);
  VERIFY (testImage(Pel8Image1, (Pel8)255));
  Pel8Image1 += Pel8Image2;
  VERIFY (testImage(Pel8Image1, (Pel8)0));

  Pel8Image1.set (0);
  Pel8Image1 -= Pel8Image2;
  VERIFY (testImage(Pel8Image1, (Pel8)255));

}


UTFUNC(clampedMath)
{
  setDescription ("Mixed");

  apRect boundary (0, 0, 1024, 1024);

  apImage<apClampedPel8> Pel8Image1 (boundary);
  apImage<apClampedPel8> Pel8Image2 (boundary);
  Pel8Image1.set (254);
  Pel8Image2.set (1);
  
  VERIFY (testImage(Pel8Image1, (apClampedPel8)254));
  VERIFY (testImage(Pel8Image2, (apClampedPel8)1));

  Pel8Image1 += Pel8Image2;
  VERIFY (testImage(Pel8Image1, (apClampedPel8)255));

  // Should clamp at 255
  Pel8Image1 += Pel8Image2;
  VERIFY (testImage(Pel8Image1, (apClampedPel8)255));

  Pel8Image1 -= Pel8Image2;
  VERIFY (testImage(Pel8Image1, (apClampedPel8)254));
}


UTFUNC(mixedrgb)
{
  setDescription ("Mixed rgb");

  apRect boundary (0, 0, 1024, 1024);

  apImage<apRGB> image1 (boundary);
  apRGB rgb (10, 20, 30);
  image1.set (rgb);

  apImage<Pel8> image2 (boundary);
  copy (image1, image2);

  // Verify each pixel
  VERIFY (true);
  apImage<Pel8>::row_iterator i;
  long w = image2.width ();
  const Pel8* p;
  for (i=image2.row_begin(); i != image2.row_end(); i++) {
    p = i->p;
    for (int x=0; x<w; x++)
      if (*p++ != 20)
        VERIFY (!"Pixel verification error 1");
  }

  image1.set (rgb);
  image2.set (5);
  image1 += image2;
  apRGB rgb2 (15, 25, 35);
  VERIFY (testImage (image1, rgb2));

}


UTFUNC(align)
{
  setDescription ("align");

  // This image is NOT aligned
  apRect boundary (0, 0, 30, 30);
  apImage<Pel8> image1 (boundary);

  apImage<Pel8> align0 = image1.align (apRectImageStorage::eNoAlign);
  apImage<Pel8> align2 = image1.align (apRectImageStorage::eWordAlign);
  apImage<Pel8> align4 = image1.align (apRectImageStorage::eDoubleWordAlign);
  apImage<Pel8> align8 = image1.align (apRectImageStorage::eQuadWordAlign);

  VERIFY (image1.rowAddress(0) == align0.rowAddress(0));
  VERIFY (align0.alignment() == apRectImageStorage::eNoAlign);
  VERIFY (align2.bestAlignment() == apRectImageStorage::eDoubleWordAlign ||
          align2.bestAlignment() == apRectImageStorage::eQuadWordAlign ||
          align2.bestAlignment() == apRectImageStorage::eWordAlign);
  VERIFY (align4.bestAlignment() == apRectImageStorage::eDoubleWordAlign ||
          align4.bestAlignment() == apRectImageStorage::eQuadWordAlign);
  VERIFY (align8.bestAlignment() == apRectImageStorage::eQuadWordAlign);

  // Do the same thing using our duplicate function
  align0 = duplicate (image1, apRectImageStorage::eNoAlign);
  align2 = duplicate (image1, apRectImageStorage::eWordAlign);
  align4 = duplicate (image1, apRectImageStorage::eDoubleWordAlign);
  align8 = duplicate (image1, apRectImageStorage::eQuadWordAlign);

  VERIFY (image1.rowAddress(0) != align0.rowAddress(0));
  VERIFY (align0.alignment() == apRectImageStorage::eNoAlign);
  VERIFY (align2.bestAlignment() == apRectImageStorage::eDoubleWordAlign ||
          align2.bestAlignment() == apRectImageStorage::eQuadWordAlign ||
          align2.bestAlignment() == apRectImageStorage::eWordAlign);
  VERIFY (align4.bestAlignment() == apRectImageStorage::eDoubleWordAlign ||
          align4.bestAlignment() == apRectImageStorage::eQuadWordAlign);
  VERIFY (align8.bestAlignment() == apRectImageStorage::eQuadWordAlign);

}

UTFUNC(trim)
{
  setDescription ("trim");

  apRect boundary (0, 0, 100, 100);
  apImage<Pel8> image1 (boundary);

  apRect window (10, 20, 30, 40);
  apImage<Pel8> image2 = image1;
  image2.window (window);

  VERIFY (image2.x0()     == 10);
  VERIFY (image2.y0()     == 20);
  VERIFY (image2.width()  == 30);
  VERIFY (image2.height() == 40);
  VERIFY (image2.ref()    == 2);

  VERIFY (image2.storage().xoffset() == 10);
  VERIFY (image2.storage().yoffset() == 20);

  image2.trim ();

  VERIFY (image2.x0()     == 10);
  VERIFY (image2.y0()     == 20);
  VERIFY (image2.width()  == 30);
  VERIFY (image2.height() == 40);
  VERIFY (image2.ref()    == 1);

  VERIFY (image2.storage().xoffset() == 0);
  VERIFY (image2.storage().yoffset() == 0);

}


UTFUNC(rebase)
{
  setDescription ("rebase");

  apRect boundary (0, 0, 100, 100);
  apImage<Pel8> image1 (boundary);

  apRect window (10, 20, 30, 40);
  apImage<Pel8> image2 = image1;
  image2.window (window);

  VERIFY (image2.x0()     == 10);
  VERIFY (image2.y0()     == 20);
  VERIFY (image2.width()  == 30);
  VERIFY (image2.height() == 40);
  VERIFY (image2.ref()    == 2);

  VERIFY (image2.storage().xoffset() == 10);
  VERIFY (image2.storage().yoffset() == 20);

  image2.rebase ();

  VERIFY (image2.x0()     == 0);
  VERIFY (image2.y0()     == 0);
  VERIFY (image2.width()  == 30);
  VERIFY (image2.height() == 40);
  VERIFY (image2.ref()    == 1);

  VERIFY (image2.storage().xoffset() == 0);
  VERIFY (image2.storage().yoffset() == 0);

}


UTFUNC(add)
{
  setDescription ("add");

  apRect boundary1 (0, 0, 640, 480);
  apRect boundary2 (1, 2, 638, 476);
  apRect boundary3 (2, 4, 636, 472);

  apImage<Pel8> Pel8Image1 (boundary1);
  Pel8Image1.set (1);

  apImage<Pel8> Pel8Image2 (boundary2);
  Pel8Image2.set (2);

  apImage<Pel8> Pel8Image3;

  // No destination specified
  add (Pel8Image1, Pel8Image2, Pel8Image3);

  apRect overlap = boundary1.intersect (boundary2);
  VERIFY (Pel8Image3.boundary() == overlap);
  VERIFY (testImage (Pel8Image3, (Pel8)3));


  // Destination specified
  Pel8Image3 = apImage<Pel8> (boundary3);
  Pel8Image3.set (100);

  add (Pel8Image1, Pel8Image2, Pel8Image3);
  VERIFY (Pel8Image3.boundary() == boundary3);
  VERIFY (testImage (Pel8Image3, (Pel8)3));


  // operator+ syntax. Additional causes wrapping
  Pel8Image1.set (255);
  Pel8Image2.set (2);
  Pel8Image3 = Pel8Image1 + Pel8Image2;

  VERIFY (Pel8Image3.boundary() == overlap);
  VERIFY (testImage (Pel8Image3, (Pel8)1));

  // operator+ syntax. Additional causes clamping
  apImage<apClampedPel8> Pel8Image1c (boundary1);
  apImage<apClampedPel8> Pel8Image2c (boundary2);
  apImage<apClampedPel8> Pel8Image3c;

  Pel8Image1c.set (254);
  Pel8Image2c.set (2);
  Pel8Image3c = Pel8Image1c + Pel8Image2c;

  VERIFY (Pel8Image3c.boundary() == overlap);
  VERIFY (testImage (Pel8Image3c, (apClampedPel8)255));

}


UTFUNC (convolve)
{
  setDescription ("convolve");

  apRect boundary1 (0, 0, 640, 480);

  apImage<Pel8> Pel8Image1 (boundary1);
  apImage<Pel8> Pel8Image2 (boundary1);
  Pel8Image1.set (1);
  Pel8Image2.set (0);

  char kernel[] = { (char)-1, (char)-1, (char)-1, (char)-1, 8, (char)-1, (char)-1, (char)-1, (char)-1 };

  convolve<Pel32s> (Pel8Image1, kernel, 3, 1, Pel8Image2);

  apImage<Pel8> Pel8Image3 (boundary1);
  Pel8Image3.set (0);
  laplacian3x3<Pel32s> (Pel8Image1, Pel8Image3);
  std::cout << "Pel8Image1 = " << (long) Pel8Image1.getPixel(0,0) << std::endl;
  std::cout << "Pel8Image2 = " << (long) Pel8Image2.getPixel(0,0) << std::endl;
  std::cout << "Pel8Image3 = " << (long) Pel8Image3.getPixel(0,0) << std::endl;

  VERIFY (Pel8Image2 == Pel8Image3);

  apImage<Pel8> Pel8Image4, Pel8Image5;
  laplacian3x3<Pel32s> (Pel8Image4, Pel8Image5);
  VERIFY (Pel8Image4.isNull());
  VERIFY (Pel8Image5.isNull());

/*
  int o;
  for (o=0; o<9; o++)
    std::cout << (int) kernel[o] << " ";
  std::cout << std::endl;

  apImage<Pel8>::row_iterator i;
  for (i=Pel8Image2.row_begin(); i != Pel8Image2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<Pel8Image2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }
*/

}


UTFUNC (laplacian3x3)
{
  setDescription ("laplacian3x3");

  apRect boundary1 (0, 0, 640, 480);

  apImage<Pel8> Pel8Image1 (boundary1);
  apImage<Pel8> Pel8Image2 (boundary1);
  Pel8Image1.set (1);

  laplacian3x3<Pel32s> (Pel8Image1, Pel8Image2);

  apRect boundary2 (0, 0, 638, 478);
  apImage<Pel8> Pel8Image3 (boundary2);
  Pel8Image3.set (0);

  apImage<Pel8> Pel8Image4 = Pel8Image2;
  Pel8Image4.window (boundary2);
  VERIFY (Pel8Image3 == Pel8Image4);
  
/*
  int o;
  for (o=0; o<9; o++)
    std::cout << (int) kernel[o] << " ";
  std::cout << std::endl;

  apImage<Pel8>::row_iterator i;
  for (i=Pel8Image2.row_begin(); i != Pel8Image2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<Pel8Image2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }
*/

}


UTFUNC (laplacian3x3dump)
{
  setDescription ("laplacian3x3 dump");

  apRect boundary1 (0, 0, 16, 16);

  apImage<Pel8> Pel8Image1 (boundary1);
  apImage<Pel8> Pel8Image2 (boundary1);
  Pel8Image1.set (200);
  Pel8Image2.set (2);
  Pel8Image1.setPixel (apPoint(8,8), 2);

  laplacian3x3<long> (Pel8Image1, Pel8Image2);
  VERIFY (Pel8Image2.boundary() == boundary1);

  apImage<Pel8> Pel8Image3;
  laplacian3x3<long> (Pel8Image1, Pel8Image3);

  apRect boundary2 = boundary1;
  boundary2.expand (-1, -1);
  VERIFY (Pel8Image3.boundary() == boundary2);

  apImage<apRGB> rgbImage1 (boundary1);
  apImage<apRGB> rgbImage2;
  rgbImage1.set (apRGB(200));
  rgbImage1.setPixel (apPoint(8,8), apRGB(2));

  laplacian3x3<apRGBPel32s> (rgbImage1, rgbImage2);
  VERIFY (rgbImage2.boundary() == boundary2);


  apImage<Pel8>::row_iterator i;
  for (i=Pel8Image2.row_begin(); i != Pel8Image2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<Pel8Image2.width(); x++)
      std::cout << (long) *p++ << " ";
    std::cout << std::endl;
  }

  for (i=Pel8Image3.row_begin(); i != Pel8Image3.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<Pel8Image3.width(); x++)
      std::cout << (long) *p++ << " ";
    std::cout << std::endl;
  }

  apImage<apRGB>::row_iterator i1;
  for (i1=rgbImage2.row_begin(); i1 != rgbImage2.row_end(); i1++) {
    const apRGB* p = i1->p;
    std::cout << i1->x << ", " << i1->y << ": ";
    for (unsigned int x=0; x<rgbImage2.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }


}

UTFUNC (laplacian3x3apRGB)
{
  setDescription ("laplacian3x3 apRGB");

  apRect boundary1 (0, 0, 640, 480);

  apImage<apRGB> apRGBImage1 (boundary1);
  apImage<apRGB> apRGBImage2 (boundary1);
  apRGBImage1.set (apRGB(1));

  laplacian3x3<apRGBPel32s> (apRGBImage1, apRGBImage2);

  apRect boundary2 (0, 0, 638, 478);
  apImage<apRGB> apRGBImage3 (boundary2);
  apRGBImage3.set (apRGB(0));

  apImage<apRGB> apRGBImage4 = apRGBImage2;
  apRGBImage4.window (boundary2);
  VERIFY (apRGBImage3 == apRGBImage4);
}



UTFUNC (laplacian3x3double)
{
  setDescription ("laplacian3x3 double");

  apRect boundary1 (0, 0, 640, 480);

  apImage<double> doubleImage1 (boundary1);
  apImage<double> doubleImage2 (boundary1);
  doubleImage1.set (1.);

  laplacian3x3<double> (doubleImage1, doubleImage2);

  apRect boundary2 (0, 0, 638, 478);
  apImage<double> doubleImage3 (boundary2);
  doubleImage3.set (0);

  apImage<double> doubleImage4 = doubleImage2;
  doubleImage4.window (boundary2);
  VERIFY (doubleImage3 == doubleImage4);
}


UTFUNC (unsharpmask)
{
  setDescription ("unsharp mask");

  apRect boundary1 (0, 0, 640, 480);

  apImage<apRGB> image1 (boundary1);
  apImage<apRGB> image2 (boundary1);
  image1.set (apRGB(1));

  image2 = unsharpMask<apRGBPel32s> (image1, 2.0);

}


UTFUNC (thumbnail)
{
  setDescription ("thumbnail");

  apRect boundary1 (0, 0, 8, 8);
  apImage<apRGB> image (boundary1);

  apImage<apRGB>::row_iterator i;
  Pel8 count = 0;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    apRGB* p = i->p;
    for (unsigned int x=0; x<image.width(); x++)
      *p++ = apRGB(count++);
  }

  std::cout << "Original:" << std::endl;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<image.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  apImage<apRGB> tnail = thumbnail<apRGBPel32s> (image, 2);

  std::cout << "Thumbnail:" << std::endl;
  for (i=tnail.row_begin(); i != tnail.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<tnail.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  // This will cause wrapping since intermediate quantity isn't big enough
  apImage<apRGB> tnail2 = thumbnail<apRGB> (image, 3);

  std::cout << "Thumbnail Pel8 average:" << std::endl;
  for (i=tnail2.row_begin(); i != tnail2.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<tnail2.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

}


UTFUNC (morphology)
{
  setDescription ("morphology");

  apRect boundary1 (0, 0, 8, 8);
  apImage<apRGB> image (boundary1);

  apRGB black (0);
  apRGB white (255);

  // Create a cross image
  image.set (black);
  image.setPixel (4, 4, white);
  image.setPixel (3, 4, white);
  image.setPixel (5, 4, white);
  image.setPixel (4, 3, white);
  image.setPixel (4, 5, white);

  apImage<apRGB> dst;
  erodeCross (image, dst);

  // Verify it again the correct output
  apRect boundary2 (1, 1, 6, 6);
  apImage<apRGB> correct (boundary2);
  correct.set (black);
  correct.setPixel (4, 4, white);
  VERIFY (dst == correct);
}


UTFUNC (timing)
{
  int i;

  setDescription ("timing");

  // copy performance compared to stl version
  apRect boundary (0, 0, 1024, 1024);
  apImage<Pel8> Pel8Image1 (boundary);
  Pel8Image1.set (1);

  apHiResElapsedTime t1;
  apImage<Pel8> Pel8Image2;
  for (i=0; i<10; i++)
    Pel8Image2 = copy (Pel8Image1);
  double t1msec = t1.msec () / 10.;

  apHiResElapsedTime t2;
  apImage<Pel8> Pel8Image3;
  for (i=0; i<10; i++)
    Pel8Image3 = copy_stl (Pel8Image1);
  double t2msec = t2.msec () / 10.;

  VERIFY (Pel8Image1 == Pel8Image2);
  VERIFY (Pel8Image1 == Pel8Image3);

  std::cout << "1024x1024 copy in " << t1msec << " msec" << std::endl;
  std::cout << "1024x1024 copy_stl in " << t2msec << " msec" << std::endl;

  // Test generic convolution vs. faster version
  char kernel[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
  Pel8Image1.set (1);

  apHiResElapsedTime t3;
  apImage<Pel8> laplace1;
  for (i=0; i<10; i++) {
    laplace1 = apImage<Pel8> (boundary);
    laplace1.set (0);
    convolve<Pel32s> (Pel8Image1, kernel, 3, 1, laplace1);
  }
  double t3msec = t3.msec () / 10.;
 
  apHiResElapsedTime t4;
  apImage<Pel8> laplace2;
  for (i=0; i<10; i++) {
   laplace2 = apImage<Pel8> (boundary);
   laplace2.set (0);
   laplacian3x3<Pel32s> (Pel8Image1, laplace2);
  }
  double t4msec = t4.msec () / 10.;

  std::cout << "1024x1024 pel8 laplace via convolve() in " << t3msec << " msec" << std::endl;
  std::cout << "1024x1024 pel8 laplace in " << t4msec << " msec" << std::endl;

  apImage<apRGB>rgbImage1 (boundary);
  rgbImage1.set (apRGB(1,1,1));

  apHiResElapsedTime t5;
  apImage<Pel8> laplace3;
  for (i=0; i<10; i++) {
    laplace3 = apImage<apRGB> (boundary);
    rgbImage1.set (apRGB(0,0,0));
    convolve<apRGBPel32s> (rgbImage1, kernel, 3, 1, laplace3);
  }
  double t5msec = t5.msec () / 10.;
 
  apHiResElapsedTime t6;
  apImage<Pel8> laplace4;
  for (i=0; i<10; i++) {
    laplace4 = apImage<apRGB> (boundary);
    rgbImage1.set (apRGB(0,0,0));
    laplacian3x3<apRGBPel32s> (rgbImage1, laplace4);
  }
  double t6msec = t6.msec () / 10.;

  std::cout << "1024x1024 rgb laplace via convolve() in " << t5msec << " msec" << std::endl;
  std::cout << "1024x1024 rgb laplace in " << t6msec << " msec" << std::endl;

  VERIFY (laplace1 == laplace2);
  VERIFY (laplace3 == laplace4);
}



// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

