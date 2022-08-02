using System;
using Windows.UI.Xaml.Data;

namespace Petzold.ProgrammingWindows6.Chapter11
{
    public class MultiplyConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            double multiplier;

            if (value is double &&
                parameter is string &&
                Double.TryParse(parameter as string, out multiplier))
            {
                return (double)value * multiplier;
            }
            return value;
        }
        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            double divider;

            if (value is double &&
                parameter is string &&
                Double.TryParse(parameter as string, out divider))
            {
                return (double)value / divider;
            }
            return value;
        }
    }
}
