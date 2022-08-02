#include <iostream>
#include <iomanip>

using namespace std;

#include "ccc_time.cpp"

/**
   Print a time in the format h:mm:ss
   @param t the time to print
*/
void print_time(Time t)
{  
   cout << t.get_hours() << ":"
      << setw(2) << setfill('0') << t.get_minutes() << ":"
      << setw(2) << t.get_seconds() << setfill(' ');
}

int main()
{  
   Time liftoff(7, 0, 15);
   Time now;
   cout << "Liftoff: ";
   print_time(liftoff);
   cout << "\n";

   cout << "Now: ";
   print_time(now);
   cout << "\n";

   return 0;
}
