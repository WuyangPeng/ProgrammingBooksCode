//
// WrapOptionsDialog.xaml.cpp
// Implementation of the WrapOptionsDialog class
//

#include "pch.h"
#include "WrapOptionsDialog.xaml.h"

using namespace AppBarPad;

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

WrapOptionsDialog::WrapOptionsDialog()
{
    InitializeComponent();
}

DependencyProperty^ WrapOptionsDialog::TextWrappingProperty::get()
{
    static DependencyProperty^ textWrappingProperty;

    if (textWrappingProperty == nullptr)
    {
        textWrappingProperty = 
            DependencyProperty::Register("TextWrapping", 
                                         TypeName(Windows::UI::Xaml::TextWrapping::typeid), 
                                         TypeName(WrapOptionsDialog::typeid), 
                                         ref new PropertyMetadata(Windows::UI::Xaml::TextWrapping::NoWrap,
                                         ref new PropertyChangedCallback(WrapOptionsDialog::OnTextWrappingChanged)));
    }
    return textWrappingProperty;
}

void WrapOptionsDialog::OnTextWrappingChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<WrapOptionsDialog^>(sender)->OnTextWrappingInstanceChanged(args);
}

void WrapOptionsDialog::OnTextWrappingInstanceChanged(DependencyPropertyChangedEventArgs^ args)
{
    for each (UIElement^ child in stackPanel->Children)
    {
        RadioButton^ radioButton = dynamic_cast<RadioButton^>(child);
        radioButton->IsChecked = Windows::UI::Xaml::TextWrapping((int)(radioButton->Tag)) == this->TextWrapping;
    }
}

void WrapOptionsDialog::OnRadioButtonChecked(Object^ sender, RoutedEventArgs^ e)
{
    RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);
    this->TextWrapping = Windows::UI::Xaml::TextWrapping((int)(radioButton->Tag));
}
