// jpeg.cpp
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
//  jpeg file delegate

#include "delegates/jpeg.h"
#include <stdio.h>


// jpeglib.h tries to redefine INT32
#ifdef WIN32
#define XMD_H
#endif

extern "C" {
#include "jpeglib.h" // third party
}


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// *****************************
// *                           *
// *  Internal jpeg functions  *
// *                           *
// *****************************

// Redefine some of the standard jpeg error handlers. We don't
// want any output or the application to stop.

// Called when jpeg encounters an error.
// This prevents the application from stopping on an error
void local_error_exit (jpeg_common_struct* cinfo)
{
  char msg[1024];
  sprintf (msg, "error_exit: %d", cinfo->err->msg_code);

  // std::cout << "jpeg: local_error_exit: " << msg << std::endl;
  // You can do something with this error_code if needed
  //  int error_code = cinfo->err->msg_code;
  throw apJPEGException (msg);
}

// Conditionally emit a trace or warning message
void local_emit_message (jpeg_common_struct* /*cinfo*/, int /*msg_level*/)
{
  return;
}

// Routine that actually outputs a trace or error message
void local_output_message (jpeg_common_struct* /*cinfo*/)
{
  //TODO Write this message to our error log
  return;
}


// ************
// *          *
// *  apJPEG  *
// *          *
// ************
//
// JPEG storage delegate


apJPEG* apJPEG::sOnly_ = 0;

apJPEG& apJPEG::gOnly()
{
  if (!sOnly_) sOnly_ = new apJPEG ();
  return *sOnly_;
}


apJPEG::apJPEG ()  {}
apJPEG::~apJPEG () {}

apDelegateInfo apJPEG::info (const std::string& filename)
{
  apDelegateInfo info;
  info.isDelegate    = false;
  info.boundary      = apRect ();
  info.bytesPerPixel = 0;
  info.planes        = 0;

  // Try and open this as jpeg
  struct jpeg_decompress_struct cinfo;
  cinfo.output_width = cinfo.output_height = 0;

  FILE *infile;
  if ((infile = fopen(filename.c_str(), "rb")) == 0)
    return info;

  // Initialize the jpeg decompressor and error handling routines
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jerr.error_exit     = local_error_exit;
  jerr.emit_message   = local_emit_message;
  jerr.output_message = local_output_message;

  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);

  // Read header information
  try {
    jpeg_read_header(&cinfo, TRUE);

    if (cinfo.out_color_space == JCS_GRAYSCALE || cinfo.out_color_space == JCS_RGB) {
      // This is a jpeg image
      info.isDelegate = true;
      info.boundary = apRect (0, 0, cinfo.image_width, cinfo.image_height);
      if (cinfo.out_color_space == JCS_GRAYSCALE)
        info.planes = 1;
      else
        info.planes = 3;
      info.bytesPerPixel = info.planes;
    }
  }
  catch (apJPEGException&) {
  }


  // Cleanup
  jpeg_destroy_decompress (&cinfo);
  fclose(infile);

  return info;
}



apImage<Pel8> apJPEG::readPel8 (const std::string& filename)
{
  return readRGB (filename);
}




