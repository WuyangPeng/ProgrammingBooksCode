/* The following code example is taken from the book
 * "C++ Templates - The Complete Guide"
 * by David Vandevoorde and Nicolai M. Josuttis, Addison-Wesley, 2002
 *
 * (C) Copyright David Vandevoorde and Nicolai M. Josuttis 2002.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
template <typename C, int N> 
class BaseMem : public C {
  public:
    BaseMem(C& c) : C(c) { }
    BaseMem(C const& c) : C(c) { }
};

template <typename FO1, typename FO2>
class Composer : private BaseMem<FO1,1>,
                 private BaseMem<FO2,2> {
  public:
    // constructor: initialize function objects
    Composer(FO1 f1, FO2 f2)
     : BaseMem<FO1,1>(f1), BaseMem<FO2,2>(f2) {
    }

    // ``function call'': nested call of function objects
    double operator() (double v) {
        return BaseMem<FO2,2>::operator()
                 (BaseMem<FO1,1>::operator()(v));
    }
};
