// Ex10_15.cpp Using lambda expressions
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>                               // For random number generation
using namespace std;                            // Just to make the code easier to read in the example...



// Initialize random number generator

// Template function to return the average of the elements in a vector
template <class T> T average(const vector<T>& vec)
{
  static_assert(std::is_arithmetic<T>::value,
    "Type parameter for average() must be arithmetic.");
  T sum{};
  for_each(begin(vec), end(vec),
    [&sum](const T& value){ sum += value; });
  return sum / vec.size();
}

// Template function to set a vector to values beginning with start
// and incremented by increment
template <class T> void setValues(vector<T>& vec, T start, T increment)
{
  static_assert(std::is_arithmetic<T>::value,
    "Type parameter for setValues() must be arithmetic.");
  T current{ start };
  generate(begin(vec), end(vec),
    [increment, &current]()  {T result{ current };
  current += increment;
  return result; });
}

// Template function to set a vector to random values between min and max
template<class T> void randomValues(vector<T>& vec, T min_value, T max_value)
{
  static_assert(std::is_arithmetic<T>::value,
    "Type parameter for randomValues() must be arithmetic.");

  random_device engine;                // Random number source
  auto max_rand = engine.max();        // Maximum random value
  auto min_rand = engine.min();        // Minimum random value

  generate(begin(vec), end(vec),
    [&engine, max_rand, min_rand, min_value, max_value]
  {  return static_cast<T>(static_cast<double>(engine()) / max_rand*(max_value - min_value) + min_value); });
}

// Template function to list the values in a vector
template<class T> void listVector(const vector<T>& vec)
{
  int count{};       // Used to control outputs per line
  const int valuesPerLine{ 5 };
  for_each(cbegin(vec), cend(vec),
    [&count, valuesPerLine](const T& n) { cout << setw(10) << n << "  ";
  if (++count % valuesPerLine == 0)
    cout << endl; });
}

int main()
{
  vector<int> integerData(50);
  randomValues(integerData, 1, 10);            // Set random integer values
  cout << "Vector contains random integers:" << endl;
  listVector(integerData);
  cout << "Average value is " << average(integerData) << endl;

  vector<double> realData(20);
  setValues(realData, 5.0, 2.5);   // Set real values starting at 5.0
  cout << "\nVector contains real values:" << endl;
  listVector(realData);
  cout << "Average value is " << average(realData) << endl;

  vector<double> randomData(20);
  randomValues(randomData, 5.0, 25.0);   // Set random values from 5.0 to 25
  cout << "\nVector contains random real values:" << endl;
  listVector(randomData);
  cout << "Average value is " << average(randomData) << endl;
}
