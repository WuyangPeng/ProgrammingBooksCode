 /* '06 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare an array of int's */
 int Values [10];
 int * PointerValues;
 int NumberValues;

  /* Initialize the pointer to the first element of array */
 PointerValues = Values;

  /* Fill in array with random values */
 for (NumberValues = 0; NumberValues < 10; NumberValues ++)
 {
  Values [NumberValues] = rand () % 1000;
 }

  std::cout << "Array \tIndirection \tAddress" << std::endl;

  /* Print array using normal array accessing and pointer arithmetic */
 for (NumberValues = 0; NumberValues < 10; NumberValues ++)
 {
  std::cout << Values [NumberValues] << "\t";
  std::cout << *PointerValues << "\t\t";
  std::cout << PointerValues++ << std::endl;
 }

 return 0;
}