//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ColorItems;

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

// C# assembly
using namespace ReflectionHelper;

MainPage::MainPage()
{
    InitializeComponent();

    // Implemented in C# assembly ReflectionHelper
    TypeInformation^ typeInfo = ref new TypeInformation(Colors::typeid);
    IIterable<PropertyInformation^>^ properties = typeInfo->DeclaredProperties;

    for each (PropertyInformation^ property in properties)
    {
        Color clr = (Color)property->GetValue(nullptr);
        itemsControl->Items->Append(clr);
    }
}
