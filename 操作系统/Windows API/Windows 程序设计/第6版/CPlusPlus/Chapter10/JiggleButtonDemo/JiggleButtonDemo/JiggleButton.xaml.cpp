//
// JiggleButton.xaml.cpp
// Implementation of the JiggleButton class
//

#include "pch.h"
#include "JiggleButton.xaml.h"

using namespace JiggleButtonDemo;

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

JiggleButton::JiggleButton()
{
    InitializeComponent();
}

void JiggleButton::OnJiggleButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup("jiggleAnimation"));
    storyboard->Begin();
}
