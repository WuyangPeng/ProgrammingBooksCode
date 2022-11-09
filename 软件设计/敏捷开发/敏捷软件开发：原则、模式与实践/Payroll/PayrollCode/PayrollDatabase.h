#ifndef PAYROLLDATABASE_H
#define PAYROLLDATABASE_H

#include <list>
#include <map>

class Employee;

class PayrollDatabase
{
public:
    virtual ~PayrollDatabase();
    Employee* GetEmployee(int empId);
    void AddEmployee(int empid, Employee*);
    void DeleteEmployee(int empid);
    void AddUnionMember(int memberId, Employee*);
    Employee* GetUnionMember(int memberId);
    void RemoveUnionMember(int memberId);
    void clear();
    void GetAllEmployeeIds(std::list<int>&);

private:
    std::map<int, Employee*> itsEmployees;
    std::map<int, int> itsUnionMembers;
};

#endif
