#pragma once

namespace Good
{
    class FullName;
    class TaxId;
    class JobClassification;
    class String;

    // 展现良好抽象的类接口。
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

    // 在维护时被破坏的类接口
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

    // 暴露了类内部的实现细节。
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

    // 隐藏类的实现细节
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