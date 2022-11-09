#ifndef PAYCHECK_H
#define PAYCHECK_H

#include "Date.h"

#include <map>
#include <string>

class Paycheck
{
public:
    virtual ~Paycheck();
    Paycheck(const Date& payPeriodStart, const Date& payPeriodEnd);

    void SetGrossPay(double grossPay);
    void SetDeductions(double deductions);
    void SetNetPay(double netPay);

    double GetGrossPay() const
    {
        return itsGrossPay;
    }
    double GetDeductions() const
    {
        return itsDeductions;
    }
    double GetNetPay() const
    {
        return itsNetPay;
    }

    Date GetPayPeriodEndDate() const
    {
        return itsPayPeriodEndDate;
    }
    Date GetPayPeriodStartDate() const
    {
        return itsPayPeriodStartDate;
    }
    void SetField(std::string name, std::string value);
    std::string GetField(std::string name);

private:
    Date itsPayPeriodStartDate;
    Date itsPayPeriodEndDate;
    double itsGrossPay;
    double itsNetPay;
    double itsDeductions;
    std::map<std::string, std::string> itsFields;
};
#endif
