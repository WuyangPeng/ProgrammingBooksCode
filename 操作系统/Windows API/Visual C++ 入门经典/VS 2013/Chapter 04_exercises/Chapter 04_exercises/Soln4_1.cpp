// Soln4_1.cpp
#include <iostream>
#include <iomanip>

int main()
{
  size_t arraySize{ 5 };
  double* values{ new double[arraySize] };   // Initial array to store values
  double* temp{};                            // Temporary store for pointer to new array
  double inputValue{};                       // Current input value
  size_t index{};                            // Index to the values array
  for(;;)
  {
    // Read the next value
    std::cout << "Enter a value or 0 to end: ";
    std::cin >> inputValue;

    // If it is 0 we are done so exit the loop
    if(inputValue == 0.0)
      break;

    values[index++] = inputValue;                // Store the value and increment index

    if(index == arraySize)                       // If index reaches arraySize
    {                                            // We need a bigger array...
      arraySize += 5;                            // Increase the array size value
      temp = new double[arraySize];              // Allocate the new array

      for (size_t i{}; i < index; ++i)           // Copy old array elements to new
        temp[i] = values[i];

      delete[] values;                           // Delete the old array
      values = temp;                             // Store address of new array
      temp = nullptr;                            // Reset temp to null
    }
  }
  // Calcuate the average and output the values
  double average{};                              // Store for the average
  for (size_t i{}; i < index; ++i)
  {
    average += values[i];                        // Add value
    std::cout << std::setw(10) << values[i];     // Output current value
    if((i + 1) % 5 == 0)                         // If it's multiple of 5
      std::cout << std::endl;                    // start a new line
  }
  std::cout << std::endl                     
            << "Average is " << average/index    // Output the average
            << std::endl;
  delete[] values;                               // Release memory for array
  values = nullptr;                              // Reset to null
}
