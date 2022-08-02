//
// XYSlider.xaml.cpp
// Implementation of the XYSlider class
//

#include "pch.h"
#include "XYSlider.h"

using namespace XYSliderDemo;

using namespace Platform;
using namespace Windows::Foundation;
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
}

DependencyProperty^ XYSlider::ValueProperty::get()
{
    return valueProperty;
}

Point XYSlider::Value::get()
{
    return (Point)GetValue(ValueProperty);
}

void XYSlider::Value::set(Point value)
{
    SetValue(ValueProperty, value);
}

void XYSlider::OnApplyTemplate()
{
    // Detach event handlers
    if (contentPresenter != nullptr)
    {
        contentPresenter->ManipulationStarted -= contentPresenterManipulationStartedEventToken;
        contentPresenter->ManipulationDelta -= contentPresenterManipulationDeltaEventToken;
        contentPresenter->SizeChanged -= contentPresenterSizeChangedEventToken;
    }

    // Get new parts
    crossHairPart = dynamic_cast<FrameworkElement^>(GetTemplateChild("CrossHairPart"));
    contentPresenter = dynamic_cast<ContentPresenter^>(GetTemplateChild("ContentPresenterPart"));

    // Attach event handlers
    if (contentPresenter != nullptr)
    {
        contentPresenter->ManipulationMode = ManipulationModes::TranslateX | ManipulationModes::TranslateY;
        contentPresenterManipulationStartedEventToken = contentPresenter->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &XYSlider::OnContentPresenterManipulationStarted);
        contentPresenterManipulationDeltaEventToken = contentPresenter->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &XYSlider::OnContentPresenterManipulationDelta);
        contentPresenterSizeChangedEventToken = contentPresenter->SizeChanged += ref new SizeChangedEventHandler(this, &XYSlider::OnContentPresenterSizeChanged);
    }

    // Make cross-hair transparent to touch
    if (crossHairPart != nullptr)
    {
        crossHairPart->IsHitTestVisible = false;
    }
}

void XYSlider::OnContentPresenterManipulationStarted(Object^ sender, ManipulationStartedRoutedEventArgs^ args)
{
    RecalculateValue(args->Position);
}

void XYSlider::OnContentPresenterManipulationDelta(Object^ sender, ManipulationDeltaRoutedEventArgs^ args)
{
    RecalculateValue(args->Position);
}

void XYSlider::OnContentPresenterSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    SetCrossHair();
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

