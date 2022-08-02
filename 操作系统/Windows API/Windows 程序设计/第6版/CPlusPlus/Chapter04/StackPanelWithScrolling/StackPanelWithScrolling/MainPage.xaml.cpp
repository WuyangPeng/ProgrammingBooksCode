//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace StackPanelWithScrolling;

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

// C# assembly
using namespace ReflectionHelper;

MainPage::MainPage()
{
    InitializeComponent();

    TypeName colorsTypeName = { Colors::typeid->FullName, TypeKind::Metadata };

    // Implemented in C# assembly ReflectionHelper
    TypeInformation^ typeInfo = ref new TypeInformation(colorsTypeName);
    IIterable<PropertyInformation^>^ properties = typeInfo->DeclaredProperties;

    for each (PropertyInformation^ property in properties)
    {
        Windows::UI::Color clr = static_cast<Windows::UI::Color>(property->GetValue(nullptr));
        wchar_t str[40];
        swprintf(str, sizeof(str) / sizeof(str[0]), 
                      L"%s \x2014 %02X-%02X-%02X-%02X", 
                      property->Name->Data(), 
                      clr.A, clr.R, clr.G, clr.B);

        TextBlock^ txtblk = ref new TextBlock();
        txtblk->Text = ref new String(str);
        stackPanel->Children->Append(txtblk);
    }
}
