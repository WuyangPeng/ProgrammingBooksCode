using System;
using Windows.UI;
using Windows.UI.Xaml.Data;

namespace Petzold.ProgrammingWindows6.Chapter11
{
    public class ColorToContrastColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            Color clr = (Color)value;
            double grayShade = 0.30 * clr.R + 0.59 * clr.G + 0.11 * clr.B;
            return grayShade > 128 ? Colors.Black : Colors.White;
        }
        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return value;
        }
    }
}
