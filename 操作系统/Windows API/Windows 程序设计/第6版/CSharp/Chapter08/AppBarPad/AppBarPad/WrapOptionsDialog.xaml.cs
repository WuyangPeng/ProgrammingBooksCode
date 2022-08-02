using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace AppBarPad
{
    public sealed partial class WrapOptionsDialog : UserControl
    {
        static WrapOptionsDialog()
        {
            TextWrappingProperty = DependencyProperty.Register("TextWrapping",
                typeof(TextWrapping),
                typeof(WrapOptionsDialog),
                new PropertyMetadata(TextWrapping.NoWrap, OnTextWrappingChanged));
        }

        public static DependencyProperty TextWrappingProperty { private set; get; }

        public WrapOptionsDialog()
        {
            this.InitializeComponent();
        }

        public TextWrapping TextWrapping
        {
            set { SetValue(TextWrappingProperty, value); }
            get { return (TextWrapping)GetValue(TextWrappingProperty); }
        }

        static void OnTextWrappingChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            (obj as WrapOptionsDialog).OnTextWrappingChanged(args);
        }

        void OnTextWrappingChanged(DependencyPropertyChangedEventArgs args)
        {
            foreach (UIElement child in stackPanel.Children)
            {
                RadioButton radioButton = child as RadioButton;
                radioButton.IsChecked = (TextWrapping)radioButton.Tag == (TextWrapping)args.NewValue;
            }
        }

        void OnRadioButtonChecked(object sender, RoutedEventArgs args)
        {
            this.TextWrapping = (TextWrapping)(sender as RadioButton).Tag;
        }
    }
}
