#ifndef PAYDAYTRANSACTION_H
#define PAYDAYTRANSACTION_H

#include "Date.h"
#include "Transaction.h"

#include <map>

class Paycheck;

class PaydayTransaction : public Transaction
{
public:
    virtual ~PaydayTransaction();
    PaydayTransaction(Date payDate);
    virtual void Execute();
    Paycheck* GetPaycheck(int empId);
    int GetPaycheckCount() const;

private:
    Date itsPayDate;
    std::map<int, Paycheck*> itsPaychecks;
};

#endif
