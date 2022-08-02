#ifndef _imageDelegate_h_
#define _imageDelegate_h_

// imageDelegate.h
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
// Image delegation object to allow optimized implementations of 
// image processing functions to be used dynamically.


// Disable the warning regarding long symbol names caused by templates
#ifdef WIN32
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif


#include "image/imageTypes.h"
#include "image/imageStorageTmpl.h"

#include <string>
#include <map>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// Generic definition of a function that takes 2 args and returns 1
template<class S1, class S2, class D1>
class apSSD
{
public:
  virtual ~apSSD () {}

  virtual bool operator() (const apImageStorage<S1>& s1, const apImageStorage<S2>& s2, apImageStorage<D1>& d1) const = 0;
};


// *********************
// *                   *
// *  apImageDelegate  *
// *                   *
// *********************

// typedef apImageStorage<T> (*functionSD)  (const apImageStorage<T>&);
// typedef apImageStorage<T> (*functionSSD) (const apImageStorage<T>&, const apImageStorage<T>&);


// 

class apImageDelegate
{
public:
  typedef void (*Function) ();

  typedef apImageStorage<Pel8>  (*FunctionS8D8)     (const apImageStorage<Pel8>&);
  typedef apImageStorage<Pel32s>(*FunctionS32D32)   (const apImageStorage<Pel32s>&);
  typedef apImageStorage<apRGB> (*FunctionSrgbDrgb) (const apImageStorage<apRGB>&);

  typedef apImageStorage<Pel8>  (*FunctionS8S8D8)   (const apImageStorage<Pel8>&,
                                                     const apImageStorage<Pel8>&);
  typedef apImageStorage<Pel32s>(*FunctionS32S32D32) (const apImageStorage<Pel32s>&,
                                                      const apImageStorage<Pel32s>&);
  typedef apImageStorage<apRGB> (*FunctionSrgbSrgbDrgb) (const apImageStorage<apRGB>&,
                                                         const apImageStorage<apRGB>&);

  typedef std::map<std::string, Function> Typemap;
  typedef std::map<std::string, Typemap>  Functionmap;

  static apImageDelegate& gOnly();


  void addDelegate (std::string name, FunctionS8D8 function);

protected:
  apImageDelegate ();

  static apImageDelegate* sOnly_;

  Typemap     typemap_;
  Functionmap functionmap_;
};

/*
class apImageFunction
{
};

class apImageFunctionS8D8 : public apImageFunction
{
public:
  typedef apImageStorage<Pel8>  (*Function)     (const apImageStorage<Pel8>&);

  static apImageFunctionS8D8& gOnly();


  void add (std::string name, apImageDelegate::FunctionS8D8 function);
  apImageDelegate::FunctionS8D8 fetch (std::string name);

private:
  apImageFunctionS8D8 ();

  static apImageFunctionS8D8* sOnly_;

  Typemap     typemap_;
  Functionmap functionmap_;
};
*/

#endif // _imageDelegate_h_
