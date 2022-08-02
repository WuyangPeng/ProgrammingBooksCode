using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Automation.Peers;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace BetterCharacterInput
{
    public sealed partial class RudimentaryTextBox : UserControl
    {
        public RudimentaryTextBox()
        {
            this.InitializeComponent();
            this.IsTabStop = true;
            this.Text = "";
        }

        public string Text { set; get; }

        protected override void OnTapped(TappedRoutedEventArgs args)
        {
            this.Focus(FocusState.Programmatic);
            base.OnTapped(args);
        }

        protected override void OnGotFocus(RoutedEventArgs args)
        {
            Window.Current.CoreWindow.CharacterReceived += OnCoreWindowCharacterReceived;
            base.OnGotFocus(args);
        }

        protected override void OnLostFocus(RoutedEventArgs args)
        {
            Window.Current.CoreWindow.CharacterReceived -= OnCoreWindowCharacterReceived;
            base.OnLostFocus(args);
        }

        protected override AutomationPeer OnCreateAutomationPeer()
        {
            return new RudimentaryTextBoxPeer(this);
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
