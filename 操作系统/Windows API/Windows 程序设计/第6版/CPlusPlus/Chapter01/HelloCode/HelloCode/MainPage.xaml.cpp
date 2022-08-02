//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HelloCode;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
    InitializeComponent();

    TextBlock^ txtblk = ref new TextBlock();
    txtblk->Text = "Hello, Windows 8!"; 
    txtblk->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Times New Roman");
    txtblk->FontSize = 96;
    txtblk->FontStyle = Windows::UI::Text::FontStyle::Italic;
    txtblk->Foreground = ref new SolidColorBrush(Colors::Yellow);
    txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

    contentGrid->Children->Append(txtblk);
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
    (void) e;    // Unused parameter
}
