//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace WhatSnap;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
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

    this->SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);
    DisplayProperties::LogicalDpiChanged += ref new DisplayPropertiesEventHandler(this, &MainPage::OnLogicalDpiChanged);

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
    {
        UpdateDisplay();
    });
}

void MainPage::OnMainPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    UpdateDisplay();
}

void MainPage::OnLogicalDpiChanged(Object^ sender)
{
    UpdateDisplay();
}

void MainPage::UpdateDisplay()
{
    float logicalDpi = DisplayProperties::LogicalDpi;
    int pixelWidth = (int)(logicalDpi * this->ActualWidth / 96 + 0.5f);
    int pixelHeight = (int)(logicalDpi * this->ActualHeight / 96 + 0.5f);

    wchar_t str[256];
    swprintf(str, sizeof(str) / sizeof(str[0]),
             L"ApplicationViewState = %s\r\n"
             L"Windows size = %.2f x %.2f\r\n"
             L"ResolutionScale = %s\r\n"
             L"Logical DPI = %.1f\r\n"
             L"Pixel size = %i x %i",
             ApplicationView::Value.ToString()->Data(),
             this->ActualWidth, this->ActualHeight,
             DisplayProperties::ResolutionScale.ToString()->Data(),
             DisplayProperties::LogicalDpi,
             pixelWidth, pixelHeight);

    textBlock->Text = ref new String(str);
}
