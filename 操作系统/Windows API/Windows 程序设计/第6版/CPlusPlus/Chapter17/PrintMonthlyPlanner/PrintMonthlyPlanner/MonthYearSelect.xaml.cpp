//
// MonthYearSelect.xaml.cpp
// Implementation of the MonthYearSelect class
//

#include "pch.h"
#include "MonthYearSelect.xaml.h"

using namespace PrintMonthlyPlanner;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MonthYearSelect::MonthYearSelect()
{
    InitializeComponent();

    // Create Calendar with current date
    Calendar^ calendar = ref new Calendar();
    calendar->SetToNow();

    // Fill the first FlipView with the abbreviated month names
    DateTimeFormatter^ monthFormatter = 
        ref new DateTimeFormatter(YearFormat::None, MonthFormat::Abbreviated,
                                  DayFormat::None, DayOfWeekFormat::None);

    for (int month = 1; month <= 12; month++)
    {
        calendar->Month = month;
        String^ strMonth = monthFormatter->Format(calendar->GetDateTime());
        monthFlipView->Items->Append(strMonth);
    }

    // Fill the second FlipView with years (5 years before current, 25 after)
    for (int year = calendar->Year - 5; year <= calendar->Year + 25; year++)
    {
        yearFlipView->Items->Append(year);
    }

    // Set the FlipView's to the current month and year
    calendar->SetToNow();
    monthFlipView->SelectedIndex = calendar->Month - 1;
    yearFlipView->SelectedItem = calendar->Year;
    monthYear = calendar;
}

Calendar^ MonthYearSelect::MonthYear::get()
{
    return monthYear;
}

void MonthYearSelect::OnMonthYearSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    if (this->MonthYear == nullptr)
        return;

    if (monthFlipView->SelectedIndex != -1)
        this->MonthYear->Month = (int)monthFlipView->SelectedIndex + 1;

    if (yearFlipView->SelectedIndex != 1)
        this->MonthYear->Year = (int)yearFlipView->SelectedItem;

    // Fire the event
    MonthYearChanged(this, this->MonthYear);
}


