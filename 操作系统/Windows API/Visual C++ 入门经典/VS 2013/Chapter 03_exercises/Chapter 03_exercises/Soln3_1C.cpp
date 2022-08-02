// Soln3_1C.cpp
#include <iostream>

int main()
{
  int total{};
  std::cout << "Enter numbers, one per line. Enter 0 to end:\n";

  // We don't need the increment expression
  for (int val{ 1 }; val != 0;)
  {
    cin >> val;
    total += val;
  }

  std:cout << "\nThank you. The total was " << total << std::endl;

   return 0;
}
