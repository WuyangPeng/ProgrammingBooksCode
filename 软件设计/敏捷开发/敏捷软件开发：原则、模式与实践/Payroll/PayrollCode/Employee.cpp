#include "Employee.h"
#include "NoAffiliation.h"
#include "Paycheck.h"
#include "PaymentClassification.h"
#include "PaymentMethod.h"
#include "PaymentSchedule.h"

Employee::~Employee()
{
    delete itsClassification;
    delete itsSchedule;
    delete itsPaymentMethod;
}

Employee::Employee(int empid, std::string name, std::string address)
    : itsEmpid(empid), itsName(name), itsAddress(address), itsAffiliation(new NoAffiliation()), itsClassification(0), itsSchedule(0), itsPaymentMethod(0)
{
}

void Employee::SetName(std::string name)
{
    itsName = name;
}

void Employee::SetAddress(std::string address)
{
    itsAddress = address;
}

void Employee::SetClassification(PaymentClassification* pc)
{
    delete itsClassification;
    itsClassification = pc;
}

void Employee::SetSchedule(PaymentSchedule* ps)
{
    delete itsSchedule;
    itsSchedule = ps;
}

void Employee::SetMethod(PaymentMethod* pm)
{
    delete itsPaymentMethod;
    itsPaymentMethod = pm;
}

void Employee::SetAffiliation(Affiliation* af)
{
    delete itsAffiliation;
    itsAffiliation = af;
}

bool Employee::IsPayDate(const Date& payDate) const
{
    return itsSchedule->IsPayDate(payDate);
}

Date Employee::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return itsSchedule->GetPayPeriodStartDate(payPeriodEndDate);
}

void Employee::Payday(Paycheck& pc)
{
    double grossPay = itsClassification->CalculatePay(pc);
    double deductions = itsAffiliation->CalculateDeductions(pc);
    double netPay = grossPay - deductions;
    pc.SetGrossPay(grossPay);
    pc.SetDeductions(deductions);
    pc.SetNetPay(netPay);
    itsPaymentMethod->Pay(pc);
}
