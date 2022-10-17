#pragma once

#include "DepositUI.h"
#include "TransferUI.h"
#include "WithdrawalUI.h"

class UIGlobals
{
public:
    static WithdrawalUI& withdrawal;
    static DepositUI& deposit;
    static TransferUI& transfer;
};
