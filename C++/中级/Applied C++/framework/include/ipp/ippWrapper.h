#ifndef _ippWrapper_h_
#define _ippWrapper_h_

// ippWrapper.h
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
// Intel Image Processing Primative Library Wrapper (v2.0)


#include "image/imageTmpl.h"
#include "image/imageTypes.h"
#include "image/imageFuncs1.h"


// Probably in c:/Program Files/intel/IPP/include
// (or on Linux, /opt/intel/ipp/include)
#include "ipp.h"    


// On Linux systems, this has no meaning
#ifndef WIN32
#define __stdcall
#endif



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***************
// *             *
// *  IPPTraits  *
// *             *
// ***************
//
// IPPTraits maps our image types to IPP Traits. Initially, we 
// only store the corresponding IPP type name for our image type,
// but this class is useful to store other attributes as well 
// (hence why we call it a traits class). We need specializations
// for the RGB data types since the Intel IPP library treats these
// as arrays of the underlying data type (i.e. an 8-bit RGB image
// is stored as an array of bytes).


template<class T> struct IPPTraits
{
  typedef T ipptype;  // Intel IPP  type for this apImage type
};

// apRGB specialization. Ipp treats this as a Ipp8u* array
template<> struct IPPTraits<apRGB>
{
  typedef Ipp8u ipptype;  // Intel IPP  type for this apImage type
};

// apRGB specialization. Ipp treats this as a Ipp32s* array
template<> struct IPPTraits<apRGBPel32s>
{
  typedef Ipp32s ipptype;  // Intel IPP  type for this apImage type
};



// ***********************
// *                     *
// *  IPPMaskSizeTraits  *
// *                     *
// ***********************
//
// The Intel IPP library uses a simple enumeration to define the filter
// size a function uses. By making this a parameterized type we can
// write a generic function which can handle all filter types. We do not
// provide a default definition so the compiler will catch any attempts 
// to use an unsupported filter type.
//
// Our interface code uses the size information to compute the source and
// destination images which will be processed.

template<IppiMaskSize T> struct IPPMaskSizeTraits
{
  // Empty. A specialization is necessary
};

template<> struct IPPMaskSizeTraits<ippMskSize1x3>
{
  static const int xSize = 1;
  static const int ySize = 3;
};

template<> struct IPPMaskSizeTraits<ippMskSize1x5>
{
  static const int xSize = 1;
  static const int ySize = 5;
};

template<> struct IPPMaskSizeTraits<ippMskSize3x1>
{
  static const int xSize = 3;
  static const int ySize = 1;
};

template<> struct IPPMaskSizeTraits<ippMskSize3x3>
{
  static const int xSize = 3;
  static const int ySize = 3;
};

template<> struct IPPMaskSizeTraits<ippMskSize5x1>
{
  static const int xSize = 5;
  static const int ySize = 1;
};

template<> struct IPPMaskSizeTraits<ippMskSize5x5>
{
  static const int xSize = 5;
  static const int ySize = 5;
};


// ***********
// *         *
// *  apIPP  *
// *         *
// ***********
//
// The Intel IPP library is very flexible in how image pixels are passed
// to its functions. It is not difficult to map how apImage stores pixels
// to a similar IPP does. No pixel copying is necessary (unlike the older
// Intel product, IPL). Image alignment is also an important issue but it
// can be difficult to guarantee alignment because image windowing is used
// to specify the exact source and destination regions needed.
//
// apIPP is a simple wrapper function that helps convert structures between our
// (apImage) format and Intel's (IPP) format. It supports our basic monochrome
// and RGB image data types. It is also capable of creating aligned images,
// via copying, to take advantage of higher performance from the IPP package.
// This is controled by a static variable. We have found it best to leave this
// feature disabled because of the difficulty to working with aligned images
// with filtering operations.


class apIPPException : public apException
{
public:
  apIPPException (std::string name="") 
    : apException ("apIPPException: " + name) {}
};



template<class T, class S=apImageStorage<T> >
class apIPP
{
public:
  typedef typename IPPTraits<T>::ipptype ipptype;

  enum eType {
    eIPP_Unknown = 0,       // Unknown or uninitialized type
    eIPP_8u_C1   = 1,       // 8-bit monochrome
    eIPP_32s_C1  = 2,       // 32-bit (signed) monochrome
    eIPP_8u_C3   = 3,       // 8-bit RGB
    eIPP_32s_C3  = 4,       // 32-bit (signed) RGB
  };

  static bool isAligned () { return isAligned_;}
  static void isAligned (bool state) { isAligned_ = state;}
  // Enable image alignment. See the comments in the code before you
  // change this. Yes, you must set this value for each image type.

