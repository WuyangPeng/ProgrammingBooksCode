 /* '03 Main.cpp' */
#include <iostream>

 /* Start of program */
main (void)
{
  /* Variable declarations */
 short   A, B, C, D;
  /* Variable initialization */
 A = B = C = D = 10;
  /* Show the operator use */
 std::cout << "Using the operators " << std::endl;
 std::cout << "A = " << A++ << std::endl;
 std::cout << "B = " << B-- << std::endl;
 std::cout << "C = " << ++C << std::endl;
 std::cout << "D = " << --D << std::endl;
  /* Show the final values */
 std::cout << "After using the operators " << std::endl;
 std::cout << "A = " << A << std::endl;
 std::cout << "B = " << B << std::endl;
 std::cout << "C = " << C << std::endl;
 std::cout << "D = " << D << std::endl;
 return 0;
}
