#ifndef ADDHOURLYEMPLOYEE_H
#define ADDHOURLYEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
public:
    virtual ~AddHourlyEmployee();
    AddHourlyEmployee(int empid, std::string name, std::string address, double hourlyRate);
    PaymentClassification* GetClassification() const;
    PaymentSchedule* GetSchedule() const;

private:
    double itsHourlyRate;
};
#endif
