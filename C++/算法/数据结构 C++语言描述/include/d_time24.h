#ifndef TIME24_CLASS
#define TIME24_CLASS

#include <iostream>
#include <iomanip>

#include "d_except.h"	// for rangeError exception

using namespace std;

#ifdef _MSC_VER

class time24;

time24 operator+ (const time24& lhs, const time24& rhs);
time24 operator+ (const time24& lhs, int min);
time24 operator+ (int min,	const time24& rhs);
time24 operator- (const time24& lhs, const time24& rhs);

bool operator== (const time24& lhs, const time24& rhs);
bool operator<  (const time24& lhs, const time24& rhs);
istream& operator>> (istream& istr, time24 &r);
ostream& operator<< (ostream& ostr, const time24& r);

#endif	// _MSC_VER

class time24
{
   public:
      time24(int h = 0, int m = 0);
	      // constructor initializes hour and minute

      void addTime(int m);
			// update time by adding m minutes to the current time
			// Precondition:  m must be >= 0
			// Postcondition: The new time is m minutes later

		time24 duration(const time24& t);
      	// return the length of time from the current time to some later
			// time t as a time24 value
			// Precondition:  time t must not be earlier than the current time.
			// if it is, throw a rangeError exception

      void readTime();
			// input from the keyboard time in the form hh:mm
			// Postcondition: Assign value hh to hour and mm to minute and
			// adjust units to the proper range.

      void writeTime() const;
			// display on the screen the current time in the form hh:mm


      int getHour() const;
			// return the hour value for the current time
      int getMinute() const;
			// return the minute value for the current time


		// THESE FUNCTIONS ARE DISCUSSED IN CHAPTER 2 ON OPERATOR
		// OVERLOADING

		friend bool operator== (const time24& lhs, const time24& rhs);

      friend bool operator<  (const time24& lhs, const time24& rhs);

      friend time24 operator+ (const time24& lhs, const time24& rhs);
			// form and return lhs + rhs
      friend time24 operator+ (const time24& lhs, int min);
			// form and return lhs + min
			// Precondition:  min must be >= 0
      friend time24 operator+ (int min, const time24& rhs);
			// form and return min + rhs
			// Precondition:  min must be >= 0
      friend time24 operator- (const time24& lhs, const time24& rhs);
			// form and return lhs - rhs
			// Precondition: lhs >= rhs. if not, throw a rangeError exception

      time24& operator+= (const time24& rhs);
			// current object = current object + rhs
			// Postcondition: the time increases by the value of rhs
      time24& operator+= (int min);
			// current object = current object + min
			// Precondition:  min must be >= 0
			// Postcondition: the time increases by min minutes

      friend istream& operator>> (istream& istr, time24& t);
			// input t in the format hh:mm. may omit the leading digit
			// if hours or minutes < 10
      friend ostream& operator<< (ostream& ostr, const time24& t);
			// output t in the format hh:mm. always include two digits
			// for the minute (e.g. 15:07). hours before 12 use 1 digit
			// and precede the hour by a blank (e.g. " 7:15")

   private:
      int hour, minute;	// data members

		// utility function sets the hour value in the range 0 to 23
		// and the minute value in the range 0 to 50
		void normalizeTime();
};

// ***********************************************************
//      time24 class implementation
// ***********************************************************

// set minute and hour within their proper ranges
void  time24::normalizeTime()
{
   int extraHours = minute / 60;

   // set minute in range 0 to 59
   minute %= 60;

   // update hour. set in range 0 to 23
   hour = (hour + extraHours) % 24;
}

// constructor. initialize time data
time24::time24(int h, int m) : hour(h), minute(m)
{
   // put hour and minute in correct range
	normalizeTime();
}

// add m minutes to the time
void time24::addTime(int m)
{
   // add m to minute. minute may exceed 59, so normalize
   minute += m;
   normalizeTime();
}

time24 time24::duration(const time24& t)
{
	// convert current time and time t to minutes
	int currTime = hour * 60 + minute;
	int tTime = t.hour * 60 + t.minute;

	// if t is earlier than the current time, throw an exception
	if (tTime < currTime)
		throw rangeError(
			"time24 duration(): argument is an earlier time");
	else
		// create an anonymous object as the return value
		return time24(0, tTime-currTime);
}

