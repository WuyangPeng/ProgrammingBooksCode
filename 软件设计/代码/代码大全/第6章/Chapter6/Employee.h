#pragma once

namespace Good
{
    class FullName;
    class TaxId;
    class JobClassification;
    class String;

    // չ�����ó������ӿڡ�
    class Employee
    {
    public:
        Employee();
        Employee(FullName name, String address, String workPhone, String homePhone, TaxId taxIdNumber, JobClassification jobClass);
        virtual ~Employee();

        FullName GetName() const;
        String GetAddress() const;
        String GetWorkPhone() const;
        String GetHomePhone() const;
        TaxId GetTaxIdNumber() const;
        JobClassification GetJobClassification() const;

    private:
    };
}

namespace Bad
{
    class FullName;
    class JobClassification;
    class String;
    class Address;
    class PhoneNumber;
    class SqlQuery;

    // ��ά��ʱ���ƻ�����ӿ�
    class Employee
    {
    public:
        FullName GetName() const;
        String GetAddress() const;
        String GetWorkPhone() const;

        bool IsJobClassificationValid(JobClassification jobClass);
        bool IsZipCodeValid(Address address);
        bool IsPhoneNumberValid(PhoneNumber phoneNumber);
        SqlQuery GetQueryToCreateNewEmployee() const;
        SqlQuery GetQueryToModifyEmployee() const;
        SqlQuery GetQueryToRetrieveEmployee() const;

    private:
    };
}

namespace Exposed
{
    class FullName;
    class TaxId;
    class JobClassification;
    class String
    {
    };

    // ��¶�����ڲ���ʵ��ϸ�ڡ�
    class Employee
    {
    public:
        Employee(FullName name, String address, String workPhone, String homePhone, TaxId taxIdNumber, JobClassification jobClass);

        FullName GetName() const;
        String GetAddress() const;

    private:
        String m_Name;
        String m_Address;
        int m_JobClass;
    };
}

namespace Hide
{
    class FullName;
    class String;
    class EmployeeImplementation;

    // �������ʵ��ϸ��
    class Employee
    {
    public:
        Employee();

        FullName GetName() const;
        String GetAddress() const;

    private:
        EmployeeImplementation* m_Implementation;
    };
}