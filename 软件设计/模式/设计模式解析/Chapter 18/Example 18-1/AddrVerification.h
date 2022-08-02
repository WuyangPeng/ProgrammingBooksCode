#pragma once
#include "Observer.h"
#include "Customer.h"

class AddrVerification : public Observer
{
public:
    AddrVerification(void);
    void update( Customer *myCust);
public:
    ~AddrVerification(void);
};