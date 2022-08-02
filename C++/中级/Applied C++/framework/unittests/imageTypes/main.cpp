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

#include "image/imageTypes.h"

#include "unitTest.h"

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


UTFUNC (apLimitPel8Pel8)
{
  setDescription ("apLimit<Pel8,Pel8>");

  Pel8 v1 = 0;
  Pel8 v2;
  for (;;) {
    v2 = apLimit<Pel8> (v1);
    VERIFY (v1 == v2);
    if (v1 == apLimitInfo<Pel8>::sType.maxValue) break;
    v1++;
  }
}

UTFUNC (apLimitPel8Pel16)
{
  setDescription ("apLimit<Pel8,Pel16>");

  Pel8 v1 = 0;
  Pel16 v2;
  for (;;) {
    v2 = apLimit<Pel16> (v1);
    VERIFY (v1 == v2);
    if (v1 == apLimitInfo<Pel8>::sType.maxValue) break;
    v1++;
  }
}

UTFUNC (apLimitPel8Pel32s)
{
  setDescription ("apLimit<Pel8,Pel32s>");

  Pel8 v1 = 0;
  Pel32s v2;
  for (;;) {
    v2 = apLimit<Pel32s> (v1);
    VERIFY (v1 == v2);
    if (v1 == apLimitInfo<Pel8>::sType.maxValue) break;
    v1++;
  }
}


UTFUNC (apLimitPel32sPel32s)
{
  setDescription ("apLimit<Pel32s,Pel32s>");

  Pel32s v1 = 0;
  Pel32s v2;
  for (;;) {
    v2 = apLimit<Pel32s> (v1);
    VERIFY (v1 == v2);
    if (v1 == 100000) break;
    v1++;
  }
}

UTFUNC (apLimitPel32sPel8)
{
  setDescription ("apLimit<Pel32s,Pel8>");

  Pel32s v1 = 0;
  Pel8 v2;
  for (;;) {
    v2 = apLimit<Pel8> (v1);
    if (v1 <= apLimitInfo<Pel8>::sType.maxValue)
      VERIFY (v1 == v2);
    else
      VERIFY (v2 == apLimitInfo<Pel8>::sType.maxValue);

    if (v1 == 100000) break;
    v1++;
  }
}


UTFUNC (apLimitPel32sPel16)
{
  setDescription ("apLimit<Pel32s,Pel16>");

  Pel32s v1 = 0;
  Pel16 v2;
  for (;;) {
    v2 = apLimit<Pel16> (v1);
    if (v1 <= apLimitInfo<Pel16>::sType.maxValue)
      VERIFY (v1 == v2);
    else
      VERIFY (v2 == apLimitInfo<Pel16>::sType.maxValue);

    if (v1 == 100000) break;
    v1++;
  }
}



UTFUNC (lfuncs)
{
  setDescription ("int Functions");

  int l1;
  int l2 = 10;
  int l;

  for (l1=0; l1<1000; l1++) {
    l = add2<int> (l1, l2);
    VERIFY (l == (l1 + l2));

    l = sub2<int> (l1, l2);
    VERIFY (l == (l1 - l2));

    l = mul2<int> (l1, l2);
    VERIFY (l == (l1 * l2));

    l = div2<int> (l1, l2);
    VERIFY (l == (l1 / l2));

    l = scale<int> (l1, 2.0);
    VERIFY (l == (l1 * 2));
  }

  Pel8 b;
  for (l1=0; l1<1000; l1++) {
    b = add2<Pel8> (l1, l2);
    VERIFY (b == (Pel8)(l1 + l2));

    b = sub2<Pel8> (l1, l2);
    VERIFY (b == (Pel8)(l1 - l2));

    b = mul2<Pel8> (l1, l2);
    VERIFY (b == (Pel8)(l1 * l2));

    b = div2<Pel8> (l1, l2);
    VERIFY (b == (Pel8)(l1 / l2));

    b = scale<Pel8> (l1, 2.0);
    VERIFY (b == (Pel8)(l1 * 2));
  }

  Pel16 w;
  for (l1=0; l1<1000; l1++) {
    w = add2<Pel16> (l1, l2);
    VERIFY (w == (Pel16)(l1 + l2));

    w = sub2<Pel16> (l1, l2);
    VERIFY (w == (Pel16)(l1 - l2));

    w = mul2<Pel16> (l1, l2);
    VERIFY (w == (Pel16)(l1 * l2));

    w = div2<Pel16> (l1, l2);
    VERIFY (w == (Pel16)(l1 / l2));

    w = scale<Pel16> (l1, 2.0);
    VERIFY (w == (Pel16)(l1 * 2));
  }

}

