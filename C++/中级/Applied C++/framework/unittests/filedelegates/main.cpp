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
// Unit Test for file delegates

#include "image/image.h"
#include "image/convolve.h"
#include "image/imageTransform.h"
#include "delegates/io.h"

#include "unitTest.h"

#include <fstream>

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




UTFUNC(ctor)
{
  setDescription ("Constructor and simple accessor tests");

  apRect boundary (0, 0, 640, 480);
  apImage<Pel8> byteImage3 (boundary, 
                            apRectImageStorage::eQuadWordAlign);

  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("jpg");
  VERIFY (delegate != 0);

  if (delegate) {
    apImage<apRGB> rgb = delegate->readRGB ("test.jpg");
    apImage<apRGB> rgbDest;

    // Only run on right half of image
    apImage<apRGB> rgbWindow = rgb;
    rgbWindow.window (apRect (rgb.width()/2, 0, rgb.width()/2, rgb.height()));

    laplacian3x3<apRGBPel32s>(rgbWindow, rgbDest);
    copy (rgbDest, rgbWindow);

    delegate->write ("output.jpg", rgb);

    // Unsharp mask test
    rgb = delegate->readRGB ("test.jpg");

    apImage<apRGB> unsharp;
    copy (rgb, unsharp);
    unsharpMask<apRGBPel32s> (unsharp, 3.0);
    delegate->write ("unsharpMask.jpg", unsharp);

    
    // Thumbnails
    apImage<apRGB> thumb2 = thumbnail<apRGBPel32s> (rgb, 2);
    delegate->write ("testthumb2.jpg", thumb2);
    apImage<apRGB> thumb3 = thumbnail<apRGBPel32s> (rgb, 3);
    delegate->write ("testthumb3.jpg", thumb3);
    apImage<apRGB> thumb4 = thumbnail<apRGBPel32s> (rgb, 4);
    delegate->write ("testthumb4.jpg", thumb4);
    apImage<apRGB> thumb8 = thumbnail<apRGBPel32s> (rgb, 8);
    delegate->write ("testthumb8.jpg", thumb8);
  }


  // TIFF test

  apImageIOBase* tiffdelegate;
  apImage<apRGB> RGBtiff;
  tiffdelegate = apImageIODelegateList::gOnly().getDelegate ("tif");
  VERIFY (tiffdelegate != 0);
  if (tiffdelegate) {
    RGBtiff = tiffdelegate->readRGB ("saturn.tif");

    delegate->write ("tif.jpg", RGBtiff);
    tiffdelegate->write ("tif.tif", RGBtiff); // Lossless

    apImage<apRGB> lossless;
    tiffdelegate->read ("tif.tif", lossless);
    VERIFY (RGBtiff == lossless);
  }


  // IAP test

  apImageIOBase* iapdelegate;
  iapdelegate = apImageIODelegateList::gOnly().getDelegate ("iap");
  VERIFY (iapdelegate != 0);
  if (iapdelegate) {
    iapdelegate->write ("iap.iap", RGBtiff);

    apImage<apRGB> rgbIAP = iapdelegate->readRGB ("iap.iap");
    if (delegate)
      delegate->write ("iap.jpg", rgbIAP);
  }


}


UTFUNC(jpeg_info)
{
  setDescription ("jpg info");

  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("jpg");
  VERIFY (delegate != 0);

  if (delegate) {
    VERIFY (delegate->info ("nonexistent.jpg").isDelegate == false);
    VERIFY (delegate->info ("iap.iap").isDelegate == false);
    VERIFY (delegate->info ("tif.tif").isDelegate == false);
    apDelegateInfo info = delegate->info ("test.jpg");
    VERIFY (info.isDelegate == true);
    VERIFY (info.boundary.x0() == 0);
    VERIFY (info.boundary.y0() == 0);
    std::cout << "width = " << info.boundary.width() << ", height = " << info.boundary.height() << std::endl;
    VERIFY (info.boundary.width() > 0);
    VERIFY (info.boundary.height() > 0);
    VERIFY (info.planes == 3);
    VERIFY (info.bytesPerPixel == 3);
  }
}

