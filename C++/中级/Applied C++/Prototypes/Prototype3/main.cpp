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

#include "imageTmpl.h"
#include "imageStorageTmpl.h"
#include "unitTest.h"
#include "iostream"

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


typedef unsigned char  Pel8;
typedef unsigned long  Pel32;

#ifdef RGB
#undef RGB
#endif

// Our basic color data type (8:8:8 format)
typedef struct RGB {
  Pel8 red; 
  Pel8 green; 
  Pel8 blue; 

  RGB (Pel8 b=0) : red (b), green (b), blue (b) {}
} RGB;

// Internal definition during computation (32:32:32 format)
typedef struct RGBPel32 {
  Pel32 red; 
  Pel32 green; 
  Pel32 blue; 

  RGBPel32 (Pel32 l=0) : red (l), green (l), blue (l) {}

} RGBPel32;


// These are needed by our apImage<> class

RGBPel32& operator += (RGBPel32& s1, const RGB& s2)
{
  s1.red += s2.red;
  s1.green += s2.green;
  s1.blue += s2.blue;
  return s1;
}

RGB operator/ (const RGBPel32& s1, int den)
{
  RGB div;
  div.red   = static_cast<Pel8>(s1.red / den);
  div.green = static_cast<Pel8>(s1.green / den);
  div.blue  = static_cast<Pel8>(s1.blue / den);
  return div;
}



// These functions are needed for our unit test

RGBPel32 operator+ (const RGB& s1, const RGB& s2)
{
  RGBPel32 sum;
  sum.red = s1.red + s2.red;
  sum.green = s1.green + s2.green;
  sum.blue = s1.blue + s2.blue;
  return sum;
}

RGBPel32 operator+ (const RGBPel32& s1, const RGB& s2)
{
  RGBPel32 sum;
  sum.red = s1.red + s2.red;
  sum.green = s1.green + s2.green;
  sum.blue = s1.blue + s2.blue;
  return sum;
}

bool operator== (const RGB& s1, const RGB& s2)
{
  return (s1.red == s2.red) && (s1.green == s2.green) && 
         (s1.blue == s2.blue);
}







UTFUNC(imageStoragePel8)
{
  setDescription ("imageStorage Pel8");

  apImageStorageTmpl<Pel8> is1 (640, 480);
  VERIFY (is1->width()  == 640);
  VERIFY (is1->height() == 480);
  VERIFY (is1->ref() == 1);
  VERIFY (is1->bytesPerPixel() == 1);

  // Convert to base class
  apImageStorage is = is1;
  VERIFY (is->width()  == 640);
  VERIFY (is->height() == 480);
  VERIFY (is->ref() == 2);
  VERIFY (is->bytesPerPixel() == 1);

  // Pointer to image data
  Pel8* base1 = is1->base ();
  Pel8* base  = is->base ();
  VERIFY (base1 == base);
}


UTFUNC(imageStorageRGB)
{
  setDescription ("imageStorage RGB");

  apImageStorageTmpl<RGB> is1 (640, 480);
  VERIFY (is1->width()  == 640);
  VERIFY (is1->height() == 480);
  VERIFY (is1->ref() == 1);
  VERIFY (is1->bytesPerPixel() == 3);

  // Convert to base class
  apImageStorage is = is1;
  VERIFY (is->width()  == 640);
  VERIFY (is->height() == 480);
  VERIFY (is->ref() == 2);
  VERIFY (is->bytesPerPixel() == 3);

  // Pointer to image data
  RGB*  base1 = is1->base ();
  Pel8* base  = is->base ();
  VERIFY ((void*)base1 == (void*)base);
}



UTFUNC(image8)
{
  setDescription ("image 8");

  unsigned int x, y;

  apImage<Pel8, Pel32> p1;
  VERIFY (p1.width()  == 0);
  VERIFY (p1.height() == 0);

  apImage<Pel8, Pel32> p2 (640, 480);
  VERIFY (p2.width()  == 640);
  VERIFY (p2.height() == 480);

  // Test pixels() and getPixel()
  memset (p2.pixels(), 0x5a, 640*480);
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++)
      VERIFY (p2.getPixel (x, y) == 0x5a);

  // Test setPixel() and getPixel()
  Pel8 pel = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++)
      p2.setPixel (x, y, pel++);

  pel = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++)
      VERIFY (p2.getPixel (x, y) == pel++);

}



