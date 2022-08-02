#ifndef _io_h_
#define _io_h_

// io.h
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
// Image I/O

//Prevents Windows from complaining about long symbol names
#ifdef WIN32
#pragma warning(disable:4786)
#endif


#include "bstring.h"
#include "image/image.h"

#include <string>
#include <map>
#include <iostream>



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *******************
// *                 *
// *  apImageIOBase  *
// *                 *
// *******************
//
// Base class for all apImage storage delegates.

struct apDelegateInfo
{
  bool         isDelegate;    // true if delegate knows this format
  apRect       boundary;      // Image boundary (if known)
  unsigned int bytesPerPixel; // Bytes per pixel (if known)
  unsigned int planes;        // Number of planes (if known) 0=mono, 3=color
  std::string format;        // Additional image format information
};
// Structure filled in by info() method


struct apDelegateParams
{
  float       quality;       // Quality parameter (depends on format)
  std::string params;        // Other parameters

  apDelegateParams (float qual=90.) : quality (qual) {}

};


class apImageIOBase
{
public:
  virtual apDelegateInfo info (const std::string& filename) = 0;
  // See if this file can be read by this delegate.

  template<class T, class S>
  void read (const std::string& filename, apImage<T,S>& image)
  {
    if (typeid(apImage<apRGB>) == typeid(image))
      image = readRGB (filename);
    else if (typeid(apImage<Pel8>) == typeid(image))
      image = readPel8 (filename);
    else
      copy (readRGB (filename), image);
  }
  // This needs run-time type identification. 
  // You can do without it, but you will wind up with an additional
  // image copy when you read an RGB, or Pel8 image.


  template<class T, class S>
  void write (const std::string& filename, apImage<T,S>& image, 
              const apDelegateParams& params = sNoParams)
  {
    if (typeid(apImage<apRGB>) == typeid(image))
      write (filename, image.storage(), params);
    else if (typeid(apImage<Pel8>) == typeid(image))
      write (filename, image.storage(), params);
    else {
      apImage<apRGB> rgb = image;
      write (filename, rgb.storage(), params);
    }
  }
  // This needs run-time type identification. Performing these
  // checks allows us to coerce out image into a popular format for
  // storage. You can do this in a specific image delegate, but
  // it works nicely here.


  virtual apImage<apRGB> readRGB   (const std::string& filename) = 0;
  virtual apImage<Pel8>  readPel8  (const std::string& filename) = 0;
  // Most file formats have limited ways that files are stored. These 
  // functions read RGB and 8-bit monochrome images.

  virtual bool write (const std::string& filename, 
                      const apRectImageStorage& pixels, 
                      const apDelegateParams& params) = 0;


  // Default copy constructor and assignment operators ok.
protected:
  apImageIOBase ();
  virtual ~apImageIOBase ();

  static apDelegateParams sNoParams;
};



// ***************************
// *                         *
// *  apImageIODelegateList  *
// *                         *
// ***************************

class apImageIODelegateList
{
public:
  static apImageIODelegateList& gOnly ();
  // Our only instance

  apImageIOBase* getDelegate (const std::string& type);
  void setDelegate (const std::string& type, apImageIOBase* object);
  // Get/set delegate information

  apImageIOBase* findDelegate (const std::string& filename);
  // Return the delegate to handle this file, or null

private:
  typedef std::map<std::string, apImageIOBase*> map;
  typedef map::iterator iterator;

  map map_;   // Our mapping of file type to a delegate to handle it

  static apImageIODelegateList* sOnly_;

  apImageIODelegateList ();
};




#endif // _io_h_
