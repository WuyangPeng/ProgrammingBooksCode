// Soln3_3.cpp

/* Using the setw manipulator ensures the spacing is consistent for all results
   and the values line up in columns.
   Note how I have used a \n character for a newline in the output. 
   You could use endl instead but you would have to output it separately from other text.
*/

#include <iostream>
#include <iomanip>

int main()
{
   std::cout << "     2     3     4     5     6     7     8     9    10    11    12\n";
   std::cout << "------------------------------------------------------------------------\n";
   for (int i{ 1 }; i <= 12; ++i)          // rows
   {
     for (int j{ 2 }; j <= 12; ++j)      // columns
      {
         std::cout << std::setw(6) << j*i;
      }
      std::cout << '\n';
   }
}
