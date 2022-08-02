#include <iostream>
#include <iomanip>

using namespace std;

#include "ccc_time.cpp"

/**
   Compute the number of seconds between two points in time.
   @param a a point in time
   @param b another point in time
   @return the number of seconds that a is away from b
*/
int operator-(Time a, Time b)
{  
   return a.seconds_from(b);
}

/**
   Compute a point in time that is some number of seconds away.
   @param a a point in time
   @param sec the seconds to add
   @return a point in time that is sec seconds away from a
*/
Time operator+(Time a, int sec)
{  
   Time r = a;
   r.add_seconds(sec);
   return r;
}

/**
   Compare two points in time.
   @param a a point in time
   @param b another point in time
   @return true if they are the same
*/
bool operator==(Time a, Time b)
{  
   return a.seconds_from(b) == 0;
}

/**
   Compare two points in time.
   @param a a point in time
   @param b another point in time
   @return true if they are the different
*/
bool operator!=(Time a, Time b)
{  
   return a.seconds_from(b) != 0;
}

/**
   Print a Time object
   @param out an output stream
   @param a a point in time
   @return out
*/
ostream& operator<<(ostream& out, Time a)
{  
   out << a.get_hours() << ":"
      << setw(2) << setfill('0') 
      << a.get_minutes() << ":"
      << setw(2) << a.get_seconds() << setfill(' ');
   return out;
} 

int main()
{  
   Time now;
   cout << "Now it is " << now << "\n";
   Time later = now + 1000;
   cout << "A thousand seconds later it is " << later << "\n";
   Time now2;
   if (now == now2)
      cout << "It still is " << now2 << "\n";
   if (now != now2)
      cout << "It is already " << now2 << "\n";
   cout << "Another " << later - now2 
      << " seconds until " << later << "\n";
   return 0;
}