apImage<apRGB>  apJPEG::readRGB  (const std::string& filename)
{
  apImage<apRGB> rgbImage;

  struct jpeg_decompress_struct cinfo;
  cinfo.output_width = cinfo.output_height = 0;

  FILE *infile;
  if ((infile = fopen(filename.c_str(), "rb")) == 0) {
    return rgbImage;
  }

  // Initialize the jpeg decompressor and error handling routines
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jerr.error_exit     = local_error_exit;
  jerr.emit_message   = local_emit_message;
  jerr.output_message = local_output_message;

  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);

  // Read header information
  try {
    jpeg_read_header(&cinfo, TRUE);
    if (cinfo.out_color_space == JCS_UNKNOWN)
      return apImage<apRGB>::sNull;

    // Enter our decompressor loop
    jpeg_start_decompress(&cinfo);

    // If the height or width is zero, there was an error
    if (cinfo.output_width == 0) {
      jpeg_destroy_decompress (&cinfo);
      fclose(infile);
      return rgbImage;
    }

    // Allocate our entire image,
    //TODO this assumes 8:8:8
    apRect boundary (0, 0, cinfo.output_width, cinfo.output_height);
    rgbImage = apImage<apRGB> (boundary);

    Pel8* buffer[1];
    long y = 0;

    // Read each line. The memory layout depends on the image type
    switch (cinfo.out_color_space) {
    case JCS_GRAYSCALE:
      // Allocate a row of data
      buffer[0] = new Pel8 [cinfo.output_width];
      while (cinfo.output_scanline < cinfo.output_height) {
        // Read a single line right now
        apRGB* dst = rgbImage.rowAddress (cinfo.output_scanline);
        y += jpeg_read_scanlines (&cinfo, buffer, 1);
        Pel8* src = buffer[0];
        for (unsigned int x=0; x<cinfo.output_width; x++)
          *dst++ = *src++;
      }
      delete [] buffer[0];
      break;
    case JCS_RGB:
      // The data we get from jpeg_read_scanlines aligns with our own format
      while (cinfo.output_scanline < cinfo.output_height) {
        // Read a single line right now
        buffer[0] = reinterpret_cast<unsigned char*>(rgbImage.rowAddress (cinfo.output_scanline));
        y += jpeg_read_scanlines (&cinfo, buffer, 1);
      }
      break;
    default:
      // Unknown image type
      break;
    }

    jpeg_finish_decompress  (&cinfo);
  }
  catch (apJPEGException&) {
  }

  jpeg_destroy_decompress (&cinfo);
  fclose(infile);
  return rgbImage;
}


bool apJPEG::write (const std::string& filename,
                    const apRectImageStorage& pixels, 
                    const apDelegateParams& params)
{
  struct jpeg_compress_struct cinfo;

  FILE *outfile;
  if ((outfile = fopen(filename.c_str(), "wb")) == 0)
    return false;

  // Write an empty file if we are passed a null image
  if (pixels.isNull()) {
    fclose (outfile);
    return false;
  }

  // Initialize the jpeg decompressor
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jerr.error_exit     = local_error_exit;
  jerr.emit_message   = local_emit_message;
  jerr.output_message = local_output_message;


  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, outfile);

  // Initialize our header
  if (pixels.bytesPerPixel () == 3) {
    // Assume RGB image
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB; 
  }
  else if (pixels.bytesPerPixel () == 1) {
    // Assume Pel8 image
    cinfo.input_components = 1;
    cinfo.in_color_space = JCS_GRAYSCALE; 
  }
  else {
    //TODO Convert to RGB and save
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB; 
  }

  cinfo.image_width = pixels.width ();
  cinfo.image_height = pixels.height ();

  jpeg_set_defaults(&cinfo);

  // Set the quality
  int quality = static_cast<int> (params.quality);
  if (quality < 0)   quality = 50;
  if (quality > 100) quality = 100;
   jpeg_set_quality(&cinfo, quality, TRUE);

  // Compress each line

  jpeg_start_compress(&cinfo, TRUE);
  const Pel8* buffer[1];
  long y0 = pixels.y0();
  while (cinfo.next_scanline < cinfo.image_height) {
    buffer[0] = pixels.rowAddress_ (y0 + cinfo.next_scanline);
    jpeg_write_scanlines(&cinfo, const_cast<Pel8**>(buffer), 1);
  }

  // Cleanup
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  fclose(outfile);

  return false;
}


// Add this delegate to our list during static initialization
apJPEG_installer apJPEG_installer::installer;
apJPEG_installer::apJPEG_installer ()
{
  apImageIODelegateList::gOnly().setDelegate ("jpg", &apJPEG::gOnly());
}
