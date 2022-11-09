#include "Date.h"

#include <ctime>

long Date::secondsPerDay = 60L * 60L * 24L;

Date::Date()
{
    time_t now = time(NULL);
    localtime_s(&itsTimeStruct, &now);
    itsTimeStruct.tm_sec = 0;
    itsTimeStruct.tm_min = 0;
    itsTimeStruct.tm_hour = 12;
    itsTime = mktime(&itsTimeStruct);
}

Date::Date(int month, int day, int year)
{
    //bzero(reinterpret_cast<char*>(&itsTimeStruct), sizeof(itsTimeStruct));
    itsTimeStruct = {};
    itsTimeStruct.tm_mon = month - 1;
    itsTimeStruct.tm_mday = day;
    itsTimeStruct.tm_year = year - 1900;
    itsTimeStruct.tm_sec = 0;
    itsTimeStruct.tm_min = 0;
    itsTimeStruct.tm_hour = 12;
    itsTime = mktime(&itsTimeStruct);
    localtime_s(&itsTimeStruct, &itsTime);
}

Date::Date(const Date& theDate)
{
    *this = theDate;
}

Date::~Date()
{
}

Date& Date::operator=(const Date& theDate)
{
    itsTime = theDate.itsTime;

    localtime_s(&itsTimeStruct, &itsTime);
    return *this;
}

int Date::GetMonth() const
{
    return itsTimeStruct.tm_mon + 1;
}
int Date::GetDay() const
{
    return itsTimeStruct.tm_mday;
}
int Date::GetYear() const
{
    return itsTimeStruct.tm_year + 1900;
}

Date::DayOfWeek Date::GetDayOfWeek() const
{
    return (DayOfWeek)(itsTimeStruct.tm_wday);
}

std::string Date::GetDayOfWeekName() const
{
    std::string retval;
    switch (GetDayOfWeek())
    {
    case sunday:
        retval = "Sunday";
        break;
    case monday:
        retval = "Monday";
        break;
    case tuesday:
        retval = "Tuesday";
        break;
    case wednesday:
        retval = "Wednesday";
        break;
    case thursday:
        retval = "Thursday";
        break;
    case friday:
        retval = "Friday";
        break;
    case saturday:
        retval = "Saturday";
        break;
    }
    return retval;
}

std::ostream& operator<<(std::ostream& o, const Date& theDate)
{
    o << theDate.GetMonth() << '/'
      << theDate.GetDay() << '/'
      << theDate.GetYear();
    return o;
}

std::istream& operator>>(std::istream& i, Date& theDate)
{
    int month, day, year;
    char slash;
    i >> month >> slash >> day >> slash >> year;
    Date tmp(month, day, year);
    theDate = tmp;
    return i;
}

int Date::operator==(const Date& theDate) const
{
    return itsTime == theDate.itsTime;
}

int Date::operator!=(const Date& theDate) const
{
    return itsTime != theDate.itsTime;
}

int Date::operator<(const Date& theDate) const
{
    return itsTime < theDate.itsTime;
}

int Date::operator>(const Date& theDate) const
{
    return itsTime > theDate.itsTime;
}

int Date::operator<=(const Date& theDate) const
{
    return itsTime <= theDate.itsTime;
}

int Date::operator>=(const Date& theDate) const
{
    return itsTime >= theDate.itsTime;
}

Date operator+(int days, const Date& theDate)
{
    Date retval = theDate;
    retval += days;
    return retval;
}

Date operator+(const Date& theDate, int days)
{
    return days + theDate;
}

Date Date::operator-(int days) const
{
    Date retval = *this;
    retval -= days;
    return retval;
}

int Date::operator-(const Date& theDate) const
{
    return static_cast<int>((itsTime - theDate.itsTime) / secondsPerDay);
}

Date& Date::operator+=(int days)
{
    itsTime += days * secondsPerDay;
    localtime_s(&itsTimeStruct, &itsTime);

    return *this;
}

Date& Date::operator-=(int days)
{
    itsTime -= days * secondsPerDay;
    localtime_s(&itsTimeStruct, &itsTime);

    return *this;
}

Date& Date::operator++()
{
    return ((*this) += 1);
}

Date Date::operator++(int)  // postfix
{
    Date retval = *this;
    (*this) += 1;
    return retval;
}

Date& Date::operator--()
{
    return ((*this) -= 1);
}

Date Date::operator--(int)  // postfix
{
    Date retval = *this;
    (*this) -= 1;
    return retval;
}
