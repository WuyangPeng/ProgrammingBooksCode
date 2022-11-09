#ifndef CHANGEDIRECTTRANSACTION_H
#define CHANGEDIRECTTRANSACTION_H

#include "ChangeMethodTransaction.h"
#include <string>

class ChangeDirectTransaction : public ChangeMethodTransaction
{
public:
    virtual ~ChangeDirectTransaction();
    ChangeDirectTransaction(int empid, std::string bank, std::string account);
    virtual PaymentMethod* GetMethod() const;

private:
    std::string itsBank;
    std::string itsAccount;
};
#endif
