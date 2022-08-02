#include "pch.h"
#include "RoundCappedLine.h"

using namespace PetzoldWindows8VectorDrawing;

using namespace DirectX;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

RoundCappedLine::RoundCappedLine()
{
    lineSegment1 = ref new LineSegment();
    arcSegment1 = ref new ArcSegment();
    lineSegment2 = ref new LineSegment();
    arcSegment2 = ref new ArcSegment();
}

void RoundCappedLine::Set(Point point1, Point point2, float radius)
{
    XMVECTOR pt1 = XMVectorSet(point1.X, point1.Y, 0, 0);
    XMVECTOR pt2 = XMVectorSet(point2.X, point2.Y, 0, 0);
    XMVECTOR vector = pt2 - pt1;
    XMVECTOR orthogonal = radius * XMVector2Orthogonal(
                                   XMVector3Normalize(vector));

    XMVECTOR pt1a = pt1 - orthogonal;
    XMVECTOR pt2a = pt1a + vector;
    XMVECTOR pt1b = pt1 + orthogonal;
    XMVECTOR pt2b = pt1b + vector;

    Point point1a(XMVectorGetX(pt1a), XMVectorGetY(pt1a));
    Point point2a(XMVectorGetX(pt2a), XMVectorGetY(pt2a));
    Point point1b(XMVectorGetX(pt1b), XMVectorGetY(pt1b));
    Point point2b(XMVectorGetX(pt2b), XMVectorGetY(pt2b));

    lineSegment1->Set(point1a, point2a);
    arcSegment1->Set(point2, radius, point2a, point2b);
    lineSegment2->Set(point2b, point1b);
    arcSegment2->Set(point1, radius, point1b, point1a);
}

void RoundCappedLine::GetAllX(float y, IVector<float>^ xCollection)
{
    arcSegment1->GetAllX(y, xCollection);
    lineSegment1->GetAllX(y, xCollection);
    arcSegment2->GetAllX(y, xCollection);
    lineSegment2->GetAllX(y, xCollection);
}
