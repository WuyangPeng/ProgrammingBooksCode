#include <iostream>

using namespace std;

enum MonthEnum  {
  jan = 0, feb = 1, mar = 2, apr = 3, may = 4, jun = 5,
  jul = 6, aug = 7, sep = 8, oct = 9, nov = 10, dec = 11
};

bool isLeapYear(int y) {
  return (y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0));
}

const int arrayDaysInMonth[] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int n;
int arrayFirstOfMonth[] = {
  n = 0,
  n += arrayDaysInMonth[jan],
  n += arrayDaysInMonth[feb],
  n += arrayDaysInMonth[mar],
  n += arrayDaysInMonth[apr],
  n += arrayDaysInMonth[may],
  n += arrayDaysInMonth[jun],
  n += arrayDaysInMonth[jul],
  n += arrayDaysInMonth[aug],
  n += arrayDaysInMonth[sep],
  n += arrayDaysInMonth[::oct], 
  n += arrayDaysInMonth[nov]
};

int daysInMonth(MonthEnum month, int year) {
  if (month == feb) {
    return isLeapYear(year) ? 29 : 28;
  }
  else {
    return arrayDaysInMonth[month];
  }
}

int firstOfMonth(MonthEnum month, int year) {
  return arrayFirstOfMonth[month] + isLeapYear(year);
}

int dayOfYear(MonthEnum month, int monthDay, int year) {
  return firstOfMonth(month, year) + monthDay - 1;
}

int main( ) {
  cout << "July 1, 1971, was the " << dayOfYear(jul, 1, 1971);
  cout << " day of the year" << endl;
}
