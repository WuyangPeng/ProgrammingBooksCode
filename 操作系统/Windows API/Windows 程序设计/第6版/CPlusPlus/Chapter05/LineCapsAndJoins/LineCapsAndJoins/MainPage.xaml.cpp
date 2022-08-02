//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace LineCapsAndJoins;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
        {
            for (unsigned int index = 0; index < startLineCapPanel->Children->Size; index++)
            {
                RadioButton^ radioButton = dynamic_cast<RadioButton^>(startLineCapPanel->Children->GetAt(index));
                radioButton->IsChecked = PenLineCap((int)(radioButton->Tag)) == polyline->StrokeStartLineCap;
            }

            for (unsigned int index = 0; index < endLineCapPanel->Children->Size; index++)
            {
                RadioButton^ radioButton = dynamic_cast<RadioButton^>(endLineCapPanel->Children->GetAt(index));
                radioButton->IsChecked = PenLineCap((int)(radioButton->Tag)) == polyline->StrokeEndLineCap;
            }

            for (unsigned int index = 0; index < lineJoinPanel->Children->Size; index++)
            {
                RadioButton^ radioButton = dynamic_cast<RadioButton^>(lineJoinPanel->Children->GetAt(index));
                radioButton->IsChecked = PenLineJoin((int)(radioButton->Tag)) == polyline->StrokeLineJoin;
            }
        });
}

void MainPage::OnStartLineCapRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeStartLineCap = PenLineCap((int)(dynamic_cast<RadioButton^>(sender)->Tag));
}

void MainPage::OnEndLineCapRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeEndLineCap = PenLineCap((int)(dynamic_cast<RadioButton^>(sender)->Tag));
}

void MainPage::OnLineJoinRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeLineJoin = PenLineJoin((int)(dynamic_cast<RadioButton^>(sender)->Tag));
}
