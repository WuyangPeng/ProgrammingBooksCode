#ifndef GEOMETRY_RAY_H
#define GEOMETRY_RAY_H

#include "geometry/LinearObject.h"

class Ray : public LinearObject
{
public:
    Ray(const Point& p1, const Point& p2);

    virtual bool IsOn(const Point&) const;
};

#endif
