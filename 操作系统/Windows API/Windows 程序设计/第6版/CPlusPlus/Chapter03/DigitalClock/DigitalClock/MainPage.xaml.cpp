//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace DigitalClock;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
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

    calendar = ref new Calendar();
    formatter = ref new DateTimeFormatter("longtime");

    TimeSpan timespan;
    timespan.Duration = 10000000;    // 1 second in 100-nanosecond ticks

    DispatcherTimer^ timer = ref new DispatcherTimer();
    timer->Interval = timespan;
    timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);
    timer->Start();
}

void MainPage::OnTimerTick(Object^ sender, Object ^args)
{
    calendar->SetToNow();
    DateTime datetime = calendar->GetDateTime();
    txtblk->Text = formatter->Format(datetime);
}