UTFUNC (apClampedTmplPel8)
{
  setDescription ("apClampedTmpl<Pel8>");

  apClampedTmpl<Pel8> b = 0;
  VERIFY (b == 0);
  VERIFY (0 == b);

  b += apClampedTmpl<Pel8> (1);
  VERIFY (b == 1);
  b += 1;
  VERIFY (b == 2);

  b -= apClampedTmpl<Pel8> (1);
  VERIFY (b == 1);
  b -= 1;
  VERIFY (b == 0);

  b = 1;
  b *= apClampedTmpl<Pel8> (2);
  VERIFY (b == 2);
  b *= 2;
  VERIFY (b == 4);

  b /= apClampedTmpl<Pel8> (2);
  VERIFY (b == 2);
  b /= 2;
  VERIFY (b == 1);

  apClampedTmpl<Pel8> b1 = b + 1;
  VERIFY (b1 == 2);
  b1 = b + b1;
  VERIFY (b1 == 3);

  b = 255;
  VERIFY (b == 255);
  b += 1;
  VERIFY (b == 255);
  b -= 1;
  VERIFY (b == 254);
  b *= 2;
  VERIFY (b == 255);
  b /= 2;
  VERIFY (b == 127);
}


UTFUNC (apClampedTmplPel16)
{
  setDescription ("apClampedTmpl<Pel16>");

  apClampedTmpl<Pel16> w = 0;
  VERIFY (w == 0);
  VERIFY (0 == w);

  w += apClampedTmpl<Pel16> (1);
  VERIFY (w == 1);
  w += 1;
  VERIFY (w == 2);

  w -= apClampedTmpl<Pel16> (1);
  VERIFY (w == 1);
  w -= 1;
  VERIFY (w == 0);

  w = 1;
  w *= apClampedTmpl<Pel16> (2);
  VERIFY (w == 2);
  w *= 2;
  VERIFY (w == 4);

  w /= apClampedTmpl<Pel16> (2);
  VERIFY (w == 2);
  w /= 2;
  VERIFY (w == 1);

  apClampedTmpl<Pel16> w1 = w + 1;
  VERIFY (w1 == 2);
  w1 = w + w1;
  VERIFY (w1 == 3);

  w = 65535;
  VERIFY (w == 65535);
  w += 1;
  VERIFY (w == 65535);
  w -= 1;
  VERIFY (w == 65534);
  w *= 2;
  VERIFY (w == 65535);
  w /= 2;
  VERIFY (w == 32767);
}


UTFUNC (apClampedTmplPel8Pel32s)
{
  setDescription ("apClampedTmpl Pel8, Pel32s");

  apClampedTmpl<Pel8> b = 0;
  apClampedTmpl<Pel32s> l = 0;

  for (l=0; l<1000; l+=1) {
    b = l;
    if (l < 256)
      VERIFY (b == l);
    else
      VERIFY (b == 255);
  }

  l = 512;
  b = l + 1;
  VERIFY (b == 255);
  b = l / 2;
  VERIFY (b == 255);
  b = l - 256;
  VERIFY (b == 255);
  b = l - 258;
  VERIFY (b == 254);

  apClampedTmpl<Pel8> b1 = b;
  VERIFY (b1 == b);
  b1 += 1;
  VERIFY (b1 != b);
}


UTFUNC (apClampedTmplFuncs)
{
  setDescription ("apClampedTmpl Funcs");

  apClampedTmpl<Pel8> b  = 250;
  apClampedTmpl<Pel32s> l  = 2;
  apClampedTmpl<Pel8> b1;

  b1 = add2<Pel8> (b, l);
  VERIFY (b1 == 252);
  b1 = add2<Pel8> (b1, l);
  VERIFY (b1 == 254);
  b1 = add2<Pel8> (b1, l);
  VERIFY (b1 == 255);
  l = add2<Pel32s> (b, b1);
  VERIFY (l == 505);

  b = 2;
  l = 2;
  b1 = sub2<Pel8> (b, l);
  VERIFY (b1 == 0);
  b1 = sub2<Pel8> (b1, l);
  VERIFY (b1 == 0);

  b = 200;
  l = 200;
  l = l + b;
  VERIFY (l == 400);

  l = 200;
  l = b + l;   // This returns a Pel8
  VERIFY (l == 255);
}


UTFUNC (apClampedTmplRGB)
{
  setDescription ("apClampedTmpl<apRGB>");

  apRGB rgb (0);
  VERIFY (rgb.red == 0);
  VERIFY (rgb.green == 0);
  VERIFY (rgb.blue == 0);

  rgb += 255;
  VERIFY (rgb.red == 255);
  VERIFY (rgb.green == 255);
  VERIFY (rgb.blue == 255);

  rgb += 1;
  VERIFY (rgb.red == 255);
  VERIFY (rgb.green == 255);
  VERIFY (rgb.blue == 255);

  rgb -= 255;
  VERIFY (rgb.red == 0);
  VERIFY (rgb.green == 0);
  VERIFY (rgb.blue == 0);

  rgb -= 1;
  VERIFY (rgb.red == 0);
  VERIFY (rgb.green == 0);
  VERIFY (rgb.blue == 0);

  apRGBPel32s rgbl (256, 256, 256);
  rgb = rgbl;
  VERIFY (rgbl.red == 256);
  VERIFY (rgbl.green == 256);
  VERIFY (rgbl.blue == 256);
  VERIFY (rgb.red == 255);
  VERIFY (rgb.green == 255);
  VERIFY (rgb.blue == 255);

  apRGB rgb2 = rgb;
  VERIFY (rgb2.red == 255);
  VERIFY (rgb2.green == 255);
  VERIFY (rgb2.blue == 255);
}

// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

