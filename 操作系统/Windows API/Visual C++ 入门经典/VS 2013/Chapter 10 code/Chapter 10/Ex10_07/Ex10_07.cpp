// Ex10_07.cpp
// Using the remove_if() function for a list

#include <iostream>
#include <list>
#include "function_object.h"

// Template function to list the contents of a list
template <class T>
void listAll(const std::list<T>& data) {
  for (const auto& t : data)
    std::cout << t << "  ";
  std::cout << std::endl;
}

// Template function to read data from cin and store it in a list
template<class T>
void loadlist(std::list<T>& data)
{
  T value;
  while (std::cin >> value, value != T())  //Read non-zero values
    data.emplace_back(std::move(value));
}

int main()
{
  // Process integers
  std::list<int> numbers;
  std::cout << "Enter non-zero integers separated by spaces. Enter 0 to end."
    << std::endl;
  loadlist(numbers);
  std::cout << "The list contains:" << std::endl;
  listAll(numbers);
  numbers.remove_if(is_negative<int>());
  std::cout << "After applying remove_if()the list contains:" << std::endl;
  listAll(numbers);

  // Process floating-point values
  std::list<double> values;
  std::cout << "\nEnter non-zero float values separated by spaces(some negative!)."
    << "Enter 0 to end." << std::endl;
  loadlist(values);
  std::cout << "The list contains:" << std::endl;
  listAll(values);
  values.remove_if(is_negative<double>());
  std::cout << "After applying remove_if()the list contains:" << std::endl;
  listAll(values);

  /* Code to try out merge()...
  // Another list to use in merge
  std::list<double> morevalues;
  std::cout << "\nEnter non-zero float values separated by spaces. Enter 0 to end."
  << std::endl;
  loadlist(morevalues);
  std::cout << "The list contains:" << std::endl;
  listAll(morevalues);
  morevalues.remove_if(is_negative<double>());
  std::cout << "After applying the remove_if() function the list contains:" << std::endl;
  listAll(morevalues);

  // Merge the last two lists
  values.sort(std::greater<>());
  morevalues.sort(std::greater<>());
  values.merge(morevalues, std::greater<>());
  std::cout << "\Sorting and merging two lists produces:" << std::endl;
  listAll(values);
  */
}
