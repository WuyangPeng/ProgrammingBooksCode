// iap.cpp
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
// iap file delegate (our own file format)

#include "delegates/iap.h"
#include <stdio.h>



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***********
// *         *
// *  apIAP  *
// *         *
// ***********
//
// apIAP storage delegate


apIAP* apIAP::sOnly_ = 0;

apIAP& apIAP::gOnly()
{
  if (!sOnly_) sOnly_ = new apIAP ();
  return *sOnly_;
}

apIAP::apIAP ()  {}
apIAP::~apIAP () {}

apDelegateInfo apIAP::info (const std::string& filename)
{
  apDelegateInfo info;
  info.isDelegate    = false;
  info.boundary      = apRect ();
  info.bytesPerPixel = 0;
  info.planes        = 0;

  // Open the file
  FILE *infile;
  if ((infile = fopen(filename.c_str(), "rb")) == 0) {
    return info;
  }

  // Read the header
  apIAPFileHeader header;
  size_t read = fread (&header, sizeof (header), 1, infile);
  if (read != 1)
    return info;
  if (strncmp (header.signature, "apIAP   ", 8) != 0)
    return info;

  // Only support a single image
  if (header.nImages != 1)
    return info;

  // Read the image header
  apIAPImageHeader imageHeader;
  read = fread (&imageHeader, sizeof (imageHeader), 1, infile);
  if (read != 1)
    return info;

  info.isDelegate = true;
  info.boundary = apRect (imageHeader.x0, imageHeader.y0, imageHeader.width, imageHeader.height);
  info.bytesPerPixel = imageHeader.channels * imageHeader.depth/8;
  info.planes = imageHeader.channels;

  return info;
}



apImage<Pel8> apIAP::readPel8 (const std::string& filename)
{
  apImage<Pel8> dst;

  // Open the file
  FILE *infile;
  if ((infile = fopen(filename.c_str(), "rb")) == 0) {
    return dst;
  }

  // Read the header
  apIAPFileHeader header;
  size_t read = fread (&header, sizeof (header), 1, infile);
  if (read != 1)
    return dst;
  if (strncmp (header.signature, "apIAP   ", 8) != 0)
    return dst;

  // Only support a single image
  if (header.nImages != 1)
    return dst;

  // Read the image header
  apIAPImageHeader imageHeader;
  read = fread (&imageHeader, sizeof (imageHeader), 1, infile);
  if (read != 1)
    return dst;

  if (imageHeader.type == eRGB)
    dst = _readRGB (infile, imageHeader);
  else if (imageHeader.type == eMono)
    dst = _readPel8 (infile, imageHeader);
  else
    return dst; // Unknown file format

  fclose (infile);
  return dst;
}



apImage<apRGB>  apIAP::readRGB  (const std::string& filename)
{
  apImage<apRGB> dst;

  // Open the file
  FILE *infile;
  if ((infile = fopen(filename.c_str(), "rb")) == 0) {
    return dst;
  }

  // Read the header
  apIAPFileHeader header;
  size_t read = fread (&header, sizeof (header), 1, infile);
  if (read != 1)
    return dst;
  if (strncmp (header.signature, "apIAP   ", 8) != 0)
    return dst;

  // Only support a single image
  if (header.nImages != 1)
    return dst;

  // Read the image header
  apIAPImageHeader imageHeader;
  read = fread (&imageHeader, sizeof (imageHeader), 1, infile);
  if (read != 1)
    return dst;

  if (imageHeader.type == eRGB)
    dst = _readRGB (infile, imageHeader);
  else if (imageHeader.type == eMono)
    dst = _readPel8 (infile, imageHeader);
  else
    return dst; // Unknown file format

  fclose (infile);
  return dst;
}


apImage<apRGB>  apIAP::_readRGB  (FILE* fp, const apIAPImageHeader& imageHeader)
{
  // Construct our destination image
  apRect boundary (imageHeader.x0, imageHeader.y0,
                   imageHeader.width, imageHeader.height);
  apImage<apRGB> dst (boundary, apRectImageStorage::eQuadWordAlign);

  // Process each line
  size_t read;
  long bytesPerRow = imageHeader.width * imageHeader.channels * imageHeader.depth/8;
  for (long y=0; y<imageHeader.height; y++) {
    read = fread (dst.rowAddress (y+imageHeader.y0), bytesPerRow, 1, fp);
    if (read != 1) {
      // We didn't read the information
      dst = dst.sNull;
      break;
    }
  }
  return dst;
}

apImage<Pel8>  apIAP::_readPel8  (FILE* fp, const apIAPImageHeader& imageHeader)
{
  // Construct our destination image
  apRect boundary (imageHeader.x0, imageHeader.y0,
                   imageHeader.width, imageHeader.height);
  apImage<Pel8> dst (boundary, apRectImageStorage::eQuadWordAlign);

  // Process each line
  size_t read;
  long bytesPerRow = imageHeader.width * imageHeader.channels * imageHeader.depth/8;
  for (long y=0; y<imageHeader.height; y++) {
    read = fread (dst.rowAddress (y+imageHeader.y0), bytesPerRow, 1, fp);
    if (read != 1) {
      // We didn't read the information
      dst = dst.sNull;
      break;
    }
  }
  return dst;
}



bool apIAP::write (const std::string& filename,
                    const apRectImageStorage& pixels, 
                    const apDelegateParams& /*params*/)
{
  apIAPFileHeader header;
  strncpy (header.signature, "apIAP   ", 8);
  header.version = 0;
  header.nImages = 1;

  // Assumes RGB
  apIAPImageHeader imageHeader;
  imageHeader.x0       = pixels.x0 ();
  imageHeader.y0       = pixels.y0 ();
  imageHeader.width    = pixels.width ();
  imageHeader.height   = pixels.height ();
  imageHeader.format   = eNone;
  imageHeader.channels = 3;
  imageHeader.type     = eRGB;
  imageHeader.depth    = 8;


  if (pixels.bytesPerPixel() == 3) {
    // RGB
    imageHeader.channels = 3;
    imageHeader.type     = eRGB;
    imageHeader.depth    = 8;
  }
  else if (pixels.bytesPerPixel() == 1) {
    // Byte
    imageHeader.channels = 1;
    imageHeader.type     = eMono;
    imageHeader.depth    = 8;
  }
  else {
    // Other pixel format. Convert to RGB...
  }

  FILE *outfile;
  if ((outfile = fopen(filename.c_str(), "wb")) == 0)
    return false;

  // Write the headers
  size_t bytes;
  bytes = fwrite (&header, sizeof (header), 1, outfile);
  if (bytes == 1)
    bytes = fwrite (&imageHeader, sizeof (imageHeader), 1, outfile);

  // 
  if (bytes != 1 || pixels.isNull()) {
    fclose (outfile);
    return false;
  }

  // Write each row
  bool status = true;
  long bytesPerRow = imageHeader.width * imageHeader.channels * imageHeader.depth/8;
  for (long y=0; y<imageHeader.height; y++) {
    bytes = fwrite (pixels.rowAddress_ (y+imageHeader.y0), bytesPerRow, 1, outfile);
    if (bytes != 1) {
      // We didn't read the information
      status = false;
      break;
    }
  }

  fclose (outfile);
  return status;
}



// Add this delegate to our list during static initialization
apIAP_installer apIAP_installer::installer;
apIAP_installer::apIAP_installer ()
{
  apImageIODelegateList::gOnly().setDelegate ("iap", &apIAP::gOnly());
}
