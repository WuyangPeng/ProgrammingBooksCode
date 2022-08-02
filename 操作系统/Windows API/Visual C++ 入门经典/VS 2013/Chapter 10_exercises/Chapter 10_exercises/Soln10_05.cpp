// Soln10_05.cpp Using a lambda expression to generate the Fibonacci series

// There are many ways to do this so this is just one possibility.
// You may well have a different solution.
// If the results are correct then your solution must be correct!

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

int main()
{
  size_t fiboCount{ 40 };
  std::vector<long> values(fiboCount);

  long count{};
  std::generate(begin(values), end(values),

    [&count, &values]()->long{
    if (count++ <= 1L)
      return count - 1L;
    else
      return values.at(count - 2) + values.at(count - 3); }
  );

  // Output the contents of the vector
  std::cout << "The vector contains:\n";
  int i{};
  for (auto iter = std::begin(values); iter != end(values); ++iter)
  {
    std::cout << std::setw(15) << *iter;
    if (!(++i % 5))
      std::cout << std::endl;
  }
}
