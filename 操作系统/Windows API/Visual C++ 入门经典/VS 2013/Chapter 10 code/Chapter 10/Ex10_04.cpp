// Ex10_04
// Using array containers
#include <iostream>
#include <iomanip>
#include <array>
#include <numeric>
using std::array;

// Lists array container contents
template<class T, size_t N>
void listValues(const array<T, N>& data)
{
  const int values_per_line{ 6 };
  int count{};
  for (const auto& value : data)
  {
    std::cout << std::setw(14) << value;
    if (++count % values_per_line == 0)
      std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main()
{
  // Create the famous Fibonacci series
  const size_t N{ 20 };
  array<long, N> fibonacci{ 1L, 1L };
  for (size_t i{ 2 }; i<fibonacci.size(); ++i)
    fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
  std::cout << "Fibonacci series is:" << std::endl;
  listValues(fibonacci);

  array<long, N> numbers;
  numbers.fill(99L);
  fibonacci.swap(numbers);
  std::cout << std::endl << "After swap fibonacci contains:" << std::endl;
  listValues(fibonacci);

  // Create the series for pi/4
  array<double, 120> series;
  double factor{ -1.0 };
  for (size_t x{}; x<series.size(); ++x)
  {
    factor *= -1.0;
    series[x] = factor / (2 * x + 1);
  }
  std::cout << std::endl << "Series for pi is:" << std::endl;
  listValues(series);
  double result{ std::accumulate(cbegin(series), cend(series), 0.0) };
  std::cout << "The series sum converges slowly to pi/4. The sum x 4 is: "
    << 4.0*result << std::endl;
}
