//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ColorTextBoxesWithEvents;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::ViewManagement;
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

    // Set brush fields
    textBoxTextBrush = dynamic_cast<Brush^>(this->Resources->Lookup("TextBoxForegroundThemeBrush"));
    textBoxErrorBrush = ref new SolidColorBrush(Colors::Red);
    
    // Create RgbViewModel and save as field
    rgbViewModel = ref new RgbViewModel();
    rgbViewModel->PropertyChanged += ref new PropertyChangedEventHandler(this, &MainPage::OnRgbViewModelPropertyChanged); 
    this->DataContext = rgbViewModel;

    // Initialize to highlight color
    rgbViewModel->Color = (ref new UISettings())->UIElementColor(UIElementType::Highlight);
}

void MainPage::OnRgbViewModelPropertyChanged(Object^ sender, PropertyChangedEventArgs^ args)
{
    if (args->PropertyName == "Red")
        redTextBox->Text = rgbViewModel->Red.ToString();

    else if (args->PropertyName == "Green")
        greenTextBox->Text = rgbViewModel->Green.ToString();

    else if (args->PropertyName == "Blue")
        blueTextBox->Text = rgbViewModel->Blue.ToString();
}

void MainPage::OnTextBoxTextChanged(Object^ sender, TextChangedEventArgs^ args)
{
    TextBox^ txtbox = dynamic_cast<TextBox^>(sender);
    int value = 0;

    if (txtbox == redTextBox && Validate(redTextBox, &value))
        rgbViewModel->Red = value;

    else if (txtbox == greenTextBox && Validate(greenTextBox, &value))
        rgbViewModel->Green = value;

    else if (txtbox == blueTextBox && Validate(blueTextBox, &value))
        rgbViewModel->Blue = value;
}

bool MainPage::Validate(TextBox^ txtbox, int* value)
{
    String^ text = txtbox->Text;
    const wchar_t* str = text->Data();
    bool valid = false;

    for (int i = 0; str[i] != '\0'; i++)
    {
        wchar_t ch = str[i];
        valid = isdigit(ch) != 0;

        if (!valid)
            break;

        *value = 10 * *value + ch - '0';
        valid = *value < 256;

        if (!valid)
            break;
    }
    txtbox->Foreground = valid ? textBoxTextBrush : textBoxErrorBrush;
    return valid;
}