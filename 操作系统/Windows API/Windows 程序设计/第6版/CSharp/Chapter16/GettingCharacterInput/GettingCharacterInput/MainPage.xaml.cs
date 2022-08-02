using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace GettingCharacterInput
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Window.Current.CoreWindow.CharacterReceived += OnCoreWindowCharacterReceived;
        }

        void OnCoreWindowCharacterReceived(CoreWindow sender, CharacterReceivedEventArgs args)
        {
            // Process Backspace key
            if (args.KeyCode == 8 && txtblk.Text.Length > 0)
            {
                txtblk.Text = txtblk.Text.Substring(0, txtblk.Text.Length - 1);
            }
            // All other keys    
            else
            {
                txtblk.Text += (char)args.KeyCode;
            }
        }
    }
}
