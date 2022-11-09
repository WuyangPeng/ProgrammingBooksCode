#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include "PaymentMethod.h"
#include <string>

class DirectMethod : public PaymentMethod
{
public:
    virtual ~DirectMethod();
    DirectMethod(std::string bank, std::string account);
    std::string GetBank()
    {
        return itsBank;
    }
    std::string GetAccount()
    {
        return itsAccount;
    }

    virtual void Pay(Paycheck&);

private:
    std::string itsBank;
    std::string itsAccount;
};
#endif
