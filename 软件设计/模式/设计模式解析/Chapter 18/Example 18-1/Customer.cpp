#include "Customer.h"

Customer::Customer(void)
{
}

Customer::~Customer(void)
{
}

void Customer::attach( Observer *myObserver)
{
    myObs.push_back( myObserver);
}

void Customer::detach( Observer *myObserver)
{
    for (int i= 0; i< myObs.size(); i++)
    {
        if (myObs[i]== myObserver)
        {
            myObs.erase(myObs.begin()+i);
            return;
        }
    }
}

void Customer::notifyObs()
{
    // set arg to something that helps
    // tell the Observers what happened
    for (int i= 0; i< myObs.size(); i++)
    {
        myObs[i]->update(this);
    }
}

string* Customer::getState()
{
    string *state= new string;

    // set state

    return 0l;
}