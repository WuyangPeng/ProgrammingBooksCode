// Soln4_1.cpp
#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::setw;


int main()
{
  int arraySize(5);
  double* values = new double[arraySize];    // Initial array to store values
  double* temp(nullptr);                     // Temporary store for pointer to new array
  double inputValue(0.0);                    // Current input value
  int index(0);                              // Index to the values array
  for(;;)
  {
    // Read the next value
    cout << "Enter a value or 0 to end: ";
    cin >> inputValue;

    // If it is 0 we are done so exit the loop
    if(inputValue == 0.0)
      break;

    values[index++] = inputValue;            // Store the value and increment index

    if(index == arraySize)                   // If index reaches arraySize
    {                                        // We need a bigger array...
      arraySize += 5;                        // Increase the array size value
      temp = new double[arraySize];          // Allocate the new array

      for(int i = 0 ; i<index ; i++)         // Copy old array elements to new
        temp[i] = values[i];

      delete[] values;                       // Delete the old array
      values = temp;                         // Store address of new array
      temp = nullptr;                        // Reset temp to null
    }
  }
  // Calcuate the average and output the values
  double average(0.0);                       // Store for the average
  for(int i = 0 ; i<index ; i++)
  {
    average += values[i];                    // Add value
    cout << setw(10) << values[i];           // Output current value
    if((i+1)%5 == 0)                         // If it's multiple of 5
      cout << endl;                          // start a new line
  }
  cout << endl                               // Output the average
       << "Average is " << average/index
       << endl;
  delete[] values;                           // Release memory for array
  values = nullptr;                          // Reset to null

  return 0;
}
