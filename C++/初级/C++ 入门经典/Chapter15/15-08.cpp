//DISPLAY 15.8 Using Derived Classes
#include <iostream>
#include "hourlyemployee.h"
#include "salariedemployee.h"
using std::cout;
using std::endl;
using namespace employeessavitch;

int main( )
{
    HourlyEmployee joe;
    joe.setName("Mighty Joe");
    joe.setSSN("123-45-6789");
    joe.setRate(20.50);
    joe.setHours(40);
    cout << "Check for " << joe.getName( )
         << " for " << joe.getHours( ) << " hours.\n";
    joe.printCheck( );
    cout << endl;

    SalariedEmployee boss("Mr. Big Shot", "987-65-4321", 10500.50);
    cout << "Check for " << boss.getName( ) << endl;
    boss.printCheck( );

    return 0;
}
