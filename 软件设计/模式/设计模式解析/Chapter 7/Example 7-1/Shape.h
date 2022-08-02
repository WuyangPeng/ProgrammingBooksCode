#pragma once

class Shape
{
public:
    Shape(void);
    void virtual display()= 0;
public:
    ~Shape(void);
};