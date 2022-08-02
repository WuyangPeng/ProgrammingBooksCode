#ifndef _imageTools_h_
#define _imageTools_h_

// imageTools.h
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
// Tools for writing generic and specific image processing functions


// Disable the warning regarding long symbol names caused by templates
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include "image/imageTypes.h"
#include "image/imageTmpl.h"

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *********************************
// *                               *
// *  Image Intersection Routines  *
// *                               *
// *********************************
//
// Image proceessing routines need to operate on intersected regions between source
// and destination images. These routines handle the calculations

struct apIntersectRects
{
  apRect src;   // Intersection region for source image(s)
  apRect dst;   // Intersection region for dest image(s)
};


apIntersectRects intersect (const apRect& src, const apRect& dst);
apIntersectRects intersect (const apRect& src, unsigned int xKernelSize, unsigned int yKernelSize, const apRect& dst);
apIntersectRects intersect (const apRect& src1, const apRect& src2, const apRect& dst);
// Generic intersection routines. The kernel size must be odd.



// *******************
// *                 *
// *  apFunction_s1  *
// *                 *
// *******************
//
// Function object to handle image functions that look like
//   void function (apImage& src)
//
//
// This may seem like a trivial use of this functionality, but it allows
// the object to validate and lock the image, before an operation is
// applied. This means all image processing routines that use this class
// can ignore these issues and only deal with the image processing.
//
// The object can be used in one of two ways.
//   1. You can derive an object from the base class and specify
//      your own process() method to run on all the pixels
//   2. You can specify a function pointer to the constructor which
//      is called once the destination region is determined.

template<class T1, class S1=apImageStorage<T1> >
class apFunction_s1
{
public:
  apFunction_s1 () : function_ (0) {}
  // Use this ctor when you override process() yourself

  typedef void(*Function) (apImage<T1,S1>& src1);
  apFunction_s1 (Function f) : function_ (f) {}
  // Use this ctor when you specify your process function.

  virtual ~apFunction_s1 () {};

  void run (apImage<T1,S1>& src1) { execute (src1);}
  // Executes the image processing function

protected:
  Function function_;

  virtual void execute (apImage<T1,S1>& src1)
  {
    if (src1.isNull())
      return;

    apImageLocker<T1,S1> srcLocking (src1); // exception-safe locking

    // Run the image processing routine. We need to worry
    // about exceptions because we can be calling user written code
    try {
      process (src1);
    }
    catch (...) {
      // Add any recovery code here.
      throw;
    }

  }

  virtual void process (apImage<T1,S1>& src1)
  {
    if (function_)
      function_ (src1);
  }
};



// *********************
// *                   *
// *  apFunction_s1d1  *
// *                   *
// *********************
//
// Function object to handle image functions that look like
//   void function (const apImage& src, apImage& dst)
//
//
// The function is written this way so a destination can be specified, rather
// than allocated when the function executes. If a destination is specified,
// an intersection is performed to determine exactly what pixels will be
// processed.
//
// The object can be used in one of two ways.
//   1. You can derive an object from the base class and specify
//      your own process() method to run on all the pixels
//   2. You can specify a function pointer to the constructor which
//      is called once the destination region is determined.

template<class R, class T1, class T2,
         class S1=apImageStorage<T1>, class S2=apImageStorage<T2> >
class apFunction_s1d1
{
public:
  apFunction_s1d1 () : function_ (0) {}  // Override process() if you are using this

  typedef void(*Function) (const R&, const apImage<T1,S1>& src1, apImage<T2,S2>& dst1);
  apFunction_s1d1 (Function f) : function_ (f) {}

  virtual ~apFunction_s1d1 () {};

