//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace GradientBrushCode;

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

    // Create the foreground brush for the TextBlock
    LinearGradientBrush^ foregroundBrush = ref new LinearGradientBrush();
    foregroundBrush->StartPoint = Point(0, 0);
    foregroundBrush->EndPoint = Point(1, 0);

    GradientStop^ gradientStop = ref new GradientStop();
    gradientStop->Offset = 0;
    gradientStop->Color = Colors::Blue;
    foregroundBrush->GradientStops->Append(gradientStop);

    gradientStop = ref new GradientStop();
    gradientStop->Offset = 1;
    gradientStop->Color = Colors::Red;
    foregroundBrush->GradientStops->Append(gradientStop);
    
    txtblk->Foreground = foregroundBrush;

    // Create the background brush for the Grid
    LinearGradientBrush^ backgroundBrush = ref new LinearGradientBrush();
    backgroundBrush->StartPoint = Point(0, 0);
    backgroundBrush->EndPoint = Point(1, 0);

    gradientStop = ref new GradientStop();
    gradientStop->Offset = 0;
    gradientStop->Color = Colors::Red;
    backgroundBrush->GradientStops->Append(gradientStop);

    gradientStop = ref new GradientStop();
    gradientStop->Offset = 1;
    gradientStop->Color = Colors::Blue;
    backgroundBrush->GradientStops->Append(gradientStop);
    
    contentGrid->Background = backgroundBrush;
}
