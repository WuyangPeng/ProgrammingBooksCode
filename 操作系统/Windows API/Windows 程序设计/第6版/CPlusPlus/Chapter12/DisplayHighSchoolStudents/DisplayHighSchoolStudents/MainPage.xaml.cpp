//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace DisplayHighSchoolStudents;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    this->NavigationCacheMode = Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled;
    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnPageSizeChanged);
}

void MainPage::OnPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    VisualStateManager::GoToState(this, ApplicationView::Value.ToString(), true);
}

void MainPage::OnGridViewItemClick(Object^ sender, ItemClickEventArgs^ args)
{
    this->Frame->Navigate(TypeName(StudentPage::typeid), args->ClickedItem);
}

