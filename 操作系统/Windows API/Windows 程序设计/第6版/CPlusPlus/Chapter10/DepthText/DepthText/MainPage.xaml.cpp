//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace DepthText;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Text;
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

    Grid^ grid = dynamic_cast<Grid^>(this->Content);
    Brush^ foreground = dynamic_cast<Brush^>(this->Resources->Lookup("ApplicationForegroundThemeBrush"));
    Brush^ grayBrush = ref new SolidColorBrush(Colors::Gray);

    for (int i = 0; i < COUNT; i++)
    {
        bool firstOrLast = i == 0 || i == COUNT - 1;

        TextBlock^ txtblk = ref new TextBlock();
        txtblk->Text = "DEPTH";
        txtblk->FontSize = 192;
        txtblk->FontWeight = FontWeights::Bold;
        txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
        txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
        txtblk->Foreground = firstOrLast ? foreground : grayBrush;

        TranslateTransform^ translateTransform = ref new TranslateTransform();
        translateTransform->X = COUNT - i - 1;
        translateTransform->Y = i - COUNT + 1;
        txtblk->RenderTransform = translateTransform;

        grid->Children->Append(txtblk);
    }
}

