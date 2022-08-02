//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint4;

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
    Point point = args->GetCurrentPoint(this)->Position;

    // Create random color
    unsigned char r = unsigned char((rand() % 256));
    unsigned char g = unsigned char((rand() % 256));
    unsigned char b = unsigned char((rand() % 256));
    Color clr = ColorHelper::FromArgb(255, r, g, b);

    // Create PointerInfo
    PointerInfo^ pointerInfo = ref new PointerInfo();
    pointerInfo->PreviousPoint = point;
    pointerInfo->Brush = ref new SolidColorBrush(clr);

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

            // For each point, create a Line element and add to Grid
            Point point = pointerPoint->Position;
            float pressure = pointerPoint->Properties->Pressure;

            Line^ line = ref new Line();
            line->X1 = pointerInfo->PreviousPoint.X;
            line->Y1 = pointerInfo->PreviousPoint.Y;
            line->X2 = point.X;
            line->Y2 = point.Y;
            line->Stroke = pointerInfo->Brush;
            line->StrokeThickness = pressure * 24;
            line->StrokeStartLineCap = PenLineCap::Round;
            line->StrokeEndLineCap = PenLineCap::Round;
            contentGrid->Children->Append(line);

            // Update PointerInfo 
            pointerInfo->PreviousPoint = point;
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

