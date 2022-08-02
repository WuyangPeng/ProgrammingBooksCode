// Ex5_14.cpp
// Using a static variable within a function
#include <iostream>
using std::cout;
using std::endl;

void record();      // Function prototype, no arguments or return value

int main()
{
  record();

  for (int i{}; i <= 3; i++)
    record();

  cout << endl;
  return 0;
}

// A function that records how often it is called
void record()
{
  static int count{};
  cout << endl << "This is the " << ++count;
  if ((count > 3) && (count < 21))          // All this....
    cout << "th";
  else
    switch (count % 10)                     // is just to get...
  {
  case 1: cout << "st";
          break;
  case 2: cout << "nd";
          break;
  case 3: cout << "rd";
          break;
  default: cout << "th";                    // the right ending for...
  }                                         // 1st, 2nd, 3rd, 4th, etc.
  cout << " time I have been called";
  return;
}
