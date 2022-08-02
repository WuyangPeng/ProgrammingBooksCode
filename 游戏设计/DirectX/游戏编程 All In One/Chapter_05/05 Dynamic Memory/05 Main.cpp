 /* '05 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

double Average (int * ListValues, int Elements);

 /* Start */
main (void)
{
  /* Declare a pointer to an int */
 int * Values;
 int NumberValues;
 int TotalValues;

  /* Get number of values */
 std::cout << "Enter number of values : ";
 std::cin >> TotalValues;

  /* Dynamicly allocate the array */
 Values = new int [TotalValues];
 
  /* Get five values from user*/
 for (NumberValues = 0; NumberValues < TotalValues; NumberValues ++)
 {
  std::cout << "Enter value " << NumberValues + 1 << " : ";
  std::cin >> Values [NumberValues];
 }

  /* Calculate average */
 double AverageValues;
 AverageValues = Average (Values, TotalValues);

  /* Print average */
 std::cout << "The average of all the values is : " << AverageValues;
 std::cout << std::endl;

  /* Free the memory used by the array */
 delete [] Values;

 return 0;
}

 /* Calculate average */
double Average (int * ListValues, int Elements)
{
 double Total = 0;
 int NumberElement;

  /* Add all values to Total */ 
 for (NumberElement = 0; NumberElement < Elements; NumberElement ++)
 {
  Total += ListValues [NumberElement];
 }
  /* Calculate average and return it */
 return Total / Elements;
}
