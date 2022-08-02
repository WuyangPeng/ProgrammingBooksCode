//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleContextMenu;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Popups;
using namespace Windows::UI;
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

void MainPage::OnTextBlockRightTapped(Object^ sender, RightTappedRoutedEventArgs^ args)
{
    PopupMenu^ popup = ref new PopupMenu();
    popup->Commands->Append(ref new UICommand("Larger Font", 
        ref new UICommandInvokedHandler(this, &MainPage::OnFontSizeChanged), 1.2));
    popup->Commands->Append(ref new UICommand("Smaller Font", 
        ref new UICommandInvokedHandler(this, &MainPage::OnFontSizeChanged), 1 / 1.2));

    popup->Commands->Append(ref new UICommandSeparator());

    popup->Commands->Append(ref new UICommand("Red", 
        ref new UICommandInvokedHandler(this, &MainPage::OnColorChanged), Colors::Red));
    popup->Commands->Append(ref new UICommand("Green", 
        ref new UICommandInvokedHandler(this, &MainPage::OnColorChanged), Colors::Green));
    popup->Commands->Append(ref new UICommand("Blue", 
        ref new UICommandInvokedHandler(this, &MainPage::OnColorChanged), Colors::Blue));

    task<IUICommand^> showPopupTask = create_task(popup->ShowAsync(args->GetPosition(this)));
    showPopupTask.then([] (IUICommand^ command) {});
}

void MainPage::OnFontSizeChanged(IUICommand^ command)
{
    textBlock->FontSize *= (double)command->Id;
}

void MainPage::OnColorChanged(IUICommand^ command)
{
    textBlock->Foreground = ref new SolidColorBrush((Color)command->Id);
}
