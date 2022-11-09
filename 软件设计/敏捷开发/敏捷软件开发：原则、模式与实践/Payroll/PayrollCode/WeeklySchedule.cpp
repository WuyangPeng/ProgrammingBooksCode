#include "Date.h"
#include "WeeklySchedule.h"

WeeklySchedule::~WeeklySchedule()
{
}

bool WeeklySchedule::IsPayDate(const Date& theDate) const
{
    return theDate.GetDayOfWeek() == Date::friday;
}

Date WeeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return payPeriodEndDate - 6;  // The previous Saturday.
}
