#include <iostream>

using namespace std;

#include "ccc_time.h"

int main()
{  
   Time wake_up(9, 0, 0);
   wake_up.add_seconds(1000); 
      /* a thousand seconds later */
   cout << wake_up.get_hours() 
      << ":" << wake_up.get_minutes()
      << ":" << wake_up.get_seconds() << "\n";

   return 0;
}
