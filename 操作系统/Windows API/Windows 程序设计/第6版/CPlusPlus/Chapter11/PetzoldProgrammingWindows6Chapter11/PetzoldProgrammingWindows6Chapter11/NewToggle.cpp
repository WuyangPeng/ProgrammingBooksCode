//
// NewToggle.cpp
// Implementation of the NewToggle class.
//

#include "pch.h"
#include "NewToggle.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

DependencyProperty^ NewToggle::checkedContentProperty = 
    DependencyProperty::Register("CheckedContent",
                                 TypeName(Object::typeid),
                                 TypeName(NewToggle::typeid),
                                 ref new PropertyMetadata(nullptr));

DependencyProperty^ NewToggle::isCheckedProperty = 
    DependencyProperty::Register("IsChecked",
                                 TypeName(bool::typeid),
                                 TypeName(NewToggle::typeid),
                                 ref new PropertyMetadata(false,
                                    ref new PropertyChangedCallback(NewToggle::OnCheckedChangedStatic)));

NewToggle::NewToggle()
{
    DefaultStyleKey = "PetzoldProgrammingWindows6Chapter11.NewToggle";
}

void NewToggle::OnApplyTemplate()
{
    if (uncheckButton != nullptr)
        uncheckButton->Click -= uncheckClickEventToken;

    if (checkButton != nullptr)
        checkButton->Click -= checkClickEventToken; 

    uncheckButton = dynamic_cast<Button^>(GetTemplateChild("UncheckButton"));
    checkButton = dynamic_cast<Button^>(GetTemplateChild("CheckButton"));

    if (uncheckButton != nullptr)
        uncheckClickEventToken = uncheckButton->Click += ref new RoutedEventHandler(this, &NewToggle::OnButtonClick);

    if (checkButton != nullptr)
        checkClickEventToken = checkButton->Click += ref new RoutedEventHandler(this, &NewToggle::OnButtonClick);
}

void NewToggle::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->IsChecked = dynamic_cast<Button^>(sender) == checkButton;
}

void NewToggle::OnCheckedChangedStatic(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<NewToggle^>(obj)->OnCheckedChanged(nullptr);
}

void NewToggle::OnCheckedChanged(Object^ args)
{
    VisualStateManager::GoToState(this, this->IsChecked ? "Checked" : "Unchecked", true);

    CheckedChanged(this, args);
}