UTFUNC(jpeg_read)
{
  setDescription ("jpg read");


  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("jpg");
  VERIFY (delegate != 0);

  if (delegate) {
    apImage<apRGB> rgb = delegate->readRGB ("nonexistent.jpg");
    VERIFY (rgb == rgb.sNull);
    rgb = delegate->readRGB ("iap.iap");
    VERIFY (rgb == rgb.sNull);
    rgb = delegate->readRGB ("tif.tif");
    VERIFY (rgb == rgb.sNull);

    rgb = delegate->readRGB ("test.jpg");
    VERIFY (rgb != rgb.sNull);
    VERIFY (rgb.x0() == 0);
    VERIFY (rgb.y0() == 0);
    VERIFY (rgb.width() > 0);
    VERIFY (rgb.height() > 0);

    apImage<apRGB> rgb2;
    delegate->read ("test.jpg", rgb2);
    VERIFY (rgb == rgb2);

    apImage<Pel8> byte1;
    delegate->read ("test.jpg", byte1);
  delegate->write ("output-byte.jpg", byte1);

    VERIFY (rgb.boundary() == byte1.boundary());

    apImage<Pel32s> long1;
    delegate->read ("test.jpg", long1);
    VERIFY (rgb.boundary() == long1.boundary());

    // This will output as an rgb
    delegate->write ("test-long.jpg", long1);
  }
}


UTFUNC(tiff_info)
{
  setDescription ("tif info");

  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("tif");
  VERIFY (delegate != 0);

  if (delegate) {
    VERIFY (delegate->info ("nonexistent.tif").isDelegate == false);
    VERIFY (delegate->info ("iap.iap").isDelegate == false);
    VERIFY (delegate->info ("test.jpg").isDelegate == false);
    apDelegateInfo info = delegate->info ("tif.tif");
    VERIFY (info.isDelegate == true);
    VERIFY (info.boundary.x0() == 0);
    VERIFY (info.boundary.y0() == 0);
    std::cout << "width = " << info.boundary.width() << ", height = " << info.boundary.height() << std::endl;
    VERIFY (info.boundary.width() > 0);
    VERIFY (info.boundary.height() > 0);
    VERIFY (info.planes == 3);
    VERIFY (info.bytesPerPixel == 3);
  }
}

UTFUNC(tiff_read)
{
  setDescription ("tif read");


  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("tif");
  VERIFY (delegate != 0);

  if (delegate) {
    apImage<apRGB> rgb = delegate->readRGB ("nonexistent.tif");
    VERIFY (rgb == rgb.sNull);
    rgb = delegate->readRGB ("iap.iap");
    VERIFY (rgb == rgb.sNull);
    rgb = delegate->readRGB ("test.jpg");
    VERIFY (rgb == rgb.sNull);

    rgb = delegate->readRGB ("tif.tif");
    VERIFY (rgb != rgb.sNull);
    VERIFY (rgb.x0() == 0);
    VERIFY (rgb.y0() == 0);
    VERIFY (rgb.width() > 0);
    VERIFY (rgb.height() > 0);

    apImage<apRGB> rgb2;
    delegate->read ("tif.tif", rgb2);
    VERIFY (rgb == rgb2);

    apImage<Pel8> byte1;
    delegate->read ("tif.tif", byte1);
  delegate->write ("tif-byte.tif", byte1);

    VERIFY (rgb.boundary() == byte1.boundary());

    apImage<Pel32s> long1;
    delegate->read ("tif.tif", long1);
    VERIFY (rgb.boundary() == long1.boundary());
  }
}


UTFUNC(iap_info)
{
  setDescription ("iap info");

  apImageIOBase* delegate;
  delegate = apImageIODelegateList::gOnly().getDelegate ("iap");
  VERIFY (delegate != 0);

  if (delegate) {
    VERIFY (delegate->info ("nonexistent.iap").isDelegate == false);
    VERIFY (delegate->info ("test.jpg").isDelegate == false);
    VERIFY (delegate->info ("tif.tif").isDelegate == false);
    apDelegateInfo info = delegate->info ("iap.iap");
    VERIFY (info.isDelegate == true);
    VERIFY (info.boundary.x0() == 0);
    VERIFY (info.boundary.y0() == 0);
    std::cout << "width = " << info.boundary.width() << ", height = " << info.boundary.height() << std::endl;
    VERIFY (info.boundary.width() > 0);
    VERIFY (info.boundary.height() > 0);
    VERIFY (info.planes == 3);
    VERIFY (info.bytesPerPixel == 3);
  }
}


// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

