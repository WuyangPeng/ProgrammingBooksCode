 /* '05 Main.cpp' */
#include <iostream>

 /* Start of program */
main (void)
{
 short ValueA, ValueB, ValueResult;
 ValueA = 5;
 ValueB = 7;
 ValueResult = (ValueA > ValueB) ? ValueA : ValueB;
 std::cout << "The greater value is: " << ValueResult << std::endl;
 return 0;
}