UTFUNC(imageRGB)
{
  unsigned int x, y;

  setDescription ("apImage RGB");

  apImage<RGB, RGBPel32> p1;
  VERIFY (p1.width()  == 0);
  VERIFY (p1.height() == 0);

  apImage<RGB, RGBPel32> p2 (640, 480);
  VERIFY (p2.width()  == 640);
  VERIFY (p2.height() == 480);

  // Test pixels() and getPixel()
  RGB* pels = p2.pixels();
  RGB pel;
  pel.red = pel.green = pel.blue = 0;
  for (x=0; x<p2.height() * p2.width(); x++) {
    memcpy (pels++, &pel, sizeof (pel));
    pel.red++;
    pel.green++;
    pel.blue++;
  }

  RGB rgb;
  pel.red = pel.green = pel.blue = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++) {
      rgb = p2.getPixel (x, y);
      VERIFY (rgb.red   == pel.red);
      VERIFY (rgb.green == pel.green);
      VERIFY (rgb.blue  == pel.blue);
      pel.red++;
      pel.green++;
      pel.blue++;
    }


  // Test setPixel() and getPixel()
  pel.red = pel.green = pel.blue = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++) {
      p2.setPixel (x, y, pel);
      pel.red++;
      pel.green++;
      pel.blue++;
    }

  pel.red = pel.green = pel.blue = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++) {
      rgb = p2.getPixel (x, y);
      VERIFY (rgb.red   == pel.red);
      VERIFY (rgb.green == pel.green);
      VERIFY (rgb.blue  == pel.blue);
      pel.red++;
      pel.green++;
      pel.blue++;
    }
}



UTFUNC(thumbnail8)
{
  unsigned int x, y;

  setDescription ("apImage8 thumbnail");

  apImage<Pel8, Pel32> p (32, 32);
  VERIFY (p.width()  == 32);
  VERIFY (p.height() == 32);

  // Set the data
  Pel8 pel = 0;
  for (y=0; y<p.height(); y++)
    for (x=0; x<p.width(); x++)
      p.setPixel (x, y, pel++);

  apImage<Pel8, Pel32> thumbnail = p.thumbnail (2);
  VERIFY (thumbnail.width() == 16);
  VERIFY (thumbnail.height() == 16);

  for (y=0; y<thumbnail.height(); y++) {
    for (x=0; x<thumbnail.width(); x++) {
      pel = (p.getPixel (2*x,   2*y) +
             p.getPixel (2*x,   2*y+1) +
             p.getPixel (2*x+1, 2*y) +
             p.getPixel (2*x+1, 2*y+1)) / 4;
      VERIFY (thumbnail.getPixel (x, y) == pel);
    }
  }
}



UTFUNC(thumbnailRGB)
{
  unsigned int x, y;

  setDescription ("apImage RGB thumbnail");

  apImage<RGB, RGBPel32> p (32, 32);
  VERIFY (p.width()  == 32);
  VERIFY (p.height() == 32);

  // Set the data
  RGB pel;
  pel.red = pel.green = pel.blue = 0;
  for (y=0; y<p.height(); y++)
    for (x=0; x<p.width(); x++) {
      p.setPixel (x, y, pel);
      pel.red++;
      pel.green++;
      pel.blue++;
    }


  apImage<RGB, RGBPel32> thumbnail = p.thumbnail (2);
  VERIFY (thumbnail.width() == 16);
  VERIFY (thumbnail.height() == 16);

  for (y=0; y<thumbnail.height(); y++) {
    for (x=0; x<thumbnail.width(); x++) {
      pel = (p.getPixel (2*x,   2*y) +
             p.getPixel (2*x,   2*y+1) +
             p.getPixel (2*x+1, 2*y) +
             p.getPixel (2*x+1, 2*y+1)) / 4;
      VERIFY (thumbnail.getPixel (x, y) == pel);
    }
  }
}




// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

