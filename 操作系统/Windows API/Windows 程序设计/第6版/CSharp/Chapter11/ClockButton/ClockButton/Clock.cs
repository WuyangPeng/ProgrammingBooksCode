using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.UI.Xaml.Media;

namespace ClockButton
{
    public class Clock : INotifyPropertyChanged
    {
        bool isEnabled;
        int hour, minute, second;
        int hourAngle, minuteAngle, secondAngle;

        public event PropertyChangedEventHandler PropertyChanged;

        public bool IsEnabled
        {
            set
            {
                if (SetProperty<bool>(ref isEnabled, value, "IsEnabled"))
                {
                    if (isEnabled)
                        CompositionTarget.Rendering += OnCompositionTargetRendering;
                    else
                        CompositionTarget.Rendering -= OnCompositionTargetRendering;
                }
            }
            get
            {
                return isEnabled;
            }
        }

        public int Hour
        {
            set { SetProperty<int>(ref hour, value); }
            get { return hour; }
        }

        public int Minute 
        {
            set { SetProperty<int>(ref minute, value); }
            get { return minute; }
        }

        public int Second
        {
            set { SetProperty<int>(ref second, value); }
            get { return second; }
        }

        public int HourAngle
        {
            set { SetProperty<int>(ref hourAngle, value); }
            get { return hourAngle; }
        }

        public int MinuteAngle
        {
            set { SetProperty<int>(ref minuteAngle, value); }
            get { return minuteAngle; }
        }
        public int SecondAngle
        {
            set { SetProperty<int>(ref secondAngle, value); }
            get { return secondAngle; }
        }

        void OnCompositionTargetRendering(object sender, object args)
        {
            DateTime dateTime = DateTime.Now;
            this.Hour = dateTime.Hour;
            this.Minute = dateTime.Minute;
            this.Second = dateTime.Second;

            this.HourAngle = 30 * dateTime.Hour + dateTime.Minute / 2;
            this.MinuteAngle = 6 * dateTime.Minute + dateTime.Second / 10;
            this.SecondAngle = 6 * dateTime.Second + dateTime.Millisecond / 166;
        }

        protected bool SetProperty<T>(ref T storage, T value,
                                      [CallerMemberName] string propertyName = null)
        {
            if (object.Equals(storage, value))
                return false;

            storage = value;
            OnPropertyChanged(propertyName);
            return true;
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
