//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ThreeDeeSpinningText;

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

void MainPage::OnBeginStopButton(Object^ sender, RoutedEventArgs^ args)
{
    Button^ btn = dynamic_cast<Button^>(sender);
    String^ key = dynamic_cast<String^>(GetSibling(btn, -1)->Tag);
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup(key));
    Button^ pauseResumeButton = dynamic_cast<Button^>(GetSibling(btn, 1));
    pauseResumeButton->Content = "Pause";

    if (dynamic_cast<String^>(btn->Content)->Equals("Begin"))
    {
        storyboard->Begin();
        btn->Content = "Stop";
        pauseResumeButton->IsEnabled = true;
    }
    else
    {
        storyboard->Stop();
        btn->Content = "Begin";
        pauseResumeButton->IsEnabled = false;
    }
}

void MainPage::OnPauseResumeButton(Object^ sender, RoutedEventArgs^ args)
{
    Button^ btn = dynamic_cast<Button^>(sender);
    String^ key = dynamic_cast<String^>(GetSibling(btn, -2)->Tag);
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup(key));

    if (dynamic_cast<String^>(btn->Content)->Equals("Pause"))
    {
        storyboard->Pause();
        btn->Content = "Resume";
    }
    else
    {
        storyboard->Resume();
        btn->Content = "Pause";
    }
}

FrameworkElement^ MainPage::GetSibling(FrameworkElement^ element, int relativeIndex)
{
    Panel^ parent = dynamic_cast<Panel^>(element->Parent);
    unsigned int index;
    parent->Children->IndexOf(element, &index);
    return dynamic_cast<FrameworkElement^>(parent->Children->GetAt(index + relativeIndex));
}