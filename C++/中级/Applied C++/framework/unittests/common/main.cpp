// main.cpp
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
// Unit test for common.h objects

#include "geometry.h"
#include "unitTest.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



UTFUNC(apPoint)
{
  setDescription ("apPoint tests");

  apPoint p0;
  VERIFY (p0.x() == 0);
  VERIFY (p0.y() == 0);

  apPoint p1 (2,3);
  VERIFY (p1.x() == 2);
  VERIFY (p1.y() == 3);

  apPoint p2 = p1;
  VERIFY (p2.x() == 2);
  VERIFY (p2.y() == 3);
  VERIFY (p1 == p2);

  std::pair<int, int> pair = p2.point ();
  VERIFY (pair.first == 2);
  VERIFY (pair.second == 3);
}



UTFUNC(apRect)
{
  setDescription ("apRect tests");

  apRect r0;
  VERIFY (r0.width() == 0);
  VERIFY (r0.height() == 0);
  VERIFY (r0.isNull ());

  apPoint p1 (1,2);
  apPoint p2 (3,5);

  // These 3 should be identical
  apRect r1 (p1, 2, 3);
  apRect r2 (p1, p2);
  apRect r3 (1, 2, 2, 3);
  VERIFY (r1 == r2);
  VERIFY (r1 == r3);
  VERIFY (r2 == r3);

  VERIFY (!r1.isNull ());
  VERIFY (r1.width() == 2);
  VERIFY (r1.height() == 3);
  VERIFY (r1.ul() == p1);
  VERIFY (r1.lr() == p2);

  VERIFY (r1.within (p1));
  VERIFY (!r1.within (p2));

  // Try all the points in the rectangle
  VERIFY (r1.within (apPoint (1,2)));
  VERIFY (r1.within (apPoint (1,3)));
  VERIFY (r1.within (apPoint (1,4)));
  VERIFY (r1.within (apPoint (2,2)));
  VERIFY (r1.within (apPoint (2,3)));
  VERIFY (r1.within (apPoint (2,4)));

  // Try some outside
  VERIFY (!r1.within (apPoint (0,2)));
  VERIFY (!r1.within (apPoint (1,1)));
  VERIFY (!r1.within (apPoint (2,1)));
  VERIFY (!r1.within (apPoint (3,2)));
  VERIFY (!r1.within (apPoint (3,4)));
  VERIFY (!r1.within (apPoint (2,5)));
  VERIFY (!r1.within (apPoint (1,5)));
  VERIFY (!r1.within (apPoint (0,4)));

  // Intersection
  apRect big (0, 0, 100, 200);
  apRect small1 (-1, -2, 2, 3);
  apRect small2 (90, -1, 20, 30);
  apRect small3 (90, 190, 20, 30);
  apRect small4 (-1, 190, 10, 20);

  // Partial overlap
  apRect int1 = big.intersect (small1);
  apRect int2 = big.intersect (small2);
  apRect int3 = big.intersect (small3);
  apRect int4 = big.intersect (small4);
  VERIFY (int1 == apRect (0, 0, 1, 1));
  VERIFY (int2 == apRect (90, 0, 10, 29));
  VERIFY (int3 == apRect (90, 190, 10, 10));
  VERIFY (int4 == apRect (0, 190, 9, 10));

  // Complete overlap
  apRect small5 (90, 100, 10, 20);
  apRect int5 = big.intersect (small5);
  VERIFY (int5 == small5);

  // No overlap
  apRect small6 (100, 200, 1, 1);
  apRect int6 = big.intersect (small6);
  VERIFY (int6.isNull ());
}




// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

