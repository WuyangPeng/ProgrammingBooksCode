#pragma once

class PrintDriver
{
public:
    PrintDriver(void);
    virtual void print(void)=0;
public:
    ~PrintDriver(void);
};