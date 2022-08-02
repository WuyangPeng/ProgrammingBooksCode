using System;
using Windows.UI.Xaml.Data;

namespace Petzold.ProgrammingWindows6.Chapter11
{
    public class ByteToHexStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return ((byte)value).ToString("X2");
        }
        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return value;
        }
    }
}
