#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "ccc_time.h"

class Clock
{
public:
   /**
      Constructs a clock that can tell the local time.
      @param use_military true if the clock uses military format
   */
   Clock(bool use_military);
   
   /**
      Gets the location of this clock.
      @return the location
   */
   string get_location() const;

   /**
      Gets the hours of this clock.
      @return the hours, in military or am/pm format
   */
   int get_hours() const;

   /**
      Gets the minutes of this clock.
      @return the minutes
   */
   int get_minutes() const;

   /**
      Checks whether this clock uses miltary format.
      @return true if miltary format
   */
   bool is_military() const;
private:
   bool military;
};

Clock::Clock(bool use_military)
{
   military = use_military;
}

string Clock::get_location() const
{
   return "Local";
}

int Clock::get_hours() const
{
   Time now;
   int hours = now.get_hours();
   if (military) return hours;
   if (hours == 0) 
      return 12;
   else if (hours > 12)
      return hours - 12;
   else
      return hours;
}

int Clock::get_minutes() const
{
   Time now;
   return now.get_minutes();
}

bool Clock::is_military() const
{
   return military;
}

int main()
{
   Clock clock1(true);
   Clock clock2(false);

   bool more = true;
   while (more)
   {
      cout << "Military time is "
         << clock1.get_hours() << ":"
         << setw(2) << setfill('0') 
         << clock1.get_minutes() 
         << setfill(' ') << "\n";
      cout << "am/pm time is "
         << clock2.get_hours() << ":"
         << setw(2) << setfill('0') 
         << clock2.get_minutes() 
         << setfill(' ') << "\n";

      cout << "Try again? (y/n) ";
      string input;
      getline(cin, input);
      if (input != "y") more = false;
    }
   return 0;
}

