using System;
using Windows.UI.Xaml.Data;

namespace YellowPad
{
    public class IndexToPageNumberConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return String.Format("Page {0}", (int)value + 1);
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return value;
        }
    }
}
