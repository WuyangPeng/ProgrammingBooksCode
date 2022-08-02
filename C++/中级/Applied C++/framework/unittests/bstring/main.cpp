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
// Unit Test for bstring class

#include "bstring.h"
#include "unitTest.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



UTFUNC(ctor)
{
  setDescription ("Constructor and simple accessor tests");

  apBString bstr1;
  VERIFY (bstr1.size() == 0);

  std::string s = "string";
  bstr1 << (Pel8) 1 << (Pel16) 2 << (Pel32s) 3 << (float) 4.0 << (double) 5.0 << s;
  VERIFY (bstr1.size() == 35);
}


UTFUNC(Pel8)
{
  setDescription ("Pel8 tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (Pel8) 123;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == 123);
  VERIFY (w == 123);
  VERIFY (l == 123);
  VERIFY (ls== 123);
  VERIFY (f == 123);
  VERIFY (d == 123);
  VERIFY (s.compare ("123") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(Pel16)
{
  setDescription ("Pel16 tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (Pel16) 12345;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == (Pel8)12345); // Any warning issued here is ok
  VERIFY (w == 12345);
  VERIFY (l == 12345);
  VERIFY (ls== 12345);
  VERIFY (f == 12345);
  VERIFY (d == 12345);
  VERIFY (s.compare ("12345") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(Pel32s)
{
  setDescription ("Pel32s tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (Pel32s) 123456;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == (Pel8)123456); // Any warning issued here is ok
  VERIFY (w == (Pel16)123456); // Any warning issued here is ok
  VERIFY (l == 123456);
  VERIFY (ls== 123456);
  VERIFY (f == 123456);
  VERIFY (d == 123456);
  VERIFY (s.compare ("123456") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(int)
{
  setDescription ("int tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (int) -123456;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == (Pel8)-123456); // Any warning issued here is ok
  VERIFY (w == (Pel16)-123456); // Any warning issued here is ok
  VERIFY (l == (Pel32s)-123456);
  VERIFY (ls== -123456);
  VERIFY (f == -123456);
  VERIFY (d == -123456);
  VERIFY (s.compare ("-123456") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(float)
{
  setDescription ("float tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (float) 1.999;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == 1);
  VERIFY (w == 1);
  VERIFY (l == 1);
  VERIFY (ls== 1);
  VERIFYFLOAT (f, 1.999);
  VERIFYFLOAT (d, 1.999);
  VERIFY (s.compare ("1.999000") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(double)
{
  setDescription ("double tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << (double) 1.99999;

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == 1);
  VERIFY (w == 1);
  VERIFY (l == 1);
  VERIFY (ls== 1);
  VERIFYFLOAT (f, 1.99999);
  VERIFYFLOAT (d, 1.99999);
  VERIFY (s.compare ("1.999990") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(string)
{
  setDescription ("string tests");

  Pel8 b;
  Pel16 w;
  Pel32s l;
  int ls;
  float f;
  double d;
  std::string s;

  apBString bstr;
  bstr << "123.456";

  bstr >> b;  bstr.rewind ();
  bstr >> w;  bstr.rewind ();
  bstr >> l;  bstr.rewind ();
  bstr >> ls; bstr.rewind ();
  bstr >> f;  bstr.rewind ();
  bstr >> d;  bstr.rewind ();
  bstr >> s;  bstr.rewind ();

  VERIFY (b == 123);
  VERIFY (w == 123);
  VERIFY (l == 123);
  VERIFY (ls== 123);
  VERIFYFLOAT (f, 123.456);
  VERIFYFLOAT (d, 123.456);
  VERIFY (s.compare ("123.456") == 0);

  bstr >> b;
  VERIFY (bstr.eof());
}


UTFUNC(eof)
{
  setDescription ("eof tests");

  apBString bstr;
  VERIFY (bstr.eof());

  std::string s;

  bstr << "1" << "2";
  VERIFY (!bstr.eof());

  bstr >> s;
  VERIFY (s.compare("1") == 0);
  VERIFY (!bstr.eof());

  bstr >> s;
  VERIFY (s.compare("2") == 0);
  VERIFY (bstr.eof());

  bstr >> s;
  VERIFY (s.empty());
  VERIFY (bstr.eof());

  bstr.rewind ();
  VERIFY (!bstr.eof());
}


UTFUNC(data)
{
  setDescription ("data tests");

  int i;
  int s = 10;
  char data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  apBString bstr;
  bstr.append (data, sizeof (data));
  bstr << (Pel8) 1;
  bstr.append (data, sizeof (data));
  bstr << (Pel8) 2;

  Pel8 b;
  const void* vp;
  unsigned int size;
  bstr.fetch (vp, size);
  bstr >> b;
  VERIFY (b == 1);
  VERIFY (!bstr.eof());
  const char* p = reinterpret_cast<const char*>(vp);

  VERIFY (s == size);
  for (i=0; i<s; i++)
    VERIFY (p[i] == data[i]);

  bstr.fetch (vp, size);
  bstr >> b;
  VERIFY (b == 2);
  VERIFY (bstr.eof());
  p = reinterpret_cast<const char*>(vp);

  VERIFY (s == size);
  for (i=0; i<s; i++)
    VERIFY (p[i] == data[i]);
}


UTFUNC(bstr)
{
  setDescription ("bstr tests");

  apBString bstr1;
  std::string s = "string";
  bstr1 << (Pel8) 1 << (Pel16) 2 << (Pel32s) 3 << (float) 4.0 << (double) 5.0 << s;

  apBString bstr;
  bstr << bstr1 << (Pel8) 1 << bstr1 << (Pel8) 2;

  Pel8 b1, b2;
  apBString bstr2, bstr3;
  bstr >> bstr2 >> b1 >> bstr3 >> b2;
  VERIFY (b1 == 1);
  VERIFY (b2 == 2);
  VERIFY (bstr.eof());

  Pel8 b;
  Pel16 w;
  Pel32s l;
  float f;
  double d;

  bstr2 >> b >> w >> l >> f >> d >> s;
  VERIFY (bstr2.eof());
  VERIFY (b == 1);
  VERIFY (w == 2);
  VERIFY (l == 3);
  VERIFY (f == 4);
  VERIFY (d == 5);
  VERIFY (s.compare ("string") == 0);

  bstr3 >> b >> w >> l >> f >> d >> s;
  VERIFY (bstr2.eof());
  VERIFY (b == 1);
  VERIFY (w == 2);
  VERIFY (l == 3);
  VERIFY (f == 4);
  VERIFY (d == 5);
  VERIFY (s.compare ("string") == 0);
}


UTFUNC(dump)
{
  setDescription ("dump tests");

  char data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  apBString bstr;
  std::string s = "string";
  bstr << (Pel8) 1 << (Pel16) 2 << (Pel32s) 3 << (int) -3 << (float) 4.0 << (double) 5.0 << s;
  bstr << bstr;
  bstr.append (data, sizeof (data));

  std::cout << bstr.dump().c_str() << std::endl;

  VERIFY (true);  // Always pass this test
}


UTFUNC(point)
{
  setDescription ("point tests");

  apBString bstr;

  apPoint p1 (-1000, -2000);
  apPoint p2 (-3000, -4000);
  bstr << p1 << p2;

  apPoint p1a, p2a;
  bstr >> p1a >> p2a;
  VERIFY (p1 == p1a);
  VERIFY (p2 == p2a);
}

UTFUNC(rect)
{
  setDescription ("rect tests");

  apBString bstr;

  apRect  r1 (-1000, -2000, 10, 20);
  apRect  r2 (-3000, -4000, 30, 40);
  bstr << r1 << r2;

  apRect r1a, r2a;
  bstr >> r1a >> r2a;
  VERIFY (r1 == r1a);
  VERIFY (r2 == r2a);
}


// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

