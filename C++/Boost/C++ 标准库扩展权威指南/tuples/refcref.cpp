#include <tuple>
#include <functional>           // for ref, cref
using std::tr1::make_tuple;
using std::tr1::ref; using std::tr1::cref;

void test()
    {
    int i = 17;
    int j = 3;
    make_tuple(ref(i),cref(j)); // returns tuple<int\&, const int\&>
                                // first element is reference to i
                                // second element is reference to j
    }
