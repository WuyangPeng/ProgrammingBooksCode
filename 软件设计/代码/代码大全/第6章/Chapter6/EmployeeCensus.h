#pragma once

namespace Bad
{
    class ListContainer
    {
    };

    class Employee;

    // 混合了不同层次抽象的类接口
    class EmployeeCensus : public ListContainer
    {
    public:
        // 这些子程序的抽象在“雇员”这一层次上。
        void AddEmployee(Employee employee);
        void RemoveEmployee(Employee employee);

        // 这些子程序的抽象在“列表”这一层次上。
        Employee NextItemInList();
        Employee FirstItem();
        Employee LastItem();
    };
}

namespace Good
{
    class ListContainer
    {
    };
    class Employee;

    // 有着一致抽象层次的类接口
    class EmployeeCensus
    {
    public:
        // 所有这些子程序的抽象现在都是在“雇员”这一层次上了。
        void AddEmployee(Employee employee);
        void RemoveEmployee(Employee employee);
        Employee NextEmployeeInList();
        Employee FirstEmployee();
        Employee LastEmployee();

    private:
        // 使用ListContainer库，这一实现细节现在已经被隐藏起来了。
        ListContainer m_EmployeeList;
    };
}