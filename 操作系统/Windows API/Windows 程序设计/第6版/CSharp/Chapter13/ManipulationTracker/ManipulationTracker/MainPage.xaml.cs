using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace ManipulationTracker
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnManipulationModeCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            // Get composite ManipulationModes value of checked CheckBoxes
            ManipulationModes manipulationModes = ManipulationModes.None;

            foreach (UIElement child in checkBoxPanel.Children)
            {
                ManipulationModeCheckBox checkBox = child as ManipulationModeCheckBox;

                if ((bool)checkBox.IsChecked)
                    manipulationModes |= checkBox.ManipulationModes;
            }

            // Set ManipulationMode property of each Rectangle
            foreach (UIElement child in rectanglePanel.Children)
                child.ManipulationMode = manipulationModes;
        }

        protected override void OnManipulationDelta(ManipulationDeltaRoutedEventArgs args)
        {
            // OriginalSource is always Rectangle because nothing else has its
            //     ManipulationMode set to anything other than ManipulationModes.None
            Rectangle rectangle = args.OriginalSource as Rectangle;
            CompositeTransform transform = rectangle.RenderTransform as CompositeTransform;

            transform.TranslateX += args.Delta.Translation.X;
            transform.TranslateY += args.Delta.Translation.Y;

            transform.ScaleX *= args.Delta.Scale;
            transform.ScaleY *= args.Delta.Scale;

            transform.Rotation += args.Delta.Rotation;

            base.OnManipulationDelta(args);
        }
    }
}
