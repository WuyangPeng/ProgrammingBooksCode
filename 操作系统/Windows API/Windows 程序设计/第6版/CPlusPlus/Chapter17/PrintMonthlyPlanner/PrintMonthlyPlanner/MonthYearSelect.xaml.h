//
// MonthYearSelect.xaml.h
// Declaration of the MonthYearSelect class
//

#pragma once

#include "MonthYearSelect.g.h"

namespace PrintMonthlyPlanner
{
    public ref class MonthYearSelect sealed
    {
    private:
        Windows::Globalization::Calendar^ monthYear;

    public:
        MonthYearSelect();

        event Windows::Foundation::EventHandler<Windows::Globalization::Calendar^>^ MonthYearChanged;

        property Windows::Globalization::Calendar^ MonthYear
        {
            Windows::Globalization::Calendar^ get();
        }

    private:
        void OnMonthYearSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
    };
}
