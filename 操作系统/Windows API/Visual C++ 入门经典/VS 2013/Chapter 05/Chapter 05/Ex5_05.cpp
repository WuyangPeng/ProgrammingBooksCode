// Ex5_05.cpp
// Handling an array in a function as a pointer
#include <iostream>
using std::cout;
using std::endl;

double average(double* array, int count);        // Function prototype

int main()
{
  double values[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };

  cout << endl << "Average = "
       << average(values, _countof(values)) << endl;
  return 0;
}

// Function to compute an average
double average(double* array, int count)
{
  double sum {};                                 // Accumulate total in here
  for (int i {}; i < count; i++)
    sum += *array++;                             // Sum array elements

   return sum/count;                             // Return average
}
