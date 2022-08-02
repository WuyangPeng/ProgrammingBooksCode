#include "pch.h"
#include "PieSlice.h"

using namespace AnimatedPieSlice;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

DependencyProperty^ PieSlice::centerProperty = 
    DependencyProperty::Register("Center", 
                                 TypeName(Point::typeid), 
                                 TypeName(PieSlice::typeid),
                                 ref new PropertyMetadata(Point(100, 100), 
                                 ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ PieSlice::radiusProperty = 
    DependencyProperty::Register("Radius", 
                                 TypeName(double::typeid), 
                                 TypeName(PieSlice::typeid),
                                 ref new PropertyMetadata(100.0, 
                                 ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ PieSlice::startAngleProperty = 
    DependencyProperty::Register("StartAngle", 
                                 TypeName(double::typeid), 
                                 TypeName(PieSlice::typeid),
                                 ref new PropertyMetadata(0.0, 
                                 ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ PieSlice::sweepAngleProperty = 
    DependencyProperty::Register("SweepAngle", 
                                 TypeName(double::typeid), 
                                 TypeName(PieSlice::typeid),
                                 ref new PropertyMetadata(90.0, 
                                 ref new PropertyChangedCallback(OnPropertyChanged)));

PieSlice::PieSlice()
{
    lineSegment = ref new LineSegment();
    arcSegment = ref new ArcSegment();
    arcSegment->SweepDirection = SweepDirection::Clockwise;

    pathFigure = ref new PathFigure();
    pathFigure->IsClosed = true;
    pathFigure->Segments->Append(lineSegment);
    pathFigure->Segments->Append(arcSegment);

    PathGeometry^ pathGeometry = ref new PathGeometry();
    pathGeometry->Figures->Append(pathFigure);

    this->Data = pathGeometry;
    UpdateValues();
}

DependencyProperty^ PieSlice::CenterProperty::get()
{
    return centerProperty;
}

DependencyProperty^ PieSlice::RadiusProperty::get()
{
    return radiusProperty;
}

DependencyProperty^ PieSlice::StartAngleProperty::get()
{
    return startAngleProperty;
}

DependencyProperty^ PieSlice::SweepAngleProperty::get()
{
    return sweepAngleProperty;
}

void PieSlice::Center::set(Point point)
{
    SetValue(CenterProperty, point);
}

Point PieSlice::Center::get()
{
    return (Point)GetValue(CenterProperty); 
}

void PieSlice::Radius::set(double radius)
{
    SetValue(RadiusProperty, radius);
}

double PieSlice::Radius::get()
{
    return (double)GetValue(RadiusProperty);
}

void PieSlice::StartAngle::set(double angle)
{
    SetValue(StartAngleProperty, angle);
}

double PieSlice::StartAngle::get()
{
    return (double)GetValue(StartAngleProperty);
}

void PieSlice::SweepAngle::set(double angle)
{
    SetValue(SweepAngleProperty, angle);
}

double PieSlice::SweepAngle::get()
{
    return (double)GetValue(SweepAngleProperty);
}

void PieSlice::OnPropertyChanged(DependencyObject^ obj,
                                 DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<PieSlice^>(obj)->UpdateValues();
}

void PieSlice::UpdateValues()
{
    pathFigure->StartPoint = this->Center;

    double radians = 3.14159 * this->StartAngle / 180;
    double x = this->Center.X + this->Radius * sin(radians);
    double y = this->Center.Y - this->Radius * cos(radians);
    lineSegment->Point = Point((float)x, (float)y);

    radians += 3.14159 * this->SweepAngle / 180;
    x = this->Center.X + this->Radius * sin(radians);
    y = this->Center.Y - this->Radius * cos(radians);

    arcSegment->Point = Point((float)x, (float)y);
    arcSegment->IsLargeArc = this->SweepAngle >= 180;
    arcSegment->Size = Size((float)this->Radius, (float)this->Radius);
}
