// Soln13_02.cpp
/*
  The sum_of_squares function calls the parallel_invoke algorithm with
  as many arguments as there are processors available.
  The sums computed in the lambda expressions are accumulated in separate
  variables provided by a Combinable object, which are
  then combined after the parallel_invoke operation is finished.
*/

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include "ppl.h"


// Function to use parallel_invoke algorithm to compute the sume of squares
template <class T>
double sum_of_squares(T values)
{
  // This is for 4 processors
  // If you have a different number of processors,
  // change the number of arguments to the parallel_invoke function accordingly.

  Concurrency::combinable<double> sums;

  Concurrency::parallel_invoke(
    [&]
  {  for(size_t i = 0 ; i<values.size() ; i += 4)
        sums.local() += values[i]*values[i];
  },
    [&]
  {  for(size_t i = 1 ; i<values.size() ; i += 4)
        sums.local() += values[i]*values[i];
  },
    [&]
  {  for(size_t i = 2 ; i<values.size() ; i += 4)
        sums.local() += values[i]*values[i];
  },
    [&]
  {  for(size_t i = 3 ; i<values.size() ; i += 4)
      sums.local() += values[i]*values[i];
  });
 
  return sums.combine([](double lSum, double rSum){return lSum+rSum; });
}

int main()
{
  std::array<double, 40> values = {  1, 2, 3, 4, 5, 6, 7, 8, 9,10,
                                 11,12,13,14,15,16,17,18,19,20,
                                 21,22,23,24,25,26,27,28,29,30,
                                 31,32,33,34,35,36,37,38,39,40};
  std::cout << "Sum of squaresof 1,2, ...,40 is " << sum_of_squares(values) << std::endl;
  std::array<double, 10000> more_values;
  srand(static_cast<unsigned int>(time(0)));
  std::generate(more_values.begin(), more_values.end(), []{return static_cast<double>(rand());});
  std::cout << "Sum of squares of " << more_values.size() << " random number is " 
            << sum_of_squares(more_values) << std::endl;

  return 0;
}