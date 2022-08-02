#pragma once

namespace Bad
{
    class ListContainer
    {
    };

    class Employee;

    // ����˲�ͬ��γ������ӿ�
    class EmployeeCensus : public ListContainer
    {
    public:
        // ��Щ�ӳ���ĳ����ڡ���Ա����һ����ϡ�
        void AddEmployee(Employee employee);
        void RemoveEmployee(Employee employee);

        // ��Щ�ӳ���ĳ����ڡ��б���һ����ϡ�
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

    // ����һ�³����ε���ӿ�
    class EmployeeCensus
    {
    public:
        // ������Щ�ӳ���ĳ������ڶ����ڡ���Ա����һ������ˡ�
        void AddEmployee(Employee employee);
        void RemoveEmployee(Employee employee);
        Employee NextEmployeeInList();
        Employee FirstEmployee();
        Employee LastEmployee();

    private:
        // ʹ��ListContainer�⣬��һʵ��ϸ�������Ѿ������������ˡ�
        ListContainer m_EmployeeList;
    };
}