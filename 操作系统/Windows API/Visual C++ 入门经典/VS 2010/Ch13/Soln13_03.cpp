// Soln13_03.cpp
/*
  This is a relatively simple modification of the sum_of_squares function.
  With four processors, three tasks are started on spearate threads using the
  TaskGroup object that is created. The fourth task executes on the current thread.
  This time partial sums are accumulated in local variables sum1, sum2, and so on.
  You could also use a Combinable object here instead.
*/

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include "ppl.h"


// Function to use parallel operations to compute the sume of squares
template <class T>
double sum_of_squares(T values)
{
  // This is for 4 processors
  // If you have a different number of processors,
  // change the number of sumN variables and the 
  // number of calls to the task group run() function accordingly.
  double sum1(0.0), sum2(0.0), sum3(0.0), sum4(0.0);
  Concurrency::task_group taskGroup;
  taskGroup.run(
    [&]
  {  for(size_t i = 0 ; i<values.size() ; i += 4)
        sum1 += values[i]*values[i];
  });
  taskGroup.run(
    [&]
  {  for(size_t i = 1 ; i<values.size() ; i += 4)
        sum2 += values[i]*values[i];
  });
  taskGroup.run(
    [&]
  {  for(size_t i = 2 ; i<values.size() ; i += 4)
        sum4 += values[i]*values[i];
  });

  // Execute one on current thread
  for(size_t i = 3 ; i<values.size() ; i += 4)
      sum4 += values[i]*values[i];
  taskGroup.wait();                    // Wait until other threads complete execution
  
  return sum1+sum2+sum3+sum4;
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