//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PathMarkupSyntaxCode;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

MainPage::MainPage()
{
    InitializeComponent();

    Path^ path = ref new Path();
    path->Stroke = ref new SolidColorBrush(Colors::Red);
    path->StrokeThickness = 12;
    path->StrokeLineJoin = PenLineJoin::Round;
    path->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    path->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
    path->Data = PathMarkupToGeometry(
        "M 0 0 L 0 100 M 0 50 L 50 50 M 50 0 L 50 100 " +
        "M 125 0 C 60 -10, 60 60, 125 50, 60 40, 60 110, 125 100 " +
        "M 150 0 L 150 100, 200 100 " +
        "M 225 0 L 225 100, 275 100 " +
        "M 300 50 A 25 50 0 1 0 300 49.9");

    (dynamic_cast<Grid^>(this->Content))->Children->Append(path);
}

Geometry^ MainPage::PathMarkupToGeometry(String^ pathMarkup)
{
    String^ xaml = 
        "<Path " +
        "xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation'>" +
        "<Path.Data>" + pathMarkup + "</Path.Data></Path>";

    Path^ path = dynamic_cast<Path^>(XamlReader::Load(xaml));

    // Detach the PathGeometry from the Path
    Geometry^ geometry = path->Data;
    path->Data = nullptr;
    return geometry;
}