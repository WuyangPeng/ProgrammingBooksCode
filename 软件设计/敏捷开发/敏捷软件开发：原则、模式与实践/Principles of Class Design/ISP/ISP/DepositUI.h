#pragma once

#include "TransferUI.h"
#include "WithdrawalUI.h"

class Transaction
{
};

class DepositUI
{
public:
    virtual void RequestDepositAmount() = 0;
};

class DepositTransaction : public Transaction
{
public:
    DepositTransaction(DepositUI& ui)
        : itsDepositUI(ui)
    {
    }

    virtual void Execute()
    {
        // ...
        itsDepositUI.RequestDepositAmount();
        // ...
    }

private:
    DepositUI& itsDepositUI;
};

class WithdrawalTransaction : public Transaction
{
public:
    WithdrawalTransaction(WithdrawalUI& ui)
        : itsWithdrawalUI(ui)
    {
    }

    virtual void Execute()
    {
        // ...
        itsWithdrawalUI.RequestWithDrawalAmount();
        // ...
    }

private:
    WithdrawalUI& itsWithdrawalUI;
};

class TransferTransaction : public Transaction
{
public:
    TransferTransaction(TransferUI& ui)
        : itsTransferUI(ui)
    {
    }

    virtual void Execute()
    {
        // ...
        itsTransferUI.RequestTransferAmount();
        // ...
    }

private:
    TransferUI& itsTransferUI;
};

class UI : public DepositUI, public WithdrawalUI, public TransferUI
{
public:
    virtual void RequestDepositAmount();
    virtual void RequestWithDrawalAmount();
    virtual void RequestTransferAmount();
};
