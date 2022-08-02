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
// Unit Test for Intel IPP interface class

#include "image/image.h"
#include "image/convolve.h"

#include "ipp/ippWrapper.h"

#include "fastTiming.h"   // For hires timing

#include "unitTest.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


#ifdef RGB
#undef RGB
#endif

UTFUNC(testing)
{
  apRect boundary (0, 0, 30, 30);
  apImage<Pel8> image1 (boundary);
  apIPP<Pel8> wrapper (image1);
}


UTFUNC (laplacian3x3dump)
{
  setDescription ("laplacian3x3 dump");

  apRect boundary1 (0, 0, 16, 16);

  apImage<Pel8> byteImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<Pel8> byteImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  byteImage1.set (1);
  byteImage1.setPixel (apPoint(8,8), 2);

  byteImage2.set (255);

  apImage<Pel8>::row_iterator i;
  for (i=byteImage1.row_begin(); i != byteImage1.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<byteImage1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  IppStatus result = IPPLaplacian3x3<Pel8>::filter (byteImage1, byteImage2);
  VERIFY (result == 0);

  for (i=byteImage2.row_begin(); i != byteImage2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<byteImage2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }
}


UTFUNC (laplacian3x3colordump)
{
  setDescription ("laplacian3x3 color dump");

  apRect boundary1 (0, 0, 16, 16);

  apImage<apRGB> colorImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<apRGB> colorImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  colorImage1.set (apRGB(1));
  colorImage1.setPixel (apPoint(8,8), apRGB(2));

  colorImage2.set (apRGB(255));

  apImage<apRGB>::row_iterator i;
  for (i=colorImage1.row_begin(); i != colorImage1.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<colorImage1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  IppStatus result = IPPLaplacian3x3<apRGB>::filter (colorImage1, colorImage2);
  VERIFY (result == 0);

  for (i=colorImage2.row_begin(); i != colorImage2.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<colorImage2.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }
}



UTFUNC (laplacian5x5dump)
{
  setDescription ("laplacian5x5 dump");

  apRect boundary1 (0, 0, 16, 16);

  apImage<Pel8> byteImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<Pel8> byteImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  byteImage1.set (1);
  byteImage1.setPixel (apPoint(8,8), 2);

  byteImage2.set (255);

  apImage<Pel8>::row_iterator i;
  for (i=byteImage1.row_begin(); i != byteImage1.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<byteImage1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  IppStatus result = IPPLaplacian5x5<Pel8>::filter (byteImage1, byteImage2);
  VERIFY (result == 0);

  for (i=byteImage2.row_begin(); i != byteImage2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<byteImage2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }
}



UTFUNC (laplacian3x3large)
{
  setDescription ("laplacian3x3 large");

  apRect boundary1 (0, 0, 1024, 1024);

  apImage<Pel8> byteImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<Pel8> byteImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  byteImage1.set (1);
  byteImage1.setPixel (apPoint(byteImage1.width()/2,byteImage1.height()/2), 2);

  byteImage2.set (255);

  apHiResElapsedTime timer;
  IppStatus result = IPPLaplacian3x3<Pel8>::filter (byteImage1, byteImage2);
  double msec = timer.msec ();
  std::cout << "1024x1024 byte laplacian in " << msec << " msec" << std::endl;

  // Compare results with our image
  apImage<Pel8> byteImage3 (boundary1);
  byteImage3.set (255);
  apHiResElapsedTime timer2;
  laplacian3x3<Pel32s> (byteImage1, byteImage3);
  double msec2 = timer2.msec ();
  std::cout << "1024x1024 byte laplacian (our version) in " << msec2 << " msec" << std::endl;

  // Compare results with our image (slower way)
  char kernel[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
  apImage<Pel8> byteImage4 (boundary1);
  byteImage4.set (255);
  apHiResElapsedTime timer3;
  convolve<Pel32s> (byteImage1, kernel, 3, 1, byteImage4);
  double msec3 = timer3.msec ();
  std::cout << "1024x1024 byte laplacian (our convolve version) in " << msec3 << " msec" << std::endl;

  VERIFY (byteImage2 == byteImage3);
  VERIFY (byteImage3 == byteImage4);

  VERIFY (result == 0);
}

UTFUNC (laplacian3x3colorlarge)
{
  setDescription ("laplacian3x3 color large");

  apRect boundary1 (0, 0, 1024, 1024);

  apImage<apRGB> colorImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<apRGB> colorImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  colorImage1.set (apRGB(1));
  colorImage1.setPixel (apPoint(colorImage1.width()/2,colorImage1.height()/2), apRGB(2));

  colorImage2.set (apRGB(255));

  apHiResElapsedTime timer;
  IppStatus result = IPPLaplacian3x3<apRGB>::filter (colorImage1, colorImage2);
  double msec = timer.msec ();
  std::cout << "1024x1024 rgb laplacian in " << msec << " msec" << std::endl;
  VERIFY (result == 0);

  // Compare results with our image (slower way)
  char kernel[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
  apImage<apRGB> colorImage3 (boundary1, apRectImageStorage::e16ByteAlign);
  colorImage3.set (apRGB(255));
  apHiResElapsedTime timer2;
  convolve<apRGBPel32s> (colorImage1, kernel, 3, 1, colorImage3);
  double msec2 = timer2.msec ();

  apImage<apRGB> colorImage4 (boundary1, apRectImageStorage::e16ByteAlign);
  colorImage4.set (apRGB(255));
  apHiResElapsedTime timer3;
  laplacian3x3<apRGBPel32s> (colorImage1, colorImage4);
  double msec3 = timer3.msec ();

  std::cout << "1024x1024 rgb laplacian (our convolve version) in " << msec2 << " msec" << std::endl;
  std::cout << "1024x1024 rgb laplacian (our version) in " << msec3 << " msec" << std::endl;

  VERIFY (colorImage2 == colorImage3);
  VERIFY (colorImage2 == colorImage4);
}


UTFUNC (laplacian5x5large)
{
  setDescription ("laplacian5x5 large");

  apRect boundary1 (0, 0, 1024, 1024);

  apImage<Pel8> byteImage1 (boundary1, apRectImageStorage::e16ByteAlign);
  apImage<Pel8> byteImage2 (boundary1, apRectImageStorage::e16ByteAlign);
  byteImage1.set (1);
  byteImage1.setPixel (apPoint(byteImage1.width()/2,byteImage1.height()/2), 2);

  byteImage2.set (255);

  apHiResElapsedTime timer;
  IppStatus result = IPPLaplacian5x5<Pel8>::filter (byteImage1, byteImage2);
  double msec = timer.msec ();
  std::cout << "1024x1024 byte 5x5 laplacian in " << msec << " msec" << std::endl;


  VERIFY (result == 0);

}

/*
UTFUNC(testbyte)
{
  setDescription ("test byte");

  // This image is NOT aligned
  apRect boundary (0, 0, 30, 30);
  apImage<Pel8> image1 (boundary);
  apImage<Pel8> image2 (boundary);
  image1.set (1);

  // Regular
  apIPPTools<Pel8>::laplacian3x3 (image1, image2);

  // Dest created
  apImage<Pel8> image3 = apIPPTools<Pel8>::laplacian3x3 (image1);

  // Window
  apRect boundary4 (1, 10, 10, 10);
  apImage<Pel8> image4 (boundary4);
  apIPPTools<Pel8>::laplacian3x3 (image1, image4);

  // In place
  apIPPTools<Pel8>::laplacian3x3 (image1, image1);


  VERIFY (image2 == image3);

  apImage<Pel8>::row_iterator i;
  for (i=image1.row_begin(); i != image1.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image2.row_begin(); i != image2.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image4.row_begin(); i != image4.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image4.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

}


UTFUNC(testbytea)
{
  setDescription ("test bytea");

  // This image is NOT aligned
  apRect boundary (0, 0, 30, 30);
  apImage<Pel8> image1 (boundary);
  image1.set (1);

  apRect boundary3 (1, 10, 10, 10);
  apImage<Pel8> image3 = image1;
  image3.window (boundary3);

  // In-place to a window
  apIPPTools<Pel8>::laplacian3x3 (image3, image3);


  apImage<Pel8>::row_iterator i;
  for (i=image1.row_begin(); i != image1.row_end(); i++) {
    const Pel8* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }
}


UTFUNC(testlong)
{
  setDescription ("test long");

  // This image is aligned
  apRect boundary (0, 0, 30, 30);
  apImage<Pel32s> image1 (boundary);
  apImage<Pel32s> image2 (boundary);
  image1.set (1);

  // Regular
  apIPPTools<Pel32s>::laplacian3x3 (image1, image2);

  // Dest created
  apImage<Pel32s> image3 = apIPPTools<Pel32s>::laplacian3x3 (image1);

  // Window
  apRect boundary4 (1, 10, 10, 10);
  apImage<Pel32s> image4 (boundary4);
  apIPPTools<Pel32s>::laplacian3x3 (image1, image4);

  // In place
  apIPPTools<Pel32s>::laplacian3x3 (image1, image1);


  VERIFY (image2 == image3);

  apImage<Pel32s>::row_iterator i;
  for (i=image1.row_begin(); i != image1.row_end(); i++) {
    const Pel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image1.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image2.row_begin(); i != image2.row_end(); i++) {
    const Pel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image2.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image4.row_begin(); i != image4.row_end(); i++) {
    const Pel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image4.width(); x++)
      std::cout << (Pel32s) *p++ << " ";
    std::cout << std::endl;
  }

}



UTFUNC(testrgb)
{
  setDescription ("test rgb");

  // This image is aligned
  apRect boundary (0, 0, 30, 30);
  apImage<apRGB> image1 (boundary);
  apImage<apRGB> image2 (boundary);
  image1.set (apRGB(1));

  // Regular
  apIPPTools<apRGB>::laplacian3x3 (image1, image2);

  // Dest created
  apImage<apRGB> image3 = apIPPTools<apRGB>::laplacian3x3 (image1);

  // Window
  apRect boundary4 (1, 10, 10, 10);
  apImage<apRGB> image4 (boundary4);
  apIPPTools<apRGB>::laplacian3x3 (image1, image4);

  // In place
  apIPPTools<apRGB>::laplacian3x3 (image1, image1);


  VERIFY (image2 == image3);

  apImage<apRGB>::row_iterator i;
  for (i=image1.row_begin(); i != image1.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image1.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image2.row_begin(); i != image2.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image2.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image4.row_begin(); i != image4.row_end(); i++) {
    const apRGB* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image4.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

}



UTFUNC(testrgblong)
{
  setDescription ("test rgb long");

  // This image is aligned
  apRect boundary (0, 0, 30, 30);
  apImage<apRGBPel32s> image1 (boundary);
  apImage<apRGBPel32s> image2 (boundary);
  image1.set (apRGBPel32s(1));

  // Regular
  apIPPTools<apRGBPel32s>::laplacian3x3 (image1, image2);

  // Dest created
  apImage<apRGBPel32s> image3 = apIPPTools<apRGBPel32s>::laplacian3x3 (image1);

  // Window
  apRect boundary4 (1, 10, 10, 10);
  apImage<apRGBPel32s> image4 (boundary4);
  apIPPTools<apRGBPel32s>::laplacian3x3 (image1, image4);

  // In place
  apIPPTools<apRGBPel32s>::laplacian3x3 (image1, image1);


  VERIFY (image2 == image3);

  apImage<apRGBPel32s>::row_iterator i;
  for (i=image1.row_begin(); i != image1.row_end(); i++) {
    const apRGBPel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image1.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image2.row_begin(); i != image2.row_end(); i++) {
    const apRGBPel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image2.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  for (i=image4.row_begin(); i != image4.row_end(); i++) {
    const apRGBPel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (int x=0; x<image4.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

}
*/


// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

