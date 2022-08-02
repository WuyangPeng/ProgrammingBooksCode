// tiff.cpp
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
//  tiff file delegate

#include "delegates/tiff.h"
#include <stdio.h>


#include "tiffio.h"

//extern "C" {
//#include "TIFFlib.h" // third party
//}


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *****************************
// *                           *
// *  Internal tiff functions  *
// *                           *
// *****************************

// Redefine some of the standard tiff error handlers. We don't
// want any output or the application to stop.

// Capture errors
void TIFFError(const char* /*module*/, const char* fmt, va_list argptr)
{
  char msg[10240];  
  vsprintf (msg, fmt, argptr);

  // For debugging only
  // std::cout << "TIFFError: " << msg << std::endl;

  throw apTIFFException (msg);
}




// ************
// *          *
// *  apTIFF  *
// *          *
// ************
//
// TIFF storage delegate


apTIFF* apTIFF::sOnly_ = 0;

apTIFF& apTIFF::gOnly()
{
  if (!sOnly_) sOnly_ = new apTIFF ();
  return *sOnly_;
}

apTIFF::apTIFF ()  {}
apTIFF::~apTIFF () {}

apDelegateInfo apTIFF::info (const std::string& filename)
{
  apDelegateInfo info;
  info.isDelegate    = false;
  info.boundary      = apRect ();
  info.bytesPerPixel = 0;
  info.planes        = 0;

  TIFFSetWarningHandler (0);
  TIFFSetErrorHandler   (TIFFError);

  try {
    TIFF* tif = TIFFOpen(filename.c_str(), "r");
    if (!tif)
      return info;

    uint32 w, h;
    if (TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w) == 0)
      return info;
    if (TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h) == 0)
      return info;

    info.isDelegate = true;
    info.boundary = apRect (0, 0, w, h);
    info.bytesPerPixel = 3;
    info.planes = 3;
  }
  catch (apTIFFException&) {
    // Add any special recovery code here (or rethrow)
  }

  return info;
}



apImage<Pel8> apTIFF::readPel8 (const std::string& filename)
{
  return readRGB (filename);
}

apImage<apRGB>  apTIFF::readRGB  (const std::string& filename)
{
  apImage<apRGB> rgbImage;

  TIFFSetWarningHandler (0);
  TIFFSetErrorHandler   (TIFFError);

  try {
    TIFF* tif = TIFFOpen(filename.c_str(), "r");
    if (!tif)
      return rgbImage;

    uint32 w, h;
    size_t npixels;
    uint32* raster;

    // This reads the entire image into memory
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
    npixels = w * h;
    raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
    if (raster != 0) {
      if (TIFFReadRGBAImage(tif, w, h, raster, 0)) {
        // Extract the data we want, i.e. the rgb information
        apRect boundary (0, 0, w, h);
        rgbImage = apImage<apRGB> (boundary);
        uint32* tiffp = raster;
        uint32 tiffpel;
        for (unsigned int y=0; y<h; y++) {
          // Reverse the order since tiff is bottom to top??
          apRGB* rgb = rgbImage.rowAddress (h-1-y);
          for (unsigned int x=0; x<w; x++, rgb++) {
            tiffpel = *tiffp++;
            rgb->red   = static_cast<Pel8>(TIFFGetR(tiffpel));
            rgb->green = static_cast<Pel8>(TIFFGetG(tiffpel));
            rgb->blue  = static_cast<Pel8>(TIFFGetB(tiffpel));
          }
       }
      }
      _TIFFfree(raster);
    }
    TIFFClose(tif);
  }
  catch (apTIFFException&) {
    // Add any special recovery code here (or rethrow)
  }


  return rgbImage;
}

bool apTIFF::write (const std::string& filename,
                    const apRectImageStorage& pixels, 
                    const apDelegateParams& /*params*/)
{
  TIFFSetWarningHandler (0);
  TIFFSetErrorHandler   (TIFFError);

  try {
    TIFF* tif = TIFFOpen(filename.c_str(), "w");
    if (!tif)
      return false;

    if (pixels.isNull()) {
      TIFFClose (tif);
      return false;
    }

    //TODO This assumes RGB
    if (pixels.bytesPerPixel() == 3) {
      // RGB
      TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
      TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
      TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
    }
    else if (pixels.bytesPerPixel() == 1) {
     // 8-bit monochrome
      TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
      TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
      TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    }
    else {
      //TODO
      // Write as RGB
    }


    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, pixels.width() );
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, pixels.height() );
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_XRESOLUTION, 1);
    TIFFSetField(tif, TIFFTAG_YRESOLUTION, 1);
    TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, 1);

    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW);

    // Write one line at a time
    int status;
    for (unsigned int y=0; y<pixels.height(); y++) {
      const void* row = reinterpret_cast<const void*>(pixels.rowAddress_ (pixels.y0() + y));
      status = TIFFWriteScanline(tif, const_cast<void*>(row), y);
      if (status == -1) {
        // An error occured
        TIFFClose (tif);
        return false;
      }
    }

    TIFFClose (tif);
  }
  catch (apTIFFException&) {
    // Add any special recovery code here (or rethrow)
  }

  return true;
}


// Add this delegate to our list during static initialization
apTIFF_installer apTIFF_installer::installer;
apTIFF_installer::apTIFF_installer ()
{
  apImageIODelegateList::gOnly().setDelegate ("tiff", &apTIFF::gOnly());
  apImageIODelegateList::gOnly().setDelegate ("tif", &apTIFF::gOnly());
}
