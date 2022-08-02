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
// Unit Test for image storage class

#include "image/imageStorageTmpl.h"

#include "unitTest.h"

#include <numeric>
#include <functional>

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




template<class T>
void row_set (apImageStorage<T> image, T value)
{
  typename apImageStorage<T>::row_iterator i;
  unsigned int width = image.width ();
  for (i=image.row_begin(); i != image.row_end(); i++) {
    T* p = i->p;
    for (unsigned int x=0; x<width; x++)
      *p++ = value;
  }
}

template<class T>
void pixel_set (apImageStorage<T> image, T value)
{
  typename apImageStorage<T>::iterator i;
  for (i=image.begin(); i != image.end(); i++)
    *i = value;
}

template<class T>
void stl_set (apImageStorage<T> image, T value)
{
  std::fill (image.begin(), image.end(), value);
}


template<class T>
void set_nonstandard (apImageStorage<T> image, T value)
{
  unsigned int x, y;
  T* p;
  for (y=0; y<image.height(); y++) {
    p = image.rowAddress (y + image.y0());
    for (x=0; x<image.width(); x++)
      *p++ = value;
  }
}

template<class T>
void set_slow (apImageStorage<T> image, T value)
{
  int x0 = image.x0 ();
  int y0 = image.y0 ();
  unsigned int x, y;
  for (y=0; y<image.height(); y++)
    for (x=0; x<image.width(); x++)
      image.setPixel (x0+x, y0+y, value);
}



UTFUNC(apRect)
{
  setDescription ("apRect");

  apRect boundary (-20, -10, 120, 110);

  VERIFY (boundary.width() == 120);
  VERIFY (boundary.height() == 110);
  VERIFY (boundary.x0() == -20);
  VERIFY (boundary.y0() == -10);
  VERIFY (boundary.x1() == 100);
  VERIFY (boundary.y1() == 100);
  VERIFY (boundary.ul().x() == -20);
  VERIFY (boundary.ul().y() == -10);
  VERIFY (boundary.lr().x() == 100);
  VERIFY (boundary.lr().y() == 100);
}


UTFUNC(ctor)
{
  setDescription ("Constructor and simple accessor tests");

  apRect boundary (0, 0, 640, 480);

  apImageStorage<Pel8> byteImage1;
  apImageStorage<Pel8> byteImage2 (boundary);
  apImageStorage<Pel8> byteImage3 (boundary, 
                             apRectImageStorage::eQuadWordAlign);

  VERIFY (byteImage1.isNull());
  VERIFY (!byteImage2.isNull());
  VERIFY (!byteImage3.isNull());
  VERIFY (byteImage2.boundary() == boundary);
  VERIFY (byteImage3.boundary() == boundary);
  VERIFY (byteImage2.bytesPerPixel() == sizeof (Pel8));
  VERIFY (byteImage3.bytesPerPixel() == sizeof (Pel8));
  VERIFY (byteImage2.xoffset() == 0);
  VERIFY (byteImage3.xoffset() == 0);
  VERIFY (byteImage2.yoffset() == 0);
  VERIFY (byteImage3.yoffset() == 0);



  apImageStorage<Pel32s> longImage1;
  apImageStorage<Pel32s> longImage2 (boundary);
  apImageStorage<Pel32s> longImage3 (boundary, 
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
}



UTFUNC(rowaddress)
{
  setDescription ("rowaddress");

  apRect boundary (0, 0, 640, 480);

  apImageStorage<Pel8> byteImage2 (boundary);
  apImageStorage<Pel8> byteImage3 (boundary, 
                             apRectImageStorage::eQuadWordAlign);

  // Set all the pixels
  unsigned int i;
  for (i=0; i<byteImage2.height(); i++) {
    memset (byteImage2.rowAddress (i), 0, byteImage2.width());
  }

  // Make sure row spacing is constant and correct
  for (i=1; i<byteImage2.height(); i++) {
    Pel32s delta = byteImage2.rowAddress (i) - byteImage2.rowAddress (i-1);
    VERIFY (delta == 640);
  }


  apImageStorage<Pel32s> longImage2 (boundary);
  apImageStorage<Pel32s> longImage3 (boundary, 
                             apRectImageStorage::eQuadWordAlign);

  // Set all the pixels
  for (i=0; i<longImage2.height(); i++) {
    memset (longImage2.rowAddress (i), 0, longImage2.width() * sizeof (Pel32s));
  }

  // Make sure row spacing is constant and correct
  for (i=1; i<longImage2.height(); i++) {
    Pel32s delta = longImage2.rowAddress (i) - longImage2.rowAddress (i-1);
    VERIFY (delta == 640);  // Delta is 640 Pel32s's
  }


  // Choose an odd size with quad alignment
  apRect oddBoundary (0, 0, 13, 15);

  apImageStorage<Pel8> byteImage4 (oddBoundary, 
                             apRectImageStorage::eQuadWordAlign);

  // Make sure row spacing is constant and correct
  for (i=1; i<byteImage4.height(); i++) {
    Pel32s delta = byteImage4.rowAddress (i) - byteImage4.rowAddress (i-1);
    VERIFY (delta == 16);
  }

}


UTFUNC(getset)
{
  setDescription ("getPixel/setPixel");

  apRect boundary (0, 0, 32, 32);
  apImageStorage<Pel32s> longImage (boundary);

  // Set the pixels
  unsigned int x, y;
  Pel32s value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      longImage.setPixel (x, y, value++);
    }
  }

  // Verify their values
  value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      VERIFY (longImage.getPixel (x, y) == value++);
    }
  }

  // Verify against rowAddress
  for (y=0; y<boundary.height(); y++) {
    Pel32s* p = longImage.rowAddress (y);
    for (x=0; x<boundary.width(); x++) {
      VERIFY (*p++ == longImage.getPixel (x, y));
    }
  }

}


