//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ColorList1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

using namespace ReflectionHelper;

MainPage::MainPage()
{
    InitializeComponent();

    // Implemented in C# assembly ReflectionHelper
    TypeInformation^ typeInfo = ref new TypeInformation(Colors::typeid);
    IIterable<PropertyInformation^>^ properties = typeInfo->DeclaredProperties;

    for each (PropertyInformation^ property in properties)
    {
        Color clr = static_cast<Color>(property->GetValue(nullptr));
        
        StackPanel^ vertStackPanel = ref new StackPanel();
        vertStackPanel->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

        TextBlock^ txtblkName = ref new TextBlock();
        txtblkName->Text = property->Name;
        txtblkName->FontSize = 24;
        vertStackPanel->Children->Append(txtblkName);

        TextBlock^ txtblkRgb = ref new TextBlock();
        wchar_t str[16];
        swprintf(str, sizeof(str) / sizeof(str[0]),
                      L"%02X-%02X-%02X-%02X", 
                      clr.A, clr.R, clr.G, clr.B);
        txtblkRgb->Text = ref new String(str);
        txtblkRgb->FontSize = 18;
        vertStackPanel->Children->Append(txtblkRgb);

        StackPanel^ horzStackPanel = ref new StackPanel();
        horzStackPanel->Orientation = Orientation::Horizontal;

        Rectangle^ rectangle = ref new Rectangle();
        rectangle->Width = 72;
        rectangle->Height = 72;
        rectangle->Fill = ref new SolidColorBrush(clr);
        rectangle->Margin = Thickness(6);
        
        horzStackPanel->Children->Append(rectangle);
        horzStackPanel->Children->Append(vertStackPanel);
        stackPanel->Children->Append(horzStackPanel);
    }
}
