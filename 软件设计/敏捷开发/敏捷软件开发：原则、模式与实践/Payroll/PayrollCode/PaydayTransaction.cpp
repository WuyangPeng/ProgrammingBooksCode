#include "Date.h"
#include "Employee.h"
#include "Paycheck.h"
#include "PaydayTransaction.h"
#include "PayrollDatabase.h"

#include <list>

extern PayrollDatabase GpayrollDatabase;

PaydayTransaction::~PaydayTransaction()
{
}

PaydayTransaction::PaydayTransaction(Date payDate)
    : itsPayDate(payDate)
{
}

void PaydayTransaction::Execute()
{
    std::list<int> empIds;
    GpayrollDatabase.GetAllEmployeeIds(empIds);

    std::list<int>::iterator i = empIds.begin();
    for (; i != empIds.end(); i++)
    {
        int empId = *i;
        if (Employee* e = GpayrollDatabase.GetEmployee(empId))
        {
            if (e->IsPayDate(itsPayDate))
            {
                Paycheck* pc = new Paycheck(e->GetPayPeriodStartDate(itsPayDate),
                                            itsPayDate);
                itsPaychecks[empId] = pc;
                e->Payday(*pc);
            }
        }
    }
}

Paycheck* PaydayTransaction::GetPaycheck(int empId)
{
    return itsPaychecks[empId];
}

int PaydayTransaction::GetPaycheckCount() const
{
    return static_cast<int>(itsPaychecks.size());
}