UTFUNC(copy)
{
  setDescription ("copy");

  apRect boundary (0, 0, 32, 32);
  apImageStorage<Pel32s> longImage (boundary);

  // Set the pixels
  unsigned int x, y;
  Pel32s value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      longImage.setPixel (x, y, value++);
    }
  }

  apImageStorage<Pel32s> longImage2 (boundary);
  copy (longImage, longImage2);

  // Verify their values
  value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      VERIFY (longImage2.getPixel (x, y) == value++);
    }
  }

  // Convert to pixel
  apImageStorage<Pel8> byteImage (boundary);
  copy (longImage, byteImage);

  // Verify their values
  value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      VERIFY (byteImage.getPixel (x, y) == (Pel8)value++);
    }
  }

}


UTFUNC(duplicate)
{
  setDescription ("duplicate");

  apRect boundary (0, 0, 32, 32);
  apImageStorage<Pel32s> longImage (boundary);

  // Set the pixels
  unsigned int x, y;
  Pel32s value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      longImage.setPixel (x, y, value++);
    }
  }

  apImageStorage<Pel32s> longImage2 = duplicate (longImage, apRectImageStorage::eNoAlign);
  apImageStorage<Pel32s> longImage3 = duplicate (longImage, apRectImageStorage::eQuadWordAlign);

  VERIFY (longImage3.alignment() == apRectImageStorage::eQuadWordAlign);

  // Verify their values
  value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      VERIFY (longImage2.getPixel (x, y) == value);
      VERIFY (longImage3.getPixel (x, y) == value++);
    }
  }
}



UTFUNC(window)
{
  setDescription ("window");

  apRect boundary (-20, -10, 120, 110);
  apImageStorage<Pel8> byteImage (boundary);

  // Complete overlap
  apRect boundary2 (-100, -100, 200, 200);
  apImageStorage<Pel8> byteImage2 = byteImage;
  byteImage2.window (boundary2);
  VERIFY (byteImage2.boundary() == boundary);

  // No overlap
  apRect boundary3 (100, 100, 100, 100);
  apImageStorage<Pel8> byteImage3 = byteImage;
  byteImage3.window (boundary3);
  VERIFY (byteImage3.isNull());

  // Inside window
  apRect boundary4 (0, 10, 30, 40);
  apImageStorage<Pel8> byteImage4 = byteImage;
  byteImage4.window (boundary4);
  VERIFY (byteImage4.boundary() == boundary4);

  // Overlap 1
  apRect boundary5 (-50, -50, 60, 60);
  apRect overlap1 (-20, -10, 30, 20);
  apImageStorage<Pel8> byteImage5 = byteImage;
  byteImage5.window (boundary5);
  VERIFY (byteImage5.boundary() == overlap1);

  // Overlap 2
  apRect boundary6 (70, 80, 60, 60);
  apRect overlap2 (70, 80, 30, 20);
  apImageStorage<Pel8> byteImage6 = byteImage;
  byteImage6.window (boundary6);
  VERIFY (byteImage6.boundary() == overlap2);

}



