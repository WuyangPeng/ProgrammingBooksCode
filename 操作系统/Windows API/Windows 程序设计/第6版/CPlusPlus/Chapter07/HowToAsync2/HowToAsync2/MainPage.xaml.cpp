//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HowToAsync2;

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
    MessageDialog^ msgdlg = ref new MessageDialog("Choose a color", "How To Async #2");
    msgdlg->Commands->Append(ref new UICommand("Red", nullptr, Colors::Red));
    msgdlg->Commands->Append(ref new UICommand("Green", nullptr, Colors::Green));
    msgdlg->Commands->Append(ref new UICommand("Blue", nullptr, Colors::Blue));

    // Show the MessageDialog with a Completed handler
    IAsyncOperation<IUICommand^>^ asyncOp = msgdlg->ShowAsync();
    asyncOp->Completed = ref new AsyncOperationCompletedHandler<IUICommand^>(
        [this](IAsyncOperation<IUICommand^>^ asyncInfo, AsyncStatus asyncStatus)
        {
            // Get the Color value
            IUICommand^ command = asyncInfo->GetResults();
            Color clr = (Color)command->Id;

            // Use a Dispatcher to run in the UI thread
            IAsyncAction^ asyncAction = this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, 
                                                                   ref new DispatchedHandler(
                [this, clr]()
                {
                    // Set the background brush
                    contentGrid->Background = ref new SolidColorBrush(clr);
                }));
        });
}