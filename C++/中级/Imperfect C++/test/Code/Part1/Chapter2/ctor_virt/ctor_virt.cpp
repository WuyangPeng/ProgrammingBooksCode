/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <iostream>

class Parent
{
public:
    Parent()
    {
        Method();
    }
    virtual void Method() = 0;
};

class Child
    : public Parent
{
public:
    Child()
    {
        Method();
    }
    virtual void Method()
    {
    }
};

int main()
{
    using namespace std;

    Child   child;
    
    cout << "Hello World, this is CodeWarrior!" << endl;
    
    return 0;
}

