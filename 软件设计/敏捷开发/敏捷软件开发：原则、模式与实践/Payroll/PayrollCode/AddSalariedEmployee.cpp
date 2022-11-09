#include "AddSalariedEmployee.h"
#include "MonthlySchedule.h"
#include "SalariedClassification.h"

AddSalariedEmployee::~AddSalariedEmployee()
{
}

AddSalariedEmployee::AddSalariedEmployee(int empid, std::string name, std::string address, double salary)
    : AddEmployeeTransaction(empid, name, address), itsSalary(salary)
{
}

PaymentClassification* AddSalariedEmployee::GetClassification() const
{
    return new SalariedClassification(itsSalary);
}

PaymentSchedule* AddSalariedEmployee::GetSchedule() const
{
    return new MonthlySchedule();
}
