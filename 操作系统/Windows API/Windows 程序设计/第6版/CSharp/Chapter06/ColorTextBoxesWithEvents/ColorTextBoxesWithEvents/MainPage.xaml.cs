using System.ComponentModel;
using Windows.UI;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace ColorTextBoxesWithEvents
{
    public sealed partial class MainPage : Page
    {
        RgbViewModel rgbViewModel;
        Brush textBoxTextBrush;
        Brush textBoxErrorBrush = new SolidColorBrush(Colors.Red);

        public MainPage()
        {
            this.InitializeComponent();

            // Get TextBox brush
            textBoxTextBrush = this.Resources["TextBoxForegroundThemeBrush"] as SolidColorBrush;

            // Create RgbViewModel and save as field
            rgbViewModel = new RgbViewModel();
            rgbViewModel.PropertyChanged += OnRgbViewModelPropertyChanged;
            this.DataContext = rgbViewModel;

            // Initialize to highlight color
            rgbViewModel.Color = new UISettings().UIElementColor(UIElementType.Highlight);
        }

        void OnRgbViewModelPropertyChanged(object sender, PropertyChangedEventArgs args)
        {
            switch (args.PropertyName)
            {
                case "Red":
                    redTextBox.Text = rgbViewModel.Red.ToString("F0");
                    break;

                case "Green":
                    greenTextBox.Text = rgbViewModel.Green.ToString("F0");
                    break;

                case "Blue":
                    blueTextBox.Text = rgbViewModel.Blue.ToString("F0");
                    break;
            }
        }

        void OnTextBoxTextChanged(object sender, TextChangedEventArgs args)
        {
            byte value;

            if (sender == redTextBox && Validate(redTextBox, out value))
                rgbViewModel.Red = value;

            if (sender == greenTextBox && Validate(greenTextBox, out value))
                rgbViewModel.Green = value;

            if (sender == blueTextBox && Validate(blueTextBox, out value))
                rgbViewModel.Blue = value;
        }

        bool Validate(TextBox txtbox, out byte value)
        {
            bool valid = byte.TryParse(txtbox.Text, out value);
            txtbox.Foreground = valid ? textBoxTextBrush : textBoxErrorBrush;
            return valid;
        }
    }
}
