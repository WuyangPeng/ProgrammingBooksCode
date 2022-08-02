//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace TapToFlip;

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
    flipped = false;
    flipStoryboard = dynamic_cast<Storyboard^>(this->Resources->Lookup("flipStoryboard"));
    flipBackStoryboard = dynamic_cast<Storyboard^>(this->Resources->Lookup("flipBackStoryboard"));
}

void MainPage::OnGridTapped(Object^ sender, TappedRoutedEventArgs^ args)
{
    if (flipStoryboard->GetCurrentState() == ClockState::Active ||
        flipBackStoryboard->GetCurrentState() == ClockState::Active)
    {
        return;
    }

    Storyboard^ storyboard = flipped ? flipBackStoryboard : flipStoryboard;
    storyboard->Begin();
    flipped ^= true;
}
