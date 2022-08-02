using System;
using Windows.Globalization;
using Windows.Globalization.DateTimeFormatting;
using Windows.UI.Xaml.Controls;

namespace PrintMonthlyPlanner
{
    public sealed partial class MonthYearSelect : UserControl
    {
        public event EventHandler MonthYearChanged;

        public MonthYearSelect()
        {
            this.InitializeComponent();

            // Create Calendar with current date
            Calendar calendar = new Calendar();
            calendar.SetToNow();

            // Fill the first FlipView with the abbreviated month names
            DateTimeFormatter monthFormatter = 
                new DateTimeFormatter(YearFormat.None, MonthFormat.Abbreviated, 
                                      DayFormat.None, DayOfWeekFormat.None);

            for (int month = 1; month <= 12; month++)
            {
                string strMonth = monthFormatter.Format(
                                    new DateTimeOffset(2000, month, 15, 0, 0, 0, TimeSpan.Zero));
                monthFlipView.Items.Add(strMonth);
            }

            // Fill the second FlipView with years (5 years before current, 25 after
            for (int year = calendar.Year - 5; year <= calendar.Year + 25; year++)
            {
                yearFlipView.Items.Add(year);
            }

            // Set the FlipView's to the current month and year
            monthFlipView.SelectedIndex = calendar.Month - 1;
            yearFlipView.SelectedItem = calendar.Year;
            this.MonthYear = calendar;
        }

        public Calendar MonthYear { private set; get; }

        void OnMonthYearSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            if (this.MonthYear == null)
                return;
            
            if (monthFlipView.SelectedIndex != -1)
                this.MonthYear.Month = (int)monthFlipView.SelectedIndex + 1;

            if (yearFlipView.SelectedIndex != -1)
                this.MonthYear.Year = (int)yearFlipView.SelectedItem;

            // Fire the event
            if (MonthYearChanged != null)
                MonthYearChanged(this, EventArgs.Empty);
        }
    }
}
