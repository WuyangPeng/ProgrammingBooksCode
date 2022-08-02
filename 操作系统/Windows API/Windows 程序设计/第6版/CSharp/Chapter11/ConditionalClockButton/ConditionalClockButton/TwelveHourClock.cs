namespace ConditionalClockButton
{
    public class TwelveHourClock : ClockButton.Clock
    {
        // Initialize for Hour value of 0
        int hour12 = 12;
        bool isAm = true;
        bool isPm = false;

        public int Hour12
        {
            set { SetProperty<int>(ref hour12, value); }
            get { return hour12; }
        }

        public bool IsAm
        {
            set { SetProperty<bool>(ref isAm, value); }
            get { return isAm; }
        }

        public bool IsPm
        {
            set { SetProperty<bool>(ref isPm, value); }
            get { return isPm; }
        }

        protected override void OnPropertyChanged(string propertyName)
        {
            if (propertyName == "Hour")
            {
                this.Hour12 = (this.Hour - 1) % 12 + 1;
                this.IsAm = this.Hour < 12;
                this.IsPm = !this.IsAm;
            }

            base.OnPropertyChanged(propertyName);
        }
    }
}
