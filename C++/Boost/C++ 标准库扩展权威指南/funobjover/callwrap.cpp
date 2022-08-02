#include <iostream>
#include <math.h>
using std::cout;

class wrapper
  { // simple call wrapper type
  typedef float(*fp)(float);
public:
  wrapper(fp ptr) : fptr(ptr) {}
  float operator()(float arg)
    { // call operation; forwards to target object
    return fptr(arg);
    }
private:
  fp fptr;              // target object
  };

int main()
  { // demonstrate use of call wrapper
  wrapper wrap(cosf);   // call wrapper
  cout << "cosf(1.0) is " << cosf(1.0) << '\n';
  cout << "wrap(1.0) is " << wrap(1.0) << '\n';
  return 0;
  };