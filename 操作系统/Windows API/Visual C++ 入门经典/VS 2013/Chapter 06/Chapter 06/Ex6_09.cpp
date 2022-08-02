// Ex6_09.cpp Using the decltype operator
#include <iostream>
using std::cout;
using std::endl;
        
template<typename T1, typename T2>
auto product(T1 v1[], T2 v2[], const size_t count) -> decltype(v1[0]*v2[0])
{
  decltype(v1[0] * v2[0]) sum {};
  for (size_t i {}; i < count; i++) sum += v1[i] * v2[i];
  return sum;
}

int main()
{
  double x[] {100.5, 99.5, 88.7, 77.8};
  short y[] {3, 4, 5, 6};
  long z[] {11L, 12L, 13L, 14L};
  size_t n { _countof(x) };
  cout << "Result type is " << typeid(product(x, y, n)).name() << endl;
  cout << "Result is " << product(x, y, n) << endl;
  auto result = product(z, y, n);
  cout << "Result type is " << typeid(result).name() << endl;
  cout << "Result is " << result << endl;
  return 0;
}
