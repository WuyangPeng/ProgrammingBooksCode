//DISPLAY 15.2 Interface for the Base Class Employee
//This is the header file employee.h.
//This is the interface for the class Employee.
//This is primarily intended to be used as a base class to derive
//classes for different kinds of employees.
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

namespace employeessavitch
{
    class Employee
    {
    public:
        Employee( );
        Employee(string theName, string theSSN);
        string getName( ) const;
        string getSSN( ) const;
        double getNetPay( ) const;
        void setName(string newName);
        void setSSN(string newSSN);
        void setNetPay(double newNetPay);
        void printcheck( ) const;
    private:
        string name;
        string ssn;
        double netPay;
    };

}//employeessavitch

#endif //EMPLOYEE_H
