#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{  
   list<string> staff;

   staff.push_back("Cracker, Carl");
   staff.push_back("Hacker, Harry");
   staff.push_back("Lam, Larry");
   staff.push_back("Sandman, Susan");

   /* add a value in fourth place */

   list<string>::iterator pos;
   pos = staff.begin();
   pos++;
   pos++;
   pos++;

   staff.insert(pos, "Reindeer, Rudolf");

   /* remove the value in second place */

   pos = staff.begin();
   pos++;

   staff.erase(pos);

   /* print all values */

   for (pos = staff.begin(); pos != staff.end(); pos++)
      cout << *pos << "\n";

   return 0;
}

