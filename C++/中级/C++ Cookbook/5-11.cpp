#include "constrained_value.hpp"

typedef ConstrainedValue< RangedIntPolicy<1582, 4000> > GregYear;
typedef ConstrainedValue< RangedIntPolicy<1, 12> > GregMonth;
typedef ConstrainedValue< RangedIntPolicy<1, 31> > GregDayOfMonth;

using namespace std;

void gregOutputDate(GregDayOfMonth d, GregMonth m, GregYear y) {
  cout << m << "/" << d << "/" << y << endl;
}

int main( ) {
  try {
    gregOutputDate(14, 7, 2005);
  }
  catch(...) {
    cerr << "whoops, shouldn't be here" << endl;
  }
  try {
    gregOutputDate(1, 5, 1148);
    cerr << "whoops, shouldn't be here" << endl;
  }
  catch(...) {
    cerr << "are you sure you want to be using a Gregorian Calendar?" << endl;
  }
}
