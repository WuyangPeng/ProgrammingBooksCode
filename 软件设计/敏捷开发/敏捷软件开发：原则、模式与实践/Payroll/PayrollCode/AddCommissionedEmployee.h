#ifndef ADDCOMMISSIONEDEMPLOYEE_H
#define ADDCOMMISSIONEDEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
public:
    virtual ~AddCommissionedEmployee();
    AddCommissionedEmployee(int empid, std::string name, std::string address, double salary, double commissionRate);
    PaymentClassification* GetClassification() const;
    PaymentSchedule* GetSchedule() const;

private:
    double itsSalary;
    double itsCommissionRate;
};
#endif
