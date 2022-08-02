using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Petzold.ProgrammingWindows6.Chapter11;

namespace HorizontalListBox
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnItemLoaded(object sender, RoutedEventArgs args)
        {
            System.Diagnostics.Debug.WriteLine("Item Loaded: " +
                ((sender as FrameworkElement).DataContext as NamedColor).Name);
        }
    }
}