  apIPP (apImage<T,S>& image);
  ~apIPP () { cleanup ();}

  apIPP (const apIPP& src);
  apIPP& operator= (const apIPP& src);
  // We need our own copy constructor and assignment operator.


  ipptype* base       ()       { return reinterpret_cast<ipptype*>(align_.base());}
  const ipptype* base () const { return reinterpret_cast<ipptype*>(align_.base());}
  // Base address of image data, in the proper pointer type

  IppiSize imageSize () const
  { IppiSize sz; sz.width = align_.width(); sz.height = align_.height(); return sz;}
  // IPP image size (suitable for use in IPP routines)

  int pitch () { return align_.row_begin()->bytes;}
  // Pitch (spacing, in bytes, between rows)

  void syncImage ();
  // Called after image processing to sync up the image with the
  // aligned image, if necessary

protected:
  void createIPPImage ();
  // Convert the apImage<> image, if necessary, to a form for IPP

  void cleanup ();
  // Cleanup any memory allocated to the intel image object

  static bool isAligned_;   // true if images are aligned (8-byte) automatically 

  apImage<T,S>& image_;   // Our storage object (A reference)
  apImage<T,S>  align_;   // Our aligned image
  eType           type_;    // Image type
};


// By default, no automatic alignment is performed on the IPP images.
// You should not enable this unless you really understand what is happenning.
template <class T, class S>
bool apIPP<T,S>::isAligned_ = false;


template <class T, class S>
apIPP<T,S>::apIPP (apImage<T,S>& image) 
: image_ (image), type_ (eIPP_Unknown)
{ 
  createIPPImage ();
}


template <class T, class S>
apIPP<T,S>::apIPP (const apIPP& src)
{
  image_ = src.image_;
  align_ = src.align_;
  type_  = src.type_;
}

template <class T, class S>
apIPP<T,S>& apIPP<T,S>::operator= (const apIPP& src)
{
  if (this == &src) return *this;

  image_ = src.image_;
  align_ = src.align_;
  type_  = src.type_;
  return *this;
}


template <class T, class S>
void apIPP<T,S>::cleanup ()
{
  // Not needed for apIPP
}


template <class T, class S>
void apIPP<T,S>::syncImage ()
{
  // If our aligned image is different than our original, copy the
  // aligned pixels back to our image.
  if (align_.base() != image_.base())
    copy (align_, image_);
}


template <class T, class S>
void apIPP<T,S>::createIPPImage ()
{
  // Cleanup any existing Intel object
  cleanup ();

  // Image alignment is not necessary, and can actually be dangerous.
  // We use image windows which breaks most image alignment anyway. We
  // still keep an align_ member in case alignment ever becomes useful.
  // Our static isAligned_ controls this feature in case it is every
  // needed. This is a good example of planning for future growth in 
  // the code. There are issues when you turn alignment on because IPP
  // assumes access to pixels outside the image in order to compute
  // neighborhood filters. Make sure you understand what is going on if
  // you decide to enable this.
  if (isAligned_)
    align_ = image_.align (apRectImageStorage::eQuadWordAlign);
  else
    align_ = image_;

  // Figure out our datatype
  if (typeid(T) == typeid(Pel8)) {
    type_ = eIPP_8u_C1;
  }
  else if (typeid(T) == typeid(Pel32s)) {
    type_ = eIPP_32s_C1;
  }
  else if (typeid(T) == typeid(apRGB)) {
    type_ = eIPP_8u_C3;
  }
  else if (typeid(T) == typeid(apRGBPel32s)) {
    type_ = eIPP_32s_C3;
  }
  else {
    throw apIPPException ("Unsupported image type");
  }
}




// ***************
// *             *
// *  IPPFilter  *
// *             *
// ***************
//
// IPPFilter defines the base class for fixed filters. 
// All the neighborhood filters in the IPP library share a common form, but
// are implemented as discrete functions. IPPFilter is the base class for
// all neighborhood filters. This object is similar to our filter object
// (apFunction_s1d1Convolve) and computes the overlap region between source
// and destination images. The second template argument specifies the filter
// size (i.e. 3x3, 5x5). This was made a template parameter because the filter
// size is used both by the IPP function and also during the source/destination
// intersection step.
//
// Derived classes specify the IPP filter function to use. Doing so gives us
// class names which describe the operation while reusing as much code as
// possible.
//
// The base class defines the function call (i.e. operator()) operator to 
// manipulate the images, call the underlying IPP function, and cleaning up.
//
// Unlike apImage<> functions, these functions support in-place operations
// (i.e. the source and destination are identical). The source image is
// duplicated for the operation.
//
// Many IPP functions require slightly different paramters. If you want to support
// such function you will need to duplicate this object and change the 
// fixedFilterFunction typedef. You should also look at defining a new base class
// with only generic (i.e. no prototype dependencies) functions.


