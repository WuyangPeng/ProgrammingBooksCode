//
// StudentPage.xaml.cpp
// Implementation of the StudentPage class
//

#include "pch.h"
#include "StudentPage.xaml.h"

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
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

StudentPage::StudentPage()
{
    InitializeComponent();
}

void StudentPage::OnPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
   VisualStateManager::GoToState(this, ApplicationView::Value.ToString(), true);
}

void StudentPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    this->DataContext = args->Parameter;
}

void StudentPage::OnBackButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoBack();
}
