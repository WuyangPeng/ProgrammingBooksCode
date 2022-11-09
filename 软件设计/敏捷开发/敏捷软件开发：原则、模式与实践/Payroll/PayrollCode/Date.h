// Copyright (C) 1995 by R. C. M. Consulting Inc
// All Rights Reserved.

#ifndef COMPONENTS_DATE_H
#define COMPONENTS_DATE_H

#include <time.h> /* unix and borland compatible. */
#include <iostream>
#include <string>

class Date
{
public:
    enum DayOfWeek
    {
        sunday = 0,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday
    };
    // Canonical Form
    Date();
    Date(int month, int day, int year);
    Date(const Date&);
    virtual ~Date();
    Date& operator=(const Date&);

    // Accessors
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;
    DayOfWeek GetDayOfWeek() const;
    std::string GetDayOfWeekName() const;

    // Input & Output
    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);

    // Arithmetic and comparison operators
    int operator==(const Date&) const;
    int operator!=(const Date&) const;
    int operator<(const Date&) const;
    int operator>(const Date&) const;
    int operator<=(const Date&) const;
    int operator>=(const Date&) const;
    friend Date operator+(int, const Date&);
    friend Date operator+(const Date&, int);
    Date operator-(int) const;
    int operator-(const Date&) const;
    Date& operator+=(int);
    Date& operator-=(int);
    Date& operator++();
    Date operator++(int);  // postfix
    Date& operator--();
    Date operator--(int);  // postfix

    static bool IsBetween(const Date& theDate, const Date& startDate, const Date& endDate)
    {
        return (theDate >= startDate) && (theDate <= endDate);
    }

private:
    time_t itsTime;
    tm itsTimeStruct;

    static long secondsPerDay;
};

#endif
