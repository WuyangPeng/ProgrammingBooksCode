//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleAnimationCode;

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
    DoubleAnimation^ anima = ref new DoubleAnimation();
    anima->EnableDependentAnimation = true;
    anima->To = 96.0;
    TimeSpan timespan = { 10000000 };   // 1 second in 100-nanosecond ticks
    anima->Duration = DurationHelper::FromTimeSpan(timespan);
    anima->AutoReverse = true;
    anima->RepeatBehavior = RepeatBehaviorHelper::FromCount(3);

    Storyboard::SetTarget(anima, dynamic_cast<Button^>(sender));
    Storyboard::SetTargetProperty(anima, "FontSize");

    Storyboard^ storyboard = ref new Storyboard();
    storyboard->Children->Append(anima);
    storyboard->Begin();
}
