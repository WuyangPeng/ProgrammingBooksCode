#pragma once
#include "Observer.h"
#include "Customer.h"

class WelcomeLetter : public Observer
{
public:
    WelcomeLetter(void);
    void update( Customer *myCust);
public:
    ~WelcomeLetter(void);
};