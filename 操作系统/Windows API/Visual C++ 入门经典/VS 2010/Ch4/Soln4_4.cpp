// Soln4_4.cpp : main project file.

#include "stdafx.h"

using namespace System;
/*
 This uses an array of bool values to record which data values
 have been output at any given time. A value that has been output
 is marked as true in the used array, and only values that have a 
 corresponding true value in the used array are checked each time.
*/

int main(array<System::String ^> ^args)
{
  Random^ generator = gcnew Random;
  array<int>^ values = gcnew array<int>(generator->Next(10,20));

  // Initialize the array of data value
  for (int i = 0 ; i < values->Length ; i++)
    values[i] = generator->Next(100,1000);

  // Create array to identify elements that have been output
  array<bool>^ used = gcnew array<bool>(values->Length);
  Array::Clear(used, 0, used->Length);      // Set elements false

  Console::WriteLine(L"There are {0} values.", values->Length);


  int minimum = Int32::MaxValue;            // Current minimum - set to maximum possible value
  int minIndex = 0;                         // Index of current minimum

  // Output the values in ascending sequence
  for(int count = 0 ; count<values->Length ; count++)
  {
    // Find minimum of those not yet output
    for(int i = 0 ; i<values->Length ; i++)
      if(!used[i] && minimum > values[i])
      {
        minimum = values[i];
        minIndex = i;
      }

    used[minIndex] = true;                 // Record minimum as used
    Console::Write(L"{0,10}", minimum);    // Write the minimum
    if((count+1)%5 == 0)                   // If it's multiple of 5
      Console::WriteLine();                // Write a newline
    minimum = Int32::MaxValue;             // Reset to maximum possible
  }

  Console::WriteLine();
  return 0;
}
