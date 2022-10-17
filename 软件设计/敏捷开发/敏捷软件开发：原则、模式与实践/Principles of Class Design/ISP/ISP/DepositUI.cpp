#include "DepositUI.h"

UI Gui;  // global object;

void f()
{
    DepositTransaction dt(Gui);
}

// in some module that gets linked in
// to the rest of the app.
static UI Lui;  // non-global object
DepositUI& GdepositUI = Lui;
WithdrawalUI& GwithdrawalUI = Lui;
TransferUI& GtransferUI = Lui;

// In the depositTransaction.h

class WithDrawalTransaction : public Transaction
{
public:
    virtual void Execute()
    {
        // ...
        GwithdrawalUI.RequestWithDrawalAmount();
        // ...
    }
};

void g(DepositUI&, TransferUI&);

void g(UI&);

// g(ui, ui);

class Service
{
public:
    virtual ~Service() noexcept = default;
};

class NewService : Service
{
};

void Client(Service* s)
{
    if (NewService* ns = dynamic_cast<NewService*>(s))
    {
        // use the new service interface
    }
}