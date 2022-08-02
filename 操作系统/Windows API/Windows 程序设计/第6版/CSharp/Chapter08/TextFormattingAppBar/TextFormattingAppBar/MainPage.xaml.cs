using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Documents;

namespace TextFormattingAppBar
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnBoldAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            CheckBox chkbox = sender as CheckBox;
            textBlock.FontWeight = (bool)chkbox.IsChecked ? FontWeights.Bold : FontWeights.Normal;
        }

        void OnItalicAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            CheckBox chkbox = sender as CheckBox;
            textBlock.FontStyle = (bool)chkbox.IsChecked ? FontStyle.Italic : FontStyle.Normal;
        }

        void OnUnderlineAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            CheckBox chkbox = sender as CheckBox;
            Inline inline = textBlock.Inlines[0];

            if ((bool)chkbox.IsChecked && !(inline is Underline))
            {
                Underline underline = new Underline();
                textBlock.Inlines[0] = underline;
                underline.Inlines.Add(inline);
            }
            else if (!(bool)chkbox.IsChecked && inline is Underline)
            {
                Underline underline = inline as Underline;
                Run run = underline.Inlines[0] as Run;
                underline.Inlines.Clear();
                textBlock.Inlines[0] = run;
            }
        }

        void OnFontColorAppBarRadioButtonChecked(object sender, RoutedEventArgs args)
        {
            textBlock.Foreground = (sender as RadioButton).Foreground;
        }
    }
}