template<typename T, IppiMaskSize S> class IPPFilter
{
public:
  typedef typename IPPTraits<T>::ipptype ipptype;
  typedef IppStatus  (__stdcall *fixedFilterFunction)(const ipptype* /*pSrc*/, 
                                           int /*srcStep*/, 
                                           ipptype* /*pDst*/, 
                                           int /*dstStep*/, 
                                           IppiSize /*dstRoiSize*/,
                                           IppiMaskSize /*mask*/);


  IppStatus operator() (const apImage<T>& src, apImage<T>& dst)
  {
    if (src.isNull())
      return ippStsNoErr;

    apImageLocker<T> srcLocking (src);

    apImage<T> source = src;
    apImage<T> dest   = dst;

    eMethod method = eRegular;

    // If destination is specified, use it in computing the overlap.
    if (dest.isNull()) {
     // Our destination size is smaller than the source, but aligned
      int size = IPPMaskSizeTraits<S>::xSize;
      int expansion = (size-1) / 2;
      apRect region = src.boundary ();
      region.expand (-expansion, -expansion);

      dst = apImage<T> (region, src.alignment());
      dest = dst;
      method = eCreatedDest;
    }
    else if (src.isIdentical (dst)) {
      // In-place operation
      dest = duplicate (source, apRectImageStorage::e16ByteAlign);
      method = eInPlace;
    }
    else if (source.boundary() != dest.boundary()) {
      // Restrict output to the intersection of the images
      dest.window   (src.boundary());
      source.window (dest.boundary());
      method = eWindow;
    }

    // Lock destination after it is created (if necessary)
    apImageLocker<T> dstLocking (dst);

    // Compute the overlap between the images
    apIntersectRects overlap = intersect (src.boundary(), IPPMaskSizeTraits<S>::xSize, IPPMaskSizeTraits<S>::ySize, dst.boundary());

    // Return a null image if there is no overlap
    if (overlap.dst.isNull()) {
      dstLocking.unlock ();
      dst = dst.sNull;
      return ippStsNoErr;
    }

    // Work only within the overlap area. Unlike our implementation, we must pass roi's to the IPP
    // library which indicate the destination pixels to compute. IPP assumes that the source pixels
    // surrounding this point exists. Our window() operation uses the same overlap as a result.
    apImage<T> roi1 = src;
    apImage<T> roi2 = dst;
    roi1.window (overlap.dst);  //Note: This is different from our own implementation
    roi2.window (overlap.dst);

    apIPP<T> s (roi1);
    apIPP<T> d (roi2);

    // Call the IPP function
    IppStatus status = func_ (s.base(), s.pitch(), d.base(), d.pitch(), s.imageSize(), S);

    d.syncImage ();

    // Post-processing
    switch (method) {
    case eInPlace:
      copy (dest, source);
      dst = dest;
      break;
    default:
      break;
    }

    return status;
  }

protected:
  enum eMethod { eRegular, eInPlace, eCreatedDest, eWindow};

  IPPFilter (fixedFilterFunction f) : func_ (f) {}

  fixedFilterFunction func_;
};



// ***************
// *             *
// *  Laplacian  *
// *             *
// ***************

// IPPLaplacian3x3 is a very descriptive name for users, which is why we
// derive from IPPFilter<> as opposed to adding additional template paramters.

template<typename T> class IPPLaplacian3x3 : public IPPFilter<T, ippMskSize3x3>
{
public:
  typedef typename IPPFilter<T, ippMskSize3x3>::fixedFilterFunction fixedFilterFunction;
  static IPPLaplacian3x3 filter;
protected:

  IPPLaplacian3x3 (fixedFilterFunction f) : IPPFilter<T, ippMskSize3x3> (f) {}
};


template<typename T> class IPPLaplacian5x5 : public IPPFilter<T, ippMskSize5x5>
{
public:
  typedef typename IPPFilter<T, ippMskSize5x5>::fixedFilterFunction fixedFilterFunction;
  static IPPLaplacian5x5 filter;
protected:

  IPPLaplacian5x5 (fixedFilterFunction f) : IPPFilter<T, ippMskSize5x5> (f) {}
};


