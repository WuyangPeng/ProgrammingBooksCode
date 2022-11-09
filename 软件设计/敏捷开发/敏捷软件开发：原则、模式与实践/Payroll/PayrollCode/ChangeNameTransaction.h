#ifndef CHANGENAMETRANSACTION_H
#define CHANGENAMETRANSACTION_H

#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:
    virtual ~ChangeNameTransaction();
    ChangeNameTransaction(int empid, std::string name);
    virtual void Change(Employee&);

private:
    std::string itsName;
};

#endif
