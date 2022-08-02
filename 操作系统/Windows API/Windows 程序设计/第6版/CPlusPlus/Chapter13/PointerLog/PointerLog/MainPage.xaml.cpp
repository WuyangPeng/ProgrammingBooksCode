//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PointerLog;

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
    timer = ref new DispatcherTimer();
    TimeSpan interval = { 50000000 };
    timer->Interval = interval;
    timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);
}

void MainPage::OnClearButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    logger->Clear();
}

void MainPage::OnCaptureToggleButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    ToggleButton^ toggle = dynamic_cast<ToggleButton^>(sender);
    logger->CaptureOnPress = toggle->IsChecked->Value;
}

void MainPage::OnReleaseCapturesButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    timer->Start();
}

void MainPage::OnTimerTick(Object^ sender, Object^ args)
{
    logger->ReleasePointerCaptures();
    timer->Stop();
}
