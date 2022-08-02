//
// SplitContainer.xaml.cpp
// Implementation of the SplitContainer class
//

#include "pch.h"
#include "SplitContainer.xaml.h"

using namespace XamlCruncher;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ SplitContainer::child1Property = 
    DependencyProperty::Register("Child1", 
                                 TypeName(UIElement::typeid), 
                                 TypeName(SplitContainer::typeid),
                                 ref new PropertyMetadata(nullptr, 
                                 ref new PropertyChangedCallback(OnChildChanged)));

DependencyProperty^ SplitContainer::child2Property = 
    DependencyProperty::Register("Child2", 
                                 TypeName(UIElement::typeid), 
                                 TypeName(SplitContainer::typeid),
                                 ref new PropertyMetadata(nullptr, 
                                 ref new PropertyChangedCallback(OnChildChanged)));

DependencyProperty^ SplitContainer::swapChildrenProperty = 
    DependencyProperty::Register("SwapChildren", 
                                 TypeName(bool::typeid), 
                                 TypeName(SplitContainer::typeid),
                                 ref new PropertyMetadata(ref new Box<Boolean>(false),
                                 ref new PropertyChangedCallback(OnSwapChildrenChanged)));

DependencyProperty^ SplitContainer::orientationProperty = 
    DependencyProperty::Register("Orientation", 
                                 TypeName(Windows::UI::Xaml::Controls::Orientation::typeid), 
                                 TypeName(SplitContainer::typeid),
                                 ref new PropertyMetadata(Windows::UI::Xaml::Controls::Orientation::Horizontal,
                                 ref new PropertyChangedCallback(OnOrientationChanged)));

DependencyProperty^ SplitContainer::minimumSizeProperty = 
    DependencyProperty::Register("MinimumSize", 
                                 TypeName(double::typeid), 
                                 TypeName(SplitContainer::typeid),
                                 ref new PropertyMetadata(100.0,
                                 ref new PropertyChangedCallback(OnMinSizeChanged)));

SplitContainer::SplitContainer()
{
    InitializeComponent();
}

// Static dependency property definitions
DependencyProperty^ SplitContainer::Child1Property::get()
{
    return child1Property;
}

DependencyProperty^ SplitContainer::Child2Property::get()
{
    return child2Property;
}

DependencyProperty^ SplitContainer::SwapChildrenProperty::get()
{
    return swapChildrenProperty;
}

DependencyProperty^ SplitContainer::OrientationProperty::get()
{
    return orientationProperty;
}

DependencyProperty^ SplitContainer::MinimumSizeProperty::get()
{
    return minimumSizeProperty;
}

void SplitContainer::Child1::set(UIElement^ value)
{
    SetValue(Child1Property, value);
}

UIElement^ SplitContainer::Child1::get()
{
    return dynamic_cast<UIElement^>(GetValue(Child1Property));
}

void SplitContainer::Child2::set(UIElement^ value)
{
    SetValue(Child2Property, value);
}

UIElement^ SplitContainer::Child2::get()
{
    return dynamic_cast<UIElement^>(GetValue(Child2Property));
}

void SplitContainer::Orientation::set(Windows::UI::Xaml::Controls::Orientation value)
{
    SetValue(OrientationProperty, value); 
}

Windows::UI::Xaml::Controls::Orientation SplitContainer::Orientation::get()
{
    return Windows::UI::Xaml::Controls::Orientation(GetValue(OrientationProperty));
}

void SplitContainer::SwapChildren::set(bool value)
{
    SetValue(SwapChildrenProperty, value);
}

bool SplitContainer::SwapChildren::get()
{
    return (bool)GetValue(SwapChildrenProperty);
}

void SplitContainer::MinimumSize::set(double value)
{
    SetValue(MinimumSizeProperty, value);
}

double SplitContainer::MinimumSize::get()
{
    return (double)GetValue(MinimumSizeProperty);
}

void SplitContainer::OnChildChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<SplitContainer^>(sender)->OnChildInstanceChanged(args);
}

void SplitContainer::OnChildInstanceChanged(DependencyPropertyChangedEventArgs^ args)
{
    Grid^ targetGrid = (args->Property == Child1Property) ? grid1 : grid2;
    targetGrid->Children->Clear();

    if (args->NewValue != nullptr)
        targetGrid->Children->Append(dynamic_cast<UIElement^>(args->NewValue));
}

void SplitContainer::OnOrientationChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<SplitContainer^>(sender)->OnOrientationInstanceChanged((Windows::UI::Xaml::Controls::Orientation)args->OldValue,
                                                                        (Windows::UI::Xaml::Controls::Orientation)args->NewValue);
}

