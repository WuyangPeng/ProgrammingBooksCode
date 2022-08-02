/* /////////////////////////////////////////////////////////////////////////////
 * File:        date_property_test.cpp
 *
 * Purpose:     Implementation file for the date_property_test project.
 *
 * Created:     21st October 2003
 * Updated:     22nd October 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <time.h>

#include <stlsoft.h>

#include <stdexcept>

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
struct tm
{
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

struct Date
{
public:
    enum WeekDay { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

private:
    Date()
        : m_time(time(NULL))
    {}
    explicit Date(time_t time)
        : m_time(time)
    {}
public:
    Date(Date const &rhs)
        : m_time(rhs.m_time)
    {}
    Date &operator =(Date const &rhs)
    {
        m_time = rhs.m_time;

        return *this;
    }

// Property methods
public:
    WeekDay     propget_DayOfWeek() const;
    int         propget_DayOfMonth() const;
    void        propset_DayOfMonth(int day);
    int         propget_Year() const;
    static Date propget_Now();

// Properties
public:
#if defined(__STLSOFT_COMPILER_IS_BORLAND)
    __property WeekDay DayOfWeek = {read = propget_DayOfWeek};
//  __property Date Now = {read = propget_Now};
#elif defined(__STLSOFT_COMPILER_IS_INTEL) || \
      defined(__STLSOFT_COMPILER_IS_MSVC)
    __declspec(property(get = propget_DayOfWeek)) WeekDay DayOfWeek;
    __declspec(property(get = propget_DayOfMonth, put = propset_DayOfMonth)) int DayOfMonth;
//  static __declspec(property(get = propget_Now)) Date Now;
#else
# error Properties not supported by your compiler
#endif // compiler

// Implementation
private:
    bool ValidateDay(struct tm const &tm, int day);

private:
    time_t  m_time;
};

/* ////////////////////////////////////////////////////////////////////////// */

Date::WeekDay Date::propget_DayOfWeek() const
{
    return static_cast<WeekDay>(localtime(&m_time)->tm_wday);
}

int Date::propget_DayOfMonth() const
{
    return localtime(&m_time)->tm_mday;
}

void Date::propset_DayOfMonth(int day)
{
    struct tm   tm = *localtime(&m_time);

    if(!ValidateDay(tm, day))
    {
        throw std::out_of_range("The given day is not valid for the current month");
    }

    tm.tm_mday = day;

    time_t  t = mktime(&tm);

    if(static_cast<time_t>(-1) == t)
    {
        throw std::out_of_range("The given day is not valid for the current month");
    }

    m_time = t;
}

int Date::propget_Year() const
{
    return localtime(&m_time)->tm_year;
}

/* static */ Date Date::propget_Now()
{
    return Date();
}

bool Date::ValidateDay(struct tm const &tm, int day)
{
    // NOTE: This function does *not* do leap year calculations!
    int minDay  =   1;
    int maxDay  =   31;

    switch(tm.tm_mon)
    {
        case    8: // Sep
        case    3: // Apr
        case    5: // June
        case    10: // Nov
            maxDay = 30;
            break;
        case    1: // Feb
            maxDay = 28;
            break;
    }

    return !(day < minDay) && !(maxDay < day);
}


/* ////////////////////////////////////////////////////////////////////////// */

#define tm  Date

int main(int /* argc */, char ** /*argv*/)
{
    puts("date_property_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    Date            date    =   Date::propget_Now();
    Date::WeekDay   weekDay =   date.DayOfWeek;

    try
    {
        for(;;)
        {
            date.DayOfMonth = date.DayOfMonth + 1;

            weekDay =   date.DayOfWeek;
        }
    }
    catch(std::exception &x)
    {
        printf("%s\n", x.what());
    }

    struct tm   date2   =   tm::propget_Now();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
