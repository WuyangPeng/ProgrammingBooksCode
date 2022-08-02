// Ex10_05.cpp
// Using a double-ended queue

#include <iostream>
#include <deque>
#include <algorithm>                 // For sort<T>()
#include <numeric>                   // For accumulate<T>()
#include <functional>                // For transparent operator functors

int main()
{
  std::deque<int> data;

  // Read the data
  std::cout << "Enter a series of non-zero integers separated by spaces."
    << " Enter 0 to end." << std::endl;
  int value{};
  while (std::cin >> value, value != 0)
    data.push_front(value);

  // Output the data
  std::cout << std::endl << "The values you entered are:" << std::endl;
  for (const auto& n : data)
    std::cout << n << "  ";
  std::cout << std::endl;

  // Output the data using a reverse iterator
  std::cout << std::endl << "In reverse order the values you entered are:" << std::endl;
  for (auto riter = crbegin(data); riter != crend(data); ++riter)
    std::cout << *riter << "  ";
  std::cout << std::endl;

  // Sort the data in descending sequence

  std::cout << std::endl << "In descending sequence the values you entered are:" << std::endl;
  std::sort(begin(data), end(data), std::greater<>());   // Sort the elements
  for (const auto& n : data)
    std::cout << n << "  ";
  std::cout << std::endl;

  // Calculate the sum of the elements
  std::cout << std::endl << "The sum of the elements in the queue is: "
    << std::accumulate(cbegin(data), cend(data), 0) << std::endl;
}
