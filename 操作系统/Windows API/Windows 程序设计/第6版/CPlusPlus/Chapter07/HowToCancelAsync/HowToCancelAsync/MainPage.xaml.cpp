//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                            // includes ppltasks.h
#include "MainPage.xaml.h"

using namespace HowToCancelAsync;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
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

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    MessageDialog^ msgdlg = ref new MessageDialog("Choose a color", "How To Cancel Async");
    msgdlg->Commands->Append(ref new UICommand("Red", nullptr, Colors::Red));
    msgdlg->Commands->Append(ref new UICommand("Green", nullptr, Colors::Green));
    msgdlg->Commands->Append(ref new UICommand("Blue", nullptr, Colors::Blue));

    // Start a five-second timer
    TimeSpan timeSpan;
    timeSpan.Duration = 50000000;   // 5 seconds

    DispatcherTimer^ timer = ref new DispatcherTimer();
    timer->Interval = timeSpan;
    timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);
    timer->Start();

    // Show the MessageDialog
    cancellationTokenSource = cancellation_token_source();
    task<IUICommand^> showTask = create_task(msgdlg->ShowAsync(), cancellationTokenSource.get_token());
    showTask.then([this, timer](task<IUICommand^> thisTask)
    {
        IUICommand^ command = nullptr;

        try
        {
            command = thisTask.get();
        }
        catch (task_canceled)
        {
            // The exception in this case will be task_canceled
        }

        // Stop the timer
        timer->Stop();

        // If the operation wasn't cancelled, use the value
        if (command != nullptr)
        {
            // Get the Color value and set the background brush
            Color clr = (Color)command->Id;
            contentGrid->Background = ref new SolidColorBrush(clr);
        }
    });
}

void MainPage::OnTimerTick(Object^ sender, Object^ args)
{
    cancellationTokenSource.cancel();
}
