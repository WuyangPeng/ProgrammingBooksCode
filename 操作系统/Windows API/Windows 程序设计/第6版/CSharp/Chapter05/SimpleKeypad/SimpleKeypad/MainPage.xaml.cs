using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace SimpleKeypad
{
    public sealed partial class MainPage : Page
    {
        string inputString = "";
        char[] specialChars = { '*', '#' };

        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnCharButtonClick(object sender, RoutedEventArgs args)
        {
            Button btn = sender as Button;
            inputString += btn.Content as string;
            FormatText();
        }

        void OnDeleteButtonClick(object sender, RoutedEventArgs args)
        {
            inputString = inputString.Substring(0, inputString.Length - 1);
            FormatText();
        }

        void FormatText()
        {
            bool hasNonNumbers = inputString.IndexOfAny(specialChars) != -1;

            if (hasNonNumbers || inputString.Length < 4 || inputString.Length > 10)
                resultText.Text = inputString;

            else if (inputString.Length < 8)
                resultText.Text = String.Format("{0}-{1}", inputString.Substring(0, 3),
                                                           inputString.Substring(3));
            else
                resultText.Text = String.Format("({0}) {1}-{2}", inputString.Substring(0, 3),
                                                                 inputString.Substring(3, 3),
                                                                 inputString.Substring(6));
            deleteButton.IsEnabled = inputString.Length > 0;
        }
    }
}
