//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace TapAndShowPoint;

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
using namespace Windows::UI::Xaml::Shapes;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnTapped(TappedRoutedEventArgs^ args)
{
    Point pt = args->GetPosition(this);

    // Create dot
    Ellipse^ ellipse = ref new Ellipse();
    ellipse->Width = 3;
    ellipse->Height = 3;
    ellipse->Fill = this->Foreground;

    Canvas::SetLeft(ellipse, pt.X);
    Canvas::SetTop(ellipse, pt.Y);
    canvas->Children->Append(ellipse);

    // Create text
    TextBlock^ txtblk = ref new TextBlock();
    txtblk->Text = "(" + pt.X.ToString() + ", " + pt.Y.ToString() + ")";
    txtblk->FontSize = 24;

    Canvas::SetLeft(txtblk, pt.X);
    Canvas::SetTop(txtblk, pt.Y);
    canvas->Children->Append(txtblk);

    args->Handled = true;
}
