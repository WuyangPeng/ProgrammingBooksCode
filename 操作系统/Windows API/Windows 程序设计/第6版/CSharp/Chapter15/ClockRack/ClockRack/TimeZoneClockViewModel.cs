using System;
using System.ComponentModel;
using System.Reflection;
using System.Runtime.CompilerServices;
using Windows.UI;

namespace ClockRack
{
    public class TimeZoneClockViewModel : INotifyPropertyChanged
    {
        string location = "New York City", timeZoneKey = "Eastern Standard Time";
        Color background = Colors.Yellow, foreground = Colors.Blue;
        string backgroundName = "Yellow", foregroundName = "Blue";
        DateTime dateTime;
        string formattedDateTime;
        double hourAngle, minuteAngle, secondAngle;
        TypeInfo colorsTypeInfo = typeof(Colors).GetTypeInfo();

        public event PropertyChangedEventHandler PropertyChanged;

        public string Location
        {
            set { SetProperty<string>(ref location, value); }
            get { return location; }
        }

        public string TimeZoneKey
        {
            set { SetProperty<string>(ref timeZoneKey, value); }
            get { return timeZoneKey; }
        }

        public string BackgroundName 
        { 
            set 
            { 
                if (SetProperty<string>(ref backgroundName, value))
                    this.Background = NameToColor(value);
            }
            get { return backgroundName; } 
        }

        public Color Background
        {
            set 
            {
                if (SetProperty<Color>(ref background, value))
                    this.BackgroundName = ColorToName(value);
            }
            get { return background; }
        }

        public string ForegroundName
        {
            set
            {
                if (SetProperty<string>(ref foregroundName, value))
                    this.Foreground = NameToColor(value);
            }
            get { return foregroundName; }
        }

        public Color Foreground
        {
            set 
            {
                if (SetProperty<Color>(ref foreground, value))
                    this.ForegroundName = ColorToName(value);
            }
            get { return foreground; }
        }

        public DateTime DateTime
        {
            set
            {
                if (SetProperty<DateTime>(ref dateTime, value))
                {
                    this.FormattedDateTime = String.Format("{0:D} {1:t}", value, value);
                    this.SecondAngle = 6 * (dateTime.Second + dateTime.Millisecond / 1000.0);
                    this.MinuteAngle = 6 * dateTime.Minute + this.SecondAngle / 60;
                    this.HourAngle = 30 * (dateTime.Hour % 12) + this.MinuteAngle / 12;
                }
            }
            get { return dateTime; }
        }

        public string FormattedDateTime
        {
            set { SetProperty<string>(ref formattedDateTime, value); }
            get { return formattedDateTime; }
        }

        public double HourAngle
        {
            set { SetProperty<double>(ref hourAngle, value); }
            get { return hourAngle; }
        }

        public double MinuteAngle
        {
            set { SetProperty<double>(ref minuteAngle, value); }
            get { return minuteAngle; }
        }

        public double SecondAngle
        {
            set { SetProperty<double>(ref secondAngle, value); }
            get { return secondAngle; }
        }

        Color NameToColor(string name)
        {
            return (Color)colorsTypeInfo.GetDeclaredProperty(name).GetValue(null);
        }

        string ColorToName(Color color)
        {
            foreach (PropertyInfo property in colorsTypeInfo.DeclaredProperties)
                if (color.Equals((Color)property.GetValue(null)))
                    return property.Name;

            return "";
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

        protected void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
