#ifndef _iap_h_
#define _iap_h_

// iap.h
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


#include "delegates/io.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345






// ***********
// *         *
// *  apIAP  *
// *         *
// ***********
//
// IAP storage delegate. Being our own file format we will keep it
// simple, and maintain all the necessary information


class apIAP : public apImageIOBase
{
public:

  static apIAP& gOnly ();

  virtual apDelegateInfo info (const std::string& filename);
  // Given data from the header of an image, return information
  // about this image, or indicate that nothing is known.

  virtual apImage<apRGB> readRGB   (const std::string& filename);
  virtual apImage<Pel8>  readPel8  (const std::string& filename);

  bool write (const std::string& filename, const apRectImageStorage& pixels, const apDelegateParams& params = sNoParams);


  struct apIAPFileHeader
  {
    char signature[8];   // File signature 'apIAP   '
    long version;        // File version (ignored for now)
    long nImages;        // Number of images stored (normally 1)
  };


  struct apIAPImageHeader
  {
    long    x0;          // Coordinates of upper-left corner
    long    y0;
    long    width;       // Image width
    long    height;      // Image height
    long    channels;    // Number of channels (1, 3)
    long    type;        // Type (see eapIAPFileType below)
    long    depth;       // Bits per pixel per channel (8, 32)
    long    format;      // Format (see eapIAPFileFormat below)
  };


  enum eapIAPFileType
  {
    eMono = 0,              // Monochrome image
    eRGB  = 1,              // RGB image
  };

  enum eapIAPFileFormat
  {
    eNone = 0,              // No compression
  };


  // Default copy constructor and assignment operators ok.
private:
  static apIAP* sOnly_;

  apImage<apRGB> _readRGB  (FILE* fp, const apIAPImageHeader& imageHeader);
  apImage<Pel8>  _readPel8 (FILE* fp, const apIAPImageHeader& imageHeader);
  // Internal functions to read various image types

  apIAP ();
  ~apIAP ();
};


// This object will make sure that jpeg is added to our supported list
// during static initialization

class apIAP_installer
{
public:
  static apIAP_installer installer;
private:
  apIAP_installer ();
};


#endif // _iap_h_
