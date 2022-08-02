//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint5;

using namespace DirectX;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

MainPage::MainPage()
{
    InitializeComponent();
    pointerDictionary = ref new Map<unsigned int, PointerInfo^>();
     srand(int(time(NULL)));
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;
    PointerPoint^ pointerPoint = args->GetCurrentPoint(this);

    // Create random color
    unsigned char r = unsigned char((rand() % 256));
    unsigned char g = unsigned char((rand() % 256));
    unsigned char b = unsigned char((rand() % 256));
    Color color = ColorHelper::FromArgb(255, r, g, b);

    // Create PointerInfo
    PointerInfo^ pointerInfo = ref new PointerInfo();
    pointerInfo->PreviousPoint = pointerPoint->Position;
    pointerInfo->PreviousRadius = 24 * pointerPoint->Properties->Pressure;
    pointerInfo->Brush = ref new SolidColorBrush(color);

    // Add to dictionary
    pointerDictionary->Insert(id, pointerInfo);

    // Capture the Pointer
    CapturePointer(args->Pointer);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, create a new Line element and add to Grid
    if (pointerDictionary->HasKey(id))
    {
        PointerInfo^ pointerInfo = pointerDictionary->Lookup(id);
        IVector<PointerPoint^>^ pointerPoints = args->GetIntermediatePoints(this);

        for (int i = pointerPoints->Size - 1; i >= 0; i--)
        {
            PointerPoint^ pointerPoint = pointerPoints->GetAt(i);

            // For each point, create a Path element and add to Grid
            Point point = pointerPoint->Position;
            float pressure = pointerPoint->Properties->Pressure;
            float radius = 12 * pressure;

            Geometry^ geometry = 
                CreateTaperedLineGeometry(pointerInfo->PreviousPoint,
                                          pointerInfo->PreviousRadius,
                                          point,
                                          radius);

            Path^ path = ref new Path();
            path->Data = geometry;
            path->Fill = pointerInfo->Brush;
            contentGrid->Children->Append(path);

            // Update PointerInfo 
            pointerInfo->PreviousPoint = point;
            pointerInfo->PreviousRadius = radius;
        }
    }
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, remove it
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, remove it
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

Geometry^ MainPage::CreateTaperedLineGeometry(Point c0, float r0, Point c1, float r1)
{
    // Swap the centers and radii so that c0 is
    //      the center of the smaller circle
    if (r1 < r0)
    {
        Point point = c0;
        c0 = c1;
        c1 = point;

        float radius = r0;
        r0 = r1;
        r1 = radius;
    }

    // Get vector from C1 to c0
    XMVECTOR vC0 = XMVectorSet(c0.X, c0.Y, 0, 0);
    XMVECTOR vC1 = XMVectorSet(c1.X, c1.Y, 0, 0);
    XMVECTOR vCenters = vC0 - vC1;

    // Get lenth and normalized versions
    float d = XMVectorGetX(XMVector2Length(vCenters));
    vCenters = XMVector2Normalize(vCenters);

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

    // Create PathGeometry with implied closing line
    PathGeometry^ pathGeometry = ref new PathGeometry();
    PathFigure^ pathFigure = ref new PathFigure();
    pathFigure->StartPoint = Point(XMVectorGetX(t0R), XMVectorGetY(t0R));
    pathFigure->IsClosed = true;
    pathFigure->IsFilled = true;
    pathGeometry->Figures->Append(pathFigure);

    // Arc around smaller circle
    ArcSegment^ arc0Segment = ref new ArcSegment();
    arc0Segment->Point = Point(XMVectorGetX(t0L), XMVectorGetY(t0L));
    arc0Segment->Size = Size(r0, r0);
    arc0Segment->SweepDirection = SweepDirection::Clockwise;
    arc0Segment->IsLargeArc = false;
    pathFigure->Segments->Append(arc0Segment);

    // Line connecting smaller circle to larger circle
    LineSegment^ lineSegment = ref new LineSegment();
    lineSegment->Point = Point(XMVectorGetX(t1L), XMVectorGetY(t1L));
    pathFigure->Segments->Append(lineSegment);

    // Arc around larger cirlce
    ArcSegment^ arc1Segment = ref new ArcSegment();
    arc1Segment->Point = Point(XMVectorGetX(t1R), XMVectorGetY(t1R));
    arc1Segment->Size = Size(r1, r1);
    arc1Segment->SweepDirection = SweepDirection::Clockwise;
    arc1Segment->IsLargeArc = true;
    pathFigure->Segments->Append(arc1Segment);

    return pathGeometry;
}