  void run (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  { return execute (src1, dst1);}
  // Executes the image processing function

protected:
  Function       function_; // Our process function, if any
  apImage<T1,S1> roi1_;     // roi of src1 image
  apImage<T2,S2> roi2_;     // roi of dst1 image

  virtual apIntersectRects intersection (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  { return intersect (src1.boundary(), dst1.boundary());}

  virtual void execute (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  {
    // If a null image is passed, return a null image
    if (src1.isNull()) {
      dst1 = dst1.sNull;
      return;
    }

    // Exception-safe locking.
    apImageLocker<T1,S1> srcLocking (src1);

    // Create the destination if it was not specified. Create an
    // output image with the same alignment as the input.
    if (dst1.isNull())
      createDestination (src1, dst1);

    // Lock destination after it is created (if necessary)
    apImageLocker<T2,S2> dstLocking (dst1);

    // Compute the overlap between the images
    apIntersectRects overlap = intersection (src1, dst1);

    // Return a null image if there is no overlap
    if (overlap.dst.isNull()) {
      dstLocking.unlock(); // We must unlock the object before assignment
      dst1 = dst1.sNull;
      return;
    }

    // Work only within the overlap area
    roi1_ = src1;
    roi2_ = dst1;
    roi1_.window (overlap.src);
    roi2_.window (overlap.dst);

    // Run the image processing routine.
    try {
      process ();
    }
    catch (...) {
      // Add any recovery code here.
      throw;
    }
  }
  // Execute the image processing function on the indicated images

  virtual void createDestination (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  {
    // Images are already locked as required.
    dst1 = apImage<T2,S2> (src1.boundary(), src1.alignment());
  }
  // Create our destination. Derived objects may want to change this

  virtual void process ()
  {
    R placeholder;
    if (function_)
      function_ (placeholder, roi1_, roi2_);
  }
};



// *****************************
// *                           *
// *  apFunction_s1d1Convolve  *
// *                           *
// *****************************
//
// Function object to handle image functions that look like
//   void function (const apImage& src, const char* kernel, unsigned int size, int divisor, apImage& dst)
//
//
// The function is written this way so a destination can be specified, rather
// than allocated when the function executes. If a destination is specified,
// an intersection is performed to determine exactly what pixels will be
// processed.
//
// The object can be used in one of two ways.
//   1. You can derive an object from the base class and specify
//      your own process() method to run on all the pixels
//   2. You can specify a function pointer to the constructor which
//      is called once the destination region is determined.

template<class R, class T1, class T2,
         class S1=apImageStorage<T1>, class S2=apImageStorage<T2> >
class apFunction_s1d1Convolve : public apFunction_s1d1<R,T1,T2,S1,S2>
{
public:
  apFunction_s1d1Convolve () : function_ (0) {}
  // Use this ctor when you override process() yourself

  typedef void(*Function) (const R&, const apImage<T1,S1>& src1,
                           const char* kernel, unsigned int size, int divisor,
                           apImage<T2,S2>& dst1);
  apFunction_s1d1Convolve (Function f) : function_ (f) {}
  // Use this ctor when you specify your process function.

  virtual ~apFunction_s1d1Convolve () {};

  void run (const apImage<T1,S1>& src1, 
            const char* kernel, unsigned int size, int divisor,
            apImage<T2,S2>& dst1)
  {
    kernel_  = kernel;
    size_    = size;
    divisor_ = divisor;

    execute (src1, dst1);
  }
  // Executes the image processing function

protected:
  Function     function_; // Our process function, if any
  const char*  kernel_;   // Pointer to filter kernel (square)
  unsigned int size_;     // Kernel size
  int          divisor_;  // Divisor to apply after filter

  virtual apIntersectRects intersection (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  { return intersect (src1.boundary(), size_, size_, dst1.boundary());}

  virtual void createDestination (const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
  {
    // Images are already locked as required.

    // Our destination size is smaller than the source
    int expansion = (size_-1) / 2;
    apRect region = src1.boundary ();
    region.expand (-expansion, -expansion);

    dst1 = apImage<T2,S2> (region, src1.alignment());
  }
  // Create our destination. 

  virtual void process ()
  {
    R placeholder;
    if (function_)
      function_ (placeholder, this->roi1_, kernel_, size_, divisor_, this->roi2_);
  }
};




// ***********************
// *                     *
// *  apFunction_s1s2d1  *
// *                     *
// ***********************
//
// Function object to handle image functions that look like
//   void function (const apImage& src1, const apImage& src2, apImage& dst)
//
//
// The function is written this way so a destination can be specified, rather
// than allocated when the function executes. If a destination is specified,
// an intersection is performed to determine exactly what pixels will be
// processed.
//
// The object can be used in one of two ways.
//   1. You can derive an object from the base class and specify
//      your own process() method to run on all the pixels
//   2. You can specify a function pointer to the constructor which
//      is called once the destination region is determined.

template<class R, class T1, class T2, class T3,
         class S1=apImageStorage<T1>, class S2=apImageStorage<T2>, class S3=apImageStorage<T3> >
class apFunction_s1s2d1
{
public:
  apFunction_s1s2d1 () : function_ (0) {}
  // Use this ctor when you override process() yourself

  typedef void(*Function) (const R&, const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1);
  apFunction_s1s2d1 (Function f) : function_ (f) {}
  // Use this ctor when you specify your process function.

  virtual ~apFunction_s1s2d1 () {};

  void run (const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1)
  { return execute (src1, src2, dst1);}
  // Executes the image processing function

protected:
  Function          function_; // Our process function, if any
  apImage<T1,S1> roi1_;     // roi of src1 image
  apImage<T2,S2> roi2_;     // roi of src2 image
  apImage<T3,S3> roi3_;     // roi of dst1 image

  virtual apIntersectRects intersection (const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1)
  { return intersect (src1.boundary(), src2.boundary(), dst1.boundary());}

  virtual void execute (const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1)
  {
    // Exception-safe locking.
    apImageLocker<T1,S1> src1Locking (src1);
    apImageLocker<T2,S2> src2Locking (src2);

    apRect srcOverlap = src1.boundary ();
    srcOverlap = srcOverlap.intersect (src2.boundary ());

    // If a null image is passed, return a null image
    if (srcOverlap.isNull()) {
      dst1 = dst1.sNull;
      return;
    }

    // Create the destination if it was not specified. Create an
    // output image with the same alignment as the overlap input.
    if (dst1.isNull()) {
      dst1 = apImage<T2,S2> (srcOverlap, src1.alignment());
    }

    // Compute the overlap between the images
    apIntersectRects overlap = intersection (src1, src2, dst1);

    // Return a null image if there is no overlap
    if (overlap.dst.isNull()) {
      dst1 = dst1.sNull;
      return;
    }

    // Lock destination after it is created (if necessary)
    apImageLocker<T3,S3> dstLocking  (dst1);


    // Work only within the overlap area
    roi1_ = src1;
    roi2_ = src2;
    roi3_ = dst1;
    roi1_.window (overlap.src);
    roi2_.window (overlap.src);
    roi3_.window (overlap.dst);

    // Run the image processing routine.
    try {
      process ();
    }
    catch (...) {
      // Add any recovery code here.
      throw;
    }
  }
  // Execute the image processing function on the indicated images

  virtual void process ()
  {
    R placeholder;
    if (function_)
      function_ (placeholder, roi1_, roi2_, roi3_);
  }
};




#endif // _imageTools_h_
