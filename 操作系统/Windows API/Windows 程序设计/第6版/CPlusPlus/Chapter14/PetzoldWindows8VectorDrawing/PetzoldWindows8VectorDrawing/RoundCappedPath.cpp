#include "pch.h"
#include "RoundCappedPath.h"

using namespace PetzoldWindows8VectorDrawing;

using namespace DirectX;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

RoundCappedPath::RoundCappedPath()
{
    lineSegment1 = ref new LineSegment();
    arcSegment1 = ref new ArcSegment();
    lineSegment2 = ref new LineSegment();
    arcSegment2 = ref new ArcSegment();
}

void RoundCappedPath::Set(Point point1, Point point2, float radius1, float radius2)
{
    // Get vector from C1 to c0
    XMVECTOR vC0 = XMVectorSet(point1.X, point1.Y, 0, 0);
    XMVECTOR vC1 = XMVectorSet(point2.X, point2.Y, 0, 0);
    XMVECTOR vCenters = vC0 - vC1;

    // Get lenth and normalized versions
    float d = XMVectorGetX(XMVector2Length(vCenters));
    vCenters = XMVector2Normalize(vCenters);

    // For convenience
    float r0 = radius1;
    float r1 = radius2;

    // Determine if one circle is enclosed in the other
    bool enclosed = r0 + d < r1;

    // Define tangent points derived in both algorithms
    XMVECTOR t0R;
    XMVECTOR t0L;
    XMVECTOR t1R;
    XMVECTOR t1L;

    // Case for two circles of same size
    if (r0 == r1 || enclosed)
    {
        // Rotate centers vector 90 degrees
        XMVECTOR vLeft = XMVector2Orthogonal(vCenters);

        // Rotate -90 degrees
        XMVECTOR vRight = -vLeft;

        // Find tangent points
        t0R = vC0 + r0 * vRight;
        t0L = vC0 + r0 * vLeft;
        t1R = vC1 + r1 * vRight;
        t1L = vC1 + r1 * vLeft;
    }
    // A bit more difficult for two circles of unequal size
    else
    {
        // Create focal point F extenting from c0
        float e = d * r0 / (r1 - r0);
        XMVECTOR F = vC0 + e * vCenters;

        // Find angle and length of right-triangle legs
        float alpha = (float)asin(r0 / e);
        float leg0 = (float)sqrt(e * e - r0 * r0);
        float leg1 = (float)sqrt((e + d) * (e + d) - r1 * r1);

        // Vectors of tangent lines
        XMVECTOR vRight = -XMVector2Transform(vCenters, XMMatrixRotationZ(alpha));
        XMVECTOR vLeft = -XMVector2Transform(vCenters, XMMatrixRotationZ(-alpha));

        // Find tangent vector
        t0R = F + leg0 * vRight;
        t0L = F + leg0 * vLeft;
        t1R = F + leg1 * vRight;
        t1L = F + leg1 * vLeft;
    }

    Point point0R(XMVectorGetX(t0R), XMVectorGetY(t0R));
    Point point0L(XMVectorGetX(t0L), XMVectorGetY(t0L));
    Point point1R(XMVectorGetX(t1R), XMVectorGetY(t1R));
    Point point1L(XMVectorGetX(t1L), XMVectorGetY(t1L));

    lineSegment1->Set(point1R, point0R);
    arcSegment1->Set(point1, radius1, point0R, point0L);
    lineSegment2->Set(point0L, point1L);
    arcSegment2->Set(point2, radius2, point1L, point1R);
}

void RoundCappedPath::GetAllX(float y, IVector<float>^ xCollection)
{
    arcSegment1->GetAllX(y, xCollection);
    lineSegment1->GetAllX(y, xCollection);
    arcSegment2->GetAllX(y, xCollection);
    lineSegment2->GetAllX(y, xCollection);
}
