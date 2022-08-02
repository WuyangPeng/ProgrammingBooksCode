//
// ColorItem.xaml.cpp
// Implementation of the ColorItem class
//

#include "pch.h"
#include "ColorItem.xaml.h"

using namespace ColorList2;

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

ColorItem::ColorItem(String^ name, Color clr)
{
    InitializeComponent();

    wchar_t str[16];
    swprintf(str,
             sizeof(str) / sizeof(str[0]),
             L"%02X-%02X-%02X-%02X", 
             clr.A, clr.R, clr.G, clr.B);
    
    rectangle->Fill = ref new SolidColorBrush(clr);
    txtblkName->Text = name;
    txtblkRgb->Text = ref new String(str);
}
