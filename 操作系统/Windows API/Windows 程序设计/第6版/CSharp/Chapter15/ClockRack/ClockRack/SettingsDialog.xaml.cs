// using System.Reflection;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Petzold.ProgrammingWindows6.Chapter11;

namespace ClockRack
{
    public sealed partial class SettingsDialog : UserControl
    {
        public SettingsDialog(TimeZoneManager timeZoneManager)
        {
            this.InitializeComponent();

            // Set ItemsSource for time zone ComboBox
            timeZoneComboBox.ItemsSource = timeZoneManager.DisplayInformation;

            // Set ItemsSource for foreground and background ComboBoxes
            foregroundComboBox.ItemsSource = NamedColor.All;
            backgroundComboBox.ItemsSource = NamedColor.All;
        }

        void OnLocationTextBoxTextChanged(object sender, TextChangedEventArgs args)
        {
            (this.DataContext as TimeZoneClockViewModel).Location = (sender as TextBox).Text;
        }
    }
}
