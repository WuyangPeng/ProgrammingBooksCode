//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                // includes ppltasks.h
#include "MainPage.xaml.h"

using namespace HowToAsync3;

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
    MessageDialog^ msgdlg = ref new MessageDialog("Choose a color", "How To Async #3");
    msgdlg->Commands->Append(ref new UICommand("Red", nullptr, Colors::Red));
    msgdlg->Commands->Append(ref new UICommand("Green", nullptr, Colors::Green));
    msgdlg->Commands->Append(ref new UICommand("Blue", nullptr, Colors::Blue));

    // Show the MessageDialog
    task<IUICommand^> showTask = create_task(msgdlg->ShowAsync());
    showTask.then([this](IUICommand^ command)
    {
        // Get the Color value
        Color clr = (Color)command->Id;

        // Set the background brush
        contentGrid->Background = ref new SolidColorBrush(clr);
    });
}