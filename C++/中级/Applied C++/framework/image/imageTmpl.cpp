// imageTmpl.cpp
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
// Image template class


#include "image/imageTmpl.h"
#include "image/imageFuncs.h"



// *************************
// *                       *
// *  Specialization: set  *
// *                       *
// *************************
//

template<> void set (apImage<Pel8>& s, const Pel8& value)
{
  s.lockImage ();

  apImage<Pel8>::row_iterator i;
  long w = s.width ();
  Pel8* p;
  for (i=s.row_begin(); i != s.row_end(); i++) {
    p = i->p;
    memset (p, value, w);
  }

  s.unlockImage ();
}


template<> void set (apImage<Pel32s>& s, const Pel32s& value)
{
  s.lockImage ();

  if (s.height() < 1)
    return;

  apImage<Pel32s>::row_iterator i;
  long w = s.width ();
  Pel32s* p;

  // Initialize the first line
  i = s.row_begin();
  Pel32s* p0 = i->p;
  p = p0;
  for (int x=0; x<w; x++)
    *p++ = value;

  long bytes = w * sizeof (Pel32s);
  for (; i != s.row_end(); i++) {
    p = i->p;
    memcpy (p, p0, bytes);
  }

  s.unlockImage ();
}


template<> void set (apImage<apRGB>& s, const apRGB& value)
{
  s.lockImage ();

  if (s.height() < 1)
    return;

  apImage<apRGB>::row_iterator i;
  long w = s.width ();
  apRGB* p;

  // Initialize the first line
  i = s.row_begin();
  apRGB* p0 = i->p;
  p = p0;
  for (int x=0; x<w; x++)
    *p++ = value;

  long bytes = w * sizeof (apRGB);
  for (; i != s.row_end(); i++) {
    p = i->p;
    memcpy (p, p0, bytes);
  }

  s.unlockImage ();
}
