// Ex4_03.cpp
// Storing bean plant production in an array
#include <iostream>                                // For stream I/O
#include <iomanip>                                 // For stream manipulators
using namespace std;                               // Any name in std namespace

int main()
{
  const int plant_row_count{ 6 };                  // Count of plants in a row
  double beans[][plant_row_count] {                // Production for each plant
    { 12, 15 },
    { 0, 10, 13, 0, 11, 2 },
    { 8, 7, 10, 10, 13 },
    { 9, 8, 11, 13, 16 }
  };

  double averages[_countof(beans)] {};              // Stores average plant production
  for (int row{}; row < _countof(beans); ++row)
  {
    for (int plant{}; plant < plant_row_count; ++plant)
    {
      averages[row] += beans[row][plant];
    }
    averages[row] /= plant_row_count;
  }

  cout << "Average production per row is :"
    << setiosflags(ios::fixed)                      // Fixed point output
    << setprecision(2)                              // 2 decimal places
    << endl;

  int n{};                                         // Row number
  for (double ave : averages)
    cout << "Row " << ++n << setw(10) << ave << endl;

  return 0;
}
