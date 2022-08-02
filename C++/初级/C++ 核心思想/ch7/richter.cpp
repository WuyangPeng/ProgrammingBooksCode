#include <iostream>
#include <string>

using namespace std;

int main()
{  
   cout << "Enter a magnitude on the Richter scale: ";
   double richter;
   cin >> richter;

   if (richter >= 8.0)
      cout << "Most structures fall\n";
   else if (richter >= 7.0)
      cout << "Many buildings destroyed\n";
   else if (richter >= 6.0)
      cout << "Many buildings considerably damaged, "
         << "some collapse\n";
   else if (richter >= 4.5)
      cout << "Damage to poorly constructed buildings\n";
   else if (richter >= 3.5)
      cout << "Felt by many people, no destruction\n";
   else if (richter >= 0)
      cout << "Generally not felt by people\n";
   else
      cout << "Negative numbers are not valid\n";
   return 0;
}

