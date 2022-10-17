#ifndef GEOMETRY_LINE_OBJECT_H
#define GEOMETRY_LINE_OBJECT_H

#include "geometry/point.h"

class LinearObject
{
public:
    LinearObject(const Point& p1, const Point& p2);

    double GetSlope() const;
    double GetIntercept() const;
    Point GetP1() const
    {
        return itsP1;
    }

    Point GetP2() const
    {
        return itsP2;
    }

    virtual bool IsOn(const Point&) const = 0;  // abstract

private:
    Point itsP1;
    Point itsP2;
};

#endif
