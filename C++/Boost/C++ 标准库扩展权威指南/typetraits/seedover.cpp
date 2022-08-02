#include <iostream>
#include <typeinfo>
#include <random>
using std::cout;

template <class Ty>
void seed_integral(Ty val)
  { // seed with an integral type
  cout << "Called integral version of seed,"
       << " with argument type "
       << typeid(Ty).name() << '\n';
  }

template <class Ty>
void seed_object(Ty val)
  { // seed with a nonintegral type
  cout << "Called nonintegral version of seed,"
       << " with argument type "
       << typeid(Ty).name() << '\n';
  }

    // dispatch to seed_integral for integral types
void seed(char val) { seed_integral(val); }
void seed(unsigned char val) { seed_integral(val); }
void seed(signed char val) { seed_integral(val); }
void seed(short val) { seed_integral(val); }
void seed(unsigned short val) { seed_integral(val); }
void seed(int val) { seed_integral(val); }
void seed(unsigned int val) { seed_integral(val); }
void seed(long val) { seed_integral(val); }
void seed(unsigned long val) { seed_integral(val); }

    // dispatch to seed_object for nonintegral types
template <class Ty>
void seed(Ty val) { seed_object(val); }

int main()
  { // call seed with several argument types
  seed(1);
  seed('a');
  seed(std::tr1::mt19937());
  return 0;
  }