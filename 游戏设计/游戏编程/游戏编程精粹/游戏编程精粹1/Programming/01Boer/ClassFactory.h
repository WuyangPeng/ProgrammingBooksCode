#pragma once

class BaseClass;

class ClassFactory
{
    BaseClass* CreateObject(int id);
};

class BaseClass
{
public:
    BaseClass() noexcept = default;
    virtual ~BaseClass() = default;

    void Init()
    {
    }
};

class Class1 : public BaseClass
{
public:
    Class1() noexcept = default;
};

class Class2 : public BaseClass
{
public:
    Class2() noexcept = default;
};

class Class3 : public BaseClass
{
public:
    Class3() noexcept = default;
};