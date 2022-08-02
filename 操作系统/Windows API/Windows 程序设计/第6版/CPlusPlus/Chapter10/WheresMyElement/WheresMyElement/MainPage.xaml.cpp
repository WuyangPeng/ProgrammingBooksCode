//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace WheresMyElement;

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
}

void MainPage::OnTapped(TappedRoutedEventArgs^ args)
{
    if (storyboardPaused)
    {
        storyboard->Resume();
        storyboardPaused = false;
        return;
    }

    GeneralTransform^ xform = txtblk->TransformToVisual(contentGrid);

    // Draw blue polygon around element
    polygon->Points->Clear();
    polygon->Points->Append(xform->TransformPoint(Point(0, 0)));
    polygon->Points->Append(xform->TransformPoint(Point((float)txtblk->ActualWidth, 0)));
    polygon->Points->Append(xform->TransformPoint(Point((float)txtblk->ActualWidth, 
                                                        (float)txtblk->ActualHeight)));
    polygon->Points->Append(xform->TransformPoint(Point(0, (float)txtblk->ActualHeight)));

    // Draw red bounding box
    RectangleGeometry^ rectangleGeometry = ref new RectangleGeometry();
    rectangleGeometry->Rect = xform->TransformBounds(Rect(Point(0, 0), txtblk->DesiredSize));
    path->Data = rectangleGeometry;

    storyboard->Pause();
    storyboardPaused = true;
}
