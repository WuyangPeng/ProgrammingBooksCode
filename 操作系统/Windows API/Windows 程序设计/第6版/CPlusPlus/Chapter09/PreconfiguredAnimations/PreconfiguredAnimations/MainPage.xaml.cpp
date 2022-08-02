//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PreconfiguredAnimations;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ btn = dynamic_cast<Button^>(sender);
    String^ key = dynamic_cast<String^>(btn->Tag);
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup(key));
    storyboard->Begin();
}
