#pragma once
#include 
#include 
#include "Observer.h"
using namespace std;

class Customer
{
public:
    Customer(void);
    
    void attach( Observer *myObserver);
    void detach( Observer *myObserver);
    string* getState();
    void notifyObs();
private:
    vector myObs;
public:
    ~Customer(void);
};