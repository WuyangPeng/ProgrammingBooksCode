using Windows.UI.Xaml.Controls;
using Petzold.ProgrammingWindows6.Chapter11;

namespace ColorItemsSource
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            itemsControl.ItemsSource = NamedColor.All;
        }
    }
}
