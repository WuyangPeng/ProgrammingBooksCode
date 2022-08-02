using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace SilentPiano
{
    public sealed partial class Octave : UserControl
    {
        static readonly DependencyProperty lastKeyVisibleProperty =
                DependencyProperty.Register("LastKeyVisible",
                        typeof(bool), typeof(Octave),
                        new PropertyMetadata(false, OnLastKeyVisibleChanged));

        public Octave()
        {
            this.InitializeComponent();
        }

        public static DependencyProperty LastKeyVisibleProperty
        {
            get { return lastKeyVisibleProperty; }
        }

        public bool LastKeyVisible
        {
            set { SetValue(LastKeyVisibleProperty, value); }
            get { return (bool)GetValue(LastKeyVisibleProperty); }
        }

        static void OnLastKeyVisibleChanged(DependencyObject obj, 
                                            DependencyPropertyChangedEventArgs args)
        {
            (obj as Octave).lastKey.Visibility = 
                (bool)args.NewValue ? Visibility.Visible : Visibility.Collapsed;
        }
    }
}
