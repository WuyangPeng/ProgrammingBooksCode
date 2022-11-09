#ifndef ADDSALARIEDEMPLOYEE_H
#define ADDSALARIEDEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
public:
    virtual ~AddSalariedEmployee();
    AddSalariedEmployee(int empid, std::string name, std::string address, double salary);
    PaymentClassification* GetClassification() const;
    PaymentSchedule* GetSchedule() const;

private:
    double itsSalary;
};
#endif
