#pragma once

class Rectangle
{
public:
    Rectangle(double, double, double, double);
    virtual void drawLine(double, double, double, double)=0;
    void draw();
public:
    ~Rectangle(void);
private:
    double _x1, _x2, _y1, _y2;
};