//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint1;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
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
    pointerDictionary = ref new Map<unsigned int, Polyline^>();
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

    // Create Polyline
    Polyline^ polyline = ref new Polyline();
    polyline->Stroke = ref new SolidColorBrush(clr);
    polyline->StrokeThickness = 24;
    polyline->Points->Append(point);

    // Add to Grid
    contentGrid->Children->Append(polyline);

    // Add to dictionary
    pointerDictionary->Insert(id, polyline);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;
    Point point = args->GetCurrentPoint(this)->Position;

    // If ID is in dictionary, add the point to the Polyline
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Lookup(id)->Points->Append(point);
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, remove it
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}
