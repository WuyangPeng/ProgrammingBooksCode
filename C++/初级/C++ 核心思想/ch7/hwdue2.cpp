#include <iostream>

using namespace std;

#include "ccc_time.cpp"

int main()
{  
   cout << 
       "Enter homework due time (hours minutes): ";
   int hours;
   int minutes;
   cin >> hours >> minutes;
   Time homework_due(hours, minutes, 0);
   Time now;

   if (now.get_hours() < homework_due.get_hours() ||
         (now.get_hours() == homework_due.get_hours() &&
         now.get_minutes() <= homework_due.get_minutes()))
      cout << "Still time to finish the homework.\n";
   else
      cout << "The homework is already past due.\n";

   return 0;
}

