#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H

#include "geometry/point.h"

class Line
{
public:
    Line(const Point& p1, const Point& p2);

    double GetSlope() const;
    double GetIntercept() const;  // Y Intercept
    Point GetP1() const
    {
        return itsP1;
    }

    Point GetP2() const
    {
        return itsP2;
    }

    virtual bool IsOn(const Point&) const;

private:
    Point itsP1;
    Point itsP2;
};

#endif