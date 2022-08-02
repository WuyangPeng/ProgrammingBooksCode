//: C07:StreambufIterator.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// istreambuf_iterator & ostreambuf_iterator.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include "../require.h"
using namespace std;

int main() {
  ifstream in("StreambufIterator.cpp");
  assure(in, "StreambufIterator.cpp");
  // Exact representation of stream:
  istreambuf_iterator<char> isb(in), end;
  ostreambuf_iterator<char> osb(cout);
  while(isb != end)
    *osb++ = *isb++; // Copy 'in' to cout
  cout << endl;
  ifstream in2("StreambufIterator.cpp");
  // Strips white space:
  istream_iterator<char> is(in2), end2;
  ostream_iterator<char> os(cout);
  while(is != end2)
    *os++ = *is++;
  cout << endl;
} ///:~
