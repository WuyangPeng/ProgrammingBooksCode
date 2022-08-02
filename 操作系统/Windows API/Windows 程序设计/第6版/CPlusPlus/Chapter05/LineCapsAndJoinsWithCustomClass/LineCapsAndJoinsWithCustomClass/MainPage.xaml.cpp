//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "LineCapRadioButton.h"
#include "LineJoinRadioButton.h"

using namespace LineCapsAndJoinsWithCustomClass;

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
                LineCapRadioButton^ radioButton = dynamic_cast<LineCapRadioButton^>(startLineCapPanel->Children->GetAt(index));
                radioButton->IsChecked = radioButton->LineCapTag == polyline->StrokeStartLineCap;
            }

            for (unsigned int index = 0; index < endLineCapPanel->Children->Size; index++)
            {
                LineCapRadioButton^ radioButton = dynamic_cast<LineCapRadioButton^>(endLineCapPanel->Children->GetAt(index));
                radioButton->IsChecked = radioButton->LineCapTag == polyline->StrokeEndLineCap;
            }

            for (unsigned int index = 0; index < lineJoinPanel->Children->Size; index++)
            {
                LineJoinRadioButton^ radioButton = dynamic_cast<LineJoinRadioButton^>(lineJoinPanel->Children->GetAt(index));
                radioButton->IsChecked = radioButton->LineJoinTag == polyline->StrokeLineJoin;
            }
    });
}

void MainPage::OnStartLineCapRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeStartLineCap = dynamic_cast<LineCapRadioButton^>(sender)->LineCapTag;
}

void MainPage::OnEndLineCapRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeEndLineCap = dynamic_cast<LineCapRadioButton^>(sender)->LineCapTag;
}

void MainPage::OnLineJoinRadioButtonChecked(Object^ sender, RoutedEventArgs^ arg)
{
    polyline->StrokeLineJoin = dynamic_cast<LineJoinRadioButton^>(sender)->LineJoinTag;
}
