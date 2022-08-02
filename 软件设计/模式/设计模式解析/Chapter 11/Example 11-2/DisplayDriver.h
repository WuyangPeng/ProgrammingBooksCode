#pragma once

class DisplayDriver
{
public:
    DisplayDriver(void);
    virtual void draw(void)=0;
public:
    ~DisplayDriver(void);
};