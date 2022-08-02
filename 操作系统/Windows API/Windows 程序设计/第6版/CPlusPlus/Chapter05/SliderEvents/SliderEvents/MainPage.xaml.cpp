//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SliderEvents;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    Slider^ slider = dynamic_cast<Slider^>(sender);
    Panel^ parentPanel = dynamic_cast<Panel^>(slider->Parent);
    uint32 childIndex;
    parentPanel->Children->IndexOf(slider, &childIndex);
    TextBlock^ txtblk = dynamic_cast<TextBlock^>(parentPanel->Children->GetAt(childIndex + 1));
    txtblk->Text = args->NewValue.ToString();
}
