#include "ChangeHourlyTransaction.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"

ChangeHourlyTransaction::~ChangeHourlyTransaction()
{
}

ChangeHourlyTransaction::ChangeHourlyTransaction(int empid, double hourlyRate)
    : ChangeClassificationTransaction(empid), itsHourlyRate(hourlyRate)
{
}

PaymentSchedule* ChangeHourlyTransaction::GetSchedule() const
{
    return new WeeklySchedule();
}

PaymentClassification* ChangeHourlyTransaction::GetClassification() const
{
    return new HourlyClassification(itsHourlyRate);
}
