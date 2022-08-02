#include <utility>
#include <tuple>
using std::tr1::tuple; using std::pair;

class C {
public:
  C() : val(0) {}
  C(int i) : val(i) {}
private:
  int val;
};

tuple<> t0;                 // default constructor
tuple<int> t1;              // default constructor; element
                            // not initialized
tuple<int> t2(3);           // element initialized to 3
tuple<C> t3;                // element initialized to C()
tuple<C> t4(C(1));          // element initialized to C(1)
tuple<C, C> t5(1, 2);       // first element initialized to C(1)
                            // second element initialized to C(2)
tuple<double> t6(t2);       // element initialized to 3.0
pair<int, int> p0(3, 4);    // first element initialized to 3
                            // second element initialized to 4
tuple<C, C> t7(p0);         // first element initialized to C(3)
                            // second element initialized to C(4)