void time24::readTime()
{
   char colonSeparator;

   cin >> hour >> colonSeparator >> minute;
   // make sure hour and minute are in range
   normalizeTime();
}

// output time in the format <hour>:<minute>
void time24::writeTime() const
{
	// the implementation uses stream handling functions
	// not discussed in the book. consult your compiler
	// help system for details

   // save current format flags and fill character
   ios_base::fmtflags currentFlags = cout.flags();
   char currentFill = cout.fill();

   // set fill char to ' ' and enable right justification
   cout.fill(' ');
   cout.setf(ios::right,ios::adjustfield);

   // output the hour
   cout << setw(2) << hour << ':';

   // set fill char to '0' and output the minute
   cout.fill('0');
   cout << setw(2) << minute << "  ";

   // restore the fill char and the format flags
   cout.fill(currentFill);
   cout.setf(currentFlags);
}

int time24::getHour() const
{
   return hour;
}

int time24::getMinute() const
{
   return minute;
}

// compare hours and minutes
bool operator== (const time24& lhs, const time24& rhs)
{
	return lhs.hour == rhs.hour && lhs.minute == rhs.minute;
}

// convert the hour and minute values for each operand to
// minutes. compare lhs in minutes with rhs in minutes
bool operator<  (const time24& lhs, const time24& rhs)
{
	return (lhs.hour*60 + lhs.minute) < (rhs.hour*60 + rhs.minute);
}

// create an anonymous object with hour = lhs.hour + rhs.hour
// and minute = lhs.minute+rhs.minute.
time24 operator+ (const time24& lhs, const time24& rhs)
{
	return time24(lhs.hour+rhs.hour, lhs.minute+rhs.minute);
}

// create an anonymous object with hour = lhs.hour and
// minute = lhs.minute + min.
time24 operator+ (const time24& lhs, int min){
	return time24(lhs.hour, lhs.minute + min);
}

// return the value rhs + min that is computed by
//    time24 operator+ (const time24& lhs, int min)
time24 operator+ (int min, const time24& rhs)
{
	return rhs + min;
}

// using the < operator, check whether lhs < rhs is true. if so
// terminate; otherwise return a time24 result built
// using the constructor
time24 operator- (const time24& lhs, const time24& rhs)
{
	if (lhs < rhs)
		throw rangeError("time24 operator-: Cannot subtract later from earlier time");

	// convert each object to minutes and compute the
	// difference in minutes. return the time24 object
	// having 0 as hours and the value of the difference
	// as minutes
	return time24(0, (lhs.hour*60 + lhs.minute) -
						  (rhs.hour*60 + rhs.minute));
}

// implement += by using addition with operands *this and rhs
time24& time24::operator+= (const time24& rhs)
{
	// add *this and rhs using overloaded + operator
	*this = *this + rhs;

   // return a reference to the current object
	return *this;
}

// implement += by using addition with operands *this and min
time24& time24::operator+= (int min)
{
	// add *this and min using overloaded + operator
	*this = *this + min;

   // return a reference to the current object
   return *this;
}

// overload stream operator >>. input has the form
//   hour:minute
istream& operator>> (istream& istr, time24& t)
{
   char separatorChar;

   istr >> t.hour >> separatorChar >> t.minute;
   // make sure hour and minute are in range
   t.normalizeTime();

   // return the stream
   return istr;
}

// overload stream operator <<. output in the form
//   hour:minute
ostream& operator<< (ostream& ostr, const time24& t)
{
	// the implementation uses stream handling functions
	// not discussed in the book. consult your compiler
	// help system for details

   // save current format flags and fill character
   ios_base::fmtflags currentFlags = ostr.flags();
   char currentFill = ostr.fill();

   // set fill char to ' ' and enable right justification
   ostr.fill(' ');
   ostr.setf(ios::right,ios::adjustfield);

   // output the hour
   ostr << setw(2) << t.hour << ':';

   // set fill char to '0' and output the minute
   ostr.fill('0');
   ostr << setw(2) << t.minute;

   // restore the fill char and the format flags
   ostr.fill(currentFill);
   ostr.setf(currentFlags);

   return ostr;
}

#endif   // TIME24_CLASS
