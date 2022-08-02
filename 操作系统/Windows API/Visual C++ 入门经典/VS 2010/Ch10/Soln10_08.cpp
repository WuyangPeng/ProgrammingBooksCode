// Soln10_08.cpp Using a lambda expression to generate the Fibonacci series

// There are many way to do this so this is just one possibility.
// You may well have a different solution.
// If the results are correct then your solution must be correct!

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <algorithm>

using std::function;
using std::cout;
using std::endl;
                        
int main()
{
  std::vector<long> values(40);

  long count(0L);    
  std::generate(values.begin(), values.end(),
   
    [&count, &values]()->long{ 
      if(count++ <= 1L)
        return count-1;
      else
        return values.at(count-2) + values.at(count-3); });

  // Output the contents of the vector
  cout << "The vector contains:" << endl;
  int i(0);
  for(auto iter = values.begin() ; iter != values.end() ; ++iter)
  {
    cout << std::setw(15) << *iter;
    if(!(++i % 5))
      cout << endl;
  }
   return 0;
}