IPPLaplacian3x3<Pel8>  IPPLaplacian3x3<Pel8>::filter       (ippiFilterLaplace_8u_C1R);
IPPLaplacian3x3<apRGB> IPPLaplacian3x3<apRGB>::filter      (ippiFilterLaplace_8u_C3R);

IPPLaplacian5x5<Pel8>  IPPLaplacian5x5<Pel8>::filter       (ippiFilterLaplace_8u_C1R);
IPPLaplacian5x5<apRGB> IPPLaplacian5x5<apRGB>::filter      (ippiFilterLaplace_8u_C3R);




// **************
// *            *
// *  Gaussian  *
// *            *
// **************

template<typename T> class IPPGaussian3x3 : public IPPFilter<T, ippMskSize3x3>
{
public:
  static IPPGaussian3x3 filter;
  typedef typename IPPFilter<T, ippMskSize3x3>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPGaussian3x3 (fixedFilterFunction f) : IPPFilter<T, ippMskSize3x3> (f) {}
};


template<typename T> class IPPGaussian5x5 : public IPPFilter<T, ippMskSize5x5>
{
public:
  static IPPGaussian5x5 filter;
  typedef typename IPPFilter<T, ippMskSize5x5>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPGaussian5x5 (fixedFilterFunction f) : IPPFilter<T, ippMskSize5x5> (f) {}
};


IPPGaussian3x3<Pel8>  IPPGaussian3x3<Pel8>::filter       (ippiFilterGauss_8u_C1R);
IPPGaussian3x3<apRGB> IPPGaussian3x3<apRGB>::filter      (ippiFilterGauss_8u_C3R);

IPPGaussian5x5<Pel8>  IPPGaussian5x5<Pel8>::filter       (ippiFilterGauss_8u_C1R);
IPPGaussian5x5<apRGB> IPPGaussian5x5<apRGB>::filter      (ippiFilterGauss_8u_C3R);




// ************
// *          *
// *  Hipass  *
// *          *
// ************

template<typename T> class IPPHipass3x3 : public IPPFilter<T, ippMskSize3x3>
{
public:
  static IPPHipass3x3 filter;
  typedef typename IPPFilter<T, ippMskSize3x3>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPHipass3x3 (fixedFilterFunction f) : IPPFilter<T, ippMskSize3x3> (f) {}
};


template<typename T> class IPPHipass5x5 : public IPPFilter<T, ippMskSize5x5>
{
public:
  static IPPHipass5x5 filter;
  typedef typename IPPFilter<T, ippMskSize5x5>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPHipass5x5 (fixedFilterFunction f) : IPPFilter<T, ippMskSize5x5> (f) {}
};


IPPHipass3x3<Pel8>  IPPHipass3x3<Pel8>::filter       (ippiFilterHipass_8u_C1R);
IPPHipass3x3<apRGB> IPPHipass3x3<apRGB>::filter      (ippiFilterHipass_8u_C3R);

IPPHipass5x5<Pel8>  IPPHipass5x5<Pel8>::filter       (ippiFilterHipass_8u_C1R);
IPPHipass5x5<apRGB> IPPHipass5x5<apRGB>::filter      (ippiFilterHipass_8u_C3R);



// *************
// *           *
// *  Lowpass  *
// *           *
// *************

template<typename T> class IPPLowpass3x3 : public IPPFilter<T, ippMskSize3x3>
{
public:
  static IPPLowpass3x3 filter;
  typedef typename IPPFilter<T, ippMskSize3x3>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPLowpass3x3 (fixedFilterFunction f) : IPPFilter<T, ippMskSize3x3> (f) {}
};


template<typename T> class IPPLowpass5x5 : public IPPFilter<T, ippMskSize5x5>
{
public:
  static IPPLowpass5x5 filter;
  typedef typename IPPFilter<T, ippMskSize5x5>::fixedFilterFunction fixedFilterFunction;
protected:

  IPPLowpass5x5 (fixedFilterFunction f) : IPPFilter<T, ippMskSize5x5> (f) {}
};


IPPLowpass3x3<Pel8>  IPPLowpass3x3<Pel8>::filter       (ippiFilterLowpass_8u_C1R);
IPPLowpass3x3<apRGB> IPPLowpass3x3<apRGB>::filter      (ippiFilterLowpass_8u_C3R);

IPPLowpass5x5<Pel8>  IPPLowpass5x5<Pel8>::filter       (ippiFilterLowpass_8u_C1R);
IPPLowpass5x5<apRGB> IPPLowpass5x5<apRGB>::filter      (ippiFilterLowpass_8u_C3R);




#endif // _iplWrapper_h_
