// Soln3_3.cpp

/* Using the setw manipulator ensures the spacing is consistent for all results
   and the value line up in columns.
   Note how I have used a \n character for a newline in the output. 
   You could use endl instead but you would have to output it separately from other text.
*/

#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;

int main()
{
   cout << "     2     3     4     5     6     7     8     9    10    11    12\n";
   cout << "------------------------------------------------------------------------\n";
   for (int i=1; i<13; i++)         // rows
   {
      for (int j=2; j<13; j++)      // columns
      {
         cout << setw(6) << j*i;
      }
      cout << '\n';
   }
   return 0;
}
