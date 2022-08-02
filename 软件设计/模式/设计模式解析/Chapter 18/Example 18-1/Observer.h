#pragma once
class Customer;

class Observer
{
public:
    Observer(void);
    virtual void update( Customer *myCust)= 0;
public:
    ~Observer(void);
};