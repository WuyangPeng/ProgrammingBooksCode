//
// StudentPage.xaml.h
// Declaration of the StudentPage class
//

#pragma once

#include "StudentPage.g.h"

namespace DisplayHighSchoolStudents
{
    public ref class StudentPage sealed
    {
    public:
        StudentPage();

    protected:
        void OnPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        void OnBackButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
