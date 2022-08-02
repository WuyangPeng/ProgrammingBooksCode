 /* '03 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a normal int and a pointer to an int */
 int Value;
 int * PointerValue;

  /* Init Value to 23 and PointerValue to the address of Value */
 Value = 23;
 PointerValue = &Value;

  /* Print value of Value using the variable and using the indirection
     operator in the pointer */
 std::cout << "Using Value = " << Value << std::endl;
 std::cout << "Using indirection operator = ";
 std::cout << *PointerValue << std::endl;

  /* Print address of Value using the address-of operator and using the 
     pointer value */
 std::cout << "Using address-of operator = " << &Value << std::endl;
 std::cout << "Using PointerValue = ";
 std::cout << PointerValue << std::endl;

 return 0;
}