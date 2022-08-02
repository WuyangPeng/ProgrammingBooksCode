// Ex6_02.cpp
// A pointer to a function as an argument
#include <iostream>
using std::cout;
using std::endl;

// Function prototypes
double squared(double);
double cubed(double);
double sumarray(const double data[], size_t len, double(*pfun)(double));

int main()
{
  double data[] { 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5 };
  size_t len{ _countof(data) };

  cout << endl << "Sum of squares = " << sumarray(data, len, squared);
  cout << endl << "Sum of cubes = " << sumarray(data, len, cubed);
  cout << endl;
  return 0;
}

// Function for a square of a value
double squared(double x)
{
  return x*x;
}

// Function for a cube of a value
double cubed(double x)
{
  return x*x*x;
}

// Function to sum functions of array elements
double sumarray(const double data[], size_t len, double(*pfun)(double))
{
  double total{};                   // Accumulate total in here

  for (size_t i{}; i < len; i++)
    total += pfun(data[i]);

  return total;
}