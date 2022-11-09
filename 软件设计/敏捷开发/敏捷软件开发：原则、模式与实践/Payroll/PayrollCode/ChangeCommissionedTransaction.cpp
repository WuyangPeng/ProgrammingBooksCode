#include "BiweeklySchedule.h"
#include "ChangeCommissionedTransaction.h"
#include "CommissionedClassification.h"

ChangeCommissionedTransaction::~ChangeCommissionedTransaction()
{
}

ChangeCommissionedTransaction::ChangeCommissionedTransaction(int empid, double salary, double rate)
    : ChangeClassificationTransaction(empid), itsSalary(salary), itsRate(rate)
{
}

PaymentSchedule* ChangeCommissionedTransaction::GetSchedule() const
{
    return new BiweeklySchedule();
}

PaymentClassification* ChangeCommissionedTransaction::GetClassification() const
{
    return new CommissionedClassification(itsSalary, itsRate);
}
