#ifndef TIMECARDTRANSACTION_H
#define TIMECARDTRANSACTION_H

#include "Date.h"
#include "Transaction.h"

class TimeCardTransaction : public Transaction
{
public:
    virtual ~TimeCardTransaction();
    TimeCardTransaction(const Date& date, double hours, int empid);

    virtual void Execute();

private:
    int itsEmpid;
    Date itsDate;
    double itsHours;
};
#endif
