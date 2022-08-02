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
// Unit Test for apAlloc<> template class.

#include "allocTmpl.h"
#include "unitTest.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


UTFUNC(null)
{
  setDescription ("Null alloc");

  apAlloc<int> data;
  VERIFY (data.size() == 0);
  VERIFY (data.data() == apAlloc<int>::gNull().data());
  VERIFY (data.isNull());

  apAlloc<int> data2 (2);
  VERIFY (!data2.isNull());
}


UTFUNC(simple)
{
  setDescription ("Simple test of accessors");

  int i;
  apAlloc<int> data (10);

  VERIFY (data.size() == 10);
  VERIFY (data.ref() == 1);

  const apAlloc<int> data2 = data;
  for (i=0; i<data.size(); i++) {
    VERIFY (data[i] == data2[i]);
  }
}

UTFUNC(alignment)
{
  setDescription ("Memory alignment");

  apAlloc<int> data2 (10, 2);
  apAlloc<int> data4 (10, 4);
  apAlloc<int> data8 (10, 8);
  apAlloc<int> data3 (10, 1024);

  VERIFY ((reinterpret_cast<int>((const int*)data2.data()) & 1) == 0);
  VERIFY ((reinterpret_cast<int>((const int*)data4.data()) & 3) == 0);
  VERIFY ((reinterpret_cast<int>((const int*)data8.data()) & 7) == 0);
  VERIFY ((reinterpret_cast<int>((const int*)data3.data()) & 1023) == 0);
}

UTFUNC(set1)
{
  setDescription ("Set/get memory with []");

  int i;
  apAlloc<int> data (10);

  for (i=0; i<data.size(); i++)
    data[i] = i;

  for (i=0; i<data.size(); i++) {
    VERIFY(data[i] == i);
  }

  const apAlloc<int> data2 = data;
  for (i=0; i<data2.size(); i++) {
    VERIFY(data2[i] == i);
  }

}

UTFUNC(set2)
{
  setDescription ("Set/get memory with *");

  int i;
  apAlloc<int> data (10);

  int* p1 = data.data();
  for (i=0; i<data.size(); i++)
    *p1++ = i;

  p1 = data.data();
  for (i=0; i<data.size(); i++)
    VERIFY(*p1++ == i);

  const apAlloc<int> data2 = data;
  const int* p2 = data2.data ();
  for (i=0; i<data2.size(); i++)
    VERIFY(*p2++ == i);
}


UTFUNC(assign)
{
  setDescription ("assign");

  int i;
  apAlloc<int> data (10);

  for (i=0; i<data.size(); i++)
    data[i] = i;

  // Verify that no pixels are copied
  apAlloc<int> data2 = data;
  VERIFY(data2.data() == data.data());
  for (i=0; i<data.size(); i++) {
    VERIFY(data[i] == i);
    VERIFY(data2[i] == i);
  }
}



UTFUNC(duplicate)
{
  setDescription ("Test duplicate() explicity");

  int i;
  apAlloc<int> data (10, true);
  for (i=0; i<data.size(); i++)
    data[i] = i;
  VERIFY (data.ref() == 1);

  const int* p1 = data.data();
  data.duplicate ();
  VERIFY (p1 == data.data()); // nop if only 1 reference count

  // Create a second reference
  apAlloc<int> data2 = data;
  VERIFY (data.ref() == 2);
  VERIFY (data.data() == data2.data());

  // Explicitly duplicate the data
  data2.duplicate ();
  VERIFY (data.ref() == 1);
  VERIFY (data2.ref() == 1);
  VERIFY (data.data() != data2.data());
  VERIFY (p1 == data.data());

  for (i=0; i<data.size(); i++) {
    VERIFY (data[i] == i);
    VERIFY (data2[i] == i);
  }
}


UTFUNC(largeAlloc)
{
  setDescription ("1000 large allocations");

  int i;

  apAlloc<char> image (1);
  for (i=0; i<1000; i++) {
    image = apAlloc<char> (1024*1024);
    VERIFY (image.ref() == 1);
  }
}


UTFUNC(exception)
{
  setDescription ("Exceptions");

  int i;
  apAlloc<int> data (10);

  // This should generate 2 exceptions
  int caught = 0;
  int sum = 0;
  int sz = data.size();
  for (i=-1; i<sz + 1; i++) {
    try {
      sum += data[i];
    }
    catch (const std::range_error&) {
      caught++;
    }
  }


  VERIFY (caught == 2);
}



// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

