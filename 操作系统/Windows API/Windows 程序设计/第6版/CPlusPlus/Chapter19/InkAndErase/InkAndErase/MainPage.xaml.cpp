//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace InkAndErase;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Devices::Input;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
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
    inkDrawingAttributes = ref new InkDrawingAttributes();
    pointerDictionary = ref new Map<unsigned int, Point>;

    // Check if there's a pen among the pointer input devices
    for each (PointerDevice^ device in PointerDevice::GetPointerDevices())
        hasPen |= device->PointerDeviceType == PointerDeviceType::Pen;

    // Default drawing attributes
    inkDrawingAttributes->Color = Colors::Blue;
    inkDrawingAttributes->Size = SizeHelper::FromDimensions(6, 6);
    inkManager->SetDefaultDrawingAttributes(inkDrawingAttributes);
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    if (args->Pointer->PointerDeviceType == PointerDeviceType::Pen || !hasPen)
    {
        // Get information
        PointerPoint^ pointerPoint = args->GetCurrentPoint(this);

        // Initialize for inking or erasing
        if (!pointerPoint->Properties->IsEraser)
        {
            inkManager->Mode = InkManipulationMode::Inking;
        }
        else
        {
            inkManager->Mode = InkManipulationMode::Erasing;
        }

        // Give PointerPoint to InkManager
        inkManager->ProcessPointerDown(pointerPoint);

        // Add an entry to the dictionary
        pointerDictionary->Insert(args->Pointer->PointerId, pointerPoint->Position);

        // Capture the pointer
        CapturePointer(args->Pointer);
    }
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    // Get information
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        IVector<PointerPoint^>^ points = args->GetIntermediatePoints(this);

        for (int i = points->Size - 1; i >= 0; i--)
        {
            PointerPoint^ pointerPoint = points->GetAt(i);

            // Give PointerPoint to InkManager
            Object^ obj = inkManager->ProcessPointerUpdate(pointerPoint);

            if (inkManager->Mode == InkManipulationMode::Erasing)
            {
                // See if something has actually been removed
                Rect rect = (Rect)obj;

                if (rect.Width != 0 && rect.Height != 0)
                {
                    RenderAll();
                }
            }
            else
            {
                // Render the line
                Point point1 = pointerDictionary->Lookup(id);
                Point point2 = pointerPoint->Position;

                Line^ line = ref new Line();
                line->X1 = point1.X;
                line->Y1 = point1.Y;
                line->X2 = point2.X;
                line->Y2 = point2.Y;
                line->Stroke = ref new SolidColorBrush(inkDrawingAttributes->Color);
                line->StrokeThickness = inkDrawingAttributes->Size.Width * 
                                        pointerPoint->Properties->Pressure;
                line->StrokeStartLineCap = PenLineCap::Round;
                line->StrokeEndLineCap = PenLineCap::Round;

                newLineGrid->Children->Append(line);
                pointerDictionary->Insert(id, point2);
            }
        }
    }
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    // Get information
    PointerPoint^ pointerPoint = args->GetCurrentPoint(this);
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        // Give PointerPoint to InkManager
        inkManager->ProcessPointerUp(pointerPoint);

        if (inkManager->Mode == InkManipulationMode::Inking)
        {
            // Get rid of the little line segments
            newLineGrid->Children->Clear();

            // Render the new stroke
            IVectorView<InkStroke^>^ inkStrokes = inkManager->GetStrokes();
            InkStroke^ inkStroke = inkStrokes->GetAt(inkStrokes->Size - 1);
            RenderStroke(inkStroke);
        }
        pointerDictionary->Remove(id);
    }
}

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        pointerDictionary->Remove(id);
        newLineGrid->Children->Clear();
        RenderAll();
    }
}

void MainPage::RenderAll()
{
    contentGrid->Children->Clear();

    for each (InkStroke^ inkStroke in inkManager->GetStrokes())
        RenderStroke(inkStroke);
}

void MainPage::RenderStroke(InkStroke^ inkStroke)
{
    Brush^ brush = ref new SolidColorBrush(inkStroke->DrawingAttributes->Color);
    IVectorView<InkStrokeRenderingSegment^>^ inkSegments = inkStroke->GetRenderingSegments();

    for (unsigned int i = 1; i < inkSegments->Size; i++)
    {
        InkStrokeRenderingSegment^ inkSegment = inkSegments->GetAt(i);

        BezierSegment^ bezierSegment = ref new BezierSegment();
        bezierSegment->Point1 = inkSegment->BezierControlPoint1;
        bezierSegment->Point2 = inkSegment->BezierControlPoint2;
        bezierSegment->Point3 = inkSegment->Position;

        PathFigure^ pathFigure = ref new PathFigure();
        pathFigure->StartPoint = inkSegments->GetAt(i - 1)->Position;
        pathFigure->IsClosed = false;
        pathFigure->IsFilled = false;
        pathFigure->Segments->Append(bezierSegment);

        PathGeometry^ pathGeometry = ref new PathGeometry();
        pathGeometry->Figures->Append(pathFigure);

        Path^ path = ref new Path();
        path->Stroke = brush;
        path->StrokeThickness = inkStroke->DrawingAttributes->Size.Width *
                                inkSegment->Pressure;
        path->StrokeStartLineCap = PenLineCap::Round;
        path->StrokeEndLineCap = PenLineCap::Round;
        path->Data = pathGeometry;

        contentGrid->Children->Append(path);
    }
}


