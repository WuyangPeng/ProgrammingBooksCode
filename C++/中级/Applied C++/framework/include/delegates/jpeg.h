#ifndef _jpeg_h_
#define _jpeg_h_

// jpeg.h
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
// jpeg file delegate


#include "delegates/io.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ************
// *          *
// *  apJPEG  *
// *          *
// ************
//
// JPEG storage delegate

class apJPEGException : public apException
{
public:
  apJPEGException (std::string name="") 
    : apException ("apJPEGException: " + name) {}
};


class apJPEG : public apImageIOBase
{
public:
  static apJPEG& gOnly ();

  virtual apDelegateInfo info (const std::string& filename);
  // Given data from the header of an image, return information
  // about this image, or indicate that nothing is known.

  virtual apImage<apRGB> readRGB   (const std::string& filename);
  virtual apImage<Pel8>  readPel8  (const std::string& filename);

  virtual bool write (const std::string& filename, const apRectImageStorage& pixels, const apDelegateParams& params = sNoParams);

  // Default copy constructor and assignment operators ok.
private:
  static apJPEG* sOnly_;

  apJPEG ();
  ~apJPEG ();
};


// This object will make sure that jpeg is added to our supported list
// during static initialization

class apJPEG_installer
{
public:
  static apJPEG_installer installer;
private:
  apJPEG_installer ();
};


#endif // _jpeg_h_
