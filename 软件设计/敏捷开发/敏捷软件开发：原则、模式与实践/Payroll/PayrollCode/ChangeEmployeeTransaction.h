
#ifndef CHANGEEMPLOYEETRANSACTION_H
#define CHANGEEMPLOYEETRANSACTION_H

#include "Employee.h"
#include "Transaction.h"

class ChangeEmployeeTransaction : public Transaction
{
public:
    ChangeEmployeeTransaction(int empid);
    virtual ~ChangeEmployeeTransaction();
    virtual void Execute();
    virtual void Change(Employee&) = 0;

protected:
    int GetEmpId()
    {
        return itsEmpId;
    }

private:
    int itsEmpId;
};

#endif
