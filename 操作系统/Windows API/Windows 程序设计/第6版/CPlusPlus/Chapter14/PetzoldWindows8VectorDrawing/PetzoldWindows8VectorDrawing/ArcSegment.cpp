#include "pch.h"
#include "ArcSegment.h"

using namespace PetzoldWindows8VectorDrawing;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

void ArcSegment::Set(Point center, float radius, Point point1, Point point2)
{
    this->center = center;
    this->radius = radius;
    this->point1 = point1;
    this->point2 = point2;
    this->angle1 = (float)(atan2(point1.Y - center.Y, point1.X - center.X));
    this->angle2 = (float)(atan2(point2.Y - center.Y, point2.X - center.X));
}

void ArcSegment::GetAllX(float y, IVector<float>^ xCollection)
{
    double sqrtArg = radius * radius - pow(y - center.Y, 2);

    if (sqrtArg >= 0)
    {
        float squareRoot = (float)sqrt(sqrtArg);
        TryY(y, center.X + squareRoot, xCollection);
        TryY(y, center.X - squareRoot, xCollection);
    }
}

void ArcSegment::TryY(float y, float x, IVector<float>^ xCollection)
{
    float angle = (float)atan2(y - center.Y, x - center.X);

    if ((angle1 < angle2 && (angle1 <= angle && angle < angle2)) ||
        (angle1 > angle2 && (angle1 <= angle || angle < angle2)))
    {
        xCollection->Append(x);
    }
}
