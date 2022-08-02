//
// AboutBox.xaml.cpp
// Implementation of the AboutBox class
//

#include "pch.h"
#include "AboutBox.xaml.h"

using namespace FingerPaint;

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

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

AboutBox::AboutBox()
{
    InitializeComponent();
}

void AboutBox::OnBackButtonClick(Object^ sender, RoutedEventArgs^  args)
{
    // Dismiss Popup
    Popup^ popup = dynamic_cast<Popup^>(this->Parent);

    if (popup != nullptr)
        popup->IsOpen = false;
}
