#include <random>
#include <sstream>
#include <iostream>
using std::stringstream; using std::cout;

template <class Eng>
void readwrite()
  { // write and read engine state
  Eng eng, eng1;
  eng();        // change state
  if (eng == eng1)
    cout << "Something's wrong\n";
  else
    cout << "Engines are not equal\n";

  stringstream str;
  str << eng;   // write state of eng
  str >> eng1;  // read state into eng1
  if (eng != eng1)
    cout << "Something's wrong\n";
  else
    cout << "Engines are equal\n";
  }

int main()
  { // demonstrate reading and writing engine states
  readwrite<std::tr1::mt19937>();
  return 0;
  }