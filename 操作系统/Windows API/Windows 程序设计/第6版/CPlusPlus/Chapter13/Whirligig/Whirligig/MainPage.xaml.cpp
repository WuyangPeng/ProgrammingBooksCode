//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Whirligig;

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
    pointerDictionary = ref new Map<unsigned int, TouchInfo^>();
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;
    Point point = args->GetCurrentPoint(this)->Position;

    // Create Polyline
    Polyline^ polyline = ref new Polyline();
    polyline->Stroke = dynamic_cast<Brush^>(this->Resources->Lookup("ApplicationForegroundThemeBrush"));
    polyline->StrokeThickness = 1;

    // Add to Grid
    contentGrid->Children->Append(polyline);

    // Create TouchInfo
    TouchInfo^ touchInfo = ref new TouchInfo();
    touchInfo->LastPoint = point;
    touchInfo->Polyline = polyline;

    // Add to dictionary
    pointerDictionary->Insert(id, touchInfo);

    // Capture the Pointer
    CapturePointer(args->Pointer);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    static float Radius = 24;               // 1/4 inch
    static double AngleIncrement = 0.5;     // radians per pixel

    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;
    Point point = args->GetCurrentPoint(this)->Position;

    // If ID is not in dictionary, don't do anything
    if (!pointerDictionary->HasKey(id))
        return;

    // Get TouchInfo objects
    TouchInfo^ touchInfo = pointerDictionary->Lookup(id);
    Polyline^ polyline = touchInfo->Polyline;
    Point lastPoint = touchInfo->LastPoint;
    double angle = touchInfo->Angle;

    // Distance from last point to this point
    float distance = (float)sqrt(pow(point.X - lastPoint.X, 2) +
                                 pow(point.Y - lastPoint.Y, 2));
    int divisions = (int)distance;

    for (int i = 0; i < divisions; i++)
    {
        // Sub-divide the distance between the last point and the new
        float x = (i * point.X + (divisions - i) * lastPoint.X) / divisions;
        float y = (i * point.Y + (divisions - i) * lastPoint.Y) / divisions;
        Point pt = Point(x, y);

        // Increase the angle
        angle += distance * AngleIncrement / divisions;

        // Rotate the point
        pt.X += Radius * (float)cos(angle);
        pt.Y += Radius * (float)sin(angle);

        // Add to Polyline
        polyline->Points->Append(pt);
    }

    // Save new information
    touchInfo->LastPoint = point;
    touchInfo->Angle = angle;
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

