#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

time_t dateToTimeT(int month, int day, int year) {
  // january 5, 2000 is passed as (1, 5, 2000)
  tm tmp = tm( );
  tmp.tm_mday = day;
  tmp.tm_mon = month - 1;
  tmp.tm_year = year - 1900;
  return mktime(&tmp);
}

time_t badTime( ) {
  return time_t(-1);
}

time_t now( ) {
  return time(0);
}

int main( ) {
  time_t date1 = dateToTimeT(1,1,2000);
  time_t date2 = dateToTimeT(1,1,2001);

  if ((date1 == badTime( )) || (date2 == badTime( ))) {
    cerr << "unable to create a time_t struct" << endl;
    return EXIT_FAILURE;
  }
  double sec = difftime(date2, date1);
  long days = static_cast<long>(sec / (60 * 60 * 24));
  cout << "the number of days between Jan 1, 2000, and Jan 1, 2001, is ";
  cout << days << endl;
  return EXIT_SUCCESS;
}
