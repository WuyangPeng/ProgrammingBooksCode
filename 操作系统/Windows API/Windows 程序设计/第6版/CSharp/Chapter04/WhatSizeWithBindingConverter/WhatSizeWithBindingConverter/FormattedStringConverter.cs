using System;
using System.Globalization;
using Windows.UI.Xaml.Data;

namespace WhatSizeWithBindingConverter
{
    public class FormattedStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is IFormattable && 
                parameter is string && 
                !String.IsNullOrEmpty(parameter as string) &&
                targetType == typeof(string))
            {
                if (String.IsNullOrEmpty(language))
                    return (value as IFormattable).ToString(parameter as string, null);

                return (value as IFormattable).ToString(parameter as string, 
                                                        new CultureInfo(language));
            }

            return value;
        }
        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return value;
        }
    }
}
