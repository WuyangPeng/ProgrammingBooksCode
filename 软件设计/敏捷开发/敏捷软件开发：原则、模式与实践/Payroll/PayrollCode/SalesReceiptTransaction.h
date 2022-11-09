#ifndef SALESRECEIPTTRANSACTION_H
#define SALESRECEIPTTRANSACTION_H

#include "Date.h"
#include "Transaction.h"

class SalesReceiptTransaction : public Transaction
{
public:
    virtual ~SalesReceiptTransaction();
    SalesReceiptTransaction(const Date& saleDate, double amount, int empid);

    virtual void Execute();

private:
    int itsEmpid;
    Date itsSaleDate;
    double itsAmount;
};
#endif
