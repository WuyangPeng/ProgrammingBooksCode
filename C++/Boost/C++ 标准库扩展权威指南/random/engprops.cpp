#include <random>
#include <iomanip>
#include <iostream>
using std::cout; using std::setw;

template <class Ty>
void show(const char *title, Ty value)
  { // show property title and value
  cout << setw(35) << title << ": " << value << '\n';
  }

unsigned trivial_seed()
  { // trivial seed generator
  return 4;
  }

template <class Eng>
void show_properties(const char *name)
  { // show properties of engine type Eng
  cout << "\nProperties of " << name << '\n';
  Eng eng;
  show("Minimum", eng.min());
  show("Maximum", eng.max());
  show("Initial value", eng());
  eng.seed();
  show("After calling seed()", eng());
  Eng eng1(3);
  show("Constructed with Eng(3)", eng1());
  eng.seed(3);
  show("After calling seed(3)", eng());
  Eng eng2(trivial_seed);
  show("Constructed with Eng(trivial_seed)", eng2());
  eng.seed(trivial_seed);
  show("After calling seed(trivial_seed)", eng());
  }

int main()
  { // show properties of a few engines
  show_properties<std::tr1::minstd_rand>("minstd_rand");
  show_properties<std::tr1::ranlux_base_01>(
    "ranlux_base_01");
  return 0;
  }