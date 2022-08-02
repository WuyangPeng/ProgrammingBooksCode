//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleInking;

using namespace Platform;
using namespace Windows::Devices::Input;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Input;
using namespace Windows::UI::Input::Inking;
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

    inkManager = ref new InkManager();

    // Check if there's a pen among the pointer input devices
    for each (PointerDevice^ device in PointerDevice::GetPointerDevices())
        hasPen |= device->PointerDeviceType == PointerDeviceType::Pen;
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    if (args->Pointer->PointerDeviceType == PointerDeviceType::Pen || !hasPen)
    {
        PointerPoint^ pointerPoint = args->GetCurrentPoint(this);
        inkManager->ProcessPointerDown(pointerPoint);
    }
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    if ((args->Pointer->PointerDeviceType == PointerDeviceType::Pen || !hasPen) &&
        args->Pointer->IsInContact)
    {
        IVector<PointerPoint^>^ points = args->GetIntermediatePoints(this);

        for (int i = points->Size - 1; i >= 0; i--)
        {
            PointerPoint^ pointerPoint = points->GetAt(i);
            inkManager->ProcessPointerUpdate(pointerPoint);
        }
    }
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    if (args->Pointer->PointerDeviceType != PointerDeviceType::Pen && hasPen)
        return;

    inkManager->ProcessPointerUp(args->GetCurrentPoint(this));

    // Render the most recent InkStroke
    IVectorView<InkStroke^>^ inkStrokes = inkManager->GetStrokes();
    InkStroke^ inkStroke = inkStrokes->GetAt(inkStrokes->Size - 1);

    // Create SolidColorBrush used for all segments in the stroke
    Brush^ brush = ref new SolidColorBrush(inkStroke->DrawingAttributes->Color);

    // Get the segments
    IVectorView<InkStrokeRenderingSegment^>^ inkSegments = inkStroke->GetRenderingSegments();

    // Notice loop starts at 1
    for (unsigned int i = 1; i < inkSegments->Size; i++)
    {
        InkStrokeRenderingSegment^ inkSegment = inkSegments->GetAt(i);

        // Create a BezierSegment from the points
        BezierSegment^ bezierSegment = ref new BezierSegment();
        bezierSegment->Point1 = inkSegment->BezierControlPoint1;
        bezierSegment->Point2 = inkSegment->BezierControlPoint2;
        bezierSegment->Point3 = inkSegment->Position;

        // Create a PathFigure that begins at the preceding Position
        PathFigure^ pathFigure = ref new PathFigure();
        pathFigure->StartPoint = inkSegments->GetAt(i - 1)->Position;
        pathFigure->IsClosed = false;
        pathFigure->IsFilled = false;
        pathFigure->Segments->Append(bezierSegment);

        // Create a PathGeometry with that PathFigure
        PathGeometry^ pathGeometry = ref new PathGeometry();
        pathGeometry->Figures->Append(pathFigure);

        // Create a Path with that PathGeometry
        Path^ path = ref new Path();
        path->Stroke = brush;
        path->StrokeThickness = inkStroke->DrawingAttributes->Size.Width *
                                inkSegment->Pressure;
        path->StrokeStartLineCap = PenLineCap::Round;
        path->StrokeEndLineCap = PenLineCap::Round;
        path->Data = pathGeometry;

        // Add it to the Grid
        contentGrid->Children->Append(path);
    }
}