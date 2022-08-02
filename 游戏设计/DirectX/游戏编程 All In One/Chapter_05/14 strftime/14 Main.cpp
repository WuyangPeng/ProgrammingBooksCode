 /* '14 Main.cpp' */

 /* Input output stream header file */
#include <iostream>
 /* Time header file */
#include <time.h>

 /* Start */
main (void)
{
  /* Declare a string and a time structure */
 char String [255];
 time_t Today;
 tm * Time;

  /* Get current time */
 time (&Today);
  /* Convert time to a structure*/
 Time = localtime (&Today);

  /* Convert time to our format */
 strftime (String, 255, "Today is %A, day %d of %B in the year %Y.\n\
It's also %H hours, %M minutes and %S seconds", Time);

  /* Output the time */
 std::cout << String << std::endl;

 return 0;
}