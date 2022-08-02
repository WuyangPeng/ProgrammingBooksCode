// Ex10_01.cpp
// Exploring the size and capacity of a vector

#include <iostream>
#include <vector>
using std::vector;

// Template function to display the size and capacity of any vector
template<class T>
void listInfo(const vector<T>& v)
{
  std::cout << "Container capacity: " << v.capacity()
    << " size: " << v.size() << std::endl;
}

int main()
{
  // Basic vector creation
  vector<double> data;
  listInfo(data);

  data.reserve(100);
  std::cout << "After calling reserve(100):" << std::endl;
  listInfo(data);


  vector<int> numbers(10, -1); // Create a vector with 10 elements and initialize it
  std::cout << "The initial values are: ";

  for (auto n : numbers)       // You can use the range-based for loop with a vector
    std::cout << " " << n;
  std::cout << std::endl << std::endl;

  // See how adding elements affects capacity increments
  auto oldC = numbers.capacity();   // Old capacity
  auto newC = oldC;                 // New capacity after adding element
  listInfo(numbers);
  for (int i{}; i<1000; i++)
  {
    numbers.push_back(2 * i);
    newC = numbers.capacity();
    if (oldC < newC)                 // Only output when capacity increases
    {
      oldC = newC;
      listInfo(numbers);
    }
  }
}
