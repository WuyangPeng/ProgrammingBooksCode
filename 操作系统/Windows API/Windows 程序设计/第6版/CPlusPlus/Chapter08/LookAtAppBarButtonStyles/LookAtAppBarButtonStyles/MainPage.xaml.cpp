//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace LookAtAppBarButtonStyles;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Automation;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    appBarStyles = ref new Vector<Item^>();
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnLoaded);
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Basically ges StandardStyles.xaml
    ResourceDictionary^ dictionary = Application::Current->Resources->MergedDictionaries->GetAt(0);
    Windows::UI::Xaml::Style^ baseStyle = dynamic_cast<Windows::UI::Xaml::Style^>(dictionary->Lookup("AppBarButtonStyle"));

    // Find all styles based on AppBarButtonStyle
    for each (IKeyValuePair<Object^, Object^>^ pair in dictionary)
    {
        Windows::UI::Xaml::Style^ style = dynamic_cast<Windows::UI::Xaml::Style^>(pair->Value);

        if (style != nullptr && style->BasedOn != nullptr && style->BasedOn == baseStyle)
        {
            Item^ item = ref new Item();
            item->Key = dynamic_cast<String^>(pair->Key);

            for each (SetterBase^ setterBase in style->Setters)
            {
                Setter^ setter = dynamic_cast<Setter^>(setterBase);

                if (setter->Property == AutomationProperties::NameProperty)
                {
                    item->Text = dynamic_cast<String^>(setter->Value);
                }

                if (setter->Property == ButtonBase::ContentProperty)
                {
                    item->Symbol = dynamic_cast<String^>(setter->Value)->Data()[0];
                }
            }

            appBarStyles->Append(item);
        }
    }

    // Display items by checking RadioButton
    symbolSortRadio->IsChecked = true;
}

void MainPage::OnRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    if (dynamic_cast<RadioButton^>(sender) == symbolSortRadio)
    {
        // Sort by symbol
        std::sort(begin(appBarStyles), end(appBarStyles), [] (Item^ item1, Item^ item2)
        {
            return item1->Symbol < item2->Symbol;
        });
    }
    else
    {
        // Sort by text
        std::sort(begin(appBarStyles), end(appBarStyles), [] (Item^ item1, Item^ item2)
        {
            return item1->Text < item2->Text;
        });
    }

    // Close app bar and display the items
    this->BottomAppBar->IsOpen = false;
    DisplayList();
}

void MainPage::DisplayList()
{
    static Windows::UI::Xaml::Media::FontFamily^ segoeSymbolFont =
                ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI Symbol");

    // Clear the StackPanel
    stackPanel->Children->Clear();

    // Loop through the styles
    for each (Item^ item in appBarStyles)
    {
        // A StackPanel for each item
        StackPanel^ itemPanel = ref new StackPanel();
        itemPanel->Orientation = Windows::UI::Xaml::Controls::Orientation::Horizontal;
        itemPanel->Margin = ThicknessHelper::FromLengths(0, 6, 0, 6);

        // The symbol itself
        TextBlock^ textBlock = ref new TextBlock();
        textBlock->Text = item->Symbol.ToString();
        textBlock->FontFamily = segoeSymbolFont;
        textBlock->Margin = ThicknessHelper::FromLengths(24, 0, 24, 0);
        itemPanel->Children->Append(textBlock);

        // The Unicode identifier
        wchar_t str[8];
        swprintf(str, sizeof(str) / sizeof(str[0]), L"0x%04X", (int)item->Symbol);

        textBlock = ref new TextBlock();
        textBlock->Text = ref new String(str);
        textBlock->Width = 96;
        itemPanel->Children->Append(textBlock);

        // The text for the Button
        textBlock = ref new TextBlock();
        textBlock->Text = "\"" + item->Text + "\"";
        textBlock->Width = 240;
        itemPanel->Children->Append(textBlock);

        // The key name
        textBlock = ref new TextBlock();
        textBlock->Text = item->Key;
        itemPanel->Children->Append(textBlock);

        stackPanel->Children->Append(itemPanel);
    }
}
