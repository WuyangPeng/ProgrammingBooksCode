#include "ChangeDirectTransaction.h"
#include "DirectMethod.h"

ChangeDirectTransaction::~ChangeDirectTransaction()
{
}

ChangeDirectTransaction::ChangeDirectTransaction(int empid, std::string bank, std::string account)
    : ChangeMethodTransaction(empid), itsBank(bank), itsAccount(account)
{
}

PaymentMethod* ChangeDirectTransaction::GetMethod() const
{
    return new DirectMethod(itsBank, itsAccount);
}
