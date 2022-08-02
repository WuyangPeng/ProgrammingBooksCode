//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleContextDialog;

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

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnTextBlockRightTapped(Object^ sender, RightTappedRoutedEventArgs^ args)
{
    StackPanel^ stackPanel = ref new StackPanel();

    // Create two Button controls and add to StackPanel
    Button^ btn1 = ref new Button();
    btn1->Content = "Larger font";
    btn1->Tag = 1.2;
    btn1->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    btn1->Margin = ThicknessHelper::FromUniformLength(12);
    btn1->Click += ref new RoutedEventHandler(this, &MainPage::OnButtonClick);
    stackPanel->Children->Append(btn1);

    Button^ btn2 = ref new Button();
    btn2->Content = "Smaller font";
    btn2->Tag = 1 / 1.2;
    btn2->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    btn2->Margin = ThicknessHelper::FromUniformLength(12);
    btn2->Click += ref new RoutedEventHandler(this, &MainPage::OnButtonClick);
    stackPanel->Children->Append(btn2);

    // Create three RadioButton controls and add to StackPanel
    static Array<String^>^ names = { "Red", "Green", "Blue" };
    static Color colors[] = { Colors::Red, Colors::Green, Colors::Blue };

    for (unsigned int i = 0; i < names->Length; i++)
    {
        RadioButton^ radioButton = ref new RadioButton();
        radioButton->Content = names[i];
        radioButton->Foreground = ref new SolidColorBrush(colors[i]);
        radioButton->IsChecked = 
            AreColorsEqual(dynamic_cast<SolidColorBrush^>(textBlock->Foreground)->Color, colors[i]);
        radioButton->Margin = ThicknessHelper::FromUniformLength(12);
        radioButton->Checked += ref new RoutedEventHandler(this, &MainPage::OnRadioButtonClick);
        stackPanel->Children->Append(radioButton);
    }

    // Create a Border for the StackPanel
    Border^ border = ref new Border();
    border->Child = stackPanel;
    border->Background = dynamic_cast<SolidColorBrush^>(this->Resources->Lookup("ApplicationPageBackgroundThemeBrush"));
    border->BorderBrush = dynamic_cast<SolidColorBrush^>(this->Resources->Lookup("ApplicationForegroundThemeBrush"));
    border->BorderThickness = ThicknessHelper::FromUniformLength(1);
    border->Padding = ThicknessHelper::FromUniformLength(24);

    // Create the Popup object
    Popup^ popup = ref new Popup();
    popup->Child = border;
    popup->IsLightDismissEnabled = true;

    // Adjust location based on content size
    border->Loaded += ref new RoutedEventHandler([this, args, popup, border, btn1] (Object^ sender, RoutedEventArgs^)
    {
        Point point = args->GetPosition(this);
        point.X -= float(border->ActualWidth) / 2;
        point.Y -= float(border->ActualHeight);

        // Leave at least a quarter inch margin
        popup->HorizontalOffset = min(this->ActualWidth - border->ActualWidth - 24, max(24, point.X));
        popup->VerticalOffset = min(this->ActualHeight - border->ActualHeight - 24, max(24, point.Y));

        auto x = popup->HorizontalOffset;
        auto y = popup->VerticalOffset;

        // Set keyboard focus to first element
        btn1->Focus(Windows::UI::Xaml::FocusState::Programmatic);
    });

    // Open the popup
    popup->IsOpen = true;
}

bool MainPage::AreColorsEqual(Color clr1, Color clr2)
{
    return clr1.A == clr2.A && clr1.R == clr2.R && clr1.G == clr2.G && clr1.B == clr2.B;
}

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    textBlock->FontSize *= (double)dynamic_cast<Button^>(sender)->Tag;
}

void MainPage::OnRadioButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    textBlock->Foreground = dynamic_cast<RadioButton^>(sender)->Foreground;
}
