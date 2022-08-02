 /* '04 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

double Average (int * ListValues, int Elements);

 /* Start */
main (void)
{
  /* Declare a normal int and a pointer to an array of int's */
 int Values [5];
 int NumberValues;

  /* Get five values from user*/
 for (NumberValues = 0; NumberValues < 5; NumberValues ++)
 {
  std::cout << "Enter value " << NumberValues + 1 << " : ";
  std::cin >> Values [NumberValues];
 }

  /* Calculate average */
 double AverageValues;
 AverageValues = Average (Values, 5);

  /* Print average */
 std::cout << "The average of all the values is : " << AverageValues;
 std::cout << std::endl;

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
