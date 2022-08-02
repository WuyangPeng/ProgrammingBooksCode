#include <iostream>

using namespace std;

#include "ccc_time.h"

int main()
{  
   Time now;
   Time day_end(23, 59, 59);
   long seconds_left = day_end.seconds_from(now);

   cout << "There are "
      << seconds_left
      << " seconds left in this day.\n";

   return 0;
}
