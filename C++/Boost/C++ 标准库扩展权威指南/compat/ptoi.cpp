#include <cstdint>
#include <iostream>
#include <iomanip>
using std::cout; using std::hex; using std::boolalpha;

int main()
  { // demonstrate intptr_t, uintptr_t
  int i;
  int *ip = &i;
  intptr_t intptr = (intptr_t)ip;
  uintptr_t uintptr = (uintptr_t)ip;
  cout << boolalpha;
  cout << "address:  " << (void*)ip << '\n';
  cout << "intptr:   " << hex << intptr << '\n';
  cout << "uintptr:  " << hex << uintptr << '\n';
  cout << "ip == (int*)intptr:  "
    << (ip == (int*)intptr) << '\n';
  cout << "ip == (int*)uintptr: "
    << (ip == (int*)uintptr) << '\n';
  return 0;
  }