void SplitContainer::OnOrientationInstanceChanged(Windows::UI::Xaml::Controls::Orientation oldOrientation,
                                                  Windows::UI::Xaml::Controls::Orientation newOrientation)
{
    // Shouldn't be necessary, but...
    if (newOrientation == oldOrientation)
        return;

    if (newOrientation == Windows::UI::Xaml::Controls::Orientation::Horizontal)
    {
        coldef1->Width = rowdef1->Height;
        coldef2->Width = rowdef2->Height;

        coldef1->MinWidth = this->MinimumSize;
        coldef2->MinWidth = this->MinimumSize;

        rowdef1->Height = GridLengthHelper::FromValueAndType(1, GridUnitType::Star);
        rowdef2->Height = GridLengthHelper::FromPixels(0);

        rowdef1->MinHeight = 0;
        rowdef2->MinHeight = 0;

        thumb->Width = 12;
        thumb->Height = _Nan._Double;

        Grid::SetRow(thumb, 0);
        Grid::SetColumn(thumb, 1);

        Grid::SetRow(grid2, 0);
        Grid::SetColumn(grid2, 2);
    }
    else
    {
        rowdef1->Height = coldef1->Width;
        rowdef2->Height = coldef2->Width;

        rowdef1->MinHeight = this->MinimumSize;
        rowdef2->MinHeight = this->MinimumSize;

        coldef1->Width = GridLengthHelper::FromValueAndType(1, GridUnitType::Star);
        coldef2->Width = GridLengthHelper::FromPixels(0);

        coldef1->MinWidth = 0;
        coldef2->MinWidth = 0;

        thumb->Height = 12;
        thumb->Width = _Nan._Double;

        Grid::SetRow(thumb, 1);
        Grid::SetColumn(thumb, 0);

        Grid::SetRow(grid2, 2);
        Grid::SetColumn(grid2, 0);
    }
}

void SplitContainer::OnSwapChildrenChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<SplitContainer^>(sender)->OnSwapChildrenInstanceChanged((bool)(args->OldValue),
                                                                         (bool)(args->NewValue));
}

void SplitContainer::OnSwapChildrenInstanceChanged(bool oldValue, bool newValue)
{
    grid1->Children->Clear();
    grid2->Children->Clear();

    grid1->Children->Append(newValue ? this->Child2 : this->Child1);
    grid2->Children->Append(newValue ? this->Child1 : this->Child2);
}

void SplitContainer::OnMinSizeChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<SplitContainer^>(sender)->OnMinSizeInstanceChanged((double)(args->OldValue),
                                                                    (double)(args->NewValue));
}

void SplitContainer::OnMinSizeInstanceChanged(double oldValue, double newValue)
{
    if (this->Orientation == Windows::UI::Xaml::Controls::Orientation::Horizontal)
    {
        coldef1->MinWidth = newValue;
        coldef2->MinWidth = newValue;
    }
    else
    {
        rowdef1->MinHeight = newValue;
        rowdef2->MinHeight = newValue;
    }
}

// Thumb event handlers
// Messier than the C# versions because C++ can't access the Value 
//      property of the GridLength value.
void SplitContainer::OnThumbDragStarted(Object^ sender, DragStartedEventArgs^ args)
{
    if (this->Orientation == Windows::UI::Xaml::Controls::Orientation::Horizontal)
    {
        grid1Size = coldef1->ActualWidth;
        grid2Size = coldef2->ActualWidth;

        coldef1->Width = GridLengthHelper::FromValueAndType(grid1Size, GridUnitType::Star);
        coldef2->Width = GridLengthHelper::FromValueAndType(grid2Size, GridUnitType::Star);
    }
    else
    {
        grid1Size = rowdef1->ActualHeight;
        grid2Size = rowdef2->ActualHeight;

        rowdef1->Height = GridLengthHelper::FromValueAndType(grid1Size, GridUnitType::Star);
        rowdef2->Height = GridLengthHelper::FromValueAndType(grid2Size, GridUnitType::Star);
    }
}

void SplitContainer::OnThumbDragDelta(Object^ sender, DragDeltaEventArgs^ args)
{
    if (this->Orientation == Windows::UI::Xaml::Controls::Orientation::Horizontal)
    {
        grid1Size = max(0.0, grid1Size + args->HorizontalChange);
        grid2Size = max(0.0, grid2Size - args->HorizontalChange);

        coldef1->Width = GridLengthHelper::FromValueAndType(grid1Size, GridUnitType::Star);
        coldef2->Width = GridLengthHelper::FromValueAndType(grid2Size, GridUnitType::Star);
    }
    else
    {
        grid1Size = max(0.0, grid1Size + args->VerticalChange);
        grid2Size = max(0.0, grid2Size - args->VerticalChange);

        rowdef1->Height = GridLengthHelper::FromValueAndType(grid1Size, GridUnitType::Star);
        rowdef2->Height = GridLengthHelper::FromValueAndType(grid2Size, GridUnitType::Star);
    }
}
