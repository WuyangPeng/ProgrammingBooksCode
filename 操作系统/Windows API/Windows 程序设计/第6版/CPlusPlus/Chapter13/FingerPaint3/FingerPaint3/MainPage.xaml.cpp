//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint3;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI;
using namespace Windows::UI::Popups;
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
    this->IsTabStop = true;
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
    polyline->PointerPressed += ref new PointerEventHandler(this, &MainPage::OnPolylinePointerPressed);
    polyline->RightTapped += ref new RightTappedEventHandler(this, &MainPage::OnPolylineRightTapped);
    polyline->Points->Append(point);

    // Add to Grid
    contentGrid->Children->Append(polyline);

    // Add to dictionary
    pointerDictionary->Insert(id, polyline);

    // Capture the Pointer
    CapturePointer(args->Pointer);

    // Set input focus
    Focus(Windows::UI::Xaml::FocusState::Programmatic);
}

void MainPage::OnPolylinePointerPressed(Object^ sender, PointerRoutedEventArgs^ args)
{
    args->Handled = true;
}

void MainPage::OnPolylineRightTapped(Object^ sender, RightTappedRoutedEventArgs^ args)
{
    Polyline^ polyline = dynamic_cast<Polyline^>(sender);
    PopupMenu^ popupMenu = ref new PopupMenu();
    popupMenu->Commands->Append(ref new UICommand("Change color", ref new UICommandInvokedHandler(this, &MainPage::OnMenuChangeColor), polyline));
    popupMenu->Commands->Append(ref new UICommand("Delete", ref new UICommandInvokedHandler(this, &MainPage::OnMenuDelete), polyline));
    popupMenu->ShowAsync(args->GetPosition(this));
}

void MainPage::OnMenuChangeColor(IUICommand^ command)
{
    Polyline^ polyline = dynamic_cast<Polyline^>(command->Id);
      unsigned char r = unsigned char((rand() % 256));
    unsigned char g = unsigned char((rand() % 256));
    unsigned char b = unsigned char((rand() % 256));
    Color clr = ColorHelper::FromArgb(255, r, g, b);
    dynamic_cast<SolidColorBrush^>(polyline->Stroke)->Color = clr;
}

void MainPage::OnMenuDelete(IUICommand^ command)
{
    Polyline^ polyline = dynamic_cast<Polyline^>(command->Id);
    unsigned int index;
    contentGrid->Children->IndexOf(polyline, &index);
    contentGrid->Children->RemoveAt(index);
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

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, abandon the drawing operation
    if (pointerDictionary->HasKey(id))
    {
        unsigned int index;
        contentGrid->Children->IndexOf(pointerDictionary->Lookup(id), &index);
        contentGrid->Children->RemoveAt(index);
        pointerDictionary->Remove(id);
    }
}

void MainPage::OnKeyDown(KeyRoutedEventArgs^ args)
{
    if (args->Key == VirtualKey::Escape)
        ReleasePointerCaptures();
}
