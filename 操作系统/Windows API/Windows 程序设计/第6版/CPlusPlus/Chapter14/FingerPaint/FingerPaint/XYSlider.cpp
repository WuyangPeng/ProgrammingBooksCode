//
// XYSlider.xaml.cpp
// Implementation of the XYSlider class
//

#include "pch.h"
#include "XYSlider.h"

using namespace FingerPaint;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;

DependencyProperty^ XYSlider::valueProperty = 
    DependencyProperty::Register("Point", 
                                 TypeName(Point::typeid), 
                                 TypeName(XYSlider::typeid), 
                                 ref new PropertyMetadata(Point(0.5f, 0.5f), 
                                 ref new PropertyChangedCallback(&XYSlider::OnDependencyPropertyValueChanged)));

XYSlider::XYSlider()
{
    this->DefaultStyleKey = "XYSliderDemo.XYSlider";
    pointerDictionary = ref new Map<unsigned int, Point>();
}

void XYSlider::OnApplyTemplate()
{
    // Detach event handlers
    if (contentPresenter != nullptr)
    {
        contentPresenter->PointerPressed -= contentPresenterPointerPressedEventToken;
        contentPresenter->PointerMoved -= contentPresenterPointerMovedEventToken;
        contentPresenter->PointerReleased -= contentPresenterPointerReleasedEventToken;
        contentPresenter->PointerCaptureLost -= contentPresenterPointerCaptureLostEventToken;

        contentPresenter->SizeChanged -= contentPresenterSizeChangedEventToken;
    }

    // Get new parts
    crossHairPart = dynamic_cast<FrameworkElement^>(GetTemplateChild("CrossHairPart"));
    contentPresenter = dynamic_cast<ContentPresenter^>(GetTemplateChild("ContentPresenterPart"));

    // Attach event handlers
    if (contentPresenter != nullptr)
    {
        contentPresenter->ManipulationMode = ManipulationModes::TranslateX | ManipulationModes::TranslateY;

        contentPresenterPointerPressedEventToken = contentPresenter->PointerPressed += ref new PointerEventHandler(this, &XYSlider::OnContentPresenterPointerPressed);
        contentPresenterPointerMovedEventToken = contentPresenter->PointerMoved += ref new PointerEventHandler(this, &XYSlider::OnContentPresenterPointerMoved);
        contentPresenterPointerReleasedEventToken = contentPresenter->PointerReleased += ref new PointerEventHandler(this, &XYSlider::OnContentPresenterPointerReleased);
        contentPresenterPointerCaptureLostEventToken = contentPresenter->PointerCaptureLost += ref new PointerEventHandler(this, &XYSlider::OnContentPresenterPointerReleased);

        contentPresenterSizeChangedEventToken = contentPresenter->SizeChanged += ref new SizeChangedEventHandler(this, &XYSlider::OnContentPresenterSizeChanged);
    }

    // Make cross-hair transparent to touch
    if (crossHairPart != nullptr)
    {
        crossHairPart->IsHitTestVisible = false;
    }
}

void XYSlider::OnContentPresenterPointerPressed(Object^ sender, PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;
    Point point = args->GetCurrentPoint(contentPresenter)->Position;
    pointerDictionary->Insert(id, point);
    contentPresenter->CapturePointer(args->Pointer);

    RecalculateValue();
}

void XYSlider::OnContentPresenterPointerMoved(Object^ sender, PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        Point point = args->GetCurrentPoint(contentPresenter)->Position;
        pointerDictionary->Insert(id, point);
        RecalculateValue();
    }
}

void XYSlider::OnContentPresenterPointerReleased(Object^ sender, PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        pointerDictionary->Remove(id);
        RecalculateValue();
    }
}

void XYSlider::OnContentPresenterSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    SetCrossHair();
}

void XYSlider::RecalculateValue()
{
    if (pointerDictionary->Size > 0)
    {
        Point accumPoint(0, 0);

        // Average all teh curent touch points
        for each(IKeyValuePair<unsigned int, Point>^ pair in pointerDictionary)
        {
            accumPoint.X += pair->Value.X;
            accumPoint.Y += pair->Value.Y;
        }

        accumPoint.X /= pointerDictionary->Size;
        accumPoint.Y /= pointerDictionary->Size;

        RecalculateValue(accumPoint);
    }
}

void XYSlider::RecalculateValue(Point absolutePoint)
{
    double x = max(0.0, min(1.0, absolutePoint.X / contentPresenter->ActualWidth));
    double y = max(0.0, min(1.0, absolutePoint.Y / contentPresenter->ActualHeight));
    this->Value = Point((float)x, (float)y);
}

void XYSlider::SetCrossHair()
{
    if (contentPresenter != nullptr && crossHairPart != nullptr)
    {
        Canvas::SetLeft(crossHairPart, this->Value.X * contentPresenter->ActualWidth);
        Canvas::SetTop(crossHairPart, this->Value.Y * contentPresenter->ActualHeight);
    }
}

void XYSlider::OnDependencyPropertyValueChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<XYSlider^>(obj)->SetCrossHair();
    dynamic_cast<XYSlider^>(obj)->OnValueChanged((Point)args->NewValue);
}

void XYSlider::OnValueChanged(Point value)
{
    ValueChanged(this, value);
}

