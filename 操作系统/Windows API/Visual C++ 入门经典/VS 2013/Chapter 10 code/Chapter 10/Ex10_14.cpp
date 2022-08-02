// Ex10_14.cpp
// Using stream and inserter iterators
#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>

int main()
{
  std::vector<int> numbers;
  std::cout << "Enter a series of integers separated by spaces"
    << " followed by Ctrl+Z or a letter:" << std::endl;

  std::istream_iterator<int> input{ std::cin }, input_end;
  std::ostream_iterator<int> out{ std::cout, " " };

  std::copy(input, input_end, std::back_inserter<std::vector<int>> {numbers});

  std::cout << "You entered the following values:" << std::endl;
  std::copy(std::cbegin(numbers), std::cend(numbers), out);

  std::cout << "\nThe sum of these values is "
    << std::accumulate(std::cbegin(numbers), std::cend(numbers), 0) << std::endl;
}
