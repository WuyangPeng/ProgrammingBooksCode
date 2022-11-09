#include "DirectMethod.h"
#include "Paycheck.h"

DirectMethod::~DirectMethod()
{
}

DirectMethod::DirectMethod(std::string bank, std::string account)
    : itsBank(bank), itsAccount(account)
{
}

void DirectMethod::Pay(Paycheck& pc)
{
    pc.SetField("Disposition", "Direct");
}
