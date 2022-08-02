#pragma once

class Drawing
{
public:
    Drawing(void);
public:
    ~Drawing(void);
    virtual void drawLine( double, double, double, double)=0;
    virtual void drawCircle( double, double, double)=0;
};
