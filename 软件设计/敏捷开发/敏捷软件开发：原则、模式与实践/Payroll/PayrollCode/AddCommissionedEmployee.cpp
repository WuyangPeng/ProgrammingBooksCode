#include "AddCommissionedEmployee.h"
#include "BiweeklySchedule.h"
#include "CommissionedClassification.h"

AddCommissionedEmployee::~AddCommissionedEmployee()
{
}

AddCommissionedEmployee::AddCommissionedEmployee(int empid, std::string name, std::string address, double salary, double commissionRate)
    : AddEmployeeTransaction(empid, name, address), itsSalary(salary), itsCommissionRate(commissionRate)
{
}

PaymentClassification* AddCommissionedEmployee::GetClassification() const
{
    return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule* AddCommissionedEmployee::GetSchedule() const
{
    return new BiweeklySchedule();
}