UTFUNC(rebase)
{
  setDescription ("rebase");

  apRect boundary (-20, -10, 120, 110);
  apImageStorage<Pel8> byteImage (boundary);

  // First check the existing image
  VERIFY (byteImage.boundary() == boundary);
  VERIFY (byteImage.x0()       == -20);
  VERIFY (byteImage.y0()       == -10);
  VERIFY (byteImage.width()    == 120);
  VERIFY (byteImage.height()   == 110);
  VERIFY (byteImage.xoffset()  == 0);
  VERIFY (byteImage.yoffset()  == 0);

  byteImage.rebase ();
  VERIFY (byteImage.boundary() == apRect (0, 0, 120, 110));
  VERIFY (byteImage.x0()       == 0);
  VERIFY (byteImage.y0()       == 0);
  VERIFY (byteImage.width()    == 120);
  VERIFY (byteImage.height()   == 110);
  VERIFY (byteImage.xoffset()  == 0);
  VERIFY (byteImage.yoffset()  == 0);

  // Try it on a window
  byteImage = apImageStorage<Pel8> (boundary);
  row_set<Pel8> (byteImage, 0);

  apRect window (10, 20, 30, 40);
  byteImage.window (window);
  row_set<Pel8> (byteImage, 1);

  VERIFY (byteImage.boundary() == window);
  VERIFY (byteImage.x0()       == 10);
  VERIFY (byteImage.y0()       == 20);
  VERIFY (byteImage.width()    == 30);
  VERIFY (byteImage.height()   == 40);
  VERIFY (byteImage.xoffset()  == 30);
  VERIFY (byteImage.yoffset()  == 30);

  byteImage.rebase ();
  VERIFY (byteImage.boundary() == apRect (0, 0, 30, 40));
  VERIFY (byteImage.x0()       == 0);
  VERIFY (byteImage.y0()       == 0);
  VERIFY (byteImage.width()    == 30);
  VERIFY (byteImage.height()   == 40);
  VERIFY (byteImage.xoffset()  == 30);
  VERIFY (byteImage.yoffset()  == 30);

  int x, y;
  for (y=0; y<byteImage.height(); y++) {
    for (x=0; x<byteImage.width(); x++) {
      VERIFY (byteImage.getPixel (x, y) == 1);
    }
  }

}


UTFUNC(display)
{
  setDescription ("display");

  // Set the image to 0
  apRect boundary (-1, -1, 31, 31);
  apImageStorage<Pel32s> longImage (boundary);
  row_set<Pel32s> (longImage, 0);

  // Set a small window to 1
  apRect boundary2 (1, 2, 4, 5);
  apImageStorage<Pel32s> longImage2 = longImage;
  longImage2.window (boundary2);
  row_set<Pel32s> (longImage2, 1);


  apImageStorage<Pel32s>::row_iterator i;
  for (i=longImage.row_begin(); i != longImage.row_end(); i++) {
    const Pel32s* p = i->p;
    std::cout << i->x << ", " << i->y << ": ";
    for (unsigned int x=0; x<longImage.width(); x++)
      std::cout << *p++ << " ";
    std::cout << std::endl;
  }

  // Verify their values
  for (int y=boundary.y0(); y<boundary.y1(); y++) {
    for (int x=boundary.x0(); x<boundary.x1(); x++) {
      if (x >= 1 && x <= 4 && y >= 2 && y <= 6)
        VERIFY (longImage.getPixel (x, y) == 1);
      else
        VERIFY (longImage.getPixel (x, y) == 0);
    }
  }

  // Do this four other ways as a check
  apImageStorage<Pel32s> longImage3 = longImage;
  longImage3.window (boundary2);
  pixel_set<Pel32s> (longImage3, 1);

  apImageStorage<Pel32s> longImage4 = longImage;
  longImage4.window (boundary2);
  stl_set<Pel32s> (longImage3, 1);

  apImageStorage<Pel32s> longImage5 = longImage;
  longImage5.window (boundary2);
  set_nonstandard<Pel32s> (longImage3, 1);

  apImageStorage<Pel32s> longImage6 = longImage;
  longImage6.window (boundary2);
  set_slow<Pel32s> (longImage3, 1);

  VERIFY (longImage3 == longImage2);
  VERIFY (longImage4 == longImage2);
  VERIFY (longImage5 == longImage2);
  VERIFY (longImage6 == longImage2);
}



