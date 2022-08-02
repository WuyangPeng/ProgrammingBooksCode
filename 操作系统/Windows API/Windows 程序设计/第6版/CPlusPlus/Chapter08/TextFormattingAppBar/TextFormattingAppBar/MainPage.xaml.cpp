//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace TextFormattingAppBar;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnBoldAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
    bool isChecked = checkBox->IsChecked->Value;
    textBlock->FontWeight = isChecked ? FontWeights::Bold : FontWeights::Normal;
}

void MainPage::OnItalicAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
    bool isChecked = checkBox->IsChecked->Value;
    textBlock->FontStyle = isChecked ? Windows::UI::Text::FontStyle::Italic : 
                                       Windows::UI::Text::FontStyle::Normal;
}

void MainPage::OnUnderlineAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
    bool isChecked = checkBox->IsChecked->Value;

    Inline^ inlineRun = textBlock->Inlines->GetAt(0);
    bool isUnderline = nullptr != dynamic_cast<Underline^>(inlineRun);

    if (isChecked && !isUnderline)
    {
        Underline^ underline = ref new Underline();
        textBlock->Inlines->SetAt(0, underline);
        underline->Inlines->Append(inlineRun);
    }
    else if (!isChecked && isUnderline)
    {
        Underline^ underline = dynamic_cast<Underline^>(inlineRun);
        Run^ run = dynamic_cast<Run^>(underline->Inlines->GetAt(0));
        underline->Inlines->Clear();
        textBlock->Inlines->SetAt(0, run);
    }
}

void MainPage::OnFontColorAppBarRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    textBlock->Foreground = dynamic_cast<RadioButton^>(sender)->Foreground;
}
