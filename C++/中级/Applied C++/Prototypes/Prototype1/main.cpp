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


#include "image.h"
#include "unitTest.h"
#include "iostream"

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


UTFUNC(image8)
{
  unsigned int x, y;

  setDescription ("apImage8");

  apImage8 p1;
  VERIFY (p1.width()  == 0);
  VERIFY (p1.height() == 0);

  apImage8 p2 (640, 480);
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



UTFUNC(thumbnail)
{
  unsigned int x, y;

  setDescription ("apImage8 thumbnail");

  apImage8 p (32, 32);
  VERIFY (p.width()  == 32);
  VERIFY (p.height() == 32);

  // Set the data
  Pel8 pel = 0;
  for (y=0; y<p.height(); y++)
    for (x=0; x<p.width(); x++)
      p.setPixel (x, y, pel++);

  apImage8 thumbnail = p.thumbnail (2);

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



UTFUNC(image32)
{
  unsigned int x, y;

  setDescription ("apImage32");

  apImage32 p1;
  VERIFY (p1.width()  == 0);
  VERIFY (p1.height() == 0);

  apImage32 p2 (640, 480);
  VERIFY (p2.width()  == 640);
  VERIFY (p2.height() == 480);

  // Test pixels() and getPixel()
  Pel32 pel = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++)
      p2.setPixel (x, y, pel++);
  pel = 0;
  for (y=0; y<p2.height(); y++)
    for (x=0; x<p2.width(); x++)
      VERIFY (p2.getPixel (x, y) == pel++);
}



UTFUNC(thumbnail32)
{
  unsigned int x, y;

  setDescription ("apImage32 thumbnail");

  apImage32 p (32, 32);
  VERIFY (p.width()  == 32);
  VERIFY (p.height() == 32);

  // Set the data
  Pel32 pel = 0;
  for (y=0; y<p.height(); y++)
    for (x=0; x<p.width(); x++)
      p.setPixel (x, y, pel++);

  apImage32 thumbnail = p.thumbnail (2);

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