UTFUNC(row_iterator)
{
  setDescription ("row iterator");

  apRect boundary (0, 0, 32, 32);
  apImageStorage<Pel32s> longImage (boundary);

  // Set the pixels manually
  unsigned int x, y;
  Pel32s value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      longImage.setPixel (x, y, value++);
    }
  }

  // Verify (forward)
  apImageStorage<Pel32s>::row_iterator i;
  long width = longImage.width ();
  value = 0;
  for (i=longImage.row_begin(); i != longImage.row_end(); i++) {
    Pel32s* p = i->p;
    for (int x=0; x<width; x++) {
      VERIFY (*p++ == value++);
    }
  }
}



UTFUNC(iterator)
{
  setDescription ("pixel iterator");

  apRect boundary (0, 0, 32, 32);
  apImageStorage<Pel32s> longImage (boundary);

  // Set the pixels manually
  unsigned int x, y;
  Pel32s sum = 0;
  Pel32s value = 0;
  for (y=0; y<boundary.height(); y++) {
    for (x=0; x<boundary.width(); x++) {
      sum += value;
      longImage.setPixel (x, y, value++);
    }
  }

  // Verify (forward)
  apImageStorage<Pel32s>::iterator i;
  value = 0;
  for (i=longImage.begin(); i != longImage.end(); i++) {
    VERIFY (*i == value++);
  }

  // Make sure that STL can use this iterator
  Pel32s computedSum = std::accumulate (longImage.begin(), longImage.end(), 0, std::plus<Pel32s>());
  VERIFY (computedSum == sum);

  std::fill (longImage.begin(), longImage.end(), 1);
  for (i=longImage.begin(); i != longImage.end(); i++) {
    VERIFY (*i == 1);
  }

}


#ifdef WIN32
#include "win32/fasttiming.h"

UTFUNC(timing)
{
  setDescription ("win32 timing");
  VERIFY (1 == 1);

  int i;
  apRect boundary (0, 0, 1024, 1024);

  apImageStorage<Pel32s> image (boundary);

  apHiResElapsedTime timer1;
  for (i=0; i<100; i++)
    row_set<Pel32s> (image, 0);
  double t1 = timer1.msec ()/100;

  apHiResElapsedTime timer2;
  for (i=0; i<100; i++)
    pixel_set<Pel32s> (image, 0);
  double t2 = timer2.msec ()/100;

  apHiResElapsedTime timer3;
  for (i=0; i<100; i++)
    stl_set<Pel32s> (image, 0);
  double t3 = timer3.msec ()/100;

  apHiResElapsedTime timer4;
  for (i=0; i<100; i++)
    set_nonstandard<Pel32s> (image, 0);
  double t4 = timer4.msec ()/100;

  apHiResElapsedTime timer5;
  for (i=0; i<10; i++) // Keep this at 10. It's slow!
    set_slow<Pel32s> (image, 0);
  double t5 = timer5.msec ()/10;

  std::cout << "1024x1024 row_set<> in " << t1 << " msec" << std::endl;
  std::cout << "1024x1024 pixel_set<> in " << t2 << " msec" << std::endl;
  std::cout << "1024x1024 stl_set<> in " << t3 << " msec" << std::endl;
  std::cout << "1024x1024 set_nonstandard<> in " << t4 << " msec" << std::endl;
  std::cout << "1024x1024 set_slow<> in " << t5 << " msec" << std::endl;
}

#endif


// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

